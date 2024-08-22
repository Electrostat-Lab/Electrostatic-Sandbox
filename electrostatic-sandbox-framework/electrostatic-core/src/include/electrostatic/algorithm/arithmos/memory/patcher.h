// Header file for memory pathcer algorithms.
// Author: pavl_g.
// Conceptually Based on: the Finite-Automata Theory.

#ifndef PATCHER_H_
#define PATCHER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

typedef struct {
    void* start_address;
    void* end_address;
    size_t offset;
    size_t size;
    size_t pointer_location;

    void (*invalidate)(void*);

} memory_partition;

#ifdef __cplusplus
}
#endif
#endif