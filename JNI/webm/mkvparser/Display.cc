// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Display, functionName, ##__VA_ARGS__)

FUNCTION(jstring, GetCountry, jlong jDisplay) {
  mkvparser::Chapters::Display* display =
      reinterpret_cast<mkvparser::Chapters::Display*>(jDisplay);
  return env->NewStringUTF(display->GetCountry());
}

FUNCTION(jstring, GetLanguage, jlong jDisplay) {
  mkvparser::Chapters::Display* display =
      reinterpret_cast<mkvparser::Chapters::Display*>(jDisplay);
  return env->NewStringUTF(display->GetLanguage());
}

FUNCTION(jstring, GetString, jlong jDisplay) {
  mkvparser::Chapters::Display* display =
      reinterpret_cast<mkvparser::Chapters::Display*>(jDisplay);
  return env->NewStringUTF(display->GetString());
}
