// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Cues, functionName, ##__VA_ARGS__)

FUNCTION(jboolean, DoneParsing, jlong jCues) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  return cues->DoneParsing();
}

FUNCTION(jboolean, Find, jlong jCues, jlong time_ns, jlong jTrack,
                         jlongArray jCuePoint, jlongArray jTrackPosition) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  const mkvparser::CuePoint* cuePoint = 0;
  const mkvparser::CuePoint::TrackPosition* trackPosition = 0;
  bool result = cues->Find(time_ns, track, cuePoint, trackPosition);
  jlong outputCuePoint = reinterpret_cast<jlong>(cuePoint);
  env->SetLongArrayRegion(jCuePoint, 0, 1, &outputCuePoint);
  jlong outputTrackPosition = reinterpret_cast<jlong>(trackPosition);
  env->SetLongArrayRegion(jTrackPosition, 0, 1, &outputTrackPosition);
  return result;
}

FUNCTION(jlong, GetCount, jlong jCues) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  return cues->GetCount();
}

FUNCTION(jlong, getElementSize, jlong jCues) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  return cues->m_element_size;
}

FUNCTION(jlong, getElementStart, jlong jCues) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  return cues->m_element_start;
}

FUNCTION(jlong, GetFirst, jlong jCues) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  return reinterpret_cast<jlong>(cues->GetFirst());
}

FUNCTION(jlong, GetLast, jlong jCues) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  return reinterpret_cast<jlong>(cues->GetLast());
}

FUNCTION(jlong, GetNext, jlong jCues, jlong jCurrent) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  mkvparser::CuePoint* current =
      reinterpret_cast<mkvparser::CuePoint*>(jCurrent);
  return reinterpret_cast<jlong>(cues->GetNext(current));
}

FUNCTION(jlong, getSegment, jlong jCues) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  return reinterpret_cast<jlong>(cues->m_pSegment);
}

FUNCTION(jlong, getSize, jlong jCues) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  return cues->m_size;
}

FUNCTION(jlong, getStart, jlong jCues) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  return cues->m_start;
}

FUNCTION(jboolean, LoadCuePoint, jlong jCues) {
  mkvparser::Cues* cues = reinterpret_cast<mkvparser::Cues*>(jCues);
  return cues->LoadCuePoint();
}
