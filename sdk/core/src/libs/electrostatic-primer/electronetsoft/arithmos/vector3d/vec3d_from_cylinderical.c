#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_from_cylinderical(vec3d_cylinderical cylinder,
                                    vector3d *out,
                                    vec3d_processors *processors) {
    if (NULL == out) {
        vec3d_safe_exec_failure(&vec3d_from_cylinderical,
                                processors, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }

    out->x = cylinder.r * vector2d_cos(cylinder.phi);
    out->y = cylinder.r * vector2d_sin(cylinder.phi);
    out->z = cylinder.z;

    vec3d_safe_exec_success(*out, &vec3d_from_cylinderical, processors);

    return PASS;
}