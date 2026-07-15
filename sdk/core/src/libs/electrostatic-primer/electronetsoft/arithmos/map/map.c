#include <electronetsoft/arithmos/adt/map.h>
#include <electronetsoft/arithmos/map/hashmap.h>
#include <electronetsoft/arithmos/adt/list.h>
#include <stdio.h>

status_code init_map_function_table(map *m, map_function_table *table,
                                    api_lifecycle *lifecycle) {
    if (NULL == m || NULL == table) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;

    if (m->type == MAP_TYPE_HASHMAP) {
        __code = hashmap_init(m, table, lifecycle);
    } else if (m->type == MAP_TYPE_TREEMAP) {
        // NOT IMPLEMENTED YET!
        return EINCOMPATTYPE;
    } else {
        return EINCOMPATTYPE;
    }

    if (PASS != __code) {
        return __code;
    }

    return PASS;
}


status_code deinit_map_function_table(map *m, api_lifecycle *lifecycle) {
    if (NULL == m) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;

    if (m->type == MAP_TYPE_HASHMAP) {
        __code = hashmap_deinit(m, lifecycle);
    } else if (m->type == MAP_TYPE_TREEMAP) {
        // NOT IMPLEMENTED YET!
        return EINCOMPATTYPE;
    } else {
        return EINCOMPATTYPE;
    }

    if (PASS != __code) {
        return __code;
    }

    return PASS;
}