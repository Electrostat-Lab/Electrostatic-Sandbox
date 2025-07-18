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

Formal definition of the deterministic machines: 
> A deterministic finite automaton or a state-machine "M" is a 5-tuple sequence composed of $$Q$$ representing a finite set of states, $$\Sigma$$ representing a finite set of input symbols known as the "alphabet of the language of the automaton", $$\delta$$ is the transition function of the automaton and together with the members of $$\Sigma$$ they lay down the rules for transiting from a state to another, $$q_0$$ representing the initial state of the machine; where $$q_{0}\ \in\ Q$$, and $$F$$ representing the set of the final accepting states; where $$F\ \subseteq\ Q$$, which together with the initial states are used to define the set of the regular expressions that are recognizable by the automaton "M", also known as the Language of M or $$L(M)$$.

Formal Notation of the deterministic machines:
> A finite automaton is quintuple (5-tuple) sequence; where
> $M = \(Q, \Sigma, \delta, q_0, F\)\$:
> 1) $$Q$$ is a **finite set of states**.
> 2) $$\Sigma$$ is a **finite set of the input symbols**, aka. the **alphabets** of the automaton language.
> 3) $$\delta$$ is the **transition function** $$\delta: Q \times \Sigma \rightarrow Q$$, that together with the input symbols define the rules for state transitions.
> 4) $$q_0 \in Q$$ is the **initial** or the **start** state.
> 5) $$F \subseteq Q$$ is a **finite set of states** representing the **final states** aka. the **accept states**; such that the $$F$$ set is a subset of the $$Q$$. 

Formal definition of the non-deterministic machines:
> The formal definition of a non-deterministic machine is similar to that of its deterministic counterpart. Both have states, an input alphabet, a transition function, a start state, and a set of accepting states. However, they differ in one essential way: in the type of the transition function. In a DFA, the transition function takes a state and an input symbol and produces the next state, while in an NFA, the transition function takes a state and an input symbol or **_an empty string_** and produces **the set of possible next states**. For any set $$Q$$, we write $$P(Q)$$ to be the collection of all subsets of $$Q$$. Here $$P(Q)$$ is called the _power set of $$Q$$_. For any alphabet $$\Sigma$$, we write $$\Sigma_{\epsilon}$$ to be $$\Sigma \cup \epsilon$$; thus the formal description of the type of the transition function in NFA is: $$\delta: Q \times \Sigma_{\epsilon} \rightarrow P(Q)$$.

Formal notation of the deterministic machines:
> A non-deterministic finite automaton is quintuple (5-tuple) sequence; where
> $M = \(Q, \Sigma, \delta, q_0, F\)\$:
> 1) $$Q$$ is a **finite set of states**.
> 2) $$\Sigma$$ is a **finite set of the input symbols**, aka. the **alphabets** of the automaton language; such that $$\Sigma = \Sigma_{\epsilon}$$; as $$\Sigma_{\epsilon} = \Sigma \cup \epsilon$$ where $$\epsilon$$ is the empty string.
> 3) $$\delta$$ is the **transition function** $$\delta: Q \times \Sigma_{\epsilon} \rightarrow P(Q)$$, that together with the input symbols define the rules for state transitions.
> 4) $$q_0 \in Q$$ is the **initial** or the **start** state.
> 5) $$F \subseteq Q$$ is a **finite set of states** representing the **final states** aka. the **accept states**; such that the $$F$$ set is a subset of the $$Q$$. 

