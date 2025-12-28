#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_is_rotated(vector2d v0, vector2d v1, vec_component angle,
                             vec2d_processors *processors) {
    vector2d vec = {};
    vec.x = v0.x * vector2d_cos(angle) - v0.y * vector2d_sin(angle);
    vec.y = v0.x * vector2d_sin(angle) + v0.y * vector2d_cos(angle);

    if (v1.x != vec.x || v1.y != vec.y) {
        if (NULL != processors && NULL != processors->on_op_failed) {
            processors->on_op_failed(&vec2d_is_rotated, ASSERTION_FAILURE);
        }
        return ASSERTION_FAILURE;
    }

    if (NULL != processors && NULL != processors->on_op_success) {
        processors->on_op_success(&vec2d_is_rotated, v1);
    }

    return PASS;
}