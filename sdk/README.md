# The Electrostatic-Sandbox SDK suite

## Preface

The Electrostatic-Sandbox SDK is a high-performance infrastructure framework for distributed systems simulation based on the IEEE-1516 HLA Specification and NASA DSES. It is designed to provide a comprehensive set of tools and libraries for building and managing large-scale simulations, leveraging various platform binding APIs and hardware abstraction layers.

## Uses

The SDK can be utilized for:
- Developing distributed simulation systems.
- Connecting to peripheral digital/analog devices via simulation interfaces.
- Simulating large-scale missions and projects.
- Building in-home, office, and outdoor distributed IoT projects.

## Subprojects

### ElectroSim Project
The ElectroSim Project encompasses the following components:
- **IEEE-1516 RTI**: Real-Time Infrastructure for distributed simulations.
- **RTI Federates**: Components that interact in a distributed simulation.
- **FOM**: Federation Object Model used to define the data structures for simulation entities.

### ElectroNetSoft Project
The ElectroNetSoft Project includes:
- **Networking and Software Infrastructure**: Core networking capabilities and software infrastructure.
- **Base OS Resources and Std Libraries APIs**: Standard libraries and base OS resources.
- **Std Libs**: Standard libraries utilized by the SDK.
- **Base OS Resources**: Fundamental OS resources required for simulation.

### ElectroIO Project
The ElectroIO Project is divided into two subprojects, ElectroMIO and ElectroKIO:
- **ElectroMIO**: Provides modules for interacting with microcontroller I/O such as GPIO, USART, ADC, EEPROM, TWI, SPI, and WiFi-Sockets.
- **ElectroKIO**: Covers connectivity modules including USB-FS, RS232, IEEE-1284, IEEE-802.3, DVD-CDROM, and PCI-e.

## Architecture Diagram

<img src="https://electrostat-lab.github.io/Electrostatic-Sandbox/electrostatic-sandbox-framework/docs/electrostatic-sdk.svg"/>

