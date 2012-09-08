// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Frame, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteFrame, jlong jFrame) {
  mkvparser::Block::Frame* frame =
      reinterpret_cast<mkvparser::Block::Frame*>(jFrame);
  delete frame;
}

FUNCTION(jlong, getLen, jlong jFrame) {
  mkvparser::Block::Frame* frame =
      reinterpret_cast<mkvparser::Block::Frame*>(jFrame);
  return frame->len;
}

FUNCTION(jlong, getPos, jlong jFrame) {
  mkvparser::Block::Frame* frame =
      reinterpret_cast<mkvparser::Block::Frame*>(jFrame);
  return frame->pos;
}

FUNCTION(jlong, newFrame) {
  jlong jFrame =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::Block::Frame);
  return jFrame;
}

FUNCTION(jlong, Read, jlong jFrame, jlong jMkvReader, jobjectArray jBuffer) {
  mkvparser::Block::Frame* frame =
      reinterpret_cast<mkvparser::Block::Frame*>(jFrame);
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  unsigned char* buffer = new (std::nothrow) unsigned char[frame->len];
  if (!buffer) {
    return -1;
  }

  long result = frame->Read(mkvReader, buffer);
  if (result) {
    env->SetObjectArrayElement(jBuffer, 0, 0);
    delete[] buffer;
    return result;
  }

  jbyteArray jBufferElement = env->NewByteArray(frame->len);
  env->SetByteArrayRegion(jBufferElement, 0, frame->len,
                          reinterpret_cast<const jbyte*>(buffer));
  env->SetObjectArrayElement(jBuffer, 0, jBufferElement);
  delete[] buffer;
  return result;
}

FUNCTION(void, setLen, jlong jFrame, jlong len) {
  mkvparser::Block::Frame* frame =
      reinterpret_cast<mkvparser::Block::Frame*>(jFrame);
  frame->len = len;
}

FUNCTION(void, setPos, jlong jFrame, jlong pos) {
  mkvparser::Block::Frame* frame =
      reinterpret_cast<mkvparser::Block::Frame*>(jFrame);
  frame->pos = pos;
}
