// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Edition, functionName, ##__VA_ARGS__)

FUNCTION(jlong, GetAtom, jlong jEdition, jint index) {
  mkvparser::Chapters::Edition* edition =
      reinterpret_cast<mkvparser::Chapters::Edition*>(jEdition);
  return reinterpret_cast<jlong>(edition->GetAtom(index));
}

FUNCTION(jint, GetAtomCount, jlong jEdition) {
  mkvparser::Chapters::Edition* edition =
      reinterpret_cast<mkvparser::Chapters::Edition*>(jEdition);
  return edition->GetAtomCount();
}
