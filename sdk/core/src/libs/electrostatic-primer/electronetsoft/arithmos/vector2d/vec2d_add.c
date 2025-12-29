#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_add(vector2d v0, vector2d v1, vector2d *out,
                      vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        if (NULL != processors && NULL != processors->on_op_failed) {
            processors->on_op_failed(&vec2d_add, EUNDEFINEDBUFFER);
        }
        return EUNDEFINEDBUFFER;
    }

    out->x = v0.x + v1.x;
    out->y = v0.y + v1.y;

    if (NULL != processors && NULL != processors->on_op_success) {
        processors->on_op_success(&vec2d_add, *out);
    }

    return PASS;
}
