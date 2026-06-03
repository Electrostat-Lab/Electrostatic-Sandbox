#include <electronetsoft/util/unit-testing/unit_test.h>
#include <electronetsoft/util/console/colors.h>
#include <electronetsoft/arithmos_calculus.h>
#include <math.h>
#include <stdio.h>

// Helper function to print gimbal state
static void print_gimbal_state(const char *label, mat3_gimbal gimbal) {
    fprintf(stdout, CYAN "%s\n" RESET, label);
    fprintf(stdout, CYAN "  X-Gimbal angle: %f\n" RESET, gimbal.gimbal3d.x_gimbal);
    fprintf(stdout, CYAN "  Y-Gimbal angle: %f\n" RESET, gimbal.gimbal3d.y_gimbal);
    fprintf(stdout, CYAN "  Z-Gimbal angle: %f\n" RESET, gimbal.gimbal3d.z_gimbal);
}

// Helper function to print gimbal orientation matrix
static void print_gimbal_orientation(const char *label, mat3_gimbal gimbal) {
    fprintf(stdout, CYAN "%s\n" RESET, label);
    fprintf(stdout, CYAN "  X-Gimbal orientation: [%f, %f, %f]\n" RESET,
            gimbal.gimbal3d.orientation->element[0][0],
            gimbal.gimbal3d.orientation->element[1][0],
            gimbal.gimbal3d.orientation->element[2][0]);
    fprintf(stdout, CYAN "  Y-Gimbal orientation: [%f, %f, %f]\n" RESET,
            gimbal.gimbal3d.orientation->element[0][1],
            gimbal.gimbal3d.orientation->element[1][1],
            gimbal.gimbal3d.orientation->element[2][1]);
    fprintf(stdout, CYAN "  Z-Gimbal orientation: [%f, %f, %f]\n" RESET,
            gimbal.gimbal3d.orientation->element[0][2],
            gimbal.gimbal3d.orientation->element[1][2],
            gimbal.gimbal3d.orientation->element[2][2]);
}

