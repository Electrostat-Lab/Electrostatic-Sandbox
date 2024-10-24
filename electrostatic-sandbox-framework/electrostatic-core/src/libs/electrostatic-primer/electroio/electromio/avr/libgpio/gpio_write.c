#include<electrostatic/electroio/electromio/avr/gpio/gpio.h>

void gpio_write(const gpio_port port, const uint8_t pin, uint8_t state) {
    *(port.DDRx) |= (1 << pin);
    /* Recall, PORTx = 0b01100000
       And, we want to change PINx4 to one
       Then, 1) Disable PORTxn first, through [(*(port.PORTx) & (~(1 << pin))].
             2) Add a state to PINxn, through [state << pin].
             3) Apply the PINxn_STATE to the PORT via [PORTxn_DISABLED | PINxn_STATE].
             4) Add the pin state to the PORT via [PORTxn_DISABLED | PINxn_STATE].
       So, PORTx = (0b01100000 & 0b11101111) | ((0b00010000) & (0b11111111)) 
                 = 0b01100000 | 0b00010000 = 0b01110000 */
    const volatile uint8_t PORTxn_DISABLED = (*(port.PORTx) & ~(1 << pin));
    const volatile uint8_t PINxn_STATE = (state && 0xFF) << pin;
    *(port.PORTx) = PORTxn_DISABLED | PINxn_STATE;
} 