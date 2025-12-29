#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

example="${1}"
executable="${2}"
target="${3}"
chip_alias=${4}
build_dir="${5}"

./helper-scripts/project-impl/compile-examples-mcu.sh "-mmcu=${target}" \
    "${example}" "${executable}" "${build_dir}" "${target}" "OFF"

root_build_path="$(pwd)/sdk/examples"

./helper-scripts/project-impl/upload-hex.sh "${executable}.elf" \
    "${root_build_path}/cmake-build/${build_dir}/${target}" "${chip_alias}" ""