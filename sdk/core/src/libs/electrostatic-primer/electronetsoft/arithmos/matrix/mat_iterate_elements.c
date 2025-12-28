#include <electronetsoft/util/caller_graphs.h>
#include <electronetsoft/arithmos/vectorspaces/matrix/matrix.h>

static inline status_code row_convention_iterator(matrix mat, mat_processors proc,
                                           uint64_t *rows, uint64_t *columns,
                                           uint8_t *signal_row_increment,
                                           caller_graph *root_caller) {

    // preprocessing automata -- Define Machine Input (Sigma, the machine language)
    caller_graph caller = {
            .api = "arithmos:matrix#row_convention_iterator",
            .func = &row_convention_iterator,
            .params = NULL,
            .return_value = NULL,
            .root = root_caller
    };

    mat_proc_sig proc_sig = {
            .mat = mat,
            .row_index = *rows,
            .col_index = *columns,
            .proc = proc,
            .caller = caller,
            .metadata = proc.metadata
    };

    status_code __code;

    // preprocessing automata -- Validate machine input
    // for null-terminated matrices
    if (NULL == mat.element[*rows]) {
        if (NULL != proc.on_op_failure) {
            proc.on_op_failure(proc_sig, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    // processing automata -- conditional sub-automata (1)
    // use row-first convention to iterate over elements
    // therefore, increment columns first
    if (is_last_column(mat, *columns)) {
        // signal a on_row_iterated
        if (NULL != proc.on_row_iterated) {
            __code = proc.on_row_iterated(proc_sig);
            if (PASS != __code) {
                return __code;
            }
        }
        // signal an increment at the final states (post-processing)
        *signal_row_increment = 1;
    }

    // processing automata -- conditional sub-automata (2)
    // signal a on_column_iterated for all elements lying in this range
    if (is_last_row(mat, *rows)) {
        // signal a on_column_iterated
        if (NULL != proc.on_column_iterated) {
            __code = proc.on_column_iterated(proc_sig);
            if (PASS != __code) {
                return __code;
            }
        }
    }

    // post-processing automata
    // signal a on_entry_iterated
    __code = proc.on_entry_iterated(proc_sig);

    // Update the machine input
    *columns = (*columns + 1) % mat.n; // increment the columns, but protect memory accessibility!

    if (*signal_row_increment) {
        *rows = *rows + 1;
        *signal_row_increment = 0;
    }
    return __code;
}

static inline status_code column_convention_iterator(matrix mat, mat_processors proc,
                                           uint64_t *rows, uint64_t *columns,
                                           uint8_t *signal_column_increment,
                                           caller_graph *root_caller) {

    // preprocessing automata -- Define Machine Input (Sigma, the machine language)
    caller_graph caller = {
            .api = "arithmos:matrix#column_convention_iterator",
            .func = &column_convention_iterator,
            .params = NULL,
            .return_value = NULL,
            .root = root_caller
    };

    mat_proc_sig proc_sig = {
            .mat = mat,
            .row_index = *rows,
            .col_index = *columns,
            .proc = proc,
            .caller = caller,
            .metadata = proc.metadata
    };

    status_code __code;

    // preprocessing automata -- Validate machine input
    // for null-terminated matrices
    if (NULL == mat.element[*rows]) {
        if (NULL != proc.on_op_failure) {
            proc.on_op_failure(proc_sig, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    // processing automata -- conditional sub-automata (1)
    // use column-first convention to iterate over elements
    // therefore, increment rows for every column of index (columns)
    if (is_last_row(mat, *rows)) {
        // signal a on_column_iterated
        if (NULL != proc.on_column_iterated) {
            __code = proc.on_column_iterated(proc_sig);
            if (PASS != __code) {
                return __code;
            }
        }
        // signal an increment at the final states (post-processing)
        *signal_column_increment = 1;
    }

    // processing automata -- conditional sub-automata (2)
    // signal a on_row_iterated for all elements lying in this range
    if (is_last_column(mat, *columns)) {
        // signal a on_row_iterated for the last column only
        if (NULL != proc.on_row_iterated) {
            __code = proc.on_row_iterated(proc_sig);
            if (PASS != __code) {
                return __code;
            }
        }
    }

    // post-processing automata
    // signal a on_entry_iterated
    __code = proc.on_entry_iterated(proc_sig);

    // Update the machine input
    *rows = (*rows + 1) % mat.m; // increment the rows, but protect memory accessibility!

    if (*signal_column_increment) {
        *columns = *columns + 1;
        *signal_column_increment = 0;
    }
    return __code;
}

status_code mat_iterate_elements(matrix mat, mat_iterator iterator, mat_processors proc) {
    caller_graph caller = {
        .api = "arithmos:matrix#mat_iterate_elements",
        .func = &mat_iterate_elements,
        .params = NULL,
        .return_value = NULL,
        .root = proc.root
    };

    mat_proc_sig proc_sig = {
        .proc = proc,
        .caller = caller,
        .metadata = proc.metadata
    };

    // pre-processing automata -- Validate main matrix memory addresses
    if (NULL == mat.element || 0 == mat.m || 0 == mat.n ||
            NULL == proc.on_entry_iterated) {
        return EUNDEFINEDBUFFER;
    }

    // preprocessing automata -- Local automatic stack allocation
    // those are grouped into a set of input sigma
    // the sigmas are the language recognized by the machine
    status_code __code;
    uint8_t signal_increment = 0;
    uint64_t rows = 0;
    uint64_t columns = 0;
    uint64_t elements = 0;

    for (;elements < mat.m * mat.n; elements++) {
        if (iterator == ROW_CONVENTION_ITERATOR) {
            __code = row_convention_iterator(mat, proc, &rows, &columns,
                                    &signal_increment,
                                    &caller);
        } else {
            __code = column_convention_iterator(mat, proc, &rows, &columns,
                                       &signal_increment,
                                       &caller);
        }
        if (PASS != __code) {
            if (NULL != proc.on_op_failure) {
                proc.on_op_failure(proc_sig, __code);
            }
            return __code;
        }
    }
    return PASS;
}