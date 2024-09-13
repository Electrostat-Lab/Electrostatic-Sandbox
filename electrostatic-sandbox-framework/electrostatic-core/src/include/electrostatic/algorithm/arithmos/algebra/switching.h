//
// A header file for switching algebra operations.
// Author: pavl_g.
//

#ifndef _SWITCHING_ALGEBRA_H_
#define _SWITCHING_ALGEBRA_H_

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#if !defined(SWITCHING_TYPE)
#define SWITCHING_TYPE uint8_t
#endif

typedef enum filter_type {
    NO_FILTER,
    NOT_GATE,
} filter_type;

typedef struct switching_filter {
    uint8_t (*filter)(SWITCHING_TYPE input, SWITCHING_TYPE *output);
    filter_type type;
} switching_filter;

uint8_t init_switching_filter(switching_filter *filter);
uint8_t switching_not(SWITCHING_TYPE input, SWITCHING_TYPE *output);
uint8_t switching_and(SWITCHING_TYPE **inputs, SWITCHING_TYPE *output);
uint8_t switching_or(SWITCHING_TYPE **inputs, SWITCHING_TYPE *output);
uint8_t switching_xor(SWITCHING_TYPE **inputs, SWITCHING_TYPE *output);
uint8_t switching_multiplex(SWITCHING_TYPE **inputs, SWITCHING_TYPE *output, SWITCHING_TYPE **selects, struct switching_filter ***filters);
uint8_t switching_multiplex_bitlevel(SWITCHING_TYPE input, SWITCHING_TYPE *output, SWITCHING_TYPE line_select);
uint8_t switching_demultiplex(SWITCHING_TYPE input, SWITCHING_TYPE **outputs, uint8_t line_select);

#ifdef __cplusplus
}
#endif

#endif