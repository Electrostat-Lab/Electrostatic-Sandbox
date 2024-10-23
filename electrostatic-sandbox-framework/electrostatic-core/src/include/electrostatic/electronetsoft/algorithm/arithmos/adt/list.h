//
// ADT file for the Lists, is analogous to the Java Util List interface.
// Author: pavl_g.
// Based on: the OpenJDK under the terms of the GNU General Public License version 2, Oracle Foundation.
// Conceptually Based on: the Finite-Automata Theory.
//

//
// Scientific basis:
// According to the Scientific Ontology, the Designation part of the relations
// defines relations between objects and constructs; which ends by assigning
// some constructs to some objects, and so by applying this relation here
// we could deduce that this file can literally hold the "constructor routines"
// for different objects; the routines are the way that we change the direction
// of the deterministic automata in procedural programming.
//

//
// Hierarchial architectural pattern for "List" Abstract Data Type in Arithmos:
//                             ADT Layer ## list ##
// [struct list - struct list_element - struct list_function_table - enum list_type]
//         ----Sortables AND Searchables (Pre-sorted and Non-sorted)----
//      [Note: Sorting and Searching algorithms are separated in another utilities.]
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| ## Specializations
// /                     \                    \                         \
// contiguous_buffer     linked_buffer       memorypool_buffer
//                           \
//              [doubly_linked_buffer - circular_linked_buffer - unrolled_linked_buffer]
//

#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdlib.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/memory/patcher.h>
#include <electrostatic/electronetsoft/util/errno/errno.h>

typedef struct list(list);
typedef struct list_info(list_info);
typedef enum list_type(list_type);
typedef struct list_element(list_element);
typedef struct list_function_table(list_function_table);

enum list_type {
  CONTIGUOUS_BUFFER,
  LINKED_NODES
};

struct list_element {
  void *data;
  size_t size;
};

struct list_info {
  uint64_t start_index;
  uint64_t length;
  uint64_t rate;
};

struct list {
  list_element **elements;
  list_function_table *function_table;
  list_type type;
  memory_partition elements_memory;
  uint64_t length;
  uint64_t limit;
  errno error; //dereference and examine just in case an errno is thrown value is always > 0
};

struct list_function_table {
  uint8_t (*contains)(list *, list_element *);
  void (*iterator)(list *, list_info, void (*callback)(list *, list_element *));
  uint8_t (*add)(list *, list_element *);
  list_element *(*get)(list *, uint64_t);
  uint8_t (*indexof)(list *, list_element *, uint64_t *);
  uint8_t (*resize)(list *, uint16_t);
  uint8_t (*update_buffer_size)(list *, void *);
  uint8_t (*remove_by_element)(list *, list_element *);
  uint8_t (*remove_by_index)(list *, uint64_t);
  uint8_t (*contains_all)(list *, list_element **);
  uint8_t (*add_all)(list *, list_element **);
  uint8_t (*remove_all)(list *, list_element **);
  uint8_t (*retains_all)(list *, list_element **);
  list_element *(*get_start_address)(list *);
  list_element *(*get_end_address)(list *);
};

uint8_t init_list_function_table(list *, list_element **, list_function_table *);

#ifdef __cplusplus
}
#endif
#endif