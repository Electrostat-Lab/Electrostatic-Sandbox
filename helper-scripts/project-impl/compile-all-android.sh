#!/bin/bash
source "./helper-scripts/project-impl/variables.sh"

PRIMER_SUFFIX="${1}"

##
# define source modules
# The suffix 'primer' swaps binaries with
# the original project for testing purposes!
##
electronetsoft="$(pwd)/electrostatic-sandbox-framework/${source_dir}/src/libs/electrostatic${PRIMER_SUFFIX}/electronetsoft"

platform_module="${electronetsoft}/platform/linux/"
comm_module="${electronetsoft}/comm/"
algorithm_module="${electronetsoft}/algorithm/"
util_module="${electronetsoft}/util/"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" "ON" \
        "-target ${ARM_64}" "${NDK_TOOLCHAIN_INCLUDES}" "${platform_module} ${comm_module} \
        ${algorithm_module} ${util_module}" "NULL" "android" "${ARM_64}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" "ON" \
        "-target ${ARM_32}" "${NDK_TOOLCHAIN_INCLUDES}" "${platform_module} ${comm_module} \
        ${algorithm_module} ${util_module}" "NULL" "android" "${ARM_32}" "${PRIMER}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" "ON" \
        "-target ${ANDROID_x86}" "${NDK_TOOLCHAIN_INCLUDES}" "${platform_module} ${comm_module} \
        ${algorithm_module} ${util_module}" "NULL" "android" "${ANDROID_x86}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" "ON" \
        "-target ${ANDROID_x86_64}" "${NDK_TOOLCHAIN_INCLUDES}" "${platform_module} ${comm_module} \
        ${algorithm_module} ${util_module}" "NULL" "android" "${ANDROID_x86_64}"
