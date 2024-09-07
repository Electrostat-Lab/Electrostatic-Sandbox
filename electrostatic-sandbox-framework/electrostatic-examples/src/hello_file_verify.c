#include <stdio.h>
#include <electrostatic/util/filesystem/file_verify.h>

int main() {
    while (1) {
        if (is_existential("/dev/ttyUSB0")) {
            printf("Serial Device Exists!\n");
            break;
        }
        printf("Assert file existence %i\n", is_existential("/dev/ttyUSB0"));
    }
    return 0;
}