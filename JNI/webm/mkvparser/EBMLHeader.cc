// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>
#include <string.h>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, EbmlHeader, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteEBMLHeader, jlong jEbmlHeader) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  delete ebmlHeader;
}

FUNCTION(jstring, getDocType, jlong jEbmlHeader) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  jstring jDocType = env->NewStringUTF(ebmlHeader->m_docType);
  return jDocType;
}

FUNCTION(jlong, getDocTypeReadVersion, jlong jEbmlHeader) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  return ebmlHeader->m_docTypeReadVersion;
}

FUNCTION(jlong, getDocTypeVersion, jlong jEbmlHeader) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  return ebmlHeader->m_docTypeVersion;
}

FUNCTION(jlong, getMaxIdLength, jlong jEbmlHeader) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  return ebmlHeader->m_maxIdLength;
}

FUNCTION(jlong, getMaxSizeLength, jlong jEbmlHeader) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  return ebmlHeader->m_maxSizeLength;
}

FUNCTION(jlong, getReadVersion, jlong jEbmlHeader) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  return ebmlHeader->m_readVersion;
}

FUNCTION(jlong, getVersion, jlong jEbmlHeader) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  return ebmlHeader->m_version;
}

FUNCTION(void, Init, jlong jEbmlHeader) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  ebmlHeader->Init();
}

FUNCTION(jlong, newEBMLHeader) {
  jlong jEbmlHeader =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::EBMLHeader);
  return jEbmlHeader;
}

FUNCTION(jlong, Parse, jlong jEbmlHeader, jlong jMkvReader,
                       jlongArray jPosition) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  mkvparser::IMkvReader* mkvReader =
      reinterpret_cast<mkvparser::IMkvReader*>(jMkvReader);
  long long position = 0;
  long long result = ebmlHeader->Parse(mkvReader, position);
  jlong outputPosition = position;
  env->SetLongArrayRegion(jPosition, 0, 1, &outputPosition);
  return result;
}

FUNCTION(void, setDocType, jlong jEbmlHeader, jstring jDocType) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  const char* docType = env->GetStringUTFChars(jDocType, 0);
  size_t length = strlen(docType);
  delete[] ebmlHeader->m_docType;
  ebmlHeader->m_docType = new char[length + 1];
  strcpy(ebmlHeader->m_docType, docType);
  env->ReleaseStringUTFChars(jDocType, docType);
}

FUNCTION(void, setDocTypeReadVersion, jlong jEbmlHeader,
                                      jlong docTypeReadVersion) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  ebmlHeader->m_docTypeReadVersion = docTypeReadVersion;
}

FUNCTION(void, setDocTypeVersion, jlong jEbmlHeader, jlong docTypeVersion) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  ebmlHeader->m_docTypeVersion = docTypeVersion;
}

FUNCTION(void, setMaxIdLength, jlong jEbmlHeader, jlong maxIdLength) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  ebmlHeader->m_maxIdLength = maxIdLength;
}

FUNCTION(void, setMaxSizeLength, jlong jEbmlHeader, jlong maxSizeLength) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  ebmlHeader->m_maxSizeLength = maxSizeLength;
}

FUNCTION(void, setReadVersion, jlong jEbmlHeader, jlong readVersion) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  ebmlHeader->m_readVersion = readVersion;
}

FUNCTION(void, setVersion, jlong jEbmlHeader, jlong version) {
  mkvparser::EBMLHeader* ebmlHeader =
      reinterpret_cast<mkvparser::EBMLHeader*>(jEbmlHeader);
  ebmlHeader->m_version = version;
}
