// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class SegmentInfo extends Common {

  public SegmentInfo() {
    nativePointer = newSegmentInfo();
  }

  public double duration() {
    return duration(nativePointer);
  }

  public boolean finalizeSegmentInfo(IMkvWriter writer) {
    return Finalize(nativePointer, writer.getNativePointer());
  }

  public boolean init() {
    return Init(nativePointer);
  }

  public String muxingApp() {
    return muxing_app(nativePointer);
  }

  public void setDuration(double duration) {
    set_duration(nativePointer, duration);
  }

  public void setMuxingApp(String app) {
    set_muxing_app(nativePointer, app);
  }

  public void setTimecodeScale(long scale) {
    set_timecode_scale(nativePointer, scale);
  }

  public void setWritingApp(String app) {
    set_writing_app(nativePointer, app);
  }

  public long timecodeScale() {
    return timecode_scale(nativePointer);
  }

  public boolean write(IMkvWriter writer) {
    return Write(nativePointer, writer.getNativePointer());
  }

  public String writingApp() {
    return writing_app(nativePointer);
  }

  protected SegmentInfo(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteSegmentInfo(nativePointer);
  }

  private native void deleteSegmentInfo(long jSegmentInfo);
  private native double duration(long jSegmentInfo);
  private native boolean Finalize(long jSegmentInfo, long jWriter);
  private native boolean Init(long jSegmentInfo);
  private native String muxing_app(long jSegmentInfo);
  private native long newSegmentInfo();
  private native void set_duration(long jSegmentInfo, double duration);
  private native void set_muxing_app(long jSegmentInfo, String jApp);
  private native void set_timecode_scale(long jSegmentInfo, long scale);
  private native void set_writing_app(long jSegmentInfo, String jApp);
  private native long timecode_scale(long jSegmentInfo);
  private native boolean Write(long jSegmentInfo, long jWriter);
  private native String writing_app(long jSegmentInfo);
}
