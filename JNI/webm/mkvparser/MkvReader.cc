// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvreader.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, MkvReader, functionName, ##__VA_ARGS__)

FUNCTION(void, Close, jlong jMkvReader) {
  mkvparser::MkvReader* mkvReader =
      reinterpret_cast<mkvparser::MkvReader*>(jMkvReader);
  mkvReader->Close();
}

FUNCTION(void, deleteMkvReader, jlong jMkvReader) {
  mkvparser::MkvReader* mkvReader =
      reinterpret_cast<mkvparser::MkvReader*>(jMkvReader);
  delete mkvReader;
}

FUNCTION(jboolean, IsOpen, jlong jMkvReader) {
  mkvparser::MkvReader* mkvReader =
      reinterpret_cast<mkvparser::MkvReader*>(jMkvReader);
  return mkvReader->IsOpen();
}

FUNCTION(jint, Length, jlong jMkvReader, jlongArray jTotal,
                       jlongArray jAvailable) {
  mkvparser::MkvReader* mkvReader =
      reinterpret_cast<mkvparser::MkvReader*>(jMkvReader);
  long long available = 0;
  long long total = 0;
  int result = mkvReader->Length(&total, &available);
  jlong outputAvailable = available;
  env->SetLongArrayRegion(jAvailable, 0, 1, &outputAvailable);
  jlong outputTotal = total;
  env->SetLongArrayRegion(jTotal, 0, 1, &outputTotal);
  return result;
}

FUNCTION(jlong, newMkvReader) {
  jlong jMkvReader =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::MkvReader);
  return jMkvReader;
}

FUNCTION(jint, Open, jlong jMkvReader, jstring jFileName) {
  mkvparser::MkvReader* mkvReader =
      reinterpret_cast<mkvparser::MkvReader*>(jMkvReader);
  const char* fileName = env->GetStringUTFChars(jFileName, 0);
  int result = mkvReader->Open(fileName);
  env->ReleaseStringUTFChars(jFileName, fileName);
  return result;
}

FUNCTION(jint, Read, jlong jMkvReader, jlong position, jlong length,
                     jobjectArray jBuffer) {
  mkvparser::MkvReader* mkvReader =
      reinterpret_cast<mkvparser::MkvReader*>(jMkvReader);
  unsigned char* buffer = new (std::nothrow) unsigned char[length];
  if (!buffer) {
    return -1;
  }

  int result = mkvReader->Read(position, length, buffer);
  if (result) {
    env->SetObjectArrayElement(jBuffer, 0, 0);
    delete[] buffer;
    return result;
  }

  jbyteArray jBufferElement = env->NewByteArray(length);
  env->SetByteArrayRegion(jBufferElement, 0, length,
                          reinterpret_cast<const jbyte*>(buffer));
  env->SetObjectArrayElement(jBuffer, 0, jBufferElement);
  delete[] buffer;
  return result;
}
