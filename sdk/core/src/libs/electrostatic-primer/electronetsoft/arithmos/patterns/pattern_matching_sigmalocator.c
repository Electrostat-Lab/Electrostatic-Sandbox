#include <electronetsoft/arithmos/patterns/pattern_matching.h>
#include <electronetsoft/arithmos/adt/map.h>
#include <electronetsoft/util/maps/lookup_table_util.h>
#include <math.h>
#include <alloca.h>
#include <stdint.h>
#include <time.h>

static inline status_code __lookup_preprocessor(text in, text pattern, size_t i) {
    if (in.chars[i] != pattern.chars[0]) {
        return ENOELEMENT;
    }

    size_t __last_char = i + (pattern.length - 1);
    if (__last_char >= in.length) {
        return EBUFFERTURNCATION;
    }

    if (in.chars[__last_char] != pattern.chars[pattern.length - 1]) {
        return ENOELEMENT;
    }

    size_t __middle_index = (pattern.length - 1) / 2;
    if (in.chars[i + __middle_index] != pattern.chars[__middle_index]) {
        return ENOELEMENT;
    }

    size_t __middle_third_index = (pattern.length - 1) / 3;
    if (in.chars[i + __middle_third_index] != pattern.chars[__middle_third_index]) {
        return ENOELEMENT;
    }

    size_t __middle_two_third_index = (pattern.length - 1) / 1.5;
    if (in.chars[i + __middle_two_third_index] != pattern.chars[__middle_two_third_index]) {
        return ENOELEMENT;
    }

    return PASS;
}

static inline status_code __eval_pattern(text in, text pattern, size_t leading_index) {
    for (size_t i = 0; i < pattern.length; i++) {
        // preprocessor memory validation
        if ((leading_index + i) >= in.length) {
            return ENOELEMENT;
        }
        if (in.chars[leading_index + i] != pattern.chars[i]) {
            return ENOELEMENT;
        }
    }
    return PASS;
}

static inline status_code __sigma_locate_pattern(map hashmap, text in,
                                                 text pattern,
                                                 text_substring *out) {

    status_code __code;
    map_element __element = {0};
    list_element *__list_element = NULL;
    typed_pointer lookup_key = {0};
    size_t leading_index = 0;

    char initial_char[2] = {pattern.chars[0], '\0'};
    __code = hashmap.function_table->get_raw(&hashmap, (typed_pointer) {
            .address.str = (char *) initial_char,
            .type = TYPE_STR
    }, &__element);

    if (PASS != __code) {
        return ENOELEMENT;
    }

    if (ELEMENT_LIST == __element.value->type) {
        list *__buffer = __element.value->data;

        if (NULL == __buffer || NULL == __buffer->elements) {
            return EUNDEFINEDBUFFER;
        }

        for (uint64_t j = 0; j < __buffer->limit; j++) {
            __code = __buffer->function_table->get(__buffer, j, &__list_element);
            if (PASS != __code) {
                if (j == __buffer->limit - 1) {
                    return ENOELEMENT;
                }
                continue;
            }

            lookup_key = __list_element->metadata;
            leading_index = *((size_t *) __list_element->data);

            if (strcmp(lookup_key.address.str, initial_char) != 0) {
                if (j == __buffer->limit - 1) {
                    return ENOELEMENT;
                }
                continue;
            }

            __code = __lookup_preprocessor(in, pattern, leading_index);
            if (PASS != __code) {
                if (j == __buffer->limit - 1) {
                    return ENOELEMENT;
                }
                continue;
            }

            // start index found
            __code = __eval_pattern(in, pattern, leading_index);
            if (PASS != __code) {
                if (j == __buffer->limit - 1) {
                    return ENOELEMENT;
                }
                continue;
            }

            out->start_index = leading_index;
            out->length = pattern.length;

            return PASS;
        }
    }

    __list_element = __element.value;
    leading_index = *((size_t *) __list_element->data);
    lookup_key = __list_element->metadata;

    if (strcmp(lookup_key.address.str, initial_char) != 0) {
        return ENOELEMENT;
    }

    __code = __eval_pattern(in, pattern, leading_index);
    if (PASS != __code) {
        return ENOELEMENT;
    }

    out->start_index = leading_index;
    out->length = pattern.length;

    return PASS;
}

