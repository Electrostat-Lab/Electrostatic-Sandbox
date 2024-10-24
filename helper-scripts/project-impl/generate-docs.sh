#!/bin/bash

source "./helper-scripts/abstract/abstract-doxygen-generator.sh"

sudo apt install graphviz
sudo apt install doxygen

generate_default_config "$(pwd)/electrostatic-sandbox-framework/docs/doxygen/" "DOC-CONFIG"

generate_docs "$(pwd)/electrostatic-sandbox-framework/docs/doxygen/" "DOC-CONFIG"
