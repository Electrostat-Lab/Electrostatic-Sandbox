#include <electronetsoft/arithmos/vectorspaces/matrix/matrix.h>

status_code mat_create_from_vector3d(vector3d v, matrix *mat, mat_processors processors) {
    caller_graph caller = {
            .api = "arithmos:matrix#mat_create_from_vector3d",
            .func = &mat_create_from_vector3d,
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

    proc_sig.mat = *mat;

    // preprocessor automata -- Test elements allocation
    if (rvalue(mat->element + 1) == NULL || rvalue(mat->element + 2) == NULL) {
        if (NULL != processors.on_op_failure) {
            processors.on_op_failure(proc_sig, EBUFFERTURNCATION);
        }
        return EBUFFERTURNCATION;
    }

    // processing automata -- Adapt elements
    *(mat->element[0]) = v.x;
    *(mat->element[1]) = v.y;
    *(mat->element[2]) = v.z;

    return PASS;
}