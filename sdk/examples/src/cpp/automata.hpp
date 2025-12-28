/**
 * This is a design for a state-machines library written completely in C++11/17
 * using C++ static types by defining user-defined types representing the most
 * primitive constituents of a State Machine.
 *
 * <p>
 * Usages include running a chain of responsibility activity, concurrent tasking
 * and text recognition via input matching.
 *
 * @author pavl_g.
 */
#ifndef __AUTOMATA_CPP_
#define __AUTOMATA_CPP_

#ifdef __cplusplus // disables C++ name mangling for backward C libraries compatibility
                   // notice that this disables the polymorphic language features!
extern "C++" {
#endif

/**
 * @brief A namespace that encapsulates the abstract types
 * for an Automaton object.
 */
namespace Automata {

    // shall process an
    // shall define a primitive component
    // for an aggregate component on the Machine type
    class State {
        public:
            State(bool is_initial, bool is_final):
                        initial(is_initial), final(is_final) {}
            virtual ~State();
        protected:
            bool initial;
            bool final;
    };

    // A state machine is a quintuple sequence M = {q0, Q, d, S, F}
    // that could be reduced t
    template<typename R, typename S, typename I>
    class Machine {
        public:
            /**
             * @brief Transits to the next state and the next input,
             * and dispatches the [on_transit].
             */
            void transit();
            /**
             * @brief Instantiates a new machine with a set of states
             * and a set of inputs.
             *
             * @param states a sequence of states
             * @param inputs a sequence of inputs
             * @param on_transit an event invokable function
             */
            Machine(S **states, I **inputs, R (*on_transit)(S*, I*)):
                            states(states), inputs(inputs), on_transit(on_transit) {}
            virtual ~Machine();

        protected:
            S **states;
            I **inputs;
            R (*on_transit)(S*, I*);
    };
};

#ifdef __cplusplus
};
#endif
#endif