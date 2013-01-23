// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "vorbis/codec.h"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, VorbisDspState, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteVorbisDspState, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  delete vorbisDspState;
}

FUNCTION(jint, getAnalysisp, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->analysisp;
}

FUNCTION(jlong, getBackendState, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return reinterpret_cast<jlong>(vorbisDspState->backend_state);
}

FUNCTION(jlong, getCenterW, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->centerW;
}

FUNCTION(jint, getEofflag, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->eofflag;
}

FUNCTION(jlong, getFloorBits, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->floor_bits;
}

FUNCTION(jlong, getGlueBits, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->glue_bits;
}

FUNCTION(jlong, getGranulepos, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->granulepos;
}

FUNCTION(jlong, getLW, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->lW;
}

FUNCTION(jlong, getNW, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->nW;
}

FUNCTION(jlong, getPcm, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return reinterpret_cast<jlong>(vorbisDspState->pcm);
}

FUNCTION(jint, getPcmCurrent, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->pcm_current;
}

FUNCTION(jlong, getPcmret, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return reinterpret_cast<jlong>(vorbisDspState->pcmret);
}

FUNCTION(jint, getPcmReturned, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->pcm_returned;
}

FUNCTION(jint, getPcmStorage, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->pcm_storage;
}

FUNCTION(jint, getPreextrapolate, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->preextrapolate;
}

FUNCTION(jlong, getResBits, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->res_bits;
}

FUNCTION(jlong, getSequence, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->sequence;
}

FUNCTION(jlong, getTimeBits, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->time_bits;
}

FUNCTION(jlong, getVi, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return reinterpret_cast<jlong>(vorbisDspState->vi);
}

FUNCTION(jlong, getW, jlong jVorbisDspState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  return vorbisDspState->W;
}

FUNCTION(jlong, newVorbisDspState) {
  jlong jVorbisDspState =
      reinterpret_cast<jlong>(new (std::nothrow) vorbis_dsp_state);
  return jVorbisDspState;
}

FUNCTION(void, setAnalysisp, jlong jVorbisDspState, jint analysisp) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->analysisp = analysisp;
}

FUNCTION(void, setBackendState, jlong jVorbisDspState, jlong backendState) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->backend_state = reinterpret_cast<void*>(backendState);
}

FUNCTION(void, setCenterW, jlong jVorbisDspState, jlong centerW) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->centerW = centerW;
}

FUNCTION(void, setEofflag, jlong jVorbisDspState, jint eofflag) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->eofflag = eofflag;
}

FUNCTION(void, setFloorBits, jlong jVorbisDspState, jlong floorBits) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->floor_bits = floorBits;
}

FUNCTION(void, setGlueBits, jlong jVorbisDspState, jlong glueBits) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->glue_bits = glueBits;
}

FUNCTION(void, setGranulepos, jlong jVorbisDspState, jlong granulepos) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->granulepos = granulepos;
}

FUNCTION(void, setLW, jlong jVorbisDspState, jlong lW) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->lW = lW;
}

FUNCTION(void, setNW, jlong jVorbisDspState, jlong nW) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->nW = nW;
}

FUNCTION(void, setPcm, jlong jVorbisDspState, jlong pcm) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->pcm = reinterpret_cast<float**>(pcm);
}

FUNCTION(void, setPcmCurrent, jlong jVorbisDspState, jint pcmCurrent) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->pcm_current = pcmCurrent;
}

FUNCTION(void, setPcmret, jlong jVorbisDspState, jlong pcmret) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->pcmret = reinterpret_cast<float**>(pcmret);
}

FUNCTION(void, setPcmReturned, jlong jVorbisDspState, jint pcmReturned) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->pcm_returned = pcmReturned;
}

FUNCTION(void, setPcmStorage, jlong jVorbisDspState, jint pcmStorage) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->pcm_storage = pcmStorage;
}

FUNCTION(void, setPreextrapolate, jlong jVorbisDspState, jint preextrapolate) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->preextrapolate = preextrapolate;
}

FUNCTION(void, setResBits, jlong jVorbisDspState, jlong resBits) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->res_bits = resBits;
}

FUNCTION(void, setSequence, jlong jVorbisDspState, jlong sequence) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->sequence = sequence;
}

FUNCTION(void, setTimeBits, jlong jVorbisDspState, jlong timeBits) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->time_bits = timeBits;
}

FUNCTION(void, setVi, jlong jVorbisDspState, jlong vi) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->vi = reinterpret_cast<vorbis_info*>(vi);
}

FUNCTION(void, setW, jlong jVorbisDspState, jlong W) {
  vorbis_dsp_state* vorbisDspState =
      reinterpret_cast<vorbis_dsp_state*>(jVorbisDspState);
  vorbisDspState->W = W;
}
