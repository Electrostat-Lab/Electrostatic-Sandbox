#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

coordinate vector2d_dot_product(vector2d vec0, vector2d vec1) {
    return vec0.x * vec1.x + vec0.y * vec1.y;
}
