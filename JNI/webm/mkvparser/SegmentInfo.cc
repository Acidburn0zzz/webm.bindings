// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, SegmentInfo, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteSegmentInfo, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  delete segmentInfo;
}

FUNCTION(jlong, GetDuration, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return segmentInfo->GetDuration();
}

FUNCTION(jlong, getElementSize, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return segmentInfo->m_element_size;
}

FUNCTION(jlong, getElementStart, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return segmentInfo->m_element_start;
}

FUNCTION(jstring, GetMuxingAppAsUTF8, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return env->NewStringUTF(segmentInfo->GetMuxingAppAsUTF8());
}

FUNCTION(jlong, getSegment, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return reinterpret_cast<jlong>(segmentInfo->m_pSegment);
}

FUNCTION(jlong, getSize, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return segmentInfo->m_size;
}

FUNCTION(jlong, getStart, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return segmentInfo->m_start;
}

FUNCTION(jlong, GetTimeCodeScale, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return segmentInfo->GetTimeCodeScale();
}

FUNCTION(jstring, GetTitleAsUTF8, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return env->NewStringUTF(segmentInfo->GetTitleAsUTF8());
}

FUNCTION(jstring, GetWritingAppAsUTF8, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return env->NewStringUTF(segmentInfo->GetWritingAppAsUTF8());
}

FUNCTION(jlong, newSegmentInfo, jlong jSegment, jlong start, jlong size,
                                jlong element_start, jlong element_size) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  jlong jSegmentInfo =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::SegmentInfo(
          segment, start, size, element_start, element_size));
  return jSegmentInfo;
}

FUNCTION(jlong, Parse, jlong jSegmentInfo) {
  mkvparser::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvparser::SegmentInfo*>(jSegmentInfo);
  return segmentInfo->Parse();
}
