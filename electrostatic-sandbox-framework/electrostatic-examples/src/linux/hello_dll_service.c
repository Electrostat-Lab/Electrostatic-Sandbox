#include <electrostatic/util/loader/dll_loader.h>
#include <electrostatic/util/console/colors.h>
#include <stdio.h>

void *dll_conventional_routine(routine_data *data);

void *dll_conventional_routine(routine_data *data) {
    // interpret the conventional call into a service job
    const char *caller = data->dispatcher_name;
    
    fprintf(stdout, MAGENTA "Dispatched service from caller substrate --- %s\n" MAGENTA, caller);
    fprintf(stdout, GREEN "%s" GREEN, ((const char **) data->routine_inputs)[0]);
    fprintf(stdout, GREEN "%s" GREEN, ((const char **) data->routine_inputs)[1]);
    
    return "Hello Back\n";
}

int main() {
    return 0;
}