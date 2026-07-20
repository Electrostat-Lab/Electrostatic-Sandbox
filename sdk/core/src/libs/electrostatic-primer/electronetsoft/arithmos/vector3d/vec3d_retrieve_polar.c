#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_retrieve_polar(vector3d v, vec3d_polar *out,
                                 vec3d_processors *processors) {
    if (rvalue(out) == NULL) {
        vec3d_safe_exec_failure(&vec3d_retrieve_polar,
                                processors, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }

    status_code __code;

    // the radius component
    __code = vec3d_length(v, &(out->r), processors);
    if (PASS != __code) {
        vec3d_safe_exec_failure(&vec3d_retrieve_polar,
                                processors, __code);
        return __code;
    }

    vec_component v_xy = vector2d_sqrt((v.x * v.x) + (v.y * v.y));

    out->phi = vector2d_atan2(v.y, v.x);
    out->theta = vector2d_atan2(v_xy, v.z);

    vec3d_safe_exec_success(v, &vec3d_retrieve_polar, processors);

    return PASS;
}
