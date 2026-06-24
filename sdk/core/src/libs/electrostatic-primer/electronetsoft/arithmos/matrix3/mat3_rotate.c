#include <electronetsoft/arithmos/vectorspaces/matrix/matrix3.h>
#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>

status_code mat3_rotate(mat3_gimbal in, vector3d axis,
                        mat3_gimbal *out, vec_component angle,
                        mat3_processors proc) {

    caller_graph caller = {
            .api = "arithmos:matrix3#mat3_rotate",
            .func = &mat3_rotate,
            .params = NULL,
            .root = proc.processors.root,
    };

    mat_proc_sig proc_sig = {
            .proc = proc.processors,
            .caller = caller,
            .metadata = proc.processors.metadata,
    };

    // preprocessing automata -- input validation phases
    if (NULL == in.mat3d.element ||
        NULL == in.gimbal3d.orientation ||
        NULL == in.gimbal3d.orientation->element ||
        NULL == out ||
        NULL == out->mat3d.element ||
        NULL == out->gimbal3d.orientation ||
        NULL == out->gimbal3d.orientation->element) {

        if (NULL != proc.processors.on_op_failure) {
            proc.processors.on_op_failure(proc_sig, EUNDEFINEDBUFFER);
        }

        return EUNDEFINEDBUFFER;
    }

    // test in.mat3d against in.gimbal3d
    if (in.mat3d.m != in.gimbal3d.orientation->m ||
            in.mat3d.n != in.gimbal3d.orientation->n ||
            in.mat3d.m != in.mat3d.n ||
            in.mat3d.m != 3) {

        if (NULL != proc.processors.on_op_failure) {
            proc.processors.on_op_failure(proc_sig, EBUFFERTURNCATION);
        }

        return EBUFFERTURNCATION;
    }

    // test in.gimbal3d against out.gimbal3d
    if (in.gimbal3d.orientation->m != out->gimbal3d.orientation->m ||
        in.gimbal3d.orientation->n != out->gimbal3d.orientation->n ||
        out->gimbal3d.orientation->m != out->gimbal3d.orientation->n ||
        out->gimbal3d.orientation->m != 3) {

        if (NULL != proc.processors.on_op_failure) {
            proc.processors.on_op_failure(proc_sig, EBUFFERTURNCATION);
        }

        return EBUFFERTURNCATION;
    }

    // test in.mat3d against out->mat3d
    if (in.mat3d.m != out->mat3d.m ||
            in.mat3d.n != out->mat3d.n) {

        if (NULL != proc.processors.on_op_failure) {
            proc.processors.on_op_failure(proc_sig, EBUFFERTURNCATION);
        }

        return EBUFFERTURNCATION;
    }

    proc_sig.mat = out->mat3d;

    status_code __code;
    vec_component *gimbal_angle = NULL;
    vector_gimbal rotator_gimbal;

    if (get_vec_gimbal(axis) == GIMBAL_X) {
        out->gimbal3d.x_gimbal += angle;
        out->gimbal3d.delta_x = angle;
        gimbal_angle = &(out->gimbal3d.x_gimbal);
        rotator_gimbal = GIMBAL_X;
    } else if (get_vec_gimbal(axis) == GIMBAL_Y) {
        out->gimbal3d.y_gimbal += angle;
        out->gimbal3d.delta_y = angle;
        gimbal_angle = &(out->gimbal3d.y_gimbal);
        rotator_gimbal = GIMBAL_Y;
    } else if (get_vec_gimbal(axis) == GIMBAL_Z) {
        out->gimbal3d.z_gimbal += angle;
        out->gimbal3d.delta_z = angle;
        gimbal_angle = &(out->gimbal3d.z_gimbal);
        rotator_gimbal = GIMBAL_Z;
    } else {
        return EINCOMPATTYPE;
    }

    // preprocessing automata -- initialize the input column vector

    // preprocessing automata -- allocate rotator matrix for the angular motion
    vec_component __rotate_x[3] = {0, 0, 0,};
    vec_component __rotate_y[3] = {0, 0, 0,};
    vec_component __rotate_z[3] = {0, 0, 0,};
    vec_component *__rotate_comps[3] = {__rotate_x, __rotate_y, __rotate_z};
    matrix __rotator = {
            .element = __rotate_comps,
            .m = 3,
            .n = 3,
    };

    // preprocessing automata -- init rotator matrix for the angular motion with an angular
    //                           rotator vector matrix
    __code = init_rotator_gimbal(axis, *(in.gimbal3d.orientation), &__rotator, angle);
    if (PASS != __code) {
        if (NULL != proc.processors.on_op_failure) {
            proc.processors.on_op_failure(proc_sig, __code);
        }
        return __code;
    }

    // processing automata -- rotate the matrix
    __code = mat_product(__rotator, in.mat3d, &(out->mat3d), proc.processors);
    if (PASS != __code) {
        if (NULL != proc.processors.on_op_failure) {
            proc.processors.on_op_failure(proc_sig, __code);
        }
        return __code;
    }
        // post-processing automata -- handle gimbals and gimbal rotation
    if (fabsf(vector2d_abs(vector2d_cos(*gimbal_angle)) - ___ROTATION_MIN_THRESHOLD) < ___DELTA ||
        fabsf(vector2d_abs(vector2d_sin(*gimbal_angle)) - 1.0f) < ___DELTA) {
        // rotate the gimbals axes (the orientation)
        __code = init_rotator_gimbal(axis, *(in.gimbal3d.orientation), &__rotator, *gimbal_angle);
        if (PASS != __code) {
            if (NULL != proc.processors.on_op_failure) {
                proc.processors.on_op_failure(proc_sig, __code);
            }
            return __code;
        }

        __code = rotate_gimbal(axis, __rotator,
                               &(in.gimbal3d),
                               &out->gimbal3d,
                               NULL);

        if (PASS != __code) {
            if (NULL != proc.processors.on_op_failure) {
                proc.processors.on_op_failure(proc_sig, __code);
            }
            return __code;
        }

        // execute the gimbal trap post-processor
        if (NULL != proc.on_gimbal_lock_trap) {
            proc.on_gimbal_lock_trap(*out, rotator_gimbal, *gimbal_angle,
                                     proc.processors);
        }

        *gimbal_angle = 0.0f;
    }

    if (NULL != proc.processors.on_op_success) {
        proc.processors.on_op_success(proc_sig);
    }

    return PASS;
}

