#ifndef _FILE_ATTRS_H_
#define _FILE_ATTRS_H_

#ifndef _ELECTRO_MIO

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <electronetsoft/util/utilities.h>

static inline status_code get_file_bytes(int fd, __off_t *__size) {
    if (fd < 0 || NULL == __size) {
        return EUNDEFINEDBUFFER;
    }
    struct stat statbuf;
    int __status = fstat(fd, &statbuf);
    if (__status != 0) {
        return errno;
    }
    *__size = statbuf.st_size;

    return PASS;
}

static inline status_code get_file_pos(int fd, off_t *__offset) {
    if (fd < 0 || NULL == __offset) {
        return EUNDEFINEDBUFFER;
    }
    *__offset = lseek(fd, 0, SEEK_CUR);
    if (*__offset < 0) {
        return errno;
    }
    return PASS;
}

#ifdef __cplusplus
}
#endif

#endif
#endif