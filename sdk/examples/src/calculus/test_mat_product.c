#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include <stdlib.h>
#include <electrostatic/electronetsoft/arithmos_calculus.h>

void on_op_success(mat_proc_sig proc_sig) {
    matrix mat = proc_sig.mat;

    fprintf(stdout, "Elementary Success\n");
    fprintf(stdout, "Elementary Op Output = %f\n",
            mat.element[proc_sig.row_index][proc_sig.col_index]);
}
status_code on_binary_op_preprocessor(mat_binary_op_sig binary_sig) {
    matrix m0 = binary_sig.m0;
    matrix m1 = binary_sig.m1;
    uint64_t row = binary_sig.row_index;
    uint64_t col = binary_sig.col_index;

//    m0.element[row][col] = m0.element[row][col] * 2;
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
            .element = malloc(((2 * 1) * sizeof (vec_component *))),
            .m = 2,
            .n = 1
    };

    matrix out = {
            .element = malloc(((3 * 1) * sizeof (vec_component *))),
            .m = 3,
            .n = 1
    };

    mat_processors processors = {
            .on_op_success = &on_op_success,
            .on_elementary_op_postprocessor = &on_elementary_op_postprocessor,
            .on_binary_op_preprocessor = &on_binary_op_preprocessor
    };

    memset(mat0.element, '\0', ((3 * 2) * sizeof (vec_component *)));
    memset(mat1.element, '\0', ((2 * 1) * sizeof (vec_component *)));
    memset(out.element, '\0', ((3 * 1) * sizeof (vec_component *)));

    vec_component c0[2] = {1, 2};
    vec_component c1[2] = {3, 4};
    vec_component c2[2] = {200, 6};

    vec_component c02[1] = {3,};
    vec_component c12[1] = {5,};

    vec_component c_out0[1] = {0,};
    vec_component c_out1[1] = {0,};
    vec_component c_out2[1] = {0,};

    mat0.element[0] = &c0[0];
    mat0.element[1] = &c1[0];
    mat0.element[2] = &c2[0];

    mat1.element[0] = &c02[0];
    mat1.element[1] = &c12[0];

    out.element[0] = &c_out0[0];
    out.element[1] = &c_out1[0];
    out.element[2] = &c_out2[0];

    status_code __code = mat_product(mat0, mat1, &out, processors);
    if (PASS != __code) {
        fprintf(stderr, "Error: %d\n", __code);
    }

    free(mat0.element);
    free(mat1.element);
    free(out.element);

    return 0;
}