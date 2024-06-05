#include <jni/electrostatic4j_NativeLibrary.h>
#include <electrostatic/comm/comm.h>
#include <stdio.h>

JNIEXPORT jint JNICALL Java_electrostatic4j_NativeLibrary_open
  (JNIEnv* env, jclass clazz, jstring data) {
    comm_protocol serial;
    comm_protocol parallel;
    init_protocol_default(&serial, Serial);
    init_protocol_default(&parallel, Parallel);
    parallel.open(0);
    serial.open(0);
    return 0;
}
