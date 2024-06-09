#!/bin/bash
source "./helper-scripts/project-impl/variables.sh"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ARM_64} -ldl -lc" "${NDK_TOOLCHAIN_INCLUDES}" "android" "${ARM_64}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ARM_32} -ldl -lc" "${NDK_TOOLCHAIN_INCLUDES}" "android" "${ARM_32}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ANDROID_x86} -ldl -lc" "${NDK_TOOLCHAIN_INCLUDES}" "android" "${ANDROID_x86}"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ANDROID_x86_64} -ldl -lc" "${NDK_TOOLCHAIN_INCLUDES}" "android" "${ANDROID_x86_64}"