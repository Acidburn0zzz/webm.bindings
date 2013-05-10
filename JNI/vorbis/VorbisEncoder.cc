#include <assert.h>
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

FUNCTION(jboolean, Init, jlong jVorbisEncoder, jlong jVorbisEncoderConfig) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  vorbis::VorbisEncoderConfig* config =
        reinterpret_cast<vorbis::VorbisEncoderConfig*>(jVorbisEncoderConfig);
  return encoder->Init(*config);
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

FUNCTION(jobject, ReadCompressedFrame, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);

  unsigned char* data;
  int length;
  int64_t timestamp;
  if (!encoder->ReadCompressedAudio(&data, &length, &timestamp))
    return false;

  jclass audioFrame = env->FindClass("com/google/libvorbis/AudioFrame");
  assert(audioFrame != NULL);

  jmethodID afInitMethodId = env->GetMethodID(audioFrame, "<init>", "(J)V");
  assert(afInitMethodId != NULL);

  jfieldID bufferId = env->GetFieldID(audioFrame, "buffer", "[B");
  assert(bufferId != NULL);

  jfieldID ptsId = env->GetFieldID(audioFrame, "pts", "J");
  assert(ptsId != NULL);

  jobject frame = env->NewObject(audioFrame,
                                 afInitMethodId,
                                 (jlong)length);

  jobject jba = env->GetObjectField(frame, bufferId);
  assert(jba != NULL);

  env->SetByteArrayRegion((jbyteArray)jba, 0,
                          length, reinterpret_cast<jbyte *>(data));
  env->SetLongField(frame, ptsId, timestamp);

  return frame;
}

FUNCTION(jbyteArray, CodecPrivate, jlong jVorbisEncoder) {
  vorbis::VorbisEncoder* encoder =
      reinterpret_cast<vorbis::VorbisEncoder*>(jVorbisEncoder);
  const unsigned char* data = encoder->codec_private();
  const int length = encoder->codec_private_length();
  return newByteArray(env, data, length);
}
