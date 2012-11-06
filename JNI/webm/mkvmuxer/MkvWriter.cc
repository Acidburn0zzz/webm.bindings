// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxertypes.hpp"
#include "mkvwriter.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, MkvWriter, functionName, ##__VA_ARGS__)

FUNCTION(void, Close, jlong jMkvWriter) {
  mkvmuxer::MkvWriter* mkvWriter =
      reinterpret_cast<mkvmuxer::MkvWriter*>(jMkvWriter);
  mkvWriter->Close();
}

FUNCTION(void, deleteMkvWriter, jlong jMkvWriter) {
  mkvmuxer::MkvWriter* mkvWriter =
      reinterpret_cast<mkvmuxer::MkvWriter*>(jMkvWriter);
  delete mkvWriter;
}

FUNCTION(void, ElementStartNotify, jlong jMkvWriter, jlong element_id,
                                   jlong position) {
  mkvmuxer::MkvWriter* mkvWriter =
      reinterpret_cast<mkvmuxer::MkvWriter*>(jMkvWriter);
  mkvWriter->ElementStartNotify(element_id, position);
}

FUNCTION(jlong, GetPosition, jlong jMkvWriter) {
  mkvmuxer::MkvWriter* mkvWriter =
      reinterpret_cast<mkvmuxer::MkvWriter*>(jMkvWriter);
  return mkvWriter->Position();
}

FUNCTION(jlong, newMkvWriter) {
  jlong jMkvWriter =
      reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::MkvWriter);
  return jMkvWriter;
}

FUNCTION(jboolean, Open, jlong jMkvWriter, jstring jFilename) {
  mkvmuxer::MkvWriter* mkvWriter =
      reinterpret_cast<mkvmuxer::MkvWriter*>(jMkvWriter);
  const char* filename = env->GetStringUTFChars(jFilename, 0);
  bool result = mkvWriter->Open(filename);
  env->ReleaseStringUTFChars(jFilename, filename);
  return result;
}

FUNCTION(jboolean, Seekable, jlong jMkvWriter) {
  mkvmuxer::MkvWriter* mkvWriter =
      reinterpret_cast<mkvmuxer::MkvWriter*>(jMkvWriter);
  return mkvWriter->Seekable();
}

FUNCTION(jint, SetPosition, jlong jMkvWriter, jlong position) {
  mkvmuxer::MkvWriter* mkvWriter =
      reinterpret_cast<mkvmuxer::MkvWriter*>(jMkvWriter);
  return mkvWriter->Position(position);
}

FUNCTION(jint, Write, jlong jMkvWriter, jbyteArray jBuffer, jint length) {
  mkvmuxer::MkvWriter* mkvWriter =
      reinterpret_cast<mkvmuxer::MkvWriter*>(jMkvWriter);
  char* buffer = new char[length];
  env->GetByteArrayRegion(jBuffer, 0, length, reinterpret_cast<jbyte*>(buffer));
  mkvmuxer::int32 result = mkvWriter->Write(buffer, length);
  delete[] buffer;
  return result;
}
