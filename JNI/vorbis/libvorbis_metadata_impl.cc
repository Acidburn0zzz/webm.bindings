// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "ogg/ogg.h"
#include "vorbis/codec.h"

#define FUNCTION(returnType, name, ...) \
  extern "C" { \
    JNIEXPORT returnType Java_com_google_libvorbis_LibVorbisMetadata_##name \
        (JNIEnv* env, jobject self, ##__VA_ARGS__); \
  } \
  JNIEXPORT returnType Java_com_google_libvorbis_LibVorbisMetadata_##name \
      (JNIEnv* env, jobject self, ##__VA_ARGS__) \

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

FUNCTION(jint, vorbisCommentheaderOut, jlong jvc, jlong jop) {
  vorbis_comment* vc = reinterpret_cast<vorbis_comment*>(jvc);
  ogg_packet* op = reinterpret_cast<ogg_packet*>(jop);
  return vorbis_commentheader_out(vc, op);
}
