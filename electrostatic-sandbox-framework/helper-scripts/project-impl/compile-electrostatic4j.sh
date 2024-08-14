#!/bin/bash

# This must be called from the gradle wrapper directory entry
# That is why we use the return or back component [..]
source "./helper-scripts/abstract/abstract-compile.sh"
source "./helper-scripts/abstract/abstract-util.sh"
source "./helper-scripts/project-impl/variables.sh"

project_dir="${1}"
commission_lib="${2}"
GCC_BIN="${3}"
GPP_BIN="${4}"
TOOLCHAIN_HEADERS="${5}"
java_home="${6}"
target="${7}"
system_dir="${8}"
build_dir="${9}"

echo "${build_dir}"

# precompile scripts
sources=$(find "$(pwd)/${project_dir}/src/" -name *.c -o -name *.cpp -o -name *.cxx | tr '\n' ';')
dependencies=$(find "$(pwd)/${project_dir}/dependencies/libs/${system_dir}/${build_dir}" -name *.a | tr '\n' ';')

getCurrentSystem

JNI_HEADERS_SYSTEM="${JNI_HEADERS}/${system}"

compile "${commission_lib}" "${GCC_BIN}" "${GPP_BIN}" "${INPUT_COMPILER_OPTIONS}" \
        "${target}" "${TOOLCHAIN_HEADERS};${JNI_HEADERS};${JNI_HEADERS_SYSTEM}" "${system_dir}/${build_dir}"  \
        "." "${project_dir}" "${sources}" "${dependencies}"

moveFile "${project_dir}/cmake-build/${system_dir}/${build_dir}/lib${commission_lib}.so" \
         "${project_dir}/build/lib/${system_dir}/${build_dir}/"
