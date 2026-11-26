#include <electronetsoft/util/types.h>
#include <electronetsoft/util/maps/lookup_table_util.h>
#include <stddef.h>
#include <stdio.h>

status_code lookup_table_init(map *hashmap,
                              lookup_buffer buffer,
                              lookup_table_init_scheme scheme) {
    // preprocessor automata -- Validate the input params
    if (NULL == hashmap || NULL == hashmap->operations
            || NULL == hashmap->operations->insert) {
        return EUNDEFINEDBUFFER;
    }

    if (scheme != USE_INDICES && scheme != DEFAULT) {
        return EINCOMPATTYPE;
    }

    if (NULL == buffer.in.chars || NULL == buffer.pattern.chars || NULL == buffer.__indices ||
        NULL == buffer.__keys) {
        return EUNDEFINEDBUFFER;
    }

    if (buffer.in.length == 0 || buffer.pattern.length > buffer.in.length) {
        return EBUFFERTURNCATION;
    }

    status_code __code;
    size_t i = 0;
    for (size_t k = 0; i < buffer.in.length; i++, k += 2) {
        // construct key string
        buffer.__keys[k] = buffer.in.chars[i];
        buffer.__keys[k + 1] = '\0';
        // construct map element and data
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

        typed_pointer __t = (typed_pointer) {
            .type = TYPE_STR,
            .address.str = (buffer.__keys + k)
        };

        list_element __e = {
            .data = buffer.__indices + i,
            .metadata = __t,
            .type = ELEMENT_MAP_ITEM
        };

        map_element _m_e = {
            .key = __t,
            .value = __e
        };

        // insert map element
        __code = hashmap->operations->insert(hashmap, &_m_e);

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