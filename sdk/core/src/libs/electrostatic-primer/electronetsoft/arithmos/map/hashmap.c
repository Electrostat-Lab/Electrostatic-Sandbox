#include "electronetsoft/util/types.h"
#include <electronetsoft/arithmos/map/hashmap.h>
#include <electronetsoft/arithmos/map/collision_handler.h>
#include <electronetsoft/arithmos/map/map_companion.h>
#include <electronetsoft/arithmos/adt/list.h>
#include <electronetsoft/util/number/crypto.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static inline status_code hashmap_on_collision(list *buffer,
                                               uint64_t index,
                                               list_element *element) {

    status_code __code;

    // processing automata -- Allocate a secondary Linked Buffer
    //                     -- if already allocated; insert directly using the index
    if (ELEMENT_LIST == buffer->elements[index].type) {
        list *internal_buffer = buffer->elements[index].data;
        key_element __key = {0};
        // test if the list has the element with the exact key
        // add to the secondary buffer only if it is not present
        // if the element is not present in the buffer; add it
        if (ALLOW_DUPLICATES == buffer->col_scheme ||
                     ENOELEMENT == get_element_by_typed_key(internal_buffer,
                           element->metadata, &__key)) {
            return internal_buffer->operations->
                            add(internal_buffer, element);
        }
        return internal_buffer->operations->insert_overwrite(internal_buffer, element, __key.index);
    }

    if (ELEMENT_MAP_ITEM != buffer->elements[index].type) {
        return EINCOMPATTYPE;
    }

    // fetch the item in the mainstream list
    list_element item = {0};
    __code = buffer->operations->get(buffer, index, &item);
    if (PASS != __code) {
        return __code;
    }

    __code = no_duplicates_handler(buffer, &item, element);
    if (EBUFFER_EXISTS == __code) {
        return __code;
    }

    __code = init_chain(buffer, &item, element, index);

    // examples of dereferencing the data (comments for an illustrative example)
    // fprintf(stderr, "Test Data %s \n",
    //        *((const char **) ((list *) buffer->elements[index]->data)->elements[0]->data));
    // fprintf(stderr, "Test Data %s \n",
    //        *((const char **) ((list *) buffer->elements[index]->data)->elements[1]->data));

    return __code;
}

