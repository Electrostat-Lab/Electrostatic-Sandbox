#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

vector2d VEC2_X_COMPONENT = {
    .x = 1,
    .y = 0
};

vector2d VEC2_Y_COMPONENT = {
    .x = 0,
    .y = 1
};

status_code vec2d_component(vector2d v, vector2d comp,
                              vector2d *out, vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    return vec2d_product(v, comp, out, processors);
}