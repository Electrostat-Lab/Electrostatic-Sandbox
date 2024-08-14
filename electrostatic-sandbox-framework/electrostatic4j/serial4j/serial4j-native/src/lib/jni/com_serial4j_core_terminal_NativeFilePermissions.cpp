#include<jni/com_serial4j_core_terminal_NativeFilePermissions.h>
#include<fcntl.h>

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFilePermissions_getReadOnly
  (JNIEnv* env, jclass clazz) {
    return O_RDONLY;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFilePermissions_getWriteOnly
  (JNIEnv* env, jclass clazz) {
    return O_WRONLY;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFilePermissions_getReadWrite
  (JNIEnv* env, jclass clazz) {
    return O_RDWR;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFilePermissions_getNoControlTerminalDevice
  (JNIEnv* env, jclass clazz) {
    return O_NOCTTY;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFilePermissions_getTerminalNonBlock
  (JNIEnv* env, jclass clazz) {
    return O_NONBLOCK;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFilePermissions_getCreateFile
  (JNIEnv* env, jclass clazz) {
    return O_CREAT;
}