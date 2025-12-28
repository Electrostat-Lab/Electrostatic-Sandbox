#!/bin/bash

project_root=$(pwd)
electrostatic_sandbox="sdk"
NULL="NULL"

sandbox_path="/opt/electrostatic-sandbox"
COMMISSION_LIB="electrostatic"
COMMISSION_LIB_AR="electrostatic-a"
COMMISSION_LIB_4j="${COMMISSION_LIB}4j"
# home for toolchains and header files to link to sources
GCC_BIN_x86="gcc"
GPP_BIN_x86="g++"
TOOLCHAIN_INCLUDES_x86="/usr/local/include/posix-headers"
JAVA_HOME="/opt/electrostatic-sandbox/jdk-20.0.2"
JNI_HEADERS="${JAVA_HOME}/include"
INPUT_COMPILER_OPTIONS="-O2"
NDK_HOME="${sandbox_path}/android-ndk-r27c"

# specify android triples
minSDKVersion="21"
ARM_64="aarch64-linux-android${minSDKVersion}"
ARM_32="armv7a-linux-androideabi${minSDKVersion}"
ANDROID_x86="i686-linux-android${minSDKVersion}"
ANDROID_x86_64="x86_64-linux-android${minSDKVersion}"

# specify symbolic binaries for android llvm
CLANG_BIN="${NDK_HOME}/toolchains/llvm/prebuilt/linux-x86_64/bin/clang"
CLANGPP_BIN="${NDK_HOME}/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++"
NDK_TOOLCHAIN_INCLUDES="android-ndk-headers"

AVR_GCC_BIN="avr-gcc"
AVR_GPP_BIN="avr-g++"
AVR_TOOLCHAIN_INCLUDES="avr-headers"

# supported targets for intel chipsets
x86="x86"
x86_64="x86-64"
TARGET_x86_64="-m64"
TARGET_x86="-m32"

# cmake build caches
source_dir="core"
examples_dir="examples"

electrostatic_core_headers="$(pwd)/sdk/core/src/include"
POST_COMPILE_TRUE="POST_COMPILE_TRUE"

e4j_dir="electrostatic4j/electrostatic4j-native"
serial4j_dir="electrostatic4j/serial4j"

# AVR-DUDE properties
BAUD_RATE='57600'
PORT='/dev/ttyUSB0'
CHIP_ALIAS='m328p'
PROGRAMMER='arduino'
