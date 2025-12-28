#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_scalar_divide(vector2d v0, vec_component scalar,
                                vector2d *out, vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    out->x = v0.x / scalar;
    out->y = v0.y / scalar;

    return PASS;
}
