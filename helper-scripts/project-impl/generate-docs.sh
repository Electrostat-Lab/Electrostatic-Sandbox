#!/bin/bash

source "./helper-scripts/abstract/abstract-doxygen-generator.sh"

generate_default_config "$(pwd)/electrostatic-sandbox-framework/docs/doxygen/" "DOC-CONFIG"

generate_docs "$(pwd)/electrostatic-sandbox-framework/docs/doxygen/" "DOC-CONFIG"

temp=$(pwd)

cd "./electrostatic-sandbox-framework/docs/"

dot -Tsvg -o electrostatic-sdk.svg "./electrostatic-sdk.dot"

cd "${temp}"
