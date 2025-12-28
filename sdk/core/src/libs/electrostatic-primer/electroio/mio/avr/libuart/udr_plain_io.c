#include <electroio/mio/uart/uart.h>

volatile uint8_t uart_poll_read_ascii() {
    while (!(REG_UCSRA & (1 << BIT_RXC)));
    return REG_UDR;
}
