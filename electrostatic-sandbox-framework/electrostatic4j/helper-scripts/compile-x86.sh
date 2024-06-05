#!/bin/bash

# This must be called from the gradle wrapper directory entry
# That is why we use the return or back component [..]
source "../helper-scripts/abstract/abstract-compile-javabinding.sh"
source "../helper-scripts/abstract/abstract-util.sh"
source "./helper-scripts/variables.sh"

java_home=${1}
arch=${2}

compile "${GCC_BIN}" "${GPP_BIN}" "${INPUT_COMPILER_OPTIONS}" \
        "${arch}" "${TOOLCHAIN_INCLUDES}" "${java_home}"  \
        "${electrostatic_core}" "${e4j_source}"

getCurrentSystem

moveFile "${e4j_source}/cmake-build/${arch}/${library}.so" \
         "${e4j_source}/build/lib/${system}/${arch}/"