#!/bin/bash

PRIMER="${1}"

./helper-scripts/project-impl/compile-all.sh "${PRIMER}"
./helper-scripts/project-impl/compile-all-android.sh "${PRIMER}"
