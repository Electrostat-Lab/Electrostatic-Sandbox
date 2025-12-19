#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>
#include <math.h>

struct vec2d_orient_metadata {
    matrix *local;
    matrix *shared;
};

status_code __on_op_postprocessor(mat_proc_sig proc_sig) {
    struct vec2d_orient_metadata *metadata = proc_sig.metadata;
    uint64_t row = proc_sig.row_index;
    uint64_t column = proc_sig.col_index;

    matrix *local = metadata->local;

    // post-processing -- deep copy the new orientation of the two axes
    if (vector2d_abs(local->element[row][column])
                        <= ___ROTATION_MIN_THRESHOLD) {
        local->element[row][column] = 0;
    } else {
        local->element[row][column] = vector2d_abs(local->element[row][column]);
    }

    return PASS;
}

static inline status_code __on_entry_iterated(mat_proc_sig proc_sig) {
    struct vec2d_orient_metadata *metadata = proc_sig.metadata;
    uint64_t row = proc_sig.row_index;
    uint64_t column = proc_sig.col_index;

    matrix *local = metadata->local;
    matrix *shared = metadata->shared;

    shared->element[row][column] = local->element[row][column];

    return PASS;
}

status_code vec2d_rotate(vector2d v, vector2d axis, vec_component angle,
                         vector2d *out, vec2d_processors *processors) {

    // Pre-processing Automata -- Machine Input Validation
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    if (rvalue(out->orientation) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL == v.orientation || NULL == out->orientation
            || NULL == v.orientation->element || NULL == out->orientation->element) {
        return EUNDEFINEDBUFFER;
    }

    if ((v.orientation->n != 2) ||
        (v.orientation->m != v.orientation->n)) {
        return EBUFFERTURNCATION;
    }

    // use the complementary angle if the angle
    // is ordered with the positive direction of y-axis.
    if (axis.y) {
        angle = M_PI - angle;
    }

    // processing automata -- rotate the vector
    out->x = v.x * vector2d_cos(angle) - v.y * vector2d_sin(angle);
    out->y = v.x * vector2d_sin(angle) + v.y * vector2d_cos(angle);

    // post-processing -- rotate the orientation vectors
    // allocate a rotator matrix
    vec_component x_comps[2] = {vector2d_cos(angle), -vector2d_sin(angle)};
    vec_component y_comps[2] = {vector2d_sin(angle), vector2d_cos(angle)};
    vec_component *comps[2] = {x_comps, y_comps};
    matrix rotator = {
        .element = comps,
        .m = 2,
        .n = 2
    };

    // allocate an output orientator
    vec_component out_x[2] = {0, 0};
    vec_component out_y[2] = {0, 0};
    vec_component *out_comps[2] = {out_x, out_y};
    matrix out_orientator = {
            .element = out_comps,
            .m = 2,
            .n = 2
    };

    struct vec2d_orient_metadata metadata = {
        .local = &out_orientator,
        .shared = out->orientation
    };

    mat_processors procs = {
        .on_elementary_op_postprocessor = &__on_op_postprocessor,
        .on_entry_iterated = &__on_entry_iterated,
        .metadata = &metadata
    };

    // rotate the orientation using matrix algebra
    status_code __code = mat_product(rotator, *(v.orientation),
                                     &out_orientator, procs);
    if (PASS != __code) {
        if (NULL != processors && NULL != processors->on_op_failed) {
            processors->on_op_failed(&vec2d_rotate, __code);
        }
        return __code;
    }

    // postprocessing finalizing automata --
    // deep copy the values to the output orientation
    __code = mat_iterate_elements(out_orientator,
                                  ROW_CONVENTION_ITERATOR, procs);
    if (PASS != __code) {
        if (NULL != processors && NULL != processors->on_op_failed) {
            processors->on_op_failed(&vec2d_rotate, __code);
        }
        return __code;
    }

    if (NULL != processors && NULL != processors->on_op_success) {
        processors->on_op_success(&vec2d_rotate, *out);
    }

    return PASS;
}