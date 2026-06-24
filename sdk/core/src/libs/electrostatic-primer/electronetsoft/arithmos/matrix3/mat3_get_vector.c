#include <electronetsoft/arithmos/vectorspaces/matrix/matrix3.h>
#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>

status_code mat3_get_vector(mat3_gimbal mat, vector3d axis, vector3d *out) {
    if (NULL == mat.mat3d.element || mat.mat3d.m != 3 ||
                mat.mat3d.m != mat.mat3d.n || NULL == out) {
        return EUNDEFINEDBUFFER;
    }

    vec_component __x_comp[1] = {axis.x};
    vec_component __y_comp[1] = {axis.y};
    vec_component __z_comp[1] = {axis.z};
    vec_component *__vec_comps[3] = {__x_comp, __y_comp, __z_comp};

    matrix m_axis = {
            .element = __vec_comps,
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

    status_code __code = mat_product(mat.mat3d, m_axis, &out_mat, (mat_processors) {});

    if (PASS != __code) {
        return __code;
    }

    out->x = out_mat.element[0][0];
    out->y = out_mat.element[1][0];
    out->z = out_mat.element[2][0];

    return PASS;
}