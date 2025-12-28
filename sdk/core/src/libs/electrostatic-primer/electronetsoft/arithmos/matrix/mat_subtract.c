#include <electronetsoft/arithmos/vectorspaces/matrix/matrix.h>

struct mat_subtract_metadata {
    matrix *m1;
    matrix *output;
    mat_processors *processors;
};

static inline status_code __on_entry_iterated(mat_proc_sig proc_sig) {
    // preprocessing automata -- Machine Input
    matrix m0 = proc_sig.mat;
    uint64_t row = proc_sig.row_index;
    uint64_t column = proc_sig.col_index;
    struct mat_subtract_metadata *metadata = proc_sig.proc.metadata;

    matrix m1 = *(metadata->m1);
    matrix *out = metadata->output;
    mat_processors user_proc = *(metadata->processors);
    status_code __code;

    // preprocessing automata -- Execute preprocessing sub-automata
    if (NULL != user_proc.on_binary_op_preprocessor) {
        __code = user_proc.on_binary_op_preprocessor((mat_binary_op_sig) {
            .m0 = m0,
            .m1 = m1,
            .row_index = row,
            .col_index = column,
            .proc = user_proc,
        });
        if (PASS != __code) {
            return __code;
        }
    }

    // processing automata
    out->element[row][column] =
            m0.element[row][column] - m1.element[row][column];

    // postprocessing chain
    if (NULL != user_proc.on_elementary_op_postprocessor) {
        __code = user_proc.on_elementary_op_postprocessor(proc_sig);
        if (PASS != __code) {
            return __code;
        }
    }

    return PASS;
}

status_code mat_subtract(matrix m0, matrix m1, matrix *out,
                         mat_processors processors) {
    caller_graph caller = {
        .api = "arithmos:matrix#mat_subtract",
        .func = &mat_subtract,
        .params = NULL,
        .root = processors.root,
    };

    mat_proc_sig proc_sig = {
        .proc = processors,
        .caller = caller,
        .metadata = processors.metadata
    };

    if (rvalue(out) == NULL ||
        rvalue(out->element) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    proc_sig.mat = *out;

    if (m0.m != m1.m ||
        m0.n != m1.n ||
        m0.m != out->m ||
        m0.n != out->n) {
        return EBUFFERTURNCATION;
    }

    struct mat_subtract_metadata metadata = {
        .m1 = &m1,
        .output = out,
        .processors = &processors, // performed a chained automata processors
    };

    mat_processors __proc = {
        .on_entry_iterated = &__on_entry_iterated,
        .metadata = &metadata
    };

    status_code __code = mat_iterate_elements(m0, ROW_CONVENTION_ITERATOR, __proc);
    if (PASS != __code) {
        if (NULL != processors.on_op_failure) {
            processors.on_op_failure(proc_sig, __code);
        }
        return __code;
    }

    if (NULL != processors.on_op_success) {
        processors.on_op_success(proc_sig);
    }

    return PASS;
}