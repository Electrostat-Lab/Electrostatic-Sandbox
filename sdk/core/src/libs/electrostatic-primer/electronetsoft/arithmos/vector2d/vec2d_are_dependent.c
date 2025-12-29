#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_are_dependent(vector2d v0, vector2d v1, vec2d_processors *processors) {

    vector2d out;
    status_code __code = vec2d_divide(v0, v1, &out, processors);
    if (PASS != __code) {
        return __code;
    }

    return out.x == out.y != 0;
}
