// dissociate this file from the ElectroMIO Library
#if !(defined GIMBAL_VISUALIZER_H && (defined __LINUX_x86 || defined _ELECTRO_MIO || defined _ELECTRO_ANDROID))

#define GIMBAL_VISUALIZER_H

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <electronetsoft/arithmos_calculus.h>
#include <electronetsoft/arithmos/vectorspaces/matrix/matrix.h>

typedef struct {
    GLFWwindow *window;
    int width;
    int height;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    vec3d_gimbal gimbal;
} gimbal_visualizer;

/* Initialize the OpenGL window and visualizer */
gimbal_visualizer* gimbal_visualizer_init(int width, int height, vec3d_gimbal *gimbal);

/* Update and Render the gimbal visualization */
void gimbal_visualizer_render(gimbal_visualizer *viz, mat3_gimbal *gimbal);
void gimbal_visualizer_update(gimbal_visualizer *viz, mat3_gimbal *mat_gimbal);

/* Check if the visualizer window should close */
int gimbal_visualizer_should_close(gimbal_visualizer *viz);

/* Cleanup and destroy the visualizer */
void gimbal_visualizer_destroy(gimbal_visualizer *viz);

#endif