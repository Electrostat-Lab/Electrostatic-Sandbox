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

#"$(pwd)/${source_dir}/dependencies/libs/"

# precompile scripts
sources=$(find ${CODEBASE_MODULES[*]} -name *.c -o -name *.cpp -o -name *.cxx | tr '\n' ';')
dependencies=$(find ${DEPENDENCIES_MODULES[*]} -name *.a -o -name *.so -o -name *.ar | tr '\n' ';')

# compile scripts
compile "${COMMISSION_LIB}" "${GCC_BIN}" "${GPP_BIN}" "${BUILD_SHARED}" "${INPUT_COMPILER_OPTIONS}" \
        "${TARGET_MACHINE}" "${TOOLCHAIN_HEADERS}" \
        "${SYSTEM_DIR}/${BUILD_DIR}" "." "${source_dir}" "${sources}" "${dependencies};m;pthread;dl"


# post compile scripts
mkdir -p "$(pwd)/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}"

mkdir -p "$(pwd)/${e4j_dir}/dependencies/"
mkdir -p "$(pwd)/${e4j_dir}/dependencies/libs/"

mkdir -p "$(pwd)/${serial4j_dir}/serial4j-native/dependencies/"
mkdir -p "$(pwd)/${serial4j_dir}/serial4j-native/dependencies/libs/"

mkdir -p "$(pwd)/${serial4j_dir}/serial4j-native-examples/dependencies/"
mkdir -p "$(pwd)/${serial4j_dir}/serial4j-native-examples/dependencies/libs/"

mkdir -p "$(pwd)/${examples_dir}/dependencies/"
mkdir -p "$(pwd)/${examples_dir}/dependencies/libs/"

# copying dependencies
cp "$(pwd)/${source_dir}/cmake-build/${SYSTEM_DIR}/${BUILD_DIR}/lib${COMMISSION_LIB}.so" \
    "$(pwd)/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}/"

cp "$(pwd)/${source_dir}/cmake-build/${SYSTEM_DIR}/${BUILD_DIR}/lib${COMMISSION_LIB_AR}.a" \
    "$(pwd)/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}/"

cp -r "$(pwd)/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/${e4j_dir}/dependencies/libs/"

cp -r "$(pwd)/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/${serial4j_dir}/serial4j-native/dependencies/libs/"

cp -r "$(pwd)/${source_dir}/build/${SYSTEM_DIR}" \
"$(pwd)/${serial4j_dir}/serial4j-native-examples/dependencies/libs/"

cp -r "$(pwd)/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/${examples_dir}/dependencies/libs/"

cp -r "$(pwd)/${source_dir}/src/include/" \
    "$(pwd)/${e4j_dir}/dependencies/"

cp -r "$(pwd)/${source_dir}/src/include/" \
    "$(pwd)/${serial4j_dir}/serial4j-native/dependencies/"

cp -r "$(pwd)/${source_dir}/src/include/" \
"$(pwd)/${serial4j_dir}/serial4j-native-examples/dependencies/"

cp -r "$(pwd)/${source_dir}/src/include/" \
    "$(pwd)/${examples_dir}/dependencies/"

cd ${project_root} || exit
