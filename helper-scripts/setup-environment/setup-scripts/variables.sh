#!/bin/sh
working_dir=$(pwd)
root_path="${working_dir}/helper-scripts"
sandbox_path="/opt/electrostatic-sandbox"
local_bin="/usr/local/bin"
local_include="/usr/local/include"

unit_tests="${root_path}/setup-environment/setup-scripts/testing/testing.sh"
abstract_scripts="${root_path}/setup-environment/setup-scripts/abstract/setup-utils.sh"
setup_jdk_script="${root_path}/setup-environment/setup-scripts/tools/setup-jdk.sh"
setup_arduinoide_script="${root_path}/setup-environment/setup-scripts/tools/setup-arduinoide.sh"
setup_ide_script="${root_path}/setup-environment/setup-scripts/tools/setup-ide.sh"
setup_gradle_script="${root_path}/setup-environment/setup-scripts/tools/setup-gradle.sh"
setup_cmake_script="${root_path}/setup-environment/setup-scripts/tools/setup-cmake.sh"
setup_avrdude_script="${root_path}/setup-environment/setup-scripts/tools/setup-avrdude.sh"
setup_android_ndk_script="${root_path}/setup-environment/setup-scripts/tools/setup-android-ndk.sh"
setup_avr_toolchains_script="${root_path}/setup-environment/setup-scripts/tools/setup-avr-toolchains.sh"
setup_doxygen_script="${root_path}/setup-environment/setup-scripts/tools/setup-doxygen.sh"
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
java_headers="${local_include}/java-20.0.2-headers"
jdk_provisional_path="${download_dir}/${jdk_tar_name}"


##
# Gradle 8.3
##
gradle_url="https://services.gradle.org/distributions/gradle-8.3-all.zip"
gradle_zip_name="gradle-8.3-all.zip"
gradle_zip_content="gradle-8.3"
gradle_symbol="${local_bin}/gradle"
gradle_provisional_path="${download_dir}/${gradle_zip_name}"

##
# CMake 3.19.6
##
cmake_url="https://github.com/Kitware/CMake/releases/download/v3.19.6/cmake-3.19.6-Linux-x86_64.tar.gz"
cmake_tar_name="cmake-3.19.6-Linux-x86_64.tar.gz"
cmake_tar_content="cmake-3.19.6-Linux-x86_64"
cmake_symbol="${local_bin}/cmake-3.19"
cmake_provisional_path="${download_dir}/${cmake_tar_name}"
posix_headers_symbol="${local_include}/posix-headers"

##
# Android NDK
##
ndk_url="https://dl.google.com/android/repository/android-ndk-r27c-linux.zip"
ndk_zip_name="android-ndk-r27c-linux.zip"
ndk_zip_content="android-ndk-r27c"
clang_symbol="${local_bin}/android-clang"
clangpp_symbol="${local_bin}/android-clang++"
android_ndk_headers="${local_include}/android-ndk-headers"
ndk_provisional_path="${download_dir}/${ndk_zip_name}"

##
# Avr toolchains
##
avr_url="https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/avr8-gnu-toolchain-3.7.0.1796-linux.any.x86_64.tar.gz"
avr_zip_name="avr8-gnu-toolchain-3.7.0.1796-linux.any.x86_64.tar.gz"
avr_zip_content="avr8-gnu-toolchain-linux_x86_64"
avrgcc_symbol="${local_bin}/avr-gcc"
avrgpp_symbol="${local_bin}/avr-g++"
avrobjcopy_symbol="${local_bin}/avr-objcopy"
avrheaders_symbol="${local_bin}/avr-headers"
avr_provisional_path="${download_dir}/${avr_zip_name}"

##
# AVRDude
##
avrdude_url="https://github.com/avrdudes/avrdude/releases/download/v7.3/avrdude-v7.3-linux_x64.zip"
avrdude_zip_name="avrdude-v7.3-linux_x64.zip"
avrdude_zip_content="avrdude_linux_x64"
avrdude_symbol="${local_bin}/avrdude"
avrdude_provisional_path="${download_dir}/${avrdude_zip_name}"


##
# Doxygen
##
doxygen_url="https://github.com/doxygen/doxygen/releases/download/Release_1_12_0/doxygen-1.12.0.linux.bin.tar.gz"
doxygen_tar_name="doxygen-1.12.0.linux.bin.tar.gz"
doxygen_tar_content="doxygen-1.12.0"
doxygen_symbol="${local_bin}/doxygen-1.12.0"
doxygen_provisional_path="${download_dir}/${doxygen_tar_name}"


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
