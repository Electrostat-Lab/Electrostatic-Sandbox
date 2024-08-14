#include <electrostatic/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

vector2d vector2d_extrapolate(vector2d vec0, vector2d vec1, coordinate scale) {
    return (vector2d) {
        ((vec0.x + vec1.x) * scale) + vec0.x,
        ((vec0.y + vec1.y) * scale) + vec0.y
    };
}
