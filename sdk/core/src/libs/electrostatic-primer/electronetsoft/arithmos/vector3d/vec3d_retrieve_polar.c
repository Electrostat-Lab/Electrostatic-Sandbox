#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_retrieve_polar(vector3d v, vec3d_polar *out,
                                 vec3d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    vec2d_polar polar_vector;
    status_code __code;

    vector2d v_xy = {
        .x = v.x,
        .y = v.y,
    };
    vector2d v_z = {
        .y = v.z,
    };

    __code = vec3d_length(v, &(out->r), processors);
    if (PASS != __code) {
        return __code;
    }

    __code = vec2d_retrieve_polar(v_xy, &polar_vector, NULL);
    if (PASS != __code) {
        return __code;
    }

    out->phi = polar_vector.phi;

    // find the resultant vector component of the XY plane
    // put the result into the v_z (x component)
    __code = vec2d_length(v_xy, &(v_z.x), NULL);
    if (PASS != __code) {
        return __code;
    }

    __code = vec2d_retrieve_polar(v_z, &polar_vector, NULL);
    if (PASS != __code) {
        return __code;
    }

    out->theta = polar_vector.phi;

    return PASS;
}
