#if !(defined __LINUX_x86 || defined _ELECTRO_MIO || defined _ELECTRO_ANDROID)
#include <electronetsoft/arithmos/vectorspaces/gimbal_visualizer.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Draw a 3D axis with colored lines */
static void draw_axis(float length, vector3d x_orientation,
                                    vector3d y_orientation,
                                    vector3d z_orientation) {
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    /* X-axis (Red) */
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(- length * x_orientation.x,
               - length * x_orientation.y,
               - length * x_orientation.z);
    glVertex3f(length * x_orientation.x,
               length * x_orientation.y,
               length * x_orientation.z);

    /* Y-axis (Green) */
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(- length * y_orientation.x,
               - length * y_orientation.y,
               - length * y_orientation.z);
    glVertex3f(length * y_orientation.x,
               length * y_orientation.y,
               length * y_orientation.z);

    /* Z-axis (Blue) */
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(- length * z_orientation.x,
               - length * z_orientation.y,
               - length * z_orientation.z);
    glVertex3f(length * z_orientation.x,
               length * z_orientation.y,
               length * z_orientation.z);
    glEnd();
    glLineWidth(1.0f);
}

/* Draw a gimbal ring (circle) */
static void draw_gimbal_ring(float radius, int segments) {
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    glColor4f(0.7f, 0.7f, 0.7f, 0.6f);

    for (int i = 0; i < segments; i++) {
        float angle = 2.0f * 3.14159265f * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0.0f);
    }

    glEnd();
    glLineWidth(1.0f);
}

/* Draw a cube to represent the gimbal object */
static void draw_cube(float size) {
    float s = size / 2.0f;

    glColor3f(0.2f, 0.5f, 0.8f);

    glBegin(GL_QUADS);
    /* Front face */
    glColor3f(0.2f, 0.5f, 0.8f);
    glVertex3f(-s, -s, s);
    glVertex3f(s, -s, s);
    glVertex3f(s, s, s);
    glVertex3f(-s, s, s);

    /* Back face */
    glColor3f(0.15f, 0.4f, 0.6f);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, -s, -s);

    /* Top face */
    glColor3f(0.3f, 0.6f, 0.9f);
    glVertex3f(-s, s, -s);
    glVertex3f(-s, s, s);
    glVertex3f(s, s, s);
    glVertex3f(s, s, -s);

    /* Bottom face */
    glColor3f(0.1f, 0.3f, 0.5f);
    glVertex3f(-s, -s, -s);
    glVertex3f(s, -s, -s);
    glVertex3f(s, -s, s);
    glVertex3f(-s, -s, s);

    /* Right face */
    glColor3f(0.25f, 0.55f, 0.85f);
    glVertex3f(s, -s, -s);
    glVertex3f(s, s, -s);
    glVertex3f(s, s, s);
    glVertex3f(s, -s, s);

    /* Left face */
    glColor3f(0.18f, 0.45f, 0.75f);
    glVertex3f(-s, -s, -s);
    glVertex3f(-s, -s, s);
    glVertex3f(-s, s, s);
    glVertex3f(-s, s, -s);

    glEnd();
}

gimbal_visualizer* gimbal_visualizer_init(int width, int height, vec3d_gimbal *gimbal) {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }

    GLFWwindow *window = glfwCreateWindow(width, height, "Gimbal Rotation Visualizer", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); /* Enable vsync */

    gimbal_visualizer *viz = (gimbal_visualizer *)malloc(sizeof(gimbal_visualizer));
    if (!viz) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return NULL;
    }

    viz->window = window;
    viz->width = width;
    viz->height = height;
    viz->gimbal = *gimbal;

    /* Setup OpenGL perspective */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)width / (float)height;
    float fov = 45.0f * 3.14159265f / 180.0f;
    float f = 1.0f / tanf(fov / 2.0f);
    float near = 0.1f, far = 100.0f;

    glFrustum(-aspect * near / f, aspect * near / f,
              -near / f, near / f, near, far);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    return viz;
}

void gimbal_visualizer_update(gimbal_visualizer *viz, mat3_gimbal *p_gimbal) {
    if (!viz) return;

    mat3_gimbal gimbal = *p_gimbal;

    viz->rotation_x = (float)gimbal.gimbal3d.x_gimbal * 180.0f / 3.14159265f;
    viz->rotation_y = (float)gimbal.gimbal3d.y_gimbal * 180.0f / 3.14159265f;
    viz->rotation_z = (float)gimbal.gimbal3d.z_gimbal * 180.0f / 3.14159265f;
}


void gimbal_visualizer_render(gimbal_visualizer *viz, mat3_gimbal *p_gimbal) {
    if (!viz) return;

    mat3_gimbal gimbal = *p_gimbal;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    vector3d X_AXIS = {
    };

    vector3d Y_AXIS = {
    };

    vector3d Z_AXIS = {
    };

    mat3_get_axis_orientation(gimbal, VEC3_X_COMPONENT, &X_AXIS);
    mat3_get_axis_orientation(gimbal, VEC3_Y_COMPONENT, &Y_AXIS);
    mat3_get_axis_orientation(gimbal, VEC3_Z_COMPONENT, &Z_AXIS);

    /* Apply gimbal rotations with the gimbals orientations */
    glRotatef(viz->rotation_x,
              X_AXIS.x,
              X_AXIS.y,
              X_AXIS.z);
    glRotatef(viz->rotation_y,
              Y_AXIS.x,
              Y_AXIS.y,
              Y_AXIS.z);
    glRotatef(viz->rotation_z,
              Z_AXIS.x,
              Z_AXIS.y,
              Z_AXIS.z);
    /* Draw reference axes */
    draw_axis(1.5f, X_AXIS, Y_AXIS, Z_AXIS);
    glPopMatrix();

    glPushMatrix();
    /* Draw gimbal rings */
    glRotatef(viz->rotation_x,
              X_AXIS.x,
              X_AXIS.y,
              X_AXIS.z);
    draw_gimbal_ring(1.0f, 32);

    glRotatef(viz->rotation_y,
              Y_AXIS.x,
              Y_AXIS.y,
              Y_AXIS.z);
    draw_gimbal_ring(1.0f, 32);

    glRotatef(viz->rotation_z,
              Z_AXIS.x,
              Z_AXIS.y,
              Z_AXIS.z);
    draw_gimbal_ring(1.0f, 32);
    glPopMatrix();

    /* Draw the central object */
    glPushMatrix();

    glRotatef(viz->rotation_x,
              X_AXIS.x,
              X_AXIS.y,
              X_AXIS.z);
    glRotatef(viz->rotation_y,
              Y_AXIS.x,
              Y_AXIS.y,
              Y_AXIS.z);
    glRotatef(viz->rotation_z,
              Z_AXIS.x,
              Z_AXIS.y,
              Z_AXIS.z);
    draw_cube(0.5f);
    glPopMatrix();

    glfwSwapBuffers(viz->window);
    glfwPollEvents();
}

int gimbal_visualizer_should_close(gimbal_visualizer *viz) {
    if (!viz) return 1;
    return glfwWindowShouldClose(viz->window);
}

void gimbal_visualizer_destroy(gimbal_visualizer *viz) {
    if (!viz) return;

    if (viz->window) {
        glfwDestroyWindow(viz->window);
    }
    glfwTerminate();
    free(viz);
}
#endif