#!/bin/bash

function compile() {
    local GCC_BIN=${1}
    local GPP_BIN=${2}
    local BUILD_SHARED=${3}
    local INPUT_COMPILER_OPTIONS=${4}
    local TARGET=${5}
    local TOOLCHAIN_INCLUDES=${6}
    local ELECTROSTATIC_CORE=${7}
    local EXAMPLE=${8}
    local EXECUTABLE_SUFFIX=${9}
    local BUILD_DIR=${10}
    local SOURCE_DIR=${11}
    
    local TEMP=$(pwd)
    cd ${SOURCE_DIR}
    
    cmake-3.19 "-DGCC_BIN=${GCC_BIN}" \
               "-DGPP_BIN=${GPP_BIN}" \
               "-DBUILD_SHARED=${BUILD_SHARED}" \
               "-DINPUT_COMPILER_OPTIONS=${INPUT_COMPILER_OPTIONS}" \
               "-DTARGET=${TARGET}" \
               "-DTOOLCHAIN_INCLUDES=${TOOLCHAIN_INCLUDES}" \
               "-DELECTROSTATIC_CORE=${ELECTROSTATIC_CORE}" \
               "-DEXAMPLE=${EXAMPLE}" \
               "-DEXECUTABLE_SUFFIX=${EXECUTABLE_SUFFIX}" \
               "-DBUILD_DIR=${BUILD_DIR}" \
               -S . -B "$(pwd)/build/${BUILD_DIR}"
          
    cmake-3.19 --build "$(pwd)/build/${BUILD_DIR}"
    cd ${TEMP}
}

