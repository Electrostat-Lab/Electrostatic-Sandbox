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

### Platform Binding APIs
The Platform Binding APIs facilitate the integration of various APIs and frameworks into the SDK:
- **Serial4j**: Serial communication library.
- **Jector**: Dependency injection framework.
- **Articular-ES**: Articulated simulation components.
- **Jme-alloc**: Memory allocation library.
- **jSnapLoader**: Snapshot loader.
- **Automata4j**: Automata processing library.
- **ElectroIO**: Interface for the ElectroIO project.
- **Parallel4j**: Parallel processing library.

## Architecture Diagram

```dot
digraph ElectrostaticSandboxSDK {
    rankdir=TB; // Top to Bottom
    fontsize=12;
    node [shape=rectangle, style=filled, color=lightgrey, fontname="Helvetica"];
    edge [fontname="Helvetica"];

    // Main Components
    ElectrostaticSandboxSDK [label="Electrostatic-Sandbox SDK", shape=ellipse, style=filled, color=lightblue];
    ElectroSim [label="ElectroSim Project"];
    ElectroNetSoft [label="ElectroNetSoft Project"];
    ElectroIO [label="ElectroIO Project"];
    HAL [label="Hardware Abstraction Layer (HAL)"];

    // Relationships
    ElectrostaticSandboxSDK -> ElectroSim;
    ElectrostaticSandboxSDK -> ElectroNetSoft;
    ElectrostaticSandboxSDK -> ElectroIO;

    subgraph cluster_ElectroSim {
        label="ElectroSim Project";
        color=lightgrey;
        style=dashed;

        RTI_IEEE [label="IEEE-1516 RTI"];
        FED_IEEE [label="RTI Federates"];
        FOM_IEEE [label="FOM"];
        
        ElectroSim -> RTI_IEEE;
        ElectroSim -> FED_IEEE;
        ElectroSim -> FOM_IEEE;
    }

    subgraph cluster_ElectroNetSoft {
        label="ElectroNetSoft Project";
        color=lightgrey;
        style=dashed;

        NETSOFT_INFRA [label="Networking and Software Infrastructure"];
        OS_RES [label="Base OS Resources and Std Libraries APIs"];
        Std [label="Std Libs"];
        OSRES [label="Base OS Resources"];
        
        ElectroNetSoft -> NETSOFT_INFRA;
        NETSOFT_INFRA -> OS_RES;
        OS_RES -> Std;
        OS_RES -> OSRES;
    }

    subgraph cluster_ElectroIO {
        label="ElectroIO Project";
        color=lightgrey;
        style=dashed;

        ElectroMIO [label="ElectroMIO"];
        ElectroKIO [label="ElectroKIO"];
        
        ElectroIO -> ElectroMIO;
        ElectroIO -> ElectroKIO;

        subgraph cluster_ElectroMIO {
            label="ElectroMIO";
            color=lightgrey;
            style=dashed;

            GPIO [label="GPIO"];
            UART [label="USART"];
            ADC [label="ADC"];
            EEPROM [label="EEPROM"];
            TWI [label="TWI"];
            SPI [label="SPI"];
            SOCKET [label="WiFi-Sockets"];
            
            ElectroMIO -> GPIO;
            ElectroMIO -> UART;
            ElectroMIO -> ADC;
            ElectroMIO -> EEPROM;
            ElectroMIO -> TWI;
            ElectroMIO -> SPI;
            ElectroMIO -> SOCKET;
        }

        subgraph cluster_ElectroKIO {
            label="ElectroKIO";
            color=lightgrey;
            style=dashed;

            USB [label="USB-FS"];
            RS232 [label="RS232"];
            PARA [label="IEEE-1284"];
            ETH [label="IEEE-802.3"];
            CD [label="DVD-CDROM"];
            PCI [label="PCI-e"];
            
            ElectroKIO -> USB;
            ElectroKIO -> RS232;
            ElectroKIO -> PARA;
            ElectroKIO -> ETH;
            ElectroKIO -> CD;
            ElectroKIO -> PCI;
        }
    }

    subgraph cluster_PlatformBindingAPIs {
        label="Platform Binding APIs";
        color=lightgrey;
        style=dashed;

        SERIAL [label="Serial4j"];
        JECTOR [label="Jector"];
        ART [label="Articular-ES"];
        JME [label="Jme-alloc"];
        JSNAP [label="jSnapLoader"];
        AUTO [label="Automata4j"];
        ELECTROIO [label="ElectroIO"];
        PARALLEL [label="Parallel4j"];

        PLATFORM_BINDING [label="Platform Binding APIs", shape=ellipse, style=filled, color=lightgreen];
        
        PLATFORM_BINDING -> SERIAL;
        PLATFORM_BINDING -> JECTOR;
        PLATFORM_BINDING -> ART;
        PLATFORM_BINDING -> JME;
        PLATFORM_BINDING -> JSNAP;
        PLATFORM_BINDING -> AUTO;
        PLATFORM_BINDING -> ELECTROIO;
        PLATFORM_BINDING -> PARALLEL;
    }
}

