#!/bin/bash

source "./Electrostatic-Sandbox/setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function download_gradle() {
	download_package "${download_dir}" "${gradle_url}" ""
}

function extract_gradle() {
	zip_extract_package "${gradle_provisional_path}" "${sandbox_path}"
}

function cleanup_gradle() {
	rm --verbose "${download_dir}/${gradle_zip_name}"
}

function create_gradle_symbol() {
	create_sandbox_symbol "${sandbox_path}/${gradle_zip_content}/bin/gradle" "${gradle_symbol}"
}