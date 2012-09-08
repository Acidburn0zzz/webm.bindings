// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class SegmentInfo extends Common {

  public SegmentInfo(Segment segment, long start, long size, long elementStart, long elementSize) {
    nativePointer =
        newSegmentInfo(segment.getNativePointer(), start, size, elementStart, elementSize);
  }

  public long getDuration() {
    return GetDuration(nativePointer);
  }

  public long getElementSize() {
    return getElementSize(nativePointer);
  }

  public long getElementStart() {
    return getElementStart(nativePointer);
  }

  public String getMuxingAppAsUtf8() {
    return GetMuxingAppAsUTF8(nativePointer);
  }

  public Segment getSegment() {
    long pointer = getSegment(nativePointer);
    return new Segment(pointer);
  }

  public long getSize() {
    return getSize(nativePointer);
  }

  public long getStart() {
    return getStart(nativePointer);
  }

  public long getTimeCodeScale() {
    return GetTimeCodeScale(nativePointer);
  }

  public String getTitleAsUtf8() {
    return GetTitleAsUTF8(nativePointer);
  }

  public String getWritingAppAsUtf8() {
    return GetWritingAppAsUTF8(nativePointer);
  }

  public long Parse() {
    return Parse(nativePointer);
  }

  protected SegmentInfo(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteSegmentInfo(nativePointer);
  }

  private native void deleteSegmentInfo(long jSegmentInfo);
  private native long GetDuration(long jSegmentInfo);
  private native long getElementSize(long jSegmentInfo);
  private native long getElementStart(long jSegmentInfo);
  private native String GetMuxingAppAsUTF8(long jSegmentInfo);
  private native long getSegment(long jSegmentInfo);
  private native long getSize(long jSegmentInfo);
  private native long getStart(long jSegmentInfo);
  private native long GetTimeCodeScale(long jSegmentInfo);
  private native String GetTitleAsUTF8(long jSegmentInfo);
  private native String GetWritingAppAsUTF8(long jSegmentInfo);
  private native long newSegmentInfo(long jSegment, long start, long size, long element_start,
      long element_size);
  private native long Parse(long jSegmentInfo);
}
