#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_add(vector3d v0, vector3d v1, vector3d *out,
                      vec3d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    vector2d v0_xy = {
        .x = v0.x,
        .y = v0.y,
    };
    vector2d v0_z = {
       .y = v0.z,
    };

    vector2d v1_xy = {
        .x = v1.x,
        .y = v1.y
    };
    vector2d v1_z = {
        .y = v1.z,
    };
    status_code __code;
    vector2d xy_out;
    vector2d z_out;

    __code = vec2d_add(v0_xy, v1_xy, &xy_out, NULL);
    if (PASS != __code) {
        return __code;
    }

    __code = vec2d_add(v0_z, v1_z, &z_out, NULL);
    if (PASS != __code) {
        return __code;
    }

    out->x = xy_out.x;
    out->y = xy_out.y;
    out->z = z_out.y;

    return PASS;
}
