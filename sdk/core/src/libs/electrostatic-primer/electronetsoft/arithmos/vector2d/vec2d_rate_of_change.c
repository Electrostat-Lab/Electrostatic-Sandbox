#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_rate_of_change(vector2d v0,
                                 vector2d (*vec2d_func)(vec_component x),
                                 vec_component delta_x,
                                 vec_component *out, vec2d_processors *procs) {
    if (NULL == vec2d_func || NULL == out) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec2d_rate_of_change, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    vector2d _v1 = vec2d_func(v0.x + delta_x);

    *out = (_v1.x - v0.x) / (_v1.y - v0.y);

    if (NULL != procs && NULL != procs->on_op_success) {
        procs->on_op_success(&vec2d_rate_of_change, (vector2d) {
            .x = *out
        });
    }
    return PASS;
}