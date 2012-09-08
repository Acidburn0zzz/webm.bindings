// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Entry, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteEntry, jlong jEntry) {
  mkvparser::SeekHead::Entry* entry =
      reinterpret_cast<mkvparser::SeekHead::Entry*>(jEntry);
  delete entry;
}

FUNCTION(jlong, getElementSize, jlong jEntry) {
  mkvparser::SeekHead::Entry* entry =
      reinterpret_cast<mkvparser::SeekHead::Entry*>(jEntry);
  return entry->element_size;
}

FUNCTION(jlong, getElementStart, jlong jEntry) {
  mkvparser::SeekHead::Entry* entry =
      reinterpret_cast<mkvparser::SeekHead::Entry*>(jEntry);
  return entry->element_start;
}

FUNCTION(jlong, getId, jlong jEntry) {
  mkvparser::SeekHead::Entry* entry =
      reinterpret_cast<mkvparser::SeekHead::Entry*>(jEntry);
  return entry->id;
}

FUNCTION(jlong, getPos, jlong jEntry) {
  mkvparser::SeekHead::Entry* entry =
      reinterpret_cast<mkvparser::SeekHead::Entry*>(jEntry);
  return entry->pos;
}

FUNCTION(jlong, newEntry) {
  jlong jEntry =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::SeekHead::Entry);
  return jEntry;
}

FUNCTION(void, setElementSize, jlong jEntry, jlong element_size) {
  mkvparser::SeekHead::Entry* entry =
      reinterpret_cast<mkvparser::SeekHead::Entry*>(jEntry);
  entry->element_size = element_size;
}

FUNCTION(void, setElementStart, jlong jEntry, jlong element_start) {
  mkvparser::SeekHead::Entry* entry =
      reinterpret_cast<mkvparser::SeekHead::Entry*>(jEntry);
  entry->element_start = element_start;
}

FUNCTION(void, setId, jlong jEntry, jlong id) {
  mkvparser::SeekHead::Entry* entry =
      reinterpret_cast<mkvparser::SeekHead::Entry*>(jEntry);
  entry->id = id;
}

FUNCTION(void, setPos, jlong jEntry, jlong pos) {
  mkvparser::SeekHead::Entry* entry =
      reinterpret_cast<mkvparser::SeekHead::Entry*>(jEntry);
  entry->pos = pos;
}
