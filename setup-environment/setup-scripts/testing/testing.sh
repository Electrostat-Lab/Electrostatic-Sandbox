#!/bin/sh

source "./Electrostatic-Sandbox/setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function test_preparation() {
	prepare_sandbox "${sandbox_path}" "+rwx" ""
}

function test_downloader() {
	download_package "${download_dir}" "${test_file_url}" ""
}

function test_extracting() {
	extract_package "${test_file_provisional_path}" "${sandbox_path}"
}

function test_creating_symbols() {
	create_sandbox_symbol "${sandbox_path}/${test_file_content}" "${test_file_symbol}"
}

function ping_package() {
	cat "${sandbox_path}/${test_file_content}"
}

function cleanup() {
	rm --verbose "${download_dir}/${test_file_name}"
}
