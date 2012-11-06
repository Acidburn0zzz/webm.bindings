// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, Chapters, functionName, ##__VA_ARGS__)

FUNCTION(jlong, AddChapter, jlong jChapters, jint jSeed) {
  mkvmuxer::Chapters* chapters =
      reinterpret_cast<mkvmuxer::Chapters*>(jChapters);
  unsigned int seed = jSeed;
  return reinterpret_cast<jlong>(chapters->AddChapter(&seed));
}

FUNCTION(jint, Count, jlong jChapters) {
  mkvmuxer::Chapters* chapters =
      reinterpret_cast<mkvmuxer::Chapters*>(jChapters);
  return chapters->Count();
}

FUNCTION(void, deleteChapters, jlong jChapters) {
  mkvmuxer::Chapters* chapters =
      reinterpret_cast<mkvmuxer::Chapters*>(jChapters);
  delete chapters;
}

FUNCTION(jlong, newChapters) {
  jlong jChapters =
      reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::Chapters);
  return jChapters;
}

FUNCTION(jboolean, Write, jlong jChapters, jlong jWriter) {
  mkvmuxer::Chapters* chapters =
      reinterpret_cast<mkvmuxer::Chapters*>(jChapters);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return chapters->Write(writer);
}
