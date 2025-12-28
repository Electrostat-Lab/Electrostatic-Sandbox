#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_retrieve_polar(vector2d v, vec2d_polar *out, vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    // calculate length of the vector
    status_code __code = vec2d_length(v, &(out->r), processors);
    if (PASS != __code) {
        return __code;
    }
    out->phi = vector2d_atan2(v.y, v.x);

    return PASS;
}
