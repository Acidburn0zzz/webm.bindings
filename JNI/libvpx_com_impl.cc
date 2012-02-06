// Copyright 2012 Google Inc. All Rights Reserved.
// Author: frkoenig@google.com (Fritz Koenig)
#include <jni.h>
#include <string.h>
#include <new>

#include "vpx/vpx_codec.h"

#ifdef NDEBUG
# define printf(fmt, ...)
#else
# ifdef ANDROID_NDK
#  include <android/log.h>
#  define printf(fmt, ...) \
   __android_log_print(ANDROID_LOG_DEBUG, "LIBVPX_COM", fmt, ##__VA_ARGS__)
# else
#  define printf(fmt, ...) \
   printf(fmt "\n", ##__VA_ARGS__)
# endif
#endif

#define FUNC(RETURN_TYPE, NAME, ...) \
  extern "C" { \
  JNIEXPORT RETURN_TYPE Java_com_google_libvpx_LibVpxCom_ ## NAME \
                      (JNIEnv * env, jobject thiz, ##__VA_ARGS__);\
  } \
  JNIEXPORT RETURN_TYPE Java_com_google_libvpx_LibVpxCom_ ## NAME \
                      (JNIEnv * env, jobject thiz, ##__VA_ARGS__)\

#define STRING_RETURN(JNI_NAME, LIBVPX_NAME) \
  FUNC(jstring, JNI_NAME) { \
    printf(#JNI_NAME); \
    return env->NewStringUTF(LIBVPX_NAME()); \
  }

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
  JNIEnv* env;
  if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return -1;
  }

  // Get jclass with env->FindClass.
  // Register methods with env->RegisterNatives.

  return JNI_VERSION_1_6;
}

STRING_RETURN(vpxCodecVersionStr, vpx_codec_version_str)
STRING_RETURN(vpxCodecVersionExtraStr, vpx_codec_version_extra_str)
STRING_RETURN(vpxCodecBuildConfig, vpx_codec_build_config)

FUNC(jstring, vpxCodecIfaceName, jlong jiface) {
  const vpx_codec_iface_t *iface =
      reinterpret_cast<vpx_codec_iface_t *>(jiface);

  return env->NewStringUTF(vpx_codec_iface_name(iface));
}

FUNC(jboolean, vpxCodecIsError, jlong jctx) {
  const vpx_codec_ctx_t *ctx = reinterpret_cast<vpx_codec_ctx_t *>(jctx);

  if (ctx->err)
    return true;

  return false;
}

FUNC(jstring, vpxCodecErrToString, jint jerr) {
  const vpx_codec_err_t err = (vpx_codec_err_t)jerr;

  return env->NewStringUTF(vpx_codec_err_to_string(err));
}

FUNC(jstring, vpxCodecError, jlong jctx) {
  vpx_codec_ctx_t *ctx = reinterpret_cast<vpx_codec_ctx_t *>(jctx);

  return env->NewStringUTF(vpx_codec_error(ctx));
}

FUNC(jstring, vpxCodecErrorDetail, jlong jctx) {
  vpx_codec_ctx_t *ctx = reinterpret_cast<vpx_codec_ctx_t *>(jctx);

  return env->NewStringUTF(vpx_codec_error_detail(ctx));
}

FUNC(jlong, vpxCodecAllocCodec) {
  printf("vpxCodecAllocCodec");
  const vpx_codec_ctx_t *codec = new (std::nothrow) vpx_codec_ctx_t;

  return (intptr_t)codec;
}

FUNC(void, vpxCodecFreeCodec, jlong jcodec) {
  printf("vpxCodecFreeCodec");
  const vpx_codec_ctx_t *codec = reinterpret_cast<vpx_codec_ctx_t*>(jcodec);

  delete codec;
}

FUNC(jlong, vpxCodecAllocVpxImageI420, jint width, jint height) {
  printf("vpxCodecAllocVpxImageI420");
  vpx_image_t *img = new (std::nothrow) vpx_image_t;
  vpx_img_alloc(img, VPX_IMG_FMT_I420, width, height, 1);

  return (intptr_t)img;
}

FUNC(void, vpxCodecFreeVpxImage, jlong jimg) {
  printf("vpxCodecFreeVpxImage");
  vpx_image_t *img = reinterpret_cast<vpx_image_t*>(jimg);

  if (img != 0) {
    vpx_img_free(img);
    delete img;
  }
}

FUNC(void, vpxCodecFillVpxImage, jlong jimg, jbyteArray jframe) {
  printf("vpxCodecFillVpxImage");
  const vpx_image_t *img = reinterpret_cast<vpx_image_t*>(jimg);
  jboolean isCopy;
  jbyte *frame = env->GetByteArrayElements(jframe, &isCopy);
  jbyte *framePtr = frame;

  for (int plane = 0; plane < 3; plane++) {
    unsigned char *ptr;
    const int w = (plane ? (1 + img->d_w) / 2 : img->d_w);
    const int h = (plane ? (1 + img->d_h) / 2 : img->d_h);

    /* Determine the correct plane based on the image format. The for-loop
      * always counts in Y,U,V order, but this may not match the order of
      * the data on disk.
      */
    switch (plane) {
      case 1:
        ptr = img->planes[(img->fmt == VPX_IMG_FMT_YV12) ?
                                      VPX_PLANE_V : VPX_PLANE_U];
        break;
      case 2:
        ptr = img->planes[(img->fmt == VPX_IMG_FMT_YV12) ?
                                      VPX_PLANE_U : VPX_PLANE_V];
        break;
      default:
        ptr = img->planes[plane];
    }

    for (int r = 0; r < h; r++) {
      memcpy(ptr, framePtr, w);
      ptr += img->stride[plane];
      framePtr += w;
    }
  }

  if (isCopy == JNI_TRUE)
    env->ReleaseByteArrayElements(jframe, frame, 0);
}

FUNC(jint, vpxCodecDestroy, jlong jctx) {
  printf("vpxCodecDestroy");
  vpx_codec_ctx_t *ctx = reinterpret_cast<vpx_codec_ctx_t *>(jctx);

  return vpx_codec_destroy(ctx);
}

FUNC(jint, vpxCodecControl, jlong jctx, jint arg0, jint arg1) {
  printf("vpxCodecControl");
  vpx_codec_ctx_t *ctx = reinterpret_cast<vpx_codec_ctx_t *>(jctx);

  return vpx_codec_control_(ctx, arg0, arg1);
}
