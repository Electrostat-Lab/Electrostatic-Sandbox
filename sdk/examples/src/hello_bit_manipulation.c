#include <stdio.h>
#include <electronetsoft/util/number/bitwise.h>

int main() {
    uint64_t value = 0b00000000000000000000000011111111;
    fprintf(stdout, "PRINT %lu\n", value);
    status_code __code = bitwise_push_byte(0x00,
                                      (uint64_t *) &value, 0);
    if (PASS != __code) {
        fprintf(stderr, "ERROR %d\n", __code);
    }
    fprintf(stdout, "PRINT %lu\n", value);
    return 0;
}