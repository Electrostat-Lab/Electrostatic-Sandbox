#include<electrostatic/electroio/electromio/avr/uart/uart.h>

/**
 * @brief Triggered when the bit UDRE0 is one (the data register buffer is empty and ready to send data).
 */
ISR (USART_UDRE_vect) {
    if (uart_internal_callbacks != NULL && uart_internal_callbacks->on_databuffer_cleared != NULL) {
        uart_internal_callbacks->on_databuffer_cleared();
    }
}

void uart_start_udre_isr() {
    REG_UCSRB |= (1 << BIT_UDRIE);
    /* start the interrupt service handlers */
    sei();
}

void uart_stop_udre_isr() {
    // Finds the 1s complement of all bits in UDRIE0 ---> eg: 0b11111101
    REG_UCSRB &= ~(1 << BIT_UDRIE); 
}
