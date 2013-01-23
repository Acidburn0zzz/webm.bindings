// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "vorbis/codec.h"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, VorbisInfo, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteVorbisInfo, jlong jVorbisInfo) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  delete vorbisInfo;
}

FUNCTION(jlong, getBitrateLower, jlong jVorbisInfo) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  return vorbisInfo->bitrate_lower;
}

FUNCTION(jlong, getBitrateNominal, jlong jVorbisInfo) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  return vorbisInfo->bitrate_nominal;
}

FUNCTION(jlong, getBitrateUpper, jlong jVorbisInfo) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  return vorbisInfo->bitrate_upper;
}

FUNCTION(jlong, getBitrateWindow, jlong jVorbisInfo) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  return vorbisInfo->bitrate_window;
}

FUNCTION(jint, getChannels, jlong jVorbisInfo) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  return vorbisInfo->channels;
}

FUNCTION(jlong, getCodecSetup, jlong jVorbisInfo) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  return reinterpret_cast<jlong>(vorbisInfo->codec_setup);
}

FUNCTION(jlong, getRate, jlong jVorbisInfo) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  return vorbisInfo->rate;
}

FUNCTION(jint, getVersion, jlong jVorbisInfo) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  return vorbisInfo->version;
}

FUNCTION(jlong, newVorbisInfo) {
  jlong jVorbisInfo = reinterpret_cast<jlong>(new (std::nothrow) vorbis_info);
  return jVorbisInfo;
}

FUNCTION(void, setBitrateLower, jlong jVorbisInfo, jlong bitrateLower) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  vorbisInfo->bitrate_lower = bitrateLower;
}

FUNCTION(void, setBitrateNominal, jlong jVorbisInfo, jlong bitrateNominal) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  vorbisInfo->bitrate_nominal = bitrateNominal;
}

FUNCTION(void, setBitrateUpper, jlong jVorbisInfo, jlong bitrateUpper) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  vorbisInfo->bitrate_upper = bitrateUpper;
}

FUNCTION(void, setBitrateWindow, jlong jVorbisInfo, jlong bitrateWindow) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  vorbisInfo->bitrate_window = bitrateWindow;
}

FUNCTION(void, setChannels, jlong jVorbisInfo, jint channels) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  vorbisInfo->channels = channels;
}

FUNCTION(void, setCodecSetup, jlong jVorbisInfo, jlong codecSetup) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  vorbisInfo->codec_setup = reinterpret_cast<void*>(codecSetup);
}

FUNCTION(void, setRate, jlong jVorbisInfo, jlong rate) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  vorbisInfo->rate = rate;
}

FUNCTION(void, setVersion, jlong jVorbisInfo, jint version) {
  vorbis_info* vorbisInfo = reinterpret_cast<vorbis_info*>(jVorbisInfo);
  vorbisInfo->version = version;
}
