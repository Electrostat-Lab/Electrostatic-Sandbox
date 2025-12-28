#include <electroio/mio/adc/adc.h>

volatile uint16_t adc_read() { 
    volatile uint8_t adcl = ADCL; /* ADCL must be read before ADCH */
    volatile uint8_t adch = ADCH;
    return ((0x00 | adch) << 8) | adcl; /* concatenate the 2 (8-bit registers) in a 16-bit software register */
}
