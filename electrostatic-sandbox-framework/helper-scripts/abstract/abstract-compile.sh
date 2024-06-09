#!/bin/bash

function compile() {
    local COMMISSION_LIB=${1}
    local GCC_BIN=${2}
    local GPP_BIN=${3}
    local INPUT_COMPILER_OPTIONS=${4}
    local TARGET=${5}
    local TOOLCHAIN_HEADERS=${6}
    local BUILD_DIR=${7}
    local CMAKE_DIR=${8}
    local SOURCES_DIR=${9}
    local PROJECT_SOURCES=${10}
    local DEPENDENCIES=${11}
    
    local TEMP=$(pwd)

    cd ${CMAKE_DIR}

    cmake-3.19 "-DCOMMISSION_LIB=${COMMISSION_LIB}" \
          "-DGCC_BIN=${GCC_BIN}" \
          "-DGPP_BIN=${GPP_BIN}" \
          "-DINPUT_COMPILER_OPTIONS=${INPUT_COMPILER_OPTIONS}" \
          "-DTARGET=${TARGET}" \
          "-DTOOLCHAIN_HEADERS=${TOOLCHAIN_HEADERS}" \
          "-DBUILD_DIR=${BUILD_DIR}" \
          "-DSOURCES_DIR=${SOURCES_DIR}" \
          "-DPROJECT_SOURCES=${PROJECT_SOURCES}" \
          "-DDEPENDENCIES=${DEPENDENCIES}" \
          -S . -B "./${SOURCES_DIR}/cmake-build/${BUILD_DIR}"

    cmake --build "./${SOURCES_DIR}/cmake-build/${BUILD_DIR}"
    cd ${TEMP}
}

