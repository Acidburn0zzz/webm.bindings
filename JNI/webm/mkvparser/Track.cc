// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <typeinfo>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Track, functionName, ##__VA_ARGS__)

FUNCTION(jlong, Create, jlong jSegment, jlong jInfo, jlong element_start,
                        jlong element_size, jlongArray jTrack) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  mkvparser::Track::Info& info =
      *reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  mkvparser::Track* track = 0;
  long result = mkvparser::Track::Create(segment, info, element_start,
                                         element_size, track);
  jlong outputTrack = reinterpret_cast<jlong>(track);
  env->SetLongArrayRegion(jTrack, 0, 1, &outputTrack);
  return result;
}

FUNCTION(void, deleteTrack, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  delete track;
}

FUNCTION(jint, getClassType, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  int type = 0;
  if (!track) {
    return type;
  }
  const std::type_info& typeInfo = typeid(*track);
  if (typeInfo == typeid(mkvparser::AudioTrack)) {
    type = 1;
  } else if (typeInfo == typeid(mkvparser::Track)) {
    type = 2;
  } else if (typeInfo == typeid(mkvparser::VideoTrack)) {
    type = 3;
  }
  return type;
}

FUNCTION(jstring, GetCodecId, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return env->NewStringUTF(track->GetCodecId());
}

FUNCTION(jstring, GetCodecNameAsUTF8, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return env->NewStringUTF(track->GetCodecNameAsUTF8());
}

FUNCTION(jbyteArray, GetCodecPrivate, jlong jTrack, jlongArray jSize) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  size_t size = 0;
  const unsigned char* codecPrivate = track->GetCodecPrivate(size);
  jlong outputSize = size;
  env->SetLongArrayRegion(jSize, 0, 1, &outputSize);
  return newByteArray(env, codecPrivate, size);
}

FUNCTION(jlong, GetContentEncodingByIndex, jlong jTrack, jlong idx) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return reinterpret_cast<jlong>(track->GetContentEncodingByIndex(idx));
}

FUNCTION(jlong, GetContentEncodingCount, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return track->GetContentEncodingCount();
}

FUNCTION(jlong, getElementSize, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return track->m_element_size;
}

FUNCTION(jlong, getElementStart, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return track->m_element_start;
}

FUNCTION(jlong, GetEOS, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return reinterpret_cast<jlong>(track->GetEOS());
}

FUNCTION(jlong, GetFirst, jlong jTrack, jlongArray jBlockEntry) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  const mkvparser::BlockEntry* blockEntry = 0;
  long result = track->GetFirst(blockEntry);
  jlong outputBlockEntry = reinterpret_cast<jlong>(blockEntry);
  env->SetLongArrayRegion(jBlockEntry, 0, 1, &outputBlockEntry);
  return result;
}

FUNCTION(jboolean, GetLacing, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return track->GetLacing();
}

FUNCTION(jstring, GetNameAsUTF8, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return env->NewStringUTF(track->GetNameAsUTF8());
}

FUNCTION(jlong, GetNext, jlong jTrack, jlong jCurrent, jlongArray jNext) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  mkvparser::BlockEntry* current =
      reinterpret_cast<mkvparser::BlockEntry*>(jCurrent);
  const mkvparser::BlockEntry* next = 0;
  long result = track->GetNext(current, next);
  jlong outputNext = reinterpret_cast<jlong>(next);
  env->SetLongArrayRegion(jNext, 0, 1, &outputNext);
  return result;
}

FUNCTION(jlong, GetNumber, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return track->GetNumber();
}

FUNCTION(jlong, getSegment, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return reinterpret_cast<jlong>(track->m_pSegment);
}

FUNCTION(jlong, GetType, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return track->GetType();
}

FUNCTION(jlong, GetUid, jlong jTrack) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return track->GetUid();
}

FUNCTION(jlong, ParseContentEncodingsEntry, jlong jTrack, jlong start,
                                            jlong size) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return track->ParseContentEncodingsEntry(start, size);
}

FUNCTION(jlong, Seek, jlong jTrack, jlong time_ns, jlongArray jResult) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  const mkvparser::BlockEntry* result = 0;
  long output = track->Seek(time_ns, result);
  jlong outputResult = reinterpret_cast<jlong>(result);
  env->SetLongArrayRegion(jResult, 0, 1, &outputResult);
  return output;
}

FUNCTION(jboolean, VetEntry, jlong jTrack, jlong jBlockEntry) {
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  mkvparser::BlockEntry* blockEntry =
      reinterpret_cast<mkvparser::BlockEntry*>(jBlockEntry);
  return track->VetEntry(blockEntry);
}
