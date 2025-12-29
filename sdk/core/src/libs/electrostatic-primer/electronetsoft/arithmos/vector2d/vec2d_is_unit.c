#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <math.h>

status_code vec2d_is_unit(vector2d v, vec2d_processors *procs) {
    vec_component out;
    status_code __code = vec2d_length(v, &out, NULL);
    if (__code != PASS) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec2d_is_unit, __code);
        }
        return __code;
    }

    if (round(out) != 1) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec2d_is_unit, ASSERTION_FAILURE);
        }
        return ASSERTION_FAILURE;
    }

    if (NULL != procs && NULL != procs->on_op_success) {
        procs->on_op_success(&vec2d_is_unit, v);
    }

    return PASS;
}