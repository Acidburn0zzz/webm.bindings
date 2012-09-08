// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, CuePoint, functionName, ##__VA_ARGS__)

FUNCTION(jlong, Find, jlong jCuePoint, jlong jTrack) {
  mkvparser::CuePoint* cuePoint =
      reinterpret_cast<mkvparser::CuePoint*>(jCuePoint);
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return reinterpret_cast<jlong>(cuePoint->Find(track));
}

FUNCTION(jlong, getElementSize, jlong jCuePoint) {
  mkvparser::CuePoint* cuePoint =
      reinterpret_cast<mkvparser::CuePoint*>(jCuePoint);
  return cuePoint->m_element_size;
}

FUNCTION(jlong, getElementStart, jlong jCuePoint) {
  mkvparser::CuePoint* cuePoint =
      reinterpret_cast<mkvparser::CuePoint*>(jCuePoint);
  return cuePoint->m_element_start;
}

FUNCTION(jlong, GetTime, jlong jCuePoint, jlong jSegment) {
  mkvparser::CuePoint* cuePoint =
      reinterpret_cast<mkvparser::CuePoint*>(jCuePoint);
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return cuePoint->GetTime(segment);
}

FUNCTION(jlong, GetTimeCode, jlong jCuePoint) {
  mkvparser::CuePoint* cuePoint =
      reinterpret_cast<mkvparser::CuePoint*>(jCuePoint);
  return cuePoint->GetTimeCode();
}

FUNCTION(void, Load, jlong jCuePoint, jlong jMkvReader) {
  mkvparser::CuePoint* cuePoint =
      reinterpret_cast<mkvparser::CuePoint*>(jCuePoint);
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  cuePoint->Load(mkvReader);
}

FUNCTION(void, setElementSize, jlong jCuePoint, jlong element_size) {
  mkvparser::CuePoint* cuePoint =
      reinterpret_cast<mkvparser::CuePoint*>(jCuePoint);
  cuePoint->m_element_size = element_size;
}

FUNCTION(void, setElementStart, jlong jCuePoint, jlong element_start) {
  mkvparser::CuePoint* cuePoint =
      reinterpret_cast<mkvparser::CuePoint*>(jCuePoint);
  cuePoint->m_element_start = element_start;
}
