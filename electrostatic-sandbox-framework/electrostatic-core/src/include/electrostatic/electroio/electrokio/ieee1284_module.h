/**
 * @brief A library to control the IEEE-1284-A Parallel Module provided by the Super I/O
 * IT8728 ITE Chip on the Gigabyte motherboards (Notice that this library uses a high-level
 * OS system calls and not direct address bus invokes; thus its highly compatible with other platforms).
 * <br/>
 *
 * <p>
 * Documents for IEEE-1284:
 * <a href="https://ieeexplore.ieee.org/document/879340">IEEE-1284 Standard Document</a>
 * <a href="https://www.kernel.org/doc/html/v4.12/driver-api/miscellaneous.html">Linux Kernel Parallel Port Devices</a>
 * </p>
 *
 * <p>
 * Physical Architecture for the IEEE-1284 modular
 * library:
 * <img src="" height=150 width=80/>
 * </p>
 *
 * @author pavl_g.
 */
#ifndef ___PARPORT_H_
#define ___PARPORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/parport.h>
#include <linux/ppdev.h>
#include <sys/ioctl.h>
#include <inttypes.h>

#define IEEE1284_LOGIC_ON ((uint8_t)(0xFF))
#define IEEE1284_LOGIC_OFF ((uint8_t)(0x00))

#define IEEE1284_PIN_0 ((uint8_t)0b0)
#define IEEE1284_PIN_1 ((uint8_t)0x01)
#define IEEE1284_PIN_2 ((uint8_t)0x02)
#define IEEE1284_PIN_3 ((uint8_t)0x03)
#define IEEE1284_PIN_4 ((uint8_t)0x04)
#define IEEE1284_PIN_5 ((uint8_t)0x05)
#define IEEE1284_PIN_6 ((uint8_t)0x06)
#define IEEE1284_PIN_7 ((uint8_t)0x07)

typedef struct parport_module(parport_module);
typedef struct parport_control(parport_control);
typedef struct parport_status(parport_status);
typedef struct parport_register(parport_register);
typedef struct parport_callbacks(parport_callbacks);

typedef enum {
    DATA_LINE_INPUT,
    DATA_LINE_OUTPUT
} data_line_direction;

/**
 * Defines the control register part.
 */
struct parport_register {
    uint8_t bit0;
    uint8_t bit1;
    uint8_t bit2;
    uint8_t bit3;
    uint8_t bit4;
    uint8_t bit5;
    uint8_t bit6;
    uint8_t bit7;
    uint8_t memory;
};

/**
 * Provides callbacks strategy for the API IOCTL calls.
 */
struct parport_callbacks {
    void (*on_operation_success)(parport_module *parport, void *caller);
    void (*on_operation_failure)(parport_module *parport, int err, void *caller);
    void (*cleanup)(parport_module *parport);

    // reserved usage
    void (*on_operation_success1)(parport_module *parport, ...);
    void (*on_operation_failure1)(parport_module *parport, ...);
    void (*indeterminate_operation_status)(parport_module *parport);
};

/**
 * A physical model defining the module part of the ITE-IT8728 module.
 * <a href="https://www.ite.com.tw/en/product/cate2/IT8728">ITE-IT8728 LPC Super I/O Module</a>.
 * Use this status ping to get the base addresses for the memory registers of the parallel
 * port:
 * | sudo cat /proc/ioports | grep parport
 */
struct parport_module {
    char *device;
    parport_callbacks pport_callbacks;
    int fd;
    int access;
    int pport_mode;
};

uint8_t pport_init_callbacks(parport_module *, parport_callbacks);

int pport_open(parport_module *pmodule);

__int8_t pport_close(parport_module *pmodule);

__int8_t pport_release(parport_module *pmodule);

__int8_t pport_load_mode(parport_module *pmodule);

__int8_t pport_claim(parport_module *pmodule);

__int8_t init_mode(parport_module *pmodule);

__int8_t terminate_mode(parport_module *pmodule);

__int8_t pport_write_control_bit(parport_module *pmodule, uint8_t PIN, uint8_t STATE);

__int8_t pport_register_data_lines(parport_module *pmodule, data_line_direction dld);

__int8_t pport_write_data_bit(parport_module *pmodule, uint8_t PIN, uint8_t STATE);

__int8_t pport_write_controls(parport_module *pmodule, parport_register *pregister);

__int8_t pport_read_controls(parport_module *pmodule, parport_register *pregister);

__int8_t pport_read_control_bit(parport_module *pmodule, uint8_t PIN, uint8_t *out);

__int8_t pport_write_data(parport_module *pmodule, parport_register *pregister);

__int8_t pport_read_data(parport_module *pmodule, parport_register *pregister);

__int8_t pport_read_data_bit(parport_module *pmodule, uint8_t PIN, uint8_t *out);

__int8_t pport_read_status(parport_module *pmodule, parport_register *pregister);

__int8_t pport_read_status_bit(parport_module *pmodule, uint8_t PIN, uint8_t *out);

#ifdef __cplusplus
}
#endif

#endif
