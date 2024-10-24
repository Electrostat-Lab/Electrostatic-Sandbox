#include<electrostatic/electroio/electromio/avr/uart/uart.h>

/**
 * @brief Triggered when the bit TXC is settled and the data transmission has been completed.
 */
ISR (__vector_USART_TX) {
    if (uart_internal_callbacks != NULL && uart_internal_callbacks->on_data_transmission_completed != NULL) {
        uart_internal_callbacks->on_data_transmission_completed((const uint8_t) REG_UDR);
    }
}

void uart_start_transmitter_isr() {
    REG_UCSRB |= (1 << BIT_TXCIE);
    /* start the interrupt service handlers */
    sei();
}

void uart_stop_transmitter_isr() {
    // Finds the 1s complement of all bits in RXCIE0 ---> eg: 0b11111101
    REG_UCSRB &= ~(1 << BIT_TXCIE); 
}
