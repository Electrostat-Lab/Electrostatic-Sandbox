#!/bin/bash

source "./helper-scripts/abstract/abstract-compile.sh"
source "./helper-scripts/abstract/abstract-util.sh"
source "./helper-scripts/project-impl/variables.sh"

TARGET_MACHINE="${1}"
BUILD_DIR="${TARGET_MACHINE}"

compile "" "${CLANG_BIN}" "${CLANGPP_BIN}" "${INPUT_COMPILER_OPTIONS}" \
"${NDK_TOOLCHAIN_INCLUDES}" "${TARGET_MACHINE}" "${BUILD_DIR}" "${source_dir}"