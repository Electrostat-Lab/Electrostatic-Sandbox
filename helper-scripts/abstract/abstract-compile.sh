#!/bin/bash

function compile() {
    local COMMISSION_LIB=${1}
    local GCC_BIN=${2}
    local GPP_BIN=${3}
    local BUILD_SHARED=${4}
    local INPUT_COMPILER_OPTIONS=${5}
    local TARGET=${6}
    local TOOLCHAIN_HEADERS=${7}
    local BUILD_DIR=${8}
    local CMAKE_DIR=${9}
    local SOURCES_DIR=${10}
    local PROJECT_SOURCES=${11}
    local DEPENDENCIES=${12}
    
    local TEMP=$(pwd)

    cd ${CMAKE_DIR}

    cmake-3.19 "-DCOMMISSION_LIB=${COMMISSION_LIB}" \
          "-DGCC_BIN=${GCC_BIN}" \
          "-DGPP_BIN=${GPP_BIN}" \
          "-DBUILD_SHARED=${BUILD_SHARED}" \
          "-DINPUT_COMPILER_OPTIONS=${INPUT_COMPILER_OPTIONS}" \
          "-DTARGET=${TARGET}" \
          "-DTOOLCHAIN_HEADERS=${TOOLCHAIN_HEADERS}" \
          "-DBUILD_DIR=${BUILD_DIR}" \
          "-DSOURCES_DIR=${SOURCES_DIR}" \
          "-DPROJECT_SOURCES=${PROJECT_SOURCES}" \
          "-DDEPENDENCIES=${DEPENDENCIES}" \
          -S . -B "$(pwd)/${SOURCES_DIR}/cmake-build/${BUILD_DIR}"

    cmake-3.19 --build "$(pwd)/${SOURCES_DIR}/cmake-build/${BUILD_DIR}"
    cd ${TEMP}
}

