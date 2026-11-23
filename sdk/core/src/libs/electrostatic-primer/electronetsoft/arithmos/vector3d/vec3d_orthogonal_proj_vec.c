#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_orthogonal_proj_vec(vector3d u, vector3d v,
                                      vector3d *out, vec3d_processors *proc) {
    if (NULL == out) {
        vec3d_safe_exec_failure(&vec3d_orthogonal_proj_vec, proc, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }

    vector3d __proj_uv = {0};
    status_code __code = vec3d_projection_vector(u, v, &__proj_uv, proc);
    if (PASS != __code) {
        vec3d_safe_exec_failure(&vec3d_orthogonal_proj_vec, proc, __code);
        return __code;
    }

    __code = vec3d_subtract(u, __proj_uv, out, proc);
    if (PASS != __code) {
        vec3d_safe_exec_failure(&vec3d_orthogonal_proj_vec, proc, __code);
        return __code;
    }

    vec3d_safe_exec_success(*out, &vec3d_orthogonal_proj_vec, proc);

    return PASS;
}