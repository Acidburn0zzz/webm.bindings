
#include <jni.h>

#include "common.h"
#include "ogg/ogg.h"
#include "vorbis/codec.h"
#include "vorbis/vorbisenc.h"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, VorbisEnc, functionName, ##__VA_ARGS__)

FUNCTION(jint, vorbisEncodeSetupManaged, jlong jvi, jlong channels, jlong rate,
		 jlong maxBitrate, jlong nominalBitrate, jlong minBitrate) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  return vorbis_encode_setup_managed(vi, channels, rate, maxBitrate,
		                             nominalBitrate, minBitrate);
}

FUNCTION(jint, vorbisEncodeSetupInit, jlong jvi) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  return vorbis_encode_setup_init(vi);
}

FUNCTION(jint, vorbisEncodeCtlSetNull, jlong jvi, jint number) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  return vorbis_encode_ctl(vi, number, NULL);
}

FUNCTION(jint, vorbisEncodeCtlSetInt, jlong jvi, jint number, jint arg) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  return vorbis_encode_ctl(vi, number, &arg);
}

FUNCTION(jint, vorbisEncodeCtlSetDouble, jlong jvi, jint number, jdouble arg) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  return vorbis_encode_ctl(vi, number, &arg);
}
