#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_cylinderical_to_spherical(vec3d_cylinderical cylinder,
                                            vec3d_polar *sphere,
                                            vec3d_processors *processors) {
    if (NULL == sphere) {
        vec3d_safe_exec_failure(&vec3d_cylinderical_to_spherical, processors, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }

    sphere->r = vector2d_sqrt(vector2d_pow(cylinder.r, 2) + vector2d_pow(cylinder.z, 2));
    sphere->phi = cylinder.phi;
    // (M_PI/2.0f) - vector2d_atan2(cylinder.z, cylinder.r);
    // is the same as vector2d_atan2(cylinder.r, cylinder.z)
    sphere->theta = vector2d_atan2(cylinder.r, cylinder.z);

    vec3d_safe_exec_success((vector3d) {
            .x = (sphere->r * vector2d_sin(sphere->theta)) * vector2d_cos(sphere->phi),
            .y = (sphere->r * vector2d_sin(sphere->theta)) * vector2d_sin(sphere->phi),
            .z = sphere->r * vector2d_cos(sphere->theta),
        }, &vec3d_cylinderical_to_spherical, processors);

    return PASS;
}