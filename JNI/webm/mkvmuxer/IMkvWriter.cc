// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <typeinfo>

#include "common.h"
#include "mkvmuxer.hpp"
#include "mkvwriter.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, IMkvWriter, functionName, ##__VA_ARGS__)

FUNCTION(jint, getType, jlong jMkvWriter) {
  mkvmuxer::IMkvWriter* mkvWriter =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jMkvWriter);
  const std::type_info& typeInfo = typeid(*mkvWriter);
  int type = 0;
  if (typeInfo == typeid(mkvmuxer::MkvWriter)) {
    type = 1;
  }
  return type;
}
