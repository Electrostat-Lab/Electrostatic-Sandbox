// dissociate this file from the ElectroMIO Library
#if !(defined _DLL_LOADER_H_ && defined _ELECTRO_MIO)
#define _DLL_LOADER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <dlfcn.h>
#include <electronetsoft/util/utilities.h>
#include <electronetsoft/arithmos/memory/patcher.h>
#include <electronetsoft/util/types.h>

struct routine_data {
  char *dispatcher_name;
  char *dll_name;
  void *dll_handle;
  int dll_flags;
  
  char *routine_name;
  void *routine_output;
  void **routine_inputs;
  char *dll_error;
  
  routine_callbacks *callbacks;
  status_code __code;
  memory_partition routine_memory;
};

// dynamic linking function table
struct dll_function_table {
  status_code (*dll_open)(routine_data *); // the dynamic library loading function
  status_code (*dll_close)(routine_data *); // the dynamic library closing function
  status_code (*dll_function_loading)(routine_data *, dll_function_table *table); // the loading function
  
  // this is the common pipe between dll files that the user should implement their logic in.
  // notice that this could be used with JNI too...
  // there will be native utilities on the Electrostatic-Sandbox for this
  // jSnapLoader v1.1.0 will be contemplated to create a dispatcher JNI routine
  // for this function on a specified DLL file on the file systems.
  void *(*dll_conventional_routine)(routine_data *data); // the conventional function
};

// NOT IMPLEMENTED YET!
struct routine_callbacks {
  void (*on_dispatch_success)(routine_data *);
  void (*on_dispatch_failure)(routine_data *, status_code);
  void (*on_loading_success)(routine_data *);
  void (*on_loading_failure)(routine_data *, status_code);
};

status_code init(dll_function_table *object);
status_code init_from(dll_function_table from, dll_function_table *to);
status_code call_dll_convention(routine_data *data, dll_function_table *table);

#ifdef __cplusplus
}
#endif

#endif