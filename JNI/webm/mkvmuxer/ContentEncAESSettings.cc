// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"

#define FUNCTION(returnType, functionName, ...) FUNC(returnType, mkvmuxer, \
    ContentEncAesSettings, functionName, ##__VA_ARGS__)

FUNCTION(jlong, cipherMode, jlong jContentEncAesSettings) {
  mkvmuxer::ContentEncAESSettings* contentEncAesSettings =
      reinterpret_cast<mkvmuxer::ContentEncAESSettings*>(
          jContentEncAesSettings);
  return contentEncAesSettings->cipher_mode();
}

FUNCTION(void, deleteContentEncAesSettings, jlong jContentEncAesSettings) {
  mkvmuxer::ContentEncAESSettings* contentEncAesSettings =
      reinterpret_cast<mkvmuxer::ContentEncAESSettings*>(
          jContentEncAesSettings);
  delete contentEncAesSettings;
}

FUNCTION(jlong, newContentEncAesSettings) {
  jlong jContentEncAesSettings = reinterpret_cast<jlong>(
      new (std::nothrow) mkvmuxer::ContentEncAESSettings);
  return jContentEncAesSettings;
}

FUNCTION(jlong, Size, jlong jContentEncAesSettings) {
  mkvmuxer::ContentEncAESSettings* contentEncAesSettings =
      reinterpret_cast<mkvmuxer::ContentEncAESSettings*>(
          jContentEncAesSettings);
  return contentEncAesSettings->Size();
}

FUNCTION(jboolean, Write, jlong jContentEncAesSettings, jlong jWriter) {
  mkvmuxer::ContentEncAESSettings* contentEncAesSettings =
      reinterpret_cast<mkvmuxer::ContentEncAESSettings*>(
          jContentEncAesSettings);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return contentEncAesSettings->Write(writer);
}
