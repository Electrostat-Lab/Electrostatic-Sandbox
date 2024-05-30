#!/bin/sh
working_dir="`pwd`"
root_path="${working_dir}/Electrostatic-Sandbox"
sandbox_path="/opt/electrostatic-sandbox"
local_bin="/usr/local/bin"

unit_tests="${root_path}/setup-environment/setup-scripts/testing/testing.sh"
abstract_scripts="${root_path}/setup-environment/setup-scripts/abstract/setup-utils.sh"
download_dir="${HOME}/Downloads"

##
# Test files
##
test_file_url="https://github.com/Electrostat-Lab/Electrostatic-Sandbox/releases/download/TEST-FILE/TESTING.tar.xz"
test_file_name="TESTING.tar.xz"
test_file_content="TESTING.txt"
test_file_symbol="${local_bin}/ping-test"
test_file_provisional_path="${download_dir}/${test_file_name}"

##
# Oracle JDK
##
jdk_url="https://download.oracle.com/java/20/archive/jdk-20.0.2_linux-x64_bin.tar.gz"
jdk_tar_name="jdk-20.0.2_linux-x64_bin.tar.gz"
jdk_tar_content="jdk-20.0.2"
java_symbol="java-20.0.2"
jdk_provisional_path="${download_dir}/${jdk_tar_name}"


