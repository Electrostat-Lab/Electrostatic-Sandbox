#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_abs(vector3d in, vector3d *out, vec3d_processors *procs) {
    if (NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    out->x = vector2d_abs(in.x);
    out->y = vector2d_abs(in.y);
    out->z = vector2d_abs(in.z);
}