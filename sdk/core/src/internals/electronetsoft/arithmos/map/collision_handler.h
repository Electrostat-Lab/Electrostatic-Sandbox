#ifndef __COLLISION_HANDLER_H_
#define __COLLISION_HANDLER_H_

#include <electronetsoft/util/types.h>
#include <electronetsoft/arithmos/adt/list.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

status_code init_chain(list *, list_element *, list_element *, uint64_t);
status_code no_duplicates_handler(list *, list_element *, list_element *);
status_code de_init_chain(list *, uint64_t);

#ifdef __cplusplus
};
#endif

#endif 