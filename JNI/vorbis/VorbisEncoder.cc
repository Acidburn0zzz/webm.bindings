#include <jni.h>
#include <new>

#include "common.h"
#include "vorbis/codec.h"
#include "vorbis_encoder.h"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, VorbisEncoderC, functionName, ##__VA_ARGS__)

jobjectArray createByteArray(JNIEnv* env, int outerLength, int innerLength,
                             unsigned char** data) {
  jclass byteArrayClass = env->FindClass("[B");
  if (!byteArrayClass) {
    return 0;
  }
  jobjectArray outerArray =
      env->NewObjectArray(outerLength, byteArrayClass, 0);
  if (!outerArray) {
    return 0;
  }
  for (int i = 0; i < outerLength; ++i) {
    jbyteArray innerArray = env->NewByteArray(innerLength);
    if (!innerArray) {
      return 0;
    }
    env->SetByteArrayRegion(innerArray, 0, innerLength,
                            reinterpret_cast<const jbyte*>(data[i]));
    env->SetObjectArrayElement(outerArray, i, innerArray);
    env->DeleteLocalRef(innerArray);
  }
  return outerArray;
}

FUNCTION(void, deleteVorbisEncoder, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  delete encoder;
}

FUNCTION(jlong, newVorbisEncoder) {
  jlong jVorbisEncoder =
      reinterpret_cast<jlong>(new (std::nothrow) vorbis::VorbisEncoder);
  return jVorbisEncoder;
}

FUNCTION(jboolean, Init, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->Init();
}


FUNCTION(jboolean, Encode, jlong jVorbisEncoder, jbyteArray jBuffer,
         jint length) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  unsigned char* buffer = new unsigned char[length];
  env->GetByteArrayRegion(jBuffer, 0, length,
                          reinterpret_cast<jbyte*>(buffer));
  bool result = encoder->Encode(buffer, length);
  delete [] buffer;
  return result;
}

FUNCTION(jbyteArray, ReadCompressedAudio, jlong jVorbisEncoder,
         jlongArray jTimestamp) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);

  unsigned char* data;
  int length;
  int64_t timestamp;
  if (!encoder->ReadCompressedAudio(&data, &length, &timestamp))
    return false;

  jlong outputTimestamp = timestamp;
  env->SetLongArrayRegion(jTimestamp, 0, 1, &outputTimestamp);
  return newByteArray(env, data, length);
}

FUNCTION(jbyteArray, CodecPrivate, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  const unsigned char* data = encoder->codec_private();
  const int length = encoder->codec_private_length();
  return newByteArray(env, data, length);
}

FUNCTION(jint, GetChannels, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->GetChannels();
}

FUNCTION(jint, GetSampleRate, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->GetSampleRate();
}

FUNCTION(jint, GetBitsPerSample, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->GetBitsPerSample();
}

FUNCTION(jint, GetAverageBitrate, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->GetAverageBitrate();
}

FUNCTION(jint, GetMinimumBitrate, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->GetMinimumBitrate();
}

FUNCTION(jint, GetMaximumBitrate, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->GetMaximumBitrate();
}

FUNCTION(void, SetChannels, jlong jVorbisEncoder, jint channels) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->SetChannels(channels);
}

FUNCTION(void, SetSampleRate, jlong jVorbisEncoder, jint sample_rate) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->SetSampleRate(sample_rate);
}

FUNCTION(void, SetBitsPerSample, jlong jVorbisEncoder, jint bits_per_sample) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->SetBitsPerSample(bits_per_sample);
}

FUNCTION(void, SetAverageBitrate, jlong jVorbisEncoder, jint bitrate) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->SetAverageBitrate(bitrate);
}

FUNCTION(void, SetMinimumBitrate, jlong jVorbisEncoder, jint bitrate) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->SetMinimumBitrate(bitrate);
}

FUNCTION(void, SetMaximumBitrate, jlong jVorbisEncoder, jint bitrate) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  return encoder->SetMaximumBitrate(bitrate);
}
