// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, TrackPosition, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteTrackPosition, jlong jTrackPosition) {
  mkvparser::CuePoint::TrackPosition* trackPosition =
      reinterpret_cast<mkvparser::CuePoint::TrackPosition*>(jTrackPosition);
  delete trackPosition;
}

FUNCTION(jlong, getBlock, jlong jTrackPosition) {
  mkvparser::CuePoint::TrackPosition* trackPosition =
      reinterpret_cast<mkvparser::CuePoint::TrackPosition*>(jTrackPosition);
  return trackPosition->m_block;
}

FUNCTION(jlong, getPos, jlong jTrackPosition) {
  mkvparser::CuePoint::TrackPosition* trackPosition =
      reinterpret_cast<mkvparser::CuePoint::TrackPosition*>(jTrackPosition);
  return trackPosition->m_pos;
}

FUNCTION(jlong, getTrack, jlong jTrackPosition) {
  mkvparser::CuePoint::TrackPosition* trackPosition =
      reinterpret_cast<mkvparser::CuePoint::TrackPosition*>(jTrackPosition);
  return trackPosition->m_track;
}

FUNCTION(jlong, newTrackPosition) {
  jlong jTrackPosition = reinterpret_cast<jlong>(
      new (std::nothrow) mkvparser::CuePoint::TrackPosition);
  return jTrackPosition;
}

FUNCTION(void, Parse, jlong jTrackPosition, jlong jMkvReader, jlong start,
                      jlong size) {
  mkvparser::CuePoint::TrackPosition* trackPosition =
      reinterpret_cast<mkvparser::CuePoint::TrackPosition*>(jTrackPosition);
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  trackPosition->Parse(mkvReader, start, size);
}

FUNCTION(void, setBlock, jlong jTrackPosition, jlong block) {
  mkvparser::CuePoint::TrackPosition* trackPosition =
      reinterpret_cast<mkvparser::CuePoint::TrackPosition*>(jTrackPosition);
  trackPosition->m_block = block;
}

FUNCTION(void, setPos, jlong jTrackPosition, jlong pos) {
  mkvparser::CuePoint::TrackPosition* trackPosition =
      reinterpret_cast<mkvparser::CuePoint::TrackPosition*>(jTrackPosition);
  trackPosition->m_pos = pos;
}

FUNCTION(void, setTrack, jlong jTrackPosition, jlong track) {
  mkvparser::CuePoint::TrackPosition* trackPosition =
      reinterpret_cast<mkvparser::CuePoint::TrackPosition*>(jTrackPosition);
  trackPosition->m_track = track;
}
