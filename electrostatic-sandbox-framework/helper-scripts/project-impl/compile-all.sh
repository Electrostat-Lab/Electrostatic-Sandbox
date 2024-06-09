#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${GCC_BIN_x86}" "${GPP_BIN_x86}" \
        "${TARGET_x86_64}" "${TOOLCHAIN_INCLUDES}" "linux" "${x86_64}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${GCC_BIN_x86}" "${GPP_BIN_x86}" \
        "${TARGET_x86}" "${TOOLCHAIN_INCLUDES}" "linux" "${x86}"