#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>
#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>

status_code preprocess_mat3_orientator(vec3d_gimbal gimbal, vector3d *axis) {
    if (NULL == axis ||
         NULL == gimbal.orientation ||
         NULL == gimbal.orientation->element) {
        return EUNDEFINEDBUFFER;
    }

    vector3d v3 = {
        .gimbal = (vec3d_gimbal) {
            .orientation = gimbal.orientation
        }
    };

    preprocess_orientator(&v3, axis);

    return PASS;
}