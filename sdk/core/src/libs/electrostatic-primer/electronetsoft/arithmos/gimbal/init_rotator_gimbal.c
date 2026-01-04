#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>

status_code init_rotator_gimbal(vector3d axis, matrix *__rotator,
                                            vec_component angle,
                                            vec_component *angle1,
                                            vec3d_gimbal *gimbal) {

    if (NULL == __rotator || NULL == __rotator->element) {
        return EUNDEFINEDBUFFER;
    }

    if (get_vec_gimbal(axis) == GIMBAL_Z) {
    // rotate around z-axis
    // pre-processing automata
    // Let the X-axis in the R(3) space be the X-axis in the 2D projection.
    // Let the Y-axis in the R(3) space be the Y-axis in the 2D projection.

    // work in XY plane
    __rotator->element[0][0] = vector2d_cos(angle);
    __rotator->element[0][1] = -vector2d_sin(angle);
    __rotator->element[1][0] = vector2d_sin(angle);
    __rotator->element[1][1] = vector2d_cos(angle);
    __rotator->element[2][2] = 1;

    if (NULL != gimbal && NULL != angle1) {
        gimbal->z_gimbal += angle;
        *angle1 = gimbal->z_gimbal;
    }

    } else if (get_vec_gimbal(axis) == GIMBAL_Y) {
    // rotate around y-axis
    // pre-processing automata
    // Let the X-axis in the R(3) space be the X-axis in the 2D projection.
    // Let the Z-axis in the R(3) space be the Y-axis in the 2D projection.

    // work in XZ plane
    __rotator->element[0][0] = vector2d_cos(angle);
    __rotator->element[0][2] = -vector2d_sin(angle);
    __rotator->element[2][0] = vector2d_sin(angle);
    __rotator->element[2][2] = vector2d_cos(angle);
    __rotator->element[1][1] = 1;

    if (NULL != gimbal && NULL != angle1) {
        gimbal->y_gimbal += angle;
        *angle1 = gimbal->y_gimbal;
    }

    } else if (get_vec_gimbal(axis) == GIMBAL_X) {

    // rotate around x-axis
    // pre-processing automata
    // Let the Z-axis in the R(3) space be the X-axis in the 2D projection.
    // Let the Y-axis in the R(3) space be the Y-axis in the 2D projection.

    // work in ZY plane
    __rotator->element[2][2] = vector2d_cos(angle);
    __rotator->element[2][1] = -vector2d_sin(angle);
    __rotator->element[1][2] = vector2d_sin(angle);
    __rotator->element[1][1] = vector2d_cos(angle);
    __rotator->element[0][0] = 1;

    if (NULL != gimbal && NULL != angle1) {
        gimbal->x_gimbal += angle;
        *angle1 = gimbal->x_gimbal;
    }

    } else {
        return EINCOMPATTYPE;
    }

    return PASS;
}
