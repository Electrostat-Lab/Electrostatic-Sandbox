/**
 * @brief Provides incomplete type declarations to avoid cyclic headers processing issues.
 * @note Cyclic headers declaration issues arise when it's required by the utilities to include headers
 *       from the libraries (e.g., ADT Lists), and vice versa when those libraries are required to include
 *       declarations from utilities. The fix is to separate type declarations into another header unit.
 * @author pavl_g.
 */
#ifndef __TYPES_H_
#define __TYPES_H_

#include <inttypes.h>

#ifdef __cplusplus
extern "C" { // disables C++ Name Mangling
#endif

// Abstract Data Types for Lists
typedef struct list (list);
typedef struct list_info (list_info);

typedef enum list_type {
    CONTIGUOUS_BUFFER,
    LINKED_BUFFER
} list_type;

typedef struct list_element (list_element);
typedef struct list_function_table (list_function_table);

// Concretized types for linked buffers
typedef struct linked_buffer (linked_buffer);

typedef enum linked_buffer_type {
    SINGLE_ENDED,
    DOUBLE_ENDED,
} linked_buffer_type;

// Abstract types for Mathematical Graph Structures
typedef struct vertex (vertex);
typedef struct path (path);
typedef struct cellular_matrix (cellular_matrix);

// for edge-based implementation
typedef struct edge_matrix (edge_matrix);
typedef struct edge (edge);
typedef struct edge_path (edge_path);
typedef struct graph_processors (graph_processors);

// Concretized types for Graph Algorithms
typedef struct prim_processors (prim_processors);
typedef struct prim_structure (prim_structure);

typedef struct dijkstra_processors (dijkstra_processors);
typedef struct dijkstra_structure (dijkstra_structure);

// Abstract Types for utilities
typedef struct api_lifecycle (api_lifecycle);
typedef struct typed_pointer (typed_pointer);
typedef union pointer (pointer);

typedef enum status_code {
    PASS = INT32_MAX,
    EUNDEFINEDBUFFER = INT32_MIN,
    EEMPTYBUFFER = (EUNDEFINEDBUFFER + 1),
    EFULLBUFFER = (EEMPTYBUFFER + 1),
    EINCOMPATTYPE = (EFULLBUFFER + 1),
    ENOELEMENT = (EINCOMPATTYPE + 1),
    EBUFFERTURNCATION = (ENOELEMENT + 1),
    EBUFFEROVERFLOW = (EBUFFERTURNCATION + 1),
    EDLLOPENFAIL = (EBUFFEROVERFLOW + 1),
    EDLLSYMFAIL = (EDLLOPENFAIL + 1),
    EDLLCONVENTIONCALLRETURN = (EDLLSYMFAIL + 1),
    UNEXPECTED_ERROR = (EDLLCONVENTIONCALLRETURN + 1),
    ASSERTION_SUCCESS = 1,
    ASSERTION_FAILURE = 0
} status_code;

typedef struct memory_partition (memory_partition);

// Types for DLL Loader
typedef struct routine_data (routine_data);
typedef struct dll_function_table (dll_function_table);
typedef struct routine_callbacks (routine_callbacks);

typedef struct op_processor (op_processor);
typedef struct update_op_processor (update_op_processor);

typedef struct serializer_op_processor (serializer_op_processor);
typedef struct file_mem (file_mem);
typedef struct pipe_serializer (pipe_serializer);

// Types for Vector Maths Libraries
typedef struct vector2d (vector2d);

#ifdef __cplusplus
};
#endif

#endif