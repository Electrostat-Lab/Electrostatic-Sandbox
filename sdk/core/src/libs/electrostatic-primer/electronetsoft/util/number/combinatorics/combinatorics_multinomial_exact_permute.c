#include <electronetsoft/util/number/combinatorics.h>

status_code combinatorics_multinomial_exact_permute(permutation p) {
    if (NULL == p.k || NULL == p.k[0] || NULL == p.out) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;
    uint64_t sum_k = 0;
    uint64_t p_out = 0;
    uint64_t combination_out = 1;

    permutation __p = {
        .out = &p_out,
        .is_combination = 1,
        .on_permute_tick = p.on_permute_tick,
    };

    for (uint64_t i = 0; p.k[i] != NULL;
                            sum_k += *p.k[i], i++) {
        __p.n = p.n - sum_k;
        __p.r = *p.k[i];
        __code = combinatorics_n_combine_r(__p);
        if (PASS != __code) {
            return __code;
        }
        combination_out *= p_out;
    }

    *p.out = combination_out;

    return PASS;
}