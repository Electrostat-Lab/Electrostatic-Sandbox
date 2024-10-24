#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

vector2d vector2d_normalize(vector2d vec) {
    return vector2d_scalar_divide(vec, vector2d_length(vec));
}
