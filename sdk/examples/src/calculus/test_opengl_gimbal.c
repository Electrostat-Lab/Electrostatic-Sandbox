#include <electronetsoft/util/unit-testing/unit_test.h>
#include <electronetsoft/util/console/colors.h>
#include <electronetsoft/arithmos_calculus.h>
#include <electronetsoft/arithmos/vectorspaces/gimbal_visualizer.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

vec_component ref_angle = 0.0f;
vec_component delta = 0.0f;
vec_component phi = 0.0f;

typedef struct {
    mat3_gimbal *mat_gimbal;
    vec_component a0;
    vec_component a1;
    vec_component delta;
    vec_component phi;
    vec_component etta;
    vector3d axis;
    float lerp;
    uint8_t finished;
    uint8_t loop;
    char *name;
} rotation_transformer;

static void print_gimbal_state(const char *label, mat3_gimbal gimbal) {
    fprintf(stdout, CYAN "%s\n" RESET, label);
    fprintf(stdout, CYAN "  X-Gimbal angle: %f\n" RESET, gimbal.gimbal3d.x_gimbal);
    fprintf(stdout, CYAN "  Y-Gimbal angle: %f\n" RESET, gimbal.gimbal3d.y_gimbal);
    fprintf(stdout, CYAN "  Z-Gimbal angle: %f\n" RESET, gimbal.gimbal3d.z_gimbal);
}

// Helper function to print gimbal orientation matrix
static void print_gimbal_orientation(const char *label, mat3_gimbal gimbal) {

    vector3d X_AXIS = {
    };

    vector3d Y_AXIS = {
    };

    vector3d Z_AXIS = {
    };

    mat3_get_axis_orientation(gimbal, VEC3_X_COMPONENT, &X_AXIS);
    mat3_get_axis_orientation(gimbal, VEC3_Y_COMPONENT, &Y_AXIS);
    mat3_get_axis_orientation(gimbal, VEC3_Z_COMPONENT, &Z_AXIS);

    fprintf(stdout, CYAN "%s\n" RESET, label);
    fprintf(stdout, CYAN "  X-Gimbal orientation: [%f, %f, %f]\n" RESET,
            X_AXIS.x,
            X_AXIS.y,
            X_AXIS.z);
    fprintf(stdout, CYAN "  Y-Gimbal orientation: [%f, %f, %f]\n" RESET,
            Y_AXIS.x,
            Y_AXIS.y,
            Y_AXIS.z);
    fprintf(stdout, CYAN "  Z-Gimbal orientation: [%f, %f, %f]\n" RESET,
            Z_AXIS.x,
            Z_AXIS.y,
            Z_AXIS.z);
}

void on_gimbal_lock_trap(mat3_gimbal rotated,
                            vector_gimbal gimbal,
                            vec_component angle,
                            mat_processors proc) {
    rotation_transformer **transformers = proc.metadata;
    int gimbal_index = 0;
    if (GIMBAL_X == gimbal) {
        gimbal_index = 0;
    } else if (GIMBAL_Y == gimbal) {
        gimbal_index = 1;
    } else if (GIMBAL_Z == gimbal) {
        gimbal_index = 2;
    }
    if (transformers[gimbal_index]->loop == 1) {
        transformers[gimbal_index]->a0 = ref_angle;
        transformers[gimbal_index]->phi = phi;
        transformers[gimbal_index]->delta = delta;
        transformers[gimbal_index]->finished = 0;
    } else {
        transformers[gimbal_index]->finished = 1;
    }
    fprintf(stdout, "Gimbal lock trap triggered!\n");
    print_gimbal_state(YELLOW "Rotated Gimbal Angles:" RESET, rotated);
    print_gimbal_orientation(YELLOW "Rotated Gimbal Orientations:" RESET, rotated);
}

static void mat3_interpolate_rotation(rotation_transformer *transformer,
                                      mat3_processors processors) {

    transformer->phi = (transformer->a1 - transformer->a0) * transformer->lerp
                        + transformer->a0;
    // calculate the delta
    transformer->delta = transformer->phi - transformer->a0;
    transformer->a0 = transformer->phi;

    status_code __code =
            mat3_rotate(*transformer->mat_gimbal,
                            transformer->axis,
                        transformer->mat_gimbal,
                        transformer->delta, processors);

    if (PASS != __code) {
        return;
    }
}

/* [Previous test functions remain the same: print_gimbal_state, print_gimbal_orientation,
   assert_x_rotation_90, assert_y_rotation_90, assert_z_rotation_90,
   assert, on_assertion_success, on_assertion_failure] */

