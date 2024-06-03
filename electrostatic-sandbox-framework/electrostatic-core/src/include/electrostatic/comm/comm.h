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

extern device_metadata open(void**);
extern int init(void*);
extern int finalize(void*);
extern int close(void*);

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

/**
 * Initializes a comm protocol function table with
 * some callback functions.
 */
extern uint8_t init_protocol(comm_protocol*, comm_protocol);

/**
 * Initializes a comm protocol function table with
 * pre-defined some callback functions from their respective libraries.
 */
extern uint8_t init_protocol_from_encoding(long);

#ifdef __cplusplus
}
#endif

#endif //_ELECTROSTATIC_COMM_H_