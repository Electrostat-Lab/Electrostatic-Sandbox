#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

PRIMER_SUFFIX="${1}"

##
# define source modules
# The suffix 'primer' swaps binaries with
# the original project for testing purposes!
##
electronetsoft="$(pwd)/electrostatic-sandbox-framework/${source_dir}/src/libs/electrostatic${PRIMER_SUFFIX}/electronetsoft"
electroio="$(pwd)/electrostatic-sandbox-framework/${source_dir}/src/libs/electrostatic${PRIMER_SUFFIX}/electroio"

platform_module="${electronetsoft}/platform/linux/"
comm_module="${electronetsoft}/comm/"
algorithm_module="${electronetsoft}/algorithm/"
util_module="${electronetsoft}/util/"
electromio_module="${electroio}/electromio/"

# override the input options
INPUT_COMPILER_OPTIONS="-O2"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${AVR_GCC_BIN}" "${AVR_GPP_BIN}" "OFF" \
        "-mmcu=atmega32 -D_ELECTRO_MIO" "${AVR_TOOLCHAIN_INCLUDES}" "${platform_module} \
         ${comm_module} ${algorithm_module} ${util_module} ${electromio_module}" "NULL" "avr-mcu" "atmega32"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${AVR_GCC_BIN}" "${AVR_GPP_BIN}" "OFF" \
        "-mmcu=atmega328p -D_ELECTRO_MIO" "${AVR_TOOLCHAIN_INCLUDES}" "${platform_module} \
        ${comm_module} ${algorithm_module} ${util_module} ${electromio_module}" "NULL" "avr-mcu" "atmega328p"
