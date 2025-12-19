#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_are_parallel(vector2d v0, vector2d v1, vec2d_processors *processors) {

    vec_component dot_prod;
    status_code __code =
            vec2d_dot_product(v0, v1, &dot_prod, processors);
    if (PASS != __code) {
        return __code;
    }

    vec_component v0_len;
    __code = vec2d_length(v0, &v0_len, processors);
    if (PASS != __code) {
        return __code;
    }

    vec_component v1_len;
    __code = vec2d_length(v1, &v1_len, processors);
    if (PASS != __code) {
        return __code;
    }

    return dot_prod == (v0_len * v1_len);
}
