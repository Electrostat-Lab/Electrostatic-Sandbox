#include <electronetsoft/arithmos/vectorspaces/matrix/matrix.h>

status_code mat_iterate_rows(matrix mat, mat_processors proc) {
    caller_graph caller = {
            .api = "arithmos:matrix#mat_iterate_rows",
            .func = &mat_iterate_rows,
            .params = NULL,
            .root = proc.root,
    };

    mat_proc_sig proc_sig = {
            .proc = proc,
            .caller = caller,
            .metadata = proc.metadata
    };

    if (NULL == mat.element || 0 == mat.m || NULL == proc.on_row_iterated) {
        return EUNDEFINEDBUFFER;
    }

    for (uint64_t i = 0; i < mat.m; i++) {
        proc_sig.row_index = i;

        status_code __code = proc.on_row_iterated(proc_sig);
        if (PASS != __code) {
            if (NULL != proc.on_op_failure) {
                proc.on_op_failure(proc_sig, __code);
            }
            return __code;
        }
    }

    return PASS;
}