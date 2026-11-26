#ifndef __TEXT_ADT_H_
#define __TEXT_ADT_H_

#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <electronetsoft/arithmos/adt/list.h>
#include <electronetsoft/arithmos/memory/patcher.h>
#include <electronetsoft/util/utilities.h>
#include <electronetsoft/util/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct text {
    const char *chars;
    size_t length;
    size_t position;
    bool override_position;
    text_operations *operations;
};

struct text_substring {
    size_t start_index;
    size_t length;
};

struct text_operations {
    /**
     * Substrings the input text using an index and a length.
     */
    status_code (*substring)(text, text, text, text_substring *);
    status_code (*to_list)(text, list *);
    status_code (*from_list)(list, text *);

    /**
     * Pattern matches the input text against the pattern; analogous
     * to the (index_of) operator.
     * @note Pattern matching is a text searching procedure utilized to localize
     * a strip of text inside a larger text.
     *
     * @retrun [ENOELEMENT] if the buffer cannot be found at all.
     * [EBUFFERTURNCATION] if at least the first element is present, and the rest of the buffer
     * is absent. One then may examine the output buffer to see the characters found during the search.
     */
    status_code (*pattern_match)(text, text, text_substring *);

    /**
     * Adds a delimiter to subsequent strips of text using substring.
     */
    status_code (*delimits)(text, text_substring, char, text *);
    status_code (*replace)(text, text, text, text *);
};

status_code text_init(text *, text_operations *);
status_code text_deinit(text *);

#ifdef __cplusplus
};
#endif

#endif