> [!TIP]
> Some vague terms are ought to be defined so far:
> 1) _The Language of the Automaton_: the set of all strings that the machine _M_ accepts, and is better be defined formally using the set builder notation (e.g.: $$L(M) = \\{s\ |\ s$$ _is a string composed of the alphabets_ $$\Sigma \land Rule_1 \land ...\\}$$).
>
> 2) _Finite State Recognizers_: abstract machines used to determine whether a given input string belongs to a particular language, as defined by a formal grammar.
>  
> 3) _State-State Relations_: are defined by the transition functions, which are functions in case of the deterministic machines and relations and/or partial functions in case of the non-deterministic machines.
> 
> 4) _Deterministic Automaton (Revisited)_: a deterministic machine defines a unique transition function for each pair of state $q_i$ and input $\sigma_{i + 1}$; where $$i \in N$$ is the index of the current state in the collection $$Q$$, and $$(i + 1) \in N$$ is an arbitrary number representing the position of the input $$\sigma$$ in the collection $$\Sigma$$, the output of the function is deterministically the next state $q_{i + 1}$; where $$0 <= i < n$$ and $$n \in N$$ is an arbitrary number representing the index of the final accepting state; thus the following holds and can be used to define the set for the output states: $Q_{out} = \\{\bigcup_{i = 0}^{n - 1} \delta(q_i, \sigma_{i + 1}) \rightarrow \\{q_{i + 1}\\}\\} = \\{q \in Q | \delta(q_i, \sigma_{i + 1}) = q_{i + 1};\ where\ 0 <= i < n \land n \in N\\}$
> 
> 5) _Non-deterministic Automaton (Revisited)_: a non-deterministic machine defines a non-unique transition function for each pair of state $q_i$ and input $\sigma_{i + 1}$, in other words the transition from the state $q_i$ with the input $\sigma_{i + 1}$ is not pre-determined, thus we can define the transition function as $$\delta (q_{i}, \sigma_{i + 1}) \rightarrow P(Q)$$; where $$P(Q)$$ is the power set of Q of cardinality $$|P(Q)| = 2^{|Q|}$$, and the set for the output states of this machine as $Q_{out} = \\{\bigcup_{i = 0}^{n - 1} \delta(q_i, \sigma_{i + 1}) \rightarrow P(Q)\\} = \\{q \in P(Q) | \delta(q_i, \sigma_{i + 1}) = q_{i + 1};\ where\ 0 <= i < n \land n \in N\\}$.
>
> 6) A quick guess to a typical GNU/C99 prototype abstraction that models the automaton constructs; it essentially uses the _proof by construction_ to construct the automaton by putting the most peculiar rule in-mind; which states that _an automaton uses a limited memory and is a quintuple sequence_:
> ```c
> #ifndef __AUTOMATA_H__
> #define __AUTOMATA_H__
>
> // insert pre-processor directives here ...
> 
> #include <inttypes.h>
> #include <stdlib.h>
>
> // shutdown C++ name mangling for effective C backward compatibility 
> #ifdef __cplusplus
> extern "C" {
> #endif
>
> typedef struct automaton (automaton);
> typedef struct automaton_state (automaton_state);
> typedef struct automaton_input (automaton_input);
> typedef struct automaton_transition_complex (automaton_transition_complex);
> typedef struct automaton_pattern (automaton_pattern);
> typedef struct automaton_recognizer (automaton_recognizer);
> typedef struct automaton_processors (automaton_processors);
> typedef automaton_state *(*delta)(automaton_input *) (automaton_delta);
> 
> /**
>  * @brief Provides an abstract construct skeleton to the automaton state.
>  */
> struct automaton_state {
>    uint8_t is_initial;
>    uint8_t is_final;
>    void *state; // field is not nullable 
>    void *metadata; // field is nullable for the basic automata
> };
>
> /**
>  * @brief Provides an abstract construct skeleton to the automaton input.
>  */
> struct automaton_input {
>    /**
>     * Field is not nullable.
>     */ 
>    void *input;
>
>    /**
>     * Metadata are additional data such as:
>     * virtual time or time stamps - memory stamps - clock ticks and so on -
>     * field is nullable.
>     */
>    void *metadata;
> };
>
> /**
>  * @brief A triplet sequence representing the next transition complex.
>  */
> struct automaton_transition_complex {
>    automaton_state *next_state;
>    automaton_input *next_input;
>    void *metadata; 
> };
>
> struct automaton_processors {
>    void (*init_post_processing)(automaton *);
>    void (*transition_post_processing)(automaton *);
>    void (*transition_failure_post_processing)(automaton *);
>    void (*automaton_pattern_accepted)(automaton *, automaton_recognizer *);
>    void (*automaton_pattern_rejected)(automaton *, automaton_recognizer *);
>    void (*start_state_processing)(automaton *);
>    void (*accept_state_processing)(automaton *);
>    void (*destroy_post_processing)(automaton *);
> };
>
> /**
>  * @brief A quadruple sequence providing
>  * an abstract construct skeleton to the automaton machine.
>  */
> struct automaton {
>    /**
>     * A pointer to the current state, updated on each transition.
>     * - Default value: an address to the start state q0.
>     */
>    automaton_state *state;
>
>    /**
>     * A pointer to the current input, updated on each transition.
>     * - Default value: an address to the first input in the alphabet
>     * of the language of the automaton.
>     */
>    automaton_input *input;
> 
>    /**
>     * A pointer to the transition funcion, constant along the transition engine.
>     */
>    automaton_delta delta;
>
>    void *metadata;
> };
>
> struct automaton_pattern {
>    automaton_transition_complex *start_address;
>    automaton_transition_complex *end_address;
> };
>
> struct automaton_recognizer {
>    /**
>     * @brief Provides a complex binary-tuple representing
>     * the Sigma and the Q collections.
>     */
>    automaton_transition_complex **reference_complexes;
>
>    /**
>     * @brief Provdies clamping maneuvers to synthesis a
>     * word from the alphabet of the automaton
>     * (i.e., the reference complexes).
>     */
>    automaton_pattern *pattern;
> };
>
> uint8_t automaton_init(automaton *machine);
>
> uint8_t automaton_destroy(automaton *machine);
>
> uint8_t automaton_transit(automaton *machine, automaton_transition_complex *transition);
>
> /**
>  * @brief Automaton Pattern recognizer is a finite machine that
>  * tests whether a specific pattern of addresses is recognizable in this
>  * automaton. A transition complex sequence (i.e., the string in formal languages) is
>  * said to be recognized if and only if the final member in the sequence collection
>  * `automaton_transition_complex`, that is synethesized from the automaton alphabet, contains
>  * an accepting state, However, if this condition cannot be met; then the memory pattern
>  * is said not to be recognizable under this automaton recognizer machine. If the recognition
>  * operation is a success, the recognition success processer will be invoked, otherwise if the
>  * machine doesn't accept then the recognition failure processor will be invoked.
>  */
> uint8_t automaton_recognizer(automaton *machine, automaton_recognizer *recognizer);
> 
> #ifdef __cplusplus
> }
> #endif
> #endif 
> ```
>
> In this API, it's said that a memory pattern is recognized if the following 2 conditions are met (Conditions for the pattern recognizer algorithm):
> 1) The `automaton_pattern` represents a start address and an end address for a string from the alphabet collection (i.e., `automaton_transition_complex`).
> 2) The `automaton_pattern` start address coincides with a transition complex that when unwrapped contains a next state marked as _a start state to initiate the automaton_, and the end address coincides with _a transition to a final accepting state to terminate the automaton_ with the invocation of the `automaton_pattern_accepted` processor. In case of the transition processing reached the end address, and the end address is not coincident with a transition complex that contains a final accepting state; the transition processor exits, and the `automaton_pattern_rejected` processor is invoked. Likewise, if the start address of the `automaton_pattern` is not coincident with a state marked as a start state, the transition processor exits, and the `automaton_pattern_rejected` processor is invoked.
>


