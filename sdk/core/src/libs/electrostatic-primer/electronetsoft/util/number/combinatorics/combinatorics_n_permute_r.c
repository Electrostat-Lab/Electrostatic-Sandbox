#include <electronetsoft/util/number/combinatorics.h>

static inline uint64_t combinatorics_permutation_equation(permutation p, uint64_t i) {
    return (p.n - i);
}

static inline uint8_t combinatorics_permutation_condition(permutation p, uint64_t i) {
    return combinatorics_permutation_equation(p, i) >=
                combinatorics_permutation_equation(p, (p.r - 1));
}

status_code combinatorics_n_permute_r(permutation p) {
    if (NULL == p.out) {
        return EUNDEFINEDBUFFER;
    }

    if (p.r > p.n || p.r < 1) {
        return EINCOMPATTYPE;
    }

    if (NULL == p.permutation_condition) {
        p.permutation_condition = &combinatorics_permutation_condition;
    }

    if (NULL == p.permutation_equation) {
        p.permutation_equation = &combinatorics_permutation_equation;
    }

    if (p.permutation_equation == &combinatorics_permutation_equation &&
        p.permutation_condition == &combinatorics_permutation_condition) {
        p.is_combination = 0;
    }

    status_code __code;
    *(p.out) = 1;

    for (uint64_t i = 0; p.permutation_condition(p, i); i++) {
        *(p.out) *= p.permutation_equation(p, i);
        if (NULL != p.on_permute_tick) {
            __code = p.on_permute_tick(&p, p.permutation_equation(p, i), i);
            if (PASS != __code) {
                return __code;
            }
        }
    }

    return PASS;
}