#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

vector3d VEC3_X_COMPONENT = {
    .x = 1,
    .y = 0,
    .z = 0
};

vector3d VEC3_Y_COMPONENT = {
    .x = 0,
    .y = 1,
    .z = 0
};

vector3d VEC3_Z_COMPONENT = {
    .x = 0,
    .y = 0,
    .z = 1
};

status_code vec3d_component(vector3d v, vector3d comp,
                              vector3d *out, vec3d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    return vec3d_product(v, comp, out, processors);
}