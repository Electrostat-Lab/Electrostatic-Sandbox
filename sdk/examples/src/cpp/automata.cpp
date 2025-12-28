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

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

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
        State() = default;
        State(bool is_initial, bool is_final):
                initial(is_initial), final(is_final) {
            printf("Initializer Root\n");
        }
        virtual ~State() {
            printf("Destruction Root\n");
        }
        bool is_initial() {
            return initial;
        }
        bool is_final() {
            return final;
        }
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
        void transit() {
            std::cout << states[0].is_initial() << std::endl;
        }

        /**
         * @brief Instantiates a new machine with a set of states
         * and a set of inputs.
         *
         * @param states a sequence of states
         * @param inputs a sequence of inputs
         * @param on_transit an event invokable function
         */
        Machine(std::size_t s, std::size_t i, R (*on_transit)(S*, I*)):
                validator(validate(s, i)), states(std::vector<S>(s)), inputs(std::vector<I>(i)),
                on_transit(on_transit) {
            // validate the count of states and inputs here!

            // initialize the rest of members through members initializers dispatch
        }

        // default constructor for instantiation using the vector
        Machine() = default;

        Machine(const std::vector<S>& states_copy,
                const std::vector<I>& input_copy, R (*on_transit)(S*, I*)) = delete;

        Machine(std::vector<S>&& states_mv,
                std::vector<I>&& input_mv, R (*on_transit)(S*, I*)) noexcept :
                validator(validate(states_mv.size, input_mv.size)),
                states(std::move(states_mv)), inputs(std::move(input_mv)), on_transit(on_transit) {

            // no destruction -- data are moved!
        }

        Machine& operator=(const Machine& machine) = delete;

        Machine& operator=(Machine&& machine) noexcept { //define moving operator
            // This machine doesn't directly own the memory!
            // And thus; it must delegate the operation implicitly
            // to the memory owners or else get into the troubles of
            // memory ownership management that could end in
            // segmentation faults or double free attempts!

            // don't destroy the current vectors!
            // those vectors have pre-compiled overridden assignment
            // operations for moving values as long as
            // the passed argument is a reference!
            if (this == &machine) {
                return *this;
            }
            // rebuild from another source
            // use the overridden move assignments on the vector class
            states = std::move(machine.states);
            inputs = std::move(machine.inputs);
            on_transit = machine.on_transit;

            // nullify the references
            machine.on_transit = nullptr;
            return *this;
        }

        ~Machine() = default;

    protected:
        static inline void* validate(std::size_t s, std::size_t i) {
            if (i != (s - 1)) {
                throw std::invalid_argument("Input sequence must be less than the states sequence length by 1!");
            }
            return nullptr;
        }
        void *validator;

        std::vector<S> states;
        std::vector<I> inputs;
        R (*on_transit)(S*, I*);
    };
};

class BaseState: public Automata::State {
public:
    BaseState() = default;
    BaseState(bool initial, bool final):
            Automata::State(initial, final) {
        printf("Initializer Base\n");
    }

    virtual ~BaseState() override {
        initial = false;
        printf("Destruction2\n");
    }
};

int main() {
    std::vector<BaseState> states(5);
    std::vector<std::string> inputs(4);

    Automata::Machine<int, BaseState, int> m(10, 9, nullptr);
    m.transit();

    return 0;
}
#ifdef __cplusplus
};
#endif
#endif