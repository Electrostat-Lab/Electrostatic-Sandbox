#!/bin/bash

source "./setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function download_jdk() {
	download_package "${download_dir}" "${jdk_url}" ""
}

function extract_jdk() {
	tar_extract_package "${jdk_provisional_path}" "${sandbox_path}"
}

function cleanup_jdk() {
	rm --verbose "${download_dir}/${jdk_tar_name}"
}

function create_java_symbol() {
	create_sandbox_symbol "${sandbox_path}/${jdk_tar_content}/bin/java" "${java_symbol}"
	create_sandbox_symbol "${sandbox_path}/${jdk_tar_content}/include" "${java_headers}"
}

function setup_java_home() {
	export ${JAVA_HOME}="${sandbox_path}/${jdk_tar_content}/bin"
}