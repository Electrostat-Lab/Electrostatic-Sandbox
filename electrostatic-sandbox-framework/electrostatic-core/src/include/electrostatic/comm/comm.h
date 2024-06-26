/**
 * Defines a prototype for the abstract
 * API that would be commonly used among
 * embedded applications on the electrostatic-sandbox
 * workstation.
 * 
 * @author pavl_g
 */
#ifndef _ELECTROSTATIC_COMM_H_
#define _ELECTROSTATIC_COMM_H_

#include <stdio.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char *name;
    int descriptor;
    char *protocol_name;
    char *file_system;
} device_metadata;

typedef struct {
    void** (*on_open)(void**);
    void** (*on_init)(void**);
    void** (*on_deinit)(void**);
    void** (*on_read)(void**);
    void** (*on_write)(void**);
    void** (*on_close)(void**);
} comm_callbacks;

typedef struct {
    device_metadata (*open)(void**);
    uint8_t (*init)(void**);
    uint8_t (*deinit)(void**);
    uint64_t (*read)(void**);
    uint64_t (*write)(void**);
    uint8_t (*close)(void**);
    device_metadata (*get_metadata)(void**);
    comm_callbacks *callbacks;
} comm_protocol;

/**
 * Defines function tables for communication protocols.
 */
enum CommProtocol {
    SERIAL_RS232 = 0x00,
    IEEE_1284 = 0x01,
    PCI = 0x02,
    NET_SOCKETS = 0x03,
    SERIAL_UART = 0x04,
    SERIAL_SPI = 0x05,
    SERIAL_TWI = 0x06,
    SERIAL_CUSTOM_01 = 0x07,
    SERIAL_CUSTOM_02 = 0x08
};

extern uint8_t init_protocol(comm_protocol*, const comm_protocol*);
extern uint8_t init_protocol_default(comm_protocol*, enum CommProtocol, const comm_callbacks*);

#ifdef __cplusplus
}
#endif

#endif //_ELECTROSTATIC_COMM_H_
