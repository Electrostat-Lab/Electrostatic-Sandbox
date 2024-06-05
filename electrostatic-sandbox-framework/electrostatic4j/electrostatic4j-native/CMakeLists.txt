cmake_minimum_required(VERSION 3.18.1)

# define a project with a version
project(electrostatic4j-native VERSION 1.0)

# print java_home
message(STATUS "GCC: ${GCC_BIN}")
message(STATUS "GPP: ${GPP_BIN}")
message(STATUS "Compiler Options: ${INPUT_COMPILER_OPTIONS}")
message(STATUS "Target architecture: ${TARGET}")
message(STATUS "Toolchain Includes: ${TOOLCHAIN_INCLUDES}")
message(STATUS "JAVA_HOME: ${JAVA_HOME}")
message(STATUS "Included-library: ${ELECTROSTATIC_CORE}")

# assign the system dependent jni-headers identifier
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(system "win32")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(system "darwin")
else()
    set(system "linux")
endif()

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
set(library "electrostatic4j")
set(jni_headers "${JAVA_HOME}/include/"
                "${JAVA_HOME}/include/${system}/")
set(electrostatic_headers "${ELECTROSTATIC_CORE}/src/include/")
set(headers 
            "${CMAKE_CURRENT_SOURCE_DIR}/src/include/"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/include/${system}/"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/include/jni/"
            "${jni_headers}"
            "${electrostatic_headers}")
set(jni_sources "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/jni/electrostatic4j_NativeLibrary.c")
set(sources "${jni_sources}"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/linux/")

# add a library target
add_library(${library} SHARED ${sources})

# setup compiler options
set(COMPILER_OPTIONS "${ARCH_OPTIONS} ${INPUT_COMPILER_OPTIONS}")
message(STATUS "Building binary for: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Target Binary Instruction-set: ${TARGET}")

# set both COMPILE_FLAGS and LINK_FLAGS to the specified binary architecture
set_target_properties(${library} PROPERTIES COMPILE_FLAGS "${COMPILER_OPTIONS}" LINK_FLAGS "${COMPILER_OPTIONS}")

# include headers for the target
target_include_directories(${library} PUBLIC ${headers})

target_link_libraries(${library} PUBLIC "${ELECTROSTATIC_CORE}/build/${TARGET}/libelectrostatic-a.a")

# Start building the target
target_sources(${library} PUBLIC ${sources})