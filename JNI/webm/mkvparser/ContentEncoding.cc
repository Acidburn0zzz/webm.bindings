// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, ContentEncoding, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteContentEncoding, jlong jContentEncoding) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  delete contentEncoding;
}

FUNCTION(jlong, encoding_order, jlong jContentEncoding) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  return contentEncoding->encoding_order();
}

FUNCTION(jlong, encoding_scope, jlong jContentEncoding) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  return contentEncoding->encoding_scope();
}

FUNCTION(jlong, encoding_type, jlong jContentEncoding) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  return contentEncoding->encoding_type();
}

FUNCTION(jlong, GetCompressionByIndex, jlong jContentEncoding, jlong idx) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  return reinterpret_cast<jlong>(contentEncoding->GetCompressionByIndex(idx));
}

FUNCTION(jlong, GetCompressionCount, jlong jContentEncoding) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  return contentEncoding->GetCompressionCount();
}

FUNCTION(jlong, GetEncryptionByIndex, jlong jContentEncoding, jlong idx) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  return reinterpret_cast<jlong>(contentEncoding->GetEncryptionByIndex(idx));
}

FUNCTION(jlong, GetEncryptionCount, jlong jContentEncoding) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  return contentEncoding->GetEncryptionCount();
}

FUNCTION(jlong, newContentEncoding) {
  jlong jContentEncoding =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::ContentEncoding);
  return jContentEncoding;
}

FUNCTION(jlong, ParseContentEncAESSettingsEntry, jlong jContentEncoding,
                                                 jlong start,
                                                 jlong size,
                                                 jlong jMkvReader,
                                                 jlong jContentEncAesSettings) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  mkvparser::ContentEncoding::ContentEncAESSettings* contentEncAesSettings =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncAESSettings*>(
          jContentEncAesSettings);
  return contentEncoding->ParseContentEncAESSettingsEntry(start, size,
      mkvReader, contentEncAesSettings);
}

FUNCTION(jlong, ParseContentEncodingEntry, jlong jContentEncoding, jlong start,
                                           jlong size, jlong jMkvReader) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  return contentEncoding->ParseContentEncodingEntry(start, size, mkvReader);
}

FUNCTION(jlong, ParseEncryptionEntry, jlong jContentEncoding,
                                      jlong start,
                                      jlong size,
                                      jlong jMkvReader,
                                      jlong jContentEncryption) {
  mkvparser::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvparser::ContentEncoding*>(jContentEncoding);
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  return contentEncoding->ParseEncryptionEntry(start, size, mkvReader,
                                               contentEncryption);
}
