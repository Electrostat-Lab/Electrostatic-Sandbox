#!/bin/bash

source "./setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function download_ndk() {
    download_package "${download_dir}" "${ndk_url}" ""
}

function extract_ndk() {
    zip_extract_package "${ndk_provisional_path}" "${sandbox_path}"
}

function cleanup_ndk() {
    rm --verbose "${download_dir}/${ndk_zip_name}"
}

function create_ndk_home_symbol() {
    create_sandbox_symbol "${sandbox_path}/${ndk_zip_content}" \
    "${android_ndk_home}"
}

function create_clang_symbols() {
    create_sandbox_symbol "${sandbox_path}/${ndk_zip_content}/toolchains/llvm/prebuilt/linux-x86_64/bin/clang" \
    "${clang_symbol}"

    create_sandbox_symbol "${sandbox_path}/${ndk_zip_content}/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++" \
    "${clangpp_symbol}"
}

function create_ndk_headers_symbol() {
    create_sandbox_symbol "${sandbox_path}/${ndk_zip_content}/prebuilts/ndk/headers" \
    "${android_ndk_headers}"
}