#include<electrostatic/electroio/electromio/avr/uart/uart.h>

void uart_println(const int64_t data, const uint8_t base) {
    uart_print(data, base);
    uart_sprint(NEW_LINE_CARRIAGE_R);
}
