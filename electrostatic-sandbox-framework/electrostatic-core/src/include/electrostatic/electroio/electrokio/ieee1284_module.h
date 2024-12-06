#ifndef ___PARPORT_H_
#define ___PARPORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/parport.h>
#include <linux/ppdev.h>
#include <sys/ioctl.h>
#include <inttypes.h>

#define IEEE1284_LOGIC_ON ((uint8_t) (0xFF))
#define IEEE1284_LOGIC_OFF ((uint8_t) (0x00))

#define IEEE1284_PIN_0 (0b0)
#define IEEE1284_PIN_1 (0x01)
#define IEEE1284_PIN_2 (0x02)
#define IEEE1284_PIN_3 (0x03)
#define IEEE1284_PIN_4 (0x04)
#define IEEE1284_PIN_5 (0x05)
#define IEEE1284_PIN_6 (0x06)
#define IEEE1284_PIN_7 (0x07)

typedef struct parport_module (parport_module);
typedef struct parport_control (parport_control);
typedef struct parport_status (parport_status);
typedef struct parport_data (parport_data);
typedef struct parport_callbacks (parport_callbacks);

/**
 * Defines the control register part.
 */
struct parport_control {
    uint8_t c0;
    uint8_t c1;
    uint8_t c2;
    uint8_t c3;
    uint8_t c4;
    uint8_t c5;
    uint8_t c6;
    uint8_t c7;
    uint8_t c_register;
};

/**
 * Defines the status register part.
 */
struct parport_status {
    uint8_t s0;
    uint8_t s1;
    uint8_t s2;
    uint8_t s3;
    uint8_t s4;
    uint8_t s5;
    uint8_t s6;
    uint8_t s7;
    uint8_t s_register;
};

/**
 * Defines the data register part.
 */
struct parport_data {
    uint8_t d0;
    uint8_t d1;
    uint8_t d2;
    uint8_t d3;
    uint8_t d4;
    uint8_t d5;
    uint8_t d6;
    uint8_t d7;
    uint8_t d_register;
};

/**
 * Provides callbacks strategy for the API IOCTL calls.
 */
struct parport_callbacks {
    void (*on_open_failure)(parport_module *, int);
    void (*on_open_success)(parport_module *);
    void (*on_claim_success)(parport_module *);
    void (*on_claim_failure)(parport_module *, int);
    void (*on_close_failure)(parport_module *, int);
    void (*on_close_success)(parport_module *);
    void (*cleanup)(parport_module *);
    void (*on_release_failure)(parport_module *, int);
    void (*on_release_success)(parport_module *);
    void (*on_mode_loading_failure)(parport_module *, int);
    void (*on_mode_loading_success)(parport_module *);
    void (*on_read_failure)(parport_module *, int);
    void (*on_read_success)(parport_module *);
    void (*on_write_failure)(parport_module *, int);
    void (*on_write_success)(parport_module *);

    // reserved usage
    void (*on_operation_success)(parport_module *, ...);
    void (*on_operation_failure)(parport_module *, ...);
};

/**
 * A physical model defining the module part of the ITE-IT8728 module.
 * <a href="https://www.ite.com.tw/en/product/cate2/IT8728">ITE-IT8728 LPC Super I/O Module</a>.
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

__int8_t pport_write_controls(parport_module *pmodule, parport_control *pcontrol);

__int8_t pport_read_controls(parport_module *pmodule, parport_control *pcontrol);

__int8_t pport_write_data(parport_module *pmodule, parport_data *pdata);

__int8_t pport_read_data(parport_module *pmodule, parport_data *pdata);

__int8_t pport_read_status(parport_module *pmodule, parport_status *pstatus);

#ifdef __cplusplus
}
#endif

#endif
