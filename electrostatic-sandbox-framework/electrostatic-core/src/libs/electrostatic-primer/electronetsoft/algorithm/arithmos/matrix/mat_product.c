#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/matrix/matrix.h>

struct mat_product_metadata {
    matrix *m0;
    matrix *m1;
    matrix *output;
    mat_processors *processors;
    vec_component *cache;
    uint64_t *dot_prod_index;
};

static inline status_code __on_entry_iterated(mat_proc_sig proc_sig) {
    // preprocessing automata -- Machine Input
    uint64_t row = proc_sig.row_index;
    uint64_t column = proc_sig.col_index;
    struct mat_product_metadata *metadata = proc_sig.proc.metadata;

    matrix m0 = *(metadata->m0);
    matrix m1 = *(metadata->m1);
    matrix *out = metadata->output;
    mat_processors user_proc = *(metadata->processors);
    vec_component *cache = metadata->cache;

    uint64_t dot_prod_index = *(metadata->dot_prod_index);

    status_code __code;

    // preprocessing automata -- Execute preprocessing sub-automata
    if (NULL != user_proc.on_binary_op_preprocessor) {
        __code = user_proc.on_binary_op_preprocessor((mat_binary_op_sig) {
                .m0 = m0,
                .m1 = m1,
                .row_index = row,
                .col_index = column,
                .proc = user_proc,
                .metadata = user_proc.metadata
        });
        if (PASS != __code) {
            return __code;
        }
    }

    // processing automata
    *cache += m0.element[dot_prod_index][row] * m1.element[row][column];

//    if (NULL != user_proc.on_binary_op_postprocessor) {
//        __code = user_proc.on_binary_op_postprocessor((mat_binary_op_sig) {
//                .m0 = m0,
//                .m1 = m1,
//                .row_index = row,
//                .col_index = column,
//                .proc = user_proc,
//                .metadata = user_proc.metadata
//        });
//        if (PASS != __code) {
//            return __code;
//        }
//    }

    // postprocessing automata -- test the column
    if (is_last_row(m1, row)) {
        out->element[dot_prod_index][column] = *cache;
        *cache = (vec_component) 0; // reset cache value

        if (NULL != user_proc.on_elementary_op_postprocessor) {
            __code = user_proc.on_elementary_op_postprocessor(
                    (mat_proc_sig) {
                        .mat = *out,
                        .row_index = dot_prod_index,
                        .col_index = column,
                        .metadata = user_proc.metadata
                    });
            if (PASS != __code) {
                return __code;
            }
        }
    }

    return PASS;
}

static inline status_code __on_row_iterated(mat_proc_sig proc_sig) {
    // preprocessing automata -- Machine Input
    uint64_t row = proc_sig.row_index; // the row buffer index
    uint64_t column = proc_sig.col_index;
    struct mat_product_metadata *metadata = proc_sig.proc.metadata;

    matrix m0 = *(metadata->m0);
    matrix m1 = *(metadata->m1);
    matrix *out = metadata->output;
    mat_processors user_proc = *(metadata->processors);
    vec_component *cache = metadata->cache;

    uint64_t *dot_prod_index = metadata->dot_prod_index;
    *dot_prod_index = row;

    status_code __code;

    mat_processors __proc = {
         .on_entry_iterated = &__on_entry_iterated,
         .metadata = metadata,
    };

    // processing automata
    __code = mat_iterate_elements(m1, COLUMN_CONVENTION_ITERATOR, __proc);
    if (PASS != __code) {
        if (NULL != user_proc.on_op_failure) {
            user_proc.on_op_failure(proc_sig, __code);
        }
        return __code;
    }

    return PASS;
}

status_code mat_product(matrix m0, matrix m1,
                        matrix *out, mat_processors processors) {

    caller_graph caller = {
        .api = "arithmos:matrix#mat_product",
        .func = &mat_product,
        .params = NULL,
        .root = processors.root,
    };

    mat_proc_sig proc_sig = {
        .proc = processors,
        .caller = caller,
        .metadata = processors.metadata
    };

    if (NULL == out || NULL == out->element ||
            NULL == m0.element || NULL == m1.element) {
        if (NULL != processors.on_op_failure) {
            processors.on_op_failure(proc_sig, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    proc_sig.mat = *out;

    // preprocessing automata -- validating the general predicate
    // P (m*n x n*q == m*q); general predicate for matrix product
    if (m0.n != m1.m ||
            out->m != m0.m ||
                out->n != m1.n) {
        if (NULL != processors.on_op_failure) {
            processors.on_op_failure(proc_sig, EBUFFERTURNCATION);
        }
        return EBUFFERTURNCATION;
    }

    vec_component cache;

    uint64_t dot_prod_index;

    struct mat_product_metadata metadata = {
        .m0 = &m0,
        .m1 = &m1,
        .output = out,
        .processors = &processors, // performed a chained automata processors
        .cache = &cache,
        .dot_prod_index = &dot_prod_index
    };

    mat_processors __proc = {
        .on_row_iterated = &__on_row_iterated,
        .metadata = &metadata
    };

    status_code __code = mat_iterate_rows(m0, __proc);
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
