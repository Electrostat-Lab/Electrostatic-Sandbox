#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

./helper-scripts/project-impl/compile-x86.sh "${m64}"
./helper-scripts/project-impl/compile-x86.sh "${m32}"
