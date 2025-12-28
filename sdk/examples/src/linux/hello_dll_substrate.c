#include <electrostatic/electronetsoft/util/loader/dll_loader.h>
#include <electrostatic/electronetsoft/util/console/colors.h>
#include <stdlib.h>
#include <stdio.h>
#include <gnu/lib-names.h>

int main() {
    dll_function_table function_table = {
    };
    
    routine_data *data = calloc(1, sizeof(routine_data));
    // allocate 2 blocks for memory addresses of binary address size
    data->routine_inputs = calloc(2, sizeof(void *));
    // name caller service handler
    data->dispatcher_name = "DLL_SUBSTRATE-00144";
    data->dll_flags = RTLD_LAZY;
    // pass some args
    data->routine_inputs[0] = "Hello";
    data->routine_inputs[1] = " World\n";
    // define the absolute directory for the dll file
    data->dll_name = "/media/pavl/pavl-g/Projects/Electrostatic-Sandbox/electrostatic-sandbox-framework/electrostatic-examples/cmake-build/linux/x86-64/libhello_dll_service.c.so.elf";
    // define the service conventional routine name
    data->routine_name = "dll_conventional_routine";
    
    // initialize the default functions
    status_code _code0 = init(&function_table);
    if (PASS != _code0) {
        perror("Failed to initialize the function table\n");
    }
    
    // open the dll
    status_code _code1 = function_table.dll_open(data);
    if (PASS != _code1) {
        printf("Failed to open the dll file %s!\n", data->dll_error);
    }

    status_code _code2 = function_table.dll_function_loading(data, &function_table);
    if (PASS != _code2) {
        printf("Failed to load the dll function %s!\n", data->dll_error);
    }

    status_code _code3 = call_dll_convention(data, &function_table);
    if (PASS != _code3) {
        printf("Failed to call dll convention %s!\n", data->dll_error);
    } else {
        printf("Convention Output = %s", (const char *) data->routine_output);
    }

    function_table.dll_close(data);
    
    free(data->routine_inputs);
    free(data);
    return 0;
}