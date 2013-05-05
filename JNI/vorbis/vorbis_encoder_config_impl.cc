// Copyright 2013 Google Inc. All Rights Reserved.
#include <assert.h>
#include <jni.h>
#include <string.h>
#include <new>

#include "vorbis_encoder_config.h"

#ifdef NDEBUG
# define printf(fmt, ...)
#else
# ifdef __ANDROID__
#  include <android/log.h>
#  define printf(fmt, ...) \
   __android_log_print(ANDROID_LOG_DEBUG, "VORBIS_ENC_CFG", fmt, ##__VA_ARGS__)
# else
#  define printf(fmt, ...) \
   printf(fmt "\n", ##__VA_ARGS__)
# endif
#endif

#define FUNC(RETURN_TYPE, NAME, ...) \
  extern "C" { \
  JNIEXPORT RETURN_TYPE Java_com_google_libvorbis_VorbisEncConfig_ ## NAME \
                      (JNIEnv * env, jobject thiz, ##__VA_ARGS__);\
  } \
  JNIEXPORT RETURN_TYPE Java_com_google_libvorbis_VorbisEncConfig_ ## NAME \
                      (JNIEnv * env, jobject thiz, ##__VA_ARGS__)\

#define CONFIG_FIELD(JNI_NAME, FIELD_NAME, TYPE) \
  FUNC(void, vorbisEncSet ##JNI_NAME, jlong jcfg, jint jparam) { \
    printf("vorbisEncSet" #JNI_NAME); \
    printf("Setting cfg->" #FIELD_NAME " = %d", jparam); \
    vorbis::VorbisEncoderConfig *cfg =\
        reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg); \
    cfg->FIELD_NAME = (TYPE)jparam;\
  } \
  FUNC(int, vorbisEncGet ##JNI_NAME, jlong jcfg) { \
    printf("vorbisEncGet" #JNI_NAME); \
    const vorbis::VorbisEncoderConfig *cfg = \
        reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg); \
    printf("Getting cfg->" #FIELD_NAME " = %d", cfg->FIELD_NAME); \
    return cfg->FIELD_NAME;\
  }

CONFIG_FIELD(FormatTag, format_tag, int)
FUNC(void, vorbisEncSetChannels, jlong jcfg, jshort channels) {
  vorbis::VorbisEncoderConfig *cfg =
      reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg);
  cfg->channels = channels;
  cfg->block_align = (cfg->bits_per_sample / 8) * cfg->channels;
  cfg->bytes_per_second = cfg->sample_rate * cfg->block_align;
}

FUNC(jshort, vorbisEncGetChannels, jlong jcfg) {
  vorbis::VorbisEncoderConfig *cfg =
      reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg);
  return cfg->channels;
}

FUNC(void, vorbisEncSetSampleRate, jlong jcfg, jint sample_rate) {
  vorbis::VorbisEncoderConfig *cfg =
      reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg);
  cfg->sample_rate = sample_rate;
  cfg->bytes_per_second = cfg->sample_rate * cfg->block_align;
}

FUNC(jint, vorbisEncGetSampleRate, jlong jcfg) {
  vorbis::VorbisEncoderConfig *cfg =
      reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg);
  return cfg->sample_rate;
}

FUNC(jint, vorbisEncGetBytesPerSecond, jlong jcfg) {
  vorbis::VorbisEncoderConfig *cfg =
      reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg);
  return cfg->bytes_per_second;
}

FUNC(jshort, vorbisEncGetBlockAlign, jlong jcfg) {
  vorbis::VorbisEncoderConfig *cfg =
      reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg);
  return cfg->block_align;
}

FUNC(void, vorbisEncSetBitsPerSample, jlong jcfg, jshort bits_per_sample) {
  vorbis::VorbisEncoderConfig *cfg =
      reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg);
  cfg->bits_per_sample = bits_per_sample;
  cfg->block_align = (cfg->bits_per_sample / 8) * cfg->channels;
  cfg->bytes_per_second = cfg->sample_rate * cfg->block_align;
}

FUNC(jshort, vorbisEncGetBitsPerSample, jlong jcfg) {
  vorbis::VorbisEncoderConfig *cfg =
      reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg);
  return cfg->bits_per_sample;
}

CONFIG_FIELD(AverageBitrate, average_bitrate, int)
CONFIG_FIELD(MinimumBitrate, minimum_bitrate, int)
CONFIG_FIELD(MaximumBitrate, maximum_bitrate, int)

CONFIG_FIELD(BitrateBasedQuality, bitrate_based_quality, bool)
CONFIG_FIELD(ImpulseBlockBias, impulse_block_bias, double)
CONFIG_FIELD(LowpassFrequency, lowpass_frequency, double)

FUNC(jlong, vorbisEncAllocCfg) {
  printf("vorbisEncAllocCfg");

  const vorbis::VorbisEncoderConfig *cfg =
      new (std::nothrow) vorbis::VorbisEncoderConfig;
  return (jlong)cfg;
}

FUNC(void, vorbisEncFreeCfg, jlong jcfg) {
  printf("vorbisEncFreeCfg");

  const vorbis::VorbisEncoderConfig *cfg =
      reinterpret_cast<vorbis::VorbisEncoderConfig*>(jcfg);
  delete cfg;
}
