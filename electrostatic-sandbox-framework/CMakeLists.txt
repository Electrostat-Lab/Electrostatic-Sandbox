cmake_minimum_required(VERSION 3.18.1)

# define a project with a version
project(electrostatic-sandbox VERSION 1.0)

# To generate compile_commands.json for your project,
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Project: electrostatic-sandbox")
message(STATUS "Current Library in-comission: ${COMMISSION_LIB}")
message(STATUS "GCC: ${GCC_BIN}")
message(STATUS "GPP: ${GPP_BIN}")
message(STATUS "Compiler Options: ${INPUT_COMPILER_OPTIONS}")
message(STATUS "Target architecture: ${TARGET}")
message(STATUS "Toolchain Headers: ${TOOLCHAIN_HEADERS}")
message(STATUS "Source Directory: ${SOURCES_DIR}")
message(STATUS "Project sources: ${PROJECT_SOURCES}")
message(STATUS "Dependencies: ${DEPENDENCIES}")
message(STATUS "Dependencies Directories: ${DEPENDENCIES_DIRS}")
message(STATUS "Building the binaries to: ${BUILD_DIR}")

set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCES_DIR}")

# Cmake variables
set(library_so "${COMMISSION_LIB}")
set(library_a "${COMMISSION_LIB}-a")

set(CMAKE_C_COMPILER "${GCC_BIN}")
set(CMAKE_CXX_COMPILER "${GPP_BIN}")
set(COMPILER_OPTIONS "${TARGET} ${INPUT_COMPILER_OPTIONS}")

set(headers "${TOOLCHAIN_HEADERS}"
            "${PROJECT_SOURCE_DIR}/dependencies/include/"
            "${PROJECT_SOURCE_DIR}/src/include/")
            
set(libelectrostatic "${PROJECT_SOURCES}")

# add a library target
add_library(${library_a} STATIC ${libelectrostatic})
add_library(${library_so} SHARED ${libelectrostatic})

# set both COMPILE_FLAGS and LINK_FLAGS to the specified binary architecture
set_target_properties(${library_a} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")
set_target_properties(${library_so} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")

# include headers for the target
target_include_directories(${library_a} PUBLIC ${headers})
target_include_directories(${library_so} PUBLIC ${headers})

link_directories(${DEPENDENCIES_DIRS})

target_link_libraries(${library_a} PUBLIC "${DEPENDENCIES}")
target_link_libraries(${library_so} PUBLIC "${DEPENDENCIES}")

# Start building the target
target_sources(${library_a} PUBLIC ${libelectrostatic})
target_sources(${library_so} PUBLIC ${libelectrostatic})