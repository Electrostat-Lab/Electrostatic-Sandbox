#!/bin/bash

former_working_dir="`pwd`"

##
# The root directory specified as a command parameter.
##
root="${1}"

cd "${root}"

working_dir="`pwd`"

source "${working_dir}/Electrostatic-Sandbox/setup-environment/setup-scripts/variables.sh"
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

##
# exit
##
cd "${former_working_dir}"
