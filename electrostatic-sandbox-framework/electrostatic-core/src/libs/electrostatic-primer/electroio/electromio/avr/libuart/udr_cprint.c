#include<electrostatic/electroio/electromio/avr/uart/uart.h>

void uart_cprint(char data) {
    while (!(REG_UCSRA & (1 << BIT_UDRE)));
    REG_UDR = data;
}
