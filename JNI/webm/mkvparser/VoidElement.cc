// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, VoidElement, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteVoidElement, jlong jVoidElement) {
  mkvparser::SeekHead::VoidElement* voidElement =
      reinterpret_cast<mkvparser::SeekHead::VoidElement*>(jVoidElement);
  delete voidElement;
}

FUNCTION(jlong, getElementSize, jlong jVoidElement) {
  mkvparser::SeekHead::VoidElement* voidElement =
      reinterpret_cast<mkvparser::SeekHead::VoidElement*>(jVoidElement);
  return voidElement->element_size;
}

FUNCTION(jlong, getElementStart, jlong jVoidElement) {
  mkvparser::SeekHead::VoidElement* voidElement =
      reinterpret_cast<mkvparser::SeekHead::VoidElement*>(jVoidElement);
  return voidElement->element_start;
}

FUNCTION(jlong, newVoidElement) {
  jlong jVoidElement = reinterpret_cast<jlong>(
      new (std::nothrow) mkvparser::SeekHead::VoidElement);
  return jVoidElement;
}

FUNCTION(void, setElementSize, jlong jVoidElement, jlong element_size) {
  mkvparser::SeekHead::VoidElement* voidElement =
      reinterpret_cast<mkvparser::SeekHead::VoidElement*>(jVoidElement);
  voidElement->element_size = element_size;
}

FUNCTION(void, setElementStart, jlong jVoidElement, jlong element_start) {
  mkvparser::SeekHead::VoidElement* voidElement =
      reinterpret_cast<mkvparser::SeekHead::VoidElement*>(jVoidElement);
  voidElement->element_start = element_start;
}
