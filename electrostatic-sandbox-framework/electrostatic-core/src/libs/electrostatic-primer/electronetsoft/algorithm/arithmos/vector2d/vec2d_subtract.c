#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_subtract(vector2d v0, vector2d v1,
                           vector2d *out, vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // find the negation of v1
    status_code __code;
    vector2d neg_v1;
    vector2d neg_unit = {
         .x = (vec_component) -1,
         .y = (vec_component) -1,
    };

    __code = vec2d_product(v1, neg_unit, &neg_v1, processors);
    if (PASS != __code) {
        return __code;
    }
    // calculate the addition primitive op.

    return vec2d_add(v0, neg_v1, out, processors);
}
