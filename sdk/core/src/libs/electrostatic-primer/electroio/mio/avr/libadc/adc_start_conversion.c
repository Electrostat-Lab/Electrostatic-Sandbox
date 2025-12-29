#include <electroio/mio/adc/adc.h>

void adc_start_conversion(const uint8_t PIN, const uint8_t V_REF, const uint8_t CONVERSION_SPEED) {
    /* setup ADMUX */
    ADCSRA |= CONVERSION_SPEED;
    ADMUX = V_REF | PIN; 
    ADCSRA |= (1 << ADSC); /* the last step: start conversion */
    
    if (adc_internal_callbacks != NULL && adc_internal_callbacks->adc_on_start_conversion != NULL) {
        adc_internal_callbacks->adc_on_start_conversion();
    }
}
