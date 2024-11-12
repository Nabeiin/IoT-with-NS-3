# IoT-with-NS-3
Building IoT architecture  with NS-3 and C++
Soil Moisture Sensor IoT Simulation
**Overview**

This project simulates the interaction between a soil moisture sensor and a network layer in an IoT architecture using the ns-3 network simulator. The simulation demonstrates data generation from a soil moisture sensor, transmission using the UDP protocol, and reception by a network node. Visualization is provided through NetAnim, illustrating the data flow and node interactions.


**Features**

    Sensor Simulation: Simulates a soil moisture sensor that generates random data.
    UDP Communication: Uses UDP for data transmission between the sensor (application layer) and the network node.
    Mobility Models: Assigns fixed positions to nodes for simulation purposes.
    Visualization: Generates an XML file compatible with NetAnim for visual representation of the simulation.
    Packet Capture: Enables packet capture for further analysis.

    
  ** ** Prerequisites****
  

Before running the project, ensure you have the following installed:

    Ubuntu 20.04
    ns-3.41 (built using CMake)
    NetAnim (for visualization)
    C++ compiler (e.g., g++)
   ** Project Structure**
   project-name/
├── src/
│   └── IoT1.cc           # Main simulation code
├── CMakeLists.txt        # Build configuration file
├── output/
│   └── IoT1.xml          # NetAnim-compatible XML output
├── README.md             # Documentation
└── .gitignore            # Excluded files (e.g., binaries, logs)



1. Installation of ns-3 with CMake (Using a tar.bz2 File)
Commands:
# Update and install necessary dependencies
nabin@nabin:~$ sudo apt update
nabin@nabin:~$ sudo apt upgrade
nabin@nabin:~$ sudo apt install build-essential gcc g++ python3 python3-pip cmake libgtk2.0-dev pkg-config libxml2-dev qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools libqt5svg5-dev git unzip

# Download ns-3 tar.bz2 file
nabin@nabin:~$ wget https://www.nsnam.org/release/ns-allinone-3.41.tar.bz2

# Extract the tar.bz2 file
nabin@nabin:~$ tar -xjf ns-allinone-3.41.tar.bz2

# Navigate to the extracted directory
nabin@nabin:~$ cd ns-allinone-3.41

# Configure ns-3 with CMake
nabin@nabin:~/ns-allinone-3.41$ ./build.py --enable-examples --enable-tests


2. Setting Up Python Bindings
Commands:
# Install Python bindings
nabin@nabin:~/ns-allinone-3.41$ sudo apt install python3-dev python3-setuptools
nabin@nabin:~/ns-allinone-3.41$ pip3 install cppyy CPyCppyy cppyy-backend cppyy-cling


3. Verifying the ns-3 Installation
Commands:
# Navigate to ns-3 directory
nabin@nabin:~/ns-allinone-3.41$ cd ns-3.41

# Build ns-3 examples
nabin@nabin:~/ns-allinone-3.41/ns-3.41$ ./ns3 configure --build-profile=debug --enable-examples --enable-tests
nabin@nabin:~/ns-allinone-3.41/ns-3.41$ ./ns3 build

4. Writing IoT Simulation Code (Physical to Network Layer)
Using Geany as a Code Editor
# Open Geany to write/edit the IoT simulation code
nabin@nabin:~/ns-allinone-3.41/ns-3.41$ geany scratch/IoT1.cc &

5. Building the Simulation Code
Commands:
# Use CMake to build the simulation
nabin@nabin:~/ns-allinone-3.41/ns-3.41$ mkdir build
nabin@nabin:~/ns-allinone-3.41/ns-3.41$ cd build
nabin@nabin:~/ns-allinone-3.41/ns-3.41/build$ cmake ..
nabin@nabin:~/ns-allinone-3.41/ns-3.41/build$ make

6. Running the IoT Simulation
Commands:
# Run the IoT simulation
nabin@nabin:~/ns-allinone-3.41/ns-3.41/build$ ./scratch/IoT1

7. Visualizing the Simulation in NetAnim
Commands:

# Navigate to the NetAnim directory
nabin@nabin:~/ns-allinone-3.41/ns-3.41$ cd ../../netanim-<version>

# Launch NetAnim
nabin@nabin:~/ns-allinone-3.41/netanim-<version>$ ./NetAnim
Steps in NetAnim:

    Load the IoT1.xml file generated during the simulation run.
    Play the animation to observe the UDP workflow:
        Data generation at the sensor node.
        Transmission from the sensor node to the network node.
        Reception at the network node.
