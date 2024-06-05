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

# assign the target architecture arguments from the pre-determined directory
if("${TARGET}" STREQUAL "x86")
    set(ARCH_OPTIONS "-m32")
    message(STATUS "Compiling for 32-bit Intel Chipset")
elseif("${TARGET}" STREQUAL "x86-64")
    set(ARCH_OPTIONS "-m64")
    message(STATUS "Compiling for 64-bit Intel Chipset")
# elseif(${TARGET} STREQUAL "android-x86")
else()
    set(${TARGET} "x86-64")
    set(ARCH_OPTIONS "-m64")
endif()

# Cmake variables
set(library_so "electrostatic")
set(library_a "electrostatic-a")

set(CMAKE_C_COMPILER "${GCC_BIN}")
set(CMAKE_CXX_COMPILER "${GPP_BIN}")
set(COMPILER_OPTIONS "${ARCH_OPTIONS} ${INPUT_COMPILER_OPTIONS}")

set(toolchain_headers "${TOOLCHAIN_INCLUDES}")
set(libelectrostatic "${CMAKE_CURRENT_SOURCE_DIR}/src/libelectrostatic/comm/init_protocol.c")

set(headers "${toolchain_headers}"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/include/")

# add a library target
add_library(${library_a} STATIC ${libelectrostatic})
add_library(${library_so} SHARED ${libelectrostatic})

# set both COMPILE_FLAGS and LINK_FLAGS to the specified binary architecture
set_target_properties(${library_a} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")
set_target_properties(${library_so} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")


# include headers for the target
target_include_directories(${library_a} PUBLIC ${headers})
target_include_directories(${library_so} PUBLIC ${headers})

# Start building the target
target_sources(${library_a} PUBLIC ${libelectrostatic})
target_sources(${library_so} PUBLIC ${libelectrostatic})