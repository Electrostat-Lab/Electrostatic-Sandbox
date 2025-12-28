/**
 * @brief An example showing data transmission and data receive using UART.
 * @author pavl_g.
 * @copyright <a href="https://github.com/Software-Hardware-Codesign/ShiftAvr/blob/master/LICENSE"> GPL-v3.0 </a>
 * GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007
 *       The Avr-Sandbox project, ShiftAvr
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies 
 * of this license document, but changing it is not allowed.
 */
#define F_CPU 16000000UL
#include <electrostatic/electroio/electromio/avr/uart/uart.h>

void on_protocol_started() {
}

void on_protocol_stopped() {
}

void on_data_received(const uint8_t datum) {
    uart_cprint(datum);
    uart_start_transmitter_isr();
    uart_start_udre_isr();
}

void on_data_transmitted(const uint8_t datum) {
    uart_stop_transmitter_isr();
    uart_start_udre_isr();
}

void on_databuffer_cleared() {
    uart_stop_udre_isr();
}

/**
 * @note volatile: marks this object as an interrupt-safe adjustable. 
 */
volatile uart_callbacks _uart_callbacks = {
    on_protocol_started,
    on_protocol_stopped,
    on_data_received,
    on_data_transmitted,
    on_databuffer_cleared
};

int main() {
    /* assigns api callbacks */
    uart_assign_callbacks(&_uart_callbacks);
    /* start the protocol first to enable TX and RX and set BAUD! */
    uart_start_protocol(get_baud_1x_value(F_CPU, 57600));
    /* starting the ISR should be after starting the protocol! i.e, after enabling RX and TX! */
    uart_start_udre_isr();
    uart_start_receiver_isr();
    uart_start_transmitter_isr();

    while (1); /* Running forever! */
    return 0;
}
