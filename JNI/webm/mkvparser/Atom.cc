// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Atom, functionName, ##__VA_ARGS__)

FUNCTION(jlong, GetDisplay, jlong jAtom, jint index) {
  mkvparser::Chapters::Atom* atom =
      reinterpret_cast<mkvparser::Chapters::Atom*>(jAtom);
  return reinterpret_cast<jlong>(atom->GetDisplay(index));
}

FUNCTION(jint, GetDisplayCount, jlong jAtom) {
  mkvparser::Chapters::Atom* atom =
      reinterpret_cast<mkvparser::Chapters::Atom*>(jAtom);
  return atom->GetDisplayCount();
}

FUNCTION(jlong, GetStartTime, jlong jAtom, jlong jChapters) {
  mkvparser::Chapters::Atom* atom =
      reinterpret_cast<mkvparser::Chapters::Atom*>(jAtom);
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  return atom->GetStartTime(chapters);
}

FUNCTION(jlong, GetStartTimecode, jlong jAtom) {
  mkvparser::Chapters::Atom* atom =
      reinterpret_cast<mkvparser::Chapters::Atom*>(jAtom);
  return atom->GetStartTimecode();
}

FUNCTION(jlong, GetStopTime, jlong jAtom, jlong jChapters) {
  mkvparser::Chapters::Atom* atom =
      reinterpret_cast<mkvparser::Chapters::Atom*>(jAtom);
  mkvparser::Chapters* chapters =
      reinterpret_cast<mkvparser::Chapters*>(jChapters);
  return atom->GetStopTime(chapters);
}

FUNCTION(jlong, GetStopTimecode, jlong jAtom) {
  mkvparser::Chapters::Atom* atom =
      reinterpret_cast<mkvparser::Chapters::Atom*>(jAtom);
  return atom->GetStopTimecode();
}

FUNCTION(jstring, GetStringUID, jlong jAtom) {
  mkvparser::Chapters::Atom* atom =
      reinterpret_cast<mkvparser::Chapters::Atom*>(jAtom);
  return env->NewStringUTF(atom->GetStringUID());
}

FUNCTION(jlong, GetUID, jlong jAtom) {
  mkvparser::Chapters::Atom* atom =
      reinterpret_cast<mkvparser::Chapters::Atom*>(jAtom);
  return atom->GetUID();
}
