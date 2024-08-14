#include <electrostatic/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

coordinate vector2d_length(vector2d vec) {
    float sum = powf(vec.x, 2) + powf(vec.y, 2);
    return powf(sum, 0.5);
}
