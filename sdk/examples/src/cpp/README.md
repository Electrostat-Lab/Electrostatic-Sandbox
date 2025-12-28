# C++ Programming Language 

> [!TIPS]
> Introduction:
> The following is an introduction taken directly from "Professional Assembly Language by Richard Blum" on the types of the high-level programming languages and their uses. 
> Types of high-level languages: While programmers can choose from many different HLLs available, they all can be classified into two different categories, based on how they are run on the computer:
> * Compiled languages.
> * Interpreted languages.
> While it is possible for different implementations of the same programming language to be either compiled or interpreted (e.g., the Python programming language), these categories are used to show how a particular HLL implementation defines how the programs are run on the processor. The following sections describe the methods used to run programs and show how they affect how the processor operates with them.

> * Compiled languages:
> Most production applications are created using compiled HLLs. The programmer creates a program
> using common statements for the language which carry out the logic of the application. The text program statements are then converted into a set of instruction codes that can be run on the processor.
>
> Usually, what is commonly called compiling a program is actually a two-step process:
> * Compiling the HLL statements into raw instruction codes.
> * Linking the raw instruction codes to produce an executable program.
>
> The compiling step converts the text programming language statements into the instruction codes
> required to carry out the application function. Each of the HLL lines of code are matched up with one or
> more instruction codes pertaining to the specific processor on which the application will run. For example, the simple HLL code:
> ```c
> int main() {
>   int i = 1;
>  exit(0);
> }
> ```
> is compiled into the following IA-32 instruction codes:
> ```
> 55
> 89 E5
> 83 EC 08
> C7 45 FC 01 00 00 00
> 83 EC 0C
> 6A 00
> E8 D1 FE FF FF
> ```
> This step produces an intermediate file, called an object code file. The object code file contains the instruction codes that represent the core of the application functions, as shown above. The object code file itself cannot be run by the operating system. Often the host operating system requires special file formats for executable files (program files that can be run on the system), and the HLL program may require program functions from other object files. Another step is required to add these components.
> After the code is compiled into an object file, a linker is used to link the application object code file with any additional object files required by the application and to create the final executable output file. The output of the linker is an executable file that can only be run on the operating system for which the program is written. Unfortunately, each operating system uses a different format for executable files, so an application compiled on a Microsoft Windows workstation will not work as is on a Linux workstation, and vice versa.
>
> Object files that contain commonly used functions can be combined into a single file, called a library
> file. The library file can then be linked into multiple applications either at compile time (called static libraries), or at the time the application is run on the system (called dynamic libraries).
>
> * Interpreted languages:
> As opposed to compiled programs, which run by themselves on a processor, an interpreted language
> program is read and run by a separate program. The separate program is a host for the application program, reading and interpreting the program as it is processed. It is the job of the host program to convert the interpreted program code into the proper instruction codes for the processor as the program is running.
> Obviously, the downside to using interpreted languages is speed. Instead of the program being com-
> piled directly to instruction codes that are run on the processor, an intermediary program reads each line of program code and processes the required functions. The amount of time the host program takes to read the code and execute it adds additional delays to the execution of the application.
>
> * What Is Assembly Language?
> With the resulting reduction in speed when using interpreted languages, you may be wondering why
> anyone still uses them. One answer is convenience. With compiled programs, every time a change is
> made to the program, the program must be recompiled and relinked with the proper code libraries. With
> interpreted programs, changes can be quickly made to the source code file and the program rerun to
> check for errors. In addition, with interpreted languages, the interpreter application automatically determines what functions need to be included with the core code to support functions. 
>
> Today’s programming language environment muddies the waters between compiled and interpreted languages. No one specific language can be classified in either category. Instead, individual implementations of different HLLs are categorized. For example, while many BASIC programming implementations require interpreters to interpret the BASIC code into an executable program, there are many BASIC implementations that enable the programmer to compile the BASIC programs into executable instruction code.
>
> * Hybrid languages
> Hybrid languages are a recent trend in programming that combine the features of a compiled program
> with the versatility and ease of an interpreted program. A perfect example is the popular Java programing language. The Java programming language is compiled into what is called byte code. The byte code is similar to the instruction code you would see on a processor, but is itself not compatible with any current processor family (although there have been plans to create a processor that can run Java byte code as instruction sets).
> Instead, the Java byte code must be interpreted by a **Java Virtual Machine (JVM)**, running separately on the host computer. The Java byte code is portable, in that it can be run by any JVM on any type of host computer. The advantage is that different platforms can have their own specific JVMs, which are used to interpret the same Java byte code without it having to be recompiled from the original source code.

Some C++11/17 examples taken from the book "C++ Programming Language by Bjarne Stroustrup" to dissect the C++ STL and language features.

## Outline:
* Chapter.01: 
    * 1.1: C++ Projects Codebase Model.
    * 1.2: C++ Compilers and Compilation phases.
    * 1.3: C++ Native Executables and Executables lifecycle.
    * 1.4: C++ Runtime Programs Memory Model and Processes.
    * 1.5: Profiling C++ process Memory on GNU/Linux Systems.
* Chapter.02:
    * 2.1: C++ Program Design around RAII.
    * 2.2: C++ Classes Constructors (e.g., Base constructors and Members constructors).
    * 2.3: C++ Instances construction lifecycle.
    * 2.4: C++ Instances construction maneuvers (e.g., Copying and Moving construction).
    * 2.5: C++ Instances destructor lifecycle.
    * 2.6: C++ Memory Ownership.
    * 2.7: Smart pointers and ownership transfer strategies.

## Chapter.01:
### 1.1 C++ Projects Codebase Model:
Conventionally, a C/C++ project is composed of 2 directories; one for headers and usually named `include` or `headers`, and the other one for source code and usually named `src` or `sources` or conventionally `lib` on Unix-based systems.   

