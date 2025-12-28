/**
 * @brief An example showing an example :-).
 * @author pavl_g.
 * @copyright BSD-3 Clause Arithmos, The Electrostatic-Sandbox Distributed Simulation Framework.
 */
#include <stdio.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

vector2d vec0 = {
    4,
    6
};

vector2d vec1 = {
    2,
    3
};

void on_op_completed(void *caller, vector2d result) {
   // hardware OK!
   // simulator OK!
   //

}

void on_op_failed(void *caller, status_code err) {

}

int main() {
    vector2d out = {};
    vec_component scalar;
    status_code __code;

    vec2d_processors proc = {
        .on_op_success = &on_op_completed,
        .on_op_failed = &on_op_failed,
    };

    __code = vec2d_add(vec0, vec1, &out, &proc);
    if (PASS != __code) {
    }
    printf("Summation = [%f, %f] \n", out.x, out.y);

    __code = vec2d_subtract(vec0, vec1, &out, NULL);
    if (PASS != __code) {
    }
    printf("Subtraction = [%f, %f] \n", out.x, out.y);

    __code = vec2d_product(vec0, vec1, &out, NULL);
    if (PASS != __code) {
    }
    printf("Product = [%f, %f] \n", out.x, out.y);


    __code = vec2d_divide(vec0, vec1, &out, NULL);
    if (PASS != __code) {
    }
    printf("Division = [%f, %f] \n", out.x, out.y);


    __code = vec2d_distance(vec0, vec1, &scalar, NULL);
    if (PASS != __code) {
    }
    printf("Distance = [%f] \n", scalar);

    __code = vec2d_cross_product(vec0, vec1, &scalar, NULL);
    if (PASS != __code) {
    }
    printf("Cross Product = [%f] \n", scalar);

    __code = vec2d_interpolate(vec0, vec1, 0.5f, &out, NULL);
    if (PASS != __code) {
    }
    printf("Interpolate into 1/2 = [%f, %f] \n", out.x, out.y);


    __code = vec2d_component(vec0, VEC2_X_COMPONENT, &out, NULL);
    if (PASS != __code) {
    }
    printf("Vector X Component = [%f, %f] \n", out.x, out.y);

//    printf("Cross Product = [%f] \n", vector2d_cross_product(vec0, vec1));
//    printf("Distance = [%f] \n", vector2d_distance(vec0, vec1));
//    printf("Are perpendicular = %u \n", vector2d_are_perpendicular(vec0, vec1));
//    printf("Extrapolate to 1/2 after the last vector = [%f, %f] \n", vector2d_extrapolate(vec0, vec1, 0.5).x, vector2d_extrapolate(vec0, vec1, 0.5).y);

    return 0;
}
