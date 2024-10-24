#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

vector2d vector2f_scalar_moduluo(vector2d vec, coordinate scalar) {
    vec.x = ((mod_coordinate) vec.x) % ((mod_coordinate) scalar);
    vec.y = ((mod_coordinate) vec.y) % ((mod_coordinate) scalar);
    return vec;
}
