// Copyright 2012 Google Inc. All Rights Reserved.
// Author: frkoenig@google.com (Fritz Koenig)
package com.google.libvpx;

import java.util.ArrayList;

/**
 * libvpx JNI wrapper for encoding functions.
 */
public class LibVpxEnc extends LibVpxCom {
  private native void vpxCodecEncInit(long encoder, long cfg);

  private native int vpxCodecEncCtlSetCpuUsed(long ctx, int value);
  private native int vpxCodecEncCtlSetEnableAutoAltRef(long ctx, int value);
  private native int vpxCodecEncCtlSetNoiseSensitivity(long ctx, int value);
  private native int vpxCodecEncCtlSetSharpness(long ctx, int value);
  private native int vpxCodecEncCtlSetStaticThreshold(long ctx, int value);
  private native int vpxCodecEncCtlSetTokenPartitions(long ctx, int value);
  private native int vpxCodecEncCtlSetARNRMaxFrames(long ctx, int value);
  private native int vpxCodecEncCtlSetARNRStrength(long ctx, int value);
  private native int vpxCodecEncCtlSetARNRType(long ctx, int value);
  private native int vpxCodecEncCtlSetTuning(long ctx, int value);
  private native int vpxCodecEncCtlSetCQLevel(long ctx, int value);
  private native int vpxCodecEncCtlSetMaxIntraBitratePct(long ctx, int value);

  private native boolean vpxCodecEncode(long ctx, byte[] frame,
                                        long pts, long duration,
                                        long flags, long deadline);

  private native ArrayList<VpxCodecCxPkt> vpxCodecEncGetCxData(long ctx);

  public LibVpxEnc(LibVpxEncConfig cfg) throws LibVpxException {
    vpxCodecIface = vpxCodecAllocCodec();
    if (vpxCodecIface == 0) {
      throw new LibVpxException("Can not allocate JNI codec object");
    }

    vpxCodecEncInit(vpxCodecIface, cfg.handle());
    if (isError()) {
      String errorMsg = vpxCodecErrorDetail(vpxCodecIface);
      vpxCodecFreeCodec(vpxCodecIface);
      throw new LibVpxException(errorMsg);
    }
  }

  public boolean isError() {
    return vpxCodecIsError(vpxCodecIface);
  }

  private void throwOnError() throws LibVpxException {
    if (vpxCodecIsError(vpxCodecIface)) {
      throw new LibVpxException(vpxCodecErrorDetail(vpxCodecIface));
    }
  }

  public ArrayList<VpxCodecCxPkt> encodeFrame(byte[] frame,
                                              long frameStart,
                                              long frameDuration) throws LibVpxException {
    if (!vpxCodecEncode(vpxCodecIface, frame, frameStart, frameDuration, 0L, 0L)) {
      throw new LibVpxException("Unable to allocate space to wrap image buffer");
    }
    throwOnError();
    return vpxCodecEncGetCxData(vpxCodecIface);
  }

  public void close() {
    vpxCodecDestroy(vpxCodecIface);
    vpxCodecFreeCodec(vpxCodecIface);
  }

  public void setCpuUsed(int value) throws LibVpxException {
    // TODO(frkoenig) : Investigate anonymous interface class to reduce duplication
    if (vpxCodecEncCtlSetCpuUsed(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set CpuUsed");
    }

    throwOnError();
  }

  public void setEnableAutoAltRef(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetEnableAutoAltRef(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to Enable Auto Alt Ref");
    }

    throwOnError();
  }

  public void setNoiseSensitivity(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetNoiseSensitivity(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set Noise Sensitivity");
    }

    throwOnError();
  }

  public void setSharpness(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetSharpness(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set Sharpness");
    }

    throwOnError();
  }

  public void setStaticThreshold(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetStaticThreshold(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set Static Threshold");
    }

    throwOnError();
  }

  public void setTokenPartitions(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetTokenPartitions(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set Token Partitions");
    }

    throwOnError();
  }

  public void setARNRMaxFrames(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetARNRMaxFrames(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set ARNR Max Frames");
    }

    throwOnError();
  }

  public void setARNRStrength(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetARNRStrength(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set ARNR Strength");
    }

    throwOnError();
  }

  public void setARNRType(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetARNRType(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set ARNRType");
    }

    throwOnError();
  }

  public void setTuning(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetTuning(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set Tuning");
    }

    throwOnError();
  }

  public void setCQLevel(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetCQLevel(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set CQLevel");
    }

    throwOnError();
  }

  public void setMaxIntraBitratePct(int value) throws LibVpxException {
    if (vpxCodecEncCtlSetMaxIntraBitratePct(vpxCodecIface, value) != 0) {
      throw new LibVpxException("Unable to set Max Intra Bitrate Pct");
    }

    throwOnError();
  }
}
