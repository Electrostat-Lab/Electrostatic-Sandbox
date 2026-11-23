#include <electronetsoft/util/maps/lookup_table_util.h>

status_code lookup_table_init(map *hashmap,
                              lookup_buffer buffer,
                              lookup_table_init_scheme scheme) {
    // preprocessor automata -- Validate the input params
    if (NULL == hashmap || NULL == hashmap->function_table
            || NULL == hashmap->function_table->insert) {
        return EUNDEFINEDBUFFER;
    }

    if (scheme != USE_INDICES && scheme != DEFAULT) {
        return EINCOMPATTYPE;
    }

    if (NULL == buffer.in.chars || NULL == buffer.pattern.chars || NULL == buffer.__indices ||
        NULL == buffer.__keys || NULL == buffer.__elements ||
            NULL == buffer.__map_elements) {
        return EUNDEFINEDBUFFER;
    }

    if (buffer.in.length == 0 || buffer.pattern.length > buffer.in.length) {
        return EBUFFERTURNCATION;
    }

    status_code __code;
    for (size_t i = 0, k = 0; i < buffer.in.length; i++, k += 2) {
        // construct key string
        buffer.__keys[k] = buffer.in.chars[i];
        buffer.__keys[k + 1] = '\0';
        // construct map element and data
        buffer.__elements[i].type = ELEMENT_MAP_ITEM;
        if (USE_INDICES == scheme) {
            // preprocessor excluding algorithm
            if (NULL != buffer.processors && NULL != buffer.processors->lookup_preprocessor) {
                __code = buffer.processors->lookup_preprocessor(buffer.in, buffer.pattern, i);
                if (PASS != __code) {
                    continue;
                }
            }
            buffer.__indices[i] = i;
        } else {
            buffer.__indices[i] = -1;
        }
        buffer.__elements[i].data = buffer.__indices + i;

        // construct key pointer
        buffer.__map_elements[i].key = (typed_pointer) {
            .type = TYPE_STR,
            .address.str = (buffer.__keys + k)
        };
        // construct map element
        buffer.__map_elements[i].value = buffer.__elements + i;

        // insert map element
        __code = hashmap->function_table->insert(hashmap, buffer.__map_elements + i);

        if (PASS != __code && EBUFFER_EXISTS != __code) {
            return __code;
        }

        // postprocessing
        if (NULL != buffer.processors && NULL != buffer.processors->lookup_postprocessor) {
            __code = buffer.processors->lookup_postprocessor(buffer.in, buffer.pattern, i);
            if (PASS != __code) {
                return __code;
            }
        }
    }
    return PASS;
}