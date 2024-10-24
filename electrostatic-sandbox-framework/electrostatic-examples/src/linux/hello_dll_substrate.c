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
    data->dll_name = "/media/pavl-x86-machine/pavl-g/Projects/Electrostatic-Sandbox/electrostatic-sandbox-framework/electrostatic-examples/build/linux/x86-64/libhello_dll_service.c.so";
    // define the service conventional routine name
    data->routine_name = "dll_conventional_routine";
    
    // initialize the default functions
    init(&function_table);
    
    // open the dll
    function_table.dll_open(data);
    function_table.dll_function_loading(data, &function_table);
    call_dll_convention(data, &function_table);
    
    printf("Convention Output = %s", (const char *) data->routine_output);
    
    function_table.dll_close(data);
    
    free(data->routine_inputs);
    free(data);
    return 0;
}