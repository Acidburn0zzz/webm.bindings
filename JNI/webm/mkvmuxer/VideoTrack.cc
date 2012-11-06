// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, VideoTrack, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteVideoTrack, jlong jVideoTrack) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  delete videoTrack;
}

FUNCTION(jlong, display_height, jlong jVideoTrack) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  return videoTrack->display_height();
}

FUNCTION(jlong, display_width, jlong jVideoTrack) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  return videoTrack->display_width();
}

FUNCTION(jdouble, frame_rate, jlong jVideoTrack) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  return videoTrack->frame_rate();
}

FUNCTION(jlong, height, jlong jVideoTrack) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  return videoTrack->height();
}

FUNCTION(jlong, newVideoTrack, jint jSeed) {
  unsigned int seed = jSeed;
  jlong jVideoTrack =
      reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::VideoTrack(&seed));
  return jVideoTrack;
}

FUNCTION(jlong, PayloadSize, jlong jVideoTrack) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  return videoTrack->PayloadSize();
}

FUNCTION(void, set_display_height, jlong jVideoTrack, jlong height) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  videoTrack->set_display_height(height);
}

FUNCTION(void, set_display_width, jlong jVideoTrack, jlong width) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  videoTrack->set_display_width(width);
}

FUNCTION(void, set_frame_rate, jlong jVideoTrack, jdouble frame_rate) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  videoTrack->set_frame_rate(frame_rate);
}

FUNCTION(void, set_height, jlong jVideoTrack, jlong height) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  videoTrack->set_height(height);
}

FUNCTION(void, set_width, jlong jVideoTrack, jlong width) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  videoTrack->set_width(width);
}

FUNCTION(jboolean, SetStereoMode, jlong jVideoTrack, jlong stereo_mode) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  return videoTrack->SetStereoMode(stereo_mode);
}

FUNCTION(jlong, stereo_mode, jlong jVideoTrack) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  return videoTrack->stereo_mode();
}

FUNCTION(jlong, width, jlong jVideoTrack) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  return videoTrack->width();
}

FUNCTION(jboolean, Write, jlong jVideoTrack, jlong jWriter) {
  mkvmuxer::VideoTrack* videoTrack =
      reinterpret_cast<mkvmuxer::VideoTrack*>(jVideoTrack);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return videoTrack->Write(writer);
}
