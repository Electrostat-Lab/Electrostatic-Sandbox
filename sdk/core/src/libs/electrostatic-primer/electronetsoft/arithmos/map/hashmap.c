#include <electronetsoft/arithmos/map/hashmap.h>
#include <electronetsoft/arithmos/adt/list.h>
#include <electronetsoft/util/number/crypto.h>
#include <stdio.h>

typedef struct {
    list_element *value;
    uint64_t index;
} key_element;

static inline status_code init_adt_list(list **buffer, uint64_t limit) {
    if (NULL == buffer) {
        return EUNDEFINEDBUFFER;
    }

    *buffer = calloc(1, sizeof(list));
    if (NULL == buffer) {
        return EBUFFEROVERFLOW;
    }

    (*buffer)->type = CONTIGUOUS_BUFFER;
    (*buffer)->limit = limit;

    // Preprocessing automata (pre-init phase) -- memory allocation
    list_function_table *list_table = calloc(1, sizeof(list_function_table));
    if (NULL == list_table) {
        return EBUFFEROVERFLOW;
    }

    list_element **elements = calloc((*buffer)->limit, sizeof(list_element *));
    if (NULL == elements) {
        return EBUFFEROVERFLOW;
    }

    // Processing and Post automata (initialization phase) -- list initialization

    return init_list_function_table(*buffer, elements, list_table, NULL);
}

static inline status_code get_element_by_str_key(list *buffer,
                                    const char *__key0,
                                    key_element *__out) {
    char *__key1 = NULL;
    status_code __code;

    for (uint64_t i = 0; i < buffer->limit; i += 1) {
        if (NULL == buffer->elements[i] ||
            NULL == buffer->elements[i]->data) {
            continue;
        }
        // HERE
        __key1 = buffer->elements[i]->metadata;
        if (strcmp(__key0, __key1) != 0) {
            __code = ENOELEMENT;
            continue;
        }
        __code = PASS;

        if (NULL != __out) {
            __out->index = i;
            __out->value = buffer->elements[i];
        }
        break;
    }
    return __code;
}

static inline status_code get_element_by_long_key(list *buffer, uint64_t *key,
                                                  key_element *__out) {
    uint64_t *__key1 = NULL;
    status_code __code;

    for (uint64_t i = 0; i < buffer->limit; i += 1) {
        if (NULL == buffer->elements[i] ||
            NULL == buffer->elements[i]->data) {
            continue;
        }
        // HERE
        __key1 = buffer->elements[i]->metadata;
        if (*__key1 != *key) {
            __code = ENOELEMENT;
            continue;
        }
        __code = PASS;

        if (NULL != __out) {
            __out->index = i;
            __out->value = buffer->elements[i];
        }
        break;
    }
    return __code;
}

static inline status_code get_element_by_typed_key(list *buffer, typed_pointer key,
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

static inline status_code collision_init_separate_chain
                                (list *buffer,
                                 list_element *header,
                                 list_element *next,
                                 uint64_t index) {
    status_code __code;

    list *__separate_chain = NULL;
    __code = init_adt_list(&__separate_chain, (8 << 2) + 1);
    if (PASS != __code || NULL == __separate_chain) {
        return __code;
    }

    // copy it to the buffer
    __code = __separate_chain->function_table->add(__separate_chain, header);
    if (PASS != __code) {
        return __code;
    }

    __code = __separate_chain->function_table->add(__separate_chain, next);
    if (PASS != __code) {
        return __code;
    }

    // add the secondary buffer instead
    list_element *__chain_element = (list_element *) calloc(1, sizeof(list_element));
    __chain_element->data = __separate_chain;
    __chain_element->type = ELEMENT_LIST;
    __chain_element->size = sizeof (list);
    __chain_element->metadata = buffer->elements[index]->metadata;

    __code = buffer->function_table->insert_overwrite(buffer, __chain_element, index);
    if (PASS != __code) {
        return __code;
    }

    return PASS;
}

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
        if (ENOELEMENT == get_element_by_typed_key(__internal_buffer,
                                                   *((typed_pointer *) element->metadata), NULL)) {
            return __internal_buffer->function_table->
                            add(__internal_buffer, element);
        }
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

    // test if they are identical items
    // replace the map element with the new
    // map_element carried on the element
    // de-allocate the carrier structure
    const char *__key0 = item->metadata;
    const char *__key1 = element->metadata;
    if (strcmp(__key0, __key1) == 0) {
        item->data = element->data;
        item->type = element->type;
        item->size = element->size;
        return EBUFFER_EXISTS;
    }

    __code = collision_init_separate_chain(buffer, item,
                                           element, index);

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
                hasher.key = *((typed_pointer *) __buffer->elements[j]->metadata);
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
            hasher.key = *((typed_pointer *) buffer->elements[i]->metadata);
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
    element->value->metadata = &(element->key);
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
                element.key = *((typed_pointer *) __buffer->elements[j]->metadata);
                __code = callback(hashmap, &element);
                if (PASS != __code) {
                    return __code;
                }
            }
            continue;
        }
        element.value = buffer->elements[i];
        element.key = *((typed_pointer *) buffer->elements[i]->metadata);
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

    *lambda = (float) (hashmap->count/hashmap->adt->limit);

    return PASS;
}

status_code hashmap_init(map *hashmap, map_function_table *table,
                         api_lifecycle *lifecycle) {
    if (NULL == hashmap) {
        return EUNDEFINEDBUFFER;
    }

    // preprocessing automata -- ADT allocation and initialization
    list *buffer = NULL;
    status_code __code = init_adt_list(&buffer, (16 << 2) + 1);

    if (PASS != __code) {
        return __code;
    }

    // processing automata -- HASHMap allocation and initialization
    hashmap->adt = buffer;
    hashmap->type = MAP_TYPE_HASHMAP;
    hashmap->function_table = table;

    table->insert = &hashmap_insert;
    table->insert_all = &hashmap_insert_all;
    table->rehash = &hashmap_rehash;
    table->iterator = &hashmap_iterator;
    table->contains = &hashmap_contains;
    table->contains_all = &hashmap_contains_all;
    table->get = &hashmap_get;
    table->remove = &hashmap_remove;
    table->remove_all = &hashmap_remove_all;

    if (NULL != hashmap->processors &&
            NULL != hashmap->processors->on_initialization) {
        hashmap->processors->on_initialization(hashmap);
    }

    return PASS;
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

    list *buffer = (list *) (hashmap->adt);

    for (uint64_t i = 0; i < hashmap->adt->limit; i++) {
        if (NULL != buffer->elements[i] && ELEMENT_LIST == buffer->elements[i]->type) {
            list *buffer2 = buffer->elements[i]->data;
            free(buffer2->function_table);
            free(buffer2->elements);
            free(buffer2);
            free(buffer->elements[i]);
        }
    }

    free(buffer->function_table);
    free(buffer->elements);
    free(buffer);

    if (NULL != lifecycle && NULL != lifecycle->on_operation_succeeded) {
        lifecycle->on_operation_succeeded(&hashmap_deinit, hashmap);
    }

    return PASS;
}
