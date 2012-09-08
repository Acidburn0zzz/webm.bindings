// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, SimpleBlock, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteSimpleBlock, jlong jSimpleBlock) {
  mkvparser::SimpleBlock* simpleBlock =
      reinterpret_cast<mkvparser::SimpleBlock*>(jSimpleBlock);
  delete simpleBlock;
}

FUNCTION(jlong, GetBlock, jlong jSimpleBlock) {
  mkvparser::SimpleBlock* simpleBlock =
      reinterpret_cast<mkvparser::SimpleBlock*>(jSimpleBlock);
  return reinterpret_cast<jlong>(simpleBlock->GetBlock());
}

FUNCTION(jint, GetKind, jlong jSimpleBlock) {
  mkvparser::SimpleBlock* simpleBlock =
      reinterpret_cast<mkvparser::SimpleBlock*>(jSimpleBlock);
  return simpleBlock->GetKind();
}

FUNCTION(jlong, newSimpleBlock, jlong jCluster, jlong index, jlong start,
                                jlong size) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  jlong jSimpleBlock = reinterpret_cast<jlong>(
      new (std::nothrow) mkvparser::SimpleBlock(cluster, index, start, size));
  return jSimpleBlock;
}

FUNCTION(jlong, Parse, jlong jSimpleBlock) {
  mkvparser::SimpleBlock* simpleBlock =
      reinterpret_cast<mkvparser::SimpleBlock*>(jSimpleBlock);
  return simpleBlock->Parse();
}
