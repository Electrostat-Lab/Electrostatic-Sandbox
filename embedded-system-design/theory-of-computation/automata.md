# The Automata Theory

## Preface:
Describing the computational machines can be attained through several ways; one common way, though complex, however usually used in embedded systems, is through _computer organization_ standards. Though highly accurate, it is still a concrete intricate way of describing a very specific machine or so far a family of machines (e.g., The x86 family, The ARM family, and The AVR MCU family) and there are so much details that not all computer scientists would appeal dealing with them. In addition, tackling through computer organization requires a strong background in _digital electronics_, and _embedded circuit design_. Thus, using an abstract mathematical model would be much appealing in understanding specific parts that are not easily-explained using computer organization. The Automata Models could be also utilized efficiently in a code-first approach to define software algorithms, and deal with heavy-tasking computations, so far you will find these use cases in _Appendix-D_. 

## Scientific Models and their usage
So far the _Automata Models_ are categorized under the _Mathematical Models_ which are subsets of the _Scientific Models_. Scientific Models are utilized to describe intricate systems by breaking them down into several components; then by building them up in a more _miniaturized form_, the Model. So, in plain English, Scientific models are miniaturized forms of the components of a system describing a specific phenomenon (e.g., in this case, a computational algorithm or digital signals manipulation in embedded systems) based on a theory (e.g., in this case, the Set Theory). The aim is to study the systems' components in an efficient way by breaking them down into managable models.

## Table of contents:
* Computational Models.
* Abstract Mathematical Models (e.g., Continuous V.S. Discrete Mathematical Models).
* Finite Automata Models (D.F.A and N.F.A).
* Automata Languages (e.g., `L(M)` of Machine M).
* Regular Expressions, Regular Languages, and regular operations (i.e., Union - Concatenation - Closures).
* Appendixes.
  * Appendix-A: Proof by construction:
    * Proof by construction of the equivalency of both N.F.A and D.F.A.
    * Proof of construction that the regular operations are closed under the class of regular languages.
  * Appendix-B: References and More about the Automata theory.
  * Appendix-C: The use of the Automata Theory in Medicine.
  * Appendix-D: A Coding project on the _Electrostatic-Sandbox SDK_.

### Computational Models and the Automata Models

Computational Models are abstract mathematical models that aim to provide miniaturized forms for the systems' components that are of interest to describe a specific phenomenon based on a scientific theory.

> [!NOTE]
> The Finite-Automata Model is the most basic model in the Automata Theory, in addition, it's considered to be the building unit of the other more advanced models (e.g., Pushdown Automatas (PDA) - Turing Machines (TM) - Markov Chains). A finite-state-automaton has a limited memory that is allocated only for an input symbol, and the data of the current state in execution. The more advanced models of the Automata Theory usually have other additional means of memory.

Examples of some systems which can be modeled using the finite-automata model are: 
* Vending Machines.
* Automatic doors' controllers.
* Elevators.
* Traffic Systems.
* Electric Railway Systems.
* Kinematics of Armatures (e.g., Animation Systems in Game Engines).
* Data manipulation in Flip-flops (e.g., Tabular form of the truth table).
* The reproductive power of bacterium (e.g., The Cellular automata of binary fusion).

### The Abstract Mathematical Models (Continuous V.S. Discrete Models)

The Automata Models are classified as discrete mathematical models which explain systems in terms of discrete states and relations (or better described as transition functions) based on the Set Theory. Unlike the automata models, the continuous functions (e.g., differential and integral functions) on the other side of mathematics are utilized as mathematical models for modelling continuous systems (e.g., AC Waveforms - DC Noise Filter Circuits - RC Circuits - Rectification Circuits - Medications plasma half-life). The Automata theory cannot be utilized directly for modelling these continuous systems. Some Modified Automatas known as [_"Hybrid Automata"_](https://link.springer.com/chapter/10.1007/978-3-642-59615-5_13) are commonly used in systems that involve both continuous and discrete behavior (e.g., Analog/Digital Circuits. for example, The Electric Railway Monitoring systems - Temperature monitoring systems).

### Finite Automata Models (D.F.A and N.F.A)

Formal definition: 
> A finite automaton or a state-machine "M" is a 5-tuple sequence composed of $$Q$$ representing a finite set of states, $$\Sigma$$ representing a finite set of input symbols known as the "alphabet of the language of the automaton", $$\delta$$ is the transition function of the automaton and together with the members of $$\Sigma$$ they lay down the rules for transiting from a state to another, $$q_0$$ representing the initial state of the machine; where $$q_{0}\ \in\ Q$$, and $$F$$ representing the set of the final accepting states; where $$F\ \subseteq\ Q$$, which together with the initial states are used to define the set of the regular expressions that are recognizable by the automaton "M", also known as the Language of M or $$L(M)$$.

Formal Notation:
> A finite automaton is quintuple (5-tuple) sequence; where
> $M = \(Q, \Sigma, \delta, q_0, F\)\$:
> 1) $$Q$$ is a **finite set of states**.
> 2) $$\Sigma$$ is a **finite set of the input symbols**, aka. the **alphabets** of the automaton language.
> 3) $$\delta$$ is the **transition function** $$\delta: Q \times \Sigma \rightarrow Q$$, that together with the input symbols define the rules for state transitions.
> 4) $$q_0 \in Q$$ is the **initial** or the **start** state.
> 5) $$F \subseteq Q$$ is a **finite set of states** representing the **final states** aka. the **accept states**; such that the $$F$$ set is a subset of the $$Q$$. 

> [!TIP]
> Some vague terms are ought to be defined so far:
> 1) _The Language of the Automaton_: the set of all strings that the machine _M_ accepts, and is better be defined formally using the set builder notation (e.g., $$L(M) = [s\ |\ s$$ _is a string composed of the alphabets_ $$\Sigma \land Rule_1 \land ...]$$).
> 2) _Finite State Recognizers_: abstract machines used to determine whether a given input string belongs to a particular language, as defined by a formal grammar.
> 3) _State-State Relations_: are defined by the transition functions, which are functions in case of the deterministic machines and relations and/or partial functions in case of the non-deterministic machines.
> 4) _Deterministic Automaton_: a deterministic machine defines a unique transition function for each pair of state $q_n$ and input $\sigma_n$; the output of the function is deterministically the next state $q_{n + 1}$; thus the following holds and can be used to define the set for the output states: $$Q_{out} = [\bigcup_{i = 0}^n \delta(q_i, \sigma_i) \rightarrow [q_{i + 1}]] = [q \in Q | \delta(q_i, \sigma_i) = q_{i + 1};\ where\ i <= n]$$     
> 6) _Non-deterministic Automaton_:
