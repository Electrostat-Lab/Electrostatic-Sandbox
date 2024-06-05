#!/bin/bash

project_root=$(pwd)
# home for toolchains and header files to link to sources
GCC_BIN="/usr/bin/gcc"
GPP_BIN="/usr/bin/g++"
TOOLCHAIN_INCLUDES="/usr/include/"
INPUT_COMPILER_OPTIONS="-fPIC -O2"

# specify home for android llvm
NDK_TOOLCHAIN_LLVM=""
NDK_TOOLCHAIN_INCLUDES=""
OPTIONS_X86="-target x86"

# supported targets
x86="x86"
x86_64="x86-64"

# cmake build caches
source_dir="$project_root/electrostatic-core/"
examples_dir="$project_root/electrostatic-examples"

e4j_dir="$project_root/electrostatic4j/electrostatic4j-native/"
