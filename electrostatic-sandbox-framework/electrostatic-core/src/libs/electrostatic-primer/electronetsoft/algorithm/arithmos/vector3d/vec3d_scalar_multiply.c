#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_scalar_multiply(vector3d v, vec_component scalar,
                                  vector3d *out, vec3d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    vector2d v_xy = {
        .x = v.x,
        .y = v.y,
    };
    vector2d v_z = {
        .y = v.z,
    };

    status_code __code;
    vector2d xy_out;
    vector2d z_out;

    __code = vec2d_scalar_multiply(v_xy, scalar, &xy_out, NULL);
    if (PASS != __code) {
        return __code;
    }

    __code = vec2d_scalar_multiply(v_z, scalar, &z_out, NULL);
    if (PASS != __code) {
        return __code;
    }

    out->x = xy_out.x;
    out->y = xy_out.y;
    out->z = z_out.y;

    return PASS;
}
