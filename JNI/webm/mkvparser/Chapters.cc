// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Chapters, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteChapters, jlong jChapters) {
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  delete chapters;
}

FUNCTION(jlong, GetEdition, jlong jChapters, jint index) {
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  return reinterpret_cast<jlong>(chapters->GetEdition(index));
}

FUNCTION(jint, GetEditionCount, jlong jChapters) {
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  return chapters->GetEditionCount();
}

FUNCTION(jlong, getElementSize, jlong jChapters) {
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  return chapters->m_element_size;
}

FUNCTION(jlong, getElementStart, jlong jChapters) {
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  return chapters->m_element_start;
}

FUNCTION(jlong, getSegment, jlong jChapters) {
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  return reinterpret_cast<jlong>(chapters->m_pSegment);
}

FUNCTION(jlong, getSize, jlong jChapters) {
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  return chapters->m_size;
}

FUNCTION(jlong, getStart, jlong jChapters) {
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  return chapters->m_start;
}

FUNCTION(jlong, newChapters, jlong jSegment,
                             jlong payload_start,
                             jlong payload_size,
                             jlong element_start,
                             jlong element_size) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  jlong jChapters =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::Chapters(
          segment, payload_start, payload_size, element_start, element_size));
  return jChapters;
}

FUNCTION(jlong, Parse, jlong jChapters) {
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  return chapters->Parse();
}