static inline status_code hashmap_rehash(map *hashmap, uint64_t capacity) {
    if (NULL == hashmap || NULL == hashmap->adt || 0 == hashmap->adt->capacity
                || 0 == capacity) {
        return EUNDEFINEDBUFFER;
    }

    if (capacity == hashmap->adt->capacity) {
        return INVALID_OP;
    }

    list *buffer = hashmap->adt;
    list *_buffer = NULL;

    status_code __code = init_adt_list(&_buffer, capacity);
    if (PASS != __code) {
        return __code;
    }

    _buffer->col_scheme = buffer->col_scheme;
    _buffer->operations->on_collision = &hashmap_on_collision;

    uint64_t hashcode;
    hash_component hasher = {
          .hash = &hashcode,
          .user_key = ((uint64_t) INT16_MAX << 8) + 1
    };

    for (uint64_t i = 0; i < buffer->capacity; i++) {
        if (ELEMENT_LIST == buffer->elements[i].type) {
            list *__buffer = buffer->elements[i].data;
            if (NULL == __buffer->elements) {
                continue;
            }
            // use position to track the elements
            // not the capactiy; as the inner chains use
            // contiguous_buffer_add which respects the
            // position
            for (uint64_t j = 0; j < __buffer->position; j++) {
                // rehash the key
                hasher.key = __buffer->elements[j].metadata;
                __code = crypto_hashkey_compress64(hasher, capacity);
                if (PASS != __code) {
                    break;
                }
                
                // reinsert it with the new hash into the new buffer handling the collision again!
                __code = _buffer->operations->insert(_buffer, (__buffer->elements + j), *hasher.hash);
                if (PASS != __code) {
                    break;
                }
            }
            continue;
        }

        if (ELEMENT_MAP_ITEM == buffer->elements[i].type) {
            // rehash the key
            hasher.key = buffer->elements[i].metadata;
            __code = crypto_hashkey_compress64(hasher, capacity);
            if (PASS != __code) {
                break;
            }

            // deep/physical copy of the data from the
            // old memory to the newly allocated buffer
            // reinsert it
            __code = _buffer->operations->insert(_buffer, (buffer->elements + i), *hasher.hash);
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
                || 0 == hashmap->adt->capacity) {
        return EUNDEFINEDBUFFER;
    }

    if (ELEMENT_MAP_ITEM != element->value.type) {
        return EINCOMPATTYPE;
    }

    // processing automata -- Hashing the key
    uint64_t hash_code = 0;
    hash_component hasher = {
         .key = element->key,
         .user_key = ((uint64_t) INT16_MAX << 8) + 1,
         .hash = &hash_code
    };
    status_code __code = crypto_hashkey_compress64(hasher, hashmap->adt->capacity);
    if (PASS != __code) {
        return __code;
    }

    // processing automata -- Inserting the element using the hashcode
    //                     -- taking care of collision
    hashmap->adt->operations->on_collision = &hashmap_on_collision;

    element->value.size = sizeof(map_element);
    element->value.type = ELEMENT_MAP_ITEM;
    element->value.metadata = element->key;
    __code = hashmap->adt->operations->insert(hashmap->adt,
                                        &(element->value), hash_code);

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
        __code = hashmap_rehash(hashmap, hashmap->adt->capacity << 4);
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
                                             map_element *elements, 
                                             uint64_t n_elements) {
    return PASS;
}

static inline status_code hashmap_get_raw(map *hashmap,
                                          typed_pointer key,
                                          map_element *out) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
        0 == hashmap->adt->capacity || NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    // processing automata -- Hashing the key
    uint64_t hash_code = 0;
    hash_component hasher = {
            .key = key,
            .user_key = ((uint64_t) INT16_MAX << 8) + 1,
            .hash = &hash_code
    };
    status_code __code = crypto_hashkey_compress64(hasher, hashmap->adt->capacity);
    if (PASS != __code) {
        return __code;
    }

    list_element element = {0};
    __code = hashmap->adt->operations->get(hashmap->adt, hash_code, &element);
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
            0 == hashmap->adt->capacity || NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    // processing automata -- Hashing the key
    uint64_t hash_code = 0;
    hash_component hasher = {
            .key = key,
            .user_key = ((uint64_t) INT16_MAX << 8) + 1,
            .hash = &hash_code
    };
    status_code __code = crypto_hashkey_compress64(hasher, hashmap->adt->capacity);
    if (PASS != __code) {
        return __code;
    }

    list_element element = {0};
    __code = hashmap->adt->operations->get(hashmap->adt, hash_code, &element);
    if (PASS != __code) {
        return __code;
    }

    if (ELEMENT_LIST == element.type) {
        list *buffer = (list *) element.data;
        key_element __key_element = {
            .value = {0},
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
         .value = {0},
         .key = key
    };
    return hashmap_get(hashmap, key, &out);
}

static inline status_code __hashmap_remove(map *hashmap, hash_component hasher) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
            NULL == hasher.hash ||
                0 == hashmap->adt->capacity) {
        return EUNDEFINEDBUFFER;
    }
    // processing automata -- Hashing the key

    status_code __code;
    list_element *buffer_element = hashmap->adt->elements + *(hasher.hash);

    if (ELEMENT_LIST == buffer_element->type) {
        list *buffer = buffer_element->data;
        if (0 == buffer->position) {
            free(buffer->operations);
            free(buffer->elements);
            free(buffer);
            
            goto RESET;
        }
        key_element __key_element = {
                .value = {0},
                .index = 0
        };
        __code = get_element_by_typed_key(buffer,
                                    hasher.key,
                                    &__key_element);
        if (PASS != __code) {
            return __code;
        }

        __code = buffer->operations->remove_by_index(buffer, __key_element.index);
        if (PASS != __code) {
            return __code;
        }

        goto POSTPROCESSOR;
    }

    RESET: {
        *buffer_element = (list_element) {0};
        hashmap->count -= 1;
    }

    POSTPROCESSOR: {
        if (NULL != hashmap->processors &&
                NULL != hashmap->processors->on_removal) {
            hashmap->processors->on_removal(hashmap, hashmap->adt, *(hasher.hash));
        }
    }

    return PASS;
}

