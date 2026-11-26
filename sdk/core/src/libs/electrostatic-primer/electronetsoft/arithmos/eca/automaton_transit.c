#include <electronetsoft/arithmos/eca/automata.h>
#include <electronetsoft/util/number/crypto.h>

status_code automaton_transit(automaton *machine, automaton_component *comp) {
    if (NULL == comp || NULL == machine) {
        return EUNDEFINEDBUFFER;
    }

    if (0 == machine->current_state.id ||
        0 == machine->current_input.id) {
        return EINCOMPATTYPE;
    }

    if (0 == comp->next.id || 0 == comp->input.id) {
        return EINCOMPATTYPE;
    }

    comp->id = machine->current_state.id ^ comp->input.id;

    typed_pointer p = (typed_pointer) {
        .address.id = &(comp->id),
        .type = TYPE_ID
    };

    map_element element = {
    };

    status_code __code;

    if (machine->is_deterministic) {
        __code = machine->hashmap->operations->get(machine->hashmap, p, &element);
        if (PASS == __code) {
            machine->transition_callback.transition_failure(comp, INVALID_OP);
            return INVALID_OP;
        } else if (ENOELEMENT == __code) {
            // transit the machine
            // add the pathway

            // list_element *carrier = calloc(1, sizeof(list_element));
            // carrier->type = ELEMENT_MAP_ITEM;
            // carrier->data = comp;
            // carrier->size = sizeof(automaton_component);

            // element.value = carrier;
            // element.key = p;
            // __code = machine->hashmap->function_table->insert(machine->hashmap, &element);
            // if (PASS != __code) {
            //     return __code;
            // }
            // machine->current_state = comp->next;
            // machine->current_input = comp->input;

            // machine->transition_callback.transition_success(comp);

            return PASS;
        }
        return __code;
    }

    machine->current_state = comp->next;
    machine->current_input = comp->input;

    machine->transition_callback.transition_success(comp);

    return PASS;
}