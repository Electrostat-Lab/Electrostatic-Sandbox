#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_normalize(vector3d v, vector3d *out, vec3d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    vec_component length;
    status_code __code = vec3d_length(v, &length, processors);
    if (PASS != __code) {
        return __code;
    }

    return vec3d_scalar_divide(v, length, out, processors);
}
