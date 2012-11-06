// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;
import java.util.HashMap;
import java.util.Map;

public class VideoTrack extends Track {

  public enum StereoMode {
    kMono(0),
    kSideBySideLeftIsFirst(1),
    kTopBottomRightIsFirst(2),
    kTopBottomLeftIsFirst(3),
    kSideBySideRightIsFirst(11);

    private static final Map<Integer, StereoMode> stereoModes = new HashMap<Integer, StereoMode>();

    static {
      for (StereoMode mode : StereoMode.values()) {
        stereoModes.put(mode.toInt(), mode);
      }
    }

    private final int value;

    public static StereoMode toStereoMode(int value) {
      return stereoModes.get(value);
    }

    public int toInt() {
      return value;
    }

    private StereoMode(int value) {
      this.value = value;
    }
  };

  public VideoTrack(int seed) {
    nativePointer = newVideoTrack(seed);
  }

  public long displayHeight() {
    return display_height(nativePointer);
  }

  public long displayWidth() {
    return display_width(nativePointer);
  }

  public double frameRate() {
    return frame_rate(nativePointer);
  }

  public long height() {
    return height(nativePointer);
  }

  public long payloadSize() {
    return PayloadSize(nativePointer);
  }

  public void setDisplayHeight(long height) {
    set_display_height(nativePointer, height);
  }

  public void setDisplayWidth(long width) {
    set_display_width(nativePointer, width);
  }

  public void setFrameRate(double frameRate) {
    set_frame_rate(nativePointer, frameRate);
  }

  public void setHeight(long height) {
    set_height(nativePointer, height);
  }

  public void setStereoMode(StereoMode stereoMode) {
    SetStereoMode(nativePointer, stereoMode.toInt());
  }

  public void setWidth(long width) {
    set_width(nativePointer, width);
  }

  public StereoMode stereoMode() {
    return StereoMode.toStereoMode((int) stereo_mode(nativePointer));
  }

  public long width() {
    return width(nativePointer);
  }

  public boolean write(IMkvWriter writer) {
    return Write(nativePointer, writer.getNativePointer());
  }

  protected VideoTrack(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteVideoTrack(nativePointer);
  }

  private native void deleteVideoTrack(long jVideoTrack);
  private native long display_height(long jVideoTrack);
  private native long display_width(long jVideoTrack);
  private native double frame_rate(long jVideoTrack);
  private native long height(long jVideoTrack);
  private native long newVideoTrack(int jSeed);
  private native long PayloadSize(long jVideoTrack);
  private native void set_display_height(long jVideoTrack, long height);
  private native void set_display_width(long jVideoTrack, long width);
  private native void set_frame_rate(long jVideoTrack, double frame_rate);
  private native void set_height(long jVideoTrack, long height);
  private native void set_width(long jVideoTrack, long width);
  private native void SetStereoMode(long jVideoTrack, long stereo_mode);
  private native long stereo_mode(long jVideoTrack);
  private native long width(long jVideoTrack);
  private native boolean Write(long jVideoTrack, long jWriter);
}
