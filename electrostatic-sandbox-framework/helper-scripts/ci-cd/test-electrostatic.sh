#!/bin/bash

./helper-scripts/project-impl/compile-examples.sh "x86-64" "hello_comm.c"
./helper-scripts/project-impl/compile-examples.sh "x86" "hello_comm.c"
./electrostatic-examples/build/x86-64/hello_comm.c.elf
./electrostatic-examples/build/x86/hello_comm.c.elf