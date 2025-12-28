#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

status_code vec2d_create_subspace(vector2d ref_point,
                                  vector2d x_axis, vec2d_space *space,
                                  vec2d_processors *processors) {
    if (rvalue(space) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // 1) subtract the axis from the ref-point to find the x-axis
    vector2d space_x;
    vector2d rotated_x;

    status_code __code;

    __code = vec2d_subtract(ref_point, x_axis,
                            &space_x, processors);
    if (PASS != __code) {
        return __code;
    }

    // 2) rotate the axis by 90 degrees; creating a new vector
//
//    __code = vec2d_rotate(x_axis, ref_point, M_PI_2);
//    if (PASS != __code) {
//        return __code;
//    }

    // 3) normalize both axes and store them in the space

    __code = vec2d_normalize(space_x, &space->x_axis, processors);
    if (PASS != __code) {
        return __code;
    }

    __code = vec2d_normalize(rotated_x, &space->y_axis, processors);
    if (PASS != __code) {
        return __code;
    }

    return PASS;
}