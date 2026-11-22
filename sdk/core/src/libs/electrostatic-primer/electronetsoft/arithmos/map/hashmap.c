#include "electronetsoft/util/types.h"
#include <electronetsoft/arithmos/map/hashmap.h>
#include <electronetsoft/arithmos/map/collision_handler.h>
#include <electronetsoft/arithmos/map/map_companion.h>
#include <electronetsoft/arithmos/adt/list.h>
#include <electronetsoft/util/number/crypto.h>
#include <stdio.h>

static inline status_code hashmap_on_collision(list *buffer,
                                               uint64_t index,
                                               list_element *element) {

    status_code __code;

    // processing automata -- Allocate a secondary Linked Buffer
    //                     -- if already allocated; insert directly using the index
    if (ELEMENT_LIST == buffer->elements[index]->type) {
        list *__internal_buffer = buffer->elements[index]->data;
        // test if the list has the element with the exact key
        // add to the secondary buffer only if it is not present
        // if the element is not present in the buffer; add it
        if (ALLOW_DUPLICATES == buffer->col_scheme ||
                     ENOELEMENT == get_element_by_typed_key(__internal_buffer,
                           element->metadata, NULL)) {
            return __internal_buffer->function_table->
                            add(__internal_buffer, element);
        }
        return __internal_buffer->function_table->insert_overwrite(__internal_buffer, element, index);
    }

    if (ELEMENT_MAP_ITEM != buffer->elements[index]->type) {
        return EINCOMPATTYPE;
    }

    // fetch the item in the mainstream list
    list_element *item = NULL;
    __code = buffer->function_table->get(buffer, index, &item);
    if (PASS != __code) {
        return __code;
    }

    __code = no_duplicates_handler(buffer, item, element);
    if (EBUFFER_EXISTS == __code) {
        return __code;
    }

    __code = init_chain(buffer, item, element, index);

    // examples of dereferencing the data (comments for an illustrative example)
    // fprintf(stderr, "Test Data %s \n",
    //        *((const char **) ((list *) buffer->elements[index]->data)->elements[0]->data));
    // fprintf(stderr, "Test Data %s \n",
    //        *((const char **) ((list *) buffer->elements[index]->data)->elements[1]->data));

    return __code;
}

static inline status_code hashmap_rehash(map *hashmap, uint64_t limit) {
    if (NULL == hashmap || NULL == hashmap->adt || 0 == hashmap->adt->limit
                || 0 == limit) {
        return EUNDEFINEDBUFFER;
    }

    if (limit == hashmap->adt->limit) {
        return INVALID_OP;
    }

    list *buffer = hashmap->adt;
    list *_buffer = NULL;

    status_code __code = init_adt_list(&_buffer, limit);
    if (PASS != __code) {
        return __code;
    }

    _buffer->col_scheme = buffer->col_scheme;
    _buffer->function_table->on_collision = &hashmap_on_collision;

    uint64_t hashcode;
    hash_component hasher = {
          .hash = &hashcode,
          .user_key = ((uint64_t) INT16_MAX << 8) + 1
    };

    for (uint64_t i = 0; i < buffer->limit; i++) {
        if (NULL == buffer->elements[i]) {
            continue;
        }

        if (ELEMENT_LIST == buffer->elements[i]->type) {
            list *__buffer = buffer->elements[i]->data;
            if (NULL == __buffer->elements) {
                continue;
            }
            for (uint64_t j = 0; j < __buffer->limit; j++) {
                if (NULL == __buffer->elements[j]) {
                    continue;
                }
                hasher.key = __buffer->elements[j]->metadata;
                __code = crypto_hashkey_compress64(hasher, limit);
                if (PASS != __code) {
                    break;
                }

                __code = _buffer->function_table->insert(_buffer, __buffer->elements[j], *hasher.hash);
                if (PASS != __code) {
                    break;
                }
            }
            continue;
        }

        if (ELEMENT_MAP_ITEM == buffer->elements[i]->type) {
            hasher.key = buffer->elements[i]->metadata;
            __code = crypto_hashkey_compress64(hasher, limit);
            if (PASS != __code) {
                break;
            }

            // deep/physical copy of the data from the
            // old memory to the newly allocated buffer

            __code = _buffer->function_table->insert(_buffer, buffer->elements[i], *hasher.hash);
            if (PASS != __code) {
                break;
            }
        }
    }

    // post-processing automata -- re-invalidate the internal buffer
    __code = hashmap_deinit(hashmap, NULL);
    if (PASS != __code) {
        return __code;
    }
    hashmap->adt = _buffer;

    if (NULL != hashmap->processors &&
        NULL != hashmap->processors->on_rehash_dispatch) {
        hashmap->processors->on_rehash_dispatch(hashmap, buffer->elements);
    }

    return PASS;
}

