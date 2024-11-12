#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/mobility-module.h"
#include "ns3/animation-interface.h"
#include "ns3/udp-echo-helper.h"

using namespace ns3;

// Define the Soil Moisture Sensor Class
class SoilMoistureSensor {
public:
    SoilMoistureSensor(std::string address) : address(address) {}

    float ReadMoistureLevel() {
        float level = static_cast<float>(rand() % 100);
        NS_LOG_UNCOND("Sensor " << address << ": Generated Moisture Level = " << level);
        return level;
    }

    std::string GetAddress() const {
        return address;
    }

private:
    std::string address;
};

int main(int argc, char *argv[]) {
    NS_LOG_COMPONENT_DEFINE("MainSimulation");

    srand(static_cast<unsigned int>(time(0)));
    SoilMoistureSensor sensor("Sensor_1");

    NodeContainer nodes;
    nodes.Create(2);

    // Setup Point-to-Point link
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));
    NetDeviceContainer devices = pointToPoint.Install(nodes);

    // Install Internet Stack on nodes
    InternetStackHelper internet;
    internet.Install(nodes);

    // Assign IP addresses
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);

    // Set up Mobility Model
    MobilityHelper mobility;
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(nodes);

    Ptr<MobilityModel> mob1 = nodes.Get(0)->GetObject<MobilityModel>();
    mob1->SetPosition(Vector(1.0, 2.0, 0.0));

    Ptr<MobilityModel> mob2 = nodes.Get(1)->GetObject<MobilityModel>();
    mob2->SetPosition(Vector(5.0, 2.0, 0.0));

    // UDP Echo Server on Node 1 (Network Layer)
    UdpEchoServerHelper echoServer(9);
    ApplicationContainer serverApps = echoServer.Install(nodes.Get(1));
    serverApps.Start(Seconds(0.0));
    serverApps.Stop(Seconds(10.0));

    // UDP Echo Client on Node 0 (Sensor) to send data to the server
    UdpEchoClientHelper echoClient(interfaces.GetAddress(1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(10));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
    clientApps.Start(Seconds(1.0));
    clientApps.Stop(Seconds(10.0));

    // NetAnim setup for visualization
    AnimationInterface anim("/home/nabin/ns-allinone-3.41/ns-3.41/IoT1.xml");

    // Set initial positions and descriptions for nodes
    anim.SetConstantPosition(nodes.Get(0), 1.0, 2.0);
    anim.SetConstantPosition(nodes.Get(1), 5.0, 2.0);
    anim.UpdateNodeDescription(nodes.Get(0), "Sensor Node (UDP Client)");
    anim.UpdateNodeDescription(nodes.Get(1), "Network Node (UDP Server)");

    // Enhanced Visualization Settings
    anim.UpdateNodeColor(nodes.Get(0), 255, 0, 0);  // Sensor: Red color
    anim.UpdateNodeColor(nodes.Get(1), 0, 0, 255);  // Network Node: Blue color

    // Schedule events for enhanced UDP visualization
    Simulator::Schedule(Seconds(1.0), [&sensor, &anim, nodes]() {
        NS_LOG_UNCOND("Sensor Node: Generating data...");
        float moistureLevel = sensor.ReadMoistureLevel();
        NS_LOG_UNCOND("Current moisture level: " << moistureLevel);  // Log the moisture level

        // Visual cue for data generation
        anim.UpdateNodeDescription(nodes.Get(0), "Sensor: Data Generated");
        anim.UpdateNodeColor(nodes.Get(0), 0, 255, 0);  // Change to green for data generation
    });

    Simulator::Schedule(Seconds(1.5), [&anim, nodes]() {
        NS_LOG_UNCOND("Sensor Node: Transmitting data...");

        // Visualize UDP packet transmission
        anim.UpdateNodeDescription(nodes.Get(0), "Sensor: Transmitting Data (UDP Packet)");
        anim.UpdateNodeColor(nodes.Get(0), 255, 165, 0);  // Orange for transmission
        anim.UpdateNodeColor(nodes.Get(1), 0, 255, 255);  // Cyan for packet received indication
    });

    Simulator::Schedule(Seconds(2.0), [&anim, nodes]() {
        NS_LOG_UNCOND("Network Node: Receiving data...");

        // Network Node color and size change to show data reception
        anim.UpdateNodeDescription(nodes.Get(1), "Network: Data Received (UDP Packet)");
        anim.UpdateNodeColor(nodes.Get(1), 0, 255, 255);  // Cyan for data received
    });

    // Enable pcap tracing to capture UDP packets for post-simulation analysis
    pointToPoint.EnablePcapAll("udp-packets-trace");

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
