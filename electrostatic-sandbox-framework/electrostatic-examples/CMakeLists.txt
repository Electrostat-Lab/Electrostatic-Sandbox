cmake_minimum_required(VERSION 3.18.1)

# define a project with a version
project(electrostatic-examples VERSION 1.0)

# display external options
message(STATUS "Project: electrostatic-examples")
message(STATUS "GCC: ${GCC_BIN}")
message(STATUS "GPP: ${GPP_BIN}")
message(STATUS "Compiler Options: ${INPUT_COMPILER_OPTIONS}")
message(STATUS "Target architecture: ${TARGET}")
message(STATUS "Toolchain Includes: ${TOOLCHAIN_INCLUDES}")
message(STATUS "Runnable-example: ${EXAMPLE}")
message(STATUS "Building the binaries to: ${BUILD_DIR}")

# Cmake variables
set(executable_a "${EXAMPLE}-a.elf") # target for archive-linked binary
set(executable_so "${EXAMPLE}.elf") # target for shared-linked binary

set(CMAKE_C_COMPILER "${GCC_BIN}")
set(CMAKE_CXX_COMPILER "${GPP_BIN}")
set(COMPILER_OPTIONS "${TARGET} ${INPUT_COMPILER_OPTIONS}")

set(lib_headers "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include")
set(headers "${TOOLCHAIN_INCLUDES}")

# C sources
set(sources "${CMAKE_CURRENT_SOURCE_DIR}/src/${EXAMPLE}")

# add a library target
add_executable(${executable_a}) # executable based on the static archive
add_executable(${executable_so}) # executable based on the dynamic library

# set both COMPILE_FLAGS and LINK_FLAGS to the specified binary architecture
set_target_properties(${executable_a} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")
set_target_properties(${executable_so} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")

# include headers for the target
target_include_directories(${executable_a} PUBLIC ${lib_headers} ${headers})
target_include_directories(${executable_so} PUBLIC ${lib_headers} ${headers})

target_link_libraries(${executable_a} "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/${BUILD_DIR}/libelectrostatic-a.a")
target_link_libraries(${executable_so} "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libs/${BUILD_DIR}/libelectrostatic.so")

# Start building the target
target_sources(${executable_a} PUBLIC ${sources})
target_sources(${executable_so} PUBLIC ${sources})
