#include <electroio/mio/gpio/gpio.h>

volatile uint8_t gpio_read(const gpio_port port, const uint8_t pin, const uint8_t pullupresistor_state) {
    // setup the port as INPUT with pullup resistor
    gpio_toggle_pin_pullup(port, pin, pullupresistor_state);
    // synchronize read and write operations 
    asm volatile ("nop");

    return *(port.PINx) & (1 << pin);
}