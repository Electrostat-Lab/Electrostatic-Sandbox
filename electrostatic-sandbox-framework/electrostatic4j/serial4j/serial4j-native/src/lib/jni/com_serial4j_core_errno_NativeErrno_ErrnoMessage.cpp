#include <jni/com_serial4j_core_errno_NativeErrno_ErrnoMessage.h>
#include <ErrnoUtils.h>
#include <JniUtils.h>
#include <string.h>

JNIEXPORT jstring JNICALL Java_com_serial4j_core_errno_NativeErrno_00024ErrnoMessage_getMessageFromStdErrno
(JNIEnv *env, jclass clazz, jint errnum
/* never use "errno" with the "errno.h"; this will lead to forced mangling*/) {
    switch (errnum) {
        case ERR_OPERATION_FAILED:
            return JniUtils::getStringFromBuffer(env, "Operation Failure!");
        case ERR_INVALID_PORT:
            return JniUtils::getStringFromBuffer(env, "Invalid port or abrupt device disconnection!");
        case ERR_INVALID_DIR:
            return JniUtils::getStringFromBuffer(env, "Invalid directory!");
        case ERR_NO_AVAILABLE_TTY_DEVICES:
            return JniUtils::getStringFromBuffer(env, "No Available Teletypewriter character devices; check your ports!");
        case LOGGER_DISABLED:
            return JniUtils::getStringFromBuffer(env, "The framework logging is disabled!");
        default:
            return JniUtils::getStringFromBuffer(env, strerror(errnum));
    }
}

