#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <electronetsoft/arithmos_calculus.h>

int main() {

    vec_component __in_x[3] = {0, -1, 0};
    vec_component __in_y[3] = {0, 0, 1};
    vec_component __in_z[3] = {-1, 0, 0};
    vec_component *__in_comps[3] = {__in_x, __in_y, __in_z};

    matrix in_mat = {
            .element = __in_comps,
            .m = 3,
            .n = 3
    };

    vec_component __in_axis_x[1] = {VEC3_Z_COMPONENT.x};
    vec_component __in_axis_y[1] = {VEC3_Z_COMPONENT.y};
    vec_component __in_axis_z[1] = {VEC3_Z_COMPONENT.z};
    vec_component *__in_axis[3] = {__in_axis_x, __in_axis_y, __in_axis_z};

    matrix in_axis_mat = {
            .element = __in_axis,
            .m = 3,
            .n = 1
    };

    vec_component __out_x[1] = {0};
    vec_component __out_y[1] = {0};
    vec_component __out_z[1] = {0};
    vec_component *__out_comps[3] = {__out_x, __out_y, __out_z};

    matrix out_mat = {
            .element = __out_comps,
            .m = 3,
            .n = 1
    };

    mat_processors proc = {
    };

    status_code __code = mat_product(in_mat, in_axis_mat, &out_mat, proc);

    if (PASS != __code) {
        return __code;
    }

    fprintf(stdout, "Axis out = [%f, %f, %f]\n", out_mat.element[0][0], out_mat.element[1][0], out_mat.element[2][0]);

    return 0;
}