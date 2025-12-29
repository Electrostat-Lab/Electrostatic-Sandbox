#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include <stdlib.h>
#include <electronetsoft/arithmos_calculus.h>

void on_op_success(mat_proc_sig proc_sig) {
    matrix mat = proc_sig.mat;

    fprintf(stdout, "Elementary Success = %f %lu\n",
            mat.element[0][0], sizeof (mat.element[0][0]));
}

status_code on_binary_op_preprocessor(mat_binary_op_sig binary_sig) {
    matrix m0 = binary_sig.m0;
    matrix m1 = binary_sig.m1;
    uint64_t row = binary_sig.row_index;
    uint64_t col = binary_sig.col_index;

    m1.element[row][col] = m1.element[row][col] * 2;
    return PASS;
}

status_code on_elementary_op_postprocessor(mat_proc_sig proc_sig) {
    matrix mat = proc_sig.mat;
    uint64_t row = proc_sig.row_index;
    uint64_t column = proc_sig.col_index;

    fprintf(stdout, "Elementary Op Output = %f\n",
            mat.element[row][column]);
    return PASS;
}

int main() {
    matrix mat0 = {
        .element = malloc(((3 * 2) * sizeof (vec_component *))),
        .m = 3,
        .n = 2
    };

    matrix mat1 = {
            .element = malloc(((3 * 2) * sizeof (vec_component *))),
            .m = 3,
            .n = 2
    };

    mat_processors processors = {
        .on_op_success = &on_op_success,
        .on_elementary_op_postprocessor = &on_elementary_op_postprocessor,
        .on_binary_op_preprocessor = &on_binary_op_preprocessor
    };

    memset(mat0.element, '\0', ((3 * 2) * sizeof (vec_component *)));
    memset(mat1.element, '\0', ((3 * 2) * sizeof (vec_component *)));

    vec_component c0[2] = {1, 2};
    vec_component c1[2] = {3, 4};
    vec_component c2[2] = {200, 6};

    vec_component c02[2] = {3, 4};
    vec_component c12[2] = {5, 6};
    vec_component c22[2] = {7, 8};

    mat0.element[0] = &c0[0];
    mat0.element[1] = &c1[0];
    mat0.element[2] = &c2[0];

    mat1.element[0] = &c02[0];
    mat1.element[1] = &c12[0];
    mat1.element[2] = &c22[0];

    status_code __code = mat_add(mat0, mat1, &mat0, processors);
    if (PASS != __code) {
        fprintf(stderr, "Error: %d\n", __code);
    }

    free(mat0.element);
    free(mat1.element);

    return 0;
}