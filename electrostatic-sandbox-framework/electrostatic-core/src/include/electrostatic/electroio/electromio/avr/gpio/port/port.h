/**
 * @brief Defines the data structure for shift-avr port memory address locations system.
 * @note Three I/O memory address locations are allocated for each port, one each for the data register – PORTx, data direction
 *       register – DDRx, and the port input pins – PINx.
 * @author pavl_g.
 * @copyright <a href="https://github.com/Software-Hardware-Codesign/ShiftAvr/blob/master/LICENSE"> GPL-v3.0 </a>
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *       The Avr-Sandbox project, ShiftAvr
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies 
 * of this license document, but changing it is not allowed.
 */
#ifndef _GPIO_H_
#   error "The <electrostatic/electroio/electromio/avr/gpio/port/port.h> header is an internal property, include <gpio/gpio.h> instead of this!"
#endif

#ifndef _GPIO_PORT_H_
#define _GPIO_PORT_H_

/**
 * @brief Defines a GPIO port with 3 I/O memory address locations, PORTx, DDRx and PINx.
 */
typedef struct {
    /**
     * @brief The memory address location for the data register [PORTx].
     */
    volatile uint8_t* PORTx;
    
    /**
     * @brief The memory address location for the data direction register [DDRx].
     */
    volatile uint8_t* DDRx;
    
    /**
     * @brief The memory address location for the port inputs register [PINx].
     */
    volatile uint8_t* PINx;
} gpio_port;

#endif