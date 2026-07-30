#include <electronetsoft/arithmos/adt/map.h>
#include <electronetsoft/util/console/colors.h>
#include <stdio.h>

static inline status_code iterator_callback(map *hashmap, map_element *element) {
    fprintf(stdout, "Iterated element = (%s)\n",
            (const char *) element->value->data);
    return PASS;
}

int main() {
    map hash_map = (map) {
      .type = MAP_TYPE_HASHMAP,
    };
    map_function_table table = (map_function_table) {

    };

    typed_pointer __key_0 = (typed_pointer) {
        .address.str = "test_hashes",
        .type = TYPE_STR
    };

    typed_pointer __key_1 = (typed_pointer) {
        .address.str = "hashes_test",
        .type = TYPE_STR
    };

    typed_pointer __key_2 = (typed_pointer) {
        .address.str = "test_hashes112",
        .type = TYPE_STR
    };

    status_code __code = init_map_function_table(&hash_map,
                                                 &table,
                                                 NULL);
    if (PASS != __code || hash_map.adt == NULL) {
        fprintf(stderr, "%s %d\n",
                "Error while initializing the Map!", __code);
    }

    __code = hash_map.function_table->insert(&hash_map, &((map_element) {
        .key = __key_0,
        .value = &((list_element) {
            .type = ELEMENT_MAP_ITEM,
            .data = "Data 00"
        })
    }));
    if (PASS == __code) {
        fprintf(stderr, "%s %d\n",
                GREEN "Inserting Success" RESET, __code);
    } else if (EBUFFER_EXISTS == __code) {
        fprintf(stderr, "%s %d\n",
                RED "Inserting Failed: Buffer Exists; Data Updated!" RESET, __code);
    }

    __code = hash_map.function_table->insert(&hash_map, &((map_element) {
            .key = __key_1,
            .value = &((list_element) {
                    .type = ELEMENT_MAP_ITEM,
                    .data = "Data 01"
            })
    }));
    if (PASS == __code) {
        fprintf(stderr, "%s %d\n",
                GREEN "Inserting Success" RESET, __code);
    } else if (EBUFFER_EXISTS == __code) {
        fprintf(stderr, "%s %d\n",
                RED "Inserting Failed: Buffer Exists; Data Updated!" RESET, __code);
    }

    __code = hash_map.function_table->insert(&hash_map, &((map_element) {
            .key = __key_2,
            .value = &((list_element) {
                    .type = ELEMENT_MAP_ITEM,
                    .data = "Data 00"
            })
    }));
    if (PASS == __code) {
        fprintf(stderr, "%s %d\n",
                GREEN "Inserting Success" RESET, __code);
    } else if (EBUFFER_EXISTS == __code) {
        fprintf(stderr, "%s %d\n",
                RED "Inserting Failed: Buffer Exists; Data Updated!" RESET, __code);
    }

    __code = hash_map.function_table->insert(&hash_map, &((map_element) {
            .key = __key_0,
            .value = &((list_element) {
                    .type = ELEMENT_MAP_ITEM,
                    .data = "Data 013132"
            })
    }));
    if (PASS == __code) {
        fprintf(stderr, "%s %d\n",
                GREEN "Inserting Success" RESET, __code);
    } else if (EBUFFER_EXISTS == __code) {
        fprintf(stderr, "%s %d\n",
                RED "Inserting Failed: Buffer Exists; Data Updated!" RESET, __code);
    }

    map_element out = {
    };
    __code = hash_map.function_table->get(&hash_map, __key_0, &out);
    if (PASS != __code) {
        fprintf(stderr, "%s %d\n",
                "Error while retrieving the Map item!", __code);
    } else {
        fprintf(stdout, "LOG Data item %s\n",
                (const char *) out.value->data);
    }

    __code = hash_map.function_table->iterator(&hash_map, &iterator_callback);
    if (PASS != __code) {
        fprintf(stderr, "%s %d\n",
                "Iterating has failed!", __code);
    } else {
        fprintf(stdout, "Iterated successfully!\n");
    }

    __code = hash_map.function_table->remove(&hash_map, __key_0);
    if (PASS != __code) {
        fprintf(stderr, "%s %d\n",
                "Error while retrieving the Map item!", __code);
    }

    __code = hash_map.function_table->contains_all(&hash_map,
   (typed_pointer *[]) {
            &__key_1, &__key_2, NULL
    });
    if (PASS != __code) {
        fprintf(stderr, "%s %d\n",
                RED "Contains Failed!" RESET, __code);
    } else {
        fprintf(stdout, GREEN "Contains Passed!\n" RESET);
    }

    __code = hash_map.function_table->rehash(&hash_map, hash_map.adt->limit << 4);
    if (PASS != __code) {
        fprintf(stderr, "%s %d\n",
                "Resizing has failed!", __code);
    } else {
        fprintf(stdout, "Resizing succeeded with size = (%lu)\n",
                hash_map.adt->limit);
    }

    __code = hash_map.function_table->get(&hash_map, __key_0, &out);
    if (PASS != __code) {
        fprintf(stderr, "%s %d\n",
                "Error while retrieving the Map item!", __code);
    } else {
        fprintf(stdout, "LOG Data item %s\n",
                (const char *) out.value->data);
    }

    __code = deinit_map_function_table(&hash_map, NULL);
    if (PASS != __code) {
        fprintf(stderr, "%s %d\n",
                "Error while de-initializing the Map!", __code);
    }

    return 0;
}