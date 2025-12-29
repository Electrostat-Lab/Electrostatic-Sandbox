#!/bin/bash

source "./helper-scripts/abstract/abstract-doxygen-generator.sh"

generate_default_config "$(pwd)/sdk/docs/doxygen/" "DOC-CONFIG"

generate_docs "$(pwd)/sdk/docs/doxygen/" "DOC-CONFIG"

temp=$(pwd)

cd "./sdk/docs/"

dot -Tsvg -o electrostatic-sdk.svg "./electrostatic-sdk.dot"

cd "${temp}"
