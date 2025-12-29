#include <electroio/mio/uart/uart.h>

void uart_start_protocol(const uint32_t BAUD_RATE_VAL) {
    REG_UCSRC = 0x00;
    REG_UBRRH = (uint8_t) (BAUD_RATE_VAL >> 8);
    REG_UBRRL = (uint8_t) BAUD_RATE_VAL;

    REG_UCSRB = (1 << BIT_TXEN) | (1 << BIT_RXEN); /* enable the transmit and receiver buffers */
    REG_UCSRC = (1 << BIT_URSEL) | (1 << BIT_USBS) | (3 << BIT_UCSZ0); // enables the UCSZ0, UCSZ1 and URSEL

    if (uart_internal_callbacks != NULL && uart_internal_callbacks->on_protocol_started != NULL) {
        uart_internal_callbacks->on_protocol_started();
    }
}