static inline status_code hashmap_insert(map *hashmap,
                                         map_element *element) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt || NULL == element
                || 0 == hashmap->adt->limit) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == element->value || ELEMENT_MAP_ITEM != element->value->type) {
        return EINCOMPATTYPE;
    }

    // processing automata -- Hashing the key
    uint64_t hash_code = 0;
    hash_component hasher = {
         .key = element->key,
         .user_key = ((uint64_t) INT16_MAX << 8) + 1,
         .hash = &hash_code
    };
    status_code __code = crypto_hashkey_compress64(hasher, hashmap->adt->limit);
    if (PASS != __code) {
        return __code;
    }

    // processing automata -- Inserting the element using the hashcode
    //                     -- taking care of collision
    hashmap->adt->function_table->on_collision = &hashmap_on_collision;

    element->value->size = sizeof(map_element);
    element->value->type = ELEMENT_MAP_ITEM;
    element->value->metadata = element->key;
    __code = hashmap->adt->function_table->insert(hashmap->adt,
                                        element->value, hash_code);

    if (PASS != __code) {
        return __code;
    }

    hashmap->count += 1;

    float lambda_factor = 0.0f;
    __code = map_get_lambda_factor(hashmap, &lambda_factor);
    if (PASS != __code) {
        return __code;
    }
    if (lambda_factor >= 0.75f) {
        // appy resize and rehashing algorithm
        __code = hashmap_rehash(hashmap, hashmap->adt->limit << 4);
        if (PASS != __code) {
            return __code;
        }
    }
    // otherwise return with no errors!

    if (NULL != hashmap->processors &&
        NULL != hashmap->processors->on_insertion) {
        hashmap->processors->on_insertion(hashmap, element, hash_code);
    }

    return PASS;
}

static inline status_code hashmap_insert_all(map *hashmap,
                                             map_element **element) {
    return PASS;
}

static inline status_code hashmap_get_raw(map *hashmap,
                                          typed_pointer key,
                                          map_element *out) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
        0 == hashmap->adt->limit || NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    // processing automata -- Hashing the key
    uint64_t hash_code = 0;
    hash_component hasher = {
            .key = key,
            .user_key = ((uint64_t) INT16_MAX << 8) + 1,
            .hash = &hash_code
    };
    status_code __code = crypto_hashkey_compress64(hasher, hashmap->adt->limit);
    if (PASS != __code) {
        return __code;
    }

    list_element *element = NULL;
    __code = hashmap->adt->function_table->get(hashmap->adt, hash_code, &element);
    if (PASS != __code) {
        return __code;
    }

    out->key = key;
    out->value = element;

    return PASS;
}

static inline status_code hashmap_get(map *hashmap,
                                      typed_pointer key,
                                      map_element *out) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
            0 == hashmap->adt->limit || NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    // processing automata -- Hashing the key
    uint64_t hash_code = 0;
    hash_component hasher = {
            .key = key,
            .user_key = ((uint64_t) INT16_MAX << 8) + 1,
            .hash = &hash_code
    };
    status_code __code = crypto_hashkey_compress64(hasher, hashmap->adt->limit);
    if (PASS != __code) {
        return __code;
    }

    list_element *element = NULL;
    __code = hashmap->adt->function_table->get(hashmap->adt, hash_code, &element);
    if (PASS != __code) {
        return __code;
    }

    if (ELEMENT_LIST == element->type) {
        list *buffer = (list *) element->data;
        key_element __key_element = {
            .value = NULL,
            .index = 0
        };
        __code = get_element_by_typed_key(buffer, key, &(__key_element));

        if (PASS != __code) {
            return __code;
        }
        out->value = __key_element.value;
        return PASS;
    }

    out->key = key;
    out->value = element;

    return PASS;
}

