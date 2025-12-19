#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_extrapolate(vector3d v0, vector3d v1,
                              vec_component scale, vector3d *out,
                              vec3d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;
    vector2d extrapolated_vec;

    vector2d v0_xy = {
            .x = v0.x,
            .y = v0.y,
    };
    vector2d v0_z = {
            .y = v0.z,
    };

    vector2d v1_xy = {
            .x = v1.x,
            .y = v1.y,
    };
    vector2d v1_z = {
            .y = v1.z,
    };

    __code = vec2d_extrapolate(v0_xy, v1_xy, scale, &extrapolated_vec, NULL);
    if (PASS != __code) {
        return __code;
    }

    out->x = extrapolated_vec.x;
    out->y = extrapolated_vec.y;

    __code = vec2d_extrapolate(v0_z, v1_z, scale, &extrapolated_vec, NULL);
    if (PASS != __code) {
        return __code;
    }

    out->z = extrapolated_vec.y;

    return PASS;
}
