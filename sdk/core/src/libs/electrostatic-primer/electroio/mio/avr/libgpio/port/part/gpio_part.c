#include <electroio/mio/gpio/gpio.h>

void gpio_initialize_ports() {
    #if defined (__AVR_ATmega32__)
        /* assign PORTx addresses */
        GPIO_PORTA.PORTx = &PORTA;
        GPIO_PORTA.DDRx = &DDRA;
        GPIO_PORTA.PINx = &PINA;

        GPIO_PORTB.PORTx = &PORTB;
        GPIO_PORTB.DDRx = &DDRB;
        GPIO_PORTB.PINx = &PINB;

        GPIO_PORTC.PORTx = &PORTC;
        GPIO_PORTC.DDRx = &DDRC;
        GPIO_PORTC.PINx = &PINC;

        GPIO_PORTD.PORTx = &PORTD;
        GPIO_PORTD.DDRx = &DDRD;
        GPIO_PORTD.PINx = &PIND;
        
    #elif defined (__AVR_ATmega328P__)
        /* assign PORTx addresses */
        GPIO_PORTB.PORTx = &PORTB;
        GPIO_PORTB.DDRx = &DDRB;
        GPIO_PORTB.PINx = &PINB;

        GPIO_PORTC.PORTx = &PORTC;
        GPIO_PORTC.DDRx = &DDRC;
        GPIO_PORTC.PINx = &PINC;

        GPIO_PORTD.PORTx = &PORTD;
        GPIO_PORTD.DDRx = &DDRD;
        GPIO_PORTD.PINx = &PIND;
    #endif
}