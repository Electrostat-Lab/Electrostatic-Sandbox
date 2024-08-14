#!/bin/bash
source "./common-variables.sh"
source "./helper-scripts/project-impl/variables.sh"

cd ./electrostatic4j

echo -e "${ORANGE_C} Compiling and Assembling e4j-core"
./gradlew :electrostatic4j-core:build \
          :electrostatic4j-core:generateSourcesJar \
          :electrostatic4j-core:generateJavadocJar 

cd ..
echo -e "${ORANGE_C} Compiling e4j-native"

./helper-scripts/project-impl/compile-electrostatic4j.sh \
        "${e4j_dir}" "${COMMISSION_LIB_4j}" "${GCC_BIN_x86}" "${GPP_BIN_x86}" "${TOOLCHAIN_INCLUDES_x86}" \
        "${JAVA_HOME}" "${TARGET_x86_64}" "linux" "${x86_64}"

./helper-scripts/project-impl/compile-electrostatic4j.sh \
        "${e4j_dir}" "${COMMISSION_LIB_4j}" "${GCC_BIN_x86}" "${GPP_BIN_x86}" "${TOOLCHAIN_INCLUDES_x86}" \
        "${JAVA_HOME}" "${TARGET_x86}" "linux" "${x86}"

cd ./electrostatic4j
echo -e "${ORANGE_C} Bundling e4j-native"
./gradlew :electrostatic4j-native:copyBinaries && \
./gradlew :electrostatic4j-native:build && \
./gradlew :electrostatic4j-native:copyToExamples

echo -e "${ORANGE_C} Building Examples"
./gradlew :electrostatic4j-examples:build

