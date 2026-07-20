#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_spherical_to_cylinderical(vec3d_polar sphere,
                                            vec3d_cylinderical *cylinder,
                                            vec3d_processors *processors) {
    if (NULL == cylinder) {
        vec3d_safe_exec_failure(&vec3d_spherical_to_cylinderical, processors, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }

    cylinder->r = sphere.r * vector2d_sin(sphere.theta);
    cylinder->phi = sphere.phi;
    cylinder->z = sphere.r * vector2d_cos(sphere.theta);

    // convert the cylinderical coordinates back to rectangular
    // for a callback pattern
    vec3d_safe_exec_success((vector3d) {
        .x = cylinder->r * vector2d_cos(cylinder->phi),
        .y = cylinder->r * vector2d_sin(cylinder->phi),
        .z = cylinder->z
    }, &vec3d_spherical_to_cylinderical, processors);

    return PASS;
}