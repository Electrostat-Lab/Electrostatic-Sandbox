#!/bin/bash

source "$(pwd)/helper-scripts/setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"
source "${setup_jdk_script}"
source "${setup_ide_script}"
source "${setup_gradle_script}"
source "${setup_cmake_script}"
source "${setup_avrdude_script}"
source "${setup_arduinoide_script}"
source "${setup_android_ndk_script}"
source "${setup_avr_toolchains_script}"

##
# Downloading prerequisite binaries
##
echo "Downloading missing binaries"
# typically for WSL machines
sudo apt-get install make
sudo apt-get install usbutils
sudo apt-get install xorg
sudo apt-get install libopenal-dev
sudo apt-get install pulseaudio
sudo apt-get install gcc
sudo apt-get install g++

##
# Prepare the sandbox workspace
##
prepare_sandbox "${sandbox_path}" "+rwx" ""

###
## Setup JDK
###
download_jdk
extract_jdk
cleanup_jdk


###
## Setup Gradle
###
download_gradle
extract_gradle
cleanup_gradle

#
###
## Setup CMake
###
download_cmake
extract_cmake
cleanup_cmake


###
## Setup AVRDude
####
download_avrdude
extract_avrdude
cleanup_avrdude

##
# Setup AVRDude
###
download_avr
extract_avr
cleanup_avr

###
## Setup arduino-ide
###
#download_arduinoide
#extract_arduinoide
#cleanup_arduinoide
#create_arduinoide_symbol
#
#ls -l "${download_dir}"

download_ndk
extract_ndk
cleanup_ndk

##
# Setup Jetbrains IDE
##
# download_ide
# extract_ide
# cleanup_ide
# create_ide_symbol

source "$(pwd)/helper-scripts/setup-environment/create-symbols.sh"
source "$(pwd)/helper-scripts/setup-environment/add-user-to-serial-groups.sh"