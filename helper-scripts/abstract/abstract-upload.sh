#!/bin/bash

function convert_to_hex() {
     local elf=${1}
     local directory=${2}

     temp=$(pwd)
     cd ${directory}
  	 avr-objcopy -O ihex ${elf} ${elf}'.hex'
  	 cd $temp

	 return $?
}

function upload() {
    local programmer=${1}
    local baud_rate=${2}
    local port=${3}
    local chip=${4}
    local flash_file=${5}
    local directory=${6}
    local options=${7}

    temp=$(pwd)
    cd ${directory}
	  sudo avrdude -c ${programmer} -b${baud_rate} -P${port} -p${chip} -U ${options} flash:w:${flash_file}
    cd $temp

	return $?
}