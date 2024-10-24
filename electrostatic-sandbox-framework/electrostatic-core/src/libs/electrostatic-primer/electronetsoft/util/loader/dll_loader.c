#if !defined(_ELECTRO_MIO)
#include <electrostatic/electronetsoft/util/errno/errno.h>
#include <electrostatic/electronetsoft/util/loader/dll_loader.h>
#include <stdint.h>

static inline uint8_t dispatch_on_loading_success(routine_data *data) {
    if (data->callbacks == NULL || data->callbacks->on_loading_success == NULL) {
        return 0;   
    }
    
    data->callbacks->on_loading_success(data);
    return 0;
}

static inline uint8_t dispatch_on_loading_failure(routine_data *data) {
    if (data->callbacks == NULL || data->callbacks->on_loading_failure == NULL) {
        return 1;   
    }
    data->callbacks->on_loading_failure(data, NULL);
    return 1;
}

static inline uint8_t dispatch_on_dispatch_success(routine_data *data) {
    if (data->callbacks == NULL || data->callbacks->on_dispatch_success == NULL) {
        return 0;   
    }
    data->callbacks->on_dispatch_success(data);
    return 0;
}

static inline uint8_t dispatch_on_dispatch_failure(routine_data *data) {
    if (data->callbacks == NULL || data->callbacks->on_dispatch_failure == NULL) {
        return 1;   
    }
    data->callbacks->on_dispatch_failure(data, NULL);
    return 1;
}

static inline uint8_t dll_open(routine_data *data) {
    if (data == NULL || data->dll_name == NULL) {
        init_errno(&data->error);
        data->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    data->dll_handle = dlopen(data->dll_name, data->dll_flags);
    data->dll_error = dlerror();
    return 0;
}

static inline int dll_close(routine_data *data) {
    if (data == NULL || data->dll_handle == NULL) {
        init_errno(&data->error);
        data->error.value = EUNDEFINEDBUFFER;
        return 1;
    }
    int value = dlclose(data->dll_handle);
    data->dll_error = dlerror();
    return value;
}

static inline uint8_t dll_function_loading(routine_data *data, dll_function_table *table) {
    if (data == NULL || data->dll_handle == NULL || data->routine_name == NULL) {
        init_errno(&data->error);
        data->error.value = EUNDEFINEDBUFFER;
        return dispatch_on_loading_failure(data);
    }
    table->dll_conventional_routine = dlsym(data->dll_handle, data->routine_name);
    data->dll_error = dlerror();
    return dispatch_on_loading_success(data);
}

uint8_t init(dll_function_table *object) {
    if (object == NULL) {
        return 1;
    }
    
    object->dll_open = dll_open;
    object->dll_close = dll_close;
    object->dll_function_loading = dll_function_loading;
    
    return 0;
}

uint8_t init_from(dll_function_table from, dll_function_table *to) {
    if (to == NULL) {
        return 1;
    }
    
    to->dll_conventional_routine = from.dll_conventional_routine;
    to->dll_function_loading = from.dll_function_loading;
    to->dll_open = from.dll_open;
    to->dll_close = from.dll_close;
     
    return 0;
}

void *call_dll_convention(routine_data *data, dll_function_table *table) {
    if (data == NULL || table == NULL || table->dll_conventional_routine == NULL) {
        init_errno(&data->error);
        data->error.value = EUNDEFINEDBUFFER;
        dispatch_on_dispatch_failure(data);
        return NULL;
    }
    data->routine_output = table->dll_conventional_routine(data);
    dispatch_on_dispatch_success(data);
    return data->routine_output; 
}
#endif