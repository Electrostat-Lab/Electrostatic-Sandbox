#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

PRIMER="${1}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${GCC_BIN_x86}" "${GPP_BIN_x86}" \
        "${TARGET_x86_64}" "${TOOLCHAIN_INCLUDES}" "linux" "${x86_64}" "${PRIMER}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${GCC_BIN_x86}" "${GPP_BIN_x86}" \
        "${TARGET_x86}" "${TOOLCHAIN_INCLUDES}" "linux" "${x86}" "${PRIMER}"
