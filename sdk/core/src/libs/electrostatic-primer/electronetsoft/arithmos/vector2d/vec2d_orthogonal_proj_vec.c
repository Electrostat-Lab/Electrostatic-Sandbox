#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_orthogonal_proj_vec(vector2d v1, vector2d v2, vector2d *out, vec2d_processors *procs) {
    if (NULL == out) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec2d_orthogonal_proj_vec, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    vector2d __proj_uv = {0};
    status_code __code = vec2d_projection_vector(v1, v2, &__proj_uv, procs);
    if (PASS != __code) {
        return __code;
    }

    __code = vec2d_subtract(v1, __proj_uv, out, procs);
    if (PASS != __code) {
        return __code;
    }

    if (NULL != procs && NULL != procs->on_op_success) {
        procs->on_op_success(&vec2d_orthogonal_proj_vec, *out);
    }

    return PASS;
}