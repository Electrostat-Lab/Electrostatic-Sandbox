#include <electrostatic/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

vector2d vector2d_add(vector2d vec0, vector2d vec1) {
    return (vector2d) {
        vec0.x + vec1.x,
        vec0.y + vec1.y
    };
}
