#include<jni/com_serial4j_core_terminal_NativeTerminalDevice_FileSeekCriterion.h>
#include<unistd.h>

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_00024FileSeekCriterion_getSeekFromStart
  (JNIEnv* env, jclass clazz) {
    return SEEK_SET;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_00024FileSeekCriterion_getSeekFromCurrent
  (JNIEnv* env, jclass clazz) {
    return SEEK_CUR;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_00024FileSeekCriterion_getSeekFromEnd
  (JNIEnv* env, jclass clazz) {
    return SEEK_END;
}