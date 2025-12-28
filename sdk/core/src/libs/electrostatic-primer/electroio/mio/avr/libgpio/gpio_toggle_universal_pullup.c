#include <electroio/mio/gpio/gpio.h>

void gpio_toggle_universal_pullup(const uint8_t state) {
    // flip the state and assign it to the pull-up disable bit on the MCUCR
    GPIO_MCUCR |= ((1 << PUD) & ~state);
}