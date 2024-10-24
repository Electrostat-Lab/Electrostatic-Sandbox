/** 
 * @brief Defines clock pre-scalers to adjust the speed of conversionn based on the crystal oscillator.
 * @author pavl_g
 * @note  For the AVR, the ADC requires an input clk frequency less than 200kHz 
 *        for the maximum accuracy.
 */
#ifndef _CLK_PRESCALER_H
#define _CLK_PRESCALER_H

/**
 * @brief Scales the speed to CLK/2, where [CLK] is the speed of the crystal oscillator. 
 */
#define CLK_2 ((const uint8_t) 1 << ADPS0)

/**
 * @brief Scales the speed to CLK/4, where [CLK] is the speed of the crystal oscillator. 
 */
#define CLK_4 ((const uint8_t) 1 << ADPS1)

/**
 * @brief Scales the speed to CLK/8, where [CLK] is the speed of the crystal oscillator. 
 */
#define CLK_8 ((const uint8_t) CLK_2 | CLK_4)

/**
 * @brief Scales the speed to CLK/16, where [CLK] is the speed of the crystal oscillator. 
 */
#define CLK_16 ((const uint8_t) 1 << ADPS2)

/**
 * @brief Scales the speed to CLK/32, where [CLK] is the speed of the crystal oscillator. 
 */
#define CLK_32 ((const uint8_t) CLK_16 | CLK_2)

/**
 * @brief Scales the speed to CLK/64, where [CLK] is the speed of the crystal oscillator. 
 */
#define CLK_64 ((const uint8_t) CLK_16 | CLK_4)

/**
 * @brief Scales the speed to CLK/128, where [CLK] is the speed of the crystal oscillator. 
 */
#define CLK_128 ((const uint8_t) CLK_2 | CLK_4 | CLK_16)

#endif