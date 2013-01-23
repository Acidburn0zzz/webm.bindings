// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "ogg/ogg.h"
#include "vorbis/codec.h"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, Codec, functionName, ##__VA_ARGS__)

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

// The original function (vorbis_analysis_buffer) allocates and returns an area
// of memory for you to copy your samples into.  This is not possible with JNI.
// Instead you pass this function your 2D array of samples, and it will copy
// them into the memory it gets from vorbis_analysis_buffer.
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
                                        jlong jopComm, jlong jopCode) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  ogg_packet* opComm = reinterpret_cast<ogg_packet*>(jopComm);
  ogg_packet* opCode = reinterpret_cast<ogg_packet*>(jopCode);
  return vorbis_analysis_headerout(v, vc, op, opComm, opCode);
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

FUNCTION(jint, vorbisBlockClear, jlong jvb) {
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  return vorbis_block_clear(vb);
}

FUNCTION(jint, vorbisBlockInit, jlong jv, jlong jvb) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  vorbis_block* vb = reinterpret_cast<vorbis_block*>(jvb);
  return vorbis_block_init(v, vb);
}

FUNCTION(void, vorbisCommentAdd, jlong jvc, jstring comment) {
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  const char* nativeComment = env->GetStringUTFChars(comment, 0);
  vorbis_comment_add(vc, nativeComment);
  env->ReleaseStringUTFChars(comment, nativeComment);
}

FUNCTION(void, vorbisCommentAddTag, jlong jvc, jstring tag, jstring contents) {
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  const char* nativeTag = env->GetStringUTFChars(tag, 0);
  const char* nativeContents = env->GetStringUTFChars(contents, 0);
  vorbis_comment_add_tag(vc, nativeTag, nativeContents);
  env->ReleaseStringUTFChars(tag, nativeTag);
  env->ReleaseStringUTFChars(contents, nativeContents);
}

FUNCTION(void, vorbisCommentClear, jlong jvc) {
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  vorbis_comment_clear(vc);
}

FUNCTION(jint, vorbisCommentheaderOut, jlong jvc, jlong jop) {
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  return vorbis_commentheader_out(vc, op);
}

FUNCTION(void, vorbisCommentInit, jlong jvc) {
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  vorbis_comment_init(vc);
}

FUNCTION(jstring, vorbisCommentQuery, jlong jvc, jstring tag, jint count) {
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  const char* nativeTag = env->GetStringUTFChars(tag, 0);
  char* nativeComment = vorbis_comment_query(vc, nativeTag, count);
  env->ReleaseStringUTFChars(tag, nativeTag);
  if (!nativeComment) {
    return 0;
  }
  return env->NewStringUTF(nativeComment);
}

FUNCTION(jint, vorbisCommentQueryCount, jlong jvc, jstring tag) {
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  const char* nativeTag = env->GetStringUTFChars(tag, 0);
  int comments = vorbis_comment_query_count(vc, nativeTag);
  env->ReleaseStringUTFChars(tag, nativeTag);
  return comments;
}

FUNCTION(void, vorbisDspClear, jlong jv) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  vorbis_dsp_clear(v);
}

FUNCTION(jdouble, vorbisGranuleTime, jlong jv, jlong granulepos) {
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

// For vorbisSynthesisLapout and Pcmout, the original function takes a pointer
// to a float** which is changed to point to an array of samples.  Instead, you
// must pass these function a float[][][] and the number of channels.  The
// first element in the float array will be changed to point to a 2D array of
// samples.
FUNCTION(jint, vorbisSynthesisLapout, jlong jv, jobjectArray jpcm,
                                      jint channels) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  if (jpcm == 0) {
    return vorbis_synthesis_lapout(v, 0);
  }
  float** pcm = 0;
  int length = vorbis_synthesis_lapout(v, &pcm);
  jobjectArray output = createDoubleArray(env, channels, length, pcm);
  env->SetObjectArrayElement(jpcm, 0, output);
  return length;
}

FUNCTION(jint, vorbisSynthesisPcmout, jlong jv, jobjectArray jpcm,
                                      jint channels) {
  vorbis_dsp_state* v = reinterpret_cast<vorbis_dsp_state*>(jv);
  if (jpcm == 0) {
    return vorbis_synthesis_pcmout(v, 0);
  }
  float** pcm = 0;
  int length = vorbis_synthesis_pcmout(v, &pcm);
  jobjectArray output = createDoubleArray(env, channels, length, pcm);
  env->SetObjectArrayElement(jpcm, 0, output);
  return length;
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

FUNCTION(jstring, vorbisVersionString) {
  return env->NewStringUTF(vorbis_version_string());
}
