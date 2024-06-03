#!/bin/bash

function compile() {
    local GCC_BIN=${1}
    local GPP_BIN=${2}
    local INPUT_COMPILER_OPTIONS=${3}
    local TOOLCHAIN_INCLUDES=${4}
    local TARGET=${5}
    local source_dir=${6}
    
    local temp=$(pwd)

    cd ${source_dir}

    cmake-3.19 "-DGCC_BIN=${GCC_BIN}" \
          "-DGPP_BIN=${GPP_BIN}" \
          "-DINPUT_COMPILER_OPTIONS=${INPUT_COMPILER_OPTIONS}" \
          "-DTOOLCHAIN_INCLUDES=${TOOLCHAIN_INCLUDES}" \
          "-DTARGET=-${TARGET}" \
          -S . -B "./build/${TARGET}"

    cmake --build "./build/${TARGET}"
    cd ${temp}
}

