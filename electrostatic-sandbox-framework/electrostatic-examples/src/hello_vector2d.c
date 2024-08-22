/**
 * @brief An example showing an example :-).
 * @author pavl_g.
 * @copyright BSD-3 Clause Arithmos, The Electrostatic-Sandbox Distributed Simulation Framework.
 */
#include <stdio.h>
#include <electrostatic/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

vector2d vec0 = {
    4,
    6};

vector2d vec1 = {
    2,
    3};

int main() {
    printf("Summation = [%f, %f] \n", vector2d_add(vec0, vec1).x, vector2d_add(vec0, vec1).y);
    printf("Subtraction = [%f, %f] \n", vector2d_subtract(vec0, vec1).x, vector2d_subtract(vec0, vec1).y);
    printf("Product = [%f, %f] \n", vector2d_product(vec0, vec1).x, vector2d_product(vec0, vec1).y);
    printf("Cross Product = [%f] \n", vector2d_cross_product(vec0, vec1));
    printf("Distance = [%f] \n", vector2d_distance(vec0, vec1));
    printf("Are perpendicular = %u \n", vector2d_are_perpendicular(vec0, vec1));
    printf("Extrapolate to 1/2 after the last vector = [%f, %f] \n", vector2d_extrapolate(vec0, vec1, 0.5).x, vector2d_extrapolate(vec0, vec1, 0.5).y);
    printf("Interpolate into 1/2 = [%f, %f] \n", vector2d_interpolate(vec1, vec0, 0.5).x, vector2d_interpolate(vec1, vec0, 0.5).y);

    return 0;
}
