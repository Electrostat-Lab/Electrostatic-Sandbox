#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

PRIMER_SUFFIX="${1}"

##
# define source modules
# The suffix 'primer' swaps binaries with
# the original project for testing purposes!
##
electronetsoft="$(pwd)/sdk/${source_dir}/src/libs/electrostatic${PRIMER_SUFFIX}/electronetsoft"
electroio="$(pwd)/sdk/${source_dir}/src/libs/electrostatic${PRIMER_SUFFIX}/electroio"

platform_module="${electronetsoft}/platform/linux/"
comm_module="${electronetsoft}/comm/"
algorithm_module="${electronetsoft}/arithmos/"
util_module="${electronetsoft}/util/unit-testing"
electromio_module="${electroio}/mio/"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${COMMISSION_LIB}" "${AVR_GCC_BIN}" "${AVR_GPP_BIN}" "ON" "OFF" "OFF" "-O2" \
        "-mmcu=atmega32 -D_ELECTRO_MIO" "${AVR_TOOLCHAIN_INCLUDES};${electrostatic_core_headers}" "${platform_module} \
         ${comm_module} ${algorithm_module} ${util_module} ${electromio_module}" "${NULL}" "m" "${source_dir}" "avr-mcu" "atmega32" "${POST_COMPILE_TRUE}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${COMMISSION_LIB}" "${AVR_GCC_BIN}" "${AVR_GPP_BIN}" "ON" "OFF" "OFF" "-O2" \
        "-mmcu=atmega328p -D_ELECTRO_MIO" "${AVR_TOOLCHAIN_INCLUDES};${electrostatic_core_headers}" "${platform_module} \
        ${comm_module} ${algorithm_module} ${util_module} ${electromio_module}" "${NULL}" "m" "${source_dir}" "avr-mcu" "atmega328p" "${POST_COMPILE_TRUE}"
