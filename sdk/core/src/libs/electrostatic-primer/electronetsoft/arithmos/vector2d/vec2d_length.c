#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_length(vector2d v, vec_component *out,
                         vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    float sum = powf(v.x, 2) + powf(v.y, 2);
    *out = (vec_component) powf(sum, 0.5f);

    return PASS;
}
