#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

example="${1}"
exe="${2}"

./helper-scripts/project-impl/compile-examples.sh "${TARGET_x86_64}" \
    "${example}" "${exe}" "linux" "${x86_64}"

./sdk/examples/cmake-build/linux/x86-64/${exe}.elf
