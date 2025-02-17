/**
 * @file JniUtils.util
 * @author pavl_g.
 * @brief Java Native Interface Utility methods for jni java 8 and invocation api.
 * @version 0.1
 * @date 2022-08-28
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
#ifndef JNI_UTILS 
#define JNI_UTILS 

#include<jni.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<linux/TerminalDevice.h>
#include<ErrnoUtils.h>

#define CONSTRUCTOR ((const char*) "<init>")
#define STATIC_INIT ((const char*) "<clinit>")

#define NON_PARAMTERIZED_VOID_SIG ((const char*) "()V")
#define NON_PARAMETERIZED_INT_SIG ((const char*) "()I")
#define NON_PARAMETERIZED_STRING_SIG ((const char*) "()[Ljava/lang/String;")
#define NON_PARAMETERIZED_LONG_SIG ((const char*) "()J")

#define java_lang_String ((const char*) "java/lang/String")
#define java_io_IOException ((const char*) "java/io/IOException")
#define java_io_InputStream ((const char*) "java/io/InputStream")
#define java_io_OutputStream ((const char*) "java/io/OutputStream")
#define java_io_FileInputStream ((const char*) "java/io/FileIntputStream")
#define java_io_FileOutputStream ((const char*) "java/io/FileOutputStream")

namespace JniUtils {

    static JNIEnv* env;
    static JavaVM* jvm;
    static jint version;
    static struct JavaVMAttachArgs* jvmArgs;

    static inline const char* getBufferFromString(JNIEnv* env, jstring string) {
        const char* chars = env->GetStringUTFChars(string, 0);
        return chars;
    }

    static inline jstring getStringFromBuffer(JNIEnv* env, const char* buffer) {
        return env->NewStringUTF(buffer);
    }

    /**
     * @brief Sets the Jni Env pointer for jni functions.
     * 
     * @param env the environment pointer to use.
     */
    static inline int setupJavaEnvironment(JNIEnv* env, jint version) {
        if (env == NULL) {
            return ERR_OPERATION_FAILED;
        }
        env->GetJavaVM(&JniUtils::jvm);
        JniUtils::version = version;
        return OPERATION_SUCCEEDED;
    }

    static inline JavaVM* getJavaVM() {
        return JniUtils::jvm;
    }

    /**
     * @brief Gets the Jni Env pointer from the jvm with multithreading support.
     * 
     * @return JNIEnv* the namespace env pointer.
     */
    static inline JNIEnv** getJniEnv() {
        JniUtils::jvm->GetEnv((void**) &JniUtils::env, version);
        return &JniUtils::env;
    }

    static inline struct JavaVMAttachArgs* getJVMAttachArgs(jint jreVersion, char* threadName, jobject threadGroupObj) {
        jvmArgs->version = jreVersion;
        jvmArgs->name = threadName;
        jvmArgs->group = threadGroupObj;
        return jvmArgs;
    }

    static inline jint attachNativeThread(char* threadName, jobject threadGroupObj) {
        void** jniEnvPointer = (void**) JniUtils::getJniEnv();
        struct JavaVMAttachArgs* jvmArgs = getJVMAttachArgs(JniUtils::version, threadName, threadGroupObj);
        return JniUtils::getJavaVM()->AttachCurrentThread(jniEnvPointer, jvmArgs);
    }

    /**
     * @brief Retrieves a java class from a name, the name is referred to by the
     * package/class, example: {"com/java/io/IOException"}.
     *
     * @param clazzName the class name using the format {package/class}.
     * @return jclass the reflected java class.
     */
    static inline jclass getClassFromString(JNIEnv* env, const char* clazzName) {
        return env->FindClass(clazzName);
    }

    /**
     * @brief Retrieves a java class method using the [methodName] for the method name
     * and the [sig] for the method signature.
     *
     * @param clazzName the class name in the format {"package/class"}.
     * @param methodName the method name, use `<init>` for constructors.
     * @param sig the method signature, eg: ()V for non-parameterized void method.
     * @return jmethodID a new method id for the requested method.
     */
    static inline jmethodID getClassMethod(JNIEnv* env, const char* clazzName, const char* methodName, const char* sig) {
        return env->GetMethodID(getClassFromString(env, clazzName), methodName, sig);
    }

    /**
     * @brief Retrieves the java class constructor.
     *
     * @version version 0 from getClassConstructor for parameteized constructors using constructor
     * signature.
     * @param clazzName the java class name in the format {"package/class"}.
     * @param sig the constructor signature, eg: ()V for non-parameterized void type.
     * @return jmethodID an id referring to the class constructor.
     */
    static inline jmethodID getClassConstructor0(JNIEnv* env, const char* clazzName, const char* sig) {
        return JniUtils::getClassMethod(env, clazzName, CONSTRUCTOR, sig);
    }

    /**
     * @brief Retrieves the java class non-parameterized constructor with signature
     * [NON_PARAMTERIZED_VOID_SIG].
     *
     * @param clazzName the java class name.
     * @return jmethodID an id referring to the class non-parameterized constructor.
     */
    static inline jmethodID getClassConstructor1(JNIEnv* env, const char* clazzName) {
        return JniUtils::getClassConstructor0(env, clazzName, NON_PARAMTERIZED_VOID_SIG);
    }

    /**
     * @brief Calls a parameterized method [methodName] from class [clazzName].
     *
     * @param clazzName the class name where the method is located, eg: {"java/io/IOException"}.
     * @param methodName the method name to call.
     * @param sig the signature of the method, eg: ()V for non-paramterized void methods.
     * @param args an array for the method parameters of type [jvalue] referring to one of the JNI
     * data types [jint, jbyte, jlong, jshort, jchar, jweak...etc].
     */
    static inline void callParameterizedMethod(JNIEnv* env, const char* clazzName, const char* methodName, const char* sig, jvalue* args) {
        jclass clazz = JniUtils::getClassFromString(env, clazzName);
        jmethodID mid = JniUtils::getClassMethod(env, clazzName, methodName, sig);
        if (args == NULL) {
            env->CallVoidMethod(clazz, mid);
        } else {
            env->CallVoidMethod(clazz, mid, args);
        }
    }

    /**
     * @brief Calls a non-parameterized method [methodName] with signature [sig].
     *
     * @param clazzName the class name where the method is located, eg: {"java/lang/String"}.
     * @param methodName the method name to call.
     * @param sig the signature of the method, eg: ()V, ()I, ()J.
     */
    static inline void callNonParameterizedMethod(JNIEnv* env, const char* clazzName, const char* methodName, const char* sig) {
        JniUtils::callParameterizedMethod(env, clazzName, methodName, sig, NULL);
    }

    /**
     * @brief Calls a class parameterized constructor (<init> method) with
     * signature and jvalue (holds only one variable of one JNI data type at a time) parameters.
     *
     * @param clazzName
     * @param sig
     * @param args
     */
    static inline void callParameterizedConstructor(JNIEnv* env, const char* clazzName, const char* sig, jvalue* args) {
        JniUtils::callParameterizedMethod(env, clazzName, CONSTRUCTOR, sig, args);
    }

    static inline void callNonParameterizedConstructor(JNIEnv* env, const char* clazzName) {
        JniUtils::callParameterizedConstructor(env, clazzName, NON_PARAMTERIZED_VOID_SIG, NULL);
    }

    static inline jweak getObjectFromClass0(JNIEnv* env, const char* clazzName) {
        return env->AllocObject(JniUtils::getClassFromString(env, clazzName));
    }

    static inline jweak getObjectFromClass1(JNIEnv* env, const char* clazzName, jmethodID constructor) {
        return env->NewObject(JniUtils::getClassFromString(env, clazzName), constructor);
    }

    static inline jweak getObjectFromClass2(JNIEnv* env, const char* clazzName) {
        return JniUtils::getObjectFromClass1(env, clazzName, JniUtils::getClassConstructor1(env, clazzName));
    }

    static inline jclass getObjectClass(JNIEnv* env, jweak* object) {
        return env->GetObjectClass(*object);
    }

    static inline jfieldID getFieldIDFromObject(JNIEnv* env, jweak* object, const char* fieldName, const char* fieldSig) {
        return env->GetFieldID(getObjectClass(env, object), fieldName, fieldSig);
    }

    static inline jweak getObjectFieldFromClass(JNIEnv* env, jweak* object, const char* fieldName, const char* fieldSig) {
        jfieldID fieldId = getFieldIDFromObject(env, object, fieldName, fieldSig);
        return env->GetObjectField(*object, fieldId);
    }

    static inline jint getIntFieldFromClass(JNIEnv* env, jweak* object, const char* fieldName, const char* fieldSig) {
        jfieldID fieldId = getFieldIDFromObject(env, object, fieldName, fieldSig);
        return env->GetIntField(*object, fieldId);
    }

    static inline void setObjectField(JNIEnv* env, jweak* object, const char* fieldName, const char* fieldSig, jweak value) {
        jfieldID fieldId = getFieldIDFromObject(env, object, fieldName, fieldSig);
        env->SetObjectField(*object, fieldId, value);
    }

    static inline void setIntField(JNIEnv* env, jweak* object, const char* fieldName, const char* fieldSig, jint value) {
        jfieldID fieldId = getFieldIDFromObject(env, object, fieldName, fieldSig);
        env->SetIntField(*object, fieldId, value);
    }

    /**
     * Translates a java TerminalDevice object into a native TerminalDevice object.
     *
     * @param object a pointer referring to the java TerminalDevice object.
     * @return a native terminal device holding the jdk terminal device's data.
     */
    static inline jweak getSerialPortFromTerminalDevice(JNIEnv* env, jweak* object) {
        return getObjectFieldFromClass(env, object, "serialPort", "Lcom/serial4j/core/serial/SerialPort;");
    }

    static inline int getPortDescriptorFromSerialPort(JNIEnv* env, jweak* object) {
        jweak serialPortObject = getSerialPortFromTerminalDevice(env, object);
        return getIntFieldFromClass(env, &serialPortObject, "fd", "I");
    }

    static inline int updateNativeSerialPortFrom(JNIEnv* env, jweak *object, SerialPort *port) {
        // unmarshalling Java Objects into a native object
        if (env == NULL || object == NULL || port == NULL) {
            return -1;
        }

        jweak serialPortObject = getSerialPortFromTerminalDevice(env, object);
        int fd = getIntFieldFromClass(env, &serialPortObject, "fd", "I");
        int isPortOpened = getIntFieldFromClass(env, &serialPortObject, "portOpened", "I");
        int ioFlag = getIntFieldFromClass(env, &serialPortObject, "ioFlag", "I");
        jstring _path = (jstring) getObjectFieldFromClass(env, &serialPortObject, "path", "Ljava/lang/String;");
        const char *path = getBufferFromString(env, _path);

        port->fd = fd;
        port->portOpened = isPortOpened;
        port->ioFlag = ioFlag;
        port->path = (char*) path;
        port->jstringPath = _path;

        // don't forget to dispatch "env->ReleaseStringUTFChars(port.jstringPath, port.path);"
        // after finishing from the SerialPort instance, so that the native memory
        // of the buffer path would be released back to the system

        return 0;
    }

    static inline jweak updateJVMSerialPortFrom(JNIEnv* env, jweak *object, SerialPort *port) {
        if (env == NULL || object == NULL || port == NULL) {
            return NULL;
        }

        // marshalling Native Objects into a Java object
        int fd = port->fd;
        int isPortOpened = port->portOpened;
        int ioFlag = port->ioFlag;
        const char *path = port->path;
        jstring pathValue = (jstring) getStringFromBuffer(env, path);
        jweak serialPortObject = getSerialPortFromTerminalDevice(env, object);

        setIntField(env, &serialPortObject, "fd", "I", fd);
        setIntField(env, &serialPortObject, "portOpened", "I", isPortOpened);
        setIntField(env, &serialPortObject, "ioFlag", "I", ioFlag);
        setObjectField(env, &serialPortObject, "path", "Ljava/lang/String;", pathValue);

        return serialPortObject;
    }

    static inline jobjectArray createNewArrayFromBuffer(JNIEnv* env, const char* clazzName, jsize length) {
        jstring initialElement = env->NewStringUTF("");

        jclass clazz = JniUtils::getClassFromString(env, clazzName);

        return env->NewObjectArray(length, clazz, initialElement);
    }

    static inline jobjectArray getStringArrayFromBuffer(JNIEnv* env, const char** buffer, int length) {
        jobjectArray objectBuffer = JniUtils::createNewArrayFromBuffer(env, java_lang_String, length);
        for (int i = 0; i < length; i++) {
            env->SetObjectArrayElement(objectBuffer, i, getStringFromBuffer(env, buffer[i]));
        }
        return objectBuffer;
    }

    static inline void setArrayElements(JNIEnv* env, jobjectArray array, jsize length, jobject* values) {
        for (int i = 0; i < length; i++) {
            env->SetObjectArrayElement(array, i, values[i]);
        }
    }

    static inline jweak getArrayElement(JNIEnv* env, jobjectArray* array, jsize index) {
        return env->GetObjectArrayElement(*array, index);
    }

    static inline jint* getIntArrayElements(JNIEnv* env, jintArray* array) {
        return env->GetIntArrayElements(*array, 0);
    }

    static inline jbyte* getByteArrayElement(JNIEnv* env, jbyteArray* array) {
        return env->GetByteArrayElements(*array, 0);
    }

    static inline jintArray getIntArrayFromBuffer(JNIEnv* env, int* buffer, int length) {
        jintArray intArray = env->NewIntArray(length);
        env->SetIntArrayRegion(intArray, 0, length, buffer);
        return intArray;
    }

    static inline jshortArray getShortArrayFromBuffer(JNIEnv* env, short* buffer, int length) {
        jshortArray shortArray = env->NewShortArray(length);
        env->SetShortArrayRegion(shortArray, 0, length, buffer);
        return shortArray;
    }

    static inline jbyteArray getByteArrayFromBuffer(JNIEnv* env, signed char* buffer, int length) {
        jbyteArray byteArray = env->NewByteArray(length);
        env->SetByteArrayRegion(byteArray, 0, length, buffer);
        return byteArray;
    }

    static inline jcharArray getCharArrayFromBuffer(JNIEnv* env, jchar* buffer, int length) {
        jcharArray charArray = env->NewCharArray(length);
        env->SetCharArrayRegion(charArray, 0, length, buffer);
        return charArray;
    }

    static inline jbooleanArray getBooleanArrayFromBuffer(JNIEnv* env, jboolean* buffer, int length) {
        jbooleanArray booleanArray = env->NewBooleanArray(length);
        env->SetBooleanArrayRegion(booleanArray, 0, length, buffer);
        return booleanArray;
    }

    static inline jchar* getCharArrayStartAddress(JNIEnv* env, jcharArray array) {
        return env->GetCharArrayElements(array, JNI_FALSE);
    }
}

#endif