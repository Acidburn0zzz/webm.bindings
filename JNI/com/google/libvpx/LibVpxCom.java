// Copyright 2012 Google Inc. All Rights Reserved.
// Author: frkoenig@google.com (Fritz Koenig)
package com.google.libvpx;

/**
 * Common parts of the codec that are shared by
 *  the encoder and decoder.
 */
public class LibVpxCom {
  static {
    System.loadLibrary("vpxJNI");
  }

  protected long vpxCodecIface;

  protected native String vpxCodecVersionStr();
  protected native String vpxCodecVersionExtraStr();
  protected native String vpxCodecBuildConfig();

  protected native boolean vpxCodecIsError(long ctx);
  protected native String vpxCodecErrToString(int err);
  protected native String vpxCodecError(long ctx);
  protected native String vpxCodecErrorDetail(long ctx);

  protected native long vpxCodecAllocCodec();
  protected native void vpxCodecFreeCodec(long cfg);

  protected native long vpxCodecAllocVpxImageI420(int width, int height);
  protected native void vpxCodecFreeVpxImage(long img);
  protected native void vpxCodecFillVpxImage(long img, byte[] frame);

  protected native void vpxCodecDestroy(long ctx);

  public String versionString() {
    return vpxCodecVersionStr();
  }

  public String versionExtraString() {
    return vpxCodecVersionExtraStr();
  }

  public String buildConfigString() {
    return vpxCodecBuildConfig();
  }

  public String errToString(int err) {
    return vpxCodecErrToString(err);
  }

  public String errorString() {
    return vpxCodecError(vpxCodecIface);
  }

  public String errorDetailString() {
    return vpxCodecErrorDetail(vpxCodecIface);
  }
}