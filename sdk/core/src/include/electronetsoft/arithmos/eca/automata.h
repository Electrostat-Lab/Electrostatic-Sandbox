#ifndef __AUTOMATA_ECA__
#define __AUTOMATA_ECA__

#include <electronetsoft/util/types.h>
#include <electronetsoft/util/utilities.h>
#include <electronetsoft/arithmos/adt/map.h>

#ifdef __cplusplus
extern "C" {
#endif

struct automaton_state {
    uint64_t id;
    typed_pointer state;
};

struct automaton_input {
    uint64_t id;
    typed_pointer input;
};

struct automaton_component {
    uint64_t id; // constructed using the pathway (state0 and the input) id
    automaton_state next;
    automaton_input input;
};

struct automaton_zeta {
    status_code (*transition_success)(struct automaton_component *);
    status_code (*transition_failure)(struct automaton_component *, status_code);
};

struct automaton {
    automaton_state current_state;
    automaton_input current_input;
    automaton_zeta transition_callback;
    map *hashmap;
    // hashmap housing the automaton components by their ids
    // --------------- APPLY this algorithm only in DETERMINISTIC MACHINES ---------------
    // a 2d hashmap; the first dimension lists the automata states with their IDs;
    // the second dimension lists the components arising from that state
    // those components are added using a combination of the IDs of their
    // state0 and the input only!
    // state0 and the input IDs defines the pathway of the machine from
    // the state which must be unique in case of the deterministic machines
    // when transiting from state0 to state1 using an automaton_component,
    // the algorithm will perform these computations internally:
    // 1) Verify whether the current_state from the automaton structure
    // is compatible with the state0 from the automaton_component structure.
    // IF not; terminate immediately with an error.
    // 2) Locate the hashmap for the pathways of (state0); those pathways represent mini machines starting from state0.
    // IF not present; create one and add it to the automata map.
    // proceed with execution of the next state.
    // 3) Create a pathway id using the (state0) ID and the (input) ID of the
    // automaton_component.
    // 4) Override the automaton component ID with the pathway ID.
    // 5) Try to locate the automaton component using the formed ID.
    // IF present; execute a determinism_failure trap and terminate immediately
    // IF not present; add the automaton component to the hashmap.
    // proceed with execution of the next state.
    // --------------- --------------- --------------- ---------------
    uint8_t is_deterministic;
    uint64_t id;
};

status_code automaton_init_component(automaton_component *, automaton_input, automaton_state);

status_code automaton_transit(automaton *,
                              automaton_component *);

status_code automaton_init(automaton *);
status_code automaton_deinit(automaton *);


#ifdef __cplusplus
};
#endif

#endif