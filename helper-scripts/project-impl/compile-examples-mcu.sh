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

compile "${AVR_GCC_BIN}" "${AVR_GPP_BIN}" "${SHARED_LIB}" "-D_ELECTRO_MIO" \
        "${TARGET_MACHINE}" "${AVR_TOOLCHAIN_INCLUDES}" "${source_dir}" \
        "${EXAMPLE}" "${EXECUTABLE_SUFFIX}" "${SYSTEM_DIR}/${BUILD_DIR}" "${examples_dir}"

cd "${project_root}" || exit
