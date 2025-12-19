#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_length(vector3d v, vec_component *out,
                         vec3d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    status_code __code;

    vector2d v_xy = {
        .x = v.x,
        .y = v.y,
    };
    vector2d v_z = {
        .y = v.z,
    };

    __code = vec2d_length(v_xy, &(v_z.x), NULL);
    if (PASS != __code) {
        return __code;
    }

    __code = vec2d_length(v_z, out, NULL);
    if (PASS != __code) {
        return __code;
    }

    return PASS;
}
