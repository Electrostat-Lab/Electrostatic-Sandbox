// Header file for memory pathcer algorithms.
// Author: pavl_g.
// Conceptually Based on: the Finite-Automata Theory.

#ifndef PATCHER_H_
#define PATCHER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <electrostatic/electronetsoft/util/types.h>

struct memory_partition {
    void* start_address;
    void* end_address;
    size_t offset;
    size_t size;
    size_t pointer_location;
    void (*invalidate)(void*);
};

#ifdef __cplusplus
}
#endif
#endif