/**
 * @file adc.h.
 * @author pavl_g.
 * @brief Operates and controls the ADC protocol through the ADC mulitplexers and status control registers.
 * @version 0.1
 * @date 2022-07-04
 * 
 * @copyright The AVR-Sandbox Project, Copyright (c) 2022
 */
#ifndef _ADC_H
#define _ADC_H 

/* Internal libraries used by [adc.h]! */
#include<avr/io.h>
#include<avr/interrupt.h>
#include<string.h>
#include<stdlib.h>

/* ADC pre-defined library parts! */
#include<electrostatic/electroio/electromio/avr/adc/control/clkprescaler.h>
#include<electrostatic/electroio/electromio/avr/adc/admux/channel.h>
#include<electrostatic/electroio/electromio/avr/adc/admux/vref.h>

/**
 * @brief Callbacks for the uart protocol, use the struct initializer to instantiate these pointers.
 * @example 
 * volatile adc_callbacks _adc_callbacks = {
 *     adc_on_received,
 *      NULL,
 *      NULL,
 *      NULL,
 *  };
 * ...
 * int main() { adc_assign_callbacks(&_adc_callbacks); ... while (1); }
 */
typedef struct {
    /**
     * @brief Disptached when the adc interrupt is reached.
     * @note Make sure to enable the adc isr before using.
     *       Make sure to implement this method locally on your source file.
     */
    void (*adc_on_received)(const uint16_t READ);
    void (*adc_on_start_protocol)();
    void (*adc_on_stop_protocol)();
    void (*adc_on_start_conversion)();
} adc_callbacks;

/**
 * @brief Interrupt-safe re-assignable callbacks.
 */
volatile adc_callbacks* adc_internal_callbacks;

/**
 * @brief Assigns the callbacks for the ADC conversion.
 * 
 * @param in_callbacks an interrupt-safe adc callback object.
 */
static inline void adc_assign_callbacks(volatile adc_callbacks* in_callbacks) {
    adc_internal_callbacks = in_callbacks;
}

/**
 * @brief Starts the ADC protocol and enable the adc interrupt service by setting the [ADEN] and [ADIE].
 */
void adc_start_protocol();

/**
 * @brief Stops the ADC protocol by setting [ADEN] to 0x00 through [ADCSRA = 0x00] and formatting the output pins.
 */
void adc_stop_protocol();

/**
 * @brief Enables the adc conversion complete interrupt service routine.
 */
void adc_enable_isr();

/**
 * @brief Starts the Analog to Digital conversion.
 * @note When setting the bit [ADIE] on the [ADCSRA] register, an interrupt service is fired once the conversion is completed.
 * 
 * @param PIN the ADC MUX pin to read from.
 * @param V_REF the reference voltage to use for the ADC, 
 *              the reference voltage represents the voltage to compare against.
 * @param CONVERSION_SPEED the speed of the adc conversion in relation to the crystal oscillator.
 */
void adc_start_conversion(const uint8_t PIN, const uint8_t V_REF, const uint8_t CONVERSION_SPEED);

/**
 * @brief Combines the readings of [ADCL] and [ADCH] data registers in a 16-bit software register.
 * @note Default value = 1023, max value = 1023, min value = 0.
 * 
 * @return uint16_t a new 16-bit register representing 10-bit decade data output from the ADC.
 */
volatile uint16_t adc_read();

#endif