#if !defined(_ELECTRO_MIO)
#include <electronetsoft/util/loader/dll_loader.h>
#include <stdint.h>

static inline status_code dispatch_on_loading_success(routine_data *data) {
    // preprocessing automata
    if (rvalue(data->callbacks) == NULL ||
            rvalue(data->callbacks->on_loading_success) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    
    data->callbacks->on_loading_success(data);
    return PASS;
}

static inline status_code dispatch_on_loading_failure(routine_data *data, status_code __code) {
    if (rvalue(data->callbacks) == NULL ||
            rvalue(data->callbacks->on_loading_failure) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    data->callbacks->on_loading_failure(data, __code);
    return __code;
}

static inline status_code dispatch_on_dispatch_success(routine_data *data) {
    if (rvalue(data->callbacks) == NULL ||
            rvalue(data->callbacks->on_dispatch_success) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    data->callbacks->on_dispatch_success(data);
    return PASS;
}

static inline status_code dispatch_on_dispatch_failure(routine_data *data, status_code __code) {
    if (rvalue(data->callbacks) == NULL ||
            rvalue(data->callbacks->on_dispatch_failure) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    data->callbacks->on_dispatch_failure(data, __code);
    return __code;
}

static inline status_code dll_open(routine_data *data) {
    // preprocessing automata -- Input Validation
    if (rvalue(data) == NULL || rvalue(data->dll_name) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    // processing automata
    data->dll_handle = dlopen(data->dll_name, data->dll_flags);
    data->dll_error = dlerror();
    // post-processing automata -- validate output
    if (rvalue(data->dll_handle) == NULL) {
        return EDLLOPENFAIL;
    }
    return PASS;
}

static inline status_code dll_close(routine_data *data) {
    if (rvalue(data) == NULL || rvalue(data->dll_handle) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    status_code _code = dlclose(data->dll_handle);
    data->dll_error = dlerror();
    return _code;
}

static inline status_code dll_function_loading(routine_data *data, dll_function_table *table) {
    if (rvalue(data) == NULL ||
            rvalue(data->dll_handle) == NULL ||
                rvalue(data->routine_name) == NULL) {
        dispatch_on_loading_failure(data, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }
    table->dll_conventional_routine = dlsym(data->dll_handle, data->routine_name);
    data->dll_error = dlerror();
    if (rvalue(table->dll_conventional_routine) == NULL) {
        dispatch_on_loading_failure(data, EDLLSYMFAIL);
        return EDLLSYMFAIL;
    }
    dispatch_on_loading_success(data);
    return PASS;
}

status_code init(dll_function_table *object) {
    if (rvalue(object) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    
    object->dll_open = dll_open;
    object->dll_close = dll_close;
    object->dll_function_loading = dll_function_loading;
    
    return PASS;
}

status_code init_from(dll_function_table from, dll_function_table *to) {
    if (rvalue(to) == NULL) {
        return EUNDEFINEDBUFFER;
    }
    
    to->dll_conventional_routine = from.dll_conventional_routine;
    to->dll_function_loading = from.dll_function_loading;
    to->dll_open = from.dll_open;
    to->dll_close = from.dll_close;
     
    return PASS;
}

status_code call_dll_convention(routine_data *data, dll_function_table *table) {
    if (rvalue(data) == NULL || rvalue(table) == NULL ||
            rvalue(table->dll_conventional_routine) == NULL) {
        dispatch_on_dispatch_failure(data, EUNDEFINEDBUFFER);
        return EUNDEFINEDBUFFER;
    }
    data->routine_output = table->dll_conventional_routine(data);
    dispatch_on_dispatch_success(data);
    return PASS;
}
#endif