#ifndef _ARRAY_LIST_H
#define _ARRAY_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <electrostatic/algorithm/arithmos/adt/list.h>
#include <stdlib.h>

uint8_t init_contiguous_buffer(list *list, list_element **elements, list_function_table *table);

#ifdef __cplusplus
};
#endif

#endif