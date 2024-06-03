#!/bin/bash

source "./Electrostatic-Sandbox/setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"
source "${setup_jdk_script}"
source "${setup_ide_script}"
source "${setup_gradle_script}"
source "${setup_cmake_script}"
source "${setup_avrdude_script}"
source "${setup_arduinoide_script}"

##
# Prepare the sandbox workspace
##
prepare_sandbox "${sandbox_path}" "+rwx" ""


##
# Setup JDK
##
download_jdk
extract_jdk
cleanup_jdk
create_java_symbol
setup_java_home

##
# Setup Gradle
##
download_gradle
extract_gradle
cleanup_gradle
create_gradle_symbol


##
# Setup CMake
##
download_cmake
extract_cmake
cleanup_cmake
create_cmake_symbol
install_gcc_multilib

##
# Setup AVRDude
##
download_avrdude
extract_avrdude
cleanup_avrdude
create_avrdude_symbol

##
# Setup arduino-ide
##
download_arduinoide
extract_arduinoide
cleanup_arduinoide
create_arduinoide_symbol

##
# Setup Jetbrains IDE
##
# download_ide
# extract_ide
# cleanup_ide
# create_ide_symbol


echo -e "${all_symbols_manual}"