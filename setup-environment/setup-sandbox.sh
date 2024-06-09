#!/bin/bash

source "$(pwd)/setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"
source "${setup_jdk_script}"
source "${setup_ide_script}"
source "${setup_gradle_script}"
source "${setup_cmake_script}"
source "${setup_avrdude_script}"
source "${setup_arduinoide_script}"
source "${setup_android_ndk_script}"

##
# Prepare the sandbox workspace
##
prepare_sandbox "${sandbox_path}" "+rwx" ""

###
## Setup JDK
###
#download_jdk
#extract_jdk
#cleanup_jdk
#create_java_symbol
#setup_java_home
#
###
## Setup Gradle
###
#download_gradle
#extract_gradle
#cleanup_gradle
#create_gradle_symbol
#
#ls -l "${download_dir}"
#
#
###
## Setup CMake
###
#download_cmake
#extract_cmake
#cleanup_cmake
#create_cmake_symbol
#create_posix_headers_symbol
#install_gcc_multilib
#
#ls -l "${download_dir}"
#
###
## Setup AVRDude
###
#download_avrdude
#extract_avrdude
#cleanup_avrdude
#create_avrdude_symbol
#
#ls -l "${download_dir}"
#
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
unzip -q "${ndk_zip_name}"
ls -l "${download_dir}"

#cleanup_ndk
#create_clang_symbols
#create_ndk_headers_symbol


##
# Setup Jetbrains IDE
##
# download_ide
# extract_ide
# cleanup_ide
# create_ide_symbol
#
#all_symbols_manual="============================== \n
#        		    Sybmolic Links: \n
#                    ${java_symbol} => `${java_symbol} --version` \n
#                    ${gradle_symbol} => `${gradle_symbol} --version` \n
#                    ${jetbrains_ide_symbol} `${jetbrains_ide_symbol} --version` \n
#                    ${cmake_symbol} => `${cmake_symbol} --version` \n
#                    ${arduinoide_symbol} => `${arduinoide_symbol} --version` \n
#                    $(`android-clang`) \n
#                    $(`android-clang++`) \n
#                    $(`android-ndk-headers`) \n
#                    =============================="
#
#echo -e "${all_symbols_manual}"