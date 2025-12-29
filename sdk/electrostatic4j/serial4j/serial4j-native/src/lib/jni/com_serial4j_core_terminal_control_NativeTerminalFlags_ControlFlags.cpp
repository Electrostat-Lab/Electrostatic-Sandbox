#include<jni/com_serial4j_core_terminal_control_NativeTerminalFlags_ControlFlags.h>
#include<termios.h>

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getBaudMask
  (JNIEnv* env, jclass clazz) {
    return CBAUD;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getExtendedBaudMask
  (JNIEnv* env, jclass clazz) {
    return CBAUDEX;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getInputBaudRate
  (JNIEnv* env, jclass clazz) {
    return CIBAUD;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getIgnoreModemStatusLines
  (JNIEnv* env, jclass clazz) {
    return CLOCAL;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getUseStickParity
  (JNIEnv* env, jclass clazz) {
    return CMSPAR;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getAllowInput
  (JNIEnv* env, jclass clazz) {
    return CREAD;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getEnableHardwareFlowControl
  (JNIEnv* env, jclass clazz) {
    return CRTSCTS;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getCharacterSizeMask
  (JNIEnv* env, jclass clazz) {
    return CSIZE;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getUse2StopBitsPerCharacter
  (JNIEnv* env, jclass clazz) {
    return CSTOPB;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getHangUpOnLastClose
  (JNIEnv* env, jclass clazz) {
    return HUPCL;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getParityEnable
  (JNIEnv* env, jclass clazz) {
    return PARENB;
}


JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024ControlFlags_getUseOddParity
  (JNIEnv* env, jclass clazz) {
    return PARODD;
}