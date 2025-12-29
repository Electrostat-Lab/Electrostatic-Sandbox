#include <electronetsoft/arithmos/adt/list.h>
#include <electronetsoft/util/unit-testing/unit_test.h>
#include <electronetsoft/util/console/colors.h>
#include <electronetsoft/arithmos_calculus.h>
#include <stdio.h>

static status_code assert_gimbals(vector3d v0, vector3d v,
                                  vec_component angle) {
    // assert the angle is resettled to ZERO after
    // performing an angle that introduces a gimbal lock

    // When the system reaches or Floating-point approaches
    // an angle that introduces a gimbal lock (e.g., PI/2 and 3*PI/2);
    // the system rotates the 2 Planar Gimbals that are orthogonal
    // to the axis of rotation using the accumulated gimbal angle
    // from the structure [vec3d_gimbal], and then resets this gimbal
    // angle.
    //
    // If the gimbal angle hasn't reached the gimbal lock yet; the
    // system continues and skips the gimbal rotation, however,
    // accumulates the gimbal angle inside the structure
    // [vec3d_gimbal].
    if (v.gimbal.z_gimbal != angle) {
        fprintf(stdout, RED "(1) Failed to assert the Z-Gimbal Angle Rotated Orthogonally!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(1) Asserted Z-Gimbal Angle Rotated Orthogonally!\n" RESET);

    if (v.gimbal.x_gimbal != 0) {
        fprintf(stdout, RED "(2) Failed to assert the X-Gimbal angle unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(2) Asserted the X-Gimbal angle unchanged!\n" RESET);

    if (v.gimbal.y_gimbal != 0) {
        fprintf(stdout, RED "(3) Failed to assert the Y-Gimbal angle unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(3) Asserted the Y-Gimbal angle unchanged!\n" RESET);

    // assert the position of the Z Gimbal (Which should never change!)
    if ((v.gimbal.orientation->element[2][0] != 0) ||
        (v.gimbal.orientation->element[2][1] != 0) ||
        (v.gimbal.orientation->element[2][2] != 1)) {
        fprintf(stdout, RED "(4) Failed to assert the Z-Gimbal orientation vector unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(4) Asserted the Z-Gimbal orientation vector unchanged!\n" RESET);

    // assert the new position of the X Gimbal (After performing a Pi/2 Y-gimbal rotation)
    if (!(vector2d_abs(v.gimbal.orientation->element[0][0]) <=
            ___ROTATION_MIN_THRESHOLD) ||
        (v.gimbal.orientation->element[1][0] != 1) ||
        (v.gimbal.orientation->element[2][0] != 0)) {
        fprintf(stdout, RED "(5) Failed to assert the new X-Gimbal orientation vector!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(5) Asserted the new X-Gimbal orientation vector!\n" RESET);

    // assert the new position of the Y Gimbal (After performing a Pi/2 Y-gimbal rotation).
    if ((vector2d_abs(v.gimbal.orientation->element[0][1]) != 1) ||
            !(vector2d_abs(v.gimbal.orientation->element[1][1]) <= ___ROTATION_MIN_THRESHOLD) ||
            !(v.gimbal.orientation->element[2][1] <= ___ROTATION_MIN_THRESHOLD)) {
        fprintf(stdout, RED "(6) Failed to assert the new X-Gimbal orientation vector!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(6) Asserted the new X-Gimbal orientation vector!\n" RESET);

    // assert the vector itself
    v.x = roundf(v.x);
    v.y = roundf(v.y);

    if (PASS != vec3d_are_equal(v, (vector3d) {
            .x = roundf(-v0.y),
            .y = roundf(v0.x),
            .z = v0.z}, NULL)) {
        fprintf(stdout, RED "(7) Failed to assert the position of the new vector!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(7) Asserted the position of the new vector!\n" RESET);

    return ASSERTION_SUCCESS;
}

static inline int64_t execute(void **inputs) {

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

    fprintf(stdout, "Perform a rotation around the Z-axis for the following vector with these gimbal axes.\n");

    fprintf(stdout, "V = (%f, %f, %f)\n", v.x, v.y, v.z);
    fprintf(stdout, "\n");

    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);
    fprintf(stdout, "\n");

    status_code __code = vec3d_rotate(v, VEC3_Z_COMPONENT, M_PI/2, &v, &processors);
    if (__code != PASS) {
        fprintf(stderr, "Error: %d\n", __code);
    }

    fprintf(stdout, "Vx Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][0], v.gimbal.orientation->element[1][0], v.gimbal.orientation->element[2][0]);
    fprintf(stdout, "Vy Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][1], v.gimbal.orientation->element[1][1], v.gimbal.orientation->element[2][1]);
    fprintf(stdout, "Vz Orientation = (%f, %f, %f)\n", v.gimbal.orientation->element[0][2], v.gimbal.orientation->element[1][2], v.gimbal.orientation->element[2][2]);

    fprintf(stdout, "\n");
    fprintf(stdout, "V' = (%f, %f, %f)\n", v.x, v.y, v.z);

    return assert_gimbals((vector3d) {.x = 2, .y = 3, .z = 4},
                          v, 0); // the gimbal angle is resettled to ZERO after approaching an angle
                                               // that introduces a gimbal lock
                                               // and the system rotates the 2 other Planar gimbals (i.e., the X and Y Gimbals).
}

static inline status_code assert(int64_t prop0, int64_t prop1) {
    return ((status_code) (prop0 == prop1) && ASSERTION_SUCCESS);
}

static inline void on_assertion_success(unit_test *test) {
    fprintf(stdout, GREEN "Gimbals asserted against Gimbal Locks!\n" RESET);
}

static inline void on_assertion_failure(unit_test *test) {
    fprintf(stderr, RED "Gimbals failed to rotate to the target!\n" RESET);
}

int main() {

    unit_test test = {
        .on_assertion_success = &on_assertion_success,
        .on_assertion_failure = &on_assertion_failure,
        .assert = &assert,
        .execute = &execute,
        .proposition = ASSERTION_SUCCESS,
    };

    status_code __code = assert_test(&test);
    if (ASSERTION_SUCCESS != __code) {
        fprintf(stderr, RED "Error: %d\n" RESET, __code);
    }

    return 0;
}