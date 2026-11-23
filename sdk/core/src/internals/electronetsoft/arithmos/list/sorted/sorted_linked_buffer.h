#ifndef _SORTED_LINKED_BUFFER_H
#define _SORTED_LINKED_BUFFER_H

#include <electrostatic/electronetsoft/algorithm/arithmos/adt/list.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

status_code init_sorted_linked_buffer(list *list,
                                          list_element **elements,
                                          list_function_table *table,
                                          api_lifecycle *lifecycle);

#ifdef __cplusplus
};
#endif

#endif