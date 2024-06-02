#!/bin/bash

source "./Electrostatic-Sandbox/setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function download_arduinoide() {
	download_package "${download_dir}" "${arduino_url}" ""
}

function extract_arduinoide() {
	tar_extract_package "${arduino_provisional_path}" "${sandbox_path}"
}

function cleanup_arduinoide() {
	rm --verbose "${download_dir}/${arduino_tar_name}"
}

function create_arduinoide_symbol() {
	create_sandbox_symbol "${sandbox_path}/${arduino_tar_content}/bin/arduino" "${arduino_symbol}"
}