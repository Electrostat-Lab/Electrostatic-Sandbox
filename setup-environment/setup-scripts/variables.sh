#!/bin/sh
working_dir=$(pwd)
root_path="${working_dir}"
sandbox_path="/opt/electrostatic-sandbox"
local_bin="/usr/local/bin"

unit_tests="${root_path}/setup-environment/setup-scripts/testing/testing.sh"
abstract_scripts="${root_path}/setup-environment/setup-scripts/abstract/setup-utils.sh"
setup_jdk_script="${root_path}/setup-environment/setup-scripts/tools/setup-jdk.sh"
setup_arduinoide_script="${root_path}/setup-environment/setup-scripts/tools/setup-arduinoide.sh"
setup_ide_script="${root_path}/setup-environment/setup-scripts/tools/setup-ide.sh"
setup_gradle_script="${root_path}/setup-environment/setup-scripts/tools/setup-gradle.sh"
setup_cmake_script="${root_path}/setup-environment/setup-scripts/tools/setup-cmake.sh"
setup_avrdude_script="${root_path}/setup-environment/setup-scripts/tools/setup-avrdude.sh"
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
java_symbol="${local_bin}/java-20.0.2"
jdk_provisional_path="${download_dir}/${jdk_tar_name}"


##
# Gradle 8.3
##
gradle_url="https://services.gradle.org/distributions/gradle-8.3-all.zip"
gradle_zip_name="gradle-8.3-all.zip"
gradle_zip_content="*"
gradle_symbol="gradle-8.3"
gradle_provisional_path="${download_dir}/${gradle_zip_name}"

##
# CMake 3.19.6
##
cmake_url="https://github.com/Kitware/CMake/releases/download/v3.19.6/cmake-3.19.6-Linux-x86_64.tar.gz"
cmake_tar_name="cmake-3.19.6-Linux-x86_64.tar.gz"
cmake_tar_content="cmake-3.19.6-Linux-x86_64"
cmake_symbol="${local_bin}/cmake-3.19"
cmake_provisional_path="${download_dir}/${cmake_tar_name}"

##
# AVRDude
##
avrdude_url="https://github.com/avrdudes/avrdude/releases/download/v7.3/avrdude-v7.3-linux_x64.zip"
avrdude_zip_name="avrdude-v7.3-linux_x64.zip"
avrdude_zip_content="avrdude_linux_x64"
avrdude_symbol="${local_bin}/avrdude"
avrdude_provisional_path="${download_dir}/${avrdude_zip_name}"

##
# Arduino-ide
##
arduinoide_url="https://downloads.arduino.cc/arduino-1.8.19-linux64.tar.xz"
arduinoide_tar_name="arduino-1.8.19-linux64.tar.xz"
arduinoide_tar_content="*"
arduinoide_symbol="${local_bin}/arduino-ide"
arduinoide_provisional_path="${download_dir}/${arduinoide_tar_name}"

##
# Jetbrains IDE
##
jetbrains_ide_url="https://www.jetbrains.com/fleet/download/download-thanks.html?platform=linux"
jetbrains_ide_name=""
jetbrains_ide_content=""
jetbrains_ide_symbol=""
jetbrains_ide_provisional_path=""

jetbrains_idea_url="https://www.jetbrains.com/idea/download/download-thanks.html?platform=linux&code=IIC"
jetbrains_idea_name="idea*.tar.gz"
jetbrains_idea_content="idea*"
jetbrains_idea_symbol="jetbrains-idea"
jetbrains_idea_provisional_path="${download_dir}/${jetbrains_idea_name}"
