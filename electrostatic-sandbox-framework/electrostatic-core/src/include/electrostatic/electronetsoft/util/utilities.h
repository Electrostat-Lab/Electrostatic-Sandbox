#ifndef __UTILITIES_H_
#define __UTILITIES_H_

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <electrostatic/electronetsoft/util/types.h>

#ifdef __cplusplus
extern "C" { // disable C++ name mangling by declaring function prototypes
            // a C externally linked space
#endif

union pointer {
    list *m_list;
    list_element *m_list_element;
    linked_buffer *m_linked_buffer;
    list_function_table *m_list_function_table;
};

enum pointer_type {
    TYPE_LIST = 200,
    TYPE_LIST_ELEMENT = TYPE_LIST + 1,
    TYPE_LINKED_BUFFER = TYPE_LIST_ELEMENT + 1,
    TYPE_LIST_FUNCTION_TABLE = TYPE_LINKED_BUFFER + 1,
    TYPE_UNKNOWN = TYPE_LIST_FUNCTION_TABLE + 1,
};

struct typed_pointer {
    pointer address;
    pointer_type type;
};

enum status_code {
    PASS = INT32_MAX,
    EUNDEFINEDBUFFER = INT32_MIN,
    EEMPTYBUFFER = (EUNDEFINEDBUFFER + 1),
    EFULLBUFFER = (EEMPTYBUFFER + 1),
    EINCOMPATTYPE = (EFULLBUFFER + 1),
    ENOELEMENT = (EINCOMPATTYPE + 1),
    EBUFFERTURNCATION = (ENOELEMENT + 1),
    EBUFFEROVERFLOW = (EBUFFERTURNCATION + 1),
    EDLLOPENFAIL = (EBUFFEROVERFLOW + 1),
    EDLLSYMFAIL = (EDLLOPENFAIL + 1),
    EDLLCONVENTIONCALLRETURN = (EDLLSYMFAIL + 1),
    ASSERTION_SUCCESS = 1,
    ASSERTION_FAILURE = 0
};

struct api_lifecycle {
    void (*on_operation_succeeded)(void *api, void *caller);
    void (*on_operation_failed)(void *api, void *caller, status_code cause);
};

/**
 * Uses a pointer as an r-value for safe
 * comparison reasons.
 *
 * @param address a pointer variable for a memory address.
 * @return an r-value that is a runtime constant representing the address.
 */
static inline void *const rvalue(void *address) {
    return (void *const) address;
}

/**
 * @brief Takes a null-terminated list of status codes, and
 * tests if all of them meet the PASS code.
 * @warning (Unsafe) If the contiguous buffer is not null-terminated, this
 * could lead to a dangerous buffer runtime memory access violations resulting
 * in an immediate crash without warnings.
 *
 * <p>
 * Example:
 * <code> \n
 *   status_code _code = PASS; \n
 *   status_code __code = PASS; \n
 *   status_code ___code = EUNDEFINEDBUFFER; \n
 *   status_code *codes[] = {&_code, &__code, &___code, '\0'}; \n
 *   bool pass = is_pass(codes); \n
 * </code>
 * </p>
 *
 * @param codes a null-terminated list of status codes.
 * @return true if all the codes are PASSED
 */
static inline bool is_pass(status_code **codes) {
    // preprocessing automata
    if (rvalue(codes) == NULL ||
            rvalue(*codes) == NULL) {
        return false;
    }
    // preprocessing initialize with true for
    // a Conjunctive Normal Form (CNF) accumulator formula
    bool predicate = true;
    // processing automata
    for (int i = 0; codes[i] != NULL; i++) {
        // perform a CNF accumulator algorithm
        predicate &= (PASS == *codes[i]);
    }
    return predicate;
}

static inline typed_pointer get_typed_pointer(void *address, pointer_type type) {
    // preprocessor automata -- Input Validation.
    if (rvalue(address) == NULL) {
        return (typed_pointer) {
            .address.m_list = NULL,
            .type = TYPE_UNKNOWN
        };
    }
    // processing automata -- returning a typed pointer
    return (typed_pointer) {
        .address.m_list = address,
        .type = type
    };
}

#ifdef __cplusplus
};
#endif

#endif