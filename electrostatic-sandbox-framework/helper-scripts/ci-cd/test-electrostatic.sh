#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

example="${1}"

./helper-scripts/project-impl/compile-examples.sh "${TARGET_x86_64}" "${example}" "linux" "${x86_64}"
./helper-scripts/project-impl/compile-examples.sh "${TARGET_x86}" "${example}" "linux" "${x86}"

./electrostatic-examples/build/linux/x86-64/${example}.elf
./electrostatic-examples/build/linux/x86/${example}.elf