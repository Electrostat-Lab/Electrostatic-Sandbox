#!/bin/bash

function compile() {
    local GCC_BIN=${1}
    local GPP_BIN=${2}
    local INPUT_COMPILER_OPTIONS=${3}
    local TARGET=${4}
    local TOOLCHAIN_INCLUDES=${5}
    local JAVA_HOME=${6}
    local ELECTROSTATIC_CORE=${7}
    local BUILD_DIR=${8}
    local SOURCE_DIR=${9}
    
    local TEMP=$(pwd)
    cd ${SOURCE_DIR}
    
    cmake-3.19 "-DGCC_BIN=${GCC_BIN}" \
            "-DGPP_BIN=${GPP_BIN}" \
            "-DINPUT_COMPILER_OPTIONS=${INPUT_COMPILER_OPTIONS}" \
            "-DTARGET=${TARGET}" \
            "-DTOOLCHAIN_INCLUDES=${TOOLCHAIN_INCLUDES}" \
            "-DJAVA_HOME=${JAVA_HOME}" \
            "-DELECTROSTATIC_CORE=${ELECTROSTATIC_CORE}" \
            "-DBUILD_DIR=${BUILD_DIR}" \
            -S . -B "./cmake-build/${BUILD_DIR}"
        
    cmake --build "./cmake-build/${BUILD_DIR}"
    cd ${TEMP}
}

