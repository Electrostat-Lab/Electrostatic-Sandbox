#include <electrostatic/electronetsoft/util/filesystem/file_operations.h>
#include <electrostatic/electronetsoft/util/filesystem/file_status.h>
#include <electrostatic/electronetsoft/util/filesystem/file_verify.h>

status_code read_into_mem(file_mem *mem,
                          read_op_processor *_processor,
                          update_op_processor *__processor) {
    // pre-processing automata -- Input validation
    if (rvalue(mem) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL != __processor && NULL != __processor->update_model_preprocessor) {
        __processor->update_model_preprocessor(mem, &read_into_mem);
    }

    // pre-processing automata -- Calculating the file size, current position,
                                // and the number of bytes to read
    if (mem->__auto_update_attrs) {
        status_code ___status = update_file_attrs(mem, __processor);
        if (PASS != ___status) {
            return ___status;
        }
    }

    // postprocessing automata -- Invoke the update file postprocessor
    if (NULL != __processor && NULL != __processor->update_model_postprocessor) {
        __processor->update_model_postprocessor(mem, &read_into_mem);
    }

    if (NULL == mem->buffer) {
        return EUNDEFINEDBUFFER;
    }

    // processing automata -- Reading n_bytes into heap buffer
    //                        starting from the current file position
    ssize_t read_bytes = 0;
    ssize_t total_bytes = 0;
    while (1) {
        read_bytes = read(mem->fd, (mem->buffer + total_bytes), /* Advance linearly over the File Mem model buffer
                                                                * with the read bytes */
                                   (mem->n_bytes - 1) - total_bytes); /* Retro-advance on the number of available bytes
                                                                      * on the corresponding physical file model. */

        total_bytes += read_bytes;
        mem->bytes_processed = total_bytes;
        // post processing automata

        if (-1 == read_bytes) {
            // terminated with error; report error!
            if (NULL != _processor && NULL != _processor->on_error_encountered) {
                _processor->on_error_encountered(mem, errno, &read_into_mem);
            }
            return errno;
        } else if (0 == read_bytes) {
            // EOF terminate!
            mem->buffer[total_bytes] = mem->trailing; /* add a null-terminating character */
            if (NULL != _processor && NULL != _processor->on_eof_reached) {
                _processor->on_eof_reached(mem);
            }
            // post-processing sub-state (HACK!)
            if (mem->__continue_after_eof) {
                continue;
            }
            return PASS;
        } else if (read_bytes > 0) {
            // execute on_read
            if (NULL != _processor && NULL != _processor->on_bytes_processed) {
                _processor->on_bytes_processed(mem, read_bytes, &read_into_mem);
            }

            // sample out if all the requested characters are read
            // even though the EOF is not reached, yet.
            if ((mem->n_bytes - 1) == total_bytes) {
                mem->buffer[total_bytes] = mem->trailing; /* add a null-terminating character */
                if (NULL != _processor && NULL != _processor->on_last_char_sampled) {
                    _processor->on_last_char_sampled(mem, &read_into_mem);
                }
            }
        } else {
            return UNEXPECTED_ERROR;
        }
    }

    return ASSERTION_FAILURE;
}