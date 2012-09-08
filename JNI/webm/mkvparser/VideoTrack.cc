// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, VideoTrack, functionName, ##__VA_ARGS__)

FUNCTION(jdouble, GetFrameRate, jlong jVideoTrack) {
  mkvparser::VideoTrack* videoTrack =
      reinterpret_cast<mkvparser::VideoTrack*>(jVideoTrack);
  return videoTrack->GetFrameRate();
}

FUNCTION(jlong, GetHeight, jlong jVideoTrack) {
  mkvparser::VideoTrack* videoTrack =
      reinterpret_cast<mkvparser::VideoTrack*>(jVideoTrack);
  return videoTrack->GetHeight();
}

FUNCTION(jlong, GetWidth, jlong jVideoTrack) {
  mkvparser::VideoTrack* videoTrack =
      reinterpret_cast<mkvparser::VideoTrack*>(jVideoTrack);
  return videoTrack->GetWidth();
}

FUNCTION(jlong, Parse, jlong jSegment, jlong jInfo, jlong element_start,
                       jlong element_size, jlongArray jVideoTrack) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  mkvparser::Track::Info& info =
      *reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  mkvparser::VideoTrack* videoTrack = 0;
  long result = mkvparser::VideoTrack::Parse(segment, info, element_start,
                                             element_size, videoTrack);
  jlong outputVideoTrack = reinterpret_cast<jlong>(videoTrack);
  env->SetLongArrayRegion(jVideoTrack, 0, 1, &outputVideoTrack);
  return result;
}

FUNCTION(jlong, Seek, jlong jVideoTrack, jlong time_ns, jlongArray jResult) {
  mkvparser::VideoTrack* videoTrack =
      reinterpret_cast<mkvparser::VideoTrack*>(jVideoTrack);
  const mkvparser::BlockEntry* result = 0;
  long output = videoTrack->Seek(time_ns, result);
  jlong outputResult = reinterpret_cast<jlong>(result);
  env->SetLongArrayRegion(jResult, 0, 1, &outputResult);
  return output;
}

FUNCTION(jboolean, VetEntry, jlong jVideoTrack, jlong jBlockEntry) {
  mkvparser::VideoTrack* videoTrack =
      reinterpret_cast<mkvparser::VideoTrack*>(jVideoTrack);
  mkvparser::BlockEntry* blockEntry =
      reinterpret_cast<mkvparser::BlockEntry*>(jBlockEntry);
  return videoTrack->VetEntry(blockEntry);
}
