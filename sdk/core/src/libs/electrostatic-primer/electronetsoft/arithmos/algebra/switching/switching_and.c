#include <electronetsoft/arithmos/algebra/switching.h>
#include <stdlib.h>

uint8_t switching_and(SWITCHING_TYPE **inputs, SWITCHING_TYPE *output){
    if (inputs == NULL || output == NULL) {
        return 1;
    }
    for (int i = 0; inputs[i] != NULL; i++) {
        *output &= *(inputs[i]);
    }
    return 0;
}