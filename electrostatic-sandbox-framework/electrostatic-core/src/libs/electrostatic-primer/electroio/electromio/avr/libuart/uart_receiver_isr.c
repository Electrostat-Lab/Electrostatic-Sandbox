#include<electrostatic/electroio/electromio/avr/uart/uart.h>

/**
 * @brief Triggered when the RXC0 is settled and the receiving has been completed.
 */
ISR (__vector_USART_RX) {
    if (uart_internal_callbacks != NULL && uart_internal_callbacks->on_data_receive_completed != NULL) {
        uart_internal_callbacks->on_data_receive_completed((const uint8_t) REG_UDR);
    }
}

void uart_start_receiver_isr() {
    REG_UCSRB |= (1 << BIT_RXCIE);
    /* start the interrupt service handlers */
    sei();
}

void uart_stop_receiver_isr() {
    // Finds the 1s complement of all bits in RXCIE0 ---> eg: 0b11111101
    REG_UCSRB &= ~(1 << BIT_RXCIE); 
}
