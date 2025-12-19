#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_scalar_subtract(vector2d v, vec_component scalar,
                                  vector2d *out, vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    out->x = v.x - scalar;
    out->y = v.y - scalar;
    return PASS;
}
