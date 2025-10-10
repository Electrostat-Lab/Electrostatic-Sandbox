#include <electrostatic/electronetsoft/util/filesystem/file_operations.h>
#include <electrostatic/electronetsoft/util/filesystem/file_status.h>
#include <electrostatic/electronetsoft/util/filesystem/file_verify.h>

status_code update_file_attrs(file_mem *mem,
                              update_op_processor *_processor) {
    // pre-processing automata -- Input Validation
    if (rvalue(mem) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    if (mem->fd < 0 || !is_fexistential(mem->fd)) {
        return EUNDEFINEDBUFFER;
    }

    // pre-processing automata -- Comparing Values
    __off_t __pos;
    status_code __status = get_file_pos(mem->fd, &__pos);
    if (PASS != __status) {
        __pos = 0;
    }

    __off_t __size;
    __status = get_file_bytes(mem->fd, &__size);
    if (PASS != __status) {
        return __status;
    }

    if (mem->file_pos != __pos) {
        __off_t __old = mem->file_pos;
        mem->file_pos = __pos;
        if (NULL != _processor && NULL != _processor->on_update_pos) {
            _processor->on_update_pos(mem, __old);
        }
    }

    if (mem->file_size != __size) {
        __off_t __old = mem->file_size;
        mem->file_size = __size;
        if (NULL != _processor && NULL != _processor->on_update_size) {
            _processor->on_update_size(mem, __old);
        }
    }

    if (mem->n_bytes != (__size - __pos)) {
        ssize_t __old = mem->n_bytes;
        mem->n_bytes = (__size - __pos) + 1;
        if (NULL != _processor && NULL != _processor->on_update_nbytes) {
            _processor->on_update_nbytes(mem, __old);
        }
    }

    return PASS;
}