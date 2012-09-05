// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "vorbis/codec.h"

#define FUNCTION(returnType, name, ...) \
  extern "C" { \
    JNIEXPORT returnType Java_com_google_libvorbis_LibVorbisCommon_##name \
        (JNIEnv* env, jobject self, ##__VA_ARGS__); \
  } \
  JNIEXPORT returnType Java_com_google_libvorbis_LibVorbisCommon_##name \
      (JNIEnv* env, jobject self, ##__VA_ARGS__) \

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return JNI_ERR;
  }
  return JNI_VERSION_1_6;
}

FUNCTION(void, deleteVorbisBlock, jlong jvb) {
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  delete vb;
}

FUNCTION(void, deleteVorbisComment, jlong jvc) {
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  delete vc;
}

FUNCTION(void, deleteVorbisDspState, jlong jv) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  delete v;
}

FUNCTION(void, deleteVorbisInfo, jlong jvi) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  delete vi;
}

FUNCTION(jlong, newVorbisBlock) {
  vorbis_block* vb = new (std::nothrow) vorbis_block;
  return reinterpret_cast<jlong>(vb);
}

FUNCTION(jlong, newVorbisComment) {
  vorbis_comment* vc = new (std::nothrow) vorbis_comment;
  return reinterpret_cast<jlong>(vc);
}

FUNCTION(jlong, newVorbisDspState) {
  vorbis_dsp_state* v = new (std::nothrow) vorbis_dsp_state;
  return reinterpret_cast<jlong>(v);
}

FUNCTION(jlong, newVorbisInfo) {
  vorbis_info* vi = new (std::nothrow) vorbis_info;
  return reinterpret_cast<jlong>(vi);
}

FUNCTION(jint, vorbisBlockClear, jlong jvb) {
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  return vorbis_block_clear(vb);
}

FUNCTION(jint, vorbisBlockInit, jlong jv, jlong jvb) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  return vorbis_block_init(v, vb);
}

FUNCTION(void, vorbisDspClear, jlong jv) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  vorbis_dsp_clear(v);
}

FUNCTION(double, vorbisGranuleTime, jlong jv, jlong granulepos) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  return vorbis_granule_time(v, granulepos);
}

FUNCTION(jint, vorbisInfoBlockSize, jlong jvi, jint zo) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  return vorbis_info_blocksize(vi, zo);
}

FUNCTION(void, vorbisInfoClear, jlong jvi) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  vorbis_info_clear(vi);
}

FUNCTION(void, vorbisInfoInit, jlong jvi) {
  vorbis_info* vi = reinterpret_cast<vorbis_info*>(jvi);
  vorbis_info_init(vi);
}

FUNCTION(jstring, vorbisVersionString) {
  return env->NewStringUTF(vorbis_version_string());
}
