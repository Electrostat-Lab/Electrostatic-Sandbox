#include<electrostatic/electroio/electromio/avr/extint/extint.h>

void extint_enable_isr(const physical_int extint, const uint8_t pin) {
    *(extint.CONTROLr) |= pin;    
    
}