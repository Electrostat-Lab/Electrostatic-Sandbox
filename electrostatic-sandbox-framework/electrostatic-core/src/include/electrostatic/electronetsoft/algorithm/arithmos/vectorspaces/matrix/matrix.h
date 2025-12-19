#ifndef _MAT_ND_H_
#define _MAT_ND_H_

#include <math.h>
#include <electrostatic/electronetsoft/util/types.h>
#include <electrostatic/electronetsoft/util/caller_graphs.h>
#include <electrostatic/electronetsoft/util/utilities.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector3d/vector3d.h>

#ifdef __cplusplus
extern "C" {
#endif

struct matrix {
    vec_component **element;
    uint64_t m;
    uint64_t n;
};

struct mat_processors {
    status_code (*on_entry_iterated)(mat_proc_sig);
    status_code (*on_row_iterated)(mat_proc_sig);
    status_code (*on_column_iterated)(mat_proc_sig);
    status_code (*on_binary_op_preprocessor)(mat_binary_op_sig);
    status_code (*on_binary_op_postprocessor)(mat_binary_op_sig);
    status_code (*on_unary_op_preprocessor)(mat_proc_sig);
    status_code (*on_elementary_op_postprocessor)(mat_proc_sig);
    void (*on_op_success)(mat_proc_sig);
    void (*on_op_failure)(mat_proc_sig, status_code);
    caller_graph *root;
    void *metadata;
};

struct mat_binary_op_sig {
    matrix m0;
    matrix m1;
    uint64_t row_index;
    uint64_t col_index;
    mat_processors proc;
    void *metadata;
};

struct mat_proc_sig {
    matrix mat;
    uint64_t row_index;
    uint64_t col_index;
    mat_processors proc;
    caller_graph caller;
    void *metadata;
};

static inline status_code is_last_column(matrix mat, uint64_t index) {
    return index != 0 // the last column is never at the first index!
            && (index % (mat.n - 1) == 0)
            && ASSERTION_SUCCESS;
}

static inline status_code is_last_row(matrix mat, uint64_t index) {
    return index != 0 // the last row is never at the first index!
            && (index % (mat.m - 1) == 0)
            && ASSERTION_SUCCESS;
}

status_code mat_add(matrix, matrix, matrix *, mat_processors);
status_code mat_subtract(matrix, matrix, matrix *, mat_processors);
status_code mat_product(matrix, matrix, matrix *, mat_processors);
status_code mat_scalar_prod(matrix, vec_component, matrix *, mat_processors);
status_code mat_scalar_divide(matrix, vec_component, matrix *, mat_processors);
status_code mat_create_rotator_matrix(vec_component, matrix *, mat_processors *);
status_code mat_create_from_vector2d(vector2d, matrix *, mat_processors);
status_code mat_create_from_vector3d(vector3d, matrix *, mat_processors);
status_code mat_iterate_rows(matrix, mat_processors);
status_code mat_iterate_columns(matrix, mat_processors);
status_code mat_iterate_elements(matrix, mat_iterator, mat_processors);

#ifdef __cplusplus
};
#endif

#endif