#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_swap_components(vector2d v, vector2d *out, vec2d_processors *processors) {
    if (NULL == out) {
        if (NULL != processors && NULL != processors->on_op_failed) {
            processors->on_op_failed(&vec2d_swap_components, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    out->x = v.y;
    out->y = v.x;

    if (NULL != processors && NULL != processors->on_op_success) {
        processors->on_op_success(&vec2d_swap_components, *out);
    }

    return PASS;
}