#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_component_proj_vec(vector2d v1, vector2d v2, vec_component *out, vec2d_processors *procs) {
    if (NULL == out) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec2d_component_proj_vec, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    vector2d __norm_v2 = {0};

    status_code __code = vec2d_normalize(v2, &__norm_v2, procs);
    if (PASS != __code) {
        return __code;
    }

    __code = vec2d_dot_product(v1, __norm_v2, out, procs);
    if (PASS != __code) {
        return __code;
    }

    if (NULL != procs && NULL != procs->on_op_success) {
        procs->on_op_success(&vec2d_component_proj_vec, (vector2d) {
            .x = *out
        });
    }

    return PASS;
}