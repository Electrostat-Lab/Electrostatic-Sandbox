#include <electroio/mio/uart/uart.h>

void uart_stop_protocol() {
    REG_UCSRB = 0x00; 
    if (uart_internal_callbacks != NULL && uart_internal_callbacks->on_protocol_stopped != NULL) {
        uart_internal_callbacks->on_protocol_stopped();
    }
}
