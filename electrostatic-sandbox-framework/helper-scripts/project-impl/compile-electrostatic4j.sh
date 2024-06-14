#!/bin/bash

# This must be called from the gradle wrapper directory entry
# That is why we use the return or back component [..]
source "./helper-scripts/abstract/abstract-compile.sh"
source "./helper-scripts/abstract/abstract-util.sh"
source "./helper-scripts/project-impl/variables.sh"

GCC_BIN="${1}"
GPP_BIN="${2}"
TOOLCHAIN_HEADERS="${3}"
java_home="${4}"
LINK_DIRS="${5}"
target="${6}"
system_dir="${7}"
build_dir="${8}"

echo "${build_dir}"

# precompile scripts
sources=$(find "$(pwd)/${e4j_dir}/src/" -name *.c -o -name *.cpp -o -name *.cxx | tr '\n' ';')
dependencies=$(find "$(pwd)/${e4j_dir}/dependencies/libs/${system_dir}/${build_dir}" -name *.a | tr '\n' ';')

getCurrentSystem

JNI_HEADERS_SYSTEM="${JNI_HEADERS}/${system}"

compile "${COMMISSION_LIB_4j}" "${GCC_BIN}" "${GPP_BIN}" "${INPUT_COMPILER_OPTIONS}" \
        "${target}" "${TOOLCHAIN_HEADERS};${JNI_HEADERS};${JNI_HEADERS_SYSTEM}" "${system_dir}/${build_dir}"  \
        "." "${e4j_dir}" "${sources}" "${LINK_DIRS}" "${dependencies}"

moveFile "${e4j_dir}/cmake-build/${system_dir}/${build_dir}/lib${COMMISSION_LIB_4j}.so" \
         "${e4j_dir}/build/lib/${system_dir}/${build_dir}/"