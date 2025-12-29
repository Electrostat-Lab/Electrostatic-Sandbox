/**
 * @brief A tech-demo for the implementation of the file writing algorithm using polling that provides an algorithm to write out a buffer to a file and a post processing automata to update the file attributes using the file stat attributes from the Unix Standard library by requesting a call to the file status utility.
 * @author pavl_g.
 * @date 10-2025
 */
#include <electronetsoft/util/filesystem/file_operations.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static inline void op_preprocessor(file_mem *mem, void *caller) {
    if (caller != &write_from_mem) {
        return;
    }

    int fd = open("/home/pavl-g/Desktop/test.txt", O_RDWR | O_CREAT);

    if (fd < 0) {
        fprintf(stderr, "Error Encountered: %s\n", strerror(errno));
        exit(errno);
    }

    mem->fd = fd;
    lseek(mem->fd, 0, SEEK_END); // append!

    mem->buffer = "Hello from Project: ElectroNetSoft, File Memory Modelling API.\n";
    mem->n_bytes = strlen(mem->buffer) + 1;

    fprintf(stdout, "Size of memory buffer (in bytes) = %zd\n",
            mem->n_bytes);
}

static inline void on_bytes_processed(file_mem *mem, ssize_t bytes,
                                  void *caller) {
    if (caller != &write_from_mem) {
        return;
    }

    fprintf(stdout, "%s", mem->buffer);
}

static inline void on_eob_reached(file_mem *mem, void *caller) {
    if (caller != &write_from_mem) {
        return;
    }
    fprintf(stdout, "EOB Reached!\n");
}

static inline void op_postprocessor(file_mem *mem, void *caller) {
    if (caller != &write_from_mem) {
        return;
    }
    close(mem->fd);
    mem->fd = -1;
}

int main() {
    fprintf(stdout, "Hello File Write Automata!\n");

    file_mem _file_mem = {
            .fd = -1,
            .trailing = '\0',
            .buffer = NULL,
            .n_bytes = -1,
            .file_size = -1,
            .file_pos = -1,
            .__auto_update_attrs = 1,
    };

    op_processor _processor = {
            .on_bytes_processed = &on_bytes_processed,
            .on_trailing_char_sampled = &on_eob_reached,
            .op_preprocessor = &op_preprocessor,
            .op_postprocessor = &op_postprocessor
    };

    status_code __status = write_from_mem(&_file_mem, &_processor, NULL);

    if (PASS != __status) {
        fprintf(stderr, "Error Encountered: %s\n", strerror(__status));
        exit(__status);
    }

    return 0;
}