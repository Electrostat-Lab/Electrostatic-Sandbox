#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <electrostatic/electronetsoft/algorithm/arithmos/adt/list.h>
#include <stdlib.h>

typedef struct linked_node (linked_node);
typedef enum linked_node_type (linked_node_type);

enum linked_node_type {
    SINGLE_ENDED,
    DOUBLE_ENDED,
    CLUSTER
};

struct linked_node {
  list_element *next;
  list_element *previous;
  list_element *middle;
  linked_node_type type;
  
  void* data;
};

uint8_t init_linked_buffer(list *list, list_element **elements, list_function_table *table);

#ifdef __cplusplus
};
#endif

#endif