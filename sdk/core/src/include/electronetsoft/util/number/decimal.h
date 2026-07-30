#ifndef __NUM_DECIMAL_H_
#define __NUM_DECIMAL_H_

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <electronetsoft/util/types.h>

#ifdef __cplusplus
extern "C" { // disable C++ name mangling by declaring function prototypes
            // a C externally linked space
#endif

/**
 * @brief Subtracts the last (n) digits from the input (in) of base 10
 * and stores the result into the output (out) buffer.
 *
 * @param in an input of decimal integer format up-to 64-bit number.
 * @param out an output buffer to store the result.
 * @param n the number of digits to subtract from the input counted
 *          from the least significant digit
 *          (i.e., the last digit from the right).
 * @return EUNDEFINEDBUFFER if the (out) buffer is not pre-allocated.
 *         EINCOMPATTYPE if the input is less than the divisor.
 *         PASS if the operation has passed successfully.
 */
static inline status_code dec_subtract_last_digits_b10(uint64_t in,
                                                   uint64_t *out,
                                                   uint8_t n) {
    if (NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    if (in < pow(10, n)) {
        return EINCOMPATTYPE;
    }

    *out = in / ((uint64_t) pow(10, n));

    return PASS;
}

/**
 * @brief Extracts the last (n) digits from the input (n) of base 10
 * (i.e., decimal) into the output buffer.
 *
 * @param in an input of decimal integer format up-to 64-bit number.
 * @param out an output buffer to store the result.
 * @param n the number of digits to extract from the input counted
 *          from the least significant digit.
 * @return EUNDEFINEDBUFFER if the (out) buffer is not pre-allocated.
 *         EINCOMPATTYPE if the input is less than the divisor.
 *         PASS if the operation has passed successfully.
 */
static inline status_code dec_extract_last_digits_b10(uint64_t in,
                                                  uint64_t *out,
                                                  uint8_t n) {
    if (NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    if (in < pow(10, n)) {
        return EINCOMPATTYPE;
    }

    *out = in % ((uint64_t) pow(10, n));
    return PASS;
}

static inline uint64_t dec_generate_next_odd(uint64_t n) {
    return (n * 2) + 1;
}

#ifdef __cplusplus
};
#endif

#endif