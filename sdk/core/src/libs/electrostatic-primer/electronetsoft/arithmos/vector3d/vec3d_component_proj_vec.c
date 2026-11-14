#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_component_proj_vec(vector3d u, vector3d v,
                                     vec_component *out, vec3d_processors *proc) {
    if (NULL == out) {
        vec3d_safe_exec_failure(&vec3d_component_proj_vec, proc, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }

    vector3d __norm_v = {0};
    status_code __code = vec3d_normalize(v, &__norm_v, proc);
    if (PASS != __code) {
        vec3d_safe_exec_failure(&vec3d_component_proj_vec, proc, __code);
        return __code;
    }

    __code = vec3d_dot_product(u, __norm_v, out, proc);
    if (PASS != __code) {
        vec3d_safe_exec_failure(&vec3d_component_proj_vec, proc, __code);
        return __code;
    }

    vec3d_safe_exec_success((vector3d) {
        .x = *out
        }, &vec3d_component_proj_vec, proc);

    return PASS;
}