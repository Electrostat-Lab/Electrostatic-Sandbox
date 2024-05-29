# <img src="https://github.com/Electrostat-Lab/Electrostatic-Sandbox/blob/master/assets/electrostatic-logo-2.png" height=60 width=80/> Electrostatic-Sandbox

## Preface:
An electronic monstrosity workstation designed to examine and develop systems for distributed simulations by providing an integrated environment housing the basic nostalgic communication protocols (i.e., Serial and Parallel COMs), the abstract networking interfaces, and a range of other electronic modules providing standards for controller interfaces, and sensor modules (e.g., the underdeveloped ShiftAvr, and Arduinos). 


## Hardware-Software specification overview:

| Item | Explanation |
|-------|-------------|
| _Problem Definition_ | Obtaining an integrated environment to efficiently integrate embedded systems with other resources like graphics-based applications and games, with an essential predicate of providing the blend of the old communication protocols, and externally pluggable electronic modules. |
| _Scientific Recall of the Problem_ | Using the abstract _Set Theory_ and _Predicate Logic_ annotations, the main problem can be described as a universal set of predicates. In other words, the main problem is the universe set $P_{Env.}$; where _P_ designates a problem universe set, and _Env._ stands for the environment. Now, $P_{Graphics}$ represents another requirement set of graphics-based applications, and $P_{COM}$ represents the problem set of COM protocols and finally $P_{Modules}$ designating a problem set of pluggable electronic modules including sensor modules that are indirectly established with the $P_{Env.}$. Thus, the general scientific model for the problem is $P_{Env.} = [ P_{Motherboard}, P_{Graphics}, P_{COM}, P_{Modules} ]$, and then recall their binary relations set in a duplex transmission system as $$R_{Env.} = \[(P_{Motherboard}, P_{Motherboard}), (P_{Motherboard}, P_{Graphics}), (P_{Motherboard}, P_{COM}), (P_{Motherboard}, P_{Modules}), (P_{Motherboard}, P_{Null}),$$ $$(P_{Graphics}, P_{Motherboard}), (P_{Graphics}, P_{Graphics}), (P_{Graphics}, P_{COM}), (P_{Graphics}, P_{Modules}), (P_{Graphics}, P_{Null}),$$ $$(P_{COM}, P_{Motherboard}), (P_{COM}, P_{Graphics}), (P_{COM}, P_{COM}), (P_{COM}, P_{Modules}), (P_{COM}, P_{Null}),$$ $$(P_{Modules}, P_{Motherboard}), (P_{Modules}, P_{Graphics}), (P_{Modules}, P_{COM}), (P_{Modules}, P_{Modules}), (P_{Modules}, P_{Null})\]$$, with a cardinality of $\|R_{Env.}\| = P^{e} + R_{Null} = 4^2 + 4 = 20$; where $P$ is the number of problems in the $R_{Env}$ set, $e$ is the number of problems per relation, and $R_{Null}$ is the number of null relations. Thus the final analogy of the problem is: $$P_{Env.} = [ P_{Motherboard}\ U\ P_{Graphics}\ U\ P_{COM}\ U\  P_{Modules} \ \|\  R_{Env.}\ {\neq}\ {\phi}]$$ |
| _General Approach_ | The general approach entails buying one of the available workstations or toolkits for embedded systems. |
| _Draw Backs of the General Approach_ | The problem with the general solution that it didn't address providing an efficient realtime graphics simulation environment, so the performance is quite poor when advanced graphics-based applications are required to be tested in conjunction with the communication protocols and the electronic modules. |
| _Specific Minimal Approach_ | The minimal approach utilizes this simplistic model that uses the _Set Theory_. Nonetheless, we are merely concerned about the relation set $R_{Env.}$ inside the integrated environment, as it maps the behavior we are seeking from the system. |
| _Upgrading the system_ | Theoretically, the previously mentioned scientific model includes the complements of the _problem elements_ described, therefore for instance, the $P_{Modules}$ has its complement $P'_{Modules}$ which means that we can add expansion modules designated as complements for the pre-existing modules to our system, as well. The practicability of this is well-demonstrated, but half-revealed in a way that it's very much related to the original equation: **Which motherboard are we going to use? AND Which type of COM and modules are utilized in this set? Are they really compatible? We will see about these details when we scope down on the circuit-design level...** | 
| _Scientific Recall of the solution_ | Again, using the _Set Theory_ and the _Group Theory_, envision the environment to build is a universe set _E_ with a main board known as _GA_ standing for _Gigabyte_, a set of peripherals _P_, and a set of communication modules providing communication protocols _COM_, and a set of external electronic modules _M_; thus the final scientific model will be $E = \[GA, P, COM, M\]$; where _COM = \{com \| "com" is a communication protocol provided by a SoC module providing the relations between "GA", "P" and "M" sets\}_, _P = \{p \| "p" is a peripheral device connected directly to the "GA" motherboard\}_, and _M = \{m \| "m" is an electronic module connected indirectly to the "GA" motherboard using one or more of the board communication protocols "com"\}_. |

| The main board | General layout | Scheme | 
|----------------|-----------------------|--------|
| ![image](https://github.com/Electrostat-Lab/Electrostatic-Sandbox/assets/60224159/24bf3e89-42d9-4394-9fd3-ae1a6afaec77) | ![image](https://github.com/Electrostat-Lab/Electrostatic-Sandbox/assets/60224159/320f771a-c3d9-4fd2-8e11-c24646d825ba) | ![image](https://github.com/Electrostat-Lab/Electrostatic-Sandbox/assets/60224159/28c2a865-c21c-4e0b-851d-974d92812368) |


## Table of content (WIP): 
### Hardware:
- General Components.
- General Circuitry scheme layout.
- Substantial Circuitry description (i.e., main board, peripherals, and modules).
### Software:
- Basic Environment Setup.
- Electrostatic-Sandbox Tools (i.e., development tools, frameworks, and APIs).
- Electrostatic-Sandbox Framework (a set of APIs blending Serial4j, Socket4j, ShiftAvr, and Parallel4j for building distributed simulation systems).
### Main Attachments:
- [GA-H61M-S2P Rev-2.0](https://www.gigabyte.com/Motherboard/GA-H61M-S2PV-rev-20#ov)
- PCI-e USB Card.

## DIY Tutorial:
Find the do-it-yourself tutorial at [diy-tutorial]().

## Techdemos on YouTube:
- [Serial4j, ShiftAvr, and jMonkeyEngine](https://youtu.be/4GFGsH4eyJs)

### Credits:
Credits should go to these products for being open-source and widely available with no constraints, hooray to them:
- The Java Platform.
- The CMake Building Framework.
- The jMonkeyEngine game engine.
- The Gradle API.
- The Avrdude tool.
- The Arduino Platform.
- The Gigabyte Company (not open-source, but the main board depends on).
- Zorin OS (the main OS currently in-use).
- SanDisk (flash drive).
- Microchip & ATMEL (for AVR microcontrollers).
- The Linux Man Page & Micheal Kerrisk's Linux Interfacing Book.
- The GNU/Linux glibc and the interfacing libraries.
- IEEE for providing the standards of I/O Communication interfaces.
- The ACM digital library for providing publications about distributed simulation systems.
- The GitHub Platform and Git VCS for hosting this project.
- The KiCad project.
- The Fritzing project.

And, To others who I didn't mention, and were essential predicates for the success of this project.
