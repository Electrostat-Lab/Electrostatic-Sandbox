#!/bin/bash

source "./helper-scripts/project-impl/variables.sh"

./helper-scripts/project-impl/compile-examples.sh "${TARGET_x86_64}" "hello_comm.c" "${x86_64}"
./helper-scripts/project-impl/compile-examples.sh "${TARGET_x86}" "hello_comm.c" "${x86}"

./electrostatic-examples/build/x86-64/hello_comm.c.elf
./electrostatic-examples/build/x86/hello_comm.c.elf