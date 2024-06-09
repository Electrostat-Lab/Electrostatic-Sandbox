#!/bin/bash

# This must be called from the gradle wrapper directory entry
# That is why we use the return or back component [..]
source "./helper-scripts/abstract/abstract-compile.sh"
source "./helper-scripts/abstract/abstract-util.sh"
source "./helper-scripts/project-impl/variables.sh"

java_home=${1}
target=${2}
build_dir=${3}

echo "${build_dir}"

# precompile scripts
sources=$(find "$(pwd)/${e4j_dir}/src/" -name *.c -o -name *.cpp -o -name *.cxx | tr '\n' ';')
dependencies=$(find "$(pwd)/${e4j_dir}/dependencies/libs/${build_dir}" -name *.a | tr '\n' ';')

getCurrentSystem

JNI_HEADERS_SYSTEM="${JNI_HEADERS}/${system}"

compile "${COMMISSION_LIB_4j}" "${GCC_BIN}" "${GPP_BIN}" "${INPUT_COMPILER_OPTIONS}" \
        "${target}" "${TOOLCHAIN_INCLUDES};${JNI_HEADERS};${JNI_HEADERS_SYSTEM}" "${build_dir}"  \
        "." "${e4j_dir}" "${sources}" "${dependencies}"


moveFile "${e4j_dir}/cmake-build/${build_dir}/lib${COMMISSION_LIB_4j}.so" \
         "${e4j_dir}/build/lib/${system}/${build_dir}/"