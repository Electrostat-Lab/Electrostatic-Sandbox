#ifndef __HASHMAP_UTIL_H_
#define __HASHMAP_UTIL_H_

#include <electronetsoft/arithmos/adt/text.h>
#include <electronetsoft/arithmos/adt/map.h>
#include <electronetsoft/util/types.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" { // disable C++ name mangling by declaring function prototypes
            // a C externally linked space
#endif

typedef struct {
    status_code (*lookup_preprocessor)(text in, text pattern, size_t index);
    status_code (*lookup_postprocessor)(text in, text pattern, size_t index);
} lookup_buffer_proc;

typedef struct {
    text in;
    text pattern;
    size_t *__indices;
    char *__keys;
    list_element *__elements;
    map_element *__map_elements;
    lookup_buffer_proc *processors;
} lookup_buffer;

typedef enum {
    USE_INDICES = NO_DUPLICATES - 1,
    DEFAULT = USE_INDICES - 1
} lookup_table_init_scheme;

/**
 * @brief Initializes a lookup table map from a lookup buffer structure;
 * through deeply copying the alphabet from the input (text) into hashed
 * positions inside the hashmap buffer; hash keys are typically obtained from the input characters.
 */
status_code lookup_table_init(map *, lookup_buffer, lookup_table_init_scheme);

status_code lookup_table_heap_alloc(map *);
status_code lookup_table_heap_dealloc(map *);

#ifdef __cplusplus
};
#endif

#endif