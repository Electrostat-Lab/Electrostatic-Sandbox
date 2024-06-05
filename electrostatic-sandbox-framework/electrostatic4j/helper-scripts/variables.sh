#!/bin/bash

project_root=$(pwd)
library="libelectrostatic4j"

# home for toolchains and header files to link to sources
GCC_BIN="/usr/bin/gcc"
GPP_BIN="/usr/bin/g++"
TOOLCHAIN_INCLUDES="/usr/include/"
INPUT_COMPILER_OPTIONS="-fPIC -O2"

# supported targets
x86="x86"
x86_64="x86-64"

e4j_source="./electrostatic4j-native"
