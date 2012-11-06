// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"
#include "mkvmuxertypes.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, Frame, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteFrame, jlong jFrame) {
  mkvmuxer::Frame* frame = reinterpret_cast<mkvmuxer::Frame*>(jFrame);
  delete frame;
}

FUNCTION(jbyteArray, frame, jlong jFrame) {
  mkvmuxer::Frame* frame = reinterpret_cast<mkvmuxer::Frame*>(jFrame);
  return newByteArray(env, frame->frame(), frame->length());
}

FUNCTION(jboolean, Init, jlong jFrame, jbyteArray jFrameBuffer, jlong length) {
  mkvmuxer::Frame* frame = reinterpret_cast<mkvmuxer::Frame*>(jFrame);
  char* frameBuffer = new char[length];
  env->GetByteArrayRegion(jFrameBuffer, 0, length,
                          reinterpret_cast<jbyte*>(frameBuffer));
  bool result = frame->Init(
      reinterpret_cast<const mkvmuxer::uint8*>(frameBuffer), length);
  delete[] frameBuffer;
  return result;
}

FUNCTION(jboolean, is_key, jlong jFrame) {
  mkvmuxer::Frame* frame = reinterpret_cast<mkvmuxer::Frame*>(jFrame);
  return frame->is_key();
}

FUNCTION(jlong, length, jlong jFrame) {
  mkvmuxer::Frame* frame = reinterpret_cast<mkvmuxer::Frame*>(jFrame);
  return frame->length();
}

FUNCTION(jlong, newFrame) {
  jlong jFrame = reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::Frame);
  return jFrame;
}

FUNCTION(void, set_is_key, jlong jFrame, jboolean key) {
  mkvmuxer::Frame* frame = reinterpret_cast<mkvmuxer::Frame*>(jFrame);
  frame->set_is_key(key);
}

FUNCTION(void, set_timestamp, jlong jFrame, jlong timestamp) {
  mkvmuxer::Frame* frame = reinterpret_cast<mkvmuxer::Frame*>(jFrame);
  frame->set_timestamp(timestamp);
}

FUNCTION(void, set_track_number, jlong jFrame, jlong track_number) {
  mkvmuxer::Frame* frame = reinterpret_cast<mkvmuxer::Frame*>(jFrame);
  frame->set_track_number(track_number);
}

FUNCTION(jlong, timestamp, jlong jFrame) {
  mkvmuxer::Frame* frame = reinterpret_cast<mkvmuxer::Frame*>(jFrame);
  return frame->timestamp();
}

FUNCTION(jlong, track_number, jlong jFrame) {
  mkvmuxer::Frame* frame = reinterpret_cast<mkvmuxer::Frame*>(jFrame);
  return frame->track_number();
}
