#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

coordinate vector2d_distance(vector2d vec0, vector2d vec1) {
    return vector2d_length(vector2d_subtract(vec0, vec1));
}
