#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_subtract(vector3d v0, vector3d v1,
                           vector3d *out, vec3d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // find the negation of v1
    status_code __code;
    vector3d neg_v1;
    vector3d neg_unit = {
            .x = (vec_component) -1,
            .y = (vec_component) -1,
            .z = (vec_component) -1
    };

    __code = vec3d_product(v1, neg_unit, &neg_v1, processors);
    if (PASS != __code) {
        return __code;
    }
    // calculate the addition primitive op.

    return vec3d_add(v0, neg_v1, out, processors);
}
