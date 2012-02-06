// Copyright 2012 Google Inc. All Rights Reserved.
// Author: frkoenig@google.com (Fritz Koenig)
package com.google.libvpx;

/**
 * libvpx JNI wrapper for decoding functions.
 */
public class LibVpxDec extends LibVpxCom {
  private long decCfgObj;
  private boolean postProcEnabled;
  private boolean errorConcealmentEnabled;

  private native long vpxCodecDecAllocCfg();
  private native void vpxCodecDecFreeCfg(long cfg);

  private native void vpxCodecDecSetThreads(long cfg, int value);
  private native void vpxCodecDecSetWidth(long cfg, int value);
  private native void vpxCodecDecSetHeight(long cfg, int value);
  private native int vpxCodecDecGetThreads(long cfg);
  private native int vpxCodecDecGetWidth(long cfg);
  private native int vpxCodecDecGetHeight(long cfg);

  private native int vpxCodecDecInit(long decoder, long cfg,
                                     boolean postproc, boolean ecEnabled);
  private native int vpxCodecDecDecode(long decoder, byte[] buf, int bufSize);

  public LibVpxDec(int width, int height, int threads,
                   boolean postProcEnabled, boolean errorConcealmentEnabled) {
    decCfgObj = vpxCodecDecAllocCfg();
    vpxCodecIface = vpxCodecAllocCodec();
    postProcEnabled = false;
    errorConcealmentEnabled = false;

    if (width > 0) {
      vpxCodecDecSetWidth(decCfgObj, width);
    }

    if (height > 0) {
      vpxCodecDecSetHeight(decCfgObj, height);
    }

    if (threads > 0) {
      vpxCodecDecSetThreads(decCfgObj, threads);
    }

    // TODO(frkoenig): need to check this return value.
    vpxCodecDecInit(vpxCodecIface, decCfgObj,
                    postProcEnabled, errorConcealmentEnabled);
  }

  public LibVpxDec(boolean postProcEnabled, boolean errorConcealmentEnabled) {
    this(0, 0, 0, postProcEnabled, errorConcealmentEnabled);
  }

  public LibVpxDec() {
    this(0, 0, 0, false, false);
  }

  public int decodeFrame(byte[] rawFrame) {
    return vpxCodecDecDecode(vpxCodecIface, rawFrame, rawFrame.length);
  }

  public void close() {
    vpxCodecDestroy(vpxCodecIface);
    vpxCodecDecFreeCfg(decCfgObj);
    vpxCodecFreeCodec(vpxCodecIface);
  }
}
