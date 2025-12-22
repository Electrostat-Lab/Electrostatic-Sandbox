#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_angle(vector2d v0, vector2d v1,
                        vec_component *out, vec2d_processors *processors) {
    // 1) find the dot product (inner product)
    vec_component dot_prod;
    status_code __code = vec2d_dot_product(v0, v1, &dot_prod, processors);
    if (PASS != __code) {
        return __code;
    }

    // 2) find the norm of both vectors
    vec_component vec0_norm;
    vec_component vec1_norm;

    __code = vec2d_length(v0, &vec0_norm, processors);
    if (PASS != __code) {
        return __code;
    }
    __code = vec2d_length(v1, &vec1_norm, processors);
    if (PASS != __code) {
        return __code;
    }

    // 3) find the angle of their inner product in this vector space
    *out = vector2d_acos(dot_prod / (vec0_norm * vec1_norm));

    return PASS;
}
