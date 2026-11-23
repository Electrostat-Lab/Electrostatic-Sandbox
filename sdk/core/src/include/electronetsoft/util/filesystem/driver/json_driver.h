#ifndef _JSON_DRIVER_H_
#define _JSON_DRIVER_H_

#ifndef _ELECTRO_MIO

#ifdef __cplusplus
extern "C" {
#endif

#include <electronetsoft/util/utilities.h>

struct json_driver {
    char *text;
};

status_code json_driver_init(file_driver *);
status_code json_driver_terminate(file_driver *);

#ifdef __cplusplus
};
#endif

#endif
#endif