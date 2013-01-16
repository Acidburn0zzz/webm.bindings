// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "ogg/ogg.h"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, OggpackBuffer, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteOggpackBuffer, jlong jOggpackBuffer) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  delete oggpackBuffer;
}

FUNCTION(jlong, getBuffer, jlong jOggpackBuffer) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  return reinterpret_cast<jlong>(oggpackBuffer->buffer);
}

FUNCTION(jint, getEndbit, jlong jOggpackBuffer) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  return oggpackBuffer->endbit;
}

FUNCTION(jlong, getEndbyte, jlong jOggpackBuffer) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  return oggpackBuffer->endbyte;
}

FUNCTION(jlong, getPtr, jlong jOggpackBuffer) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  return reinterpret_cast<jlong>(oggpackBuffer->ptr);
}

FUNCTION(jlong, getStorage, jlong jOggpackBuffer) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  return oggpackBuffer->storage;
}

FUNCTION(jlong, newOggpackBuffer) {
  jlong jOggpackBuffer =
      reinterpret_cast<jlong>(new (std::nothrow) oggpack_buffer);
  return jOggpackBuffer;
}

FUNCTION(void, setBuffer, jlong jOggpackBuffer, jlong buffer) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  oggpackBuffer->buffer = reinterpret_cast<unsigned char*>(buffer);
}

FUNCTION(void, setEndbit, jlong jOggpackBuffer, jlong endbit) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  oggpackBuffer->endbit = endbit;
}

FUNCTION(void, setEndbyte, jlong jOggpackBuffer, jlong endbyte) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  oggpackBuffer->endbyte = endbyte;
}

FUNCTION(void, setPtr, jlong jOggpackBuffer, jlong ptr) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  oggpackBuffer->ptr = reinterpret_cast<unsigned char*>(ptr);
}

FUNCTION(void, setStorage, jlong jOggpackBuffer, jlong storage) {
  oggpack_buffer* oggpackBuffer =
      reinterpret_cast<oggpack_buffer*>(jOggpackBuffer);
  oggpackBuffer->storage = storage;
}
