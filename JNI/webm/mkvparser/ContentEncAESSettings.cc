// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) FUNC(returnType, mkvparser, \
    ContentEncAESSettings, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteContentEncAESSettings, jlong jContentEncAesSettings) {
  mkvparser::ContentEncoding::ContentEncAESSettings* contentEncAesSettings =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncAESSettings*>(
          jContentEncAesSettings);
  delete contentEncAesSettings;
}

FUNCTION(jlong, getCipherMode, jlong jContentEncAesSettings) {
  mkvparser::ContentEncoding::ContentEncAESSettings* contentEncAesSettings =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncAESSettings*>(
          jContentEncAesSettings);
  return contentEncAesSettings->cipher_mode;
}

FUNCTION(jlong, newContentEncAESSettings) {
  jlong jContentEncAesSettings = reinterpret_cast<jlong>(
      new (std::nothrow) mkvparser::ContentEncoding::ContentEncAESSettings);
  return jContentEncAesSettings;
}

FUNCTION(void, setCipherMode, jlong jContentEncAesSettings, jlong cipherMode) {
  mkvparser::ContentEncoding::ContentEncAESSettings* contentEncAesSettings =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncAESSettings*>(
          jContentEncAesSettings);
  contentEncAesSettings->cipher_mode = cipherMode;
}
