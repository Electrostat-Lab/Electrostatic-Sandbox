#include <electronetsoft/arithmos/patterns/pattern_matching.h>
#include <alloca.h>
#include <string.h>
#include <time.h>

static inline status_code __kmp_failure(text pattern, size_t *failure) {
    if (NULL == failure) {
        return EUNDEFINEDBUFFER;
    }

    text_substring suffix = {
        .start_index = 1,
        .length = pattern.length
    };

    size_t k = 0;

    while (suffix.start_index < suffix.length) {
        // detect mismatch
        if (pattern.chars[k] != pattern.chars[suffix.start_index]) {
            if (k > 0) { // there exists some previously matched characters!
                k = failure[k - 1]; // trying to find a matching ending index at the prefix
                                    // to the current suffix index
            } else { // try to find a starting point for the next iteration
                suffix.start_index += 1;
            }
            continue;
        }
        // match!
        // still other characters to match; advance both the pattern and the text
        failure[suffix.start_index] = k + 1;

        k += 1;
        suffix.start_index += 1;
        // update the length of the prefix-is-suffix
    }

    return PASS;
}

status_code find_kmp(text in, text pattern, text_substring *out) {
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

    clock_t start = clock();

    // initialize a looking glass heuristic looker
    // starting from the rightmost character of the pattern
    // and the text comparing corresponding characters
    text_substring prefix = {
        .start_index = 0,
        .length = in.length
    };

    size_t k = 0;

    size_t *__failure = alloca(sizeof(size_t) * pattern.length);
    memset(__failure, 0, sizeof(size_t) * pattern.length);

    status_code __code = __kmp_failure(pattern, __failure);
    if (PASS != __code) {
        return __code;
    }

    while (1) {
        if (prefix.start_index >
                (prefix.length - 1)) {
            break;
        }
        // detect mismatch
        if (pattern.chars[k] != in.chars[prefix.start_index]) {
            if (k > 0) { // there exists some previously matched characters!
                k = __failure[k - 1]; // reuse an index from another algorithm!
            } else { // try to find a starting point for the next iteration
                prefix.start_index += 1;
            }
            continue;
        }
        // match!
        // last match; return the substring indexers
        if (k == pattern.length - 1) {
            out->start_index = prefix.start_index - (pattern.length - 1);
            out->length = pattern.length;
            clock_t end = clock();

            double elapsed =
                    (double)(end - start) / CLOCKS_PER_SEC;

            printf("Elapsed CPU time: %f seconds\n", elapsed);
            return PASS;
        }
        // still other characters to match; advance both the pattern and the text
        k += 1;
        prefix.start_index += 1;
    }

    out->start_index = 0;
    out->length = 0;

    return ENOELEMENT;
}