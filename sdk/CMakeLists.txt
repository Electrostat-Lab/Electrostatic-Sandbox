cmake_minimum_required(VERSION 3.18.1)

# define a project with a version
project(electrostatic-sandbox VERSION 1.0)

# To generate compile_commands.json for your project,
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###################### CMake Predefined Variables ######################
############################################################

message(STATUS "Project: electrostatic-sandbox")
message(STATUS "Current Output in-comission: ${COMMISSION_OUTPUT}")
message(STATUS "GCC: ${GCC_BIN}")
message(STATUS "GPP: ${GPP_BIN}")
message(STATUS "Build Static Library: ${BUILD_STATIC}")
message(STATUS "Build Shared Library: ${BUILD_SHARED}")
message(STATUS "Build Executable binary: ${BUILD_EXE}")
message(STATUS "Compiler Options: ${INPUT_COMPILER_OPTIONS}")
message(STATUS "Target architecture: ${TARGET}")
message(STATUS "Toolchain Headers: ${HEADERS}")
message(STATUS "Source Directory: ${SOURCES_DIR}")
message(STATUS "Project sources: ${PROJECT_SOURCES}")
message(STATUS "Dependencies: ${DEPENDENCIES}")
message(STATUS "Building the binaries to: ${BUILD_DIR}")

###################### CMake Variables ######################
############################################################

set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_DIR}")

set(commission_so "${COMMISSION_OUTPUT}")
set(commission_a "${COMMISSION_OUTPUT}-a")
set(commission_exe "${COMMISSION_OUTPUT}.elf")

set(CMAKE_C_COMPILER "${GCC_BIN}")
set(CMAKE_CXX_COMPILER "${GPP_BIN}")
set(COMPILER_OPTIONS "${TARGET} ${INPUT_COMPILER_OPTIONS}")

set(headers "${HEADERS}")

###################### Build routines ######################
############################################################

# build an executable
if (BUILD_EXE)
    # add a library target
    add_executable(${commission_exe}) # executable based on the static archive
    set_target_properties(${commission_exe} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")
    # include headers for the target
    target_include_directories(${commission_exe} PUBLIC ${lib_headers} ${headers})
    target_link_libraries(${commission_exe} PUBLIC "${DEPENDENCIES}")
    # Start building the target
    target_sources(${commission_exe} PUBLIC "${PROJECT_SOURCES}")
endif ()

if (BUILD_STATIC)
    # add a library target
    add_library(${commission_a} STATIC)
    # set both COMPILE_FLAGS and LINK_FLAGS to the specified binary architecture
    set_target_properties(${commission_a} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")
    # include headers for the target
    target_include_directories(${commission_a} PUBLIC ${headers})
    target_link_libraries(${commission_a} PUBLIC "${DEPENDENCIES}")
    # Start building the target
    target_sources(${commission_a} PUBLIC "${PROJECT_SOURCES}")
endif ()

# build a shared library version
if (BUILD_SHARED)
    add_library(${commission_so} SHARED)
    set_target_properties(${commission_so} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")
    target_include_directories(${commission_so} PUBLIC ${headers})
    target_link_libraries(${commission_so} PUBLIC "${DEPENDENCIES}")
    target_sources(${commission_so} PUBLIC "${PROJECT_SOURCES}")
endif()
