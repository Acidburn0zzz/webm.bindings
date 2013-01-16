// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <string.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Segment, functionName, ##__VA_ARGS__)

FUNCTION(jlong, CreateInstance, jlong jMkvReader, jlong position,
                                jlongArray jSegment) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  mkvparser::Segment* segment = 0;
  long long result =
      mkvparser::Segment::CreateInstance(mkvReader, position, segment);
  jlong outputSegment = reinterpret_cast<jlong>(segment);
  env->SetLongArrayRegion(jSegment, 0, 1, &outputSegment);
  return result;
}

FUNCTION(void, deleteSegment, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  delete segment;
}

FUNCTION(jboolean, DoneParsing, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return segment->DoneParsing();
}

FUNCTION(jlong, FindCluster, jlong jSegment, jlong time_nanoseconds) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->FindCluster(time_nanoseconds));
}

FUNCTION(jlong, FindOrPreloadCluster, jlong jSegment, jlong position) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->FindOrPreloadCluster(position));
}

FUNCTION(jlong, GetChapters, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->GetChapters());
}

FUNCTION(jlong, GetCount, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return segment->GetCount();
}

FUNCTION(jlong, GetCues, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->GetCues());
}

FUNCTION(jlong, GetDuration, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return segment->GetDuration();
}

FUNCTION(jlong, getElementStart, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return segment->m_element_start;
}

FUNCTION(jlong, getEos, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(&segment->m_eos);
}

FUNCTION(jlong, GetFirst, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->GetFirst());
}

FUNCTION(jlong, GetInfo, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->GetInfo());
}

FUNCTION(jlong, GetLast, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->GetLast());
}

FUNCTION(jlong, GetNext, jlong jSegment, jlong jCurrent) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  mkvparser::Cluster* current = reinterpret_cast<mkvparser::Cluster*>(jCurrent);
  return reinterpret_cast<jlong>(segment->GetNext(current));
}

FUNCTION(jlong, getReader, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->m_pReader);
}

FUNCTION(jlong, GetSeekHead, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->GetSeekHead());
}

FUNCTION(jlong, getSize, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return segment->m_size;
}

FUNCTION(jlong, getStart, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return segment->m_start;
}

FUNCTION(jlong, GetTracks, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->GetTracks());
}

FUNCTION(jlong, Load, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return segment->Load();
}

FUNCTION(jlong, LoadClusterAndPosition, jlong jSegment, jlongArray jPosition,
                                        jlongArray jSize) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  long long position = 0;
  long size = 0;
  long result = segment->LoadCluster(position, size);
  jlong outputPosition = position;
  env->SetLongArrayRegion(jPosition, 0, 1, &outputPosition);
  jlong outputSize = size;
  env->SetLongArrayRegion(jSize, 0, 1, &outputSize);
  return result;
}

FUNCTION(jlong, LoadClusterWithoutPosition, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return segment->LoadCluster();
}

FUNCTION(jlong, ParseCues, jlong jSegment, jlong cues_off, jlongArray jPosition,
                           jlongArray jLength) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  long long position = 0;
  long length = 0;
  long result = segment->ParseCues(cues_off, position, length);
  jlong outputPosition = position;
  env->SetLongArrayRegion(jPosition, 0, 1, &outputPosition);
  jlong outputLength = length;
  env->SetLongArrayRegion(jLength, 0, 1, &outputLength);
  return result;
}

FUNCTION(jlong, ParseHeaders, jlong jSegment) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return segment->ParseHeaders();
}

FUNCTION(jlong, ParseNext, jlong jSegment, jlong jCurrent, jlongArray jNext,
                           jlongArray jPosition, jlongArray jSize) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  mkvparser::Cluster* current = reinterpret_cast<mkvparser::Cluster*>(jCurrent);
  const mkvparser::Cluster* next = 0;
  long long position = 0;
  long size = 0;
  long result = segment->ParseNext(current, next, position, size);
  jlong outputNext = reinterpret_cast<jlong>(next);
  env->SetLongArrayRegion(jNext, 0, 1, &outputNext);
  jlong outputPosition = position;
  env->SetLongArrayRegion(jPosition, 0, 1, &outputPosition);
  jlong outputSize = size;
  env->SetLongArrayRegion(jSize, 0, 1, &outputSize);
  return result;
}

FUNCTION(void, setEos, jlong jSegment, jlong jEos) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  mkvparser::Cluster* eos = reinterpret_cast<mkvparser::Cluster*>(jEos);
  memcpy(&segment->m_eos, reinterpret_cast<const void*>(eos),
         sizeof(segment->m_eos));
}
