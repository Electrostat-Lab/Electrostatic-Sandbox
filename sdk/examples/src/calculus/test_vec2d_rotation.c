#include <stdio.h>
#include <electronetsoft/arithmos_calculus.h>

int main() {

    vec_component x_comp[2] = {1, 0};
    vec_component y_comp[2] = {0, 1};

    vec_component *comps[2] = {x_comp, y_comp};

    matrix orientator = {
        .element = comps,
        .m = 2,
        .n = 2
    };

    vector2d v = {
        .x = 2,
        .y = 3,
        .orientation = &orientator
    };

    vector2d rotated = {
        .orientation = &orientator
    };

    struct vec2d_processors processors = {
    };

    fprintf(stdout, "Vx Orientation = (%f, %f)\n", rotated.orientation->element[0][0], rotated.orientation->element[1][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f)\n", rotated.orientation->element[0][1], rotated.orientation->element[1][1]);

    status_code __code = vec2d_rotate(v, VEC2_X_COMPONENT, M_PI/2, &rotated, &processors);
    if (__code != PASS) {
        fprintf(stderr, "Error: %d\n", __code);
    }

    fprintf(stdout, "Vx Orientation = (%f, %f)\n", rotated.orientation->element[0][0], rotated.orientation->element[1][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f)\n", rotated.orientation->element[0][1], rotated.orientation->element[1][1]);

    return 0;
}

