#include <electronetsoft/arithmos/patterns/pattern_matching.h>
#include <time.h>

status_code find_brute(text in, text pattern, text_substring *out) {
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

    // a prefix string to the last text chunk
    // (that last text chunk is of size equal to the pattern size)
    text_substring prefix = {
        .length = in.length - pattern.length
    };

    if (in.override_position) {
        prefix.start_index = 0;
    } else {
        prefix.start_index = in.position;
    }

    if (prefix.start_index > prefix.length) {
        return EINCOMPATTYPE;
    }

    while (1) {
        // preprocessing (loop controls) -- validate the current position
        // samples when the pointer passes the prefix substring length
        // notice the last character is included
        if (prefix.start_index > prefix.length) {
            break;
        }

        size_t i = 0;
        // processing automata -- matching the pattern text chunks
        for (; i < pattern.length &&
                        in.chars[prefix.start_index + i] == pattern.chars[i]; i++);

        // post-processing automata -- validation
        if (i == pattern.length) {
            out->start_index = prefix.start_index;
            out->length = pattern.length;
            clock_t end = clock();
            double elapsed =
                    (double)(end - start) / CLOCKS_PER_SEC;

            printf("Elapsed CPU time: %f seconds\n", elapsed);
           return PASS;
        }

        // !NOT WORKING!
        // post-processing automata -- increment the counter of the prefix strip
        // post-processing optimizations via memory items...
        // remember the previously matched items!
        // and shift past them!
//        if (i > 0) {
//            prefix.start_index += i;
//            continue;
//        }
        prefix.start_index += 1;
    }

    out->start_index = 0;
    out->length = 0;

    return ENOELEMENT;
}
