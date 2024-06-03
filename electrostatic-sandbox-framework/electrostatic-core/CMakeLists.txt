cmake_minimum_required(VERSION 3.18.1)

# define a project with a version
project(electrostatic-sandbox VERSION 1.0)

# To generate compile_commands.json for your project,
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Project: electrostatic-sandbox")
message(STATUS "GCC: ${GCC_BIN}")
message(STATUS "GPP: ${GPP_BIN}")
message(STATUS "Compiler Options: ${INPUT_COMPILER_OPTIONS}")
message(STATUS "Target architecture: ${TARGET}")
message(STATUS "Toolchain Includes: ${TOOLCHAIN_INCLUDES}")

# Cmake variables
set(library "electrostatic")
set(CMAKE_C_COMPILER "${GCC_BIN}")
set(CMAKE_CXX_COMPILER "${GPP_BIN}")
set(COMPILER_OPTIONS "${TARGET} ${INPUT_COMPILER_OPTIONS}")

set(toolchain_headers "${TOOLCHAIN_INCLUDES}")
set(libelectrostatic "${CMAKE_CURRENT_SOURCE_DIR}/src/libelectrostatic/comm/comm_open.c"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/libelectrostatic/comm/comm_close.c"  
              "${CMAKE_CURRENT_SOURCE_DIR}/src/libelectrostatic/comm/comm_finalize.c"
              "${CMAKE_CURRENT_SOURCE_DIR}/src/libelectrostatic/comm/comm_init.c")

set(headers "${toolchain_headers}"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/include/")

# add a library target
add_library(${library} STATIC ${libelectrostatic})

# set both COMPILE_FLAGS and LINK_FLAGS to the specified binary architecture
set_target_properties(${library} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")

# include headers for the target
target_include_directories(${library} PUBLIC ${headers})

# Start building the target
target_sources(${library} PUBLIC ${libelectrostatic})