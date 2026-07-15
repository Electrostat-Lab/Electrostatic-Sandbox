#ifndef _HASH_MAP_H_
#define _HASH_MAP_H_

#include <electronetsoft/arithmos/adt/map.h>

#ifdef __cplusplus
extern "C" {
#endif

status_code hashmap_init(map *, map_function_table *,
                               api_lifecycle *);


status_code hashmap_deinit(map *, api_lifecycle *);

#ifdef __cplusplus
};
#endif
#endif