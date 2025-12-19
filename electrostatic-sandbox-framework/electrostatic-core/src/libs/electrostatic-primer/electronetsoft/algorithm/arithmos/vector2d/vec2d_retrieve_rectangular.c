#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_retrieve_rectangular(vec2d_polar polar, vector2d *rect,
                                       vec2d_processors *processors) {
    if (rvalue(rect) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    rect->x = polar.r * ((vec_component) cosf(polar.phi));
    rect->y = polar.r * ((vec_component) sinf(polar.phi));

    return PASS;
}