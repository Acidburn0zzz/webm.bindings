// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <typeinfo>

#include "common.h"
#include "mkvreader.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, IMkvReader, functionName, ##__VA_ARGS__)

FUNCTION(jint, getType, jlong jMkvReader) {
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  const std::type_info& typeInfo = typeid(*mkvReader);
  int type = 0;
  if (typeInfo == typeid(mkvparser::MkvReader)) {
    type = 1;
  }
  return type;
}
