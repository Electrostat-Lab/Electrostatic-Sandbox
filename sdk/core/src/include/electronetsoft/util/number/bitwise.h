#ifndef __NUM_BITWISE_H_
#define __NUM_BITWISE_H_

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
 * @brief Extracts a byte of base 2 from a 64-bit input
 * structure into an 8-bit output structure.
 *
 * @param in the input 64-bit structure.
 * @param out the output 8-bit structure.
 * @param i the index of the byte to extract out of the input structure.
 * @return EUNDEFINEDBUFFER if the (out) buffer is not pre-allocated
 *         PASS if the operation has passed successfully.
 */
static inline status_code bitwise_extract_byte(uint64_t in,
                                          uint8_t *out,
                                          uint8_t i) {
    if (NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    *out = (in >> (8 * i)) ^ 0b00000000;

    return PASS;
}

/**
 * @brief Pushes a byte of base 2 into position of index (i)
 * into the (out) structure leaving the rest of bytes unchanged.
 *
 * @param in the input byte of base 2 to push.
 * @param out the output 64-bit structure to push the byte into.
 * @param i the destined position or index of the byte.
 * @return EUNDEFINEDBUFFER if the (out) is not allocated.
 *         ENOELEMENT if the index is out of bounds.
 *         PASS if the operation has passed successfully without errors.
 */
static inline status_code bitwise_push_byte(uint8_t in,
                                       uint64_t *out,
                                       uint8_t i) {
    if (NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    if (i >= 8) {
        return ENOELEMENT;
    }

    *(((uint8_t *) out) + i) = in;
    return PASS;
}

/**
 * @brief Exchanges 2 bytes together inside the (in) 64-bit structure
 * without changing the rest of the bytes.
 *
 * @param in the input 64-bit structure.
 * @param out the output structure with changed bytes.
 * @param i0 the index of the first byte to exchange.
 * @param i1 the index of the second byte to exchange.
 * @return EUNDEFINEDBUFFER if the (out) buffer is not pre-allocated
 *         ENOELEMENT if the indexes are out of bounds or equal.
 *         PASS otherwise.
 */
static inline status_code bitwise_exchange_bytes(uint64_t in,
                                         uint64_t *out,
                                         uint8_t i0,
                                         uint8_t i1) {
    if (NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    if (i0 >= 8 || i1 >= 8 || i0 == i1) {
        return ENOELEMENT;
    }

    uint8_t byte_0 = ((uint8_t *) &in)[i0];
    uint8_t byte_1 = ((uint8_t *) &in)[i1];
    *(((uint8_t *) out) + i0) = byte_1;
    *(((uint8_t *) out) + i1) = byte_0;
    return PASS;
}

static inline status_code bitwise_left_cyclic_shift(uint64_t in,
                                               uint64_t *out,
                                               uint8_t bits) {
    if (NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    if (bits >= (sizeof (in) * 8)) {
        return EINCOMPATTYPE;
    }

    *out = (in << bits) | (in >> (sizeof (in) * 8 - bits));

    return PASS;
}

static inline status_code bitwise_right_cyclic_shift(uint64_t in,
                                                    uint64_t *out,
                                                    uint8_t bits) {
    if (NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    if (bits >= (sizeof (in) * 8)) {
        return EINCOMPATTYPE;
    }

    *out = (in >> bits) | (in << (sizeof (in) * 8 - bits));

    return PASS;
}

#ifdef __cplusplus
};
#endif

#endif