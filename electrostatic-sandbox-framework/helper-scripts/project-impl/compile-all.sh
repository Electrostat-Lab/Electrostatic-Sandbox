#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

./helper-scripts/project-impl/compile-electrostatic.sh "${TARGET_x86_64}" "${TOOLCHAIN_INCLUDES}" "${x86_64}"
./helper-scripts/project-impl/compile-electrostatic.sh "${TARGET_x86}" "${TOOLCHAIN_INCLUDES}" "${x86}"
