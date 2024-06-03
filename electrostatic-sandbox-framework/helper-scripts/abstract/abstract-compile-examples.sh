#!/bin/bash

function compile() {
    local TOOLCHAIN_HOME=${1}
    local TARGET=${2}
    local source_dir=${3}
    local FOOBAR_LIB=${4}
    local EXAMPLE=${5}
    
    local temp=$(pwd)
    cd ${source_dir}
    
    cmake-3.19 "-DTOOLCHAIN_HOME=${TOOLCHAIN_HOME}" \
          "-DTARGET=${TARGET}" \
          "-DFOO_BAR=${FOOBAR_LIB}" \
          "-DEXAMPLE=${EXAMPLE}" \
          -S . -B "./build/${TARGET}"
          
    cmake --build "./build/${TARGET}"
    cd ${temp}
}

