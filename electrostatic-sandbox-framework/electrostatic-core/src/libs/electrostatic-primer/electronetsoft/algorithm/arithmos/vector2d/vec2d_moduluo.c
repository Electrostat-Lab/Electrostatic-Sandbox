#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_moduluo(vector2d v0, vector2d v1,
                          vector2d *out, vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    out->x = ((mod_vec_component) v0.x) % ((mod_vec_component) v1.x);
    out->y = ((mod_vec_component) v0.y) % ((mod_vec_component) v1.y);
    return PASS;
}
