#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_projection_vector(vector2d v, vector2d u, vector2d *proj, vec2d_processors *processors) {
    if (rvalue(proj) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;
    vec_component dot_prod;
    vector2d norm_u;
    vec_component length_u;

    // 1) find the dot product of vectors (v, u)
    __code = vec2d_dot_product(v, u, &dot_prod, processors);
    if (PASS != __code) {
        return __code;
    }

    // 2) find the norm of vector u
    __code = vec2d_normalize(u, &norm_u, processors);
    if (PASS != __code) {
        return __code;
    }

    // 3) find the length of vector u
    __code = vec2d_length(u, &length_u, processors);
    if (PASS != __code) {
        return __code;
    }

    // 4) the component ||v||.cos(theta).n is the projection vector
    __code = vec2d_scalar_multiply(norm_u,
                                   ((vec_component) dot_prod/length_u),
                                   proj, processors);
    if (PASS != __code) {
        return __code;
    }

    return PASS;
}