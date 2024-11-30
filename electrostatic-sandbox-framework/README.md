# Electrostatic-sandbox-framework

This framework houses a standardization as a sandbox for the workstation abstracting the following: 
- Digital Communication Protocols.
- File Systems APIs.
- Memory Manipulation APIs.
- Other Operating System APIs.

This framework has 2 environments and provides binaries for 2 devices:
- The main board.
- The externally pluggable modular boards.

## Hardware-Software Specification:

| **Item** | **Explanation** |
|--------|---------------|
| _Problem Definition_ | |
| _Scientific Recall of the problem_ | |
| _General Approach_ | |
| _Specialized Approach_ | |
| _Scientific Approach_ | |
| _The Framework components_ | |

## The framework parts:
**The Native Electrostatic API**
- electrostatic-core: provides the core of the electrostatic framework written purely in C.
- electrostatic-examples: provides direct examples in the form of executables for the core API.

**The Java Binding API (Electrostatic4j aka. _e4j_)**
- electrostatic4j-core: the core Java binding API, containing the native image loader and the binding Java side of the glue code.
- electrostatic4j-native: the native Java binding API, containing the glue code written purely in C.
- electrostatic4j-examples: implicit examples for the electrostatic API through the Java binding API.
- electrostatic4j-android: android glue code (not planned!).

## Building the framework: 
- [x] Building the `electrostatic-core` module into a static and a dynamic library:

- [x] Building the `electrostatic-examples` module into an executable and linking with the `electrostatic-core` binaries:

- [x] Building the `electrostatic4j` library and runtime linking:

- [x] Running the `electrostatic4j-examples` examples: 


