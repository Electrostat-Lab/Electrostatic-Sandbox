#!/bin/bash

source "./setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function download_avrdude() {
	download_package "${download_dir}" "${avrdude_url}" ""
}

function extract_avrdude() {
	zip_extract_package "${avrdude_provisional_path}" "${sandbox_path}"
}

function cleanup_avrdude() {
	rm --verbose "${download_dir}/${avrdude_zip_name}"
}

function create_avrdude_symbol() {
	create_sandbox_symbol "${sandbox_path}/${avrdude_zip_content}/avrdude" "${avrdude_symbol}"
}