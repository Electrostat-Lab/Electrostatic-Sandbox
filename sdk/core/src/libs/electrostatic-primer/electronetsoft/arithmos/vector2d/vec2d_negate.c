#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_negate(vector2d v, vector2d axis,
                         vector2d *out, vec2d_processors *processors) {
    if (NULL == out) {
        if (NULL != processors && NULL != processors->on_op_failed) {
            processors->on_op_failed(&vec2d_negate, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    out->x = v.x * -1 * axis.x;
    out->y = v.y * -1 * axis.y;

    if (out->x == 0) {
        out->x = v.x;
    }

    if (out->y == 0) {
        out->y = v.y;
    }

    if (NULL != processors && NULL != processors->on_op_success) {
        processors->on_op_success(&vec2d_negate, *out);
    }

    return PASS;
}
