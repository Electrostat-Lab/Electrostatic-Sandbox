/**
 * @brief Defines analog ADC pins using channels [0-7] based on the multiplexers codes.
 * @author pavl_g 
 */
#ifndef _CHANNEL_H
#define _CHANNEL_H

/**
 * @brief The AVR ADC Channel-0. 
 */
#define ADC_MUX0 ((const uint8_t) 0x00)

/**
 * @brief The AVR ADC Channel-1. 
 */
#define ADC_MUX1 (ADC_MUX0 + 0x01)

/**
 * @brief The AVR ADC Channel-2. 
 */
#define ADC_MUX2 (ADC_MUX1 + 0x01)

/**
 * @brief The AVR ADC Channel-3. 
 */
#define ADC_MUX3 (ADC_MUX2 + 0x01)

/**
 * @brief The AVR ADC Channel-4. 
 */
#define ADC_MUX4 (ADC_MUX3 + 0x01)

/**
 * @brief The AVR ADC Channel-5. 
 */
#define ADC_MUX5 (ADC_MUX4 + 0x01)

/**
 * @brief The AVR ADC Channel-6. 
 */
#define ADC_MUX6 (ADC_MUX5 + 0x01)

/**
 * @brief The AVR ADC Channel-7. 
 */
#define ADC_MUX7 (ADC_MUX6 + 0x01)

#endif