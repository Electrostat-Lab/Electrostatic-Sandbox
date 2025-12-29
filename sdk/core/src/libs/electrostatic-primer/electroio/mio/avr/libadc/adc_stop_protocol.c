#include <electroio/mio/adc/adc.h>

void adc_stop_protocol() {
    ADCH = 0x00;
    ADCL = 0x00;
    ADCSRA = 0x00; /* format the control status register A including the [ADEN] bit */
    if (adc_internal_callbacks != NULL && adc_internal_callbacks->adc_on_stop_protocol != NULL) {
        adc_internal_callbacks->adc_on_stop_protocol();
    }
}

