#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/matrix/matrix.h>

struct mat_scalar_prod_metadata {
    matrix *m;
    vec_component scalar;
    matrix *output;
    mat_processors *processors;
};

status_code __on_entry_iterated(mat_proc_sig proc_sig) {
    // preprocessing automata -- Machine Input
    uint64_t row = proc_sig.row_index;
    uint64_t column = proc_sig.col_index;
    struct mat_scalar_prod_metadata *metadata = proc_sig.proc.metadata;

    matrix m = *(metadata->m);
    vec_component scalar = metadata->scalar;
    matrix *out = metadata->output;
    mat_processors user_proc = *(metadata->processors);

    status_code __code;

    // preprocessing automata -- Execute preprocessing sub-automata
    if (NULL != user_proc.on_unary_op_preprocessor) {
        __code = user_proc.on_unary_op_preprocessor((mat_proc_sig) {
                .mat = m,
                .row_index = row,
                .col_index = column,
                .proc = user_proc,
        });
        if (PASS != __code) {
            return __code;
        }
    }

    out->element[row][column] = scalar * m.element[row][column];

    if (NULL != user_proc.on_elementary_op_postprocessor) {
        __code = user_proc.on_elementary_op_postprocessor(
                (mat_proc_sig) {
                        .mat = *out,
                        .row_index = row,
                        .col_index = column,
                });
        if (PASS != __code) {
            return __code;
        }
    }

    return PASS;
}

status_code mat_scalar_product(matrix m, vec_component scalar,
                        matrix *out, mat_processors processors) {

    caller_graph caller = {
            .api = "arithmos:matrix#mat_scalar_product",
            .func = &mat_scalar_product,
            .params = NULL,
            .root = processors.root,
    };

    mat_proc_sig proc_sig = {
            .proc = processors,
            .caller = caller,
            .metadata = processors.metadata
    };

    if (NULL == m.element || NULL == out
            || NULL == out->element) {
        if (NULL != processors.on_op_failure) {
            processors.on_op_failure(proc_sig, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    // preprocessing automata -- validating the general predicate
    if (m.m != out->m || m.n != out->n) {
        if (NULL != processors.on_op_failure) {
            processors.on_op_failure(proc_sig, EBUFFERTURNCATION);
        }
        return EBUFFERTURNCATION;
    }

    proc_sig.mat = m;

    struct mat_scalar_prod_metadata metadata = {
        .m = &m,
        .scalar = scalar,
        .output = out,
        .processors = &processors,
    };

    mat_processors __proc = {
         .on_entry_iterated = &__on_entry_iterated,
         .metadata = &metadata
    };

    // processing automata -- iteration and scalar product
    status_code __code = mat_iterate_elements(m, ROW_CONVENTION_ITERATOR, __proc);

    // post-processing automata
    if (PASS != __code) {
        if (NULL != processors.on_op_failure) {
            processors.on_op_failure(proc_sig, EBUFFERTURNCATION);
        }
        return __code;
    }

    if (NULL != processors.on_op_success) {
        processors.on_op_success(proc_sig);
    }

    return PASS;
}