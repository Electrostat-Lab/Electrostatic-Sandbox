#!/bin/bash
source "./helper-scripts/common-variables.sh"
source "./helper-scripts/project-impl/variables.sh"

serial4j_core=":electrostatic-sandbox-framework:electrostatic4j:serial4j:serial4j-core"
serial4j_native=":electrostatic-sandbox-framework:electrostatic4j:serial4j:serial4j-native"
serial4j_examples=":electrostatic-sandbox-framework:electrostatic4j:serial4j:serial4j-examples"

echo -e "${ORANGE_C} Compiling and Assembling serial4j-core"

chmod +rwx ./gradlew

./gradlew \
"${serial4j_core}":build \
"${serial4j_core}":generateSourcesJar
#"${serial4j_core}":generateJavadocJar

echo -e "${ORANGE_C} Compiling serial4j-native"

./helper-scripts/project-impl/compile-electrostatic4j.sh \
       "electrostatic4j/serial4j/serial4j-native" "serial4j" "${GCC_BIN_x86}" "${GPP_BIN_x86}" "${TOOLCHAIN_INCLUDES_x86}" \
        "${JAVA_HOME}" "${TARGET_x86_64}" "linux" "${x86_64}"

./helper-scripts/project-impl/compile-electrostatic4j.sh \
       "electrostatic4j/serial4j/serial4j-native" "serial4j" "${GCC_BIN_x86}" "${GPP_BIN_x86}" "${TOOLCHAIN_INCLUDES_x86}" \
        "${JAVA_HOME}" "${TARGET_x86}" "linux" "${x86}"

echo -e "${ORANGE_C} Bundling serial4j-native"

./gradlew "${serial4j_native}":copyBinaries && \
./gradlew "${serial4j_native}":build && \
./gradlew "${serial4j_native}":copyToExamples

#echo -e "${ORANGE_C} Building Examples"
./gradlew "${serial4j_examples}":build

