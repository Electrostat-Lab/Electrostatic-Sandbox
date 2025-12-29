#include <electroio/mio/uart/uart.h>

void uart_sprint(char* data) {
    int i = 0;
    while (i < strlen(data)) {
        uart_cprint(data[i++]);
    }
}
