#include <electronetsoft/util/number/combinatorics.h>

// Pseudocode Hypothesis:
// Loop k-buffer (k) {
//        for (i = 0 to k; (k - i) >= 1) {
//            n = k - i;
//            p = fact(n)
//            for (j = 0 to r; n < r) {
//                n1 = (r - n) - j
//                p *= fact(n1)
//                n += n1
//            }
//            intersum += fact(r)/p
//        }
//        majorsum += intersum
//        intersum = 0
//}
status_code combinatorics_multinomial_variant_permute(permutation p) {
    if (NULL == p.k || NULL == p.k[0] || NULL == p.out) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;
    uint64_t p_out = 0;

    uint64_t inter_sum = 0;
    uint64_t major_sum = 0;

    uint64_t r_factorial = combinatorics_factorial(p.r, NULL);

    for (uint64_t i = 0; p.k[i] != NULL; i++) {
        // variance calculation (i.e., k_0 <= a_0 and so on; so
        // the number of items tested is from k_0 to a_0 typically
        // of (a_0 - k_0) length
        for (uint64_t _k = 0, _r = 0;
                (*p.k[i] - _k) >= 1; _k++) {

            _r = *p.k[i] - _k;
             p_out = combinatorics_factorial(_r, NULL);

             for (uint64_t __k = 0, __r = 0;
                        NULL != p.k[__k] && _r < p.r; __k++) {

                __r = (p.r - _r) - __k;
                // bounding by maxima
                if (__r > *p.k[__k]) {
                    __r = *p.k[__k];
                }
                p_out *= combinatorics_factorial(__r, NULL);
                _r += __r;
            }
            inter_sum += (r_factorial / p_out);
        }

        major_sum += inter_sum;
        inter_sum = 0;
        if (NULL != p.on_permute_tick) {
            p.on_permute_tick(&p, major_sum, i);
        }
    }
    *p.out = major_sum;

    return PASS;
}