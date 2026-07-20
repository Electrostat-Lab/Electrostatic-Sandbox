#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_from_polar(vec3d_polar polar,
                             vector3d *out,
                             vec3d_processors *processors) {
    if (NULL == out) {
        vec3d_safe_exec_failure(&vec3d_from_polar,
                                processors, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }

    out->x = (polar.r * vector2d_sin(polar.theta)) * vector2d_cos(polar.phi);
    out->y = (polar.r * vector2d_sin(polar.theta)) * vector2d_sin(polar.phi);
    out->z = polar.r * vector2d_cos(polar.theta);

    vec3d_safe_exec_success(*out, &vec3d_from_polar, processors);

    return PASS;
}