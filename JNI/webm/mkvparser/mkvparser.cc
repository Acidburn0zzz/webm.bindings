// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, MkvParser, functionName, ##__VA_ARGS__)

FUNCTION(jlong, GetUIntLength, jlong jMkvReader, jlong position,
                               jlongArray jLength) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  long length = 0;
  long long result = mkvparser::GetUIntLength(mkvReader, position, length);
  jlong outputLength = length;
  env->SetLongArrayRegion(jLength, 0, 1, &outputLength);
  return result;
}

FUNCTION(void, GetVersion, jintArray jMajor, jintArray jMinor, jintArray jBuild,
                           jintArray jRevision) {
  int build = 0;
  int major = 0;
  int minor = 0;
  int revision = 0;
  mkvparser::GetVersion(major, minor, build, revision);
  jint outputBuild = build;
  env->SetIntArrayRegion(jBuild, 0, 1, &outputBuild);
  jint outputMajor = major;
  env->SetIntArrayRegion(jMajor, 0, 1, &outputMajor);
  jint outputMinor = minor;
  env->SetIntArrayRegion(jMinor, 0, 1, &outputMinor);
  jint outputRevision = revision;
  env->SetIntArrayRegion(jRevision, 0, 1, &outputRevision);
}

FUNCTION(jboolean, MatchBuffer, jlong jMkvReader,
                                jlongArray jPosition,
                                jlong id,
                                jobjectArray jBuffer,
                                jlongArray jBufferLength) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  unsigned char* buffer = 0;
  size_t bufferLength = 0;
  long long position = 0;
  bool result = mkvparser::Match(mkvReader, position, id, buffer, bufferLength);
  jbyteArray jBufferElement = env->NewByteArray(bufferLength);
  env->SetByteArrayRegion(jBufferElement, 0, bufferLength,
                          reinterpret_cast<const jbyte*>(buffer));
  env->SetObjectArrayElement(jBuffer, 0, jBufferElement);
  jlong outputBufferLength = bufferLength;
  env->SetLongArrayRegion(jBufferLength, 0, 1, &outputBufferLength);
  jlong outputPosition = position;
  env->SetLongArrayRegion(jPosition, 0, 1, &outputPosition);
  delete[] buffer;
  return result;
}

FUNCTION(jboolean, MatchValue, jlong jMkvReader, jlongArray jPosition, jlong id,
                               jlongArray jValue) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  long long position = 0;
  long long value = 0;
  bool result = mkvparser::Match(mkvReader, position, id, value);
  jlong outputPosition = position;
  env->SetLongArrayRegion(jPosition, 0, 1, &outputPosition);
  jlong outputValue = value;
  env->SetLongArrayRegion(jValue, 0, 1, &outputValue);
  return result;
}

FUNCTION(jlong, ParseElementHeader, jlong jMkvReader,
                                    jlongArray jPosition,
                                    jlong stop,
                                    jlongArray jId,
                                    jlongArray jSize) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  long long id = 0;
  long long position = 0;
  long long size = 0;
  long result =
      mkvparser::ParseElementHeader(mkvReader, position, stop, id, size);
  jlong outputId = id;
  env->SetLongArrayRegion(jId, 0, 1, &outputId);
  jlong outputPosition = position;
  env->SetLongArrayRegion(jPosition, 0, 1, &outputPosition);
  jlong outputSize = size;
  env->SetLongArrayRegion(jSize, 0, 1, &outputSize);
  return result;
}

FUNCTION(jlong, ReadUInt, jlong jMkvReader, jlong position,
                          jlongArray jLength) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  long length = 0;
  long long result = mkvparser::ReadUInt(mkvReader, position, length);
  jlong outputLength = length;
  env->SetLongArrayRegion(jLength, 0, 1, &outputLength);
  return result;
}

FUNCTION(jlong, UnserializeFloat, jlong jMkvReader, jlong position, jlong size,
                                  jdoubleArray jResult) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  double result = 0;
  long output = mkvparser::UnserializeFloat(mkvReader, position, size, result);
  jdouble outputResult = result;
  env->SetDoubleArrayRegion(jResult, 0, 1, &outputResult);
  return output;
}

FUNCTION(jlong, UnserializeInt, jlong jMkvReader, jlong position, jlong length,
                                jlongArray jResult) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  long long result = 0;
  long output = mkvparser::UnserializeInt(mkvReader, position, length, result);
  jlong outputResult = result;
  env->SetLongArrayRegion(jResult, 0, 1, &outputResult);
  return output;
}

FUNCTION(jlong, UnserializeString, jlong jMkvReader, jlong position, jlong size,
                                   jobjectArray jStr) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  char* str = 0;
  long result = mkvparser::UnserializeString(mkvReader, position, size, str);
  jstring jStrElement = env->NewStringUTF(str);
  env->SetObjectArrayElement(jStr, 0, jStrElement);
  delete[] str;
  return result;
}

FUNCTION(jlong, UnserializeUInt, jlong jMkvReader, jlong position, jlong size) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  long long result = mkvparser::UnserializeUInt(mkvReader, position, size);
  return result;
}
