// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>
#include <typeinfo>

#include "common.h"

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return JNI_ERR;
  }
  return JNI_VERSION_1_6;
}

jbyteArray newByteArray(JNIEnv* env, const void* source, size_t size) {
  jbyteArray destination = env->NewByteArray(size);
  env->SetByteArrayRegion(destination, 0, size,
                          static_cast<const jbyte*>(source));
  return destination;
}

void setBuffer(JNIEnv* env, jbyteArray source, unsigned char** destination,
               long long* size) {
  size_t localSize = *size;
  setBuffer(env, source, destination, &localSize);
  *size = localSize;
}

void setBuffer(JNIEnv* env, jbyteArray source, unsigned char** destination,
               size_t* size) {
  delete[] *destination;
  *size = env->GetArrayLength(source);
  *destination = new unsigned char[*size];
  env->GetByteArrayRegion(source, 0, *size,
                          reinterpret_cast<jbyte*>(*destination));
}
