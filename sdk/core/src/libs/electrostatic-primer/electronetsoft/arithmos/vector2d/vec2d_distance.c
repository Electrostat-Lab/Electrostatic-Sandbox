#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_distance(vector2d v0, vector2d v1,
                           vec_component *out, vec2d_processors  *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    vector2d subtract = {};
    status_code __code = vec2d_subtract(v0, v1, &subtract, processors);
    if (PASS != __code) {
        return __code;
    }

    __code = vec2d_length(subtract, out, processors);
    if (PASS != __code) {
        return __code;
    }

    return PASS;
}
