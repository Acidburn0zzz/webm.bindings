// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "ogg/ogg.h"
#include "vorbis/codec.h"

#define FUNCTION(returnType, name, ...) \
  extern "C" { \
    JNIEXPORT returnType Java_com_google_libvorbis_LibVorbisEncode_##name \
        (JNIEnv* env, jobject self, ##__VA_ARGS__); \
  } \
  JNIEXPORT returnType Java_com_google_libvorbis_LibVorbisEncode_##name \
      (JNIEnv* env, jobject self, ##__VA_ARGS__) \

FUNCTION(jint, vorbisAnalysis, jlong jvb, jlong jop) {
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  return vorbis_analysis(vb, op);
}

FUNCTION(jint, vorbisAnalysisBlockout, jlong jv, jlong jvb) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  return vorbis_analysis_blockout(v, vb);
}

FUNCTION(void, vorbisAnalysisBuffer, jlong jv, jobjectArray samples) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  jfloatArray firstElement =
      static_cast<jfloatArray>(env->GetObjectArrayElement(samples, 0));
  jsize innerLength = env->GetArrayLength(firstElement);
  float** internalSamples = vorbis_analysis_buffer(v, innerLength);
  jsize outerLength = env->GetArrayLength(samples);
  for (int i = 0; i < outerLength; ++i) {
    jfloatArray innerArray =
        static_cast<jfloatArray>(env->GetObjectArrayElement(samples, i));
    env->GetFloatArrayRegion(innerArray, 0, innerLength, internalSamples[i]);
    env->DeleteLocalRef(innerArray);
  }
}

FUNCTION(jint, vorbisAnalysisHeaderout, jlong jv, jlong jvc, jlong jop,
         jlong jop_comm, jlong jop_code) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  ogg_packet* op_comm = reinterpret_cast<ogg_packet*>(jop_comm);
  ogg_packet* op_code = reinterpret_cast<ogg_packet*>(jop_code);
  return vorbis_analysis_headerout(v, vc, op, op_comm, op_code);
}

FUNCTION(jint, vorbisAnalysisInit, jlong jv, jlong jvi) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  return vorbis_analysis_init(v, vi);
}

FUNCTION(jint, vorbisAnalysisWrote, jlong jv, jint vals) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  return vorbis_analysis_wrote(v, vals);
}

FUNCTION(jint, vorbisBitrateAddblock, jlong jvb) {
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  return vorbis_bitrate_addblock(vb);
}

FUNCTION(jint, vorbisBitrateFlushpacket, jlong jv, jlong jop) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  return vorbis_bitrate_flushpacket(v, op);
}
