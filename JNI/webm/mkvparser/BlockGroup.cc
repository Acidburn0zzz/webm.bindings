// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, BlockGroup, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteBlockGroup, jlong jBlockGroup) {
  mkvparser::BlockGroup* blockGroup =
      reinterpret_cast<mkvparser::BlockGroup*>(jBlockGroup);
  delete blockGroup;
}

FUNCTION(jlong, GetBlock, jlong jBlockGroup) {
  mkvparser::BlockGroup* blockGroup =
      reinterpret_cast<mkvparser::BlockGroup*>(jBlockGroup);
  return reinterpret_cast<jlong>(blockGroup->GetBlock());
}

FUNCTION(jlong, GetDurationTimeCode, jlong jBlockGroup) {
  mkvparser::BlockGroup* blockGroup =
      reinterpret_cast<mkvparser::BlockGroup*>(jBlockGroup);
  return blockGroup->GetDurationTimeCode();
}

FUNCTION(jint, GetKind, jlong jBlockGroup) {
  mkvparser::BlockGroup* blockGroup =
      reinterpret_cast<mkvparser::BlockGroup*>(jBlockGroup);
  return blockGroup->GetKind();
}

FUNCTION(jlong, GetNextTimeCode, jlong jBlockGroup) {
  mkvparser::BlockGroup* blockGroup =
      reinterpret_cast<mkvparser::BlockGroup*>(jBlockGroup);
  return blockGroup->GetNextTimeCode();
}

FUNCTION(jlong, GetPrevTimeCode, jlong jBlockGroup) {
  mkvparser::BlockGroup* blockGroup =
      reinterpret_cast<mkvparser::BlockGroup*>(jBlockGroup);
  return blockGroup->GetPrevTimeCode();
}

FUNCTION(jlong, newBlockGroup, jlong jCluster,
                               jlong index,
                               jlong blockStart,
                               jlong blockSize,
                               jlong previous,
                               jlong next,
                               jlong duration) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  jlong jBlockGroup =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::BlockGroup(
          cluster, index, blockStart, blockSize, previous, next, duration, 0));
  return jBlockGroup;
}

FUNCTION(jlong, Parse, jlong jBlockGroup) {
  mkvparser::BlockGroup* blockGroup =
      reinterpret_cast<mkvparser::BlockGroup*>(jBlockGroup);
  return blockGroup->Parse();
}
