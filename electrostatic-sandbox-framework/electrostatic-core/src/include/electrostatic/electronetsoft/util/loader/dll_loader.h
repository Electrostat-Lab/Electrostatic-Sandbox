// dissociate this file from the ElectroMIO Library
#if !(defined _DLL_LOADER_H_ && defined _ELECTRO_MIO)
#define _DLL_LOADER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <dlfcn.h>
#include <electrostatic/electronetsoft/util/errno/errno.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/memory/patcher.h>

typedef struct routine_data (routine_data);
typedef struct dll_function_table (dll_function_table);
typedef struct routine_callbacks (routine_callbacks);

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
  errno error;
  memory_partition routine_memory;
};

// dynamic linking function table
struct dll_function_table {
  uint8_t (*dll_open)(routine_data *); // the dynamic library loading function
  int (*dll_close)(routine_data *); // the dynamic library closing function
  uint8_t (*dll_function_loading)(routine_data *, dll_function_table *table); // the loading function
  
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
  void (*on_dispatch_failure)(routine_data *, errno *);
  void (*on_loading_success)(routine_data *);
  void (*on_loading_failure)(routine_data *, errno *);
};

uint8_t init(dll_function_table *object);
uint8_t init_from(dll_function_table from, dll_function_table *to);
void *call_dll_convention(routine_data *data, dll_function_table *table);

#ifdef __cplusplus
}
#endif

#endif