#ifndef __ECS_ECA__
#define __ECS_ECA__

#include <electronetsoft/util/types.h>
#include <electronetsoft/util/utilities.h>
#include <electronetsoft/arithmos/adt/map.h>
#include <electronetsoft/arithmos/eca/automata.h>
#include <electronetsoft/util/number/decimal.h>
#include <electronetsoft/util/number/crypto.h>

#ifdef __cplusplus
extern "C" {
#endif

struct eca {
    map *systems;
    eca_function_table *table;
};

struct eca_function_table {
    status_code (*add_system)(eca *, eca_system);
    status_code (*remove_system)(eca *, uint64_t);
    status_code (*init_machine)(eca *, uint64_t, automaton *);
    status_code (*deinit_machine)(eca *, uint64_t);
    status_code (*start_machine)(eca *, uint64_t);
    status_code (*attach_machine)(eca *, uint64_t, automaton *);
    status_code (*detach_machine)(eca *, uint64_t, uint64_t);
    status_code (*attach_component)(eca *, eca_component);
    status_code (*detach_component)(eca *, uint64_t, uint64_t);
};

struct eca_system {
    map *components;
    map *machines;
    uint64_t sid;
};

struct eca_component {
    typed_pointer data;
    uint64_t cid;
    uint64_t sid;
};

#ifdef __cplusplus
};
#endif

#endif