#include <electronetsoft/util/number/combinatorics.h>

uint64_t combinatorics_factorial(uint64_t n,
                                status_code (*on_tick)(permutation *const, uint64_t, uint64_t)) {
    uint64_t p_out = 0;
    permutation p = {
            .is_combination = 0,
            .r = n,
            .n = n,
            .k = 0,
            .out = &p_out,
            .on_permute_tick = on_tick
    };
    status_code __code = combinatorics_n_permute_r(p);
    if (PASS != __code) {
        return __code;
    }
    return p_out;
}