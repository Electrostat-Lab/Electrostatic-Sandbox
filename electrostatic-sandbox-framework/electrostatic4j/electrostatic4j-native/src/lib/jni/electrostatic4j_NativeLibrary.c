#include <jni/electrostatic4j_NativeLibrary.h>
#include <electrostatic/comm/comm.h>
#include <stdio.h>

JNIEXPORT jint JNICALL Java_electrostatic4j_NativeLibrary_open
  (JNIEnv* env, jclass clazz, jstring data) {
    init_protocols_default();
    parallel.open(0);
    serial.open(0);
    return 0;
}
