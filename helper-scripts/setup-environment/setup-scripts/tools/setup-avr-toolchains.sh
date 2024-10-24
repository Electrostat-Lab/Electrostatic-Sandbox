#!/bin/bash

source "./helper-scripts/setup-environment/setup-scripts/variables.sh"
source "${abstract_scripts}"

function download_avr() {
    download_package "${download_dir}" "${avr_url}" ""
}

function extract_avr() {
    tar_extract_package "${avr_provisional_path}" "${sandbox_path}"
}

function cleanup_avr() {
    rm --verbose "${download_dir}/${avr_zip_name}"
}

function create_avr_symbols() {
    create_sandbox_symbol "${sandbox_path}/${avr_zip_content}/bin/avr-gcc" \
    "${avrgcc_symbol}"

    create_sandbox_symbol "${sandbox_path}/${avr_zip_content}/bin/avr-g++" \
    "${avrgpp_symbol}"

    create_sandbox_symbol "${sandbox_path}/${avr_zip_content}/bin/avr-objcopy" \
    "${avrobjcopy_symbol}"
}

function create_avr_headers_symbol() {
    create_sandbox_symbol "${sandbox_path}/${avr_zip_content}/avr/include" \
    "${avrheaders_symbol}"
}