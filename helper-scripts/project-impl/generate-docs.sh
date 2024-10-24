#!/bin/bash

source "./helper-scripts/abstract/abstract-doxygen-generator.sh"

generate_default_config "$(pwd)/electrostatic-sandbox-framework/docs/doxygen/" "DOC-CONFIG"

generate_docs "$(pwd)/electrostatic-sandbox-framework/docs/doxygen/" "DOC-CONFIG"