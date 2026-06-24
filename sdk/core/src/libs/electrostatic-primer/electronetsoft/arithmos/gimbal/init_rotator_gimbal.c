#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>
#include <electronetsoft/arithmos/vectorspaces/matrix/matrix3.h>
#include <stdio.h>

status_code init_rotator_gimbal(vector3d axis, matrix orientation,
                                            matrix *__rotator,
                                            vec_component angle) {

    if (NULL == __rotator || NULL == __rotator->element) {
        return EUNDEFINEDBUFFER;
    }

    mat3_gimbal gimbal = {
          .gimbal3d = (vec3d_gimbal) {
              .orientation = &orientation
          }
    };

    status_code __code = mat3_get_axis_orientation(gimbal, axis, &axis) &
             vec3d_abs(axis, &axis, NULL);

    if (PASS != __code) {
        return __code;
    }

    if (get_vec_gimbal(axis) == GIMBAL_Z) {
        // rotate around z-axis
        // pre-processing automata
        // Let the X-axis in the R(3) space be the X-axis in the 2D projection.
        // Let the Y-axis in the R(3) space be the Y-axis in the 2D projection.

        // work in XY plane

        __rotator->element[0][0] = vector2d_cos(angle);
        __rotator->element[0][1] = -vector2d_sin(angle);
        __rotator->element[0][2] = 0.0f;
        __rotator->element[1][0] = vector2d_sin(angle);
        __rotator->element[1][1] = vector2d_cos(angle);
        __rotator->element[1][2] = 0.0f;
        __rotator->element[2][0] = 0.0f;
        __rotator->element[2][1] = 0.0f;
        __rotator->element[2][2] = 1.0f;

    } else if (get_vec_gimbal(axis) == GIMBAL_Y) {
        // rotate around y-axis
        // pre-processing automata
        // Let the X-axis in the R(3) space be the X-axis in the 2D projection.
        // Let the Z-axis in the R(3) space be the Y-axis in the 2D projection.

        // work in XZ plane
        __rotator->element[0][0] = vector2d_cos(angle);
        __rotator->element[0][1] = 0.0f;
        __rotator->element[0][2] = -vector2d_sin(angle);
        __rotator->element[1][0] = 0.0f;
        __rotator->element[1][1] = 1;
        __rotator->element[1][2] = 0.0f;
        __rotator->element[2][0] = vector2d_sin(angle);
        __rotator->element[2][1] = 0.0f;
        __rotator->element[2][2] = vector2d_cos(angle);

    } else if (get_vec_gimbal(axis) == GIMBAL_X) {

        // rotate around x-axis
        // pre-processing automata
        // Let the Z-axis in the R(3) space be the X-axis in the 2D projection.
        // Let the Y-axis in the R(3) space be the Y-axis in the 2D projection.

        // work in ZY plane
        __rotator->element[0][0] = 1;
        __rotator->element[0][1] = 0.0f;
        __rotator->element[0][2] = 0.0f;
        __rotator->element[1][0] = 0.0f;
        __rotator->element[1][1] = vector2d_cos(angle);
        __rotator->element[1][2] = vector2d_sin(angle);
        __rotator->element[2][0] = 0.0f;
        __rotator->element[2][1] = -vector2d_sin(angle);
        __rotator->element[2][2] = vector2d_cos(angle);

    } else {
        return EINCOMPATTYPE;
    }

    return PASS;
}
