#!/bin/bash

source "./helper-scripts/abstract/abstract-compile.sh"
source "./helper-scripts/project-impl/variables.sh"

TARGET_MACHINE="${1}"
EXAMPLE="${2}"
EXECUTABLE="${3}"
SYSTEM_DIR="${4}"
BUILD_DIR="${5}"

cd "${project_root}/${electrostatic_sandbox}" || exit $?

sources="$(pwd)/${examples_dir}/src/${EXAMPLE}"
dependencies="$(pwd)/${examples_dir}/dependencies/libs/${SYSTEM_DIR}/${BUILD_DIR}/libelectrostatic-a.a"

compile "${EXECUTABLE}" "${GCC_BIN_x86}" "${GPP_BIN_x86}" \
        "OFF" "OFF" "ON" "${INPUT_COMPILER_OPTIONS}" \
        "${TARGET_MACHINE}" "${TOOLCHAIN_INCLUDES_x86};${electrostatic_core_headers}" \
        "${examples_dir}" "${sources}" "${dependencies};m;pthread;dl"  \
         "${SYSTEM_DIR}/${BUILD_DIR}" "."

cd "${project_root}" || exit $?
