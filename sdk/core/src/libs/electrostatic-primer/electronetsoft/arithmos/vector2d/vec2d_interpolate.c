#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_interpolate(vector2d v0, vector2d v1,
                              vec_component scale, vector2d *out,
                              vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // 1) find the absolute x_distance and y_distance
    vec_component x_distance = vector2d_abs(v0.x - v1.x);
    vec_component y_distance = vector2d_abs(v0.y - v1.y);
    // 2) interpolate between components with a scale starting from the first vector
    out->x = ((x_distance) * scale) + v0.x;
    out->y = ((y_distance) * scale) + v0.y;

    return PASS;
}
