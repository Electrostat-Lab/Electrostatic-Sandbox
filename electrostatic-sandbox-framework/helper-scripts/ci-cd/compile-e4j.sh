#!/bin/bash
source "./common-variables.sh"
cd ./electrostatic4j

echo -e "${ORANGE_C} Compiling and Assembling e4j-core"
./gradlew :electrostatic4j-core:build \
          :electrostatic4j-core:generateSourcesJar \
          :electrostatic4j-core:generateJavadocJar 

echo -e "${ORANGE_C} Compiling e4j-native"
./gradlew :electrostatic4j-native:compileX86 \
          :electrostatic4j-native:compileX86_64 && \
          ./gradlew :electrostatic4j-native:copyBinaries && \
          ./gradlew :electrostatic4j-native:build \
          :electrostatic4j-native:copyToExamples

echo -e "${ORANGE_C} Building Examples"
./gradlew :electrostatic4j-examples:build

