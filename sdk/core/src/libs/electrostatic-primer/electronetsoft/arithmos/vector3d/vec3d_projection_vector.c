#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_projection_vector(vector3d u, vector3d v,
                                    vector3d *out, vec3d_processors *proc) {
    if (NULL == out) {
        vec3d_safe_exec_failure(&vec3d_projection_vector, proc, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }

    // the magnitude of the projection vector of u on v
    // is essentially the same as calculating
    // the dot product of u and v and dividing it by
    // the length of v
    // or the dot product of u and the unit vector of v
    // which yields the component of u in the direction of v

    // the direction of the proj_uv vector
    // is coincident on the v vector
    vector3d __unit_v = {0};
    status_code __code = vec3d_normalize(v, &__unit_v, proc);
    if (PASS != __code) {
        vec3d_safe_exec_failure(&vec3d_projection_vector, proc, __code);
        return __code;
    }

    // the magnitude of the proj_uv vector
    // is calculated by the dot product of u and unit_v
    vec_component __dot_u_norm_v = {0};
    __code = vec3d_dot_product(u, __unit_v, &__dot_u_norm_v, proc);
    if (PASS != __code) {
        vec3d_safe_exec_failure(&vec3d_projection_vector, proc, __code);
        return __code;
    }

    __code = vec3d_scalar_multiply(__unit_v, __dot_u_norm_v,
                                   out, proc);
    if (PASS != __code) {
        vec3d_safe_exec_failure(&vec3d_projection_vector, proc, __code);
        return __code;
    }

    vec3d_safe_exec_success(*out, &vec3d_projection_vector, proc);

    return PASS;
}