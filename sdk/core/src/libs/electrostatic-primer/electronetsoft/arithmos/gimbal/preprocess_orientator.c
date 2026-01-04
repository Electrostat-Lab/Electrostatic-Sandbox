#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>

void preprocess_orientator(vector3d *v, vector3d *axis) {

    // create a column vector matrix
    vec_component axis_x[1] = {axis->x,};
    vec_component axis_y[1] = {axis->y,};
    vec_component axis_z[1] = {axis->z,};
    vec_component *axis_comps[3] = {axis_x, axis_y, axis_z};
    matrix __axis = {
            .element = axis_comps,
            .m = 3,
            .n = 1
    };

    // find the position of the orientation vectors
    vec_component _axis_x[1] = {0,};
    vec_component _axis_y[1] = {0,};
    vec_component _axis_z[1] = {0,};
    vec_component *_axis_comps[3] = {_axis_x, _axis_y, _axis_z};
    matrix ___axis = {
            .element = _axis_comps,
            .m = 3,
            .n = 1
    };

    mat_processors proc = {
    };

    mat_product(*(v->gimbal.orientation), __axis, &___axis, proc);

    axis->x = *(___axis.element[0]);
    axis->y = *(___axis.element[1]);
    axis->z = *(___axis.element[2]);
}
