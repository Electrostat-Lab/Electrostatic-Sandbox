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

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    void (*on_device_opened)(void**);
    void (*on_device_initialized)(void**);
    void (*on_device_finalized)(void**);
    void (*on_memory_destruction)(void**);
} comm_callbacks;

extern int open(void*);
extern int init(void*);
extern int finalize(void*);
extern int close(void*);


#ifdef __cplusplus
}
#endif

#endif //_ELECTROSTATIC_COMM_H_