static inline status_code hashmap_contains(map *hashmap, typed_pointer key) {
    map_element out = {
         .value = NULL,
         .key = key
    };

    status_code __code = hashmap_get(hashmap, key, &out);
    if (__code != PASS || NULL == out.value) {
        return __code;
    }
    return PASS;
}

static inline status_code __hashmap_remove(map *hashmap, hash_component hasher) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
            NULL == hasher.hash ||
                0 == hashmap->adt->limit) {
        return EUNDEFINEDBUFFER;
    }
    // processing automata -- Hashing the key

    status_code __code;

    if (ELEMENT_LIST == hashmap->adt->elements[*(hasher.hash)]->type) {
        list *buffer = hashmap->adt->elements[*(hasher.hash)]->data;
        if (buffer->position == 0) {
            free(buffer->function_table);
            free(buffer->elements);
            free(buffer);
            free(hashmap->adt->elements[*(hasher.hash)]);
            return PASS;
        }
        key_element __key_element = {
                .value = NULL,
                .index = 0
        };
        __code = get_element_by_typed_key(buffer,
                                    hasher.key,
                                    &__key_element);
        if (PASS != __code) {
            return __code;
        }
        __code = buffer->function_table->remove_by_index(buffer, __key_element.index);
        if (PASS != __code) {
            return __code;
        }

        if (NULL != hashmap->processors &&
            NULL != hashmap->processors->on_removal) {
            hashmap->processors->on_removal(hashmap, buffer, *(hasher.hash));
        }

        return PASS;
    }

    hashmap->adt->elements[*(hasher.hash)] = NULL;
    hashmap->count -= 1;

    if (NULL != hashmap->processors &&
            NULL != hashmap->processors->on_removal) {
        hashmap->processors->on_removal(hashmap, hashmap->adt, *(hasher.hash));
    }

    return PASS;
}

static inline status_code hashmap_remove(map *hashmap, typed_pointer key) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
         0 == hashmap->adt->limit) {
        return EUNDEFINEDBUFFER;
    }
    // processing automata -- Hashing the key
    uint64_t hash_code = 0;
    hash_component hasher = {
            .key = key,
            .user_key = ((uint64_t) INT16_MAX << 8) + 1,
            .hash = &hash_code
    };
    status_code __code = crypto_hashkey_compress64(hasher, hashmap->adt->limit);
    if (PASS != __code) {
        return __code;
    }

    return __hashmap_remove(hashmap, hasher);
}

static inline status_code hashmap_remove_all(map *hashmap,
                                             typed_pointer **keys) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
           0 == hashmap->adt->limit || NULL == keys || NULL == keys[0]) {
        return EUNDEFINEDBUFFER;
    }

    uint64_t __hash_code = 0;
    hash_component __hasher = {
            .key = NULL,
            .user_key = ((uint64_t) INT16_MAX << 8) + 1,
            .hash = &__hash_code
    };
    status_code __code;

    for (uint64_t i = 0; NULL != keys[i]; i++) {
        __hasher.key = *(keys[i]);
        __code = crypto_hashkey_compress64(__hasher, hashmap->adt->limit);
        if (PASS != __code) {
            return __code;
        }

        if (NULL == hashmap->adt->elements[__hash_code] ||
            (ELEMENT_MAP_ITEM != hashmap->adt->elements[__hash_code]->type) &&
            (ELEMENT_LIST != hashmap->adt->elements[__hash_code]->type)) {
            continue;
        }

        __code = __hashmap_remove(hashmap, __hasher);
        if (PASS != __code) {
            return __code;
        }
    }

    return PASS;
}

