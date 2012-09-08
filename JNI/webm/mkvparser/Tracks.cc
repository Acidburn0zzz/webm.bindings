// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Tracks, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteTracks, jlong jTracks) {
  mkvparser::Tracks* tracks = reinterpret_cast<mkvparser::Tracks*>(jTracks);
  delete tracks;
}

FUNCTION(jlong, getElementSize, jlong jTracks) {
  mkvparser::Tracks* tracks = reinterpret_cast<mkvparser::Tracks*>(jTracks);
  return tracks->m_element_size;
}

FUNCTION(jlong, getElementStart, jlong jTracks) {
  mkvparser::Tracks* tracks = reinterpret_cast<mkvparser::Tracks*>(jTracks);
  return tracks->m_element_start;
}

FUNCTION(jlong, getSegment, jlong jTracks) {
  mkvparser::Tracks* tracks = reinterpret_cast<mkvparser::Tracks*>(jTracks);
  return reinterpret_cast<jlong>(tracks->m_pSegment);
}

FUNCTION(jlong, getSize, jlong jTracks) {
  mkvparser::Tracks* tracks = reinterpret_cast<mkvparser::Tracks*>(jTracks);
  return tracks->m_size;
}

FUNCTION(jlong, getStart, jlong jTracks) {
  mkvparser::Tracks* tracks = reinterpret_cast<mkvparser::Tracks*>(jTracks);
  return tracks->m_start;
}

FUNCTION(jlong, GetTrackByIndex, jlong jTracks, jlong idx) {
  mkvparser::Tracks* tracks = reinterpret_cast<mkvparser::Tracks*>(jTracks);
  return reinterpret_cast<jlong>(tracks->GetTrackByIndex(idx));
}

FUNCTION(jlong, GetTrackByNumber, jlong jTracks, jlong tn) {
  mkvparser::Tracks* tracks = reinterpret_cast<mkvparser::Tracks*>(jTracks);
  return reinterpret_cast<jlong>(tracks->GetTrackByNumber(tn));
}

FUNCTION(jlong, GetTracksCount, jlong jTracks) {
  mkvparser::Tracks* tracks = reinterpret_cast<mkvparser::Tracks*>(jTracks);
  return tracks->GetTracksCount();
}

FUNCTION(jlong, newTracks, jlong jSegment, jlong start, jlong size,
                           jlong element_start, jlong element_size) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  jlong jTracks = reinterpret_cast<jlong>(new (std::nothrow) mkvparser::Tracks(
      segment, start, size, element_start, element_size));
  return jTracks;
}

FUNCTION(jlong, Parse, jlong jTracks) {
  mkvparser::Tracks* tracks = reinterpret_cast<mkvparser::Tracks*>(jTracks);
  return tracks->Parse();
}
