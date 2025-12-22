#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_scalar_add(vector2d vec, vec_component scalar, vector2d *out,
                             vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    out->x = vec.x + scalar;
    out->y = vec.y + scalar;

    return PASS;
}
