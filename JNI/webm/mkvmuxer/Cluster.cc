// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"
#include "mkvmuxertypes.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, Cluster, functionName, ##__VA_ARGS__)

FUNCTION(jboolean, AddFrame, jlong jCluster,
                             jbyteArray jFrame,
                             jlong length,
                             jlong track_number,
                             jlong timecode,
                             jboolean is_key) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  char* frame = new char[length];
  env->GetByteArrayRegion(jFrame, 0, length, reinterpret_cast<jbyte*>(frame));
  bool result =
      cluster->AddFrame(reinterpret_cast<const mkvmuxer::uint8*>(frame), length,
          track_number, timecode, is_key);
  delete[] frame;
  return result;
}

FUNCTION(jboolean, AddMetadata, jlong jCluster,
                                jbyteArray jFrame,
                                jlong length,
                                jlong track_number,
                                jlong timecode,
                                jlong duration) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  char* frame = new char[length];
  env->GetByteArrayRegion(jFrame, 0, length, reinterpret_cast<jbyte*>(frame));
  bool result =
      cluster->AddMetadata(reinterpret_cast<const mkvmuxer::uint8*>(frame),
          length, track_number, timecode, duration);
  delete[] frame;
  return result;
}

FUNCTION(void, AddPayloadSize, jlong jCluster, jlong size) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  cluster->AddPayloadSize(size);
}

FUNCTION(jint, blocksAdded, jlong jCluster) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  return cluster->blocks_added();
}

FUNCTION(void, deleteCluster, jlong jCluster) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  delete cluster;
}

FUNCTION(jboolean, Finalize, jlong jCluster) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  return cluster->Finalize();
}

FUNCTION(jboolean, Init, jlong jCluster, jlong jWriter) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return cluster->Init(writer);
}

FUNCTION(jlong, newCluster, jlong timecode, jlong cues_pos) {
  jlong jCluster = reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::Cluster(
      timecode, cues_pos));
  return jCluster;
}

FUNCTION(jlong, payloadSize, jlong jCluster) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  return cluster->payload_size();
}

FUNCTION(jlong, positionForCues, jlong jCluster) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  return cluster->position_for_cues();
}

FUNCTION(jlong, Size, jlong jCluster) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  return cluster->Size();
}

FUNCTION(jlong, timecode, jlong jCluster) {
  mkvmuxer::Cluster* cluster = reinterpret_cast<mkvmuxer::Cluster*>(jCluster);
  return cluster->timecode();
}
