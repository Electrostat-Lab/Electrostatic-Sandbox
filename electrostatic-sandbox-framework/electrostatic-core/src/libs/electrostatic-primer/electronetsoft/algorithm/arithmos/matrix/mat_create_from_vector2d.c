#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/matrix/matrix.h>

status_code mat_create_from_vector2d(vector2d v, matrix *mat, mat_processors processors) {
    caller_graph caller = {
            .api = "arithmos:matrix#mat_create_from_vector2d",
            .func = &mat_create_from_vector2d,
            .root = processors.root,
    };

    mat_proc_sig proc_sig = {
            .proc = processors,
            .caller = caller,
            .metadata = processors.metadata,
    };

    // preprocessor automata -- Test main matrix memory addresses
    if (rvalue(mat) == NULL ||
                rvalue(mat->element) == NULL) {
        if (NULL != processors.on_op_failure) {
            processors.on_op_failure(proc_sig, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    // preprocessor automata -- Test elements allocation
    if (rvalue(mat->element + 1) == NULL) {
        if (NULL != processors.on_op_failure) {
            processors.on_op_failure(proc_sig, EBUFFERTURNCATION);
        }
        return EBUFFERTURNCATION;
    }

    proc_sig.mat = *mat;

    // processing automata -- Adapt elements
    *(mat->element[0]) = v.x;
    *(mat->element[1]) = v.y;

    if (NULL != processors.on_op_success) {
        processors.on_op_success(proc_sig);
    }

    return PASS;
}