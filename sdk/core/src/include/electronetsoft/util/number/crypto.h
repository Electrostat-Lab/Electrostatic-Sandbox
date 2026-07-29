#ifndef __NUM_CRYPTO_H_
#define __NUM_CRYPTO_H_

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <electronetsoft/util/types.h>
#include <electronetsoft/util/utilities.h>
#include <electronetsoft/util/number/bitwise.h>

#ifdef __cplusplus
extern "C" { // disable C++ name mangling by declaring function prototypes
            // a C externally linked space
#endif

struct hash_component {
    typed_pointer key;
    uint64_t *hash;
    uint64_t user_key;
};

static inline status_code crypto_spread_64(uint64_t in, uint64_t *out) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    in = in ^ ((in ^ (in >> 32)) >> 32);
    *out = in;

    return PASS;
}

static inline status_code crypto_hash_str(hash_component hasher) {
    if (NULL == hasher.key.address.str || NULL == hasher.hash) {
        return EUNDEFINEDBUFFER;
    }

    if (TYPE_STR != hasher.key.type) {
        return EINCOMPATTYPE;
    }

    // Use a large prime constant to initialize (FNV-1a style)
    uint64_t h = 0xcbf29ce484222325ULL;
    status_code __code;

    // Process every character
    // Algorithm for polynomial hashing using Horner's rule
    for (const char *address = hasher.key.address.str; *address != '\0'; address++) {
        // use reverse Horner's Rule to compute the hash
        // 1. XOR the character into the hash
        h ^= (*address);
        // 2. Multiply by 2^5 (aka 32) which is the same as left-shifting by
        // 5 bits using Cyclic Shift Hashcode
        __code = bitwise_left_cyclic_shift(h, &h, 5);
        if (PASS != __code) {
            return __code;
        }
        // 4. Combine MSB Component with LSB Component
        h = (h >> 32) ^ h;
    }

    // Apply your spread_64 as a finalizer to ensure high entropy
    return crypto_spread_64(h ^ hasher.user_key, hasher.hash);
}

static inline status_code crypto_hash_long(hash_component hasher) {
    if (NULL == hasher.key.address.id || NULL == hasher.hash) {
        return EUNDEFINEDBUFFER;
    }

    if (TYPE_ID != hasher.key.type) {
        return EINCOMPATTYPE;
    }

    status_code __code;
    uint64_t in = *(hasher.key.address.id);

    for (int i = 0; i < 4; i += 2) {
        __code = bitwise_exchange_bytes(in, hasher.hash, i, i + 1);
        if (PASS != __code) {

            return __code;
        }

        __code = bitwise_exchange_bytes(in, hasher.hash,
                                        7 - i, 7 - (i + 1));
        if (PASS != __code) {
            return __code;
        }
    }

    *hasher.hash ^= in;

    return crypto_spread_64(*hasher.hash ^ hasher.user_key, hasher.hash);
}

static inline status_code crypto_hash_key(hash_component hasher) {
    if (NULL == hasher.key.address.str ||
        NULL == hasher.key.address.id ||
        NULL == hasher.hash) {
        return EUNDEFINEDBUFFER;
    }

    if (TYPE_ID != hasher.key.type &&
        TYPE_STR != hasher.key.type) {
        return EINCOMPATTYPE;
    }

    // TYPE LONG ID
    if (TYPE_ID == hasher.key.type) {
        return crypto_hash_long(hasher);
    }

    // TYPE_STR
    return crypto_hash_str(hasher);
}

static inline uint64_t crypto_hash_compress(uint64_t hash,
                                     uint64_t limit) {
    // the equivalent of modulus operation
    // finds the remainder of an integer division operation
    return hash - (((uint64_t) (hash/limit)) * limit);
}

/**
 * @brief Hashes a key in a string or long identifier format and
 * then compresses it using modular arithmetics.
 * @details Typical hashing algorithms; include Polynomial hashing
 * for string keys using Horner's Rule, and bytes exchange and random
 * spreading for unsigned long identifiers.
 *
 * @param hasher the hasher component structure with generic pointer.
 * @param limit the limit of the compression algorithm.
 */
static inline status_code crypto_hashkey_compress64(hash_component hasher,
                                             uint64_t limit) {
    status_code __code = crypto_hash_key(hasher);
    if (PASS != __code) {
        return __code;
    }
    *(hasher.hash) = crypto_hash_compress(*(hasher.hash), limit);

    return PASS;
}

#ifdef __cplusplus
};
#endif

#endif