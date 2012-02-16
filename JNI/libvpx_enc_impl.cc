// Copyright 2012 Google Inc. All Rights Reserved.
// Author: frkoenig@google.com (Fritz Koenig)
#include <assert.h>
#include <jni.h>
#include <string.h>

#include "vpx/vpx_encoder.h"
#include "vpx/vp8cx.h"
#include "vpx_ports/mem_ops.h"

#ifdef NDEBUG
# define printf(fmt, ...)
#else
# ifdef ANDROID_NDK
#  include <android/log.h>
#  define printf(fmt, ...) \
   __android_log_print(ANDROID_LOG_DEBUG, "LIBVPX_ENC", fmt, ##__VA_ARGS__)
# else
#  define printf(fmt, ...) \
   printf(fmt "\n", ##__VA_ARGS__)
# endif
#endif

#define FUNC(RETURN_TYPE, NAME, ...) \
  extern "C" { \
  JNIEXPORT RETURN_TYPE Java_com_google_libvpx_LibVpxEnc_ ## NAME \
                      (JNIEnv * env, jobject thiz, ##__VA_ARGS__);\
  } \
  JNIEXPORT RETURN_TYPE Java_com_google_libvpx_LibVpxEnc_ ## NAME \
                      (JNIEnv * env, jobject thiz, ##__VA_ARGS__)\

#define STRING_RETURN(JNI_NAME, LIBVPX_NAME) \
  FUNC(jstring, JNI_NAME) { \
    printf(#JNI_NAME); \
    return env->NewStringUTF(LIBVPX_NAME()); \
  }

static const struct codec_item {
  const char              *name;
  const vpx_codec_iface_t *iface;
  unsigned int             fourcc;
} codecs[] = {
  {"vp8",  &vpx_codec_vp8_cx_algo, 0x30385056},
};

#define SET_ENC_CTL_PARAM(JNI_NAME, CTL_NAME, TYPE) \
  FUNC(int, vpxCodecEncCtlSet ##JNI_NAME, jlong jctx, jint jparam) { \
    printf("vpxCodecEncCtlSet" #JNI_NAME); \
    printf("Setting control parameter " #CTL_NAME " to %d", jparam); \
    vpx_codec_ctx_t *ctx = reinterpret_cast<vpx_codec_ctx_t *>(jctx); \
    return vpx_codec_control(ctx, VP8E_SET_ ##CTL_NAME, (TYPE)jparam); \
  }

SET_ENC_CTL_PARAM(CpuUsed, CPUUSED, int)
SET_ENC_CTL_PARAM(EnableAutoAltRef, ENABLEAUTOALTREF, unsigned int)
SET_ENC_CTL_PARAM(NoiseSensitivity, NOISE_SENSITIVITY, unsigned int)
SET_ENC_CTL_PARAM(Sharpness, SHARPNESS, unsigned int)
SET_ENC_CTL_PARAM(StaticThreshold, STATIC_THRESHOLD, unsigned int)
SET_ENC_CTL_PARAM(TokenPartitions, TOKEN_PARTITIONS, vp8e_token_partitions)
SET_ENC_CTL_PARAM(ARNRMaxFrames, ARNR_MAXFRAMES, unsigned int)
SET_ENC_CTL_PARAM(ARNRStrength, ARNR_STRENGTH, unsigned int)
SET_ENC_CTL_PARAM(ARNRType, ARNR_TYPE, unsigned int)
SET_ENC_CTL_PARAM(Tuning, TUNING, vp8e_tuning)
SET_ENC_CTL_PARAM(CQLevel, CQ_LEVEL, unsigned int)
SET_ENC_CTL_PARAM(MaxIntraBitratePct, MAX_INTRA_BITRATE_PCT, unsigned int)

FUNC(void, vpxCodecEncInit, jlong jctx, jlong jcfg) {
  printf("vpxCodecEncInit");
  vpx_codec_ctx_t *ctx = reinterpret_cast<vpx_codec_ctx_t *>(jctx);
  vpx_codec_enc_cfg_t *cfg = reinterpret_cast<vpx_codec_enc_cfg_t *>(jcfg);
  const struct codec_item *codec = codecs;

  vpx_codec_enc_init(ctx, codec->iface, cfg, 0);
}

FUNC(jboolean, vpxCodecEncode, jlong jctx, jbyteArray jframe,
                               jlong pts, jlong duration,
                               jlong flags, jlong deadline) {
  printf("vpxCodecEncode");
  jboolean isCopy;
  jboolean err = false;
  jbyte *frame = env->GetByteArrayElements(jframe, &isCopy);
  vpx_codec_ctx_t *ctx = reinterpret_cast<vpx_codec_ctx_t *>(jctx);
  vpx_image_t *img = vpx_img_wrap(NULL,
                                  IMG_FMT_I420,
                                  ctx->config.enc->g_w,
                                  ctx->config.enc->g_h,
                                  0,
                                  reinterpret_cast<unsigned char *>(frame));

  if (img) {
    vpx_codec_encode(ctx, img, pts, duration, flags, deadline);
    vpx_img_free(img);
  } else {
    err = true;
  }

  if (isCopy == JNI_TRUE)
    env->ReleaseByteArrayElements(jframe, frame, 0);

  return err;
}

FUNC(jobject, vpxCodecEncGetCxData, jlong jctx) {
  printf("vpxCodecEncGetCxData");
  const vpx_codec_cx_pkt_t *pkt;
  vpx_codec_iter_t iter = NULL;
  vpx_codec_ctx_t *ctx = reinterpret_cast<vpx_codec_ctx_t *>(jctx);

  jclass arrayListClass = env->FindClass("java/util/ArrayList");
  assert(arrayListClass != NULL);

  jmethodID alInitMethodId = env->GetMethodID(arrayListClass, "<init>", "()V");
  assert(alInitMethodId != NULL);

  jobject arrayList = env->NewObject(arrayListClass, alInitMethodId);

  jmethodID alAddMethodId = env->GetMethodID(arrayListClass,
                                             "add", "(Ljava/lang/Object;)Z");
  assert(alAddMethodId != NULL);

  jclass codecCxPkt = env->FindClass("com/google/libvpx/VpxCodecCxPkt");
  assert(codecCxPkt != NULL);

  jmethodID cxInitMethodId = env->GetMethodID(codecCxPkt, "<init>", "(J)V");
  assert(cxInitMethodId != NULL);

  jfieldID bufferId = env->GetFieldID(codecCxPkt, "buffer", "[B");
  assert(bufferId != NULL);

  jfieldID ptsId = env->GetFieldID(codecCxPkt, "pts", "J");
  assert(ptsId != NULL);

  jfieldID durationId = env->GetFieldID(codecCxPkt, "duration", "J");
  assert(durationId != NULL);

  jfieldID flagsId = env->GetFieldID(codecCxPkt, "flags", "I");
  assert(flagsId != NULL);

  jfieldID partitionId = env->GetFieldID(codecCxPkt, "partitionId", "I");
  assert(partitionId != NULL);

  while ((pkt = vpx_codec_get_cx_data(ctx, &iter))) {
    printf("vpxCodecEncGetCxData : Data found!");
    if (pkt->kind == VPX_CODEC_CX_FRAME_PKT) {
      jobject cxPkt = env->NewObject(codecCxPkt,
                                     cxInitMethodId,
                                     pkt->data.frame.sz);

      env->SetIntField(cxPkt, ptsId, pkt->data.frame.pts);
      env->SetIntField(cxPkt, durationId, pkt->data.frame.duration);
      env->SetIntField(cxPkt, flagsId, pkt->data.frame.flags);
      env->SetIntField(cxPkt, partitionId, pkt->data.frame.partition_id);

      jobject jba = env->GetObjectField(cxPkt, bufferId);
      assert(jba != NULL);

      env->SetByteArrayRegion((jbyteArray)jba, 0, pkt->data.frame.sz,
                              reinterpret_cast<jbyte *>(pkt->data.frame.buf));

      env->CallBooleanMethod(arrayList, alAddMethodId, cxPkt);
      env->DeleteLocalRef(cxPkt);
    }
  }

  return arrayList;
}
