#include<electrostatic/electroio/electromio/avr/uart/uart.h>

void uart_cprintln(char data) {
    uart_cprint(data);
    uart_sprint(NEW_LINE_CARRIAGE_R);
}
