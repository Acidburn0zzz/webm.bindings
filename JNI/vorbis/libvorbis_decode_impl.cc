// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "ogg/ogg.h"
#include "vorbis/codec.h"

#define FUNCTION(returnType, name, ...) \
  extern "C" { \
    JNIEXPORT returnType Java_com_google_libvorbis_LibVorbisDecode_##name \
        (JNIEnv* env, jobject self, ##__VA_ARGS__); \
  } \
  JNIEXPORT returnType Java_com_google_libvorbis_LibVorbisDecode_##name \
      (JNIEnv* env, jobject self, ##__VA_ARGS__) \

jobjectArray createDoubleArray(JNIEnv* env, int outerLength, int innerLength,
                               float** data) {
  jclass floatArrayClass = env->FindClass("[F");
  if (!floatArrayClass) {
    return 0;
  }
  jobjectArray outerArray =
      env->NewObjectArray(outerLength, floatArrayClass, 0);
  if (!outerArray) {
    return 0;
  }
  for (int i = 0; i < outerLength; ++i) {
    jfloatArray innerArray = env->NewFloatArray(innerLength);
    if (!innerArray) {
      return 0;
    }
    env->SetFloatArrayRegion(innerArray, 0, innerLength, data[i]);
    env->SetObjectArrayElement(outerArray, i, innerArray);
    env->DeleteLocalRef(innerArray);
  }
  return outerArray;
}

FUNCTION(jlong, vorbisPacketBlocksize, jlong jvi, jlong jop) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  return vorbis_packet_blocksize(vi, op);
}

FUNCTION(jint, vorbisSynthesis, jlong jvb, jlong jop) {
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  return vorbis_synthesis(vb, op);
}

FUNCTION(jint, vorbisSynthesisBlockin, jlong jv, jlong jvb) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  return vorbis_synthesis_blockin(v, vb);
}

FUNCTION(jint, vorbisSynthesisHalfrate, jlong jvi, jint flag) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  return vorbis_synthesis_halfrate(vi, flag);
}

FUNCTION(jint, vorbisSynthesisHalfrateP, jlong jvi) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  return vorbis_synthesis_halfrate_p(vi);
}

FUNCTION(jint, vorbisSynthesisHeaderin, jlong jvi, jlong jvc, jlong jop) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  return vorbis_synthesis_headerin(vi, vc, op);
}

FUNCTION(jint, vorbisSynthesisIdheader, jlong jop) {
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  return vorbis_synthesis_idheader(op);
}

FUNCTION(jint, vorbisSynthesisInit, jlong jv, jlong jvi) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  return vorbis_synthesis_init(v, vi);
}

FUNCTION(jobjectArray, vorbisSynthesisLapout, jlong jv, jint channels) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  float** pcm = 0;
  int length = vorbis_synthesis_lapout(v, &pcm);
  return createDoubleArray(env, channels, length, pcm);
}

FUNCTION(jint, vorbisSynthesisLapoutAvailable, jlong jv) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  return vorbis_synthesis_lapout(v, 0);
}

FUNCTION(jobjectArray, vorbisSynthesisPcmout, jlong jv, jint channels) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  float** pcm = 0;
  int length = vorbis_synthesis_pcmout(v, &pcm);
  return createDoubleArray(env, channels, length, pcm);
}

FUNCTION(jint, vorbisSynthesisPcmoutAvailable, jlong jv) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  return vorbis_synthesis_pcmout(v, 0);
}

FUNCTION(jint, vorbisSynthesisRead, jlong jv, jint samples) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  return vorbis_synthesis_read(v, samples);
}

FUNCTION(jint, vorbisSynthesisRestart, jlong jv) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  return vorbis_synthesis_restart(v);
}

FUNCTION(jint, vorbisSynthesisTrackonly, jlong jvb, jlong jop) {
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  return vorbis_synthesis_trackonly(vb, op);
}
