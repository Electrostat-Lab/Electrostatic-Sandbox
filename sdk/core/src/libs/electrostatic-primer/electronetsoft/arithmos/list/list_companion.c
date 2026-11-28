#include <electronetsoft/util/types.h>
#include <electronetsoft/arithmos/list/list_companion.h>
#include <electronetsoft/arithmos/adt/list.h>

status_code list_stretch_capacity(list *buffer, void *caller) {
    if (NULL == buffer || 
            NULL == buffer->elements || 
                NULL == caller) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == buffer->operations || 
            NULL == buffer->operations->calculate_resize ||
                NULL == buffer->operations->update_buffer_size) {
        return INVALID_OP;
    }

    if (caller != buffer->operations->add && 
            caller != buffer->operations->insert &&
                caller != buffer->operations->insert_overwrite) {
        return EINCOMPATTYPE;
    }
    if (0 == buffer->capacity || buffer->capacity < buffer->position) {
        return EBUFFERTURNCATION;
    }

    uint64_t old_capacity = buffer->capacity;

    status_code __code = buffer->operations->calculate_resize(buffer, 1, 0x02, caller);
    if (PASS != __code) {
        return __code;
    }

    return buffer->operations->update_buffer_size(buffer, old_capacity, buffer->operations->insert);
}

status_code list_shrink_capacity(list *buffer, void *caller) {
    if (NULL == buffer || 
            NULL == buffer->elements || 
                NULL == caller) {
        return EUNDEFINEDBUFFER;
    }
    if (NULL == buffer->operations ||
            NULL == buffer->operations->calculate_resize ||
                NULL == buffer->operations->update_buffer_size) {
        return INVALID_OP;
    }
    if (caller != buffer->operations->remove_by_index && 
            caller != buffer->operations->remove_by_element) {
        return EINCOMPATTYPE;
    }
    if (0 == buffer->capacity || buffer->capacity < buffer->position) {
        return EBUFFERTURNCATION;
    }
    // [shrink the buffer] algorithm
    // in case the [list::capacity] is far away from the 
    // [list::position] and there are no valid
    // elements in-between; otherwise
    // if valid elements are found; obtain the 
    // index of the last valid element and use it
    if (buffer->capacity - buffer->position < (1024 << 2) + 1) {
        return PASS;
    }
    uint64_t last_index = buffer->position;
    uint64_t old_capacity = buffer->capacity;
    // calculate the last_index that reveals 
    // a valid item (i.e., data != NULL)
    // based on the linear buffer from
    // [list::position] and [list::capacity]
    for (uint64_t i = buffer->position; i < buffer->capacity; i++) {
        if (NULL == buffer->elements[i].data) {
            continue;
        }
        last_index = i;
    }

    status_code __code = buffer->operations->calculate_resize(buffer, last_index, 0x02, caller);
    if (PASS != __code) {
        return __code;
    }

    return buffer->operations->update_buffer_size(buffer, old_capacity, caller);;
}

status_code list_unsafe_leftshift_items_by_one(list *buffer, uint64_t start) {
    if (NULL == buffer || 
            NULL == buffer->elements) {
        return EUNDEFINEDBUFFER;
    }
    if (0 == buffer->capacity || buffer->capacity < buffer->position) {
        return EBUFFERTURNCATION;
    }

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

    // the algorithm defaults the 
    // iteration length to the list::capacity
    // in case the distance between the position count and 
    // the requested index is larger than
    // that of the buffer->capacity
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

    return PASS;
}

status_code list_unsafe_get_index_from_element(list *buffer, list_element *element, uint64_t *output) {
    if (NULL == buffer || 
            NULL == buffer->elements) {
        return EUNDEFINEDBUFFER;
    }
    if (0 == buffer->capacity || buffer->capacity < buffer->position) {
        return EBUFFERTURNCATION;
    }
    
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


