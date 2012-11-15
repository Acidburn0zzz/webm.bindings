// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, Tracks, functionName, ##__VA_ARGS__)

FUNCTION(jboolean, AddTrack, jlong jTracks, jlong jTrack, jint number) {
  mkvmuxer::Tracks* tracks = reinterpret_cast<mkvmuxer::Tracks*>(jTracks);
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return tracks->AddTrack(track, number);
}

FUNCTION(void, deleteTracks, jlong jTracks) {
  mkvmuxer::Tracks* tracks = reinterpret_cast<mkvmuxer::Tracks*>(jTracks);
  delete tracks;
}

FUNCTION(jlong, GetTrackByIndex, jlong jTracks, jint idx) {
  mkvmuxer::Tracks* tracks = reinterpret_cast<mkvmuxer::Tracks*>(jTracks);
  return reinterpret_cast<jlong>(tracks->GetTrackByIndex(idx));
}

FUNCTION(jlong, GetTrackByNumber, jlong jTracks, jlong track_number) {
  mkvmuxer::Tracks* tracks = reinterpret_cast<mkvmuxer::Tracks*>(jTracks);
  return reinterpret_cast<jlong>(tracks->GetTrackByNumber(track_number));
}

FUNCTION(jlong, newTracks) {
  jlong jTracks = reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::Tracks);
  return jTracks;
}

FUNCTION(jint, trackEntriesSize, jlong jTracks) {
  mkvmuxer::Tracks* tracks = reinterpret_cast<mkvmuxer::Tracks*>(jTracks);
  return tracks->track_entries_size();
}

FUNCTION(jboolean, TrackIsAudio, jlong jTracks, jlong track_number) {
  mkvmuxer::Tracks* tracks = reinterpret_cast<mkvmuxer::Tracks*>(jTracks);
  return tracks->TrackIsAudio(track_number);
}

FUNCTION(jboolean, TrackIsVideo, jlong jTracks, jlong track_number) {
  mkvmuxer::Tracks* tracks = reinterpret_cast<mkvmuxer::Tracks*>(jTracks);
  return tracks->TrackIsVideo(track_number);
}

FUNCTION(jboolean, Write, jlong jTracks, jlong jWriter) {
  mkvmuxer::Tracks* tracks = reinterpret_cast<mkvmuxer::Tracks*>(jTracks);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return tracks->Write(writer);
}
