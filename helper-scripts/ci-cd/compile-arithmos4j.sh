#!/bin/bash
source "./helper-scripts/common-variables.sh"
source "./helper-scripts/project-impl/variables.sh"

arithmos4j_core=":sdk:electrostatic4j:arithmos4j:arithmos4j-core"
arithmos4j_native=":sdk:electrostatic4j:arithmos4j:arithmos4j-native"
arithmos4j_examples=":sdk:electrostatic4j:arithmos4j:arithmos4j-examples"

echo -e "${ORANGE_C} Compiling and Assembling serial4j-core"

./gradlew ${arithmos4j_core}:build \
          ${arithmos4j_core}:generateSourcesJar
        # :serial4j:serial4j-core:generateJavadocJar 

echo -e "${ORANGE_C} Compiling arithmos4j-native"

./helper-scripts/project-impl/compile-electrostatic4j.sh \
       "electrostatic4j/arithmos4j/arithmos4j-native" "arithmos4j" "${GCC_BIN_x86}" "${GPP_BIN_x86}" "${TOOLCHAIN_INCLUDES_x86}" \
        "${JAVA_HOME}" "${TARGET_x86_64}" "linux" "${x86_64}"

./helper-scripts/project-impl/compile-electrostatic4j.sh \
       "electrostatic4j/arithmos4j/arithmos4j-native" "arithmos4j" "${GCC_BIN_x86}" "${GPP_BIN_x86}" "${TOOLCHAIN_INCLUDES_x86}" \
        "${JAVA_HOME}" "${TARGET_x86}" "linux" "${x86}"

echo -e "${ORANGE_C} Bundling arithmos4j-native"

./gradlew ${arithmos4j_native}:copyBinaries && \
./gradlew ${arithmos4j_native}:build && \
./gradlew ${arithmos4j_native}:copyToExamples

echo -e "${ORANGE_C} Building Examples"
./gradlew ${arithmos4j_native}:build

