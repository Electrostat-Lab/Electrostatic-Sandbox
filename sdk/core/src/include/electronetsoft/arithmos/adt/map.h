#ifndef _MAP_H_
#define _MAP_H_

#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <electronetsoft/arithmos/adt/list.h>

#ifdef __cplusplus
extern "C" {
#endif

struct map_element {
    typed_pointer key;
    list_element value;
};

struct map_processors {
    status_code (*on_initialization)(map *);
    status_code (*on_deinitialization)(map *);
    status_code (*on_insertion)(map *, map_element *, uint64_t);
    status_code (*on_rehash_dispatch)(map *, list_element *);
    status_code (*on_removal)(map *, list *, uint64_t);
    status_code (*on_collision)(list *,
                                uint64_t,
                                list_element *);
    status_code (*on_collision_resolution)(list *,
                                           uint64_t,
                                           list_element *);
};

struct map {
    map_operations *operations;
    map_type type;
    list *adt;
    map_processors *processors;
    uint64_t count;
    collision_scheme col_scheme;
};

struct map_operations {
    status_code (*insert)(map *, map_element *);
    status_code (*insert_all)(map *, map_element *, uint64_t);
    status_code (*remove)(map *, typed_pointer);
    status_code (*remove_all)(map *, typed_pointer *, uint64_t);
    status_code (*rehash)(map *, uint64_t);
    status_code (*contains)(map *, typed_pointer);
    status_code (*contains_all)(map *, typed_pointer *, uint64_t);
    status_code (*get)(map *, typed_pointer key, map_element *);
    status_code (*get_raw)(map *, typed_pointer key, map_element *);
    status_code (*iterator)(map *, status_code (*callback)(map *, map_element *));
};

status_code init_map(map *, map_operations *,
                                    api_lifecycle *);

status_code map_get_lambda_factor(map *, float *);

status_code deinit_map(map *, api_lifecycle *);

#ifdef __cplusplus
};
#endif
#endif
