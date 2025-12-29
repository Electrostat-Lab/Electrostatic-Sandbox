#include <electroio/mio/uart/uart.h>

void uart_sprintln(char* data) {
    uart_sprint(data);
    uart_sprint(NEW_LINE_CARRIAGE_R);
}
