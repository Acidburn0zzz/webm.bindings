// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>
#include <string.h>

#include "common.h"
#include "ogg/ogg.h"
#include "vorbis/codec.h"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, VorbisBlock, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteVorbisBlock, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  delete vorbisBlock;
}

FUNCTION(jint, getEofflag, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->eofflag;
}

FUNCTION(jlong, getFloorBits, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->floor_bits;
}

FUNCTION(jlong, getGlueBits, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->glue_bits;
}

FUNCTION(jlong, getGranulepos, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->granulepos;
}

FUNCTION(jlong, getInternal, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return reinterpret_cast<jlong>(vorbisBlock->internal);
}

FUNCTION(jlong, getLocalalloc, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->localalloc;
}

FUNCTION(jlong, getLocalstore, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return reinterpret_cast<jlong>(vorbisBlock->localstore);
}

FUNCTION(jlong, getLocaltop, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->localtop;
}

FUNCTION(jlong, getLW, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->lW;
}

FUNCTION(jint, getMode, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->mode;
}

FUNCTION(jlong, getNW, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->nW;
}

FUNCTION(jlong, getOpb, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return reinterpret_cast<jlong>(&vorbisBlock->opb);
}

FUNCTION(jlong, getPcm, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return reinterpret_cast<jlong>(vorbisBlock->pcm);
}

FUNCTION(jint, getPcmend, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->pcmend;
}

FUNCTION(jlong, getReap, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return reinterpret_cast<jlong>(vorbisBlock->reap);
}

FUNCTION(jlong, getResBits, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->res_bits;
}

FUNCTION(jlong, getSequence, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->sequence;
}

FUNCTION(jlong, getTimeBits, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->time_bits;
}

FUNCTION(jlong, getTotaluse, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->totaluse;
}

FUNCTION(jlong, getVd, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return reinterpret_cast<jlong>(vorbisBlock->vd);
}

FUNCTION(jlong, getW, jlong jVorbisBlock) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  return vorbisBlock->W;
}

FUNCTION(jlong, newVorbisBlock) {
  jlong jVorbisBlock = reinterpret_cast<jlong>(new (std::nothrow) vorbis_block);
  return jVorbisBlock;
}

FUNCTION(void, setEofflag, jlong jVorbisBlock, jint eofflag) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->eofflag = eofflag;
}

FUNCTION(void, setFloorBits, jlong jVorbisBlock, jlong floorBits) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->floor_bits = floorBits;
}

FUNCTION(void, setGlueBits, jlong jVorbisBlock, jlong glueBits) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->glue_bits = glueBits;
}

FUNCTION(void, setGranulepos, jlong jVorbisBlock, jlong granulepos) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->granulepos = granulepos;
}

FUNCTION(void, setInternal, jlong jVorbisBlock, jlong internal) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->internal = reinterpret_cast<void*>(internal);
}

FUNCTION(void, setLocalalloc, jlong jVorbisBlock, jlong localalloc) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->localalloc = localalloc;
}

FUNCTION(void, setLocalstore, jlong jVorbisBlock, jlong localstore) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->localstore = reinterpret_cast<void*>(localstore);
}

FUNCTION(void, setLocaltop, jlong jVorbisBlock, jlong localtop) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->localtop = localtop;
}

FUNCTION(void, setLW, jlong jVorbisBlock, jlong lW) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->lW = lW;
}

FUNCTION(void, setMode, jlong jVorbisBlock, jint mode) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->mode = mode;
}

FUNCTION(void, setNW, jlong jVorbisBlock, jlong nW) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->nW = nW;
}

FUNCTION(void, setOpb, jlong jVorbisBlock, jlong opb) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  memcpy(&vorbisBlock->opb, reinterpret_cast<const void*>(opb),
         sizeof(oggpack_buffer));
}

FUNCTION(void, setPcm, jlong jVorbisBlock, jlong pcm) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->pcm = reinterpret_cast<float**>(pcm);
}

FUNCTION(void, setPcmend, jlong jVorbisBlock, jint pcmend) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->pcmend = pcmend;
}

FUNCTION(void, setReap, jlong jVorbisBlock, jlong reap) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->reap = reinterpret_cast<alloc_chain*>(reap);
}

FUNCTION(void, setResBits, jlong jVorbisBlock, jlong resBits) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->res_bits = resBits;
}

FUNCTION(void, setSequence, jlong jVorbisBlock, jlong sequence) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->sequence = sequence;
}

FUNCTION(void, setTimeBits, jlong jVorbisBlock, jlong timeBits) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->time_bits = timeBits;
}

FUNCTION(void, setTotaluse, jlong jVorbisBlock, jlong totaluse) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->totaluse = totaluse;
}

FUNCTION(void, setVd, jlong jVorbisBlock, jlong vd) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->vd = reinterpret_cast<vorbis_dsp_state*>(vd);
}

FUNCTION(void, setW, jlong jVorbisBlock, jlong w) {
  vorbis_block* vorbisBlock = reinterpret_cast<vorbis_block*>(jVorbisBlock);
  vorbisBlock->W = w;
}
