#include <electronetsoft/util/types.h>
#include <electronetsoft/arithmos/adt/list.h>
#include <electronetsoft/arithmos/memory/patcher.h>
#include <electronetsoft/arithmos/list/contiguous_buffer.h>
#include <electronetsoft/util/utilities.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline status_code contiguous_update_buffer_size(list *buffer, uint64_t old_limit, void *caller) {
    if (rvalue(buffer) == NULL || rvalue(buffer->elements) == NULL
        || rvalue(buffer->operations) == NULL
        || rvalue(buffer->operations->update_buffer_size) == NULL
        || rvalue(caller) == NULL) {

        return EUNDEFINEDBUFFER;
    }
    return buffer->operations->update_buffer_size(buffer, old_limit, caller);
}

static inline status_code contiguous_buffer_memory_update(list *buffer) {
    if (NULL == buffer || NULL == buffer->elements) {
        return EUNDEFINEDBUFFER;
    }

    buffer->elements_memory.start_address = buffer->elements;
    buffer->elements_memory.end_address = buffer->elements + (buffer->capacity - 1);

    return PASS;
}

static inline status_code get_start_address(list *buffer, list_element **address) {
    if (NULL == buffer || NULL == address) {
        return EUNDEFINEDBUFFER;
    }
    *address = buffer->elements_memory.start_address;
    return PASS;
}

static inline status_code get_end_address(list *buffer, list_element **address) {
    if (NULL == buffer || NULL == address) {
        return EUNDEFINEDBUFFER;
    }
    *address = buffer->elements_memory.end_address;
    return PASS;
}

static inline status_code contiguous_buffer_resize(list *buffer, uint16_t left_shift_exponent) {
    if (NULL == buffer) {
        return EUNDEFINEDBUFFER;
    }
    buffer->capacity = (buffer->capacity << left_shift_exponent) + 1;
    return PASS;
}

static inline status_code contiguous_buffer_add(list *buffer, list_element *element) {
    if (NULL == buffer || NULL == element) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;
    
    if (0 != buffer->capacity && buffer->position >= buffer->capacity) {
        // run a stretching algorithm
        // the stretching algorithm
        uint64_t old_limit = buffer->capacity;
        if (NULL != buffer->operations &&
                NULL != buffer->operations->resize) {
            buffer->operations->resize(buffer, 0x02);
        }
        __code = contiguous_update_buffer_size(buffer, old_limit, buffer->operations->add);
        if (PASS != __code) {
            return __code;
        }
    }
    
    list_element *buffer_element = buffer->elements + buffer->position;
    buffer_element->data = element->data;
    buffer_element->metadata = element->metadata;
    buffer_element->size = element->size;
    buffer_element->type = element->type;

    buffer->position += 1;
    __code = contiguous_buffer_memory_update(buffer);
    
    return __code;
}

static inline status_code contiguous_buffer_insert(list *buffer,
                                 list_element *element,
                                 uint64_t index) {
    // preprocessor automata -- Input Validation stage
    if (NULL == buffer || NULL == element) {
        return EUNDEFINEDBUFFER;
    }

    // preprocessor automata -- Buffer Size Validation Stage and recorrection algorithm
    status_code __code;

    if (0 != buffer->capacity && index >= buffer->capacity) {
        // run a stretching algorithm
        // the stretching algorithm
        uint64_t old_limit = buffer->capacity;
        buffer->capacity = (index << 2) + 1;
        __code = contiguous_update_buffer_size(buffer, old_limit, buffer->operations->insert);
        if (PASS != __code) {
            return __code;
        }
    }

    list_element *buffer_element = buffer->elements + index;

    // preprocessor automata -- Collision Detection and callbacks
    if (NULL != buffer_element->data) {
        if (NULL != buffer->operations &&
            NULL != buffer->operations->on_collision) {
            __code = buffer->operations->on_collision(buffer, index, element);

            if (PASS != __code) {
                return __code;
            }
        }
        return PASS;
    }

    // processor automata -- Insertion of the new element
    // deep copy data to the existing buffer
    buffer_element->data = element->data;
    buffer_element->size = element->size;
    buffer_element->metadata = element->metadata;
    buffer_element->type = element->type;

    return PASS;
}

