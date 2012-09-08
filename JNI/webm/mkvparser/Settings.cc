// Author: mszal@google.com (Michael Szal)

#include <jni.h>
#include <new>

#include "common.h"
#include "mkvparser.hpp"

#define FUNCTION(returnType, functionName, ...) \
    FUNC(returnType, mkvparser, Settings, functionName, ##__VA_ARGS__)

FUNCTION(void, deleteSettings, jlong jSettings) {
  mkvparser::Track::Settings* settings =
      reinterpret_cast<mkvparser::Track::Settings*>(jSettings);
  delete settings;
}

FUNCTION(jlong, getSize, jlong jSettings) {
  mkvparser::Track::Settings* settings =
      reinterpret_cast<mkvparser::Track::Settings*>(jSettings);
  return settings->size;
}

FUNCTION(jlong, getStart, jlong jSettings) {
  mkvparser::Track::Settings* settings =
      reinterpret_cast<mkvparser::Track::Settings*>(jSettings);
  return settings->start;
}

FUNCTION(jlong, newSettings) {
  jlong jSettings =
      reinterpret_cast<jlong>(new (std::nothrow) mkvparser::Track::Settings);
  return jSettings;
}

FUNCTION(void, setSize, jlong jSettings, jlong size) {
  mkvparser::Track::Settings* settings =
      reinterpret_cast<mkvparser::Track::Settings*>(jSettings);
  settings->size = size;
}

FUNCTION(void, setStart, jlong jSettings, jlong start) {
  mkvparser::Track::Settings* settings =
      reinterpret_cast<mkvparser::Track::Settings*>(jSettings);
  settings->start = start;
}
