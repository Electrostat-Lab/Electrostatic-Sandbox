#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_are_equal(vector2d v0, vector2d v1, vec2d_processors *processors) {

    if (v0.x != v1.x || v0.y != v1.y) {
        if (NULL != processors && NULL != processors->on_op_failed) {
            processors->on_op_failed(&vec2d_are_equal, ASSERTION_FAILURE);
        }
        return ASSERTION_FAILURE;
    }

    if (NULL != processors && NULL != processors->on_op_success) {
        processors->on_op_success(&vec2d_are_equal, v1);
    }

    return PASS;
}