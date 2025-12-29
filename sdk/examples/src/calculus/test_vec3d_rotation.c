#include <stdio.h>
#include <electronetsoft/arithmos_calculus.h>

int main() {

    vec_component x_comp[3] = {1, 0, 0};
    vec_component y_comp[3] = {0, 1, 0};
    vec_component z_comp[3] = {0, 0, 1};

    vec_component *comps[3] = {x_comp, y_comp, z_comp};

    matrix orientator = {
            .element = comps,
            .m = 3,
            .n = 3
    };

    vector3d v = {
            .x = 2,
            .y = 3,
            .z = 4,
            .gimbal = (vec3d_gimbal) {
                .x_gimbal = 0,
                .y_gimbal = 0,
                .z_gimbal = 0,
                .orientation = &orientator
            }
    };

    struct vec3d_processors processors = {
    };

    fprintf(stdout, "%f\n", ___ROTATION_MIN_THRESHOLD);

    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);

    status_code __code = vec3d_rotate(v, VEC3_Y_COMPONENT, M_PI/2, &v, &processors);
    if (__code != PASS) {
        fprintf(stderr, "Error: %d\n", __code);
    }

    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);

    __code = vec3d_rotate(v, VEC3_Y_COMPONENT, M_PI/4, &v, &processors);
    if (__code != PASS) {
        fprintf(stderr, "Error: %d\n", __code);
    }


    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);

    __code = vec3d_rotate(v, VEC3_Y_COMPONENT, M_PI/4, &v, &processors);
    if (__code != PASS) {
        fprintf(stderr, "Error: %d\n", __code);
    }


    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);


    __code = vec3d_rotate(v, VEC3_Y_COMPONENT, M_PI/4, &v, &processors);
    if (__code != PASS) {
        fprintf(stderr, "Error: %d\n", __code);
    }


    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);


    __code = vec3d_rotate(v, VEC3_Y_COMPONENT, M_PI/4, &v, &processors);
    if (__code != PASS) {
        fprintf(stderr, "Error: %d\n", __code);
    }
    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);

    __code = vec3d_rotate(v, VEC3_Z_COMPONENT, M_PI/2, &v, &processors);
    if (__code != PASS) {
        fprintf(stderr, "Error: %d\n", __code);
    }
    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);

//
    __code = vec3d_rotate(v, VEC3_X_COMPONENT, M_PI/4, &v, &processors);
    if (__code != PASS) {
        fprintf(stderr, "Error: %d\n", __code);
    }


    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);


    __code = vec3d_rotate(v, VEC3_X_COMPONENT, M_PI/4, &v, &processors);
    if (__code != PASS) {
        fprintf(stderr, "Error: %d\n", __code);
    }


    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);

    return 0;
}