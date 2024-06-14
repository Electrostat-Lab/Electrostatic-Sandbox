#!/bin/bash

source "./helper-scripts/abstract/abstract-compile.sh"
source "./helper-scripts/abstract/abstract-util.sh"
source "./helper-scripts/project-impl/variables.sh"

GCC_BIN="${1}"
GPP_BIN="${2}"
TARGET_MACHINE="${3}"
TOOLCHAIN_HEADERS="${4}"
LINK_DIRS="${5}"
SYSTEM_DIR="${6}"
BUILD_DIR="${7}"
DEPENDENCIES="${8}"
CMAKE_TOOLCHAIN_FILEVAR="${9}"

# precompile scripts
sources=$(find "$(pwd)/${source_dir}/src/" -name *.c -o -name *.cpp -o -name *.cxx | tr '\n' ';')
dependencies=$(find "$(pwd)/${source_dir}/dependencies/libs/" -name *.a -o -name *.so -o -name *.ar | tr '\n' ';')

# compile scripts
compile "${COMMISSION_LIB}" "${GCC_BIN}" "${GPP_BIN}" "${INPUT_COMPILER_OPTIONS}" \
        "${TARGET_MACHINE}" "${TOOLCHAIN_HEADERS}" \
        "${SYSTEM_DIR}/${BUILD_DIR}" "." "${source_dir}" \
        "${sources}" "${LINK_DIRS}" "${dependencies};${DEPENDENCIES}" "${CMAKE_TOOLCHAIN_FILEVAR}"

# post compile scripts
mkdir -p "$(pwd)/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}"
mkdir -p "$(pwd)/${e4j_dir}/dependencies/"
mkdir -p "$(pwd)/${e4j_dir}/dependencies/libs/"

mkdir -p "$(pwd)/${examples_dir}/dependencies/"
mkdir -p "$(pwd)/${examples_dir}/dependencies/libs/"

cp -v "$(pwd)/${source_dir}/cmake-build/${SYSTEM_DIR}/${BUILD_DIR}/lib${COMMISSION_LIB}.so" \
    "$(pwd)/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}/"

cp -v "$(pwd)/${source_dir}/cmake-build/${SYSTEM_DIR}/${BUILD_DIR}/lib${COMMISSION_LIB_AR}.a" \
    "$(pwd)/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}/"

cp -rv "$(pwd)/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/${e4j_dir}/dependencies/libs/"

cp -rv "$(pwd)/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/${examples_dir}/dependencies/libs/"

cp -rv "$(pwd)/${source_dir}/src/include/" \
    "$(pwd)/${e4j_dir}/dependencies/"

cp -rv "$(pwd)/${source_dir}/src/include/" \
    "$(pwd)/${examples_dir}/dependencies/"