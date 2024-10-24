#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

example="${1}"
executable_suffix="${2}"

./helper-scripts/project-impl/compile-examples.sh "${TARGET_x86_64}" \
    "${example}" "${executable_suffix}" "linux" "${x86_64}" "OFF"
#./helper-scripts/project-impl/compile-examples.sh "${TARGET_x86}" "${example}" "linux" "${x86}"

./electrostatic-sandbox-framework/electrostatic-examples/build/linux/x86-64/techdemo-${executable_suffix}-a.elf
#./electrostatic-examples/build/linux/x86/${example}.elf