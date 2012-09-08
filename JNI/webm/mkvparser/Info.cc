// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>
#include <string.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Info, functionName, ##__VA_ARGS__)

FUNCTION(void, Clear, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  info->Clear();
}

FUNCTION(jint, Copy, jlong jInfo, jlong jDestination) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  mkvparser::Track::Info& destination =
      *reinterpret_cast<mkvparser::Track::Info*>(jDestination);
  return info->Copy(destination);
}

FUNCTION(void, deleteInfo, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  delete info;
}

FUNCTION(jstring, getCodecId, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  return env->NewStringUTF(info->codecId);
}

FUNCTION(jstring, getCodecNameAsUTF8, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  return env->NewStringUTF(info->codecNameAsUTF8);
}

FUNCTION(jbyteArray, getCodecPrivate, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  return newByteArray(env, info->codecPrivate, info->codecPrivateSize);
}

FUNCTION(jboolean, getLacing, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  return info->lacing;
}

FUNCTION(jstring, getNameAsUTF8, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  return env->NewStringUTF(info->nameAsUTF8);
}

FUNCTION(jlong, getNumber, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  return info->number;
}

FUNCTION(jlong, getSettings, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  return reinterpret_cast<jlong>(&info->settings);
}

FUNCTION(jlong, getType, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  return info->type;
}

FUNCTION(jlong, getUid, jlong jInfo) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  return info->uid;
}

FUNCTION(jlong, newInfo) {
  jlong jInfo =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::Track::Info);
  return jInfo;
}

FUNCTION(void, setCodecId, jlong jInfo, jstring jCodecId) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  const char* codecId = env->GetStringUTFChars(jCodecId, 0);
  strcpy(info->codecId, codecId);
}

FUNCTION(void, setCodecNameAsUTF8, jlong jInfo, jstring jCodecNameAsUtf8) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  const char* codecNameAsUtf8 = env->GetStringUTFChars(jCodecNameAsUtf8, 0);
  strcpy(info->codecNameAsUTF8, codecNameAsUtf8);
}

FUNCTION(void, setCodecPrivate, jlong jInfo, jbyteArray jCodecPrivate) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  setBuffer(env, jCodecPrivate, &info->codecPrivate, &info->codecPrivateSize);
}

FUNCTION(void, setLacing, jlong jInfo, jboolean lacing) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  info->lacing = lacing;
}

FUNCTION(void, setNameAsUTF8, jlong jInfo, jstring jNameAsUtf8) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  const char* nameAsUtf8 = env->GetStringUTFChars(jNameAsUtf8, 0);
  strcpy(info->nameAsUTF8, nameAsUtf8);
}

FUNCTION(void, setNumber, jlong jInfo, jlong number) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  info->number = number;
}

FUNCTION(void, setSettings, jlong jInfo, jlong jSettings) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  mkvparser::Track::Settings* settings =
      reinterpret_cast<mkvparser::Track::Settings*>(jSettings);
  memcpy(&info->settings, reinterpret_cast<const void*>(settings),
         sizeof(info->settings));
}

FUNCTION(void, setType, jlong jInfo, jlong type) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  info->type = type;
}

FUNCTION(void, setUid, jlong jInfo, jlong uid) {
  mkvparser::Track::Info* info =
      reinterpret_cast<mkvparser::Track::Info*>(jInfo);
  info->uid = uid;
}
