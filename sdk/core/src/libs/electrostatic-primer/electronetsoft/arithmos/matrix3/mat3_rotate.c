#include <electronetsoft/arithmos/vectorspaces/matrix/matrix3.h>
#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>

status_code mat3_rotate(mat3_gimbal in, vector3d axis,
                        mat3_gimbal *out, vec_component angle,
                        mat3_processors proc) {

    // preprocessing automata -- input validation phases
    if (NULL == in.mat3d.element ||
        NULL == out ||
        NULL == out->mat3d.element ||
        NULL == out->gimbal3d.orientation->element) {
        return EUNDEFINEDBUFFER;
    }

    // test in.mat3d against in.gimbal3d
    if (in.mat3d.m != in.gimbal3d.orientation->m ||
            in.mat3d.n != in.gimbal3d.orientation->n ||
            in.mat3d.m != in.mat3d.n ||
            in.mat3d.m != 3) {
        return EBUFFERTURNCATION;
    }

    // test in.gimbal3d against out.gimbal3d
    if (in.gimbal3d.orientation->m != out->gimbal3d.orientation->m ||
        in.gimbal3d.orientation->n != out->gimbal3d.orientation->n ||
        out->gimbal3d.orientation->m != out->gimbal3d.orientation->n ||
        out->gimbal3d.orientation->m != 3) {
        return EBUFFERTURNCATION;
    }

    // test in.mat3d against out->mat3d
    if (in.mat3d.m != out->mat3d.m ||
            in.mat3d.n != out->mat3d.n) {
        return EBUFFERTURNCATION;
    }

    status_code __code;
    vec_component angle1 = 0;

    // preprocessing automata -- initialize the input column vector
    preprocess_orientator(&axis, &axis);
    vec3d_abs(axis, &axis, NULL);

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
    __code = init_rotator_gimbal(axis, &__rotator, angle,
                                 &angle1, &out->gimbal3d);
    if (PASS != __code) {
        return __code;
    }

    // processing automata -- rotate the matrix
    __code = mat_product(in.mat3d, __rotator, &(out->mat3d), proc.processors);
    if (PASS != __code) {
        return __code;
    }

    // post-processing automata -- handle gimbals and gimbal rotation
    if (vector2d_abs(vector2d_cos(angle1)) <= ___ROTATION_MIN_THRESHOLD
        && vector2d_abs(vector2d_sin(angle1)) == 1) {
        if (NULL != proc.on_gimbal_lock_trap) {
            proc.on_gimbal_lock_trap(*out, get_vec_gimbal(axis), angle);
        }
        // rotate the gimbals axes (the orientation)
        __code = rotate_gimbal(axis, angle1, &__rotator,
                               &(in.gimbal3d),
                               &out->gimbal3d,
                               NULL);
        if (PASS != __code) {
            if (NULL != proc.processors.on_op_failure) {
                proc.processors.on_op_failure((mat_proc_sig) {

                    }, __code);
            }
            return __code;
        }
    }

    return PASS;
}