/* Execute test 1 with visualization */
static inline int64_t execute_x_rotation_visual(void **inputs) {
    vec_component __rotate_x[3] = {1, 0, 0,};
    vec_component __rotate_y[3] = {0, 1, 0,};
    vec_component __rotate_z[3] = {0, 0, 1,};
    vec_component *__rotate_comps[3] = {__rotate_x, __rotate_y, __rotate_z};

    vec_component __gimbal_x[3] = {1, 0, 0,};
    vec_component __gimbal_y[3] = {0, 1, 0,};
    vec_component __gimbal_z[3] = {0, 0, 1,};
    vec_component *__gimbal_comps[3] = {__gimbal_x, __gimbal_y, __gimbal_z};

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
                    .x_gimbal = 0.0f,
                    .y_gimbal = 0.0f,
                    .z_gimbal = 0.0f
            }
    };

    fprintf(stdout, "\n=== Test 1: X-axis Rotation (90°) with Visualization ===\n");

    gimbal_visualizer *viz = gimbal_visualizer_init(800, 600, &mat_gimbal.gimbal3d);
    if (!viz) {
        fprintf(stderr, RED "Failed to initialize visualizer\n" RESET);
        return ASSERTION_FAILURE;
    }


    rotation_transformer transformer_y = {
            .a0 = ref_angle,
            .a1 = 3.0f * M_PI / 2.0f,
            .delta = delta,
            .phi = phi,
            .etta = ___DELTA,
            .mat_gimbal = &mat_gimbal,
            .axis = VEC3_Y_COMPONENT,
            .lerp = .008f,
            .loop = 1,
            .name = "Y-Axis Rotation"
    };


    rotation_transformer transformer_x = {
            .a0 = ref_angle,
            .a1 = 5.0f * M_PI / 2.0f,
            .delta = delta,
            .phi = phi,
            .etta = ___DELTA,
            .mat_gimbal = &mat_gimbal,
            .axis = VEC3_X_COMPONENT,
            .lerp = .008f,
            .loop = 1,
            .name = "X-Axis Rotation"
    };

    rotation_transformer transformer_z = {
            .a0 = ref_angle,
            .a1 = M_PI / 2.0f,
            .delta = delta,
            .phi = phi,
            .etta = ___DELTA,
            .mat_gimbal = &mat_gimbal,
            .axis = VEC3_Z_COMPONENT,
            .lerp = .008f,
            .loop = 1,
            .name = "Z-Axis Rotation"
    };

    rotation_transformer *transformer[3] = {&transformer_x,
                                            &transformer_y,
                                            &transformer_z};

    mat3_processors processors = {
            .processors = {
                .metadata = transformer
            },
            .on_gimbal_lock_trap = &on_gimbal_lock_trap,
    };

    for (; ;) {
        if (transformer_x.finished == 0 || 1) {
            mat3_interpolate_rotation(&transformer_x,
                                      processors);
        }

        // after this; the Z-axis rotator is swapped with the Y-axis rotator
        // now; ordering rotation around the Y-axis would use the Z-axis rotator
        // and vice versa

        if (transformer_x.finished == 1 || 1) {
            mat3_interpolate_rotation(&transformer_y,
                                      processors);
        }

         // after this; the Z-axis rotator (which was Y rotator) is swapped with the X-axis rotator
         // now; ordering rotation around the Z-axis would use the X-axis rotator

        if (transformer_y.finished == 1 || 1) {
            mat3_interpolate_rotation(&transformer_z,
                                      processors);
        }

        gimbal_visualizer_update(viz, &mat_gimbal);
        gimbal_visualizer_render(viz, &mat_gimbal);

        if (gimbal_visualizer_should_close(viz)) break;
        usleep(16667);
    }

    gimbal_visualizer_destroy(viz);

    fprintf(stdout, GREEN "✓ Visualization completed\n" RESET);
    return ASSERTION_SUCCESS;
}

int main() {
    fprintf(stdout, "\n========================================\n");
    fprintf(stdout, "Matrix3 Gimbal Rotation - Visual Tests\n");
    fprintf(stdout, "========================================\n");

    fprintf(stdout, "\nRunning X-axis rotation test with OpenGL visualization...\n");
    execute_x_rotation_visual(NULL);

    fprintf(stdout, "\n========================================\n");
    fprintf(stdout, "Tests completed!\n");
    fprintf(stdout, "========================================\n");

    return 0;
}