/**
 * @brief Defines GPIO ports for ATMega328p.
 * @author pavl_g.
 * @copyright <a href="https://github.com/Software-Hardware-Codesign/ShiftAvr/blob/master/LICENSE"> GPL-v3.0 </a>
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *       The Avr-Sandbox project, ShiftAvr
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies 
 * of this license document, but changing it is not allowed.
 */
#ifndef _GPIO_H_
#   error "The <electrostatic/electroio/electromio/avr/gpio/port/part/part-m328p.h> header is an internal property, include <gpio/gpio.h> instead of this!"
#endif

#ifndef _GPIO_PORT_PART_ATMEGA328P_H_
#define _GPIO_PORT_PART_ATMEGA328P_H_

#include <avr/io.h>
#include <electrostatic/electroio/electromio/avr/gpio/port/port.h>

/**
 * @brief A common Microcontroller-unit-control register alias to control PUD(Pull-Up-Disable) state.
 */
#define GPIO_MCUCR MCUCR

/**
 * @brief Prototype for PORTB registers I/O memory addresses.
 */
gpio_port GPIO_PORTB;

/**
 * @brief Prototype for PORTC registers I/O memory addresses.
 */
gpio_port GPIO_PORTC;

/**
 * @brief Prototype for PORTD registers I/O memory addresses.
 */
gpio_port GPIO_PORTD;

#endif 