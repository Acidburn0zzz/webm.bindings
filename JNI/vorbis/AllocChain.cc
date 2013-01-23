// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "vorbis/codec.h"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, AllocChain, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteAllocChain, jlong jAllocChain) {
  alloc_chain* allocChain = reinterpret_cast<alloc_chain*>(jAllocChain);
  delete allocChain;
}

FUNCTION(jlong, getNext, jlong jAllocChain) {
  alloc_chain* allocChain = reinterpret_cast<alloc_chain*>(jAllocChain);
  return reinterpret_cast<jlong>(allocChain->next);
}

FUNCTION(jlong, getPtr, jlong jAllocChain) {
  alloc_chain* allocChain = reinterpret_cast<alloc_chain*>(jAllocChain);
  return reinterpret_cast<jlong>(allocChain->ptr);
}

FUNCTION(jlong, newAllocChain) {
  jlong jAllocChain = reinterpret_cast<jlong>(new (std::nothrow) alloc_chain);
  return jAllocChain;
}

FUNCTION(void, setNext, jlong jAllocChain, jlong next) {
  alloc_chain* allocChain = reinterpret_cast<alloc_chain*>(jAllocChain);
  allocChain->next = reinterpret_cast<alloc_chain*>(next);
}

FUNCTION(void, setPtr, jlong jAllocChain, jlong ptr) {
  alloc_chain* allocChain = reinterpret_cast<alloc_chain*>(jAllocChain);
  allocChain->ptr = reinterpret_cast<void*>(ptr);
}
