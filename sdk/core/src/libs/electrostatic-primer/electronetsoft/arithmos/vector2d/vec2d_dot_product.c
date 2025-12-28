#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_dot_product(vector2d v0, vector2d v1,
                              vec_component *out, vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    *out = v0.x * v1.x + v0.y * v1.y;
    return PASS;
}
