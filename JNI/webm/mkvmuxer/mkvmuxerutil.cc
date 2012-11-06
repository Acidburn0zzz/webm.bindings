// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "mkvmuxer.hpp"
#include "mkvmuxertypes.hpp"
#include "mkvmuxerutil.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, MkvMuxer, functionName, ##__VA_ARGS__)

FUNCTION(jlong, EbmlElementSizeBuffer, jlong type, jbyteArray jValue,
                                       jlong size) {
  char* value = new char[size];
  env->GetByteArrayRegion(jValue, 0, size, reinterpret_cast<jbyte*>(value));
  mkvmuxer::uint64 result = mkvmuxer::EbmlElementSize(type, value);
  delete[] value;
  return result;
}

FUNCTION(jlong, EbmlElementSizeFloat, jlong type, jfloat value) {
  return mkvmuxer::EbmlElementSize(type, value);
}

FUNCTION(jlong, EbmlElementSizeLong, jlong type, jlong jValue) {
  mkvmuxer::uint64 value = jValue;
  return mkvmuxer::EbmlElementSize(type, value);
}

FUNCTION(jlong, EbmlElementSizeString, jlong type, jstring jValue) {
  const char* value = env->GetStringUTFChars(jValue, 0);
  mkvmuxer::uint64 result = mkvmuxer::EbmlElementSize(type, value);
  env->ReleaseStringUTFChars(jValue, value);
  return result;
}

FUNCTION(jlong, EbmlMasterElementSize, jlong type, jlong value) {
  return mkvmuxer::EbmlMasterElementSize(type, value);
}

FUNCTION(void, GetVersion, jintArray jMajor, jintArray jMinor, jintArray jBuild,
                           jintArray jRevision) {
  int build = 0;
  int major = 0;
  int minor = 0;
  int revision = 0;
  mkvmuxer::GetVersion(&major, &minor, &build, &revision);
  jint outputBuild = build;
  env->SetIntArrayRegion(jBuild, 0, 1, &outputBuild);
  jint outputMajor = major;
  env->SetIntArrayRegion(jMajor, 0, 1, &outputMajor);
  jint outputMinor = minor;
  env->SetIntArrayRegion(jMinor, 0, 1, &outputMinor);
  jint outputRevision = revision;
  env->SetIntArrayRegion(jRevision, 0, 1, &outputRevision);
}

FUNCTION(jlong, MakeUID, jint jSeed) {
  unsigned int seed = jSeed;
  return mkvmuxer::MakeUID(&seed);
}

FUNCTION(jint, SerializeInt, jlong jWriter, jlong value, jint size) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return mkvmuxer::SerializeInt(writer, value, size);
}

FUNCTION(jboolean, WriteEbmlElementBuffer, jlong jWriter, jlong type,
                                           jbyteArray jValue, jlong size) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  char* value = new char[size];
  env->GetByteArrayRegion(jValue, 0, size, reinterpret_cast<jbyte*>(value));
  bool result = mkvmuxer::WriteEbmlElement(writer, type, value);
  delete[] value;
  return result;
}

FUNCTION(jboolean, WriteEbmlElementFloat, jlong jWriter, jlong type,
                                          jfloat value) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return mkvmuxer::WriteEbmlElement(writer, type, value);
}

FUNCTION(jboolean, WriteEbmlElementLong, jlong jWriter, jlong type,
                                         jlong jValue) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  mkvmuxer::uint64 value = jValue;
  return mkvmuxer::WriteEbmlElement(writer, type, value);
}

FUNCTION(jboolean, WriteEbmlElementString, jlong jWriter, jlong type,
                                           jstring jValue) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  const char* value = env->GetStringUTFChars(jValue, 0);
  bool result = mkvmuxer::WriteEbmlElement(writer, type, value);
  env->ReleaseStringUTFChars(jValue, value);
  return result;
}

FUNCTION(jboolean, WriteEbmlMasterElement, jlong jWriter, jlong value,
                                           jlong size) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return mkvmuxer::WriteEbmlMasterElement(writer, value, size);
}

FUNCTION(jint, WriteID, jlong jWriter, jlong type) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return mkvmuxer::WriteID(writer, type);
}

FUNCTION(jlong, WriteMetadataBlock, jlong jWriter,
                                    jbyteArray jData,
                                    jlong length,
                                    jlong track_number,
                                    jlong timecode,
                                    jlong duration_timecode) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  char* data = new char[length];
  env->GetByteArrayRegion(jData, 0, length, reinterpret_cast<jbyte*>(data));
  mkvmuxer::uint64 result = mkvmuxer::WriteMetadataBlock(writer,
      reinterpret_cast<const mkvmuxer::uint8*>(data), length, track_number,
      timecode, duration_timecode);
  delete[] data;
  return result;
}

FUNCTION(jlong, WriteSimpleBlock, jlong jWriter,
                                  jbyteArray jData,
                                  jlong length,
                                  jlong track_number,
                                  jlong timecode,
                                  jlong is_key) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  char* data = new char[length];
  env->GetByteArrayRegion(jData, 0, length, reinterpret_cast<jbyte*>(data));
  mkvmuxer::uint64 result = mkvmuxer::WriteSimpleBlock(writer,
      reinterpret_cast<const mkvmuxer::uint8*>(data), length, track_number,
      timecode, is_key);
  delete[] data;
  return result;
}

FUNCTION(jint, WriteUInt, jlong jWriter, jlong value) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return mkvmuxer::WriteUInt(writer, value);
}

FUNCTION(jint, WriteUIntSize, jlong jWriter, jlong value, jint size) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return mkvmuxer::WriteUIntSize(writer, value, size);
}

FUNCTION(jlong, WriteVoidElement, jlong jWriter, jlong size) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return mkvmuxer::WriteVoidElement(writer, size);
}
