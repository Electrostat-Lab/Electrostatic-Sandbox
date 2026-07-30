#include <stdio.h>
#include <stdlib.h>
#include <electronetsoft/util/number/crypto.h>

int main() {
    uint64_t hash = 0;
    hash_component component = {
         .key = (typed_pointer) {
             .address.str = "message_test_11",
             .type = TYPE_STR,
         },
         .user_key = (1024 << 8) + 1,
         .hash = &hash
    };
    status_code __code = crypto_hash_key(component);
    if (PASS != __code) {
        fprintf(stderr,
                "Failed to hash the key; exit with error = %d\n", __code);
        return __code;
    }

    fprintf(stdout, "%lu\n", hash);
    fprintf(stdout, "%lu\n", crypto_hash_compress(hash, 201));
    return 0;
}