// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Block, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteBlock, jlong jBlock) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  delete block;
}

FUNCTION(jlong, GetFrame, jlong jBlock, jint frameIndex) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  return reinterpret_cast<jlong>(&block->GetFrame(frameIndex));
}

FUNCTION(jint, GetFrameCount, jlong jBlock) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  return block->GetFrameCount();
}

FUNCTION(jint, GetLacing, jlong jBlock) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  return block->GetLacing();
}

FUNCTION(jlong, getSize, jlong jBlock) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  return block->m_size;
}

FUNCTION(jlong, getStart, jlong jBlock) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  return block->m_start;
}

FUNCTION(jlong, GetTime, jlong jBlock, jlong jCluster) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return block->GetTime(cluster);
}

FUNCTION(jlong, GetTimeCode, jlong jBlock, jlong jCluster) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return block->GetTimeCode(cluster);
}

FUNCTION(jlong, GetTrackNumber, jlong jBlock) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  return block->GetTrackNumber();
}

FUNCTION(jboolean, IsInvisible, jlong jBlock) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  return block->IsInvisible();
}

FUNCTION(jboolean, IsKey, jlong jBlock) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  return block->IsKey();
}

FUNCTION(jlong, newBlock, jlong start, jlong size) {
  jlong jBlock =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::Block(start, size));
  return jBlock;
}

FUNCTION(jlong, Parse, jlong jBlock, jlong jCluster) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return block->Parse(cluster);
}

FUNCTION(void, SetKey, jlong jBlock, jboolean key) {
  mkvparser::Block* block = reinterpret_cast<mkvparser::Block*>(jBlock);
  return block->SetKey(key);
}
