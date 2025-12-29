#include<jni/com_serial4j_core_terminal_control_NativeTerminalFlags_OutputFlags.h>
#include<termios.h>

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getBackspaceDelayMask
  (JNIEnv* env, jclass clazz) {
    return BSDLY;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getCarriageReturnDelayMask
  (JNIEnv* env, jclass clazz) {
    return CRDLY;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getFormFeedDelayMask
  (JNIEnv* env, jclass clazz) {
    return FFDLY;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getNewLineDelayMask
  (JNIEnv* env, jclass clazz) {
    return NLDLY;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getMapCarriageReturnToNewLine
  (JNIEnv* env, jclass clazz) {
    return OCRNL;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getUsePredefinedFillCharacters
  (JNIEnv* env, jclass clazz) {
    return OFDEL;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getUseFillCharacters
  (JNIEnv* env, jclass clazz) {
    return OFILL;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getMapLowercaseToUppercase
  (JNIEnv* env, jclass clazz) {
    return OLCUC;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getMapNewLineToCarriageReturn
  (JNIEnv* env, jclass clazz) {
    return ONLCR;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getNewLineAsCarriageReturn
  (JNIEnv* env, jclass clazz) {
    return ONLRET;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getNoCarriageReturnDuplicateOutput
  (JNIEnv* env, jclass clazz) {
    return ONOCR;
}


JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getPerformOutputPostProcessing
  (JNIEnv *, jclass) {
    return OPOST;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getHorizontalTabDelayMask
  (JNIEnv* env, jclass clazz) {
    return TABDLY;
}


JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024OutputFlags_getVerticalTabDelayMask
  (JNIEnv* env, jclass clazz) {
    return VTDLY;
}