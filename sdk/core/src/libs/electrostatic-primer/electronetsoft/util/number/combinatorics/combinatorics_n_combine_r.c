#include <electronetsoft/util/number/combinatorics.h>

static inline status_code on_permute_tick(permutation *const p,
                                          uint64_t intermediate,
                                          uint64_t i) {
    *p->out /= (i + 1);
    permutation *c = p->metadata.address.m_permutation;
    if (NULL != c && NULL != c->on_permute_tick) {
        status_code __code = c->on_permute_tick(c, intermediate, i);
        if (PASS != __code) {
            return __code;
        }
    }
    return PASS;
}

status_code combinatorics_n_combine_r(permutation c) {
    c.is_combination = 1;

    // deep copy the permutation structure
    permutation p = {
        .r = c.r,
        .n = c.n,
        .out = c.out,
        .on_permute_tick = &on_permute_tick,
        .metadata = (typed_pointer) {
            .address.m_permutation = &c,
            .type = TYPE_PERMUTATION
        }
    };

    status_code __code = combinatorics_n_permute_r(p);
    if (PASS != __code) {
        return __code;
    }

    return PASS;
}
