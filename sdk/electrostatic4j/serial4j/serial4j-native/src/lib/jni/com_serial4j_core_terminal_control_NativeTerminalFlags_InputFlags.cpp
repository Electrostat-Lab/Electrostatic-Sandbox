#include<jni/com_serial4j_core_terminal_control_NativeTerminalFlags_InputFlags.h>
#include<termios.h>

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getSignalInterrupt
  (JNIEnv* env, jclass clazz) {
    return BRKINT;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getMapCarriageReturnToNewLine
  (JNIEnv* env, jclass clazz) {
    return ICRNL;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getIgnoreBreakCondition
  (JNIEnv* env, jclass clazz) {
    return IGNBRK;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getIgnoreCarriageReturn
  (JNIEnv* env, jclass clazz) {
    return IGNCR;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getIgnoreCharsWithParityErrors
  (JNIEnv* env, jclass clazz) {
    return IGNPAR;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getRingBell
  (JNIEnv* env, jclass clazz) {
    return IMAXBEL;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getMapNewLineToCarriageReturn
  (JNIEnv* env, jclass clazz) {
    return INLCR;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getEnableParityChecking
  (JNIEnv* env, jclass clazz) {
    return INPCK;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getStripHighBit
  (JNIEnv* env, jclass clazz) {
    return ISTRIP;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getInputIsUnicode8
  (JNIEnv* env, jclass clazz) {
    return IUTF8;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getMapUppercaseToLowercase
  (JNIEnv* env, jclass clazz) {
    return IUCLC;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getAllowToRestartStoppedOutput
  (JNIEnv* env, jclass clazz) {
    return IXANY;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getEnableInputFlowControl
  (JNIEnv* env, jclass clazz) {
    return IXOFF;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getEnableOutputFlowControl
  (JNIEnv* env, jclass clazz) {
    return IXON;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024InputFlags_getMarkParityErrors
  (JNIEnv* env, jclass clazz) {
    return PARMRK;
}