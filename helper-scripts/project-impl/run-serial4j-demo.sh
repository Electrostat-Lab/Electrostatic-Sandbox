#!/bin/bash
source "./helper-scripts/common-variables.sh"
source "./helper-scripts/project-impl/variables.sh"

serial4j_examples=":sdk:electrostatic4j:serial4j:serial4j-examples"

demo="${1}"

./gradlew "${serial4j_examples}":run --args="${demo}"
