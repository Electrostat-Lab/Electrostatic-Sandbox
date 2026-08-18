#ifndef __NUM_DECIMAL_H_
#define __NUM_DECIMAL_H_

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <electronetsoft/util/types.h>
#include <electronetsoft/util/number/crypto.h>

#ifdef __cplusplus
extern "C" { // disable C++ name mangling by declaring function prototypes
            // a C externally linked space
#endif

struct linear_congruent_seq {
    uint64_t multiplier;
    uint64_t increment;
    uint64_t initial_value;
    uint64_t modulus;
    uint64_t *rand;
    uint64_t *k;
};

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

static inline status_code dec_is_n_digit_b10(uint64_t in, uint8_t n) {
    if (0 == in || 0 == n) {
        return EINCOMPATTYPE;
    }
    // use the scientific notation to reduce the entire ZEROTH
    uint64_t redux = in * pow(10, - (n - 1));
    if (redux > 0 && redux < 10) {
        return ASSERTION_SUCCESS;
    }
    return ASSERTION_FAILURE;
}

static inline status_code dec_extract_middle_sq_n_digits(uint64_t in,
                                                      uint8_t n,
                                                      uint64_t *out) {
    if (NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    if (dec_is_n_digit_b10(in, n) != ASSERTION_SUCCESS) {
        return EINCOMPATTYPE;
    }

    if (((uint8_t) (n/2)) == 0) {
        return EBUFFERTURNCATION;
    }

    // square the number
    in *= in;
    // subtract the least significant digits
    status_code __code = dec_subtract_last_digits_b10(in, out, n / 2);
    if (PASS != __code) {
        return __code;
    }
    // extract the middle digits
    __code = dec_extract_last_digits_b10(in, out, n);
    if (PASS != __code) {
        return __code;
    }

    return PASS;
}

/**
 * @brief Generates a random number using a modified version of the linear congruential sequence
 * algorithm; the first dispatch to this algorithm will generate a pseudorandom number from
 * the given initial value to the modulus value; both the initial value and the value of the
 * modulus are included, and a linear subsequence of kth degree (k = (1, 2)).
 *
 * @param lcs a linear congruential sequence structure.
 */
static inline status_code dec_lcg_random(linear_congruent_seq lcs) {
    if (NULL == lcs.rand) {
        return EUNDEFINEDBUFFER;
    }
    if (lcs.multiplier > lcs.modulus
            || lcs.increment > lcs.modulus
                || lcs.initial_value > lcs.modulus) {
        return EINCOMPATTYPE;
    }
    if (lcs.multiplier < 2) {
        return EINCOMPATTYPE;
    }
    if (0 == *lcs.k) {
        *lcs.k = 1;
    }
    if (0 == *lcs.rand) {
        *lcs.rand = lcs.initial_value;
    }

    // calculate the increment as a variable of the multiplier and the kth term
    // the multiplier is a constant 64-bit number less than the modulus
    // the (k) is an index of the sub-sequence of the current random number
    // the subsequence lifetime is resettled each
    uint64_t __inc = ((pow(lcs.multiplier, *lcs.k) - 1) * lcs.increment) /
                            (lcs.multiplier - 1);

    // [((ax + c) mod m) | x] is the general equation for the
    // linear congruential sequence between two values (minima and maxima)
    // where; x = the initial value of the sequence; a = multiplier; c = increment; m = modulus
    // (a < m & a > 2) & c < m & x < m
    // if (c) is another structure of (ax + c); it follows
    // that a subsequence of the original sequence is generated
    // By reverse engineering; one may convert (ax + c) into its polynomial form of kth degree:
    // (a^k.x + b^(k-j).x + c)
    // Now (c) may be even broken down into its variable form to even maximize entropy
    // let; c = ((a^k - 1) * c_0)/(a - 1)
    //        = [a^k/(a - 1)].c_0 + [- c_0/(a - 1)]
    *lcs.rand = ((uint64_t) (pow(lcs.multiplier, *lcs.k) * *(lcs.rand) + __inc)) % (lcs.modulus + 1);

    // add the bits distribution of the initial value to the rand output
    // CASE 01: adding the bits of the initial value to any number in the sequence range
    // will not change the output.
    // CASE 02: adding the bits of the initial value to any number out of the
    // sequence range below minima; will give a decimal result of their
    // summation.
    if (*lcs.rand < lcs.initial_value) {
        *lcs.rand |= lcs.initial_value;
    }

    // advances the subsequence of the initial LCQ
    // reset kth terms when reaching the power of 3
    *lcs.k = (*lcs.k * 2 + 1) % 2;

    return PASS;
}

static inline status_code dec_clock_lcg_random(linear_congruent_seq *lcs) {
    if (NULL == lcs) {
        return EUNDEFINEDBUFFER;
    }

    lcs->increment = ((clock() >> 4) + 1) % lcs->modulus;
    lcs->multiplier = ((clock() ^ (clock() >> (lcs->increment % 8))) + 1) % lcs->modulus;

    if (lcs->multiplier < 2) {
        lcs->multiplier = 2;
    }

    status_code __code = dec_lcg_random(*lcs);
    if (PASS != __code) {
        return __code;
    }

    // postprocessing automata -- hash the output random number
    //                            to increase entropy.

    typed_pointer p = {
        .address.id = lcs->rand,
        .type = TYPE_ID
    };

    __code = crypto_hashkey_compress64((hash_component) {
        .key = p,
        .hash = lcs->rand,
        .user_key = (UINT32_MAX << 8) | (UINT32_MAX >> ((sizeof(uint32_t) * 8) - 8))
    }, (lcs->modulus + 1));
    if (PASS != __code) {
        return __code;
    }

    // postprocessing automata -- append the initial value to the final
    //                            value
    // Appending the initial value will ensure the sequence value
    // doesn't fall to below the initial value by appending its bits to the result
    // thus we would have a random number in the range (initial_value, modulus)
    if (*lcs->rand < lcs->initial_value) {
        *lcs->rand |= lcs->initial_value;
    }
    return __code;
}

#ifdef __cplusplus
};
#endif

#endif