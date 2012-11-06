// Author: mszal@google.com (Michael Szal)

#include <jni.h>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, MkvMuxer, functionName, ##__VA_ARGS__)

FUNCTION(jboolean, WriteEbmlHeader, jlong jWriter) {
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return mkvmuxer::WriteEbmlHeader(writer);
}