* Header Files:
Headers are code files ending with these file extensions `.h`, `.hxx`, or `.hpp`, and theoretically it could be a text file ending with any extension, but must be parsable by the compiler.

A header file should contain preprocessor directives, functions declarations, namespaces, classes and structures declarations, and constant expressions. In practice in C++, functions and constant expressions ought to be encapsulated inside namespaces and classes. 

Namespaces, Classes, and Functions should be all of self-explanatory names (e.g., if OOP paradigm is used, then classes should name abstract types for representing real objects). 

> [!NOTE]
> * What's meant by the word "declarations"?
>     * A declaration or a prototype, in its abstract, is a model or a structural template for the compiler to bind with the source code during the linking process; that is each definition should have a matching declaration in order for the compilation to be successful.
>     * Each function call should have its own declaration and definition. 
>     * Conventionally, but not necessarily, the declaration shall appear in the header files, and the definitions shall be in the source files. Sometimes, a declaration can be omitted or merged into the definition; that is in the case of inline definitions.
> * A preprocessor directive, as the name implies, is happened to be processed (by the lexical analysis of the compiler) before the rest of the header or the source file.
> * The compiler processes the header files before the sources to determine compile-time constants and declarations. To include a header file to be processed, an `#include<...>` preprocessor directive must be present in order to call the collate the header file for the compiler preprocessor. Furthermore, the file to be included must be present inside the handled filesystem path to the compiler in the compiler preprocessor include `-I` arguments.

* Source Files:
Source files are text-based C/C++ code housing compilable units to be compiled by the compiler together with their definition files (i.e., the header files).

* Designing Native Libraries and APIs:
Usually, a C/C++ compilation unit design is composed of 2 parts; a declaration for the types and the functions to be used and that goes into a single header file, and a compilation unit representing a single function and/or class definition from that header file that does a very specific thing (e.g., `vector.h`, and `vector_add.c`, `vector_dot_product.c` or `Vector.hpp` and `VectorAdd.cpp`, `VectorDotProduct.cpp` in case of C++).

Designing the C/C++ compilation units this way will ensure that only the compiler linker will only link the necessary used compilation units by encountering their functional dispatches in the final source code that will be compiled as an executable binary.

> [!NOTE]
> 
> * An executable program is a machine-code based binary created for a specific hardware/system combination (e.g., $$Platform-Variant=(intel-x86 \land Linux)$$); it is not portable, say, from a Mac to a Windows PC. When we talk about portability of C++ programs, we usually mean portability of source code; that is, the source code can be successfully compiled and run on a variety of systems. However, not portability of an executable binary built on a particular platform.
> 
> * An executable binary usually have the file extension ".exe", and it's a linkable binary that can be loaded and linked by the operating system loader.
> ### Example:
> * Recall a simple C program that built as an executable:
> ```c
> #include <stdio.h>
> int main() {
>   return 0;
> }
> ```
> * Disassembling it into an assembler binary usually entails a `<start>` and `<main>` sections; those where the program starts, the start section invokes the GLbic `<main>` section:
> ```c
> $ objdump -Sd ./hello.o | grep _start 
> 1004:	48 8b 05 c5 2f 00 00 	mov    0x2fc5(%rip),%rax        # 3fd0 <__gmon_start__@Base>
> 0000000000001040 <_start>:
> 105b:	ff 15 5f 2f 00 00    	call   *0x2f5f(%rip)        # 3fc0 <__libc_start_main@GLIBC_2.34>
> ...
> ```
> * Now, this is another shift-in-topic into reverse engineering which depends mainly on disassembling binaries and examining what they do, but more of like using other human-friendly tools and libraries. This activity is used a lot in malware reverse engineering.

### 1.2: C++ Compilers and Compilation phases:

The following is a short explanatory image for the compilation phases for native binaries:
[]()

Here you could visualize that the following steps are encountered:
1) Preprocessing header files and declarative statements.
2) Compiling the native source code into platform-dependent object code (or machine code).
3) Linking pre-compiled object code into an executable binary via the compiler linker (static linking). 

> [!NOTE]
> * The last step though, particularly can vary based on the type of the compilation units whether they were static object files or dynamic shared object files. In case of dynamically linked libraries (dll), the dynamic linker (e.g., ldd) is responsible for opening the linkable binary and loading its function table into the memory of the process to dispatch its functions.
> * There are various C/C++ compilers out there; most of them are open source (e.g., GCC/G++, LLVM/Clang/Clang++), while others are commercial (e.g., MS C/C++ Compiler). The diversion of the compilers and various infrastructures of C++ had warranted the C++ committee to participate in a language standardization under ANSI and ISO.

## Testcases include:
- [x] C++ Classes language features in [test_classes_features.cpp]().
- [ ] C++ State Machines library design using C++ types and classes in [techdemos/automata]().
- [ ] C++ Strings in [test_strings.cpp]().
- [ ] C++ Smart Pointers and memory allocators in [test_pointers.cpp]()
- [ ] C++ Command-State Patterns using pointers to functions in [test_patterns.cpp]().

### References:
1) A Tour of C++ (C++ In-Depth Series): Second Edition by Bjarne Stroustrup.
2) C++ The Programming Language by Bjarne Stroustrup.
3) C++ for Scientists and Engineers.
4) C++ The Complete Reference
5) Professional Assembly Language 
6) The Cpp Reference Manual.
7) GoF Design Patterns Manual.
8) Data-oriented Design by Richard Fabian.
9) Introduction to the Theory of Computation.
10) Switching and Finite Automata: Cambridge Press.