#include <electrostatic/electronetsoft/util/utilities.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/adt/list.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/list/linked_buffer.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static inline status_code get_chain(list *buffer, linked_buffer **chain) {
    // preprocessing -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(buffer->elements[0]) == NULL
          || rvalue((*buffer->elements)->data) == NULL || rvalue(chain) == NULL) {
        // log memory failure
        // use printf temporarily
        fprintf(stdout, "Segment Dereferencing has failed!\n");
        return EUNDEFINEDBUFFER;
    }
    // processing -- LOAD instruction for the working address
    *chain = (*buffer->elements)->data;
    return PASS;
}

static inline status_code set_previous_element(linked_buffer *buffer, list_element *element,
                                               list_element *prev) {
    // pre-processing automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(element) == NULL
            || rvalue(element->metadata) == NULL) {
        // log memory failure
        // use printf temporarily
        fprintf(stdout, "Segment Dereferencing has failed!\n");
        return EUNDEFINEDBUFFER;
    }
    // preprocessing automata -- Input Validation for type safety
    if (DOUBLE_ENDED != buffer->type) {
        fprintf(stdout, "Type Safety checks have failed!\n");
        return EINCOMPATTYPE;
    }

    // processing -- LOAD instruction and STORE for the working address
    ((list_element **) element->metadata)[0] = prev;
    return PASS;
}

static inline status_code set_next_element(linked_buffer *buffer, list_element *element,
                                           list_element *next) {
    // preprocessing automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(element) == NULL
            || rvalue(element->metadata) == NULL) {
        // log memory failure
        // use printf temporarily
        fprintf(stdout, "Segment Dereferencing has failed!\n");
        return EUNDEFINEDBUFFER;
    }
    // preprocessing automata -- Input Validation for type safety
    if (!(SINGLE_ENDED == buffer->type || DOUBLE_ENDED == buffer->type)) {
        fprintf(stdout, "Type Safety checks have failed!\n");
        return EINCOMPATTYPE;
    }
    // processing automata -- LOAD instruction for the working address
    switch (buffer->type) {
        case DOUBLE_ENDED: {
            // preprocessing automata -- Input Validation
            if (rvalue(element->metadata + 1) == NULL) {
                return EUNDEFINEDBUFFER;
            }
            ((list_element **) element->metadata)[1] = next;
            return PASS;
        }
        // add other types here in a switch...return statement that finishes the processing automata!
        default:
            element->metadata = next;
            return PASS;
    }
}

static inline status_code get_previous_element(linked_buffer *buffer, list_element *element,
                                               list_element **prev) {
    // pre-processing automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(element) == NULL
            || rvalue(element->metadata) == NULL || rvalue(prev) == NULL) {
        // log memory failure
        // use printf temporarily
        fprintf(stdout, "Segment Dereferencing has failed!\n");
        return EUNDEFINEDBUFFER;
    }
    // preprocessing automata -- Input Validation for type safety
    if (DOUBLE_ENDED != buffer->type) {
        fprintf(stdout, "Type Safety checks have failed!\n");
        return EINCOMPATTYPE;
    }
    // processing -- LOAD instruction for the working address
    *prev = ((list_element **) element->metadata)[0];
    // post-processing automata -- Output Validation
    if (rvalue(*prev) == NULL) {
        fprintf(stdout, "Segment Dereferencing has failed!\n");
        return EUNDEFINEDBUFFER;
    }
    // post-processing automata -- User code.
    return PASS;
}

static inline status_code get_next_element(linked_buffer *buffer, list_element *element, list_element **next) {
    // preprocessing automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(element) == NULL
            || rvalue(element->metadata) == NULL || rvalue(next) == NULL) {
        // log memory failure
        // use printf temporarily
        fprintf(stdout, "Segment Dereferencing has failed!\n");
        return EUNDEFINEDBUFFER;
    }
    // preprocessing automata -- Input Validation for type safety
    if (!(SINGLE_ENDED == buffer->type || DOUBLE_ENDED == buffer->type)) {
        fprintf(stdout, "Type Safety checks have failed!\n");
        return EINCOMPATTYPE;
    }
    // processing automata -- LOAD instruction for the working address
    switch (buffer->type) {
        case DOUBLE_ENDED:
            // preprocessing automata -- Input Validation
            if (rvalue(element->metadata + 1) == NULL) {
                return EUNDEFINEDBUFFER;
            }

            // processing automata -- LOAD&STORE instruction
            *next = ((list_element **) element->metadata)[1];
            break;
        default:
            // processing automata -- LOAD&STORE instruction
            *next = (list_element *) element->metadata;
    }
    // post-processing automata -- Output Validation
    if (rvalue(next) == NULL) {
        fprintf(stdout, "Segment Dereferencing has failed!\n");
        return EUNDEFINEDBUFFER;
    }
    return PASS;
}

