#!/bin/bash

source "./setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function download_arduinoide() {
	download_package "${download_dir}" "${arduinoide_url}" ""
}

function extract_arduinoide() {
	tar_extract_package "${arduinoide_provisional_path}" "${sandbox_path}"
}

function cleanup_arduinoide() {
	rm --verbose "${download_dir}/${arduinoide_tar_name}"
}

function create_arduinoide_symbol() {
	create_sandbox_symbol "${sandbox_path}/${arduinoide_tar_content}/bin/arduino" "${arduinoide_symbol}"
}
