#include<jni/com_serial4j_core_filesystem_AbstractFilesystem.h>
#include<electrostatic/electronetsoft/util/filesystem/file_verify.h>
#include<stdlib.h>
#include<JniUtils.h>

JNIEXPORT jint JNICALL Java_com_serial4j_core_filesystem_AbstractFilesystem_isExistential
  (JNIEnv *env, jclass clazz, jstring port) {
    const char *buffer = JniUtils::getBufferFromString(env, port);
    jint state = is_existential(buffer);
    env->ReleaseStringUTFChars(port, buffer);
    return state;
}


