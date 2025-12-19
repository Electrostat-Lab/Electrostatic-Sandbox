#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_subtract(vector2d v0, vector2d v1,
                           vector2d *out, vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    out->x = v0.x - v1.x;
    out->y = v0.y - v1.y;

    return PASS;
}
