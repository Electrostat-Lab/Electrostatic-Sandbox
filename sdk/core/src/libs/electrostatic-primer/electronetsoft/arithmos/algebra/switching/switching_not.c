#include <electronetsoft/arithmos/algebra/switching.h>

uint8_t switching_not(SWITCHING_TYPE input, SWITCHING_TYPE *output) {
    if (output == NULL) {
        return 1;
    }
    *output = !input;
    return 0;
}
