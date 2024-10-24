#include <electrostatic/electronetsoft/algorithm/arithmos/adt/queue.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/queue/linked_queue.h>
//#include <electrostatic/electronetsoft/algorithm/arithmos/queue/array_queue.h>
//#include <electrostatic/electronetsoft/algorithm/arithmos/queue/priority_queue.h>

uint8_t init_queue_function_table(queue *queue, queue_function_table *table) {
    if (queue->type == LINKED) {
        return init_linked_queue_function_table(queue, table);
    } else if (queue->type == ARRAY) {
        return 0;
    } else if (queue->type == TREE) {
        return 0;
    }
    return 1;
}

/**
 * Initializes the errno structure for a queue.
 */
void init_queue_errno(queue *queue) {
    if (queue == NULL) {
        return;
    }
    if (&(queue->error) == NULL) {
        queue->error = (errno){
            .value = 0x00};
    }
}