// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, Chapter, functionName, ##__VA_ARGS__)

FUNCTION(jboolean, addString, jlong jChapter, jstring jTitle,
                              jstring jLanguage, jstring jCountry) {
  mkvmuxer::Chapter* chapter = reinterpret_cast<mkvmuxer::Chapter*>(jChapter);
  const char* country = env->GetStringUTFChars(jCountry, 0);
  const char* language = env->GetStringUTFChars(jLanguage, 0);
  const char* title = env->GetStringUTFChars(jTitle, 0);
  bool result = chapter->add_string(title, language, country);
  env->ReleaseStringUTFChars(jCountry, country);
  env->ReleaseStringUTFChars(jLanguage, language);
  env->ReleaseStringUTFChars(jTitle, title);
  return result;
}

FUNCTION(jboolean, setId, jlong jChapter, jstring jId) {
  mkvmuxer::Chapter* chapter = reinterpret_cast<mkvmuxer::Chapter*>(jChapter);
  const char* id = env->GetStringUTFChars(jId, 0);
  bool result = chapter->set_id(id);
  env->ReleaseStringUTFChars(jId, id);
  return result;
}

FUNCTION(void, setTime, jlong jChapter, jlong jSegment, jlong start_time_ns,
                        jlong end_time_ns) {
  mkvmuxer::Chapter* chapter = reinterpret_cast<mkvmuxer::Chapter*>(jChapter);
  const mkvmuxer::Segment& segment =
      *reinterpret_cast<mkvmuxer::Segment*>(jSegment);
  chapter->set_time(segment, start_time_ns, end_time_ns);
}
