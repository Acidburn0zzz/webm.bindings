// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, CuePoint, functionName, ##__VA_ARGS__)

FUNCTION(jlong, block_number, jlong jCuePoint) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  cuePoint->block_number();
}

FUNCTION(jlong, cluster_pos, jlong jCuePoint) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  cuePoint->cluster_pos();
}

FUNCTION(void, deleteCuePoint, jlong jCuePoint) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  delete cuePoint;
}

FUNCTION(jlong, newCuePoint) {
  jlong jCuePoint =
      reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::CuePoint);
  return jCuePoint;
}

FUNCTION(jlong, output_block_number, jlong jCuePoint) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  cuePoint->output_block_number();
}

FUNCTION(void, set_block_number, jlong jCuePoint, jlong block_number) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  cuePoint->set_block_number(block_number);
}

FUNCTION(void, set_cluster_pos, jlong jCuePoint, jlong cluster_pos) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  cuePoint->set_cluster_pos(cluster_pos);
}

FUNCTION(void, set_output_block_number, jlong jCuePoint,
                                        jlong output_block_number) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  cuePoint->set_output_block_number(output_block_number);
}

FUNCTION(void, set_time, jlong jCuePoint, jlong time) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  cuePoint->set_time(time);
}

FUNCTION(void, set_track, jlong jCuePoint, jlong track) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  cuePoint->set_track(track);
}

FUNCTION(jlong, Size, jlong jCuePoint) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  return cuePoint->Size();
}

FUNCTION(jlong, time, jlong jCuePoint) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  cuePoint->time();
}

FUNCTION(jlong, track, jlong jCuePoint) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  cuePoint->track();
}

FUNCTION(jboolean, Write, jlong jCuePoint, jlong jWriter) {
  mkvmuxer::CuePoint* cuePoint =
      reinterpret_cast<mkvmuxer::CuePoint*>(jCuePoint);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return cuePoint->Write(writer);
}
