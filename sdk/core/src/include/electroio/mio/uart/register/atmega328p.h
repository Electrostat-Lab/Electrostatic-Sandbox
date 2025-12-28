/**
 * @brief Defines USART registers for ATmega328p MCU. 
 * @author pavl_g
 * @copyright <a href="https://github.com/Software-Hardware-Codesign/ShiftAvr/blob/master/LICENSE"> GPL-v3.0 </a>
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *       The Avr-Sandbox project, ShiftAvr
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies 
 * of this license document, but changing it is not allowed.
 * 
 */
#ifndef _ATMEGA_328p_H
#define _ATMEGA_328p_H

/** UCSRA register */
#define REG_UCSRA UCSR0A
#define BIT_RXC RXC0
#define BIT_TXC TXC0
#define BIT_UDRE UDRE0 
#define BIT_FE FE0 
#define BIT_PE PE0 
#define BIT_U2X U2X0 
#define BIT_MPCM MPCM0

/** UCSRB register */
#define REG_UCSRB UCSR0B
#define BIT_RXCIE RXCIE0
#define BIT_TXCIE TXCIE0
#define BIT_UDRIE UDRIE0
#define BIT_RXEN RXEN0
#define BIT_TXEN TXEN0
#define BIT_UCSZ2 UCSZ02
#define BIT_RXB8 RXB80
#define BIT_TXB8 TXB80

/** UCSRC register */
#define REG_UCSRC UCSR0C 
#define BIT_URSEL 0
#define BIT_UMSEL UMSEL0 
#define BIT_UPM0  UPM00 
#define BIT_UPM1  UPM01
#define BIT_USBS  USBS0
#define BIT_UCSZ0 UCSZ00
#define BIT_UCSZ1 UCSZ01
#define BIT_UCPOL UCPOL0

#define REG_UBRR UBRR0

/** UBRRL register */
#define REG_UBRRL UBRR0L

/** UBRRH register */
#define REG_UBRRH UBRR0H

/** UDR register */
#define REG_UDR UDR0

#define __vector_USART_RX USART_RX_vect
#define __vector_USART_TX USART_TX_vect

#endif
