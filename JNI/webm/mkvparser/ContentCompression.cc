// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, ContentCompression, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteContentCompression, jlong jContentCompression) {
  mkvparser::ContentEncoding::ContentCompression* contentCompression =
      reinterpret_cast<mkvparser::ContentEncoding::ContentCompression*>(
          jContentCompression);
  delete contentCompression;
}

FUNCTION(jlong, getAlgo, jlong jContentCompression) {
  mkvparser::ContentEncoding::ContentCompression* contentCompression =
      reinterpret_cast<mkvparser::ContentEncoding::ContentCompression*>(
          jContentCompression);
  return contentCompression->algo;
}

FUNCTION(jlong, newContentCompression) {
  jlong jContentCompression = reinterpret_cast<jlong>(
      new (std::nothrow) mkvparser::ContentEncoding::ContentCompression);
  return jContentCompression;
}

FUNCTION(void, setAlgo, jlong jContentCompression, jlong algo) {
  mkvparser::ContentEncoding::ContentCompression* contentCompression =
      reinterpret_cast<mkvparser::ContentEncoding::ContentCompression*>(
          jContentCompression);
  contentCompression->algo = algo;
}

// I don't know what ContentCompression::settings is.  I assume it points to
// binary data, but the length isn't specified anywhere.
