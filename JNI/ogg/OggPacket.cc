// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "ogg/ogg.h"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, OggPacket, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteOggPacket, jlong jOggPacket) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  delete oggPacket;
}

FUNCTION(jlong, getBOS, jlong jOggPacket) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  return oggPacket->b_o_s;
}

FUNCTION(jlong, getBytes, jlong jOggPacket) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  return oggPacket->bytes;
}

FUNCTION(jlong, getEOS, jlong jOggPacket) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  return oggPacket->e_o_s;
}

FUNCTION(jlong, getGranulepos, jlong jOggPacket) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  return oggPacket->granulepos;
}

FUNCTION(jlong, getPacket, jlong jOggPacket) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  return reinterpret_cast<jlong>(oggPacket->packet);
}

FUNCTION(jlong, getPacketno, jlong jOggPacket) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  return oggPacket->packetno;
}

FUNCTION(jlong, newOggPacket) {
  jlong jOggPacket = reinterpret_cast<jlong>(new (std::nothrow) ogg_packet);
  return jOggPacket;
}

FUNCTION(void, setBOS, jlong jOggPacket, jlong bOS) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  oggPacket->b_o_s = bOS;
}

FUNCTION(void, setBytes, jlong jOggPacket, jlong bytes) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  oggPacket->bytes = bytes;
}

FUNCTION(void, setEOS, jlong jOggPacket, jlong eOS) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  oggPacket->e_o_s = eOS;
}

FUNCTION(void, setGranulepos, jlong jOggPacket, jlong granulepos) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  oggPacket->granulepos = granulepos;
}

FUNCTION(void, setPacket, jlong jOggPacket, jlong packet) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  oggPacket->packet = reinterpret_cast<unsigned char*>(packet);
}

FUNCTION(void, setPacketno, jlong jOggPacket, jlong packetno) {
  ogg_packet* oggPacket = reinterpret_cast<ogg_packet*>(jOggPacket);
  oggPacket->packetno = packetno;
}
