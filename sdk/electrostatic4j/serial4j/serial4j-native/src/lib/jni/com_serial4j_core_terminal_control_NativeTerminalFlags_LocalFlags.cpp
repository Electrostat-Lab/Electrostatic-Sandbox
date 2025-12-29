#include<jni/com_serial4j_core_terminal_control_NativeTerminalFlags_LocalFlags.h>
#include<termios.h>

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getEchoInputCharacters
  (JNIEnv* env, jclass clazz) {
    return ECHO;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getEchoControlCharacters
  (JNIEnv* env, jclass clazz) {
    return ECHOCTL;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getEchoErase
  (JNIEnv* env, jclass clazz) {
    return ECHOE;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getEchoKill
  (JNIEnv* env, jclass clazz) {
    return ECHOK;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getDisableNewLineAfterEchoKill
  (JNIEnv* env, jclass clazz) {
    return ECHOKE;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getEchoNewLine
  (JNIEnv* env, jclass clazz) {
    return ECHONL;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getEchoDeletedCharactersBackward
  (JNIEnv* env, jclass clazz) {
    return ECHOPRT;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getOutputBeingFlushed
  (JNIEnv* env, jclass clazz) {
    return FLUSHO;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getCanonicalModeInput
  (JNIEnv* env, jclass clazz) {
    return ICANON;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getEnableExtendedProcessingOfInput
  (JNIEnv* env, jclass clazz) {
    return IEXTEN;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getEnableSignalGeneratingCharacters
  (JNIEnv* env, jclass clazz) {
    return ISIG;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getDisableFlushing
  (JNIEnv* env, jclass clazz) {
    return NOFLSH;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getRedisplayPendingInput
  (JNIEnv* env, jclass clazz) {
    return PENDIN;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getGenerateTerminateSignalForBackgroundProcess
  (JNIEnv* env, jclass clazz) {
    return TOSTOP;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_control_NativeTerminalFlags_00024LocalFlags_getCanonicalPresentation
  (JNIEnv* env, jclass clazz) {
    return XCASE;
}