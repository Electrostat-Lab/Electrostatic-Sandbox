#!/bin/bash

demo="${1}"

temp=$(pwd)

cd ./electrostatic4j/

./gradlew :serial4j:serial4j-examples:run --args="${demo}"

cd $temp
