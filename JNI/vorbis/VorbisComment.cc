// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>
#include <string.h>

#include "common.h"
#include "vorbis/codec.h"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, VorbisComment, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteVorbisComment, jlong jVorbisComment) {
  vorbis_comment* vorbisComment =
      reinterpret_cast<vorbis_comment*>(jVorbisComment);
  delete vorbisComment;
}

FUNCTION(jintArray, getCommentLengths, jlong jVorbisComment) {
  vorbis_comment* vorbisComment =
      reinterpret_cast<vorbis_comment*>(jVorbisComment);
  jintArray lengths = env->NewIntArray(vorbisComment->comments);
  env->SetIntArrayRegion(lengths, 0, vorbisComment->comments,
                         vorbisComment->comment_lengths);
  return lengths;
}

FUNCTION(jint, getComments, jlong jVorbisComment) {
  vorbis_comment* vorbisComment =
      reinterpret_cast<vorbis_comment*>(jVorbisComment);
  return vorbisComment->comments;
}

FUNCTION(jobjectArray, getUserComments, jlong jVorbisComment) {
  vorbis_comment* vorbisComment =
      reinterpret_cast<vorbis_comment*>(jVorbisComment);
  jclass stringClass = env->FindClass("java/lang/String");
  jobjectArray comments =
      env->NewObjectArray(vorbisComment->comments, stringClass, 0);
  for (int i = 0; i < vorbisComment->comments; ++i) {
    jstring comment = env->NewStringUTF(vorbisComment->user_comments[i]);
    env->SetObjectArrayElement(comments, i, comment);
  }
  return comments;
}

FUNCTION(jstring, getVendor, jlong jVorbisComment) {
  vorbis_comment* vorbisComment =
      reinterpret_cast<vorbis_comment*>(jVorbisComment);
  return env->NewStringUTF(vorbisComment->vendor);
}

FUNCTION(jlong, newVorbisComment) {
  jlong jVorbisComment =
      reinterpret_cast<jlong>(new (std::nothrow) vorbis_comment);
  return jVorbisComment;
}

FUNCTION(void, setCommentLengths, jlong jVorbisComment,
                                  jintArray jCommentLengths) {
  vorbis_comment* vorbisComment =
      reinterpret_cast<vorbis_comment*>(jVorbisComment);
  jsize size = env->GetArrayLength(jCommentLengths);
  delete[] vorbisComment->comment_lengths;
  vorbisComment->comment_lengths = new int[size];
  env->GetIntArrayRegion(jCommentLengths, 0, size,
                         vorbisComment->comment_lengths);
}

FUNCTION(void, setComments, jlong jVorbisComment, jint comments) {
  vorbis_comment* vorbisComment =
      reinterpret_cast<vorbis_comment*>(jVorbisComment);
  vorbisComment->comments = comments;
}

FUNCTION(void, setUserComments, jlong jVorbisComment,
                                jobjectArray jUserComments) {
  vorbis_comment* vorbisComment =
      reinterpret_cast<vorbis_comment*>(jVorbisComment);
  for (int i = 0; i < vorbisComment->comments; ++i) {
    delete[] vorbisComment->user_comments[i];
  }
  delete[] vorbisComment->user_comments;
  jsize size = env->GetArrayLength(jUserComments);
  vorbisComment->user_comments = new char*[size];
  for (int i = 0; i < size; ++i) {
    jstring jComment =
        static_cast<jstring>(env->GetObjectArrayElement(jUserComments, i));
    vorbisComment->user_comments[i] =
        new char[env->GetStringLength(jComment) + 1];
    const char* comment = env->GetStringUTFChars(jComment, 0);
    strcpy(vorbisComment->user_comments[i], comment);
    env->ReleaseStringUTFChars(jComment, comment);
  }
}

FUNCTION(void, setVendor, jlong jVorbisComment, jstring jVendor) {
  vorbis_comment* vorbisComment =
      reinterpret_cast<vorbis_comment*>(jVorbisComment);
  delete[] vorbisComment->vendor;
  vorbisComment->vendor = new char[env->GetStringLength(jVendor) + 1];
  const char* vendor = env->GetStringUTFChars(jVendor, 0);
  strcpy(vorbisComment->vendor, vendor);
  env->ReleaseStringUTFChars(jVendor, vendor);
}
