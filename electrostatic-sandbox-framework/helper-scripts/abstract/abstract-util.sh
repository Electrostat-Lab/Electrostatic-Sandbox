#!/bin/bash

system="NULL"
ext="NULL"

function getCurrentSystem() {
    if [[ `uname` == "Darwin" ]]; then 
        system="macos"
    elif [[ `uname` == "Linux" ]]; then 
        system="linux"
    else
        system="windows"
    fi 
    return $?
}

function assignBinaryExtension() {
    getCurrentSystem
    if [[ $system == "macos" ]]; then 
        ext=".dylib"
    elif [[ $system == "linux" ]]; then 
        ext=".so"
    else 
        ext=".dll"
    fi
}

function moveFile() {
    local source=$1
    local dest=$2

    if [[ ! -e ${dest} ]]; then
        mkdir -p ${dest}
    fi
    mv --verbose "${source}" "${dest}"
}
