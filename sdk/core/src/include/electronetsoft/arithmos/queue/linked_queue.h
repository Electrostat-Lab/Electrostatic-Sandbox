////
//// A header to declare the directives for the constructs of the linked queues.
//// Author: pavl_g
//// Notice, the functions table for linked queues is internalized for maintenance purposes
//// it can only be exposed via these constructs through the "queue_function_table" routines.
//// use the "queue.c" library with the LINKED routine to route the execution to this library.
////
//
//#ifndef LINKED_QUEUE_H_
//#define LINKED_QUEUE_H_
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#include <electrostatic/electronetsoft/algorithm/arithmos/adt/queue.h>
//
//typedef enum linked_node_type(linked_node_type);
//typedef struct node_provider(node_provider);
//
//enum linked_node_type {
//    SINGLE_ENDED,
//    DOUBLE_ENDED,
//    CLUSTER
//};
//
//struct node_provider {
//    void* data;
//    queue_element *next;
//    queue_element *previous;
//    queue_element *mid; // for cluster implementations only!
//    linked_node_type type;
//};
//
//uint8_t init_linked_queue(queue *);
//
///**
// * Initializes the queue element data structure by assigning
// * the address to the linked node address (denotation) and with
// * the correct size.
// *
// * @param queue_element* the address of the queue element to initialize
// * @param node_provider* the node_provider address to use into the queue element.
// * @return (0) for success, and (1) for failure.
// */
//uint8_t init_linked_queue_element(queue_element *, node_provider *);
//uint8_t init_linked_queue_function_table(queue *, queue_function_table *);
//queue_element *allocate_node_provider_queue_element();
//uint8_t deallocate_node_provider_queue_element(queue_element *);
//uint8_t is_linked_queue_element(queue *, queue_element *);
//
//#ifdef __cplusplus
//}
//#endif
//#endif