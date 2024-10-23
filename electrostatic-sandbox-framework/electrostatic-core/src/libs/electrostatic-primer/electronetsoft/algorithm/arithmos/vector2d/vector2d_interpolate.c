#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

vector2d vector2d_interpolate(vector2d vec0, vector2d vec1, coordinate scale) {
    // 1) find the absolute x_distance and y_distance
    coordinate x_distance = vector2d_abs(vec0.x - vec1.x);
    coordinate y_distance = vector2d_abs(vec0.y - vec1.y);
    // 2) interpolate between components with a scale starting from the first vector
    return (vector2d) {
        ((x_distance) * scale) + vec0.x,
        ((y_distance) * scale) + vec0.y
    };;
}
