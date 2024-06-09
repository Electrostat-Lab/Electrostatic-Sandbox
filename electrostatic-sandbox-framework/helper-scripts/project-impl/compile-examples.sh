#!/bin/bash

source "./helper-scripts/abstract/abstract-compile-examples.sh"
source "./helper-scripts/project-impl/variables.sh"

TARGET_MACHINE="${1}"
EXAMPLE="${2}"
SYSTEM_DIR="${3}"
BUILD_DIR="${4}"

compile "${GCC_BIN_x86}" "${GPP_BIN_x86}" "${INPUT_COMPILER_OPTIONS}" \
        "${TARGET_MACHINE}" "${TOOLCHAIN_INCLUDES_x86}" "${source_dir}" \
        "${EXAMPLE}" "${SYSTEM_DIR}/${BUILD_DIR}" "${examples_dir}"
