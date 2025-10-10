#include <electrostatic/electronetsoft/util/filesystem/file_operations.h>
#include <electrostatic/electronetsoft/util/filesystem/file_status.h>
#include <electrostatic/electronetsoft/util/filesystem/file_verify.h>

status_code write_from_mem(file_mem *mem,
                           write_op_processor *_processor,
                           update_op_processor *__processor) {
    // pre-processing automata -- Input validation
    if (rvalue(mem) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL != __processor && NULL != __processor->update_model_preprocessor) {
        __processor->update_model_preprocessor(mem, &write_from_mem);
    }

    if (mem->fd < 0 || !is_fexistential(mem->fd)) {
        return UNEXPECTED_ERROR;
    }

    if (NULL == mem->buffer) {
        return EUNDEFINEDBUFFER;
    }

    // processing automata -- Write Characters until the trailing char is reached
    // NB: This is also known as write using polling!
    // On the other hand, there is write using IRQ aka. interrupt requests;
    // Soft IRQs are analogous to Process Signal Handlers; it's mediated by a Kernel
    // software trap.
    // R/W IO using Soft IRQs are covered within the [soft_irq] API.
    ssize_t written_bytes = 0;
    ssize_t total_bytes = 0;
    while (1) {
        if (*(mem->buffer + total_bytes) == mem->trailing) {
            if (NULL != _processor && NULL != _processor->on_eob_reached) {
                _processor->on_eob_reached(mem);
            }
            break;
        }

        written_bytes = write(mem->fd,
                              (const void *)
                              (mem->buffer + total_bytes),
                              (mem->n_bytes - 1) - total_bytes);
        total_bytes += written_bytes;
        // post-processing sub-machines -- Validate the state of the write bytes.
        if (written_bytes <= 0) {
            // Error encountered, report and terminate!
            if (NULL != _processor && NULL != _processor->on_error_encountered) {
                _processor->on_error_encountered(mem, errno, &write_from_mem);
            }
            return errno;
        } else if (written_bytes > 0) {
            // Execute lifecycle processors, try processing more bytes until all requested bytes are written.
            if (NULL != _processor && NULL != _processor->on_bytes_processed) {
                _processor->on_bytes_processed(mem, written_bytes, &write_from_mem);
            }
        } else if (total_bytes == (mem->n_bytes - 1)) {
            // All bytes are written? -> terminate
            // Equivalent to EOF.
            if (NULL != _processor && NULL != _processor->on_eob_reached) {
                _processor->on_eob_reached(mem);
            }
            break;
        } else {
            return UNEXPECTED_ERROR;
        }
    }

    // post-processing -- Update the file attrs
    status_code ___status = update_file_attrs(mem, __processor);
    if (PASS != ___status) {
        return ___status;
    }

    // postprocessing automata -- Invoke the update file postprocessor
    if (NULL != __processor && NULL != __processor->update_model_postprocessor) {
        __processor->update_model_postprocessor(mem, &write_from_mem);
    }

    return PASS;
}