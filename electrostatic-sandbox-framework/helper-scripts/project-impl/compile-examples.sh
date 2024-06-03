#!/bin/bash

source "./helper-scripts/abstract/abstract-compile-examples.sh"
source "./helper-scripts/project-impl/variables.sh"

TARGET_MACHINE="${1}"
example="${2}"

compile "${GCC_BIN}" "${GPP_BIN}" "${INPUT_COMPILER_OPTIONS}" \
        "${TARGET_MACHINE}" "${TOOLCHAIN_INCLUDES}" "${source_dir}" \
        "${example}" "${examples_dir}"
