#include <electrostatic/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

coordinate vector2d_polar(vector2d vec) {
    return vector2d_atan2(vec.y, vec.x);
}
