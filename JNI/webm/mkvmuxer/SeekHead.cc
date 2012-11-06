// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, SeekHead, functionName, ##__VA_ARGS__)

FUNCTION(jboolean, AddSeekEntry, jlong jSeekHead, jint id, jlong pos) {
  mkvmuxer::SeekHead* seekHead =
      reinterpret_cast<mkvmuxer::SeekHead*>(jSeekHead);
  return seekHead->AddSeekEntry(id, pos);
}

FUNCTION(void, deleteSeekHead, jlong jSeekHead) {
  mkvmuxer::SeekHead* seekHead =
      reinterpret_cast<mkvmuxer::SeekHead*>(jSeekHead);
  delete seekHead;
}

FUNCTION(jboolean, Finalize, jlong jSeekHead, jlong jWriter) {
  mkvmuxer::SeekHead* seekHead =
      reinterpret_cast<mkvmuxer::SeekHead*>(jSeekHead);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return seekHead->Finalize(writer);
}

FUNCTION(jlong, newSeekHead) {
  jlong jSeekHead =
      reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::SeekHead);
  return jSeekHead;
}

FUNCTION(jboolean, Write, jlong jSeekHead, jlong jWriter) {
  mkvmuxer::SeekHead* seekHead =
      reinterpret_cast<mkvmuxer::SeekHead*>(jSeekHead);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return seekHead->Write(writer);
}
