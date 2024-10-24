#include <electrostatic/electronetsoft/algorithm/arithmos/algebra/switching.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static inline double get_len0(void ***buffer) {
    if (buffer == NULL) {
        return -1;
    }
    double len = 0;
    for (int i = 0; buffer[i] != NULL; i++) {
        len += 1;
    }
    return len;
}

static inline double get_len(void **buffer) {
    if (buffer == NULL) {
        return -1;
    }
    double len = 0;
    for (int i = 0; buffer[i] != NULL; i++) {
        len += 1;
    }
    return len;
}

static inline uint8_t no_swithcing(SWITCHING_TYPE input, SWITCHING_TYPE *output) {
    *output = input;
    return 0;
}

uint8_t switching_multiplex(SWITCHING_TYPE **inputs, SWITCHING_TYPE *output, SWITCHING_TYPE **selects, struct switching_filter ***filters) {
    if (output == NULL) {
        printf("issue - 0");
        return 1;
    }
    
    // 1) Asserting compatibility between the number of bits in the input component and the line-select component
    double len_input = get_len((void **) inputs);
    double len_select = get_len((void **) selects);
    double len_filter = get_len0((void ***) filters);
    double _len_filter = get_len((void **) *filters);
    if ((log2(len_input) != len_select) || len_filter != len_input || _len_filter != len_select) {
        return 1;
    }
    // for all inputs
    // 2) Selecting the input line by ANDing the input lines with filtered Select lines
    *output = 0;
    for (int i = 0; i < len_input; i++) { // for all the input lines
        for (int j = 0; j < len_select // for all the select lines
                       && init_switching_filter(filters[i][j]) != 1; j++) { // 3) initialize the filters according to their type
            SWITCHING_TYPE local = 0;
            int state = filters[i][j]->filter(*(selects[j]), &local); // 4) apply the circuit filter to the select
                                                                     // lines
            // add logging here!

            *(inputs[i]) = *(inputs[i]) && local; // 5) the rest of the internal circuitry of the MUX follows
        }
        // add logging here!
        *output = *output || *(inputs[i]); // 6) final filter
    }
    
    return 0;
}

uint8_t init_switching_filter(switching_filter *filter) {
    if (filter == NULL) {
        return 1;
    } else if (filter != NULL && filter->filter != NULL) {
        return 0;
    }
    if (filter->type == NOT_GATE) {
        filter->filter = switching_not;
    } else {
        filter->filter = no_swithcing;
    }
    return 0;
}