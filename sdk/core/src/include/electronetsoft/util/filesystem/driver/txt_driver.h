#ifndef _TXT_DRIVER_H_
#define _TXT_DRIVER_H_

#ifndef _ELECTRO_MIO

#ifdef __cplusplus
extern "C" {
#endif

#include <electronetsoft/util/utilities.h>

struct txt_driver {
    char *text;
};

status_code txt_driver_init(file_driver *);
status_code txt_driver_terminate(file_driver *);

#ifdef __cplusplus
};
#endif

#endif
#endif