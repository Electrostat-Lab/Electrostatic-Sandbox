#include <electronetsoft/arithmos/vectorspaces/gimbal_system.h>

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

status_code rotate_gimbal(vector3d axis, vec_component angle1,
                          matrix *__rotator,
                          vec3d_gimbal *in_gimbal,
                          vec3d_gimbal *out_gimbal,
                          vec3d_processors *procs) {

    status_code __code = init_rotator_gimbal(axis, __rotator, angle1,
                                             NULL, NULL);
    if (PASS != __code) {
        if (NULL != procs && NULL != procs->on_op_failed) {
            procs->on_op_failed(&vec3d_rotate, __code);
        }
        return __code;
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

    __code = mat_product(*__rotator,
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