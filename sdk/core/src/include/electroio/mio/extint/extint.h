#ifndef EXT_INT_H_
#define EXT_INT_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <electroio/mio/extint/vector/physicalint.h>

#define vector uint8_t

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void (*volatile on_pin_change)(vector);
} extint_callbacks;

/**
 * @brief Registers an interrupt-safe instance of external interrupt callbacks by re-assiging its internal address.
 * 
 * @param in_callbacks an interrupt-safe pointer to an interrupt-safe instance of the external-interrupt-callbacks.
 */
extern void extint_register_callbacks(volatile extint_callbacks *volatile in_callbacks);

extern void extint_enable_isr(const physical_int extint, const uint8_t pin);

extern void extint_disable_isr(const physical_int extint, const uint8_t pin);

#undef vector 

#ifdef __cplusplus
}
#endif

#endif