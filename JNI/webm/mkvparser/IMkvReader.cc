// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <typeinfo>

#include "common.h"
#include "mkvparser.hpp"
#include "mkvreader.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, IMkvReader, functionName, ##__VA_ARGS__)

FUNCTION(jint, getClassType, jlong jMkvReader) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  int type = 0;
  if (!mkvReader) {
    return type;
  }
  const std::type_info& typeInfo = typeid(*mkvReader);
  if (typeInfo == typeid(mkvparser::MkvReader)) {
    type = 1;
  }
  return type;
}
