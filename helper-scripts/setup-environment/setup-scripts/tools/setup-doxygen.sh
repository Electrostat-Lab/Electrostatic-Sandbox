#!/bin/bash

source "./helper-scripts/setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function download_doxygen() {
	download_package "${download_dir}" "${doxygen_url}" ""
}

function extract_doxygen() {
	tar_extract_package "${doxygen_provisional_path}" "${sandbox_path}"
}

function cleanup_doxygen() {
	rm --verbose "${download_dir}/${doxygen_tar_name}"
}

function create_doxygen_symbol() {
	create_sandbox_symbol "${sandbox_path}/${doxygen_tar_content}/bin/doxygen" "${doxygen_symbol}"
}

function install_doxygen_dependencies() {
	sudo apt-get install graphviz
}