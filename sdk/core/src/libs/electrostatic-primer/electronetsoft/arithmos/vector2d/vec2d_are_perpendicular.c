#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_are_perpendicular(vector2d v0, vector2d v1, vec2d_processors *processors) {
    vec_component dot_prod;
    status_code __code =
            vec2d_dot_product(v0, v1, &dot_prod, processors);
    if (PASS != __code) {
        return __code;
    }
    return PASS;
}
