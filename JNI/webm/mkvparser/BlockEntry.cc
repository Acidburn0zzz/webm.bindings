// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <typeinfo>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, BlockEntry, functionName, ##__VA_ARGS__)

FUNCTION(jboolean, EOS, jlong jBlockEntry) {
  mkvparser::BlockEntry* blockEntry =
      reinterpret_cast<mkvparser::BlockEntry*>(jBlockEntry);
  return blockEntry->EOS();
}

FUNCTION(jint, getClassType, jlong jBlockEntry) {
  mkvparser::BlockEntry* blockEntry =
      reinterpret_cast<mkvparser::BlockEntry*>(jBlockEntry);
  int type = 0;
  if (!blockEntry) {
    return type;
  }
  const std::type_info& typeInfo = typeid(*blockEntry);
  if (typeInfo == typeid(mkvparser::BlockGroup)) {
    type = 1;
  } else if (typeInfo == typeid(mkvparser::SimpleBlock)) {
    type = 2;
  }
  return type;
}

FUNCTION(jlong, GetCluster, jlong jBlockEntry) {
  mkvparser::BlockEntry* blockEntry =
      reinterpret_cast<mkvparser::BlockEntry*>(jBlockEntry);
  return reinterpret_cast<jlong>(blockEntry->GetCluster());
}

FUNCTION(jlong, GetIndex, jlong jBlockEntry) {
  mkvparser::BlockEntry* blockEntry =
      reinterpret_cast<mkvparser::BlockEntry*>(jBlockEntry);
  return blockEntry->GetIndex();
}
