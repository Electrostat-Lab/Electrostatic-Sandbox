/**
 * @file start.c
 * @author pavl_g.
 * @brief An implementation for the [Analog.h] header file.
 * @version 0.1
 * @date 2022-07-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <electroio/mio/adc/adc.h>

void adc_start_protocol() {
    /* setup ADCSRA */
    ADCSRA = (1 << ADEN) /*enable adc protocol*/; 

    if (adc_internal_callbacks != NULL && adc_internal_callbacks->adc_on_start_protocol != NULL) {
        adc_internal_callbacks->adc_on_start_protocol();
    }
}
