#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

PRIMER_SUFFIX="${1}"

##
# define source modules
# The suffix 'primer' swaps binaries with
# the original project for testing purposes!
##
electronetsoft="$(pwd)/sdk/${source_dir}/src/libs/electrostatic${PRIMER_SUFFIX}/electronetsoft"
electrokio="$(pwd)/sdk/${source_dir}/src/libs/electrostatic${PRIMER_SUFFIX}/electroio/kio"

platform_module="${electronetsoft}/platform/linux/"
comm_module="${electronetsoft}/comm/"
algorithm_module="${electronetsoft}/arithmos/"
util_module="${electronetsoft}/util/"
electrokio_module="${electrokio}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${COMMISSION_LIB}" "${GCC_BIN_x86}" "${GPP_BIN_x86}" "ON" "ON" "OFF" "-O3 -fPIC" \
        "${TARGET_x86_64}" "${TOOLCHAIN_INCLUDES_x86};${electrostatic_core_headers}" "${platform_module} \
         ${comm_module} ${algorithm_module} ${util_module} ${electrokio_module}" "${NULL}" "m;pthread;dl" "${source_dir}" \
         "linux" "${x86_64}" "${POST_COMPILE_TRUE}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${COMMISSION_LIB}" "${GCC_BIN_x86}" "${GPP_BIN_x86}" "ON" "ON" "OFF" "-O3 -fPIC" \
        "${TARGET_x86}" "${TOOLCHAIN_INCLUDES_x86};${electrostatic_core_headers}" "${platform_module} \
        ${comm_module} ${algorithm_module} ${util_module}" "${NULL}" "m;pthread;dl" "${source_dir}" \
        "linux" "${x86}" "${POST_COMPILE_TRUE}"
