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
    char* name;
    int descriptor;
    char* protocol_name;
    char* file_system;
} device_metadata;

typedef struct {
    device_metadata (*open)(void**);
    uint8_t (*init)(void**);
    uint8_t (*deinit)(void**);
    uint64_t (*read)(void**);
    uint64_t (*write)(void**);
    uint8_t (*close)(void**);
    device_metadata (*get_metadata)(void**);
} comm_protocol;

/**
 * Defines function tables for communication protocols.
 */
comm_protocol serial;
comm_protocol parallel;
comm_protocol socket;
comm_protocol pci;
comm_protocol usbfs;

extern uint8_t init_protocol(comm_protocol*, const comm_protocol*);
extern uint8_t init_protocols_default();

#ifdef __cplusplus
}
#endif

#endif //_ELECTROSTATIC_COMM_H_