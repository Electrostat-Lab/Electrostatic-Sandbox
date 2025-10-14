#ifndef _FILE_VERIFY_H_
#define _FILE_VERIFY_H_

#ifndef _ELECTRO_MIO

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <electrostatic/electronetsoft/util/filesystem/file_operations.h>

static inline int get_path_from_fd(int fd, char *buf, ssize_t len) {
    if (fd < 0 || NULL == buf) {
        return -1;
    }

    pid_t pid = getpid();

    char path[255];
    memset(path, '\0', sizeof (path));
    sprintf(path, "/proc/%d/fd/%d", pid, fd);

    return readlink(path, buf, len) > 0;
}

static inline int is_existential(const char *file) {
    if (file == NULL) {
        return -1;
    }
    struct stat statbuf;
    return stat(file, &statbuf) == 0;
}

static inline int is_fd_existential(int fd) {
    if (fd < 0) {
        return -1;
    }
    char path[255];
    memset(path, '\0', sizeof (path));
    int __status = get_path_from_fd(fd, path, sizeof (path));
    if (!__status) {
        return -1;
    }
    return is_existential(path);
}

static inline int is_fexistential(int fd) {
    if (fd < 0) {
        return -1;
    }
    struct stat statbuf;
    return fstat(fd, &statbuf) == 0;
}

static inline int is_cs_tty(const char *file) {
    if (file == NULL) {
        return -1;
    }
    struct stat statbuf;
    int proposition0 = stat(file, &statbuf) == 0;
    int proposition1 = S_ISCHR(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_fcs_tty(int fd) {
    struct stat statbuf;
    int proposition0 = fstat(fd, &statbuf) == 0;
    int proposition1 = S_ISCHR(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_dir(const char *file) {
    if (file == NULL) {
        return -1;
    }
    struct stat statbuf;
    int proposition0 = stat(file, &statbuf) == 0;
    int proposition1 = S_ISDIR(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_fdir(int fd) {
    struct stat statbuf;
    int proposition0 = fstat(fd, &statbuf) == 0;
    int proposition1 = S_ISDIR(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_regular_file(const char *file) {
    if (file == NULL) {
        return -1;
    }
    struct stat statbuf;
    int proposition0 = stat(file, &statbuf) == 0;
    int proposition1 = S_ISREG(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_fregular_file(int fd) {
    struct stat statbuf;
    int proposition0 = fstat(fd, &statbuf) == 0;
    int proposition1 = S_ISREG(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_block_device(const char *file) {
    if (file == NULL) {
        return -1;
    }
    struct stat statbuf;
    int proposition0 = stat(file, &statbuf) == 0;
    int proposition1 = S_ISBLK(statbuf.st_mode) == 1;
    return proposition0 && proposition1;
}

static inline int is_fblock_device(int fd) {
    struct stat statbuf;
    int proposition0 = fstat(fd, &statbuf) == 0;
    int proposition1 = S_ISREG(statbuf.st_mode) == 1;
    return proposition0 && proposition1;
}

static inline int is_pipe(const char *file) {
    if (file == NULL) {
        return -1;
    }
    struct stat statbuf;
    int proposition0 = stat(file, &statbuf) == 0;
    int proposition1 = S_ISFIFO(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_fpipe(int fd) {
    struct stat statbuf;
    int proposition0 = fstat(fd, &statbuf) == 0;
    int proposition1 = S_ISFIFO(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_socket(const char *file) {
    if (file == NULL) {
        return -1;
    }
    struct stat statbuf;
    int proposition0 = stat(file, &statbuf) == 0;
    int proposition1 = S_ISSOCK(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_fsocket(int fd) {
    struct stat statbuf;
    int proposition0 = fstat(fd, &statbuf) == 0;
    int proposition1 = S_ISSOCK(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_symbolic_link(const char *file) {
    if (file == NULL) {
        return -1;
    }
    struct stat statbuf;
    int proposition0 = stat(file, &statbuf) == 0;
    int proposition1 = S_ISLNK(statbuf.st_mode) == 1; 
    return proposition0 && proposition1;
}

static inline int is_fsymbolic_link(int fd) {
    struct stat statbuf;
    int proposition0 = fstat(fd, &statbuf) == 0;
    int proposition1 = S_ISLNK(statbuf.st_mode) == 1;
    return proposition0 && proposition1;
}

#ifdef __cplusplus
}
#endif

#endif
#endif