#!/bin/bash

source "./helper-scripts/abstract/abstract-upload.sh"
source "./helper-scripts/project-impl/variables.sh"

ELF="${1}"
BUILD_DIR="${2}"
CHIP_ALIAS="${3}"
OPTIONS="${4}"

convert_to_hex "${ELF}" "${BUILD_DIR}"

upload "${PROGRAMMER}" "${BAUD_RATE}" "${PORT}" \
      "${CHIP_ALIAS}" "${ELF}" "${BUILD_DIR}" "${OPTIONS}"