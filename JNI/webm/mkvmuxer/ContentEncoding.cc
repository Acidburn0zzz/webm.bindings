// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvmuxer.hpp"
#include "mkvmuxertypes.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvmuxer, ContentEncoding, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteContentEncoding, jlong jContentEncoding) {
  mkvmuxer::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvmuxer::ContentEncoding*>(jContentEncoding);
  delete contentEncoding;
}

FUNCTION(jlong, enc_aes_settings, jlong jContentEncoding) {
  mkvmuxer::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvmuxer::ContentEncoding*>(jContentEncoding);
  return reinterpret_cast<jlong>(contentEncoding->enc_aes_settings());
}

FUNCTION(jlong, enc_algo, jlong jContentEncoding) {
  mkvmuxer::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvmuxer::ContentEncoding*>(jContentEncoding);
  return contentEncoding->enc_algo();
}

FUNCTION(jlong, encoding_order, jlong jContentEncoding) {
  mkvmuxer::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvmuxer::ContentEncoding*>(jContentEncoding);
  return contentEncoding->encoding_order();
}

FUNCTION(jlong, encoding_scope, jlong jContentEncoding) {
  mkvmuxer::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvmuxer::ContentEncoding*>(jContentEncoding);
  return contentEncoding->encoding_scope();
}

FUNCTION(jlong, encoding_type, jlong jContentEncoding) {
  mkvmuxer::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvmuxer::ContentEncoding*>(jContentEncoding);
  return contentEncoding->encoding_type();
}

FUNCTION(jlong, newContentEncoding) {
  jlong jContentEncoding =
      reinterpret_cast<jlong>(new (std::nothrow) mkvmuxer::ContentEncoding);
  return jContentEncoding;
}

FUNCTION(jboolean, SetEncryptionID, jlong jContentEncoding, jbyteArray jId,
                                    jlong length) {
  mkvmuxer::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvmuxer::ContentEncoding*>(jContentEncoding);
  char* id = new char[length];
  env->GetByteArrayRegion(jId, 0, length, reinterpret_cast<jbyte*>(id));
  bool result = contentEncoding->SetEncryptionID(
      reinterpret_cast<const mkvmuxer::uint8*>(id), length);
  delete[] id;
  return result;
}

FUNCTION(jlong, Size, jlong jContentEncoding) {
  mkvmuxer::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvmuxer::ContentEncoding*>(jContentEncoding);
  return contentEncoding->Size();
}

FUNCTION(jboolean, Write, jlong jContentEncoding, jlong jWriter) {
  mkvmuxer::ContentEncoding* contentEncoding =
      reinterpret_cast<mkvmuxer::ContentEncoding*>(jContentEncoding);
  mkvmuxer::IMkvWriter* writer =
      reinterpret_cast<mkvmuxer::IMkvWriter*>(jWriter);
  return contentEncoding->Write(writer);
}
