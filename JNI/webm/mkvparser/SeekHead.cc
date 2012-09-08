// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, SeekHead, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteSeekHead, jlong jSeekHead) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  delete seekHead;
}

FUNCTION(jint, GetCount, jlong jSeekHead) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  return seekHead->GetCount();
}

FUNCTION(jlong, getElementSize, jlong jSeekHead) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  return seekHead->m_element_size;
}

FUNCTION(jlong, getElementStart, jlong jSeekHead) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  return seekHead->m_element_start;
}

FUNCTION(jlong, GetEntry, jlong jSeekHead, jint idx) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  return reinterpret_cast<jlong>(seekHead->GetEntry(idx));
}

FUNCTION(jlong, getSegment, jlong jSeekHead) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  return reinterpret_cast<jlong>(seekHead->m_pSegment);
}

FUNCTION(jlong, getSize, jlong jSeekHead) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  return seekHead->m_size;
}

FUNCTION(jlong, getStart, jlong jSeekHead) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  return seekHead->m_start;
}

FUNCTION(jlong, GetVoidElement, jlong jSeekHead, jint idx) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  return reinterpret_cast<jlong>(seekHead->GetVoidElement(idx));
}

FUNCTION(jint, GetVoidElementCount, jlong jSeekHead) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  return seekHead->GetVoidElementCount();
}

FUNCTION(jlong, newSeekHead, jlong jSegment, jlong start, jlong size,
                             jlong element_start, jlong element_size) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  jlong jSeekHead =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::SeekHead(
          segment, start, size, element_start, element_size));
  return jSeekHead;
}

FUNCTION(jlong, Parse, jlong jSeekHead) {
  mkvparser::SeekHead* seekHead =
      reinterpret_cast<mkvparser::SeekHead*>(jSeekHead);
  return seekHead->Parse();
}
