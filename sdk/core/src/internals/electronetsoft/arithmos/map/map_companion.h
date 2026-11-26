#ifndef __MAP_COMPANION_H_
#define __MAP_COMPANION_H_

#include <electronetsoft/arithmos/adt/list.h>
#include <electronetsoft/util/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    list_element value;
    uint64_t index;
} key_element;

status_code init_adt_list(list **, uint64_t);
status_code de_init_adt_list(list **);
status_code get_element_by_str_key(list *, const char *, key_element *);
status_code get_element_by_long_key(list *, uint64_t *, key_element *);
status_code get_element_by_typed_key(list *, typed_pointer, key_element *);

#ifdef __cplusplus
};
#endif

#endif