#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

example="${1}"
executable_suffix="${2}"
target="${3}"
chip_alias=${4}
build_dir="${5}"

./helper-scripts/project-impl/compile-examples-mcu.sh "-mmcu=${target}" \
    "${example}" "${executable_suffix}" "${build_dir}" "${target}" "OFF"

root_build_path="$(pwd)/electrostatic-sandbox-framework/electrostatic-examples"

./helper-scripts/project-impl/upload-hex.sh "techdemo-${executable_suffix}-a.elf" \
    "${root_build_path}/build/${build_dir}/${target}" "${chip_alias}" ""