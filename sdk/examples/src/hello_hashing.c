#include <stdio.h>
#include <stdlib.h>
#include <electronetsoft/util/utilities.h>

int main() {
    const char *key = "test_message_11";
    uint64_t hash = 0;
    hash_key(key, &hash, (1024 << 8) + 1);

    fprintf(stdout, "%lu\n", hash);
    fprintf(stdout, "%lu\n", hash_compress(hash, 201));
    return 0;
}