#!/bin/bash

source "./helper-scripts/abstract/abstract-compile.sh"
source "./helper-scripts/abstract/abstract-util.sh"
source "./helper-scripts/project-impl/variables.sh"

cd "${project_root}/${electrostatic_sandbox}" || exit

GCC_BIN="${1}"
GPP_BIN="${2}"
BUILD_SHARED="${3}"
TARGET_MACHINE="${4}"
TOOLCHAIN_HEADERS="${5}"
CODEBASE_MODULES=("${6}")
DEPENDENCIES_MODULES=("${7}")
SYSTEM_DIR="${8}"
BUILD_DIR="${9}"

# precompile scripts
sources=$(find ${CODEBASE_MODULES[*]} -name *.c -o -name *.cpp -o -name *.cxx | tr '\n' ';')
dependencies=$(find ${DEPENDENCIES_MODULES[*]} -name *.a -o -name *.so -o -name *.ar | tr '\n' ';')

# compile scripts
compile "${COMMISSION_LIB}" "${GCC_BIN}" "${GPP_BIN}" "${BUILD_SHARED}" "${INPUT_COMPILER_OPTIONS}" \
        "${TARGET_MACHINE}" "${TOOLCHAIN_HEADERS}" \
        "${SYSTEM_DIR}/${BUILD_DIR}" "." "${source_dir}" "${sources}" "${dependencies};m;pthread;dl"

cd ${project_root}

# post compile scripts
./helper-scripts/project-impl/post-compile/post-compile-electrostatic.sh "${SYSTEM_DIR}" "${BUILD_DIR}" || exit
