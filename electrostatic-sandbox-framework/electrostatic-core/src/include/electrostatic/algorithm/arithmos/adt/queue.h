//
// ADT file for the Queues.
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

#ifndef QUEUE_H_
#define QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdlib.h>
#include <electrostatic/algorithm/arithmos/memory/patcher.h>
#include <electrostatic/util/errno/errno.h>

typedef enum queue_type(queue_type);
typedef struct queue_element(queue_element);
typedef struct queue(queue);
typedef struct queue_function_table(queue_function_table);

enum queue_type {
 ARRAY,
 LINKED,
 TREE
};

/**
 * An object prototype to define the structural aspect
 * of the automata to be used.
 */
struct queue_element {
 void *element;
 size_t size; // this protects the flow of the application, make sure to use the correct size via sizeof() routine
};

/**
 * An object prototype to define the structural aspect
 * of the automata to be used.
 */
struct queue {
 queue_element **elements; //contigous memory can be operated using partition schemes algorithms
 queue_type type;
 memory_partition elements_memory;
 uint64_t count;
 uint64_t limit;
 queue_function_table *function_table;
 errno error; //dereference and examine just in case an errno is thrown value is always > 0
};

/**
 * An object prototype to define the behavior
 * of the automata to be used.
 */
struct queue_function_table {

 /**
  * Allocates a new empty queue buffer on the heap with a
  * buffer size.
  *
  * @param size_t the buffer size in Unsigned Longs
  * @return an address to the newly allocated queue buffer in the heap.
  */
 queue *(*alloc)(size_t);

 /**
  * Allocates a new queue buffer on the heap with a
  * buffer size, and fill it using another queue-elements buffer.
  *
  * <p>
  * The type of the copying algorithm depends on the compilation units implementing
  * this 
  *
  * @param size_t the buffer size in Unsigned Longs
  * @param queue_element** an address to the queue-elements buffer used to fill this queue buffer.
  * @return an address to the newly allocated queue buffer in the heap.
  */
 queue *(*alloc_init)(size_t, queue_element **);

 /**
  * Deallocates a specified queue buffer from the heap and its elements.
  *
  * @param queue* the address of the queue buffer to deallocate
  * @return (0) on completion, (1) on error and raises the errno value
  */
 uint8_t (*deallocate)(queue *);

 /**
  * Inserts the specified element into this queue if it is possible to do so
  * immediately without violating capacity restrictions, returning
  * {@code true} upon success and returning an ERRNO_NO_SPACE
  * if no space is currently available.
  *
  * @param queue* the address to the queue object.
  * @param queue_element* the address to the queue-element to add.
  * @return {@code 0} if success, ERRNO_NO_SPACE on failure.
  */
 uint8_t (*add)(queue *, queue_element *);

 /**
  * Inserts the specified element into this queue if it is possible to do
  * so immediately without violating capacity restrictions.
  * 
  * When using a capacity-restricted queue, this method is generally
  * preferable over the {@link #add}, which can fail to insert an element only
  * by throwing an error "ERRNO_NO_SPACE".
  *
  * @param queue* the address to the queue object.
  * @param queue_element* the address to the queue-element to add.
  * @return {@code 0} if the element was added to this queue, else
  *         {@code 1}
  */
 uint8_t (*offer)(queue *, queue_element *);

 /**
  * Retrieves and removes the head of this queue.  This method differs
  * from {@link #poll() poll()} only in that it throws an error if
  * this queue is empty "ERRNO_EMPTY_BUFFER".
  *
  * @param queue* the address to the queue object to operate on.
  * @return the head of this queue
  */
 queue_element *(*remove)(queue *);

 /**
  * Retrieves and removes the head of this queue,
  * or returns {@code null} if this queue is empty.
  *
  * @param queue* the address to the queue object to operate on. 
  * @return the head of this queue, or {@code null} if this queue is empty
  */
 queue_element *(*poll)(queue *);

 /**
  * Retrieves, but does not remove, the head of this queue.  This method
  * differs from {@link #peek peek} only in that it throws an errno
  * if this queue is empty "ERRNO_EMPTY_BUFFER".
  *
  * @param queue* the address to the queue object to operate on.  
  * @return the head of this queue or NULL with an errno code.
  */
 queue_element *(*element)(queue *);

 /**
  * Retrieves, but does not remove, the head of this queue,
  * or returns {@code null} if this queue is empty.
  *
  * @param queue* the address to the queue object to operate on.   
  * @return the head of this queue, or {@code null} if this queue is empty
  */
 queue_element *(*peek)(queue *);

 /**
  * Tests whether this queue structure is allocated using the dynamic memory
  * allocation routines through the {@code queue_function_table::alloc(size_t)} and
  * the {@code queue_function_table::alloc_init(size_t, queue_element**)}.
  *
  * @return (1) if this is true, (0) otherwise.
  */
 uint8_t is_malloc;
};

/**
 * Initializes a queue function table with a queue data structure according to
 * its type. This is essentially a ready factory methods that initializes a queue function
 * table on an addressed memory.
 *
 * @param queue* an address to the queue data structure to use its type.
 * @param queue_function_table* an address to a function table to initialize.
 * @return (0) for success, (1) for failure.
 */
uint8_t init_queue_function_table(queue *, queue_function_table *);

uint8_t init_queue(queue *);

/**
 * Initializes the errno structure for a queue.
 */
void init_queue_errno(queue *);


#ifdef __cplusplus
};
#endif

#endif