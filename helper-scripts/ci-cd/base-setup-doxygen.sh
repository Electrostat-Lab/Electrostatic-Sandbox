#!/bin/bash

source "$(pwd)/helper-scripts/setup-environment/setup-scripts/variables.sh"
source "${setup_doxygen_script}"

##
# Doxygen
##
install_doxygen_dependencies
download_doxygen
extract_doxygen
cleanup_doxygen

create_doxygen_symbol

doxygen-1.12.0 -v