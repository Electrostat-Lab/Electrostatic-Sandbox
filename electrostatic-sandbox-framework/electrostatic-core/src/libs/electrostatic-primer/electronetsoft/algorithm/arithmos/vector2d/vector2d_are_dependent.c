#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

uint8_t vector2d_are_dependent(vector2d vec0, vector2d vec1) {
    vector2d constant = vector2d_divide(vec0, vec1);
    return constant.x == constant.y != 0;
}
