/**
 * @brief The main header entry for the GPIO drivers. 
 * @author pavl_g.
 * @copyright <a href="https://github.com/Software-Hardware-Codesign/ShiftAvr/blob/master/LICENSE"> GPL-v3.0 </a>
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *       The Avr-Sandbox project, ShiftAvr
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies 
 * of this license document, but changing it is not allowed.
 */
#ifndef _GPIO_H_
#define _GPIO_H_

/* Internal libraries used by [gpio.h]! */
#include <avr/io.h>
#include <avr/interrupt.h>

/* Internal use-only! */
#include <electroio/mio/gpio/port/port.h>
#include <electroio/mio/gpio/port/part/gpiopart.h>

/**
 * @brief Shortcut for PIN on state.
 */
#define ON ((const uint8_t) 0x01)

/**
 * @brief Shortcut for PIN off state.
 */
#define OFF ((const uint8_t) 0x00)

/**
 * @brief Initializes the device GPIO ports by assigning their I/O memory address locations (PORTx, DDRx and PINx).
 */
void gpio_initialize_ports();

/**
 * @brief Configures a port pin as output and toggles its state.
 * 
 * @param port the port to toggle its pin, e.g: {GPIO_PORTB}.
 * @param pin the pin number in the [port] to toggle its state, e.g: {PB5}.
 * @param state the state to assign to this port pin, either [ON] or [OFF].
 */
void gpio_write(const gpio_port port, const uint8_t pin, const uint8_t state);

/**
 * @brief Configures a port pin as input and reads its state with an initial pull-up resistor value. 
 * 
 * @param port the port to read its pin state, e.g: {GPIO_PORTB}.
 * @param pin the pin number in the [port] to read its state, e.g: {PB5}.
 * @param pullupresistor_state the initial pull-up resistor state, either [ON] or [OFF].
 * @return an interrupt-safe 8-bit unsigned integer value representing the PINxn state, where [x] is the 
 *         port and [n] is the address of the input pin on the port input register.
 */
volatile uint8_t gpio_read(const gpio_port port, const uint8_t pin, const uint8_t pullupresistor_state);

/**
 * @brief Reads a port pin state directly without an initial pull-up resistor state.
 * 
 * @param port the port to read its pin state, e.g: {GPIO_PORTB}.
 * @param pin the pin number in the [port] to read its state, e.g: {PB5}.
 * @return an interrupt-safe 8-bit unsigned integer value representing the PINxn state, where [x] is the 
 *         port and [n] is the address of the input pin on the port input register.
 */
volatile uint8_t gpio_fastread(const gpio_port port, const uint8_t pin);

/**
 * @brief Configures a port pin as input and toggles its pull-up state.
 *  
 * @param port the port to toggle its pin pull-up, e.g: {GPIO_PORTB}.
 * @param pin the pin number, e.g: {PB5}.
 * @param pullupresistor_state a pull-up resistor state to assign to the specified port pin.
 */
void gpio_toggle_pin_pullup(const gpio_port port, const uint8_t pin, const uint8_t pullupresistor_state);

/**
 * @brief Toggles the PUD(Pull-up disable) bit.
 * 
 * @param state a state to assign either [ON] or [OFF].
 */
void gpio_toggle_universal_pullup(const uint8_t state);

#endif 
