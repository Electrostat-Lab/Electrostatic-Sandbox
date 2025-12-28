#include <electronetsoft/arithmos/vectorspaces/matrix/matrix.h>

status_code mat_scalar_divide(matrix m, vec_component scalar,
                              matrix *out, mat_processors processors) {
    caller_graph caller = {
            .api = "arithmos:matrix#mat_scalar_divide",
            .func = &mat_scalar_divide,
            .params = NULL,
            .root = processors.root,
    };

    mat_proc_sig proc_sig = {
            .proc = processors,
            .caller = caller,
            .metadata = processors.metadata
    };

    return mat_scalar_prod(m, 1/scalar, out, processors);
}
