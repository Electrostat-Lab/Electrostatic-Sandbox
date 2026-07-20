#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_retrieve_cylinderical(vector3d vec3d,
                                        vec3d_cylinderical *cylinder,
                                        vec3d_processors *processors) {
    if (NULL == cylinder) {
        vec3d_safe_exec_failure(&vec3d_retrieve_cylinderical,
                                processors, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }

    vec3d_polar polar = {0};
    status_code __code = vec3d_retrieve_polar(vec3d, &polar, processors);
    if (PASS != __code) {
        vec3d_safe_exec_failure(&vec3d_retrieve_cylinderical,
                                processors, __code);
        return __code;
    }

    // The horizontal radius is the 3D radius projected onto the XY plane
    cylinder->r = polar.r * vector2d_sin(polar.theta);

    // CORRECT: The azimuthal angle remains identical
    cylinder->phi = polar.phi;

    // CORRECT: The height is the projection onto the Z axis
    cylinder->z = polar.r * vector2d_cos(polar.theta);

    vec3d_safe_exec_success(vec3d, &vec3d_retrieve_cylinderical, processors);

    return PASS;
}