static inline status_code hashmap_remove(map *hashmap, typed_pointer key) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
         0 == hashmap->adt->capacity) {
        return EUNDEFINEDBUFFER;
    }
    // processing automata -- Hashing the key
    uint64_t hash_code = 0;
    hash_component hasher = {
            .key = key,
            .user_key = ((uint64_t) INT16_MAX << 8) + 1,
            .hash = &hash_code
    };
    status_code __code = crypto_hashkey_compress64(hasher, hashmap->adt->capacity);
    if (PASS != __code) {
        return __code;
    }

    return __hashmap_remove(hashmap, hasher);
}

static inline status_code hashmap_remove_all(map *hashmap,
                                             typed_pointer *keys, uint64_t n_keys) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt ||
           0 == hashmap->adt->capacity || NULL == keys) {
        return EUNDEFINEDBUFFER;
    }

    if (0 == n_keys) {
        return EBUFFERTURNCATION;
    }

    uint64_t __hash_code = 0;
    hash_component __hasher = {
            .key = {0},
            .user_key = ((uint64_t) INT16_MAX << 8) + 1,
            .hash = &__hash_code
    };
    status_code __code;

    for (uint64_t i = 0; i < n_keys; i++) {
        __hasher.key = keys[i];
        __code = crypto_hashkey_compress64(__hasher, hashmap->adt->capacity);
        if (PASS != __code) {
            return __code;
        }

        if (0 == &(hashmap->adt->elements[__hash_code].metadata.address) ||
            (ELEMENT_MAP_ITEM != hashmap->adt->elements[__hash_code].type) &&
            (ELEMENT_LIST != hashmap->adt->elements[__hash_code].type)) {
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
                                 typed_pointer *keys, uint64_t n_keys) {
    // preprocessing automata -- Input Validation
    if (NULL == hashmap || NULL == hashmap->adt || NULL == keys ||
        0 == hashmap->adt->capacity || 0 == n_keys) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;

    for (uint64_t i = 0; i < n_keys; i++) {
        __code = hashmap_contains(hashmap, keys[i]);
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
        0 == hashmap->adt->capacity || NULL == callback) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;
    list *buffer = hashmap->adt;
    map_element element = {
         .value = NULL,
         .key = NULL
    };
    for (uint64_t i = 0; i < hashmap->adt->capacity; i++) {
        if (ELEMENT_LIST != buffer->elements[i].type && 
                ELEMENT_MAP_ITEM != buffer->elements[i].type) {
            continue;
        }
        if (ELEMENT_LIST == buffer->elements[i].type) {
            list *__buffer = buffer->elements[i].data;
            if (NULL == __buffer->elements) {
                continue;
            }
            for (uint64_t j = 0; j < __buffer->position; j++) {
                element.value = __buffer->elements[j];
                element.key = __buffer->elements[j].metadata;
                __code = callback(hashmap, &element);
                if (PASS != __code) {
                    return __code;
                }
            }
            continue;
        }
        element.value = buffer->elements[i];
        element.key = buffer->elements[i].metadata;
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
        0 == hashmap->adt->capacity) {
        return EUNDEFINEDBUFFER;
    }

    *lambda = (float) hashmap->count / (float) hashmap->adt->capacity;

    return PASS;
}

status_code hashmap_init_capacity(map *hashmap, uint64_t limit, map_operations *operations,
                               api_lifecycle *lifecycle) {
    if (NULL == hashmap || NULL == operations) {
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
    hashmap->operations = operations;

    operations->insert = &hashmap_insert;
    operations->insert_all = &hashmap_insert_all;
    operations->rehash = &hashmap_rehash;
    operations->iterator = &hashmap_iterator;
    operations->contains = &hashmap_contains;
    operations->contains_all = &hashmap_contains_all;
    operations->get = &hashmap_get;
    operations->get_raw = &hashmap_get_raw;
    operations->remove = &hashmap_remove;
    operations->remove_all = &hashmap_remove_all;

    if (NULL != hashmap->processors &&
        NULL != hashmap->processors->on_initialization) {
        hashmap->processors->on_initialization(hashmap);
    }

    return PASS;
}

status_code hashmap_init(map *hashmap, map_operations *table,
                         api_lifecycle *lifecycle) {
    return hashmap_init_capacity(hashmap, (1024 << 2) + 1, table, lifecycle);
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
