#ifndef __NUM_COMBINATORICS_H_
#define __NUM_COMBINATORICS_H_

#include <stddef.h>
#include <electronetsoft/util/utilities.h>

#ifdef __cplusplus
extern "C" { // disable C++ name mangling by declaring function prototypes
            // a C externally linked space
#endif

/**
 * @brief A permutation or combination of cardinality (r) chosen from
 * the sample space (n).
 */
struct permutation {
    /**
     * The cardinality of the sample space.
     */
    uint64_t n;
    /**
     * The cardinality of the chosen subsets or sequences from
     * the sample space.
     */
    uint64_t r;
    /**
     *
     */
    uint64_t **k;
    /**
     * An executor loader function that executes on each tick.
     */
    status_code (*on_permute_tick)(permutation *const, uint64_t, uint64_t);
    /**
     * A dangling address for the permutation condition;
     * initialized as a default condition based on the
     * type of permutation selected.
     */
    uint8_t (*permutation_condition)(permutation, uint64_t);
    /**
     * A dangling address for the permutation equation;
     * initialized as a default equation based on the
     * type of permutation selected.
     */
    uint64_t (*permutation_equation)(permutation, uint64_t);
    /**
     * The output number of permutations or combinations
     * of cardinality (r) chosen from the sample space (n).
     */
    uint64_t *out;
    /**
     * True if the permutation is a combination (i.e., permutations taken
     * over subsets without regard to the order of elements); false otherwise.
     */
    uint8_t is_combination;

    typed_pointer metadata;
};

status_code combinatorics_n_combine_r(permutation);

/**
 * @brief Permutes sequences of cardinality (r) from
 * a sample space of cardinality (n), and outputs the result
 * into the structure.
 * @details Permutations involves taking sequences of elements from
 * a sample space set respecting the order of elements; such that
 * (ABC) is different from (BCA) and (ACB); unlike combinations, in which
 * case, the order of elements is not regarded.
 * @note To produce the factorial function (n!); let (r = n) and permutate (n) over (n).
 *
 * @param permutation a permutation structure.
 * @return EUNDEFINEDBUFFER if the (out) buffer is not pre-allocated.
 *         EINCOMPATTYPE if the (r) is greater than (n).
 */
status_code combinatorics_n_permute_r(permutation);

// multinomial permutations
status_code combinatorics_multinomial_variant_permute(permutation);

status_code combinatorics_multinomial_variant_permute1v(permutation);

status_code combinatorics_multinomial_exact_permute(permutation);

uint64_t combinatorics_factorial(uint64_t n,
                        status_code (*on_tick)(permutation *const, uint64_t, uint64_t));

#ifdef __cplusplus
};
#endif
#endif