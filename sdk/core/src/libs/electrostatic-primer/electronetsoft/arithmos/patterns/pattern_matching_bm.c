#include <electronetsoft/arithmos/patterns/pattern_matching.h>
#include <electronetsoft/arithmos/adt/map.h>
#include <electronetsoft/util/maps/lookup_table_util.h>
#include <math.h>
#include <alloca.h>
#include <stdint.h>
#include <time.h>

status_code find_boyer_moore(text in, text pattern, text_substring *out) {
    // preprocessor automata -- Validate the input params
    if (NULL == in.chars || NULL == in.operations ||
        NULL == out || in.length == 0) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == pattern.chars ||
        NULL == pattern.operations || pattern.length == 0) {
        return EUNDEFINEDBUFFER;
    }

    if (in.length < pattern.length) {
        return EBUFFERTURNCATION;
    }

    clock_t start = clock();

    // initialize a lookup table
    map hash_map = {
        .type = MAP_TYPE_HASHMAP,
        .col_scheme = NO_DUPLICATES
    };
    map_function_table table = {0};
    map_element element = {0};

    status_code __code = init_map_function_table(&hash_map,
                                                 &table, NULL);
    if (PASS != __code) {
        deinit_map_function_table(&hash_map, NULL);
        return __code;
    }

    // allocate local buffers for the lookup table
    char *__in_keys_buffer = alloca(sizeof(char) * in.length * 2);
    size_t *__in_indices_buffer = alloca(sizeof(size_t) * in.length);
    list_element *__in_elements = alloca(sizeof(list_element) * in.length);
    map_element *__in_map_elements = alloca(sizeof(map_element) * in.length);

    // initialize the lookup table with (-1) indices for all
    // text buffer characters
    __code = lookup_table_init(&hash_map, (lookup_buffer) {
            .in = in,
            .pattern = pattern,
            .__elements = __in_elements,
            .__indices = __in_indices_buffer,
            .__keys = __in_keys_buffer,
            .__map_elements = __in_map_elements
    }, DEFAULT);

    if (PASS != __code) {
        deinit_map_function_table(&hash_map, NULL);
        return __code;
    }

    char *__keys_buffer = alloca(sizeof(char) * pattern.length * 2);
    size_t *__indices_buffer = alloca(sizeof(size_t) * pattern.length);
    list_element *elements = alloca(sizeof(list_element) * pattern.length);
    map_element *__map_elements = alloca(sizeof(map_element) * pattern.length);

    // replaces the (-1) indices with the corresponding
    // index in the pattern
    // only those characters from the pattern that
    // appear in the text buffer are getting
    // their (-1) data replaced with their indices in the pattern
    __code = lookup_table_init(&hash_map, (lookup_buffer) {
        .in = pattern,
        .pattern = pattern,
        .__elements = elements,
        .__indices = __indices_buffer,
        .__keys = __keys_buffer,
        .__map_elements = __map_elements
    }, USE_INDICES);

    if (PASS != __code) {
        deinit_map_function_table(&hash_map, NULL);
        return __code;
    }

    // initialize a looking glass heuristic looker
    // starting from the rightmost character of the pattern
    // and the text comparing corresponding characters
    text_substring looking_glass = {
        .start_index = (pattern.length - 1),
        .length = in.length
    };

    while (1) {
        if (looking_glass.start_index >
                (looking_glass.length - 1)) {
            break;
        }
        size_t k = pattern.length - 1;
        for (; ; k--,
                    looking_glass.start_index--) {
            // preprocessing automata
            // character mismatch!
            if (pattern.chars[k] != in.chars[looking_glass.start_index]) {
                // Initialize a jump heuristic!
                // try to locate the character elsewhere in the pattern
                // using a lookup hashtable
                char __key[2] = {in.chars[looking_glass.start_index], '\0'};
                __code = hash_map.function_table->get(&hash_map, (typed_pointer) {
                        .address.str = __key,
                        .type = TYPE_STR
                }, &element);
                if (PASS != __code) {
                    deinit_map_function_table(&hash_map, NULL);
                    return __code;
                }
                // (-1) or an index of the character in the pattern
                // from the text
                size_t j = *((size_t *) element.value->data);

                // ((the outside loop controls))
                if (j < k) { // AND if (j == -1) it follows that the entire pattern
                            // shifting is commanded
                    looking_glass.start_index += pattern.length - (j + 1);
                } else {
                    looking_glass.start_index += pattern.length - k;
                }
                break;
            }

            // postprocessing automata
            // pattern is found
            // ((the inside loop controls))
            // IS (pattern.chars[k] == in.chars[looking_glass.start_index]
            //              and k == 0)
            if (k == 0) {
                out->start_index = looking_glass.start_index;
                out->length = pattern.length;

                clock_t end = clock();
                double elapsed =
                        (double)(end - start) / CLOCKS_PER_SEC;

                printf("Elapsed CPU time: %f seconds\n", elapsed);
                deinit_map_function_table(&hash_map, NULL);
                return PASS;
            }
        }
        // postprocessing automata
        // pattern is not found; jump heuristics already applied AOT on the next loop.
    }

    out->start_index = 0;
    out->length = 0;

    __code = deinit_map_function_table(&hash_map, NULL);
    if (PASS != __code) {
        return __code;
    }

    return ENOELEMENT;
}