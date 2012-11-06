// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, Segment, functionName, ##__VA_ARGS__)

FUNCTION(jlong, AddAudioTrack, jlong jSegment, jint sample_rate, jint channels,
                               jint number) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->AddAudioTrack(sample_rate, channels, number);
}

FUNCTION(jlong, AddChapter, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->AddChapter());
}

FUNCTION(jboolean, AddCuePoint, jlong jSegment, jlong timestamp, jlong track) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->AddCuePoint(timestamp, track);
}

FUNCTION(jboolean, AddFrame, jlong jSegment,
                             jbyteArray jFrame,
                             jlong length,
                             jlong track_number,
                             jlong timestamp_ns,
                             jboolean is_key) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  char* frame = new char[length];
  env->GetByteArrayRegion(jFrame, 0, length, reinterpret_cast<jbyte*>(frame));
  bool result =
      segment->AddFrame(reinterpret_cast<const mkvmuxer::uint8*>(frame), length,
          track_number, timestamp_ns, is_key);
  delete[] frame;
  return result;
}

FUNCTION(jboolean, AddMetadata, jlong jSegment,
                                jbyteArray jFrame,
                                jlong length,
                                jlong track_number,
                                jlong timestamp_ns,
                                jlong duration_ns) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  char* frame = new char[length];
  env->GetByteArrayRegion(jFrame, 0, length, reinterpret_cast<jbyte*>(frame));
  bool result =
      segment->AddMetadata(reinterpret_cast<const mkvmuxer::uint8*>(frame),
          length, track_number, timestamp_ns, duration_ns);
  delete[] frame;
  return result;
}

FUNCTION(jlong, AddTrack, jlong jSegment, jint number) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->AddTrack(number));
}

FUNCTION(jlong, AddVideoTrack, jlong jSegment, jint width, jint height,
                               jint number) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->AddVideoTrack(width, height, number);
}

FUNCTION(jboolean, chunking, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->chunking();
}

FUNCTION(jlong, cues_track, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->cues_track();
}

FUNCTION(jboolean, CuesTrack, jlong jSegment, jlong track_number) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->CuesTrack(track_number);
}

FUNCTION(void, deleteSegment, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  delete segment;
}

FUNCTION(jboolean, Finalize, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->Finalize();
}

FUNCTION(void, ForceNewClusterOnNextFrame, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  segment->ForceNewClusterOnNextFrame();
}

FUNCTION(jlong, GetCues, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->GetCues());
}

FUNCTION(jlong, GetSegmentInfo, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->GetSegmentInfo());
}

FUNCTION(jlong, GetTrackByNumber, jlong jSegment, jlong track_number) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->GetTrackByNumber(track_number));
}

FUNCTION(jboolean, Init, jlong jSegment, jlong jWriter) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return segment->Init(writer);
}

FUNCTION(jlong, max_cluster_duration, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->max_cluster_duration();
}

FUNCTION(jlong, max_cluster_size, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->max_cluster_size();
}

FUNCTION(jboolean, output_cues, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->output_cues();
}

FUNCTION(jlong, newSegment) {
  jlong jSegment =
      reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::Segment);
  return jSegment;
}

FUNCTION(jint, mode, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return segment->mode();
}

FUNCTION(void, OutputCues, jlong jSegment, jboolean output_cues) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  segment->OutputCues(output_cues);
}

FUNCTION(jlong, segment_info, jlong jSegment) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  return reinterpret_cast<jlong>(segment->segment_info());
}

FUNCTION(void, set_max_cluster_duration, jlong jSegment,
                                         jlong max_cluster_duration) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  segment->set_max_cluster_duration(max_cluster_duration);
}

FUNCTION(void, set_max_cluster_size, jlong jSegment, jlong max_cluster_size) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  segment->set_max_cluster_size(max_cluster_size);
}

FUNCTION(void, set_mode, jlong jSegment, jint mode) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  segment->set_mode(static_cast<mkvmuxer::Segment::Mode>(mode));
}

FUNCTION(jboolean, SetChunking, jlong jSegment, jboolean chunking,
                                jstring jFilename) {
  mkvmuxer::Segment* segment = reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  const char* filename = env->GetStringUTFChars(jFilename, 0);
  bool result = segment->SetChunking(chunking, filename);
  env->ReleaseStringUTFChars(jFilename, filename);
  return result;
}
