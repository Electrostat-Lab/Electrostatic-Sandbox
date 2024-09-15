#!/bin/bash

working_dir="$(pwd)"

source "${working_dir}/Electrostatic-Sandbox/helper-scripts/setup-environment/setup-scripts/variables.sh"
source "${unit_tests}"

##
# Run tests on dummy files and then cleanup.
##
function run_tests() {
	test_preparation
	test_downloader
	test_extracting
	test_creating_symbols
	cleanup
}

run_tests
ping_package
