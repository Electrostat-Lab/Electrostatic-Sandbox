#include <jni/com_serial4j_core_errno_NativeErrno_ErrnoMessage.h>
#include <ErrnoUtils.h>
#include <string.h>

JNIEXPORT jstring JNICALL Java_com_serial4j_core_errno_NativeErrno_00024ErrnoMessage_getMessageFromStdErrno
(JNIEnv *env, jclass clazz, jint errnum
/* never use "errno" with the "errno.h"; this will lead to forced mangling*/) {
    switch (errnum) {
        case ERR_OPERATION_FAILED:
            return env->NewStringUTF("Operation Failure!");
        case ERR_INVALID_PORT:
            return env->NewStringUTF("Invalid port or abrupt device disconnection!");
        case ERR_INVALID_DIR:
            return env->NewStringUTF("Invalid directory!");
        case ERR_NO_AVAILABLE_TTY_DEVICES:
            return env->NewStringUTF("No Available Teletypewriter character devices; check your ports!");
        case LOGGER_DISABLED:
            return env->NewStringUTF("The framework logging is disabled!");
        default:
            return env->NewStringUTF(strerror(errnum));
    }
}

