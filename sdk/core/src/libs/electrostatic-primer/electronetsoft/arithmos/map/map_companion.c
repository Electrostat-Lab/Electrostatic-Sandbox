#include "electronetsoft/util/types.h"
#include <electronetsoft/arithmos/map/map_companion.h>
#include <stdio.h>

status_code init_adt_list(list **buffer, uint64_t limit) {
    if (NULL == buffer) {
        return EUNDEFINEDBUFFER;
    }

    *buffer = calloc(1, sizeof(list));
    if (NULL == buffer) {
        return EBUFFEROVERFLOW;
    }

    (*buffer)->type = CONTIGUOUS_BUFFER;
    (*buffer)->capacity = limit;

    // Preprocessing automata (pre-init phase) -- memory allocation
    list_operations *list_table = calloc(1, sizeof(list_operations));
    if (NULL == list_table) {
        return EBUFFEROVERFLOW;
    }

    list_element *elements = calloc((*buffer)->capacity, sizeof(list_element));
    if (NULL == elements) {
        return EBUFFEROVERFLOW;
    }

    // Processing and Post automata (initialization phase) -- list initialization

    return init_list(*buffer, elements, list_table, NULL);
}

status_code de_init_adt_list(list **__buffer) {
    if (NULL == __buffer || 
            NULL == *__buffer || 
                NULL == (*__buffer)->elements) {
        return EUNDEFINEDBUFFER;
    }
    if (0 == (*__buffer)->capacity) {
        return EBUFFERTURNCATION;
    }

    list *buffer = *__buffer;
    for (uint64_t i = 0; i < buffer->capacity; i++) {
        if (ELEMENT_LIST != buffer->elements[i].type) {
            continue;
        }
        list *__buffer = buffer->elements[i].data;
        free(__buffer->elements);
        __buffer->elements = NULL;
        free(__buffer->operations);    
        __buffer->operations = NULL;
        free(__buffer);
        __buffer = NULL;
    }

    free(buffer->operations);
    buffer->operations = NULL;
    free(buffer->elements);
    buffer->elements = NULL;
    free(buffer);
    buffer = NULL;

    return PASS;
}

status_code get_element_by_str_key(list *buffer,
                                    const char *__key0,
                                    key_element *__out) {
    typed_pointer __key1 = {0};
    status_code __code;

    for (uint64_t i = 0; i < buffer->position; i += 1) {
        __key1 = buffer->elements[i].metadata;
        if (strcmp(__key0, __key1.address.str) != 0) {
            __code = ENOELEMENT;
            continue;
        }

        __code = PASS;

        if (NULL != __out) {
            __out->index = i;
            __out->value = *(buffer->elements + i);
        }
        break;
    }
    return __code;
}

status_code get_element_by_long_key(list *buffer, uint64_t *key,
                                                  key_element *__out) {
    typed_pointer __key1 = {0};
    status_code __code;

    for (uint64_t i = 0; i < buffer->position; i += 1) {
        __key1 = buffer->elements[i].metadata;
        if (*__key1.address.id != *key) {
            __code = ENOELEMENT;
            continue;
        }
        __code = PASS;

        if (NULL != __out) {
            __out->index = i;
            __out->value = *(buffer->elements + i);
        }
        break;
    }
    return __code;
}

status_code get_element_by_typed_key(list *buffer, typed_pointer key,
                                                   key_element *out) {
    if (TYPE_STR == key.type) {
        return get_element_by_str_key(buffer,
                (const char *) key.address.str, out);
    } else if (TYPE_ID == key.type) {
        return get_element_by_long_key(buffer,
                                key.address.id, out);
    } else {
        return EINCOMPATTYPE;
    }
    
    return PASS;
}