#include <electronetsoft/util/number/decimal.h>
#include <electronetsoft/util/number/crypto.h>
#include <stdio.h>
#include <time.h>

int main() {

    uint64_t k = 0;
    uint64_t rand = 0;
    linear_congruent_seq lcs = {
        .initial_value = 50,
        .modulus = 200,
        .rand = &rand,
        .k = &k
    };

    status_code __code;

    for (int i = 0; i < 20; i++) {
        __code = dec_clock_lcg_random(&lcs);
        if (PASS != __code) {
            fprintf(stdout, "Failed with error code = %d\n", __code);
            return __code;
        }

        fprintf(stdout, "The random number = %ld, %lu\n", clock(), *lcs.rand);
    }

    return 0;
}