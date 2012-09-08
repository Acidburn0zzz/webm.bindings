// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, AudioTrack, functionName, ##__VA_ARGS__)

FUNCTION(jlong, GetBitDepth, jlong jAudioTrack) {
  mkvparser::AudioTrack* audioTrack =
      reinterpret_cast<mkvparser::AudioTrack*>(jAudioTrack);
  return audioTrack->GetBitDepth();
}

FUNCTION(jlong, GetChannels, jlong jAudioTrack) {
  mkvparser::AudioTrack* audioTrack =
      reinterpret_cast<mkvparser::AudioTrack*>(jAudioTrack);
  return audioTrack->GetChannels();
}

FUNCTION(jdouble, GetSamplingRate, jlong jAudioTrack) {
  mkvparser::AudioTrack* audioTrack =
      reinterpret_cast<mkvparser::AudioTrack*>(jAudioTrack);
  return audioTrack->GetSamplingRate();
}

FUNCTION(jlong, Parse, jlong jSegment, jlong jInfo, jlong element_start,
                       jlong element_size, jlongArray jAudioTrack) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  mkvparser::Track::Info& info =
      *reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  mkvparser::AudioTrack* audioTrack = 0;
  long result = mkvparser::AudioTrack::Parse(segment, info, element_start,
                                             element_size, audioTrack);
  jlong outputAudioTrack = reinterpret_cast<jlong>(audioTrack);
  env->SetLongArrayRegion(jAudioTrack, 0, 1, &outputAudioTrack);
  return result;
}

FUNCTION(jlong, Seek, jlong jAudioTrack, jlong time_ns, jlongArray jResult) {
  mkvparser::AudioTrack* audioTrack =
      reinterpret_cast<mkvparser::AudioTrack*>(jAudioTrack);
  const mkvparser::BlockEntry* result = 0;
  long output = audioTrack->Seek(time_ns, result);
  jlong outputResult = reinterpret_cast<jlong>(result);
  env->SetLongArrayRegion(jResult, 0, 1, &outputResult);
  return output;
}
