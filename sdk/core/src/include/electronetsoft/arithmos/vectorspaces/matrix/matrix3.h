#ifndef _MAT_3D_H_
#define _MAT_3D_H_

#include <math.h>
#include <electronetsoft/arithmos/vectorspaces/matrix/matrix.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mat3_gimbal {
    matrix mat3d;
    vec3d_gimbal gimbal3d;
};

struct mat3_processors {
    mat_processors processors;
    void (*on_gimbal_lock_trap)(mat3_gimbal rotated,
            vector_gimbal gimbal,
            vec_component angle);
};

status_code mat3_translate(matrix, matrix, matrix *, mat_processors);
status_code mat3_rotate(mat3_gimbal m, vector3d axis,
                        mat3_gimbal *out, vec_component angle,
                        mat3_processors proc);
#ifdef __cplusplus
};
#endif

#endif