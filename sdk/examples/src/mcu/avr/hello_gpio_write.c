/**
 * @brief An example showing a blink on PB5-PORTB.
 * @author pavl_g.
 * @copyright <a href="https://github.com/Software-Hardware-Codesign/ShiftAvr/blob/master/LICENSE"> GPL-v3.0 </a>
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *       The Avr-Sandbox project, ShiftAvr
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies 
 * of this license document, but changing it is not allowed.
 */
#define F_CPU 16000000UL
#include <electroio/mio/gpio/gpio.h>
#include <util/delay.h>

int main() {
    /* assigns the digital port addresses */
    gpio_initialize_ports();
    while (0xFF) {
        /* writes 1 to bit.5 on PORTB data register */
        gpio_write(GPIO_PORTB, PB5, ON);
        _delay_ms(500);
        /* writes 0 to bit.5 on PORTB data register */
        gpio_write(GPIO_PORTB, PB5, OFF);
        _delay_ms(500);
    }
    return 0;
}