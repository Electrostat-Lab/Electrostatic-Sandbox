#!/bin/bash
source "./helper-scripts/project-impl/variables.sh"

PRIMER="${1}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ARM_64}" "${NDK_TOOLCHAIN_INCLUDES}" "android" "${ARM_64}" "${PRIMER}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ARM_32}" "${NDK_TOOLCHAIN_INCLUDES}" "android" "${ARM_32}" "${PRIMER}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ANDROID_x86}" "${NDK_TOOLCHAIN_INCLUDES}" "android" "${ANDROID_x86}" "${PRIMER}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ANDROID_x86_64}" "${NDK_TOOLCHAIN_INCLUDES}" "android" "${ANDROID_x86_64}" "${PRIMER}"
