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
message(STATUS "Included-library: ${ELECTROSTATIC_CORE}")
message(STATUS "Runnable-example: ${EXAMPLE}")

# Cmake variables
set(executable "${EXAMPLE}.elf")

set(CMAKE_C_COMPILER "${GCC_BIN}")
set(CMAKE_CXX_COMPILER "${GPP_BIN}")
set(COMPILER_OPTIONS "-${TARGET} ${INPUT_COMPILER_OPTIONS}")

set(lib_headers "${ELECTROSTATIC_CORE}/src/include")
set(headers "${TOOLCHAIN_INCLUDES}")

# C sources
set(sources "${CMAKE_CURRENT_SOURCE_DIR}/src/${EXAMPLE}")

# add a library target
add_executable(${executable})

# set both COMPILE_FLAGS and LINK_FLAGS to the specified binary architecture
set_target_properties(${executable} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")

# include headers for the target
target_include_directories(${executable} PUBLIC ${lib_headers} ${headers})

target_link_libraries(${executable} "${ELECTROSTATIC_CORE}/build/${TARGET}/libelectrostatic.a")

# Start building the target
target_sources(${executable} PUBLIC ${sources})
