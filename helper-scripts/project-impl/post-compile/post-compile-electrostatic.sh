#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

SYSTEM_DIR="${1}"
BUILD_DIR="${2}"

# prepare dependencies directories
mkdir -p "$(pwd)/electrostatic-sandbox-framework/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}"

mkdir -p "$(pwd)/electrostatic-sandbox-framework/${e4j_dir}/dependencies/"
mkdir -p "$(pwd)/electrostatic-sandbox-framework/${e4j_dir}/dependencies/libs/"

mkdir -p "$(pwd)/electrostatic-sandbox-framework/${serial4j_dir}/serial4j-native/dependencies/"
mkdir -p "$(pwd)/electrostatic-sandbox-framework/${serial4j_dir}/serial4j-native/dependencies/libs/"

mkdir -p "$(pwd)/electrostatic-sandbox-framework/${serial4j_dir}/serial4j-native-examples/dependencies/"
mkdir -p "$(pwd)/electrostatic-sandbox-framework/${serial4j_dir}/serial4j-native-examples/dependencies/libs/"

mkdir -p "$(pwd)/electrostatic-sandbox-framework/${examples_dir}/dependencies/"
mkdir -p "$(pwd)/electrostatic-sandbox-framework/${examples_dir}/dependencies/libs/"

# copying dependencies
cp "$(pwd)/electrostatic-sandbox-framework/${source_dir}/cmake-build/${SYSTEM_DIR}/${BUILD_DIR}/lib${COMMISSION_LIB}.so" \
    "$(pwd)/electrostatic-sandbox-framework/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}/"

cp "$(pwd)/electrostatic-sandbox-framework/${source_dir}/cmake-build/${SYSTEM_DIR}/${BUILD_DIR}/lib${COMMISSION_LIB_AR}.a" \
    "$(pwd)/electrostatic-sandbox-framework/${source_dir}/build/${SYSTEM_DIR}/${BUILD_DIR}/"

cp -r "$(pwd)/electrostatic-sandbox-framework/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/electrostatic-sandbox-framework/${e4j_dir}/dependencies/libs/"

cp -r "$(pwd)/electrostatic-sandbox-framework/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/electrostatic-sandbox-framework/${serial4j_dir}/serial4j-native/dependencies/libs/"

cp -r "$(pwd)/electrostatic-sandbox-framework/${source_dir}/build/${SYSTEM_DIR}" \
"$(pwd)/electrostatic-sandbox-framework/${serial4j_dir}/serial4j-native-examples/dependencies/libs/"

cp -r "$(pwd)/electrostatic-sandbox-framework/${source_dir}/build/${SYSTEM_DIR}" \
    "$(pwd)/electrostatic-sandbox-framework/${examples_dir}/dependencies/libs/"

cp -r "$(pwd)/electrostatic-sandbox-framework/${source_dir}/src/include/" \
    "$(pwd)/electrostatic-sandbox-framework/${e4j_dir}/dependencies/"

cp -r "$(pwd)/electrostatic-sandbox-framework/${source_dir}/src/include/" \
    "$(pwd)/electrostatic-sandbox-framework/${serial4j_dir}/serial4j-native/dependencies/"

cp -r "$(pwd)/electrostatic-sandbox-framework/${source_dir}/src/include/" \
"$(pwd)/electrostatic-sandbox-framework/${serial4j_dir}/serial4j-native-examples/dependencies/"

cp -r "$(pwd)/electrostatic-sandbox-framework/${source_dir}/src/include/" \
    "$(pwd)/electrostatic-sandbox-framework/${examples_dir}/dependencies/"