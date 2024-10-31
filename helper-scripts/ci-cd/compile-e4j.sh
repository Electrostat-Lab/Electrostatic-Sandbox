#!/bin/bash
source "./helper-scripts/common-variables.sh"
source "./helper-scripts/project-impl/variables.sh"

e4j_core=":electrostatic-sandbox-framework:electrostatic4j:electrostatic4j-core"
e4j_native=":electrostatic-sandbox-framework:electrostatic4j:electrostatic4j-native"
e4j_examples=":electrostatic-sandbox-framework:electrostatic4j:electrostatic4j-examples"

echo -e "${ORANGE_C} Compiling and Assembling e4j-core"

chmod +rwx ./gradlew

./gradlew ${e4j_core}:build \
          ${e4j_core}:generateSourcesJar \
          ${e4j_core}:generateJavadocJar

echo -e "${ORANGE_C} Compiling e4j-native"

./helper-scripts/project-impl/compile-electrostatic4j.sh \
        "${e4j_dir}" "${COMMISSION_LIB_4j}" "${GCC_BIN_x86}" "${GPP_BIN_x86}" "ON" "${TOOLCHAIN_INCLUDES_x86}" \
        "${JAVA_HOME}" "${TARGET_x86_64}" "linux" "${x86_64}"

./helper-scripts/project-impl/compile-electrostatic4j.sh \
        "${e4j_dir}" "${COMMISSION_LIB_4j}" "${GCC_BIN_x86}" "${GPP_BIN_x86}" "ON" "${TOOLCHAIN_INCLUDES_x86}" \
        "${JAVA_HOME}" "${TARGET_x86}" "linux" "${x86}"

echo -e "${ORANGE_C} Bundling e4j-native"

./gradlew ${e4j_native}:copyBinaries && \
./gradlew ${e4j_native}:build && \
./gradlew ${e4j_native}:copyToExamples

echo -e "${ORANGE_C} Building Examples"
./gradlew ${e4j_examples}:build

