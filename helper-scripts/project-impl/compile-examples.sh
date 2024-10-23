#!/bin/bash

source "./helper-scripts/abstract/abstract-compile-examples.sh"
source "./helper-scripts/project-impl/variables.sh"

TARGET_MACHINE="${1}"
EXAMPLE="${2}"
EXECUTABLE_SUFFIX="${3}"
SYSTEM_DIR="${4}"
BUILD_DIR="${5}"
SHARED_LIB="${6}"

cd "${project_root}/${electrostatic_sandbox}" || exit

compile "${GCC_BIN_x86}" "${GPP_BIN_x86}" "${SHARED_LIB}" "${INPUT_COMPILER_OPTIONS}" \
        "${TARGET_MACHINE}" "${TOOLCHAIN_INCLUDES_x86}" "${source_dir}" \
        "${EXAMPLE}" "${EXECUTABLE_SUFFIX}" "${SYSTEM_DIR}/${BUILD_DIR}" "${examples_dir}"

cd "${project_root}" || exit
