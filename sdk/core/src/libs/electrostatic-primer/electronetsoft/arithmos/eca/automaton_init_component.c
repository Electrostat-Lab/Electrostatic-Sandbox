#include <electronetsoft/arithmos/eca/automata.h>
#include <electronetsoft/util/number/decimal.h>
#include <electronetsoft/util/number/crypto.h>

status_code automaton_init_component(automaton_component *component,
                                     automaton_input in,
                                     automaton_state next) {
    if (NULL == component) {
        return EUNDEFINEDBUFFER;
    }

    component->id = in.id ^ next.id;
    component->input = in;
    component->next = next;

    return PASS;
}
