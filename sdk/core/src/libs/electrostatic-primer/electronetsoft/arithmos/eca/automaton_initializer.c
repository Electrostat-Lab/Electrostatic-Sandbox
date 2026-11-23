#include <electronetsoft/arithmos/eca/automata.h>

static inline status_code __iterator_callback(map *hashmap, map_element *element) {
    if (NULL == element->value) {
        return PASS;
    }

    free(element->value);

    return PASS;
}

status_code automaton_init(automaton *machine) {
    if (NULL == machine) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL != machine->hashmap) {
        return EBUFFER_EXISTS;
    }

    machine->hashmap = calloc(1, sizeof(map));
    if (NULL == machine->hashmap) {
        return EUNDEFINEDBUFFER;
    }
    machine->hashmap->type = MAP_TYPE_HASHMAP;

    map_function_table *table = calloc(1, sizeof(map_function_table));
    if (NULL == table) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code = init_map_function_table(machine->hashmap, table, NULL);
    if (PASS != __code) {
        return __code;
    }

    // starting Identifiers
    machine->current_state.id =
            (UINT64_MAX << 8) | (UINT64_MAX >> ((sizeof(uint64_t) * 8) - 8));
    machine->current_input.id =
            (UINT64_MAX << 5) | (UINT64_MAX >> ((sizeof(uint64_t) * 8) - 5));


    return PASS;
}

status_code automaton_deinit(automaton *machine) {
    if (NULL == machine || NULL == machine->hashmap) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;

    __code = machine->hashmap->function_table->iterator(machine->hashmap, &__iterator_callback);
    if (PASS != __code) {
        return __code;
    }

    __code = deinit_map_function_table(machine->hashmap, NULL);
    if (PASS != __code) {
        return __code;
    }

    return PASS;
}