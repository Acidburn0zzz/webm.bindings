// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>
#include <string.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, ContentEncryption, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteContentEncryption, jlong jContentEncryption) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  delete contentEncryption;
}

FUNCTION(jlong, getAesSettings, jlong jContentEncryption) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  return reinterpret_cast<jlong>(&contentEncryption->aes_settings);
}

FUNCTION(jlong, getAlgo, jlong jContentEncryption) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  return contentEncryption->algo;
}

FUNCTION(jbyteArray, getKeyId, jlong jContentEncryption) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  return newByteArray(env, contentEncryption->key_id,
                      contentEncryption->key_id_len);
}

FUNCTION(jlong, getSigAlgo, jlong jContentEncryption) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  return contentEncryption->sig_algo;
}

FUNCTION(jlong, getSigHashAlgo, jlong jContentEncryption) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  return contentEncryption->sig_hash_algo;
}

FUNCTION(jbyteArray, getSigKeyId, jlong jContentEncryption) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  return newByteArray(env, contentEncryption->sig_key_id,
                      contentEncryption->sig_key_id_len);
}

FUNCTION(jbyteArray, getSignature, jlong jContentEncryption) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  return newByteArray(env, contentEncryption->signature,
                      contentEncryption->signature_len);
}

FUNCTION(jlong, newContentEncryption) {
  jlong jContentEncryption = reinterpret_cast<jlong>(
      new (std::nothrow) mkvparser::ContentEncoding::ContentEncryption);
  return jContentEncryption;
}

FUNCTION(void, setAesSettings, jlong jContentEncryption, jlong aesSettings) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  memcpy(&contentEncryption->aes_settings,
         reinterpret_cast<const void*>(aesSettings),
         sizeof(contentEncryption->aes_settings));
}

FUNCTION(void, setAlgo, jlong jContentEncryption, jlong algo) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  contentEncryption->algo = algo;
}

FUNCTION(void, setKeyId, jlong jContentEncryption, jbyteArray jKeyId) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  setBuffer(env, jKeyId, &contentEncryption->key_id,
            &contentEncryption->key_id_len);
}

FUNCTION(void, setSigAlgo, jlong jContentEncryption, jlong sigAlgo) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  contentEncryption->sig_algo = sigAlgo;
}

FUNCTION(void, setSigHashAlgo, jlong jContentEncryption, jlong sigHashAlgo) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  contentEncryption->sig_hash_algo = sigHashAlgo;
}

FUNCTION(void, setSigKeyId, jlong jContentEncryption, jbyteArray jSigKeyId) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  setBuffer(env, jSigKeyId, &contentEncryption->sig_key_id,
            &contentEncryption->sig_key_id_len);
}

FUNCTION(void, setSignature, jlong jContentEncryption, jbyteArray jSignature) {
  mkvparser::ContentEncoding::ContentEncryption* contentEncryption =
      reinterpret_cast<mkvparser::ContentEncoding::ContentEncryption*>(
          jContentEncryption);
  setBuffer(env, jSignature, &contentEncryption->signature,
            &contentEncryption->signature_len);
}
