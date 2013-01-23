// Author: mszal@google.com (Michael Szal)

#ifndef LIBVORBIS_COMMON_H
#define LIBVORBIS_COMMON_H

#include <jni.h>

#define NAME(a, b) Java_com_google_libvorbis_##a##_##b
#define FUNC(returnType, className, functionName, ...) \
  extern "C" { \
    JNIEXPORT returnType NAME(className, functionName) \
        (JNIEnv* env, jobject self, ##__VA_ARGS__); \
  } \
  JNIEXPORT returnType NAME(className, functionName) \
      (JNIEnv* env, jobject self, ##__VA_ARGS__)

jint JNI_OnLoad(JavaVM* vm, void* reserved);

#endif
