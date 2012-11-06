// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>
#include <typeinfo>

#include "common.h"
#include "mkvmuxer.hpp"
#include "mkvmuxertypes.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, Track, functionName, ##__VA_ARGS__)

FUNCTION(jboolean, AddContentEncoding, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return track->AddContentEncoding();
}

FUNCTION(jstring, codec_id, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return env->NewStringUTF(track->codec_id());
}

FUNCTION(jbyteArray, codec_private, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return newByteArray(env, track->codec_private(),
                      track->codec_private_length());
}

FUNCTION(jlong, codec_private_length, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return track->codec_private_length();
}

FUNCTION(jint, content_encoding_entries_size, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return track->content_encoding_entries_size();
}

FUNCTION(void, deleteTrack, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  delete track;
}

FUNCTION(jint, getClassType, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  const std::type_info& typeInfo = typeid(*track);
  int type = 0;
  if (typeInfo == typeid(mkvmuxer::AudioTrack)) {
    type = 1;
  } else if (typeInfo == typeid(mkvmuxer::Track)) {
    type = 2;
  } else if (typeInfo == typeid(mkvmuxer::VideoTrack)) {
    type = 3;
  }
  return type;
}

FUNCTION(jlong, GetContentEncodingByIndex, jlong jTrack, jint index) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return reinterpret_cast<jlong>(track->GetContentEncodingByIndex(index));
}

FUNCTION(jstring, language, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return env->NewStringUTF(track->language());
}

FUNCTION(jstring, name, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return env->NewStringUTF(track->name());
}

FUNCTION(jlong, newTrack, jint jSeed) {
  unsigned int seed = jSeed;
  jlong jTrack =
      reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::Track(&seed));
  return jTrack;
}

FUNCTION(jlong, number, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return track->number();
}

FUNCTION(jlong, PayloadSize, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return track->PayloadSize();
}

FUNCTION(void, set_codec_id, jlong jTrack, jstring jCodecId) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  const char* codecId = env->GetStringUTFChars(jCodecId, 0);
  track->set_codec_id(codecId);
  env->ReleaseStringUTFChars(jCodecId, codecId);
}

FUNCTION(void, set_language, jlong jTrack, jstring jLanguage) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  const char* language = env->GetStringUTFChars(jLanguage, 0);
  track->set_language(language);
  env->ReleaseStringUTFChars(jLanguage, language);
}

FUNCTION(void, set_name, jlong jTrack, jstring jName) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  const char* name = env->GetStringUTFChars(jName, 0);
  track->set_name(name);
  env->ReleaseStringUTFChars(jName, name);
}

FUNCTION(void, set_number, jlong jTrack, jlong number) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  track->set_number(number);
}

FUNCTION(void, set_type, jlong jTrack, jlong type) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  track->set_type(type);
}

FUNCTION(jboolean, SetCodecPrivate, jlong jTrack, jbyteArray jCodecPrivate,
                                    jlong length) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  char* codecPrivate = new char[length];
  env->GetByteArrayRegion(jCodecPrivate, 0, length,
                          reinterpret_cast<jbyte*>(codecPrivate));
  bool result = track->SetCodecPrivate(
      reinterpret_cast<const mkvmuxer::uint8*>(codecPrivate), length);
  delete[] codecPrivate;
  return result;
}

FUNCTION(jlong, Size, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return track->Size();
}

FUNCTION(jlong, type, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return track->type();
}

FUNCTION(jlong, uid, jlong jTrack) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  return track->uid();
}

FUNCTION(jboolean, Write, jlong jTrack, jlong jWriter) {
  mkvmuxer::Track* track = reinterpret_cast<mkvmuxer::Track*>(jTrack);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return track->Write(writer);
}
