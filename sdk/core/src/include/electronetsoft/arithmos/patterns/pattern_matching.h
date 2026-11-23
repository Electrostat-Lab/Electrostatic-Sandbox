#ifndef __PATTERN_MATCHING_H_
#define __PATTERN_MATCHING_H_

#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <electronetsoft/arithmos/adt/text.h>
#include <electronetsoft/util/utilities.h>
#include <electronetsoft/util/types.h>

#ifdef __cplusplus
extern "C" {
#endif

status_code find_brute(text, text, text_substring *);
status_code find_boyer_moore(text, text, text_substring *);
status_code find_kmp(text, text, text_substring *);
status_code find_sigma_locator(text, text, text_substring *);

#ifdef __cplusplus
};
#endif

#endif