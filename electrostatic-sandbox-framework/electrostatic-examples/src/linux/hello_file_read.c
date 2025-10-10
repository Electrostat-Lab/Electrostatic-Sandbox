/**
 * @brief A tech=demo for the implementation of the file reading algorithm that provides a dynamic algorithm of determining the number of bytes to read out of a file using the file stat attributes from the Unix Standard library by requesting a call to the file status utility.
 * @author pavl_g.
 * @date 10-2025
 */
#include <electrostatic/electronetsoft/util/filesystem/file_operations.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static inline void update_model_preprocessor(file_mem *mem, void *caller) {
    if (caller != &read_into_mem) {
        return;
    }

    int fd = open("/etc/bash.bashrc", O_RDONLY);

    if (fd < 0) {
        fprintf(stderr, "Error Encountered: %s\n", strerror(errno));
        exit(errno);
    }

    mem->fd = fd;
}

static inline void update_model_postprocessor(file_mem *mem, void *caller) {
    if (caller != &read_into_mem) {
        return;
    }

    if (mem->fd == STDIN_FILENO) {
        mem->n_bytes = 2; // two bytes are given; the leading and the trailing byte.
                          // marking the start and the end of the string buffer
    }
    fprintf(stdout, "Size of memory buffer (in bytes) = %zd\n",
            mem->n_bytes);
    mem->buffer = calloc(mem->n_bytes, sizeof (char));

    if (NULL == mem->buffer) {
        return;
    }
}

static inline void on_bytes_processed(file_mem *mem,
                                      ssize_t bytes, void *caller) {
    if (caller != &read_into_mem) {
        return;
    }
    fprintf(stdout, "Read bytes = %s\n", mem->buffer);
}

static inline void on_eof_reached(file_mem *mem) {
    // support for stdin
    if (mem->fd == STDIN_FILENO && mem->n_bytes < 20) {
        mem->n_bytes += mem->n_bytes;
        mem->buffer = realloc(mem->buffer, mem->n_bytes);
        return;
    }
    fprintf(stdout, "Read Bytes after EOF: %s\n", mem->buffer);
    fprintf(stdout, "EOF Reached!\n");
    // deallocates memory here!
    if (NULL != mem->buffer) {
        free(mem->buffer);
        mem->buffer = NULL;
    }
    int __status = close(mem->fd);
    if (0 != __status) {
        fprintf(stderr, "Error Encountered: %s\n", strerror(__status));
        exit(__status);
    }
}

int main() {
    fprintf(stdout, "Hello File Read Automata!\n");

    file_mem _file_mem = {
        .fd = -1,
        .trailing = '\0',
        .buffer = NULL,
        .n_bytes = -1,
        .file_size = -1,
        .file_pos = -1,
        .__auto_update_attrs = 1,
        .__continue_after_eof = 0
    };

    read_op_processor _processor = {
        .on_bytes_processed = &on_bytes_processed,
        .on_eof_reached = &on_eof_reached
    };

    update_op_processor __processor = {
        .update_model_preprocessor = &update_model_preprocessor,
        .update_model_postprocessor = &update_model_postprocessor,
    };

    status_code __status = read_into_mem(&_file_mem, &_processor, &__processor);

    if (PASS != __status) {
        fprintf(stderr, "Error Encountered: %s\n", strerror(__status));
        exit(__status);
    }

    return 0;
}