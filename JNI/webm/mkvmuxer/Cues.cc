// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, Cues, functionName, ##__VA_ARGS__)

FUNCTION(jboolean, AddCue, jlong jCues, jlong jCue) {
  mkvmuxer::Cues* cues = reinterpret_cast<mkvmuxer::Cues*>(jCues);
  mkvmuxer::CuePoint* cue = reinterpret_cast<mkvmuxer::CuePoint*>(jCue);
  return cues->AddCue(cue);
}

FUNCTION(jint, cueEntriesSize, jlong jCues) {
  mkvmuxer::Cues* cues = reinterpret_cast<mkvmuxer::Cues*>(jCues);
  return cues->cue_entries_size();
}

FUNCTION(jlong, GetCueByIndex, jlong jCues, jint index) {
  mkvmuxer::Cues* cues = reinterpret_cast<mkvmuxer::Cues*>(jCues);
  return reinterpret_cast<jlong>(cues->GetCueByIndex(index));
}

FUNCTION(void, deleteCues, jlong jCues) {
  mkvmuxer::Cues* cues = reinterpret_cast<mkvmuxer::Cues*>(jCues);
  delete cues;
}

FUNCTION(jlong, newCues) {
  jlong jCues = reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::Cues);
  return jCues;
}

FUNCTION(jboolean, outputBlockNumber, jlong jCues) {
  mkvmuxer::Cues* cues = reinterpret_cast<mkvmuxer::Cues*>(jCues);
  return cues->output_block_number();
}

FUNCTION(void, setOutputBlockNumber, jlong jCues,
                                     jboolean output_block_number) {
  mkvmuxer::Cues* cues = reinterpret_cast<mkvmuxer::Cues*>(jCues);
  cues->set_output_block_number(output_block_number);
}

FUNCTION(jboolean, Write, jlong jCues, jlong jWriter) {
  mkvmuxer::Cues* cues = reinterpret_cast<mkvmuxer::Cues*>(jCues);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return cues->Write(writer);
}
