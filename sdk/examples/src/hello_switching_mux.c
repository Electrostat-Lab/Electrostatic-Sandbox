#include <electronetsoft/arithmos/algebra/switching.h>
#include <stdio.h>
#include <stdlib.h>

switching_filter not_filter = {
    .type = NOT_GATE  
};

switching_filter no_filter = {
    .type = NO_FILTER  
};

SWITCHING_TYPE select_0 = 1;
SWITCHING_TYPE select_1 = 0;

SWITCHING_TYPE input_0 = 0;
SWITCHING_TYPE input_1 = 1;
SWITCHING_TYPE input_2 = 1;
SWITCHING_TYPE input_3 = 1;

SWITCHING_TYPE output = 0;

int main() {
    
    switching_filter ***_filters = (switching_filter ***) calloc(4, sizeof(switching_filter ***));
    
    switching_filter *filter_0[] = {&not_filter, &not_filter, NULL};
    _filters[0] = (switching_filter **) filter_0;
    
    switching_filter *filter_1[] = {&no_filter, &not_filter, NULL};
    _filters[1] = (switching_filter **) filter_1;
    
    switching_filter *filter_2[] = {&not_filter, &no_filter, NULL};
    _filters[2] = (switching_filter **) filter_2;
    
    switching_filter *filter_3[] = {&no_filter, &no_filter, NULL};
    _filters[3] = (switching_filter **) filter_3;
    
    _filters[4] = NULL;
    
    SWITCHING_TYPE *_selects[] = {&select_0, &select_1, NULL};
    SWITCHING_TYPE *_inputs[] = {&input_0, &input_1, &input_2, &input_3, NULL};

    int state = switching_multiplex(_inputs, &output, _selects, _filters);
    
    if (state != 0) {
        return -1;
    }
    
    printf("Switching Output = %d\n", output);
    
    free(_filters);
    
    return 0;
}