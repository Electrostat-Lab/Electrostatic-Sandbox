#!/bin/bash

source "./Electrostatic-Sandbox/setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function download_ide() {
	download_package "${download_dir}" "${jetbrains_ide_url}" ""
}

function extract_ide() {
	tar_extract_package "${jetbrains_ide_provisional_path}" "${sandbox_path}"
}

function cleanup_ide() {
	rm --verbose "${download_dir}/${jetbrains_ide_name}"
}

function create_ide_symbol() {
	create_sandbox_symbol "${sandbox_path}/${jetbrains_ide_content}/bin/java" "${jetbrains_ide_symbol}"
}