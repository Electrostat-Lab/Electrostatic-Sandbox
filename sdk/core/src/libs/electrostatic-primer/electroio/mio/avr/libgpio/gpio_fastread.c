#include <electroio/mio/gpio/gpio.h>

volatile uint8_t gpio_fastread(const gpio_port port, const uint8_t pin) {
    return *(port.PINx) & (1 << pin);
}
