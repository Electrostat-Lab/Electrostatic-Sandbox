#include <electrostatic/algorithm/arithmos/adt/list.h>
#include <electrostatic/algorithm/arithmos/memory/patcher.h>
#include <electrostatic/algorithm/arithmos/list/contiguous_buffer.h>
#include <electrostatic/util/errno/errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline uint8_t contiguous_update_buffer_size(list *list, void *caller) {
    if (list == NULL || list->elements == NULL
        || list->function_table == NULL
        || list->function_table->update_buffer_size == NULL
        || caller == NULL) {
        
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1; 
    }
    return list->function_table->update_buffer_size(list, caller);
}

static inline uint8_t contiguous_buffer_memory_update(list *list) {
    if (list == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1; 
    }
    
    if (list->elements == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    list->elements_memory.start_address = &(list->elements[0]);
    list->elements_memory.end_address = &(list->elements[list->length - 1]);
     
    return 0;
}

static inline list_element *get_start_address(list *buffer) {
    if (buffer == NULL) {
        init_errno(&buffer->error);
        buffer->error.value = EUNDEFINEDBUFFER;
        return NULL; 
    }
    
    return *((list_element **) buffer->elements_memory.start_address);
}

static inline list_element *get_end_address(list *buffer) {
    if (buffer == NULL) {
        init_errno(&buffer->error);
        buffer->error.value = EUNDEFINEDBUFFER;
        return NULL; 
    }
    
    return *((list_element **) buffer->elements_memory.end_address);
}

static inline uint8_t contiguous_buffer_resize(list *list, uint16_t left_shift_exponent) {
    if (list == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    list->limit <<= left_shift_exponent;
    return 0;
}

static inline uint8_t contiguous_buffer_add(list *list, list_element *element) {
    if (list == NULL || element == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    if (list->limit != 0 && list->length >= list->limit) {
        // run a stretching algorithm
        // the stretching algorithm 
        list->function_table->resize(list, 0x02);
        contiguous_update_buffer_size(list, list->function_table->add);
    }
    
    list->elements[list->length] = element;
    list->length += 1;
    contiguous_buffer_memory_update(list);
    
    return 0;
}

static inline uint8_t contiguous_buffer_add_all(list *list, list_element **elements) {
    if (list == NULL || elements == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    for (uint64_t i = 0; elements[i] != NULL; i++) {
        contiguous_buffer_add(list, elements[i]);
    }
    
    return 0;
}

static inline uint8_t unsafe_leftshift_items_by_one(list *list, uint64_t start) {
    list_element **elements = list->elements;
    // this algorithm merges the list items into the start index by
    // simply operating on two indices at the same time
    // and it entails shifting elements from their indicies towards
    // the start index, replacing the element in the start index
    // and finishes by nullifying the last element address
    // commonly used in remove(...) algorithms
    // runs in f[(limit - 2) - start] constant clock-complexity for the same input (deterministic complexity)
    // ---- Clock-Complexity Analysis Starts ----
    // the clock-complexity gets better when the start index is near the end of the structure
    // however, it gets worse when the start index is near the zero end.
    // and the middle-case scenario is apparently in the approximate median index.
    // ---- Clock-Complexity Analysis Ends ----
    // ---- Memory-Complexity Analysis ----
    // the heap-complexity decreases by a unit of 1*(size) of the element being removed
    // and, since the element is an address, then 1*(8 bytes) is 8 bytes
    // this is a cosntant function, so a ratio of 1 (element): 8 (bytes)
    // ---- Memory-Complexity Analysis ----
    for (uint64_t i = start; i < list->length; i++) {
        elements[i] = elements[i + 1]; // shift the elements to the left by one index (+ 1)
        elements[i + 1] = NULL;
    }
    contiguous_update_buffer_size(list, list->function_table->remove_by_index);
    return 0;
}

static inline uint8_t unsafe_get_index_from_element(list *list, list_element *element, uint64_t *output) {
    uint8_t is_found = 0;
    // determine the index first
    // this adds an f(N) overhead to the total clock complexity
    for (uint64_t i = 0; i < list->length; i++) {
        if (list->elements[i] == element) {
            *output = i;
            is_found = 1;
            break;
        }
    }
    return is_found;
}

static inline uint8_t contiguous_buffer_remove0(list *list, uint64_t index) {
    if (list == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    if (index >= list->limit) {
        // index out of boundaries
        init_errno(&list->error);
        list->error.value = EBUFFERTURNCATION;
        return 1;
    }
    
    uint8_t ret = unsafe_leftshift_items_by_one(list, index);
    
    // update the index
    list->length -= 1;
    
    // update the memory addresses
    contiguous_buffer_memory_update(list);
    
    return ret;
}

static inline uint8_t contiguous_buffer_remove_by_element(list *list, list_element *element) {
    if (list == NULL || element == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    uint64_t index = 0;
    uint8_t is_found = unsafe_get_index_from_element(list, element, &index);
    
    if (!is_found) {
        // element not found
        init_errno(&list->error);
        list->error.value = ENOELEMENT;
        return 1;
    }
    
    if (index >= list->limit) {
        // index out of boundaries
        init_errno(&list->error);
        list->error.value = EBUFFERTURNCATION;
        return 1;
    }
    
    uint8_t ret = unsafe_leftshift_items_by_one(list, index);
    
    // update the index
    list->length -= 1;
    
    // update the memory addresses
    contiguous_buffer_memory_update(list);
    
    return ret;
}

static inline uint8_t contiguous_buffer_remove_all(list *list, list_element **elements) {
    if (list == NULL || elements == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    for (uint64_t i = 0; elements[i] != NULL; i+=1) {
        if (contiguous_buffer_remove_by_element(list, elements[i]) != 0) {
            return 1; // terminate with failure
        }
    }
    return 0; // success
}

static inline void contiguous_buffer_iterator(list* list, list_info info, void (*callback)(struct list *, list_element *)) {
    if (list == NULL || callback == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return;
    } 
    for (uint64_t i = info.start_index; i < info.length; i += info.rate) {
        callback(list, list->elements[i]);
    }
}

static inline uint8_t contiguous_buffer_contains_all(list *list, list_element **elements) {
    // you could run this in Pi(V) * E(I) = V * V * (E + E + E ....) which
    // reduces to V^2 or square function
    // or better is Pi(V) * E(I) = V1 * V2 * E'(I)  which decomposes the clock-complexity
    // dependencies 
    
    if (list == NULL || elements == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    struct {
        uint64_t length;
        uint64_t found;
    } search_progress = {
        .length = 0,
        .found = 0
    };
    
    // ----- Clock Complexity Analysis ------
    // loop closure Pi(V1) = length, N(c1) = V1 * E(I) = V1 * V2 * E'(I) = length * limit * (1 + 1)
    // this complexity rises linearly when the length of the searchables increases
    // and exponentially if both increases
    // ----- Memory Complexity Analysis ------
    // Stack memory might rise by 2x, but it will drop in a glance as this
    // algorithm finishes up! Also, depending on your implementation, if the
    // list_element** component is heap-allocated then higher memory usages may be
    // incurred at this point.
    for (uint64_t i = 0; elements[i] != NULL; i += 1, search_progress.length += 1) {
        
        // ----- Clock Complexity Analysis ------
        // loop closure Pi(V2) = limit, N(c2) = V2 * E'(I) = limit * (1 + 1)
        // this subroutine complexity rises linearly when the length of the elements increases
        for (uint64_t k = 0; k < list->length; k += 1) {
            if (list->elements[k] == elements[i]) {
                search_progress.found += 1;
            }
        }
    }
    
    if (search_progress.found == search_progress.length) {
        return 0; // all items are found!
    }
    
    // elements not found!
    init_errno(&list->error);
    list->error.value = ENOELEMENT;
    
    return 1;
}

static inline uint8_t contiguous_buffer_contains(list *list, list_element *element) {
    if (list == NULL || element == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    // ----- Clock Complexity Analysis ------
    // loop closure Pi(V2) = limit, N(c2) = V2 * E'(I) = limit * (1 + 1)
    // this subroutine complexity rises linearly when the length of the elements increases
    for (uint64_t i = 0; i < list->length; i += 1) {
        if (list->elements[i] == element) {
            return 0;
        }
    }
    return 1;
}

static inline list_element *contiguous_buffer_get(list *list, uint64_t index) {
    if (list == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return NULL;
    }
    
    if (index >= list->limit) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return NULL;
    }
    
    return list->elements[index];
}

static inline uint8_t contiguous_buffer_indexof(list *list, list_element *element, uint64_t *index) {
    if (list == NULL || element == NULL || index == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    for (uint64_t i = 0; i < list->length; i++) {
        if (list->elements[i] == element) {
            *index = i;
            return 0;
        }
    }
    
    init_errno(&list->error);
    list->error.value = ENOELEMENT;
    
    return 1;
}

uint8_t init_contiguous_buffer(list *list, list_element **elements, list_function_table *table) {
    if (list == NULL || elements == NULL || table == NULL) {
        init_errno(&list->error);
        list->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    
    table->iterator = &contiguous_buffer_iterator; // tested!
    table->add = &contiguous_buffer_add; // tested!
    table->add_all = &contiguous_buffer_add_all; // tested!
    table->remove_by_element = &contiguous_buffer_remove_by_element; // tested!
    table->remove_by_index = &contiguous_buffer_remove0; // tested!
    table->remove_all = &contiguous_buffer_remove_all; // tested!
    table->retains_all = NULL;
    table->contains = &contiguous_buffer_contains; // tested!
    table->contains_all = &contiguous_buffer_contains_all; // tested!
    table->resize = &contiguous_buffer_resize;
    table->get = &contiguous_buffer_get; // tested!
    table->indexof = &contiguous_buffer_indexof; // tested!
    table->get_start_address = &get_start_address;
    table->get_end_address = &get_end_address;
    
    list->function_table = table;
    list->elements = elements;
    
    list->length = 0;
    list->limit = 8 << 2;
    list->error = (errno) {
        .value = 0
    };
  
    list->elements_memory = (memory_partition) {
        .start_address = &(list->elements[0]),
        .end_address = 0 // this is dynamic and it needs to be updated on each WRITE operation!
    };
    
    return 0;
}
