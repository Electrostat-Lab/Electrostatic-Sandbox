/**
 * @brief Provides the supported flags for the analog converter voltage reference.
 * @author pavl_g. 
 */
#ifndef _V_REF_H
#define _V_REF_H

/**
 * @brief use the external AREF pin as a voltage reference, internal V-REF turned off. 
 */
#define EXTERNAL_VREF ((const uint8_t) 0x00)

/**
 * @brief use AV(CC) with external capacitor at AREF pin.
 */
#define AVCC_VREF ((const uint8_t) 1 << REFS0)

/**
 * @brief use the internal 1.1V voltage reference with external capacitor at AREF pin, 
 */
#define INTERNAL_VREF ((const uint8_t) AVCC_VREF | (1 << REFS1))

#endif