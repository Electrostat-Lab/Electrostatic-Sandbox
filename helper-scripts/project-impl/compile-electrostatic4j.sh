#!/bin/bash

# This must be called from the gradle wrapper directory entry
# That is why we use the return or back component [..]
source "./helper-scripts/abstract/abstract-compile.sh"
source "./helper-scripts/abstract/abstract-util.sh"
source "./helper-scripts/project-impl/variables.sh"

cd "${project_root}/${electrostatic_sandbox}" || exit

project_dir="${1}"
commission_lib="${2}"
GCC_BIN="${3}"
GPP_BIN="${4}"
BUILD_SHARED="${5}"
TOOLCHAIN_HEADERS="${6}"
java_home="${7}"
target="${8}"
system_dir="${9}"
build_dir="${10}"

echo "${build_dir}"

# precompile scripts
sources=$(find "$(pwd)/${project_dir}/src/" -name *.c -o -name *.cpp -o -name *.cxx | tr '\n' ';')
dependencies=$(find "$(pwd)/${project_dir}/dependencies/libs/${system_dir}/${build_dir}" -name *.a | tr '\n' ';')

getCurrentSystem

JNI_HEADERS_SYSTEM="${JNI_HEADERS}/${system}"

compile "${commission_lib}" "${GCC_BIN}" "${GPP_BIN}" "${BUILD_SHARED}" "${INPUT_COMPILER_OPTIONS}" \
        "${target}" "${TOOLCHAIN_HEADERS};${JNI_HEADERS};${JNI_HEADERS_SYSTEM}" "${system_dir}/${build_dir}"  \
        "." "${project_dir}" "${sources}" "${dependencies};m;pthread;dl"

moveFile "${project_dir}/cmake-build/${system_dir}/${build_dir}/lib${commission_lib}.so" \
         "${project_dir}/build/lib/${system_dir}/${build_dir}/"

cd ${project_root} || exit