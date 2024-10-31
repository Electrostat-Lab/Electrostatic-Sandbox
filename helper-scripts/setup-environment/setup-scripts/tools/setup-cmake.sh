#!/bin/bash

source "./helper-scripts/setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function download_cmake() {
	download_package "${download_dir}" "${cmake_url}" ""
}

function extract_cmake() {
	tar_extract_package "${cmake_provisional_path}" "${sandbox_path}"
}

function cleanup_cmake() {
	rm --verbose "${download_dir}/${cmake_tar_name}"
}

function create_cmake_symbol() {
	create_sandbox_symbol "${sandbox_path}/${cmake_tar_content}/bin/cmake" "${cmake_symbol}"
}

function create_posix_headers_symbol() {
	create_sandbox_symbol "/usr/include" "${posix_headers_symbol}"
}

function install_gcc_multilib() {
	sudo apt-get install gcc-multilib
	sudo apt-get install g++-multilib
}