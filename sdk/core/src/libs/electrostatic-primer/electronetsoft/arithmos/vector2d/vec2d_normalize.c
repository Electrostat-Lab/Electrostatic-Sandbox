#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_normalize(vector2d v, vector2d *out, vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    vec_component length;
    status_code __code = vec2d_length(v, &length, processors);
    if (PASS != __code) {
        return __code;
    }

    return vec2d_scalar_divide(v, length, out, processors);
}
