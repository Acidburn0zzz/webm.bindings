// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, SegmentInfo, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteSegmentInfo, jlong jSegmentInfo) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  delete segmentInfo;
}

FUNCTION(jdouble, duration, jlong jSegmentInfo) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  return segmentInfo->duration();
}

FUNCTION(jboolean, Finalize, jlong jSegmentInfo, jlong jWriter) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return segmentInfo->Finalize(writer);
}

FUNCTION(jboolean, Init, jlong jSegmentInfo) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  return segmentInfo->Init();
}

FUNCTION(jstring, muxing_app, jlong jSegmentInfo) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  return env->NewStringUTF(segmentInfo->muxing_app());
}

FUNCTION(jlong, newSegmentInfo) {
  jlong jSegmentInfo =
      reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::SegmentInfo);
  return jSegmentInfo;
}

FUNCTION(void, set_duration, jlong jSegmentInfo, jdouble duration) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  segmentInfo->set_duration(duration);
}

FUNCTION(void, set_muxing_app, jlong jSegmentInfo, jstring jApp) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  const char* app = env->GetStringUTFChars(jApp, 0);
  segmentInfo->set_muxing_app(app);
  env->ReleaseStringUTFChars(jApp, app);
}

FUNCTION(void, set_timecode_scale, jlong jSegmentInfo, jlong scale) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  segmentInfo->set_timecode_scale(scale);
}

FUNCTION(void, set_writing_app, jlong jSegmentInfo, jstring jApp) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  const char* app = env->GetStringUTFChars(jApp, 0);
  segmentInfo->set_writing_app(app);
  env->ReleaseStringUTFChars(jApp, app);
}

FUNCTION(jlong, timecode_scale, jlong jSegmentInfo) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  return segmentInfo->timecode_scale();
}

FUNCTION(jboolean, Write, jlong jSegmentInfo, jlong jWriter) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return segmentInfo->Write(writer);
}

FUNCTION(jstring, writing_app, jlong jSegmentInfo) {
  mkvmuxer::SegmentInfo* segmentInfo =
      reinterpret_cast<mkvmuxer::SegmentInfo*>(jSegmentInfo);
  return env->NewStringUTF(segmentInfo->writing_app());
}
