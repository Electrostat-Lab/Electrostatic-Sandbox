#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>
#include <electronetsoft/arithmos/vectorspaces/vector3d/vector3d.h>

void vec3d_safe_exec_success(vector3d in, void *caller, vec3d_processors *proc) {
    if (NULL == proc || NULL == proc->on_op_success) {
        return;
    }
    proc->on_op_success(caller, in);
}


void vec3d_safe_exec_failure(void *caller,
                                   vec3d_processors *proc,
                                   status_code err) {
    if (NULL == proc || NULL == proc->on_op_failed) {
        return;
    }
    proc->on_op_failed(caller, err);
}