// Test 1: Rotate around X-axis by 90 degrees
static status_code assert_x_rotation_90(mat3_gimbal r0, mat3_gimbal r,
                                        vec_component angle) {
    if (r.gimbal3d.x_gimbal != angle) {
        fprintf(stdout, RED "(1) Failed to assert the X-Gimbal Angle Rotated Orthogonally!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(1) Asserted X-Gimbal Angle Rotated Orthogonally!\n" RESET);

    if (r.gimbal3d.y_gimbal != 0) {
        fprintf(stdout, RED "(2) Failed to assert the Y-Gimbal angle unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(2) Asserted the Y-Gimbal angle unchanged!\n" RESET);

    if (r.gimbal3d.z_gimbal != 0) {
        fprintf(stdout, RED "(3) Failed to assert the Z-Gimbal angle unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(3) Asserted the Z-Gimbal angle unchanged!\n" RESET);

    // assert the position of the X Gimbal (Which should never change!)
    if ((r.gimbal3d.orientation->element[0][0] != 1) ||
        (r.gimbal3d.orientation->element[1][0] != 0) ||
        (r.gimbal3d.orientation->element[2][0] != 0)) {
        fprintf(stdout, RED "(4) Failed to assert the X-Gimbal orientation unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(4) Asserted the X-Gimbal orientation unchanged!\n" RESET);

    // assert the new position of the Y Gimbal (After performing a Pi/2 X-gimbal rotation)
    if (!(vector2d_abs(r.gimbal3d.orientation->element[1][1]) <=
          ___ROTATION_MIN_THRESHOLD) ||
        (r.gimbal3d.orientation->element[0][1] != 0) ||
        (r.gimbal3d.orientation->element[2][1] != -1)) {
        fprintf(stdout, RED "(5) Failed to assert the new Y-Gimbal orientation!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(5) Asserted the new Y-Gimbal orientation!\n" RESET);

    // assert the new position of the Z Gimbal (After performing a Pi/2 X-gimbal rotation).
    if ((vector2d_abs(r.gimbal3d.orientation->element[0][2]) != 0) ||
        (vector2d_abs(r.gimbal3d.orientation->element[1][2]) != 1) ||
        !(vector2d_abs(r.gimbal3d.orientation->element[2][2]) <= ___ROTATION_MIN_THRESHOLD)){
        fprintf(stdout, RED "(6) Failed to assert the new Z-Gimbal orientation!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(6) Asserted the new Z-Gimbal orientation!\n" RESET);

    return ASSERTION_SUCCESS;
}

// Test 2: Rotate around Y-axis by 90 degrees
static status_code assert_y_rotation_90(mat3_gimbal r0, mat3_gimbal r,
                                        vec_component angle) {
    if (r.gimbal3d.y_gimbal != angle) {
        fprintf(stdout, RED "(1) Failed to assert the Y-Gimbal Angle Rotated Orthogonally!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(1) Asserted Y-Gimbal Angle Rotated Orthogonally!\n" RESET);

    if (r.gimbal3d.x_gimbal != 0) {
        fprintf(stdout, RED "(2) Failed to assert the X-Gimbal angle unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(2) Asserted the X-Gimbal angle unchanged!\n" RESET);

    if (r.gimbal3d.z_gimbal != 0) {
        fprintf(stdout, RED "(3) Failed to assert the Z-Gimbal angle unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(3) Asserted the Z-Gimbal angle unchanged!\n" RESET);

    // assert the position of the Y Gimbal (Which should never change!)
    if ((r.gimbal3d.orientation->element[0][1] != 0) ||
        (r.gimbal3d.orientation->element[1][1] != 1) ||
        (r.gimbal3d.orientation->element[2][1] != 0)) {
        fprintf(stdout, RED "(4) Failed to assert the Y-Gimbal orientation unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(4) Asserted the Y-Gimbal orientation unchanged!\n" RESET);

    // assert the new position of the X Gimbal (After performing a Pi/2 Y-gimbal rotation)
    if (!(vector2d_abs(r.gimbal3d.orientation->element[0][0]) <=
          ___ROTATION_MIN_THRESHOLD) ||
        (r.gimbal3d.orientation->element[0][1] != 0) ||
        (r.gimbal3d.orientation->element[2][0] != 1)) {
        fprintf(stdout, RED "(5) Failed to assert the new X-Gimbal orientation!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(5) Asserted the new X-Gimbal orientation!\n" RESET);

    // assert the new position of the Z Gimbal (After performing a Pi/2 Y-gimbal rotation).
    if ((vector2d_abs(r.gimbal3d.orientation->element[0][2]) != 1) ||
        !(r.gimbal3d.orientation->element[1][2] <= ___ROTATION_MIN_THRESHOLD) ||
        !(vector2d_abs(r.gimbal3d.orientation->element[2][2]) <= ___ROTATION_MIN_THRESHOLD)){
        fprintf(stdout, RED "(6) Failed to assert the new Z-Gimbal orientation!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(6) Asserted the new Z-Gimbal orientation!\n" RESET);

    return ASSERTION_SUCCESS;
}

// Test 3: Rotate around Z-axis by 90 degrees
static status_code assert_z_rotation_90(mat3_gimbal r0, mat3_gimbal r,
                                        vec_component angle) {
    if (r.gimbal3d.z_gimbal != angle) {
        fprintf(stdout, RED "(1) Failed to assert the Z-Gimbal Angle Rotated Orthogonally!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(1) Asserted Z-Gimbal Angle Rotated Orthogonally!\n" RESET);

    if (r.gimbal3d.x_gimbal != 0) {
        fprintf(stdout, RED "(2) Failed to assert the X-Gimbal angle unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(2) Asserted the X-Gimbal angle unchanged!\n" RESET);

    if (r.gimbal3d.y_gimbal != 0) {
        fprintf(stdout, RED "(3) Failed to assert the Y-Gimbal angle unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(3) Asserted the Y-Gimbal angle unchanged!\n" RESET);

    // assert the position of the Z Gimbal (Which should never change!)
    if ((r.gimbal3d.orientation->element[0][2] != 0) ||
        (r.gimbal3d.orientation->element[1][2] != 0) ||
        (r.gimbal3d.orientation->element[2][2] != 1)) {
        fprintf(stdout, RED "(4) Failed to assert the Z-Gimbal orientation unchanged!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(4) Asserted the Z-Gimbal orientation unchanged!\n" RESET);

    // assert the new position of the X Gimbal (After performing a Pi/2 Z-gimbal rotation)
    if (!(vector2d_abs(r.gimbal3d.orientation->element[0][0]) <=
          ___ROTATION_MIN_THRESHOLD) ||
        (r.gimbal3d.orientation->element[1][0] != 1) ||
        !(vector2d_abs(r.gimbal3d.orientation->element[2][0]) <= ___ROTATION_MIN_THRESHOLD)) {
        fprintf(stdout, RED "(5) Failed to assert the new X-Gimbal orientation!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(5) Asserted the new X-Gimbal orientation!\n" RESET);

    // assert the new position of the Y Gimbal (After performing a Pi/2 Z-gimbal rotation).
    if ((vector2d_abs(r.gimbal3d.orientation->element[0][1]) != 1) ||
        !(r.gimbal3d.orientation->element[1][1] <= ___ROTATION_MIN_THRESHOLD) ||
        (r.gimbal3d.orientation->element[2][1] != 0)){
        fprintf(stdout, RED "(6) Failed to assert the new Y-Gimbal orientation!\n" RESET);
        return ASSERTION_FAILURE;
    }

    fprintf(stdout, GREEN "(6) Asserted the new Y-Gimbal orientation!\n" RESET);

    return ASSERTION_SUCCESS;
}

// Execute test 1: Rotation around X-axis
static inline int64_t execute_x_rotation(void **inputs) {
    // 1) Create an identity matrix for the initial position
    vec_component __rotate_x[3] = {1, 0, 0,};
    vec_component __rotate_y[3] = {0, 1, 0,};
    vec_component __rotate_z[3] = {0, 0, 1,};
    vec_component *__rotate_comps[3] = {__rotate_x,
                                        __rotate_y,
                                        __rotate_z};

    // 2) Create an identity matrix for the orientator matrix
    vec_component __gimbal_x[3] = {1, 0, 0,};
    vec_component __gimbal_y[3] = {0, 1, 0,};
    vec_component __gimbal_z[3] = {0, 0, 1,};
    vec_component *__gimbal_comps[3] = {__gimbal_x,
                                        __gimbal_y,
                                        __gimbal_z};

    matrix __gimbal = {
            .element = __gimbal_comps,
            .m = 3,
            .n = 3,
    };

    mat3_gimbal mat_gimbal = {
            .mat3d = (matrix) {
                    .element = __rotate_comps,
                    .m = 3,
                    .n = 3,
            },
            .gimbal3d = (vec3d_gimbal) {
                    .orientation = &__gimbal,
                    .x_gimbal = 0,
                    .y_gimbal = 0,
                    .z_gimbal = 0
            }
    };

    mat3_gimbal initial_state = mat_gimbal;

    mat3_processors processors = {
    };

    fprintf(stdout, "\n=== Test 1: Rotate identity matrix around X-axis by 90 degrees ===\n");

    print_gimbal_state(YELLOW "Initial Gimbal Angles:" RESET, initial_state);
    print_gimbal_orientation(YELLOW "Initial Gimbal Orientations:" RESET, initial_state);

    status_code __code = mat3_rotate(mat_gimbal, VEC3_X_COMPONENT, &mat_gimbal, M_PI/2, processors);

    if (PASS != __code) {
        fprintf(stderr, RED "Error: %d\n" RESET, __code);
        return __code;
    }

    print_gimbal_state(YELLOW "Rotated Gimbal Angles:" RESET, mat_gimbal);
    print_gimbal_orientation(YELLOW "Rotated Gimbal Orientations:" RESET, mat_gimbal);
    fprintf(stdout, YELLOW "Expected X-Gimbal Angle: %f (radians = π/2)\n" RESET, M_PI/2);

    fprintf(stdout, "\n" YELLOW "Performing assertions...\n" RESET);
    status_code assertion_result = assert_x_rotation_90(initial_state, mat_gimbal, 0);
    return assertion_result;
}

// Execute test 2: Rotation around Y-axis
static inline int64_t execute_y_rotation(void **inputs) {
    // 1) Create an identity matrix for the initial position
    vec_component __rotate_x[3] = {1, 0, 0,};
    vec_component __rotate_y[3] = {0, 1, 0,};
    vec_component __rotate_z[3] = {0, 0, 1,};
    vec_component *__rotate_comps[3] = {__rotate_x,
                                        __rotate_y,
                                        __rotate_z};

    // 2) Create an identity matrix for the orientator matrix
    vec_component __gimbal_x[3] = {1, 0, 0,};
    vec_component __gimbal_y[3] = {0, 1, 0,};
    vec_component __gimbal_z[3] = {0, 0, 1,};
    vec_component *__gimbal_comps[3] = {__gimbal_x,
                                        __gimbal_y,
                                        __gimbal_z};

    matrix __gimbal = {
            .element = __gimbal_comps,
            .m = 3,
            .n = 3,
    };

    mat3_gimbal mat_gimbal = {
            .mat3d = (matrix) {
                    .element = __rotate_comps,
                    .m = 3,
                    .n = 3,
            },
            .gimbal3d = (vec3d_gimbal) {
                    .orientation = &__gimbal,
                    .x_gimbal = 0,
                    .y_gimbal = 0,
                    .z_gimbal = 0
            }
    };

    mat3_gimbal initial_state = mat_gimbal;

    mat3_processors processors = {
    };

    fprintf(stdout, "\n=== Test 2: Rotate identity matrix around Y-axis by 90 degrees ===\n");

    print_gimbal_state(YELLOW "Initial Gimbal Angles:" RESET, initial_state);
    print_gimbal_orientation(YELLOW "Initial Gimbal Orientations:" RESET, initial_state);

    status_code __code = mat3_rotate(mat_gimbal, VEC3_Y_COMPONENT, &mat_gimbal, M_PI/2, processors);

    if (PASS != __code) {
        fprintf(stderr, RED "Error: %d\n" RESET, __code);
        return __code;
    }

    print_gimbal_state(YELLOW "Rotated Gimbal Angles:" RESET, mat_gimbal);
    print_gimbal_orientation(YELLOW "Rotated Gimbal Orientations:" RESET, mat_gimbal);
    fprintf(stdout, YELLOW "Expected Y-Gimbal Angle: %f (radians = π/2)\n" RESET, M_PI/2);

    fprintf(stdout, "\n" YELLOW "Performing assertions...\n" RESET);
    status_code assertion_result = assert_y_rotation_90(initial_state, mat_gimbal, 0);
    return assertion_result;
}

// Execute test 3: Rotation around Z-axis
static inline int64_t execute_z_rotation(void **inputs) {
    // 1) Create an identity matrix for the initial position
    vec_component __rotate_x[3] = {1, 0, 0,};
    vec_component __rotate_y[3] = {0, 1, 0,};
    vec_component __rotate_z[3] = {0, 0, 1,};
    vec_component *__rotate_comps[3] = {__rotate_x,
                                        __rotate_y,
                                        __rotate_z};

    // 2) Create an identity matrix for the orientator matrix
    vec_component __gimbal_x[3] = {1, 0, 0,};
    vec_component __gimbal_y[3] = {0, 1, 0,};
    vec_component __gimbal_z[3] = {0, 0, 1,};
    vec_component *__gimbal_comps[3] = {__gimbal_x,
                                        __gimbal_y,
                                        __gimbal_z};

    matrix __gimbal = {
            .element = __gimbal_comps,
            .m = 3,
            .n = 3,
    };

    mat3_gimbal mat_gimbal = {
            .mat3d = (matrix) {
                    .element = __rotate_comps,
                    .m = 3,
                    .n = 3,
            },
            .gimbal3d = (vec3d_gimbal) {
                    .orientation = &__gimbal,
                    .x_gimbal = 0,
                    .y_gimbal = 0,
                    .z_gimbal = 0
            }
    };

    mat3_gimbal initial_state = mat_gimbal;

    mat3_processors processors = {
    };

    fprintf(stdout, "\n=== Test 3: Rotate identity matrix around Z-axis by 90 degrees ===\n");

    print_gimbal_state(YELLOW "Initial Gimbal Angles:" RESET, initial_state);
    print_gimbal_orientation(YELLOW "Initial Gimbal Orientations:" RESET, initial_state);

    status_code __code = mat3_rotate(mat_gimbal, VEC3_Z_COMPONENT, &mat_gimbal, M_PI/2, processors);

    if (PASS != __code) {
        fprintf(stderr, RED "Error: %d\n" RESET, __code);
        return __code;
    }

    print_gimbal_state(YELLOW "Rotated Gimbal Angles:" RESET, mat_gimbal);
    print_gimbal_orientation(YELLOW "Rotated Gimbal Orientations:" RESET, mat_gimbal);
    fprintf(stdout, YELLOW "Expected Z-Gimbal Angle: %f (radians = π/2)\n" RESET, M_PI/2);

    fprintf(stdout, "\n" YELLOW "Performing assertions...\n" RESET);
    status_code assertion_result = assert_z_rotation_90(initial_state, mat_gimbal, 0);
    return assertion_result;
}

static inline status_code assert(int64_t prop0, int64_t prop1) {
return ((status_code) (prop0 == prop1) && ASSERTION_SUCCESS);
}

static inline void on_assertion_success(unit_test *test) {
    fprintf(stdout, GREEN "✓ Test passed!\n" RESET);
}

static inline void on_assertion_failure(unit_test *test) {
    fprintf(stderr, RED "✗ Test failed!\n" RESET);
}

int main() {
    fprintf(stdout, "\n========================================\n");
    fprintf(stdout, "Matrix3 Rotation API Unit Tests\n");
    fprintf(stdout, "========================================\n");

    // Test 1: Rotation around X-axis
    unit_test test_x = {
            .on_assertion_success = &on_assertion_success,
            .on_assertion_failure = &on_assertion_failure,
            .assert = &assert,
            .execute = &execute_x_rotation,
            .proposition = ASSERTION_SUCCESS,
    };

    // Test 2: Rotation around Y-axis
    unit_test test_y = {
            .on_assertion_success = &on_assertion_success,
            .on_assertion_failure = &on_assertion_failure,
            .assert = &assert,
            .execute = &execute_y_rotation,
            .proposition = ASSERTION_SUCCESS,
    };

    // Test 3: Rotation around Z-axis
    unit_test test_z = {
            .on_assertion_success = &on_assertion_success,
            .on_assertion_failure = &on_assertion_failure,
            .assert = &assert,
            .execute = &execute_z_rotation,
            .proposition = ASSERTION_SUCCESS,
    };

    fprintf(stdout, "\nRunning tests...\n");

    status_code __code_x = assert_test(&test_x);
    if (ASSERTION_SUCCESS != __code_x) {
        fprintf(stderr, RED "Error in Test 1: %d\n" RESET, __code_x);
    }

    status_code __code_y = assert_test(&test_y);
    if (ASSERTION_SUCCESS != __code_y) {
        fprintf(stderr, RED "Error in Test 2: %d\n" RESET, __code_y);
    }

    status_code __code_z = assert_test(&test_z);
    if (ASSERTION_SUCCESS != __code_z) {
        fprintf(stderr, RED "Error in Test 3: %d\n" RESET, __code_z);
    }

    fprintf(stdout, "\n========================================\n");
    fprintf(stdout, "Tests completed!\n");
    fprintf(stdout, "========================================\n");

    return 0;
}