static inline status_code contiguous_buffer_insert_overwrite(list *buffer,
                                           list_element *element,
                                           uint64_t index) {
    if (NULL == buffer || NULL == buffer->elements ||
            NULL == element || 0 == buffer->capacity) {
        return EUNDEFINEDBUFFER;
    }

    // preprocessor automata -- Buffer Size Validation Stage and recorrection algorithm
    status_code __code = PASS;

    if (0 != buffer->capacity && index >= buffer->capacity) {
        // run a stretching algorithm
        // the stretching algorithm
        uint64_t old_limit = buffer->capacity;
        buffer->capacity = (index << 2) + 1;
        __code = contiguous_update_buffer_size(buffer, old_limit, buffer->operations->insert_overwrite);
        if (PASS != __code) {
            return __code;
        }
    }

    list_element *buffer_element = buffer->elements + index;

    // preprocessor automata -- Collision Detection and callbacks
    if (NULL != buffer_element->data) {
        if (NULL != buffer->operations &&
            NULL != buffer->operations->on_collision_overwrite) {
            __code = 
                buffer->operations->on_collision_overwrite(buffer, index, element);
        }
    }

    // processor automata -- Insertion of the new element
    buffer_element->data = element->data;
    buffer_element->metadata = element->metadata;
    buffer_element->size = element->size;
    buffer_element->type = element->type;

    return __code;
}

static inline status_code contiguous_buffer_add_all(list *buffer, list_element *elements, uint64_t n_elements) {
    if (NULL == buffer || NULL == elements) {
        return EUNDEFINEDBUFFER;
    }

    if (0 == n_elements) {
        return EBUFFERTURNCATION;
    }
    
    status_code __code;

    for (uint64_t i = 0; i < n_elements; i++) {
        __code = contiguous_buffer_add(buffer, elements + i);
        if (PASS != __code) {
            return __code;
        }
    }
    
    return PASS;
}

static inline status_code unsafe_leftshift_items_by_one(list *buffer, uint64_t start) {
    uint64_t n_elements = buffer->position;
    list_element *elements = buffer->elements;

    // length and indexes semantics guard

    // you cannot do elements shifting 
    // if the index of the element 
    // is between the list::position
    // and the list::capacity
    if (start >= buffer->position) {
        elements[start] = (list_element) {0};
        return PASS;
    }

    if (buffer->capacity - start < buffer->position - start) {
        n_elements = buffer->capacity;
    }

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
    for (uint64_t i = start; i < n_elements - 1; i++) {
        elements[i] = elements[i + 1]; // shift the elements to the left by one index (+ 1)
                                       // by performing successive deep copies and clearing the right element
        elements[i + 1] = (list_element) {0};
        // OR
        // memset(elements + (i + 1), 0, sizeof(list_element));        
    }
    return contiguous_update_buffer_size(buffer, 0, buffer->operations->remove_by_index);
}

static inline status_code unsafe_get_index_from_element(list *buffer, list_element *element, uint64_t *output) {
    uint8_t is_found = 0;
    // determine the index first
    // this adds an f(N) overhead to the total clock complexity
    // use list::capacity to be cohesive with the list_operations::insert(...)
    // functions
    // note that; this is a safe iteration as
    // the data buffer hasn't been dereferenced
    // the data address is being compared numerically!
    for (uint64_t i = 0; i < buffer->capacity; i++) {
        list_element *buffer_element = buffer->elements + i;
        if (buffer_element->type == element->type && 
                rvalue(buffer_element->data) == element->data) {
            *output = i;
            is_found = 1;
            break;
        }
    }
    if (!is_found) {
        return ENOELEMENT;
    }
    return PASS;
}

