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

create_java_symbol
setup_java_home

create_gradle_symbol

create_cmake_symbol
create_posix_headers_symbol
install_gcc_multilib

create_avrdude_symbol
create_avr_symbols
create_avr_headers_symbol

create_clang_symbols
create_ndk_headers_symbol


all_symbols_manual="============================== \n
        		    Sybmolic Links: \n
                    ${java_symbol} => `${java_symbol} --version` \n
                    ${gradle_symbol} => `${gradle_symbol} --version` \n
                    ${jetbrains_ide_symbol} `${jetbrains_ide_symbol} --version` \n
                    ${cmake_symbol} => `${cmake_symbol} --version` \n
                    ${arduinoide_symbol} => `${arduinoide_symbol} --version` \n
                    $(avr-gcc --version) \n
                    $(avr-g++ --version) \n
                    $(android-clang --version) \n
                    $(android-clang++ --version) \n
                    $(android-ndk-headers) \n
                    =============================="

echo -e "${all_symbols_manual}"