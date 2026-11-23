#include <electronetsoft/util/filesystem/file_operations.h>
#include <electronetsoft/util/filesystem/file_status.h>
#include <electronetsoft/util/filesystem/file_verify.h>

static inline status_code __preprocess_paging_semantics(file_mem *mem) {
    // apply paging values 
    // to the requested number of bytes
    if (NULL == mem->pager 
            || NULL == mem->pager->current) {
        return EUNDEFINEDBUFFER;
    }
    if (0 == mem->pager->paging_factor || 
            mem->pager->paging_factor > mem->file_size) {
        return EBUFFERTURNCATION;
    }
    mem->pager->current->__leading_byte = mem->file_pos;
    mem->pager->current->__size = (mem->file_size - 1) / mem->pager->paging_factor;

    // size of the page is the number of bytes to read
    // when the pages mode is {ON}
    mem->n_bytes = mem->pager->current->__size; 
    mem->pager->n_pages = (mem->file_size - 1) / mem->n_bytes;

    ssize_t page_index = mem->pager->current->__leading_byte / 
                            mem->pager->current->__size;
    // reached the end of pages, but
    // there exists some remaining bytes 
    // that cannot be grouped into pages
    // e.g., a file size of (14) bytes    
    // total request bytes = 13
    // if page size = 2 bytes is requested
    // then, number of pages = 13/2 = 6.5 = 6 pages;
    // it follows that; at the last page
    // page no. (12)                        
    // page-index = 12/2 = 6
    // it follows that 
    // one byte remains!  
    if (page_index >= mem->pager->n_pages) {
       mem->n_bytes = (mem->file_size - 1) - mem->bytes_processed;
    }
    return PASS;     
}

status_code read_into_mem(file_mem *mem,
                          op_processor *_processor,
                          update_op_processor *__processor) {
    // pre-processing automata -- Input validation
    if (NULL == mem) {
        return EUNDEFINEDBUFFER;
    }   

    status_code *__code = &(mem->__err_code);

    // pre-processing automata -- Calculating the file size, current position,
                                // and the number of bytes to read
    if (mem->__auto_update_attrs) {
        *__code = update_file_attrs(mem, __processor);
        if (PASS != *__code) {
            return *__code;
        }
    }

    // if pager exists
    *__code = __preprocess_paging_semantics(mem);
    if (PASS != *__code && EUNDEFINEDBUFFER != *__code) {
        return *__code;
    }

    PREPROCESS: {
        if (NULL != _processor && NULL != _processor->op_preprocessor) {
            _processor->op_preprocessor(mem, &read_into_mem);
        }
    };     

    if (NULL == mem->buffer) {
        *__code = EUNDEFINEDBUFFER;  
        goto POSTPROCESS;
    }

    // processing automata -- Reading n_bytes into heap buffer
    //                        starting from the current file position
    ssize_t read_bytes = 0;
    ssize_t cycle_bytes_processed = 0;
    ssize_t remaining_bytes = 0;

    while (1) {
        // sanity check the file
        if (!is_fd_existential(mem->fd)) {
            if (NULL != _processor && NULL != _processor->on_error_encountered) {
                _processor->on_error_encountered(mem, errno, &read_into_mem);
            }
            *__code = EUNDEFINEDBUFFER;

            goto POSTPROCESS;
        }
        // the (-1) in (mem->n_bytes - 1) removes the
        // trailing byte from the total number of bytes to read

        /* Advance linearly over the File Mem model buffer
         * with the read bytes */
        /* Retro-advance on the number of available bytes
         * on the corresponding physical file model. */
        READ: {
        // absolute number of remaining bytes  
            remaining_bytes = mem->n_bytes - cycle_bytes_processed;

            read_bytes = read(mem->fd, (mem->buffer + cycle_bytes_processed),
                              remaining_bytes);
        }
        // relative number of remaining bytes
        // float relative_bytes = (total_bytes / (mem->n_bytes - 1));
        // float remaining_factor = 1 - relative_bytes;

        // l_chunk_size = remaining_bytes * (remaining_factor / mem->f_bytes);
        // post processing automata

        if (__ERR_ENCOUNTERED == read_bytes) {
            // Error encountered, report and terminate!
            fprintf(stderr, "%s\n", strerror(errno));
            // interruption of the process has been detected
            // recall with the same parameters.
            if (EINTR == errno) {
                goto READ;
            }
            // terminated with error; report error!
            if (NULL != _processor && NULL != _processor->on_error_encountered) {
                _processor->on_error_encountered(mem, errno, &read_into_mem);
            }
            *__code = UNEXPECTED_ERROR;
            
            goto POSTPROCESS;
        } else if (0 == read_bytes) {
            // EOF terminate!
            mem->buffer[mem->n_bytes] = mem->trailing; /* add a null-terminating character */
            if (NULL != _processor && NULL != _processor->on_trailing_char_sampled) {
                _processor->on_trailing_char_sampled(mem, &read_into_mem);
            }
            // post-processing sub-state (HACK!)
            if (mem->__continue_after_eof) {
                continue;
            }
            break;
        } else if (read_bytes > 0) {
            cycle_bytes_processed += read_bytes;

            // total num of bytes processed
            mem->bytes_processed += read_bytes;

            *__code = get_file_pos(mem->fd, &(mem->file_pos));
            if (PASS != *__code) {
                goto POSTPROCESS;
            }
            // execute on_read
            if (NULL != _processor && NULL != _processor->on_bytes_processed) {
                _processor->on_bytes_processed(mem, read_bytes, &read_into_mem);
            }

            // sample out if all the requested characters are read
            // even though the EOF is not reached, yet.
            if (cycle_bytes_processed == mem->n_bytes) {
                mem->buffer[mem->n_bytes] = mem->trailing; /* add a null-terminating character */
                if (NULL != _processor && NULL != _processor->on_last_byte_sampled) {
                    _processor->on_last_byte_sampled(mem, &read_into_mem);
                }
                break;
            }
        } else {
            *__code = UNEXPECTED_ERROR;
            goto POSTPROCESS;
        }
    }

    // execute last page listener routine
    POSTPROCESS: { 
        if (NULL != _processor && NULL != _processor->op_postprocessor) {
            _processor->op_postprocessor(mem, &read_into_mem);
        }
    }  
    return *__code;
}