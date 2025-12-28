/**
 * @brief Defines dependent GPIO registers.
 * @author pavl_g.
 * @copyright <a href="https://github.com/Software-Hardware-Codesign/ShiftAvr/blob/master/LICENSE"> GPL-v3.0 </a>
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *       The Avr-Sandbox project, ShiftAvr
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies 
 * of this license document, but changing it is not allowed.
 */
#ifndef _GPIO_H_
#   error "The <gpio/port/part/gpiopart.h> header is an internal property, include <gpio/gpio.h> instead of this!"
#endif

#ifndef _GPIO_PART_H_
#define _GPIO_PART_H_

#if defined (__AVR_ATmega32__)
#  include <electroio/mio/gpio/port/part/part-m32.h>
#elif defined (__AVR_ATmega328P__)
#  include <electroio/mio/gpio/port/part/part-m328p.h>
#endif

#endif