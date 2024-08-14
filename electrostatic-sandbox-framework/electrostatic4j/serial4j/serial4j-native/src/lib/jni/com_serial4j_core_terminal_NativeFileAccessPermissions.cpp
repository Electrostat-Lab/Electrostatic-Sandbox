#include<jni/com_serial4j_core_terminal_NativeFileAccessPermissions.h>
#include<sys/stat.h>

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFileAccessPermissions_fileChmod
  (JNIEnv* env, jclass clazz, jint fd, jint mode) {
    return fchmod(fd, mode);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFileAccessPermissions_getGrantReadByOwner
  (JNIEnv* env, jclass clazz) {
    return S_IREAD;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFileAccessPermissions_getGrantWriteByOwner
  (JNIEnv* env, jclass clazz) {
    return S_IWRITE;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFileAccessPermissions_getGrantExecuteByOwner
  (JNIEnv* env, jclass clazz) {
    return S_IEXEC;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeFileAccessPermissions_getGrantFullPermissions
  (JNIEnv* env, jclass clazz) {
    return S_IRWXU;
}