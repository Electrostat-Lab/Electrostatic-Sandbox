#!/bin/bash
source "./helper-scripts/project-impl/variables.sh"

LINK_DIR="android_ndk_home/sysroot/usr/lib/aarch64-linux-android/"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ARM_64}" "${NDK_TOOLCHAIN_INCLUDES}" \
        "${LINK_DIR}" "android" "${ARM_64}" "c;dl;pthread;stdc++"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ARM_32}" "${NDK_TOOLCHAIN_INCLUDES}" \
        "${LINK_DIR}" "android" "${ARM_32}" "c;dl;pthread;stdc++"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ANDROID_x86}" "${NDK_TOOLCHAIN_INCLUDES}" \
        "${LINK_DIR}" "android" "${ANDROID_x86}" "c;dl;pthread;stdc++"

./helper-scripts/project-impl/compile-electrostatic.sh \
        "${CLANG_BIN}" "${CLANGPP_BIN}" \
        "-target ${ANDROID_x86_64}" "${NDK_TOOLCHAIN_INCLUDES}" \
        "${LINK_DIR}" "android" "${ANDROID_x86_64}" "c;dl;pthread;stdc++"