static inline status_code linked_buffer_add(list *buffer, list_element *element) {
    // preprocessing automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(element) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    // preprocessing automata -- Type-safety Checks
    if (LINKED_BUFFER != buffer->type) {
        return EINCOMPATTYPE;
    }
    // preprocessing automata -- Buffer limit check and resize
    if (0 != buffer->limit && buffer->length >= buffer->limit) {
        // run a stretching algorithm
        // the stretching algorithm
        if (rvalue(buffer->function_table) != NULL &&
                rvalue(buffer->function_table->resize) != NULL) {
            buffer->function_table->resize(buffer, 0x02);
        }
    }

    // pre-processing -- chain retrieval
    // assign the next node for single and double ended linked buffers
    linked_buffer *chain = NULL;
    status_code _code0 = get_chain(buffer, &chain);
    // premature return of failure
    if (PASS != _code0) {
        return _code0;
    }

    // Processing Automata -- Conditional Automata
    //              (Single-Ended and Double-Ended Linked Buffers)
    if (DOUBLE_ENDED == chain->type) {
        // Double-Ended Linked Buffer
        // processing automata -- Update the second link (previous node)
        status_code _code1 =
                set_previous_element(chain, element, chain->end_address);
        if (PASS != _code1) {
            return _code1;
        }
    }
    status_code _code2 = set_next_element(chain, chain->end_address, element);
    // premature return for failure
    if (PASS != _code2) {
        return _code2;
    }

    status_code _code3 = set_next_element(chain, element, NULL);
    // premature return for failure
    if (PASS != _code3) {
        return _code3;
    }

    // post-processing automata -- Update Start-Address and End-Address
    chain->end_address = element;
    // post-processing automata -- Update the Start-Address of the buffer for the first time
    if (rvalue(chain->start_address) == NULL) {
        chain->start_address = chain->end_address;
    }

    // post-processing automata -- increment the length counter
    buffer->length += 1;
    return PASS;
}

static inline status_code linked_buffer_add_all(list *buffer, list_element **elements) {
    // preprocessing automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(elements) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    // pre-processing automata -- Type safety checks
    if (LINKED_BUFFER != buffer->type) {
        return EINCOMPATTYPE;
    }

    // processing -- automata -- Add all elements
    status_code __code;
    for (uint64_t i = 0; rvalue(elements[i]) != NULL; i++) {
        __code &= linked_buffer_add(buffer, elements[i]);
    }

    return __code;
}

static inline status_code linked_buffer_index_of(list *buffer, list_element *element, uint64_t *index) {
    // preprocessing automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(element) == NULL
            || rvalue(index) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    // pre-processing automata -- Type safety checks
    if (LINKED_BUFFER != buffer->type) {
        return EINCOMPATTYPE;
    }
    // pre-processing -- chain retrieval
    // assign the next node for single and double ended linked buffers
    linked_buffer *chain = NULL;
    status_code _code = get_chain(buffer, &chain);
    if (PASS != _code) {
        return _code;
    }

    // processing automata -- Iterative Automata
    //                        (i.e., a For-All Formulation)
    list_element *_element = chain->start_address;

    uint8_t is_found = 0;
    uint64_t counter = 0;
    status_code __code = PASS;
    // initialize the index buffer with zero
    *index = 0;

    // processing automata -- Iterative Automata
    while (rvalue(_element) != NULL && PASS == __code) {
        if (rvalue(_element) == element) {
            *index = counter;
            is_found = 1;
            break;
        }
        // processing automata -- transition to the next state
        __code = get_next_element(chain, _element, &_element);
        // post-processing automata -- increment counter state
        counter++;
    }

    // post-processing automata -- Output Validation
    if (!is_found) {
        return ENOELEMENT;
    }

    return PASS;
}

static inline status_code linked_buffer_get(list *buffer, uint64_t index, list_element **element) {
    // pre-processing automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(element) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // pre-processing automata -- Type safety checks
    if (LINKED_BUFFER != buffer->type) {
        return EINCOMPATTYPE;
    }

    // pre-processing -- chain retrieval
    // assign the next node for single and double ended linked buffers
    // 1) Automatically allocate an address buffer.
    linked_buffer *chain = NULL;
    // 2) Pass the address buffer with address to the function.
    status_code _code = get_chain(buffer, &chain);
    if (PASS != _code) {
        return _code;
    }
    // processing automata -- Iterative Automata
    //                        (i.e., a For-All Formulation)
    *element = chain->start_address;
    status_code __code = PASS;
    uint64_t counter = 0;

    while (rvalue(*element) != NULL && __code == PASS
                                   && counter <= index) {
        // processing automata -- transition to the next state
        __code = get_next_element(chain, *element, element);
        // post-processing automata -- increment counter state
        counter++;
    }

    return __code;
}

