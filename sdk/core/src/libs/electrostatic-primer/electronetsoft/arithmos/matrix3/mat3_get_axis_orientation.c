#include <electronetsoft/arithmos/vectorspaces/matrix/matrix3.h>
#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>

status_code mat3_get_axis_orientation(mat3_gimbal mat, vector3d axis, vector3d *out) {
    if (NULL == mat.gimbal3d.orientation || NULL == out) {
        return EUNDEFINEDBUFFER;
    }
    out->gimbal.orientation = NULL;

    vec_component __gimbal_x[1] = {axis.x};
    vec_component __gimbal_y[1] = {axis.y};
    vec_component __gimbal_z[1] = {axis.z};
    vec_component *__gimbal_comps[3] = {__gimbal_x, __gimbal_y, __gimbal_z};

    matrix m_axis = {
          .element = __gimbal_comps,
          .m = 3,
          .n = 1
    };

    vec_component __out_x[1] = {0};
    vec_component __out_y[1] = {0};
    vec_component __out_z[1] = {0};
    vec_component *__out_comps[3] = {__out_x, __out_y, __out_z};

    matrix out_mat = {
            .element = __out_comps,
            .m = 3,
            .n = 1
    };

    status_code __code = mat_product(*mat.gimbal3d.orientation, m_axis, &out_mat, (mat_processors) {});

    if (PASS != __code) {
        return __code;
    }

    out->x = out_mat.element[0][0];
    out->y = out_mat.element[1][0];
    out->z = out_mat.element[2][0];

    return PASS;
}