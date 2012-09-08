// Author: mszal@google.com (Michael Szal)

#ifndef LIBWEBM_COMMON_H
#define LIBWEBM_COMMON_H

#include <jni.h>

#define NAME(a, b, c) Java_com_google_libwebm_##a##_##b##_##c
#define FUNC(returnType, packageName, className, functionName, ...) \
  extern "C" { \
    JNIEXPORT returnType NAME(packageName, className, functionName) \
        (JNIEnv* env, jobject self, ##__VA_ARGS__); \
  } \
  JNIEXPORT returnType NAME(packageName, className, functionName) \
      (JNIEnv* env, jobject self, ##__VA_ARGS__)

jint JNI_OnLoad(JavaVM* vm, void* reserved);
jbyteArray newByteArray(JNIEnv* env, const void* source, size_t size);
void setBuffer(JNIEnv* env, jbyteArray source, unsigned char** destination,
               long long* size);
void setBuffer(JNIEnv* env, jbyteArray source, unsigned char** destination,
               size_t* size);

#endif