static inline status_code linked_buffer_remove_by_element(list *buffer, list_element *target) {
    // pre-processing automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(target) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // pre-processing automata -- Type safety checks
    if (LINKED_BUFFER != buffer->type) {
        return EINCOMPATTYPE;
    }
    // pre-processing automata -- Get the chain pointer
    // assign the next node for single and double ended linked buffers
    linked_buffer *chain = NULL;
    status_code _code = get_chain(buffer, &chain);
    if (PASS != _code) {
        return _code;
    }

    // pre-processing automata -- Test the element presence (Optional!)
    // use {contains} algorithm!

    // pre-processing automata -- Initializing Local Variables
    // status codes are ignored; because these states are never-fail states!
    // so, checking status codes will be redundant cycles.
    list_element *prev_element = NULL;
    status_code __code = get_previous_element(chain, target, &prev_element);
    // terminate if the previous element is not present
    if (PASS != __code) {
        return __code;
    }

    list_element *next_element = NULL;
    get_next_element(chain, target, &next_element);

    // processing automata -- Jump one item
    set_next_element(chain, prev_element, next_element);
    if (DOUBLE_ENDED == chain->type) {
        // processing automata -- Update the second link (previous node)
        set_previous_element(chain, next_element, prev_element);
    }

    // post-processing automata -- decrement the length counter
    buffer->length -= 1;
    return PASS;
}

static inline status_code linked_buffer_contains(list *buffer, list_element *element) {
    // pre-processing automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(element) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // pre-processing automata -- Type safety checks
    if (LINKED_BUFFER != buffer->type) {
        return EINCOMPATTYPE;
    }

    // pre-processing -- chain retrieval
    // assign the next node for single and double ended linked buffers
    linked_buffer *chain = NULL;
    status_code _code = get_chain(buffer, &chain);
    // premature termination with an exception.
    if (PASS != _code) {
        return _code;
    }

    // processing automata -- Iterative Automata
    //                        (i.e., a For-All Formulation)
    list_element *current = chain->start_address;
    status_code __code = ENOELEMENT;
    uint8_t is_found = 0;

    while (rvalue(current) != NULL &&
            rvalue(current) != element) {
        // processing automata -- transition to the next state
        // loop until hitting the last item at which value of address buffer is NULL
        // determining the null-terminated buffer at which the status code will be EUNDEFINEDBUFFER
        __code = get_next_element(chain, current, &current);
    }

    // post-processing automata -- Validate the output and execute lifecycle functions

    return __code;
}

static inline status_code linked_buffer_remove_by_index(list *buffer, uint64_t index) {
    // pre-processing automata -- Input Validation
    if (rvalue(buffer) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // pre-processing automata -- Type safety checks
    if (LINKED_BUFFER != buffer->type) {
        return EINCOMPATTYPE;
    }
    // pre-processing automata -- Get by index
    list_element *target = NULL;
    status_code _code = linked_buffer_get(buffer, index, &target);
    // premature termination
    if (PASS != _code) {
        return _code;
    }

    // processing automata -- Removal algorithm
    return linked_buffer_remove_by_element(buffer, target);
}

static inline status_code linked_buffer_iterator(list *buffer, list_info info,
                                             void (*callback)(list *, list_element *)) {
    // pre-processor automata -- Input Validation
    if (rvalue(buffer) == NULL || rvalue(callback) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // pre-processing automata -- Type safety checks
    if (LINKED_BUFFER != buffer->type) {
        return EINCOMPATTYPE;
    }
    // pre-processing -- chain retrieval
    // assign the next node for single and double ended linked buffers
    linked_buffer *chain = NULL;
    status_code _code = get_chain(buffer, &chain);
    if (PASS != _code) {
        return _code;
    }
    // processing automata -- Iterative Automata
    //                        (i.e., a For-All Formulation)
    status_code __code = PASS;
    for (list_element *element = chain->start_address;
            (rvalue(element) != NULL &&
                    rvalue(element) != chain->end_address); // compatible with non-null terminated lists
                        __code = get_next_element(chain, element, &element)) {
        callback(buffer, element);
    }
    return PASS;
}

status_code init_linked_buffer(list *list, list_element **elements, list_function_table *table, api_lifecycle *lifecycle) {
    if (rvalue(list) == NULL || rvalue(elements) == NULL || rvalue(table) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    table->lifecycle = lifecycle;
    table->iterator = &linked_buffer_iterator;
    table->add = &linked_buffer_add;
    table->add_all = &linked_buffer_add_all;
    table->remove_by_element = &linked_buffer_remove_by_element;
    table->remove_by_index = &linked_buffer_remove_by_index;
    table->remove_all = NULL;
    table->retains_all = NULL;
    table->contains = &linked_buffer_contains;
    table->contains_all = NULL;
    table->resize = NULL;
    table->get = &linked_buffer_get;
    table->index_of = &linked_buffer_index_of;
    table->get_start_address = NULL;
    table->get_end_address = NULL;

    list->function_table = table;
    list->elements = elements;
    memset(list->elements, 0, list->length);

    list->length = 0;
    list->limit = 8 << 2;

    linked_buffer *chain = NULL;
    status_code __code = get_chain(list, &chain);
    if (PASS != __code) {
        return __code;
    }

    list->elements_memory = (memory_partition) {
        .start_address = chain->start_address,
        .end_address = chain->end_address // this is dynamic and it needs to be updated on each WRITE operation!
    };

    return PASS;
}