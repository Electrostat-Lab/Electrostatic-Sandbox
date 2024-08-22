//
// A header file designating a concurrent implementation for the thread-non-safe linked_queue.
// Author: pavl_g.
//

#ifndef CONCURRENT_LINKED_QUEUE_H_
#define CONCURRENT_LINKED_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <electrostatic/algorithm/arithmos/queue/linked_queue.h>
#include <pthread.h>

static inline queue *concurrent_linked_queue_alloc(size_t size, pthread_mutex_t *mutex) {
    return NULL;
}

#ifdef __cplusplus
}
#endif
#endif