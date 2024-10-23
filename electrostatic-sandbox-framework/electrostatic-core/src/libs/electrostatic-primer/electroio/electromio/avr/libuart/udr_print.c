#include<electrostatic/electroio/electromio/avr/uart/uart.h>

void uart_print(const int64_t data, const uint8_t base) {
    char* str = allocate_buffer();
    // convert input to string
    itoa(data, str, base);
    for (int i = 0; i < strlen(str); i++) {
        uart_cprint(str[i]);
    }
    free(str);
}
