#include <electrostatic/algorithm/arithmos/algebra/switching.h>
#include <stdlib.h>

uint8_t switching_xor(SWITCHING_TYPE **inputs, SWITCHING_TYPE *output){
    if (inputs == NULL || output == NULL) {
        return 1;
    }
    for (int i = 0; inputs[i] != NULL; i++) {
        SWITCHING_TYPE prop0 = *output;
        SWITCHING_TYPE prop1 = *(inputs[i]);
        // XOR Propositional operation break-down
        *output = ((!prop0) & prop1) | (prop0 & (!prop1));
        //
        // Example:
        // 0 ^ 1 ^ 1 = 0
        // -- break down -- 
        // 1. [(!(0) & 1) | (0 & !(1)] = 1
        // 2. [!(1) & 1) | (1 & !(1)] = 0
        //
        // XOR Function: Tests whether 2 binary sets are mutually exclusive
        // return 1 if the predicate holds, 0 otherwise.
        //
        // Note: If the negation of set A can intersect with set B OR the negation
        // of set B can intersect with set A; then, both sets are mutually exclusive.
        //
        // Note: This operates ONLY on binary sets (a set composed of only 0 or 1).
        //
    }
    return 0;
}