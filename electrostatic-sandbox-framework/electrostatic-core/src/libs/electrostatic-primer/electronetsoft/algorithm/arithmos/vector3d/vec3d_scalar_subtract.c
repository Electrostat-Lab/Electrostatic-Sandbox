#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_scalar_subtract(vector3d v, vec_component scalar,
                                  vector3d *out, vec3d_processors *processors) {
    return vec3d_scalar_add(v, -scalar, out, processors);
}
