#!/bin/bash

function compile() {
    local COMMISSION_OUTPUT=${1}
    local GCC_BIN=${2}
    local GPP_BIN=${3}
    local BUILD_STATIC=${4}
    local BUILD_SHARED=${5}
    local BUILD_EXE=${6}
    local INPUT_COMPILER_OPTIONS=${7}
    local TARGET=${8}
    local HEADERS=${9}
    local SOURCES_DIR=${10}
    local PROJECT_SOURCES=${11}
    local DEPENDENCIES=${12}
    local BUILD_DIR=${13}
    local CMAKE_DIR=${14}

    local TEMP=$(pwd)

    cd "${CMAKE_DIR}" || exit $?

    cmake-3.19 "-DCOMMISSION_OUTPUT=${COMMISSION_OUTPUT}" \
          "-DGCC_BIN=${GCC_BIN}" \
          "-DGPP_BIN=${GPP_BIN}" \
          "-DBUILD_STATIC=${BUILD_STATIC}" \
          "-DBUILD_SHARED=${BUILD_SHARED}" \
          "-DBUILD_EXE=${BUILD_EXE}" \
          "-DINPUT_COMPILER_OPTIONS=${INPUT_COMPILER_OPTIONS}" \
          "-DTARGET=${TARGET}" \
          "-DHEADERS=${HEADERS}" \
          "-DSOURCES_DIR=${SOURCES_DIR}" \
          "-DPROJECT_SOURCES=${PROJECT_SOURCES}" \
          "-DDEPENDENCIES=${DEPENDENCIES}" \
          "-DBUILD_DIR=${BUILD_DIR}" \
          -S . -B "$(pwd)/${SOURCES_DIR}/cmake-build/${BUILD_DIR}"

    cmake-3.19 --build "$(pwd)/${SOURCES_DIR}/cmake-build/${BUILD_DIR}" || exit $?

    cd "${TEMP}" || exit $?
}

