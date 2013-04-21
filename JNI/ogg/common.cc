// Author: mszal@google.com (Michael Szal)

#include <jni.h>

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
