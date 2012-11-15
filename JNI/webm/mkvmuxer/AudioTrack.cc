// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, AudioTrack, functionName, ##__VA_ARGS__)

FUNCTION(jlong, bitDepth, jlong jAudioTrack) {
  mkvmuxer::AudioTrack* audioTrack =
      reinterpret_cast<mkvmuxer::AudioTrack*>(jAudioTrack);
  return audioTrack->bit_depth();
}

FUNCTION(jlong, channels, jlong jAudioTrack) {
  mkvmuxer::AudioTrack* audioTrack =
      reinterpret_cast<mkvmuxer::AudioTrack*>(jAudioTrack);
  return audioTrack->channels();
}

FUNCTION(void, deleteAudioTrack, jlong jAudioTrack) {
  mkvmuxer::AudioTrack* audioTrack =
      reinterpret_cast<mkvmuxer::AudioTrack*>(jAudioTrack);
  delete audioTrack;
}

FUNCTION(jlong, newAudioTrack, jint jSeed) {
  unsigned int seed = jSeed;
  jlong jAudioTrack =
      reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::AudioTrack(&seed));
  return jAudioTrack;
}

FUNCTION(jlong, PayloadSize, jlong jAudioTrack) {
  mkvmuxer::AudioTrack* audioTrack =
      reinterpret_cast<mkvmuxer::AudioTrack*>(jAudioTrack);
  return audioTrack->PayloadSize();
}

FUNCTION(jdouble, sampleRate, jlong jAudioTrack) {
  mkvmuxer::AudioTrack* audioTrack =
      reinterpret_cast<mkvmuxer::AudioTrack*>(jAudioTrack);
  return audioTrack->sample_rate();
}

FUNCTION(void, setBitDepth, jlong jAudioTrack, jlong bit_depth) {
  mkvmuxer::AudioTrack* audioTrack =
      reinterpret_cast<mkvmuxer::AudioTrack*>(jAudioTrack);
  audioTrack->set_bit_depth(bit_depth);
}

FUNCTION(void, setChannels, jlong jAudioTrack, jlong channels) {
  mkvmuxer::AudioTrack* audioTrack =
      reinterpret_cast<mkvmuxer::AudioTrack*>(jAudioTrack);
  audioTrack->set_channels(channels);
}

FUNCTION(void, setSampleRate, jlong jAudioTrack, jdouble sample_rate) {
  mkvmuxer::AudioTrack* audioTrack =
      reinterpret_cast<mkvmuxer::AudioTrack*>(jAudioTrack);
  audioTrack->set_sample_rate(sample_rate);
}

FUNCTION(jboolean, Write, jlong jAudioTrack, jlong jWriter) {
  mkvmuxer::AudioTrack* audioTrack =
      reinterpret_cast<mkvmuxer::AudioTrack*>(jAudioTrack);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return audioTrack->Write(writer);
}
