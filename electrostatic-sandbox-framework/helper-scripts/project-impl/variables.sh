#!/bin/bash

project_root=$(pwd)
# home for toolchains and header files to link to sources
GCC_BIN="/usr/bin/gcc"
GPP_BIN="/usr/bin/g++"
TOOLCHAIN_INCLUDES="/usr/include/"
INPUT_COMPILER_OPTIONS="-O2"

# supported targets
m32="m32"
m64="m64"

# cmake build caches
source_dir="$project_root/electrostatic-core/"
examples_dir="$project_root/electrostatic-examples"