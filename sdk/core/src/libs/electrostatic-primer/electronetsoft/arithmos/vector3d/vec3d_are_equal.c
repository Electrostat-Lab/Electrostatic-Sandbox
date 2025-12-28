#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

status_code vec3d_are_equal(vector3d v0, vector3d v1, vec3d_processors *proc) {
    if (!(v0.x == v1.x && v0.y == v1.y && v0.z == v1.z)) {
        if (NULL != proc && NULL != proc->on_op_failed) {
            proc->on_op_failed(&vec3d_are_equal, ASSERTION_FAILURE);
        }
        return ASSERTION_FAILURE;
    }

    if (NULL != proc && NULL != proc->on_op_success) {
        proc->on_op_success(&vec3d_are_equal, v0);
    }

    return PASS;
}