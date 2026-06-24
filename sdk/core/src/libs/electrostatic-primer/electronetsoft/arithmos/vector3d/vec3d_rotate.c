#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>
#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>
#include <electronetsoft/arithmos/vectorspaces/matrix/matrix3.h>
#include <stdio.h>

static inline status_code rotate_about_gimbal(matrix *__rotator,
                                               matrix *__col_vec,
                                               matrix *_col_vec,
                                               vector3d *out,
                                               vec3d_processors *procs) {
    mat_processors mat_procs = {
    };

    status_code __code = mat_product(*__rotator,
                                     *__col_vec,
                                     _col_vec, mat_procs);
    if (PASS != __code) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec3d_rotate, __code);
        }
        return __code;
    }

    out->x = _col_vec->element[0][0];
    out->y = _col_vec->element[1][0];
    out->z = _col_vec->element[2][0];

    return PASS;
}

status_code vec3d_rotate(vector3d v, vector3d axis, vec_component angle,
                         vector3d *out, vec3d_processors *procs) {

    if (NULL == v.gimbal.orientation ||
        NULL == v.gimbal.orientation->element) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == out ||
        NULL == out->gimbal.orientation) {
        return EUNDEFINEDBUFFER;
    }

    if (v.gimbal.orientation->m != v.gimbal.orientation->n ||
        out->gimbal.orientation->m != out->gimbal.orientation->n ||
        v.gimbal.orientation->m != out->gimbal.orientation->m ||
        v.gimbal.orientation->m != 3) {
        return EBUFFERTURNCATION;
    }

    // preprocessing automata -- initialize the input column vector
    vec_component __vec_x[1] = {v.x,};
    vec_component __vec_y[1] = {v.y,};
    vec_component __vec_z[1] = {v.z,};
    vec_component *__vec_comps[3] = {__vec_x, __vec_y, __vec_z};
    matrix __col_vec = {
        .element = __vec_comps,
        .m = 3,
        .n = 1
    };

    // init the output buffer
    vec_component _vec_x[1] = {0,};
    vec_component _vec_y[1] = {0,};
    vec_component _vec_z[1] = {0,};
    vec_component *_vec_comps[3] = {_vec_x, _vec_y, _vec_z};
    matrix _col_vec = {
            .element = _vec_comps,
            .m = 3,
            .n = 1
    };

    // init the rotation matrix
    vec_component __rotate_x[3] = {0, 0, 0,};
    vec_component __rotate_y[3] = {0, 0, 0,};
    vec_component __rotate_z[3] = {0, 0, 0,};
    vec_component *__rotate_comps[3] = {__rotate_x, __rotate_y, __rotate_z};
    matrix __rotator = {
            .element = __rotate_comps,
            .m = 3,
            .n = 3,
    };

    status_code __code;
    vec_component *gimbal_angle = NULL;
    vector_gimbal rotator_gimbal;

    if (get_vec_gimbal(axis) == GIMBAL_X) {
        out->gimbal.x_gimbal += angle;
        out->gimbal.delta_x = angle;
        gimbal_angle = &(out->gimbal.x_gimbal);
        rotator_gimbal = GIMBAL_X;
    } else if (get_vec_gimbal(axis) == GIMBAL_Y) {
        out->gimbal.y_gimbal += angle;
        out->gimbal.delta_y = angle;
        gimbal_angle = &(out->gimbal.y_gimbal);
        rotator_gimbal = GIMBAL_Y;
    } else if (get_vec_gimbal(axis) == GIMBAL_Z) {
        out->gimbal.z_gimbal += angle;
        out->gimbal.delta_z = angle;
        gimbal_angle = &(out->gimbal.z_gimbal);
        rotator_gimbal = GIMBAL_Z;
    } else {
        return EINCOMPATTYPE;
    }

    __code = init_rotator_gimbal(axis, *(v.gimbal.orientation), &__rotator, angle);

    if (PASS != __code) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec3d_rotate, __code);
        }
        return __code;
    }

    __code = rotate_about_gimbal(&__rotator,
                                 &__col_vec,
                                 &_col_vec, out, procs);
    if (PASS != __code) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec3d_rotate, __code);
        }
        return __code;
    }

    if (fabsf(vector2d_abs(vector2d_cos(*gimbal_angle)) - ___ROTATION_MIN_THRESHOLD) < ___DELTA || fabsf(vector2d_abs(vector2d_sin(*gimbal_angle)) - 1.0f) < ___DELTA) {
        // rotate the gimbals axes (the orientation)
        __code = init_rotator_gimbal(axis, *(v.gimbal.orientation), &__rotator, *gimbal_angle);
        if (PASS != __code) {
            if (NULL != procs && NULL != procs->on_op_failed) {
                procs->on_op_failed(&vec3d_rotate, __code);
            }
            return __code;
        }

        __code = rotate_gimbal(axis, __rotator,
                               &(v.gimbal),
                               &out->gimbal, procs);
        if (PASS != __code) {
            if (NULL != procs && NULL != procs->on_op_failed) {
                procs->on_op_failed(&vec3d_rotate, __code);
            }
            return __code;
        }

        if (NULL != procs && NULL != procs->on_gimbal_lock_trap) {
            procs->on_gimbal_lock_trap(*out, get_vec_gimbal(axis), *gimbal_angle);
        }

        *gimbal_angle = 0.0f;
    }

    if (NULL != procs && NULL != procs->on_op_success) {
        procs->on_op_success(&vec3d_rotate, *out);
    }

    return __code;
}
