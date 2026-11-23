// Header file for memory patcher algorithms.
// Author: pavl_g.
// Conceptually Based on: the Finite-Automata Theory.

#ifndef PATCHER_H_
#define PATCHER_H_

#include <stdlib.h>
#include <electronetsoft/util/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct memory_partition {
    void* start_address;
    void* end_address;
    size_t offset;
    size_t size;
    size_t pointer_location;
    status_code (*invalidate)(memory_partition *);
};

static inline status_code invalidate(memory_partition *partition) {
    if (NULL == partition ||
        NULL == partition->start_address ||
        NULL == partition->end_address) {
        return EUNDEFINEDBUFFER;
    }

    if (partition->offset > partition->size) {
        return EBUFFERTURNCATION;
    }

    partition->start_address += partition->offset;
    partition->end_address = partition->start_address + partition->size;
    partition->pointer_location = partition->offset + partition->size;

    return PASS;
}

static inline status_code create(void *buffer, size_t offset, size_t size, memory_partition *partition) {
    if (NULL == buffer || NULL == partition) {
        return EUNDEFINEDBUFFER;
    }

    if (offset > size) {
        return EBUFFERTURNCATION;
    }

    partition->start_address = buffer + offset;
    partition->end_address = (buffer + offset) + size;
    partition->offset = offset;
    partition->size = size;
    partition->pointer_location = offset + size;
    partition->invalidate = &invalidate;

    return PASS;
}

#ifdef __cplusplus
}
#endif
#endif