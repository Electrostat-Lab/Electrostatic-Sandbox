/**
 * @file com_serial4j_core_terminal_NativeTerminalDevice.c
 * @author pavl_g.
 * @brief Instantiates a native interface of Serial4j API for the java programming language.
 * @version 0.1
 * @date 2022-09-06
 * 
 * @copyright 
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Scrappers Team, The AVR-Sandbox Project, Serial4j API.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include<jni/com_serial4j_core_terminal_NativeTerminalDevice.h>
#include<electrostatic/util/filesystem/file_verify.h>
#include<errno.h>
#include<linux/TerminalDevice.h>
#include<linux/ModemController.h>
#include<stdlib.h>
#include<JniUtils.h>

AddressesBuffer serialPorts;

/**
 * @brief Deprecated for removal.
 */
JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_setupJniEnvironment
  (JNIEnv* env, jclass clazz) {
    return JniUtils::setupJavaEnvironment(env, JNI_VERSION_1_8);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_isExistential__Ljava_lang_String_2
  (JNIEnv *env, jclass clazz, jstring port) {
    const char* buffer = JniUtils::getBufferFromString(env, port);
    jint state = is_existential(buffer);
    env->ReleaseStringUTFChars(port, buffer);
    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_isExistential
  (JNIEnv *env, jobject object) {
    jint fd = JniUtils::getPortDescriptorFromSerialPort(env, &object);
    return is_fexistential(fd);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_setTerminalControlFlag
  (JNIEnv* env, jobject object, jint flag) {
    // unmarshalling the Java Objects into the Native Placeholders
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    const TerminalFlag terminalFlag = flag;
    int state = device.setTerminalControlFlag(terminalFlag);
    env->ReleaseStringUTFChars(port.jstringPath, port.path);
    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_setTerminalLocalFlag
  (JNIEnv* env, jobject object, jint flag) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    const TerminalFlag terminalFlag = flag;
    int state = device.setTerminalLocalFlag(terminalFlag);
    env->ReleaseStringUTFChars(port.jstringPath, port.path);
    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_setTerminalInputFlag
  (JNIEnv* env, jobject object, jint flag) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    const TerminalFlag terminalFlag = flag;
    int state = device.setTerminalInputFlag(terminalFlag);
    env->ReleaseStringUTFChars(port.jstringPath, port.path);
    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_setTerminalOutputFlag
  (JNIEnv* env, jobject object, jint flag) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    const TerminalFlag terminalFlag = flag;
    int state = device.setTerminalOutputFlag(terminalFlag);
    env->ReleaseStringUTFChars(port.jstringPath, port.path);
    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_getTerminalControlFlag
  (JNIEnv* env, jobject object) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    int state = device.getTerminalControlFlag();
    env->ReleaseStringUTFChars(port.jstringPath, port.path);
    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_getTerminalLocalFlag
  (JNIEnv* env, jobject object) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    int state = device.getTerminalLocalFlag();
    env->ReleaseStringUTFChars(port.jstringPath, port.path);
    return state;
} 

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_getTerminalInputFlag
  (JNIEnv* env, jobject object) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    int state = device.getTerminalInputFlag();
    env->ReleaseStringUTFChars(port.jstringPath, port.path);
    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_getTerminalOutputFlag
  (JNIEnv* env, jobject object) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    int state = device.getTerminalOutputFlag();
    env->ReleaseStringUTFChars(port.jstringPath, port.path);
    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_setReadConfigurationMode
  (JNIEnv* env, jobject object, jshort timeoutValue, jshort minimumBytes) {
    
    /* Narrowing off the [jshort] values to [unsigned char]
       will drop the bits that are not in the range of the unsigned char */
    cc_t readConfig[READ_CONFIG_SIZE] = {(cc_t) timeoutValue, (cc_t) minimumBytes};
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    int state = device.setReadConfigurationMode(readConfig);
    env->ReleaseStringUTFChars(port.jstringPath, port.path);
    return state;
}

JNIEXPORT jshortArray JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_getReadConfigurationMode
  (JNIEnv* env, jobject object) {

    cc_t readConfig[READ_CONFIG_SIZE];
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);

    device.getReadConfigurationMode(readConfig);
    /* wrap the incompatible data type into a jint primitive array */
    /* Note: at this point, casting from [unsigned char] to [short] is implicit! */
    jshort s_readConfig[READ_CONFIG_SIZE] = {readConfig[0], readConfig[1]};
    /* create a jintArray from a primitive jint C-array */
    jshortArray array = JniUtils::getShortArrayFromBuffer(env, s_readConfig, READ_CONFIG_SIZE);

    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return array;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_fetchSerialPorts
  (JNIEnv* env, jobject object) {

     int state = TerminalDevice::fetchSerialPorts(&serialPorts);
     int length = *serialPorts.getAddressesCount();
     jobjectArray stringArray = JniUtils::getStringArrayFromBuffer(env, (const char**) serialPorts.getStartAddress(), length);
     JniUtils::setObjectField(env, &object, "serialPorts", "[Ljava/lang/String;", stringArray);
     serialPorts.deallocateAll();

     return state;  
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_write__I
  (JNIEnv* env, jobject object, jint buffer) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    int state = device.writeData(&buffer, 1);
    env->ReleaseStringUTFChars(port.jstringPath, port.path);
    return state;
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_write__Ljava_lang_String_2I
  (JNIEnv* env, jobject object, jstring string, jint length) {

    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);

    const char* buffer = JniUtils::getBufferFromString(env, string);
    int state = device.writeData(buffer, length);
    env->ReleaseStringUTFChars(string, buffer);

    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return state;
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_sread__
  (JNIEnv* env, jobject object) {

    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);

    /* construct a termios and get the control character flag from fd */
    struct termios tty;
    device.getTermiosFromFd(&tty);
    int length = tty.c_cc[VMIN] <= 0 ? 1 : tty.c_cc[VMIN];

    char strBuffer[length + 1];
    /* clear the memory blocks before using */
    memset(strBuffer, '\0', sizeof(strBuffer));
    long bytes = device.readData((void*) strBuffer, length);
    /* get the java string buffer and setup its data with the buffer */
    JniUtils::setObjectField(env, &object, "readBuffer", "Ljava/lang/String;", env->NewStringUTF(strBuffer));
    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return bytes;
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_sread__I
  (JNIEnv* env, jobject object, jint length) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);

    /* use an additional memory block for the null terminating character '\0' */
    char strBuffer[length + 1];
    /* clear the memory blocks before using */
    memset(strBuffer, '\0', sizeof(strBuffer));
    long bytes = device.readData((void*) strBuffer, length);
    /* get the java string buffer and setup its data with the buffer */
    JniUtils::setObjectField(env, &object, "readBuffer", "Ljava/lang/String;", env->NewStringUTF(strBuffer));
    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return bytes;
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_iread
  (JNIEnv* env, jobject object, jint length) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);

    /* create the buffer and initialize it with zero */
    jchar buffer[length + 1];
    memset(buffer, '\0', sizeof(buffer));

    /* read data into the buffer */
    long bytes = device.readData((void*) buffer, length);

    /* send the data to the Java buffer */
    jcharArray array = JniUtils::getCharArrayFromBuffer(env, buffer, length);
    JniUtils::setObjectField(env, &object, "buffer", "[C", array);
    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return bytes;
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_seek
  (JNIEnv* env, jobject object, jlong offset, jint whence) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    jlong state = device.seek(offset, whence);
    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_setBaudRate
  (JNIEnv* env, jobject object, jint baudRate) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    jint state = device.setBaudRate(baudRate);
    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_getBaudRate
  (JNIEnv* env, jobject object) {
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    int state = device.getBaudRate();
    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_initTerminal
  (JNIEnv* env, jobject object) {

    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);
    int state = device.initTermios();
    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_openPort
  (JNIEnv* env, jobject object) {

    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);

    int fd = device.openPort();
    // update the Java Serial Port Object from the native Serial Port C++ object
    JniUtils::updateJVMSerialPortFrom(env, &object, &port);

    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return fd;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_setModemBitsStatus
  (JNIEnv* env, jobject object, jint status) {
    int fd = JniUtils::getPortDescriptorFromSerialPort(env, &object);
    return ModemController::setModemBitsStatus(fd, &status);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_getModemBitsStatus
  (JNIEnv* env, jobject object, jintArray pointer) {
    int fd = JniUtils::getPortDescriptorFromSerialPort(env, &object);
    jint* elements = JniUtils::getIntArrayElements(env, &pointer);
    int state = ModemController::getModemBitsStatus(fd, elements);
    env->ReleaseIntArrayElements(pointer, elements, 0);
    return state;
}


JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_closePort
  (JNIEnv* env, jobject object) {
    
    SerialPort port;
    JniUtils::updateNativeSerialPortFrom(env, &object, &port);
    TerminalDevice device(&port);

    int state = device.closePort();

    // update the Java port
    JniUtils::updateJVMSerialPortFrom(env, &object, &port);

    env->ReleaseStringUTFChars(port.jstringPath, port.path);

    return state;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_terminal_NativeTerminalDevice_getErrno
  (JNIEnv* env, jobject object) {
    return errno;
}