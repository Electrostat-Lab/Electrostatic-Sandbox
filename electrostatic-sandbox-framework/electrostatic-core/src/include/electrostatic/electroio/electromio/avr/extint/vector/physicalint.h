#ifndef EXT_INT_H_
#   error "The <electrostatic/electroio/electromio/avr/extint/vector/physicalint.h> header is an internal property, include <extint/extint.h> instead of this!"
#endif

#ifndef PHYSICAL_INT_H_
#define PHYSICAL_INT_H_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the logic for a physical interrupt (interrupt sense or pin change).
 */
typedef struct {
    /**
     * @brief Defines the address for the mask register. 
     */
    volatile uint8_t* MASKr;
    
    /**
     * @brief Defines the address for the interrupt control register. 
     */
    volatile uint8_t* CONTROLr;

    /**
     * @brief Defines the address for the interrupt flag register. 
     */
    volatile uint8_t* FLAGr;
} physical_int;


#ifdef __cplusplus
}
#endif

#endif