status_code find_sigma_locator(text in, text pattern, text_substring *out) {
    // preprocessor automata -- Validate the input params
    if (NULL == in.chars || NULL == in.operations ||
        NULL == out || in.length <= 0) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == pattern.chars ||
        NULL == pattern.operations || pattern.length <= 0) {
        return EUNDEFINEDBUFFER;
    }

    if (in.length < pattern.length) {
        return EBUFFERTURNCATION;
    }

    // costly validations come eventually!
    if ('\0' == in.chars[0] || '\0' == in.chars[in.length - 1]) {
        return EBUFFERTURNCATION;
    }

    if ('\0' == pattern.chars[0] || '\0' == pattern.chars[pattern.length - 1]) {
        return EBUFFERTURNCATION;
    }

    // processing automata -- (1) initialize a lookup table with
    //    all the input text; even duplicate characters
    // key: hashcode of the character
    // value: index of the character in the input text

    // (2) Try to retrieve the first character from the pattern
    // into the text using the hashcode lookup table (i.e., hashtable)
    // --- IF the first character is not FOUND; terminate immediately
    // with ENOELEMENT ---
    // --- (3) Hashtable Heuristics ---
    // <<1>> IF the first character reveals a buffer of identical characters
    // (in case identical characters are trivially enabled by the internal hashmap)
    // a list of buffers is iterated and the value of the characters
    // iterated is utilized as an starting index from which
    // the test suite is initiated; testing is started from that index
    // up-to the pattern length; the pattern characters are tried against
    // the text characters starting from that substring spot;
    // <<2>> IF no match --- the next character from the list of buffers is tried; until one is found or none; terminating immediately with ENOELEMENT
    //
    // <<3>> The same analogy may be utilized; to try to locate the last character from the pattern into the text
    // locating the first character and the last character from the pattern into the text will provide a preprocessing optimization
    // heuristics; that is the ability to validate the algorithm length
    // and be able to test the sequence and precompute the algorithmic time ahead-of-time.
    //

    // Another easy algorithm is to depend on the collision property of the hashmaps implemented within the SDK
    // a trial to insert the pattern characters into the hashmap of the input text; if the collision occurs;
    // the collided element is checked against the requested element; and the delta factor is tested;
    // if one of them fails; the algorithm terminates; if the collided structure is a list of elements;
    // all elements are tested

    // initialize a lookup table
    map hash_map = {
            .type = MAP_TYPE_HASHMAP,
            .col_scheme = ALLOW_DUPLICATES
    };
    map_function_table table = {0};
    map_element element = {0};

    status_code __code = init_map_function_table(&hash_map, &table, NULL);
    if (PASS != __code) {
        deinit_map_function_table(&hash_map, NULL);
        return __code;
    }

    char *__keys_buffer = alloca(sizeof(char) * in.length * 2);
    size_t *__indices_buffer = alloca(sizeof(size_t) * in.length);
    list_element *elements = alloca(sizeof(list_element) * in.length);
    map_element *__map_elements = alloca(sizeof(map_element) * in.length);
    lookup_buffer_proc processors = {
         .lookup_preprocessor = NULL,
    };

    __code = lookup_table_init(&hash_map, (lookup_buffer) {
            .in = in,
            .pattern = pattern,
            .__elements = elements,
            .__indices = __indices_buffer,
            .__keys = __keys_buffer,
            .__map_elements = __map_elements,
            .processors = &processors
    }, USE_INDICES);

    if (PASS != __code) {
        return __code;
    }

    // processing automata --
    // The idea of the sigma locator algorithm
    // is to locate the first character from the pattern into the text in O(1) time using hash tables;
    // respecting the duplicates;
    // this kind of hash tables are lookup tables that allow duplicate keys, and handle them
    // using contiguous buffers;

    // duplicate list of the first characters are iterated; the map elements inside it
    // are tried as starting indices into the original input text.
    // Following that, the rest of characters are tested contiguously with those from the pattern
    // failure of all the characters inside the duplicate list results in the termination of the algorithm

    // If there are no duplicates; then the located map element is used as the starting index
    // Failure of pattern matching at this point results in the termination of the algorithm

    // The sigma locator algorithm runs in the following clock complexities:
    // Worst Runtime: O(n + d.m); where (n) is the length of the input text
    //                                  (m) is the length of the input pattern
    //                                  (d) is the number of duplicates of the first character in the pattern
    clock_t start = clock();

    __code = __sigma_locate_pattern(hash_map, in, pattern, out);
    if (PASS == __code) {
        clock_t end = clock();

        double elapsed =
                (double)(end - start) / CLOCKS_PER_SEC;

        printf("Elapsed CPU time: %f seconds\n", elapsed);

        __code = deinit_map_function_table(&hash_map, NULL);
        if (PASS != __code) {
            return __code;
        }
        return __code;
    }

    // postprocessing automata
    __code = deinit_map_function_table(&hash_map, NULL);
    if (PASS != __code) {
        return __code;
    }

    out->start_index = 0;
    out->length = 0;

    return ENOELEMENT;
}