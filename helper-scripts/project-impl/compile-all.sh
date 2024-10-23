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
        "${GCC_BIN_x86}" "${GPP_BIN_x86}" "ON" \
        "${TARGET_x86_64}" "${TOOLCHAIN_INCLUDES}" "${platform_module} \
         ${comm_module} ${algorithm_module} ${util_module}" "NULL" "linux" "${x86_64}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${GCC_BIN_x86}" "${GPP_BIN_x86}" "ON" \
        "${TARGET_x86}" "${TOOLCHAIN_INCLUDES}" "${platform_module} \
        ${comm_module} ${algorithm_module} ${util_module}" "NULL" "linux" "${x86}"
