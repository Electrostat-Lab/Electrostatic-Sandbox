#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>
#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>
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
    vec_component angle1 = 0;

    preprocess_orientator(&v, &axis);
    vec3d_abs(axis, &axis, NULL);

    __code = init_rotator_gimbal(axis, &__rotator, angle,
                                 &angle1, &out->gimbal);

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

    if (vector2d_abs(vector2d_cos(angle1)) <= ___ROTATION_MIN_THRESHOLD
            && vector2d_abs(vector2d_sin(angle1)) == 1) {
        if (NULL != procs && NULL != procs->on_gimbal_lock_trap) {
            procs->on_gimbal_lock_trap(*out, get_vec_gimbal(axis), angle);
        }
        // rotate the gimbals axes (the orientation)
        __code = rotate_gimbal(axis, angle1, &__rotator,
                               &(v.gimbal),
                               &out->gimbal, procs);
        if (PASS != __code) {
            if (NULL != procs && NULL != procs->on_op_failed) {
                procs->on_op_failed(&vec3d_rotate, __code);
            }
            return __code;
        }
    }

    if (NULL != procs && NULL != procs->on_op_success) {
        procs->on_op_success(&vec3d_rotate, *out);
    }

    return __code;
}
