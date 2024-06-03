#!/bin/bash

source "./helper-scripts/abstract/abstract-compile.sh"
source "./helper-scripts/project-impl/variables.sh"

TARGET_MACHINE="${1}"

compile "${GCC_BIN}" "${GPP_BIN}" "${INPUT_COMPILER_OPTIONS}" "${TOOLCHAIN_INCLUDES}" "${TARGET_MACHINE}" "${source_dir}"
