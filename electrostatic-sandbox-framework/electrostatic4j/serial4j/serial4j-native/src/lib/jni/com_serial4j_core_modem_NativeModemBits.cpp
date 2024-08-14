#include<jni/com_serial4j_core_modem_NativeModemBits.h>
#include<sys/ioctl.h>

JNIEXPORT jint JNICALL Java_com_serial4j_core_modem_NativeModemBits_getDatasetReadyLineEnable
  (JNIEnv* env, jclass clazz) {
    return TIOCM_LE;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_modem_NativeModemBits_getDataTerminalReady
  (JNIEnv* env, jclass clazz) {
    return TIOCM_DTR;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_modem_NativeModemBits_getRequestToSend
  (JNIEnv* env, jclass clazz) {
    return TIOCM_RTS;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_modem_NativeModemBits_getSecondaryTransmit
  (JNIEnv* env, jclass clazz) {
    return TIOCM_ST;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_modem_NativeModemBits_getSecondaryReceive
  (JNIEnv* env, jclass clazz) {
    return TIOCM_SR;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_modem_NativeModemBits_getClearToSend
  (JNIEnv* env, jclass clazz) {
    return TIOCM_CTS;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_modem_NativeModemBits_getDataCarrierDetect
  (JNIEnv* env, jclass clazz) {
    return TIOCM_CAR;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_modem_NativeModemBits_getRingSignal
  (JNIEnv* env, jclass clazz) {
    return TIOCM_RNG;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_modem_NativeModemBits_getDataSetReady
  (JNIEnv* env, jclass clazz) {
    return TIOCM_DSR;
}