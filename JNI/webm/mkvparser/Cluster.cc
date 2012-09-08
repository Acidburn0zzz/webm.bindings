// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Cluster, functionName, ##__VA_ARGS__)

FUNCTION(jlong, Create, jlong jSegment, jlong index, jlong offset) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  return reinterpret_cast<jlong>(mkvparser::Cluster::Create(segment, index,
                                                            offset));
}

FUNCTION(void, deleteCluster, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  delete cluster;
}

FUNCTION(jboolean, EOS, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return cluster->EOS();
}

FUNCTION(jlong, GetElementSize, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return cluster->GetElementSize();
}

FUNCTION(jlong, getElementStart, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return cluster->m_element_start;
}

FUNCTION(jlong, GetEntryCount, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return cluster->GetEntryCount();
}

FUNCTION(jlong, GetEntryCuePoint, jlong jCluster, jlong jCuePoint,
                                  jlong jTrackPosition) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  mkvparser::CuePoint& cuePoint =
      *reinterpret_cast<mkvparser::CuePoint*>(jCuePoint);
  mkvparser::CuePoint::TrackPosition& trackPosition =
      *reinterpret_cast<mkvparser::CuePoint::TrackPosition*>(jTrackPosition);
  return reinterpret_cast<jlong>(cluster->GetEntry(cuePoint, trackPosition));
}

FUNCTION(jlong, GetEntryIndex, jlong jCluster, jlong index,
                               jlongArray jBlockEntry) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  const mkvparser::BlockEntry* blockEntry = 0;
  long result = cluster->GetEntry(index, blockEntry);
  jlong outputBlockEntry = reinterpret_cast<jlong>(blockEntry);
  env->SetLongArrayRegion(jBlockEntry, 0, 1, &outputBlockEntry);
  return result;
}

FUNCTION(jlong, GetEntryTrack, jlong jCluster, jlong jTrack, jlong ns) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  mkvparser::Track* track = reinterpret_cast<mkvparser::Track*>(jTrack);
  return reinterpret_cast<jlong>(cluster->GetEntry(track, ns));
}

FUNCTION(jlong, GetFirst, jlong jCluster, jlongArray jBlockEntry) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  const mkvparser::BlockEntry* blockEntry = 0;
  long result = cluster->GetFirst(blockEntry);
  jlong outputBlockEntry = reinterpret_cast<jlong>(blockEntry);
  env->SetLongArrayRegion(jBlockEntry, 0, 1, &outputBlockEntry);
  return result;
}

FUNCTION(jlong, GetFirstTime, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return cluster->GetFirstTime();
}

FUNCTION(jlong, GetIndex, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return cluster->GetIndex();
}

FUNCTION(jlong, GetLast, jlong jCluster, jlongArray jBlockEntry) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  const mkvparser::BlockEntry* blockEntry = 0;
  long result = cluster->GetLast(blockEntry);
  jlong outputBlockEntry = reinterpret_cast<jlong>(blockEntry);
  env->SetLongArrayRegion(jBlockEntry, 0, 1, &outputBlockEntry);
  return result;
}

FUNCTION(jlong, GetLastTime, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return cluster->GetLastTime();
}

FUNCTION(jlong, GetNext, jlong jCluster, jlong jCurrent, jlongArray jNext) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  mkvparser::BlockEntry* current =
      reinterpret_cast<mkvparser::BlockEntry*>(jCurrent);
  const mkvparser::BlockEntry* next = 0;
  long result = cluster->GetNext(current, next);
  jlong outputNext = reinterpret_cast<jlong>(next);
  env->SetLongArrayRegion(jNext, 0, 1, &outputNext);
  return result;
}

FUNCTION(jlong, GetPosition, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return cluster->GetPosition();
}

FUNCTION(jlong, getSegment, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return reinterpret_cast<jlong>(cluster->m_pSegment);
}

FUNCTION(jlong, GetTime, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return cluster->GetTime();
}

FUNCTION(jlong, GetTimeCode, jlong jCluster) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  return cluster->GetTimeCode();
}

FUNCTION(jlong, HasBlockEntries, jlong jSegment, jlong offset,
                                 jlongArray jPosition, jlongArray jSize) {
  mkvparser::Segment* segment = reinterpret_cast<mkvparser::Segment*>(jSegment);
  long long position = 0;
  long size = 0;
  long result = mkvparser::Cluster::HasBlockEntries(segment, offset, position,
                                                    size);
  jlong outputPosition = position;
  env->SetLongArrayRegion(jPosition, 0, 1, &outputPosition);
  jlong outputSize = size;
  env->SetLongArrayRegion(jSize, 0, 1, &outputSize);
  return result;
}

FUNCTION(jlong, Load, jlong jCluster, jlongArray jPosition, jlongArray jSize) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  long long position = 0;
  long size = 0;
  long result = cluster->Load(position, size);
  jlong outputPosition = position;
  env->SetLongArrayRegion(jPosition, 0, 1, &outputPosition);
  jlong outputSize = size;
  env->SetLongArrayRegion(jSize, 0, 1, &outputSize);
  return result;
}

FUNCTION(jlong, newCluster) {
  jlong jCluster =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::Cluster);
  return jCluster;
}

FUNCTION(jlong, Parse, jlong jCluster, jlongArray jPosition, jlongArray jSize) {
  mkvparser::Cluster* cluster = reinterpret_cast<mkvparser::Cluster*>(jCluster);
  long long position = 0;
  long size = 0;
  long result = cluster->Parse(position, size);
  jlong outputPosition = position;
  env->SetLongArrayRegion(jPosition, 0, 1, &outputPosition);
  jlong outputSize = size;
  env->SetLongArrayRegion(jSize, 0, 1, &outputSize);
  return result;
}
