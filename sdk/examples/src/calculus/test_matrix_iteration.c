#include <stdio.h>
#include <string.h>
#include <alloca.h>
#include <stdlib.h>
#include <electronetsoft/arithmos_calculus.h>

status_code on_column_iterated(mat_proc_sig proc_sig) {
    matrix mat = proc_sig.mat;
    uint64_t column = proc_sig.col_index;

    if (is_last_column(mat, column)) {
        fprintf(stdout, "Column: %f\n", mat.element[0][column]);
        return PASS;
    }
    fprintf(stdout, "Column: %f\n", mat.element[column][0]);
    return PASS;
}

status_code on_row_iterated(mat_proc_sig proc_sig) {
    matrix mat = proc_sig.mat;
    uint64_t row = proc_sig.row_index;

    fprintf(stdout, "Row: %f\n", mat.element[row][0]);
    return PASS;
}

status_code on_entry_iterated(mat_proc_sig proc_sig) {
    matrix mat = proc_sig.mat;
    uint64_t row = proc_sig.row_index;
    uint64_t column = proc_sig.col_index;

    fprintf(stdout, "Element = %f\n",
            mat.element[row][column]);
    return PASS;
}

int main() {

    matrix mat = {
        .element = malloc(((3 * 2) * sizeof (vec_component *))),
        .m = 3,
        .n = 2
    };

    mat_processors processors = {
            .on_entry_iterated = &on_entry_iterated,
            .on_row_iterated = &on_row_iterated,
            .on_column_iterated = &on_column_iterated
    };

    memset(mat.element, '\0', ((3 * 2) * sizeof (vec_component *)));

    vec_component c0[2] = {1, 2};
    vec_component c1[2] = {3, 4};
    vec_component c2[2] = {5, 6};

    mat.element[0] = &c0[0];
    mat.element[1] = &c1[0];
    mat.element[2] = &c2[0];

    status_code __code =
            mat_iterate_elements(mat, ROW_CONVENTION_ITERATOR, processors);
    if (PASS != __code) {
        fprintf(stderr, "Error: %d\n", __code);
    }

    free(mat.element);

    return 0;
};
