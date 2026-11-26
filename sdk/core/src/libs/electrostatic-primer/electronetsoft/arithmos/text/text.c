#include <electronetsoft/arithmos/adt/text.h>
#include <electronetsoft/arithmos/patterns/pattern_matching.h>

static inline status_code __text_pattern_match(text in,
                                             text pattern,
                                             text_substring *out) {
    return find_kmp(in, pattern, out);
}

static inline status_code __text_substring(text in, text pattern0,
                                           text pattern1,
                                           text_substring *substring) {
    if (NULL == substring) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == in.chars || '\0' == in.chars[0]) {
        return EUNDEFINEDBUFFER;
    }

    if (in.length <= 0 || '\0' == in.chars[in.length - 1]) {
        return EBUFFERTURNCATION;
    }

    if (NULL == pattern0.chars || '\0' == pattern0.chars[0]) {
        return EUNDEFINEDBUFFER;
    }

    if (pattern0.length <= 0 || '\0' == pattern0.chars[pattern0.length - 1]) {
        return EBUFFERTURNCATION;
    }

    if (NULL == pattern1.chars || '\0' == pattern1.chars[0]) {
        return EUNDEFINEDBUFFER;
    }

    if (pattern1.length <= 0 || '\0' == pattern1.chars[pattern1.length - 1]) {
        return EBUFFERTURNCATION;
    }

    text_substring __substring_0 = {
          .start_index = 0,
          .length = 0
    };
    status_code __code = __text_pattern_match(in, pattern0, &__substring_0);
    if (PASS != __code) {
        return __code;
    }

    text_substring __substring_1 = {
          .start_index = 0,
          .length = 0
    };
    __code = __text_pattern_match(in, pattern1, &__substring_1);
    if (PASS != __code) {
        return __code;
    }

    if (__substring_0.length < __substring_1.length) {
        return EBUFFERTURNCATION;
    }

    substring->start_index = __substring_0.start_index;
    substring->length = __substring_1.start_index - __substring_0.start_index;

    return PASS;
}

status_code text_init(text *__text, text_operations *__op) {
    if (NULL == __text || NULL == __op) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == __text->chars) {
        return EUNDEFINEDBUFFER;
    }

    if (__text->length == 0) {
        return EBUFFERTURNCATION;
    }

    __text->operations = __op;

    __op->delimits = NULL;
    __op->from_list = NULL;
    __op->replace = NULL;
    __op->substring = &__text_substring;
    __op->to_list = NULL;
    __op->pattern_match = &__text_pattern_match;

    return PASS;
}

status_code text_deinit(text *__text) {
    if (NULL == __text) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == __text->chars) {
        return EBUFFERTURNCATION;
    }

    __text->length = 0;
    __text->position = -1;
    __text->operations = NULL;

    __text->chars = NULL;

    return PASS;
}