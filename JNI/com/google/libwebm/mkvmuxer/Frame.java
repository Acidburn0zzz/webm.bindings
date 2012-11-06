// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class Frame extends Common {

  public Frame() {
    nativePointer = newFrame();
  }

  public byte[] frame() {
    return frame(nativePointer);
  }

  public boolean init(byte[] frame) {
    return Init(nativePointer, frame, frame.length);
  }

  public boolean isKey() {
    return is_key(nativePointer);
  }

  public long length() {
    return length(nativePointer);
  }

  public void setIsKey(boolean key) {
    set_is_key(nativePointer, key);
  }

  public void setTimestamp(long timestamp) {
    set_timestamp(nativePointer, timestamp);
  }

  public void setTrackNumber(long trackNumber) {
    set_track_number(nativePointer, trackNumber);
  }

  public long timestamp() {
    return timestamp(nativePointer);
  }

  public long trackNumber() {
    return track_number(nativePointer);
  }

  protected Frame(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteFrame(nativePointer);
  }

  private native void deleteFrame(long jFrame);
  private native byte[] frame(long jFrame);
  private native boolean Init(long jFrame, byte[] jFrameBuffer, long length);
  private native boolean is_key(long jFrame);
  private native long length(long jFrame);
  private native long newFrame();
  private native void set_is_key(long jFrame, boolean key);
  private native void set_timestamp(long jFrame, long timestamp);
  private native void set_track_number(long jFrame, long track_number);
  private native long timestamp(long jFrame);
  private native long track_number(long jFrame);
}
