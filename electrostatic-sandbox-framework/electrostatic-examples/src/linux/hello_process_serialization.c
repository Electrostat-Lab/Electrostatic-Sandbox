/**
 * @brief This example creates a physical pipe and serializes data
 * between 2 processes over the off-heap memory. Synchronization and concurrency
 * is implemented utilizing Polling over a boolean flag on the lifecycle pattern
 * of the read_op component.
 *
 * @author pavl_g.
 */
#include <electrostatic/electronetsoft/util/filesystem/file_operations.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

static inline void on_error_encountered(file_mem *mem, int err, void *caller) {
    fprintf(stderr, "%s\n", strerror(err));
}

static inline void on_eof_reached(file_mem *mem) {
    // -------- Start the polling block --------
    uint8_t __predicate = mem->bytes_processed == 0;
    if (__predicate) {
        mem->__continue_after_eof = 1;
        // -------- Connect the polling block to the read automaton --------
        return;
    }
    // -------- End of the polling block --------
    fprintf(stdout, "Read process = %s\n", mem->buffer);
    free(mem->buffer);
    mem->buffer = NULL;
    mem->__continue_after_eof = 0;

    close(mem->fd);
}

static inline void on_eob_reached(file_mem *mem) {
    fprintf(stdout, "Write process = %s", mem->buffer);
    close(mem->fd);
}

static inline void on_last_char_sampled(file_mem *mem, void *caller) {
    mem->n_bytes += mem->n_bytes;
    mem->buffer = realloc(mem->buffer, sizeof (char) * (mem->n_bytes));
}

static inline void on_bytes_processed(file_mem *mem, ssize_t bytes,
                                      void *caller) {
}

static inline void writing_process(pipe_serializer *serializer) {

    serializer->write_end.buffer = "Hello From the Electrostatic-Sandbox SDK Pipe Serializer...\n";
    serializer->write_end.n_bytes = strlen(serializer->write_end.buffer) + 1;

    sleep(10); // simulate jobs by sleeping the process

    write_from_mem(&serializer->write_end, &(write_op_processor ) {
       .on_eob_reached = &on_eob_reached,
       .on_bytes_processed = &on_bytes_processed
    }, NULL);
}

static inline void reading_process(pipe_serializer *serializer) {

    serializer->read_end.n_bytes = 2;
    serializer->read_end.buffer = calloc(serializer->read_end.n_bytes, sizeof (char));

    if (serializer->read_end.buffer == NULL) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(errno);
    }

    status_code __status = read_into_mem(&serializer->read_end, &(read_op_processor) {
        .on_eof_reached = &on_eof_reached,
        .on_last_char_sampled = &on_last_char_sampled,
        .on_bytes_processed = &on_bytes_processed,
        .on_error_encountered = &on_error_encountered
    }, NULL);

    if (PASS != __status) {
        fprintf(stderr, "%s\n", strerror(__status));
        exit(errno);
    }
}

static inline void serializer_init_preprocessor(pipe_serializer *serializer) {
    // preprocessing check the file and remove it if it exists
    // for the test and the showcase

}

static inline void serializer_init_postprocessor(pipe_serializer *serializer) {
    // do the read/write testing here!
    serializer->write_end.fd = open("/home/pavl-g/Desktop/test.txt", O_RDWR | O_CREAT);
    serializer->read_end.fd = open("/home/pavl-g/Desktop/test.txt", O_RDONLY);

    // start another process
    pid_t pid = fork();
    if (pid > 0) { // parent process
        writing_process(serializer);
    } else if (pid == 0) { // subprocess
        reading_process(serializer);
    } else {

    }
}


int main() {
    pipe_serializer serializer = {
        .read_end = (file_mem) {
            .fd = -1,
            .trailing = '\0',
            .buffer = NULL,
            .n_bytes = -1,
            .__auto_update_attrs = 0
        },
        .write_end = (file_mem) {
            .fd = -1,
            .trailing = '\0',
            .buffer = NULL,
            .n_bytes = -1
        }
    };

    serializer_op_processor _processor = {
         .serializer_init_preprocessor = &serializer_init_preprocessor,
         .serializer_init_postprocessor = &serializer_init_postprocessor
    };

    update_op_processor __processor = {
    };

    status_code __status_code = init_serializer(&serializer, &_processor, &__processor);
    if (PASS != __status_code) {
        return __status_code;
    }

    return 0;
}