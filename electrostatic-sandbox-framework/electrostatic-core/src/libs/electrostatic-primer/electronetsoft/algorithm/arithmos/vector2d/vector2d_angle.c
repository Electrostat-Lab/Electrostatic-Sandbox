#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

coordinate vector2d_angle(vector2d vec0, vector2d vec1) {
    // 1) find the dot product
    coordinate product = vector2d_dot_product(vec0, vec1);
    // 2) find the norm of both vectors
    coordinate vec0_norm = vector2d_length(vec0);
    coordinate vec1_norm = vector2d_length(vec1);
    // 3) find the angle of their inner product in this vector space
    return vector2d_acos(product / (vec0_norm * vec1_norm));
}
