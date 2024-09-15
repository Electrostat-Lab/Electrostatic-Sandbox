#!/bin/bash

project_root=$(pwd)

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
INPUT_COMPILER_OPTIONS="-fPIC -O2"

# specify android triples
minSDKVersion="21"
ARM_64="aarch64-linux-android${minSDKVersion}"
ARM_32="armv7a-linux-androideabi${minSDKVersion}"
ANDROID_x86="i686-linux-android${minSDKVersion}"
ANDROID_x86_64="x86_64-linux-android${minSDKVersion}"

# specify symbolic binaries for android llvm
CLANG_BIN="android-clang"
CLANGPP_BIN="android-clang++"
NDK_TOOLCHAIN_INCLUDES="android-ndk-headers"

# supported targets for intel chipsets
x86="x86"
x86_64="x86-64"
TARGET_x86_64="-m64"
TARGET_x86="-m32"

# cmake build caches
source_dir="electrostatic-core"
examples_dir="electrostatic-examples"

e4j_dir="electrostatic4j/electrostatic4j-native"
serial4j_dir="electrostatic4j/serial4j"
