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
        "${COMMISSION_LIB}" "${CLANG_BIN}" "${CLANGPP_BIN}" "ON" "ON" "OFF" "-O3 -fPIC" \
        "--target=${ARM_64}" \
        "${electrostatic_core_headers}" "${platform_module} ${comm_module} \
        ${algorithm_module} ${util_module}" "${NULL}" "m;c;dl" "${source_dir}" "android" "${ARM_64}" "${POST_COMPILE_TRUE}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${COMMISSION_LIB}" "${CLANG_BIN}" "${CLANGPP_BIN}" "ON" "ON" "OFF" "-O3 -fPIC" \
        "--target=${ARM_32}" \
        "${electrostatic_core_headers}" "${platform_module} ${comm_module} \
        ${algorithm_module} ${util_module}" "${NULL}" "m;c;dl" "${source_dir}" "android" "${ARM_32}" "${POST_COMPILE_TRUE}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${COMMISSION_LIB}" "${CLANG_BIN}" "${CLANGPP_BIN}" "ON" "ON" "OFF" "-O3 -fPIC" \
        "--target=${ANDROID_x86}" \
        "${electrostatic_core_headers}" "${platform_module} ${comm_module} \
        ${algorithm_module} ${util_module}" "${NULL}" "m;c;dl" "${source_dir}" "android" "${ANDROID_x86}" "${POST_COMPILE_TRUE}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${COMMISSION_LIB}" "${CLANG_BIN}" "${CLANGPP_BIN}" "ON" "ON" "OFF" "-O3 -fPIC" \
        "--target=${ANDROID_x86_64}" \
        "${electrostatic_core_headers}" "${platform_module} ${comm_module} \
        ${algorithm_module} ${util_module}" "${NULL}" "m;c;dl" "${source_dir}" "android" "${ANDROID_x86_64}" "${POST_COMPILE_TRUE}"
