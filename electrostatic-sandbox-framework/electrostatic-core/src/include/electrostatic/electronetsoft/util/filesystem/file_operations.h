/**
 * @brief A completely memory-safe not internally synchronized API that provides a dynamic
 * way of reading and writing to files without a [realloc] overhead; by delegating memory
 * allocation as a part of the pre-processor states to the caller, and the memory deallocation or further reallocation calls
 * as a part of the accepting states to another function of the caller API or Application.
 * @note Synchronization (using polling or mutexes) could be introduced through the lifecycle struct
 *       [file_op_processor] for file operation processor.
 * @author pavl_g.
 * @date 2025-10
 */
#ifndef _FILE_OPERATIONS_H_
#define _FILE_OPERATIONS_H_

#ifndef _ELECTRO_MIO

#ifdef __ANDROID__
#define __off_t size_t
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <electrostatic/electronetsoft/util/utilities.h>

struct op_processor {
    void (*op_preprocessor)(file_mem *, void *);
    void (*op_postprocessor)(file_mem *, void *);
    void (*on_bytes_processed)(file_mem *, ssize_t, void *); /* Executed on each successful read operation. */
    void (*on_last_byte_sampled)(file_mem *, void *); // uses count
    void (*on_trailing_char_sampled)(file_mem *, void *); // uses predicate check
    void (*on_error_encountered)(file_mem *, int, void *);
};

struct update_op_processor {
    void (*on_update_nbytes)(file_mem *, ssize_t); /* Executed when updating the number of bytes attr (of the buffer for the file mem model) is commenced */
    void (*on_update_size)(file_mem *, __off_t); /* Executed when updating size is commenced. */
    void (*on_update_pos)(file_mem *, __off_t); /* Executed when updating the position is commenced. */
    void (*update_model_preprocessor)(file_mem *, void *caller); /* Executed */
    void (*update_model_postprocessor)(file_mem *, void *caller); /* Executed after the file mem model attrs update has finished. Could be used to chain calls to memory allocators. */
};

struct serializer_op_processor {
     void (*serializer_init_preprocessor)(pipe_serializer *);
     void (*serializer_init_postprocessor)(pipe_serializer *);
};

struct file_mem {
    int fd;
    char trailing; /* The trailing byte of the buffer.*/
    ssize_t n_bytes; /* Total number of bytes to allocate for the buffer in memory
                      * including the number of read or write bytes
                      * starting from the current pos based on
                      * the file size, and the trailing byte. */
    ssize_t bytes_processed;
    char *buffer;
    __off_t file_size; /* Cached file size in bytes */
    __off_t file_pos; /* Cached file position */
    uint8_t __auto_update_attrs; /* Conditional flag to specify whether auto-update
                                    * in the pre-processing stage is enabled. */
    uint8_t __continue_after_eof; /* Conditional flag to specify whether to continue after the EOF. */
};

/**
 * @brief A pipe-serializer object creates a pipe that has
 * a write end and read end; both ends are mapped to the same
 * filesystems, in which the write operations are available to be read
 * by the memory model processor. Therefore, both memory models utilize
 * a shared memory buffer, but they possess different filesystems and thus
 * different file positions.
 */
struct pipe_serializer {
    file_mem read_end;
    file_mem write_end;
};


/**
 * @brief Delegates to allocate a heap buffer and reads a file identified by this file descriptor
 * into the heap memory; returning the memory address into the
 * [buffer] pointer of the file memory model object.
 *
 * @param mem a pointer to the file memory model struct.
 * @param _processor a pointer to the file read operations processor; that links the API to the user application.
 * @param __processor a pointer to the file attrs update processors.
 */
status_code read_into_mem(file_mem *, op_processor *, update_op_processor *);

status_code update_file_attrs(file_mem *, update_op_processor *);

/**
 * @brief Writes a pre-allocated buffer to a file identified by a file descriptor from
 * the file memory model structure; until reaching the trailing character which is excluded
 * from the this write operation and marks the accepting state of this machine.
 *
 * @param mem a pointer to the file memory model struct.
 * @param processor a pointer to the file operations processor; that links the API to the user application.
 */
status_code write_from_mem(file_mem *, op_processor *, update_op_processor *);

status_code init_serializer(pipe_serializer *, serializer_op_processor *, update_op_processor *);

#ifdef __cplusplus
}
#endif

#endif
#endif