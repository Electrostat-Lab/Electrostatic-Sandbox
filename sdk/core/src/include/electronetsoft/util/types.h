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
typedef struct iterator_info (iterator_info);

typedef enum list_type {
    CONTIGUOUS_BUFFER,
    LINKED_BUFFER
} list_type;

typedef struct list_element (list_element);
typedef struct list_operations (list_operations);

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
    EBUFFER_EXISTS = (UNEXPECTED_ERROR + 1),
    INVALID_OP = (EBUFFER_EXISTS + 1),
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
typedef struct file_page (file_page);
typedef struct file_pager (file_pager);
typedef struct file_paging_processor (file_paging_processor);

typedef struct pipe_serializer (pipe_serializer);

// Types for Vector Maths Libraries
typedef struct vector2d (vector2d);
typedef struct vec2d_space (vec2d_space);
typedef struct vec2d_polar (vec2d_polar);
typedef struct vec2d_processors (vec2d_processors);

typedef struct physics_engine (physics_engine);
typedef struct physics_vector (physics_vector);
typedef struct physics_object (physics_object);
typedef struct physics_particle (physics_particle);
typedef struct physics_group (physics_group);
typedef struct physics_processor (physics_processor);
typedef enum {
    LOCAL_PHYSICS_OPERATION = -(INVALID_OP + 1),
    GLOBAL_PHYSICS_OPERATION = (LOCAL_PHYSICS_OPERATION + 1)
} physics_op_type;

typedef struct object2d_transformation (object2d_transformation);

typedef struct vector3d (vector3d);
typedef struct vec3d_space (vec3d_space);
typedef struct vec3d_polar (vec3d_polar);
typedef struct vec3d_cylinderical (vec3d_cylinderical);
typedef struct vec3d_processors (vec3d_processors);
typedef struct vec3d_gimbal (vec3d_gimbal);

typedef struct matrix (matrix);
typedef struct mat_processors (mat_processors);
typedef struct mat_proc_sig (mat_proc_sig);
typedef struct mat_binary_op_sig (mat_binary_op_sig);
typedef enum mat_iterator {
    ROW_CONVENTION_ITERATOR = ((INT32_MAX >> 16) ^ INT32_MAX),
    COLUMN_CONVENTION_ITERATOR = ROW_CONVENTION_ITERATOR - 1,
} mat_iterator;
typedef struct mat3_gimbal (mat3_gimbal);
typedef struct mat3_processors (mat3_processors);

typedef struct caller_graph (caller_graph);

typedef struct map (map);
typedef struct map_element (map_element);
typedef enum map_type {
    MAP_TYPE_HASHMAP = COLUMN_CONVENTION_ITERATOR - 1,
    MAP_TYPE_TREEMAP = MAP_TYPE_HASHMAP - 1
} map_type;
typedef struct map_operations (map_operations);
typedef struct map_processors (map_processors);
typedef struct hash_component (hash_component);

typedef struct automaton (automaton);
typedef struct automaton_state (automaton_state);
typedef struct automaton_input (automaton_input);
typedef struct automaton_zeta (automaton_zeta);
typedef struct automaton_component (automaton_component);

typedef struct linear_congruent_seq (linear_congruent_seq);

typedef enum {
    ELEMENT_LIST = MAP_TYPE_TREEMAP - 1,
    ELEMENT_MAP_ITEM = ELEMENT_LIST - 1,
} element_type;

typedef struct text (text);
typedef struct text_operations (text_operations);
typedef struct text_substring (text_substring);

typedef struct eca (eca);
typedef struct eca_function_table (eca_function_table);
typedef struct eca_system (eca_system);
typedef struct eca_component (eca_component);

typedef struct permutation (permutation);
typedef struct combination (combination);

typedef struct file_driver (file_driver);
typedef struct driver_lexical_grammar (driver_lexical_grammar);
typedef struct driver_lexical_component (driver_lexical_component);
typedef struct file_processing_metadata (file_processing_metadata);
typedef struct file_driver_processor (file_driver_processor);
typedef struct file_driver_op (file_driver_op);

typedef struct txt_driver (txt_driver);
typedef struct json_driver (json_driver);
typedef struct sqlite_driver (sqlite_driver);
typedef struct sql_driver (sql_driver);

typedef enum {
    ALLOW_DUPLICATES = (ELEMENT_MAP_ITEM - 1),
    NO_DUPLICATES = (ALLOW_DUPLICATES - 1)
} collision_scheme;

#ifdef __cplusplus
};
#endif

#endif