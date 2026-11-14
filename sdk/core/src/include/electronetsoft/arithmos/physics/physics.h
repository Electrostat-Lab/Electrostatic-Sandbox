#ifndef __PHYSICS_2D_ENGINE_H_
#define __PHYSICS_2D_ENGINE_H_

#include <electrostatic/electronetsoft/util/types.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vector2d/vector2d.h>

#ifdef __cplusplus
extern "C" {
#endif

struct physics2d_engine {
    physics2d_object **objects;
    // queue of states
};

struct physics2d_object {
    object2d_transformation *transformation;
    vector2d d_velocity;
    float d_time;
    float mass;
    uint8_t is_static;
};

struct derivative {

};

struct physics2d_processor {
    void (*on_engine_ready)(physics2d_engine *);
    void (*on_engine_update)(physics2d_engine *, float);
    void (*on_position_changed)();
    void (*on_velocity_changed)();
    void (*on_collision)();
};

status_code physics2d_apply_force();

status_code physics2d_apply_torque();


#ifdef __cplusplus
};
#endif

#endif