#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector3d/vector3d.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>
#include <stdio.h>

struct rotation_metadata {
    matrix *in_orientation;
    matrix *out_orientation;
};

typedef enum {
    GIMBAL_X = (INT16_MAX >> 8) ^ INT16_MAX,
    GIMBAL_Y = GIMBAL_X - 1,
    GIMBAL_Z = GIMBAL_Y - 1
} vector_gimbal;

static inline void preprocess_orientator(vector3d *v, vector3d *axis) {

    // create a column vector matrix
    vec_component axis_x[1] = {0,};
    vec_component axis_y[1] = {0,};
    vec_component axis_z[1] = {0,};
    vec_component *axis_comps[3] = {axis_x, axis_y, axis_z};
    matrix __axis = {
            .element = axis_comps,
            .m = 3,
            .n = 1
    };

    mat_processors procs = {
    };
    mat_create_from_vector3d(*axis, &__axis, procs);

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
    mat_product(*(v->gimbal.orientation), __axis, &___axis, procs);

    axis->x = *(___axis.element[0]);
    axis->y = *(___axis.element[1]);
    axis->z = *(___axis.element[2]);
}

static inline status_code __on_entry_iterated(mat_proc_sig proc_sig) {
    struct rotation_metadata *metadata = proc_sig.metadata;
    matrix *in_orientation = metadata->in_orientation;
    matrix *out_orientation = metadata->out_orientation;
    uint64_t row_index = proc_sig.row_index;
    uint64_t col_index = proc_sig.col_index;

    out_orientation->element[row_index][col_index] =
            in_orientation->element[row_index][col_index];

    return PASS;
}

static inline vector_gimbal get_vec_gimbal(vector3d *axis) {
    if ((axis->x > ___ROTATION_MIN_THRESHOLD) &&
        ((axis->y >= 0) && (axis->y < 1)) &&
        ((axis->z >= 0) && (axis->z < 1))) {

        return GIMBAL_X;
    } else if ((axis->y > ___ROTATION_MIN_THRESHOLD) &&
                ((axis->x >= 0) && (axis->x < 1)) &&
                ((axis->z >= 0) && (axis->z < 1))) {

        return GIMBAL_Y;
    } else if ((axis->z > ___ROTATION_MIN_THRESHOLD) &&
                ((axis->y >= 0) && (axis->y < 1)) &&
                ((axis->x >= 0) && (axis->x < 1))) {

        return GIMBAL_Z;
    }
    return -1;
}

static inline status_code init_rotator_gimbal(vector3d *axis, matrix *__rotator,
                                              vec_component angle,
                                              vec_component *angle1,
                                              vec3d_gimbal *gimbal) {
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

        gimbal->z_gimbal += angle;
        *angle1 = gimbal->z_gimbal;

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

        gimbal->y_gimbal += angle;
        *angle1 = gimbal->y_gimbal;
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

        gimbal->x_gimbal += angle;
        *angle1 = gimbal->x_gimbal;
    } else {
        return EINCOMPATTYPE;
    }

    return PASS;
}

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

static inline status_code rotate_gimbal(vector3d *axis, vec_component angle1,
                                        matrix *__rotator,
                                        vec3d_gimbal *in_gimbal,
                                        vec3d_gimbal *out_gimbal,
                                        vec3d_processors *procs) {
    if (get_vec_gimbal(axis) == GIMBAL_Z) {
        __rotator->element[0][0] = vector2d_cos(angle1);
        __rotator->element[0][1] = -vector2d_sin(angle1);
        __rotator->element[1][0] = vector2d_sin(angle1);
        __rotator->element[1][1] = vector2d_cos(angle1);
        __rotator->element[2][2] = 1;
    } else if (get_vec_gimbal(axis) == GIMBAL_Y) {
        __rotator->element[0][0] = vector2d_cos(angle1);
        __rotator->element[0][2] = -vector2d_sin(angle1);
        __rotator->element[2][0] = vector2d_sin(angle1);
        __rotator->element[2][2] = vector2d_cos(angle1);
        __rotator->element[1][1] = 1;
    } else if (get_vec_gimbal(axis) == GIMBAL_X) {
        __rotator->element[2][2] = vector2d_cos(angle1);
        __rotator->element[2][1] = -vector2d_sin(angle1);
        __rotator->element[1][2] = vector2d_sin(angle1);
        __rotator->element[1][1] = vector2d_cos(angle1);
        __rotator->element[0][0] = 1;
    } else {
        return EINCOMPATTYPE;
    }

    // init the output orientation matrix
    vec_component _orient_x[3] = {0, 0, 0,};
    vec_component _orient_y[3] = {0, 0, 0,};
    vec_component _orient_z[3] = {0, 0, 0,};
    vec_component *_orient_comps[3] = {_orient_x, _orient_y, _orient_z};
    matrix __orient = {
            .element = _orient_comps,
            .m = 3,
            .n = 3
    };

    mat_processors mat_procs = {
    };

    status_code __code =
            mat_product(*__rotator,
                        *(in_gimbal->orientation),
                        &__orient, mat_procs);
    if (PASS != __code) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec3d_rotate, __code);
        }
        return __code;
    }

    struct rotation_metadata metadata = {
            .in_orientation = &__orient,
            .out_orientation = out_gimbal->orientation
    };

    mat_procs.on_entry_iterated = &__on_entry_iterated;
    mat_procs.metadata = &metadata;

    __code = mat_iterate_elements(__orient, ROW_CONVENTION_ITERATOR, mat_procs);
    if (PASS != __code) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec3d_rotate, __code);
        }
        return __code;
    }

    if (get_vec_gimbal(axis) == GIMBAL_Z) {
        out_gimbal->z_gimbal = 0;
    } else if (get_vec_gimbal(axis) == GIMBAL_Y) {
        out_gimbal->y_gimbal = 0;
    } else {
        out_gimbal->x_gimbal = 0;
    }

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

    __code = init_rotator_gimbal(&axis, &__rotator, angle,
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
        // rotate the gimbals axes (the orientation)
        __code = rotate_gimbal(&axis, angle1, &__rotator,
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