static inline status_code contiguous_buffer_remove0(list *list, uint64_t index) {
    if (rvalue(list) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    
    if (index >= list->capacity) {
        // index out of boundaries
        return EBUFFERTURNCATION;
    }
    
    status_code left_shift = unsafe_leftshift_items_by_one(list, index);

    if (PASS != left_shift) {
        return left_shift;
    }

    // update the index
    list->position -= 1;
    
    // update the memory addresses
    status_code memory_update = contiguous_buffer_memory_update(list);
    
    return memory_update;
}

static inline status_code contiguous_buffer_remove_by_element(list *buffer, list_element *element) {
    // pre-processing automata -- Input Validation
    if (NULL == buffer || NULL == element) {
        return EUNDEFINEDBUFFER;
    }

    // pre-processing automata -- Retrieve the index of the element
    uint64_t index = 0;
    status_code __code = unsafe_get_index_from_element(buffer, element, &index);

    // pre-processing automata -- Premature return upon failure
    if (PASS != __code) {
        // element not found
        return __code;
    }

    // processing automata -- Drop an item from the list using a linear shifting algorithm
    __code = unsafe_leftshift_items_by_one(buffer, index);

    if (PASS != __code) {
        return __code;
    }

    // post-processing automata -- update the index and the addresses buffers
    buffer->position -= 1;

    __code = contiguous_buffer_memory_update(buffer);
    if (PASS != __code) {
        return __code;
    }

    return PASS;
}

static inline status_code contiguous_buffer_remove_all(list *list, list_element **elements) {
    if (rvalue(list) == NULL || rvalue(elements) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    status_code code0;
    for (uint64_t i = 0; rvalue(elements[i]) != NULL; i+=1) {
        code0 = contiguous_buffer_remove_by_element(list, elements[i]);
        if (PASS != code0) {
            return code0; // terminate with failure
        }
    }
    return PASS; // success
}

static inline status_code contiguous_buffer_iterator(list *buffer,
                                                     iterator_info info,
                                                     status_code (*callback)(list *, iterator_info, list_element *)) {
    if (rvalue(buffer) == NULL || rvalue(callback) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    status_code __code = PASS;
    for (uint64_t i = info.index; i < info.length; i += info.rate) {
        __code = callback(buffer, (iterator_info) {
            .index = i,
            .length = buffer->capacity,
            .metadata = info.metadata,
            .rate = info.rate
        }, (buffer->elements + i));
        // use the return value as a control variable
        if (PASS != __code) {
            return __code;
        }
    }
    return __code;
}

static inline status_code contiguous_buffer_contains_all(list *buffer, list_element *elements, uint64_t size) {
    // you could run this in Pi(V) * E(I) = V * V * (E + E + E ....) which
    // reduces to V^2 or square function
    // or better is Pi(V) * E(I) = V1 * V2 * E'(I)  which decomposes the clock-complexity
    // dependencies 
    
    if (NULL == buffer || NULL == elements) {
        return EUNDEFINEDBUFFER;
    }

    if (size > buffer->capacity || 0 == size) {
        return EBUFFERTURNCATION;
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
    for (uint64_t i = 0; i < size; i += 1, search_progress.length += 1) {
        
        // ----- Clock Complexity Analysis ------
        // loop closure Pi(V2) = limit, N(c2) = V2 * E'(I) = limit * (1 + 1)
        // this subroutine complexity rises linearly when the length of the elements increases
        for (uint64_t k = 0; k < buffer->capacity; k += 1) {
            if (rvalue(buffer->elements[k].data) == 
                            elements[i].data) {
                search_progress.found += 1;
                break;
            }
        }

        // a greedy mechanism: to ensure breaking the loop
        // premarturely if the list buffer has been exhausted
        // and the found items are less than expected (i.e., item is not found)
        // as by the end of the former loop each time; this must be true:
        // search_progress.found == search_progress.length
        if (search_progress.found < search_progress.length) {
            return ENOELEMENT;
        }
    }
    
    // elements not found!
    return PASS;
}

static inline status_code contiguous_buffer_contains(list *buffer, list_element *element) {
    if (NULL == buffer || NULL == element) {
        return EUNDEFINEDBUFFER;
    }
    
    // ----- Clock Complexity Analysis ------
    // loop closure Pi(V2) = limit, N(c2) = V2 * E'(I) = limit * (1 + 1)
    // this subroutine complexity rises linearly when the length of the elements increases
    uint64_t output = 0;
    return unsafe_get_index_from_element(buffer, element, &output);
}

static inline status_code contiguous_buffer_compare(list *buffer, list_element *element) {
    if (NULL == buffer || NULL == element || 0 == buffer->capacity) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == element->compare) {
        return UNEXPECTED_ERROR;
    }

    for (uint64_t i = 0; i < buffer->capacity; i += 1) {
        list_element *buffer_element = buffer->elements + i;
        if (PASS != element->compare(element, buffer_element)) {
            continue;
        }
        return PASS;
    }


    return ENOELEMENT;
}

static inline status_code contiguous_buffer_get(list *buffer, uint64_t index,
                                                list_element *out) {
    if (NULL == buffer || NULL == out) {
        return EUNDEFINEDBUFFER;
    }
    
    if (index >= buffer->capacity) {
        return EUNDEFINEDBUFFER;
    }
    list_element *buffer_element = buffer->elements + index;

    out->data = buffer_element->data;
    out->metadata = buffer_element->metadata;
    out->size = buffer_element->size;
    out->type = buffer_element->type;

    return PASS;
}

static inline status_code contiguous_buffer_indexof(list *buffer, list_element *element, uint64_t *index) {
    if (NULL == buffer ||
            NULL == index || NULL == element) {
        return EUNDEFINEDBUFFER;
    }
    
    for (uint64_t i = 0; i < buffer->position; i++) {
        list_element *buffer_element = buffer->elements + i;
        if (rvalue(buffer_element->data) == element->data) {
            *index = i;
            return PASS;
        }
    }
    
    return ENOELEMENT;
}

/**
 * Dispatched by the API callers callbacks when a "resize" command
 * is executed to continue operations safely.
 *
 * @param buffer the data buffer of interest
 * @param caller the caller address
 * @return PASS to indicate a pass code, otherwise a failure code
 */
static inline status_code dynamic_alloc_update_buffer_size(list *buffer, uint64_t old_limit, void *caller) {
    if (rvalue(buffer) == NULL || rvalue(caller) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // expand
    if (caller == buffer->operations->add ||
        caller == buffer->operations->insert ||
        caller == buffer->operations->insert_overwrite) {

        buffer->elements = realloc(buffer->elements, buffer->capacity * sizeof(list_element));
        if (NULL == buffer->elements) {
            return EBUFFERTURNCATION;
        }

        memset(buffer->elements + old_limit, 0,
        (buffer->capacity - old_limit) * sizeof(list_element));
    } else if (caller == buffer->operations->remove_by_index) {
        // shrink
        buffer->capacity >>= 2; // shrunk the limit by power of 2
        buffer->elements = realloc(buffer->elements, 
            (size_t) (buffer->position << 2) * sizeof(list_element));
    }

    if (NULL == buffer->elements) {
        return EBUFFERTURNCATION;
    }

    return PASS;
}

status_code init_contiguous_buffer(list *list, list_element *elements, list_operations *table, api_lifecycle *lifecycle) {
    if (rvalue(list) == NULL || rvalue(elements) == NULL ||
        rvalue(table) == NULL || list->capacity == 0) {
        return EUNDEFINEDBUFFER;
    }
    
    table->iterator = &contiguous_buffer_iterator; // tested!
    table->add = &contiguous_buffer_add; // tested!
    table->add_all = &contiguous_buffer_add_all; // tested!
    table->insert = &contiguous_buffer_insert;
    table->insert_overwrite = &contiguous_buffer_insert_overwrite;
    table->remove_by_element = &contiguous_buffer_remove_by_element; // tested!
    table->remove_by_index = &contiguous_buffer_remove0; // tested!
    table->remove_all = &contiguous_buffer_remove_all; // tested!
    table->retains_all = NULL;
    table->contains = &contiguous_buffer_contains; // tested!
    table->compare = &contiguous_buffer_compare;
    table->contains_all = &contiguous_buffer_contains_all; // tested!
    table->resize = &contiguous_buffer_resize;
    table->get = &contiguous_buffer_get; // tested!
    table->index_of = &contiguous_buffer_indexof; // tested!
    table->get_start_address = &get_start_address;
    table->get_end_address = &get_end_address;
    table->lifecycle = lifecycle;
    // default update buffer size function
    table->update_buffer_size = &dynamic_alloc_update_buffer_size;

    list->operations = table;
    list->elements = elements;
    
    list->position = 0;
  
    list->elements_memory = (memory_partition) {
        .start_address = &(list->elements[0]),
        .end_address = 0 // this is dynamic and it needs to be updated on each WRITE operation!
    };
    
    return PASS;
}
