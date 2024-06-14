#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

LINK_DIR="$(pwd)/${source_dir}/dependencies/libs/"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${GCC_BIN_x86}" "${GPP_BIN_x86}" \
        "${TARGET_x86_64}" "${TOOLCHAIN_INCLUDES}" \
        "${LINK_DIR}" "linux" "${x86_64}" "c;dl;pthread;stdc++"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${GCC_BIN_x86}" "${GPP_BIN_x86}" \
        "${TARGET_x86}" "${TOOLCHAIN_INCLUDES}" \
        "${LINK_DIR}" "linux" "${x86}" "c;dl;pthread;stdc++"