#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector3d/vector3d.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

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
    mat_product(*(v->orientation), __axis, &___axis, procs);

    axis->x = *(___axis.element[0]);
    axis->y = *(___axis.element[1]);
    axis->z = *(___axis.element[2]);
}

status_code vec3d_rotate(vector3d v, vector3d axis, vec_component angle,
                         vector3d *out, vec3d_processors *procs) {

    if (NULL == v.orientation ||
        NULL == axis.orientation ||
        NULL == v.orientation->element ||
        NULL == axis.orientation->element) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == out || NULL == out->orientation) {
        return EUNDEFINEDBUFFER;
    }

    if (v.orientation->m != v.orientation->n ||
        out->orientation->m != out->orientation->n ||
        v.orientation->m != out->orientation->m ||
        v.orientation->m != 3) {
        return EBUFFERTURNCATION;
    }

    vec_component orientator_x[2] = {0, 0,};
    vec_component orientator_y[2] = {0, 0,};
    vec_component *orient[2] = {orientator_x, orientator_y};
    matrix orientator = {
        .element = orient,
        .m = 2,
        .n = 2
    };
    vector2d out_2d = {
            .orientation = &orientator
    };

    status_code __code;

    preprocess_orientator(&v, &axis);

    vec3d_abs(axis, &axis, NULL);

    if (axis.z > ___ROTATION_MIN_THRESHOLD) {
        // rotate around z-axis
        // pre-processing automata
        // Let the X-axis in the R(3) space be the X-axis in the 2D projection.
        // Let the Y-axis in the R(3) space be the Y-axis in the 2D projection.
        vec_component __x[2] = {v.orientation->element[0][0], v.orientation->element[0][1],};
        vec_component __y[2] = {v.orientation->element[1][0], v.orientation->element[1][1],};
        vec_component *_orient[2] = {__y, __y};
        matrix _orientator = {
                .element = _orient,
                .m = 2,
                .n = 2
        };

        vector2d xy = {
            .x = v.x,
            .y = v.y,
            .orientation = &_orientator
        };

        // processing automata
        __code = vec2d_rotate(xy, VEC2_X_COMPONENT,
                              angle, &out_2d, NULL);

        if (PASS != __code) {
            if (NULL != procs && NULL != procs->on_op_failed) {
                procs->on_op_failed(&vec3d_rotate, __code);
            }
            return __code;
        }

        // postprocessing automata -- adapt the results from the 2d projection
        out->orientation->element[0][0] = _orientator.element[0][0];
        out->orientation->element[0][1] = _orientator.element[0][1];
        out->orientation->element[1][0] = _orientator.element[1][0];
        out->orientation->element[1][1] = _orientator.element[1][1];

    } else if (axis.y > ___ROTATION_MIN_THRESHOLD) {
        // rotate around y-axis
        // pre-processing automata
        // Let the X-axis in the R(3) space be the X-axis in the 2D projection.
        // Let the Z-axis in the R(3) space be the Y-axis in the 2D projection.

        vec_component __x[2] = {v.orientation->element[0][0], v.orientation->element[0][2],};
        vec_component __z[2] = {v.orientation->element[2][0], v.orientation->element[2][2],};
        vec_component *_orient[2] = {__x, __z};
        matrix _orientator = {
                .element = _orient,
                .m = 2,
                .n = 2
        };

        vector2d xz = {
                .x = v.x,
                .y = v.z,
                .orientation = &_orientator
        };

        // processing automata
        __code = vec2d_rotate(xz, VEC2_X_COMPONENT,
                              angle, &out_2d, NULL);

        if (PASS != __code) {
            if (NULL != procs && NULL != procs->on_op_failed) {
                procs->on_op_failed(&vec3d_rotate, __code);
            }
            return __code;
        }

        // postprocessing automata -- adapt the results from the 2d projection
        out->orientation->element[0][0] = _orientator.element[0][0];
        out->orientation->element[0][2] = _orientator.element[0][1];
        out->orientation->element[2][0] = _orientator.element[1][0];
        out->orientation->element[2][2] = _orientator.element[1][1];

    } else if (axis.x > ___ROTATION_MIN_THRESHOLD) {
        // rotate around x-axis
        // pre-processing automata
        // Let the Z-axis in the R(3) space be the X-axis in the 2D projection.
        // Let the Y-axis in the R(3) space be the Y-axis in the 2D projection.

        vec_component __z[2] = {v.orientation->element[2][2], v.orientation->element[2][1],};
        vec_component __y[2] = {v.orientation->element[1][2], v.orientation->element[1][1],};
        vec_component *_orient[2] = {__z, __y};
        matrix _orientator = {
                .element = _orient,
                .m = 2,
                .n = 2
        };

        vector2d zy = {
                .x = v.z,
                .y = v.y,
                .orientation = &_orientator
        };

        // processing automata
        __code = vec2d_rotate(zy, VEC2_X_COMPONENT,
                              angle, &out_2d, NULL);

        if (PASS != __code) {
            if (NULL != procs && NULL != procs->on_op_failed) {
                procs->on_op_failed(&vec3d_rotate, __code);
            }
            return __code;
        }

        // postprocessing automata -- adapt the results from the 2d projection
        out->orientation->element[2][2] = _orientator.element[0][0];
        out->orientation->element[2][1] = _orientator.element[0][1];
        out->orientation->element[1][2] = _orientator.element[1][0];
        out->orientation->element[1][1] = _orientator.element[1][1];
    }

    if (NULL != procs && NULL != procs->on_op_success) {
        procs->on_op_success(&vec3d_rotate, *out);
    }

    return __code;
}
