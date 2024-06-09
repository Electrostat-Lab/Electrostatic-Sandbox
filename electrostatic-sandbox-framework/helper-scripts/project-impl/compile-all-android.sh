#!/bin/bash
source "./helper-scripts/project-impl/variables.sh"

./helper-scripts/project-impl/compile-android.sh "${ARM_64}"
./helper-scripts/project-impl/compile-android.sh "${ARM_32}"
./helper-scripts/project-impl/compile-android.sh "${x86}"
./helper-scripts/project-impl/compile-android.sh "${x86_64}"