status_code hashmap_contains_all(map *hashmap,
                                 typed_pointer **keys) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt || NULL == keys ||
        0 == hashmap->adt->limit || NULL == keys[0]) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;

    for (uint64_t i = 0; NULL != keys[i]; i++) {
        __code = hashmap_contains(hashmap, *(keys[i]));
        if (PASS != __code) {
            return __code;
        }
    }

    return PASS;
}

status_code hashmap_iterator(map *hashmap,
                             status_code (*callback)(map *, map_element *)) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
        NULL == hashmap->adt->elements ||
        0 == hashmap->adt->limit || NULL == callback) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;
    list *buffer = hashmap->adt;
    map_element element = {
         .value = NULL,
         .key = NULL
    };
    for (uint64_t i = 0; i < hashmap->adt->limit; i++) {
        if (NULL == buffer->elements[i]) {
            continue;
        }
        if (ELEMENT_LIST == buffer->elements[i]->type) {
            list *__buffer = buffer->elements[i]->data;
            if (NULL == __buffer->elements) {
                continue;
            }
            for (uint64_t j = 0; j < __buffer->limit; j++) {
                if (NULL == __buffer->elements[j]) {
                    continue;
                }
                element.value = __buffer->elements[j];
                element.key = __buffer->elements[j]->metadata;
                __code = callback(hashmap, &element);
                if (PASS != __code) {
                    return __code;
                }
            }
            continue;
        }
        element.value = buffer->elements[i];
        element.key = buffer->elements[i]->metadata;
        __code = callback(hashmap, &element);
        if (PASS != __code) {
            return __code;
        }
    }

    return PASS;
}

status_code map_get_lambda_factor(map *hashmap, float *lambda) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
        0 == hashmap->adt->limit) {
        return EUNDEFINEDBUFFER;
    }

    *lambda = (float) hashmap->count / (float) hashmap->adt->limit;

    return PASS;
}

status_code hashmap_init_limit(map *hashmap, uint64_t limit, map_function_table *table,
                               api_lifecycle *lifecycle) {
    if (NULL == hashmap || NULL == table) {
        return EUNDEFINEDBUFFER;
    }

    // preprocessing automata -- ADT allocation and initialization
    list *buffer = NULL;
    status_code __code = init_adt_list(&buffer, limit);

    if (PASS != __code) {
        return __code;
    }

    // processing automata -- HASHMap allocation and initialization
    hashmap->adt = buffer;
    buffer->col_scheme = hashmap->col_scheme;
    hashmap->type = MAP_TYPE_HASHMAP;
    hashmap->function_table = table;

    table->insert = &hashmap_insert;
    table->insert_all = &hashmap_insert_all;
    table->rehash = &hashmap_rehash;
    table->iterator = &hashmap_iterator;
    table->contains = &hashmap_contains;
    table->contains_all = &hashmap_contains_all;
    table->get = &hashmap_get;
    table->get_raw = &hashmap_get_raw;
    table->remove = &hashmap_remove;
    table->remove_all = &hashmap_remove_all;

    if (NULL != hashmap->processors &&
        NULL != hashmap->processors->on_initialization) {
        hashmap->processors->on_initialization(hashmap);
    }

    return PASS;
}

status_code hashmap_init(map *hashmap, map_function_table *table,
                         api_lifecycle *lifecycle) {
    return hashmap_init_limit(hashmap, (1024 << 2) + 1, table, lifecycle);
}

status_code hashmap_deinit(map *hashmap,
                           api_lifecycle *lifecycle) {
    if (NULL == hashmap || NULL == hashmap->adt) {
        if (NULL != lifecycle && NULL != lifecycle->on_operation_failed) {
            lifecycle->on_operation_failed(&hashmap_deinit, hashmap, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    if (NULL != hashmap->processors &&
        NULL != hashmap->processors->on_deinitialization) {
        hashmap->processors->on_deinitialization(hashmap);
    }

    // fetch mainstream buffer
    status_code __code = de_init_adt_list(&(hashmap->adt));
    if (PASS != __code) {
        return __code;
    }

    if (NULL != lifecycle && NULL != lifecycle->on_operation_succeeded) {
        lifecycle->on_operation_succeeded(&hashmap_deinit, hashmap);
    }

    return PASS;
}
