#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <electrostatic/electronetsoft/algorithm/arithmos/adt/list.h>
#include <electrostatic/electronetsoft/util/utilities.h>
#include <electrostatic/electronetsoft/util/types.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" { // disables the C++ name mangling
#endif

enum linked_buffer_type {
    SINGLE_ENDED,
    DOUBLE_ENDED,
};

struct linked_buffer {
  // no alignment issues
  // 64-bit (8 bytes) aligned structure
  // size = (8 * 2) + (4) + 4-alignment = 24 Bytes
  // alignment are used to faster data LOAD and STORE
  // from/to CPU cache levels and MMIO devices
  list_element *start_address;
  list_element *end_address;
  linked_buffer_type type;
};

status_code init_linked_buffer(list *list,
                               list_element **elements,
                               list_function_table *table,
                               api_lifecycle *lifecycle);

#ifdef __cplusplus
};
#endif

#endif