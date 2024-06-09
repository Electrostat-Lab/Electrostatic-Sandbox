#!/bin/bash

source "./helper-scripts/abstract/abstract-compile.sh"
source "./helper-scripts/abstract/abstract-util.sh"
source "./helper-scripts/project-impl/variables.sh"

TARGET_MACHINE="${1}"
TOOLCHAIN_HEADERS="${2}"
BUILD_DIR="${3}"

# precompile scripts
sources=$(find "$(pwd)/${source_dir}/src/" -name *.c -o -name *.cpp -o -name *.cxx | tr '\n' ';')
dependencies=$(find "$(pwd)/${source_dir}/dependencies/libs/" -name *.a -o -name *.so -o -name *.ar | tr '\n' ';')

# compile scripts
compile "${COMMISSION_LIB}" "${GCC_BIN}" "${GPP_BIN}" "${INPUT_COMPILER_OPTIONS}" \
        "${TARGET_MACHINE}" "${TOOLCHAIN_HEADERS}" \
        "${BUILD_DIR}" "." "${source_dir}" "${sources}" "${dependencies}"

# post compile scripts
mkdir -p "$(pwd)/${source_dir}/build/${BUILD_DIR}"
mkdir -p "$(pwd)/${e4j_dir}/dependencies/"
mkdir -p "$(pwd)/${e4j_dir}/dependencies/libs/"

mkdir -p "$(pwd)/${examples_dir}/dependencies/"
mkdir -p "$(pwd)/${examples_dir}/dependencies/libs/"

cp -v "$(pwd)/${source_dir}/cmake-build/${BUILD_DIR}/lib${COMMISSION_LIB}.so" \
    "$(pwd)/${source_dir}/build/${BUILD_DIR}/" 

cp -v "$(pwd)/${source_dir}/cmake-build/${BUILD_DIR}/lib${COMMISSION_LIB_AR}.a" \
    "$(pwd)/${source_dir}/build/${BUILD_DIR}/"

cp -rv "$(pwd)/${source_dir}/build/${BUILD_DIR}/" \
    "$(pwd)/${e4j_dir}/dependencies/libs/"

cp -rv "$(pwd)/${source_dir}/build/${BUILD_DIR}/" \
    "$(pwd)/${examples_dir}/dependencies/libs/"

cp -rv "$(pwd)/${source_dir}/src/include/" \
    "$(pwd)/${e4j_dir}/dependencies/"

cp -rv "$(pwd)/${source_dir}/src/include/" \
    "$(pwd)/${examples_dir}/dependencies/"