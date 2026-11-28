#ifndef __LIST_COMPANION_H_
#define __LIST_COMPANION_H_

#include <electronetsoft/util/types.h>

#ifdef __cplusplus
extern "C" {
#endif

status_code list_stretch_capacity(list *, void *);
status_code list_shrink_capacity(list *, void *);
status_code list_unsafe_leftshift_items_by_one(list *, uint64_t);
status_code list_unsafe_get_index_from_element(list *, list_element *, uint64_t *);

#ifdef __cplusplus
};
#endif


#endif