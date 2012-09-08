// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class CuePoint extends Common {

  public TrackPosition find(Track track) {
    long pointer = Find(nativePointer, track.getNativePointer());
    return new TrackPosition(pointer);
  }

  public long getElementSize() {
    return getElementSize(nativePointer);
  }

  public long getElementStart() {
    return getElementStart(nativePointer);
  }

  public long getTime(Segment segment) {
    return GetTime(nativePointer, segment.getNativePointer());
  }

  public long getTimeCode() {
    return GetTimeCode(nativePointer);
  }

  public void load(IMkvReader mkvReader) {
    Load(nativePointer, mkvReader.getNativePointer());
  }

  public void setElementSize(long elementSize) {
    setElementSize(nativePointer, elementSize);
  }

  public void setElementStart(long elementStart) {
    setElementStart(nativePointer, elementStart);
  }

  protected CuePoint(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
  }

  private native long Find(long jCuePoint, long jTrack);
  private native long getElementSize(long jCuePoint);
  private native long getElementStart(long jCuePoint);
  private native long GetTime(long jCuePoint, long jSegment);
  private native long GetTimeCode(long jCuePoint);
  private native void Load(long jCuePoint, long jMkvReader);
  private native void setElementSize(long jCuePoint, long element_size);
  private native void setElementStart(long jCuePoint, long element_start);
}
