#ifndef _GIMBAL_SYS_H_
#define _GIMBAL_SYS_H_

#include <math.h>
#include <electronetsoft/arithmos/vectorspaces/matrix/matrix.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>
#include <electronetsoft/util/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rotation_metadata {
    matrix *in_orientation;
    matrix *out_orientation;
};

status_code init_rotator_gimbal(vector3d axis, matrix orientation,
                                                matrix *__rotator,
                                              vec_component angle);

status_code rotate_gimbal(vector3d axis, matrix __rotator,
                                        vec3d_gimbal *in_gimbal,
                                        vec3d_gimbal *out_gimbal,
                                        vec3d_processors *procs);

#ifdef __cplusplus
};
#endif

#endif