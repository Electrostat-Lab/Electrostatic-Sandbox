#include <electroio/mio/gpio/gpio.h>

void gpio_toggle_pin_pullup(const gpio_port port, const uint8_t pin, const uint8_t pullupresistor_state) {
    // setup the port as INPUT
    *(port.DDRx) &= ~(1 << pin);
    // overwrite the pull-up resistor state at this pin 
    const volatile uint8_t PORTxn_DISABLED = (*(port.PORTx) & ~(1 << pin));
    const volatile uint8_t PINxn_STATE = (pullupresistor_state && 0xFF) << pin;
    *(port.PORTx) = PORTxn_DISABLED | PINxn_STATE;
}