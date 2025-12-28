#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

SYSTEM_DIR="${1}"
BUILD_DIR="${2}"

# prepare dependencies directories
mkdir -p "$(pwd)/sdk/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}"

mkdir -p "$(pwd)/sdk/${e4j_dir}/dependencies/"
mkdir -p "$(pwd)/sdk/${e4j_dir}/dependencies/libs/"

mkdir -p "$(pwd)/sdk/${serial4j_dir}/serial4j-native/dependencies/"
mkdir -p "$(pwd)/sdk/${serial4j_dir}/serial4j-native/dependencies/libs/"

mkdir -p "$(pwd)/sdk/${serial4j_dir}/serial4j-native-examples/dependencies/"
mkdir -p "$(pwd)/sdk/${serial4j_dir}/serial4j-native-examples/dependencies/libs/"

mkdir -p "$(pwd)/sdk/${examples_dir}/dependencies/"
mkdir -p "$(pwd)/sdk/${examples_dir}/dependencies/libs/"

# copying dependencies
cp "$(pwd)/sdk/${source_dir}/cmake-build/${SYSTEM_DIR}/${BUILD_DIR}/lib${COMMISSION_LIB}.so" \
    "$(pwd)/sdk/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}/"

cp "$(pwd)/sdk/${source_dir}/cmake-build/${SYSTEM_DIR}/${BUILD_DIR}/lib${COMMISSION_LIB_AR}.a" \
    "$(pwd)/sdk/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}/"

cp -r "$(pwd)/sdk/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/sdk/${e4j_dir}/dependencies/libs/"

cp -r "$(pwd)/sdk/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/sdk/${serial4j_dir}/serial4j-native/dependencies/libs/"

cp -r "$(pwd)/sdk/${source_dir}/build/${SYSTEM_DIR}" \
"$(pwd)/sdk/${serial4j_dir}/serial4j-native-examples/dependencies/libs/"

cp -r "$(pwd)/sdk/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/sdk/${examples_dir}/dependencies/libs/"

cp -r "$(pwd)/sdk/${source_dir}/src/include/" \
    "$(pwd)/sdk/${e4j_dir}/dependencies/"

cp -r "$(pwd)/sdk/${source_dir}/src/include/" \
    "$(pwd)/sdk/${serial4j_dir}/serial4j-native/dependencies/"

cp -r "$(pwd)/sdk/${source_dir}/src/include/" \
"$(pwd)/sdk/${serial4j_dir}/serial4j-native-examples/dependencies/"

cp -r "$(pwd)/sdk/${source_dir}/src/include/" \
    "$(pwd)/sdk/${examples_dir}/dependencies/"