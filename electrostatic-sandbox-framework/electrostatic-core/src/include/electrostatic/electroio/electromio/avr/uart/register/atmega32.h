/**
 * @brief Defines USART registers for ATmega32 MCU. 
 * @author pavl_g
 * @copyright <a href="https://github.com/Software-Hardware-Codesign/ShiftAvr/blob/master/LICENSE"> GPL-v3.0 </a>
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *       The Avr-Sandbox project, ShiftAvr
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies 
 * of this license document, but changing it is not allowed.
 */
#ifndef _ATMEGA_32_H
#define _ATMEGA_32_H

/** UCSRA register */
#define REG_UCSRA UCSRA
#define BIT_RXC RXC
#define BIT_TXC TXC
#define BIT_UDRE UDRE 
#define BIT_FE FE 
#define BIT_PE PE 
#define BIT_U2X U2X 
#define BIT_MPCM MPCM

/** UCSRB register */
#define REG_UCSRB UCSRB
#define BIT_RXCIE RXCIE
#define BIT_TXCIE TXCIE
#define BIT_UDRIE UDRIE
#define BIT_RXEN RXEN
#define BIT_TXEN TXEN
#define BIT_UCSZ2 UCSZ2
#define BIT_RXB8 RXB8
#define BIT_TXB8 TXB8

/** UCSRC register */
#define REG_UCSRC UCSRC 
#define BIT_URSEL URSEL 
#define BIT_UMSEL UMSEL 
#define BIT_UPM0  UPM0 
#define BIT_UPM1  UPM1
#define BIT_USBS  USBS
#define BIT_UCSZ0 UCSZ0
#define BIT_UCSZ1 UCSZ1
#define BIT_UCPOL UCPOL

/** UBRRL register */
#define REG_UBRRL UBRRL

/** UBRRH register */
#define REG_UBRRH UBRRH

/** UDR register */
#define REG_UDR UDR

#define __vector_USART_RX USART_RXC_vect
#define __vector_USART_TX USART_TXC_vect

#endif
