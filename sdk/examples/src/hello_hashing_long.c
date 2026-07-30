#include <stdio.h>
#include <stdlib.h>
#include <electronetsoft/util/number/crypto.h>

int main() {
    uint64_t hash = 2131112;
    status_code __code = crypto_hashkey_compress64(
            (hash_component ) {
                .key = (typed_pointer) {
                    .address.id = &hash,
                    .type = TYPE_ID
                },
                .user_key = (UINT16_MAX << 8) | (UINT16_MAX >> 8),
                .hash = &hash
            }, 900);
    if (PASS != __code) {
        fprintf(stderr, "Error while hashing = %d\n", __code);
        return __code;
    }

    fprintf(stdout, "Hashed Key = %lul\n", hash);
    return 0;
}