/**
 * @brief An example showing a dirty switch processor which reads the state on PB2 and apply it
 *        on PB5 on PORTB.
 * @author pavl_g.
 * @copyright <a href="https://github.com/Software-Hardware-Codesign/ShiftAvr/blob/master/LICENSE"> GPL-v3.0 </a>
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *       The Avr-Sandbox project, ShiftAvr
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies 
 * of this license document, but changing it is not allowed.
 */
#define F_CPU 16000000UL
#include <electrostatic/electroio/electromio/avr/gpio/gpio.h>
#include <util/delay.h>

int main() {
    /* assigns port addresses */
    gpio_initialize_ports();
    while (0xFF) {
        /* reads gpio PB2 Pin with initial Pull-up [OFF] state */
        const uint8_t state = gpio_read(GPIO_PORTB, PB2, OFF);
        /* assigns the output state to bit PB5 in PORTB data register */
        gpio_write(GPIO_PORTB, PB5, state);
    }
    return 0;
}