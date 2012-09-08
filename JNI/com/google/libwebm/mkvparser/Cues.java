// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class Cues extends Common {

  public boolean doneParsing() {
    return DoneParsing(nativePointer);
  }

  public boolean find(long timeNs, Track track, CuePoint[] cuePoint,
      TrackPosition[] trackPosition) {
    long[] jCuePoint = {0};
    long[] jTrackPosition = {0};
    boolean result =
        Find(nativePointer, timeNs, track.getNativePointer(), jCuePoint, jTrackPosition);
    cuePoint[0] = new CuePoint(jCuePoint[0]);
    return result;
  }

  public long getCount() {
    return GetCount(nativePointer);
  }

  public long getElementSize() {
    return getElementSize(nativePointer);
  }

  public long getElementStart() {
    return getElementStart(nativePointer);
  }

  public CuePoint getFirst() {
    long pointer = GetFirst(nativePointer);
    return new CuePoint(pointer);
  }

  public CuePoint getLast() {
    long pointer = GetLast(nativePointer);
    return new CuePoint(pointer);
  }

  public CuePoint getNext(CuePoint current) {
    long pointer = GetNext(nativePointer, current.getNativePointer());
    return new CuePoint(pointer);
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

  public boolean loadCuePoint() {
    return LoadCuePoint(nativePointer);
  }

  protected Cues(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
  }

  private native boolean DoneParsing(long jCues);
  private native boolean Find(long jCues, long time_ns, long jTrack, long[] jCuePoint,
      long[] jTrackPosition);
  private native long GetCount(long jCues);
  private native long getElementSize(long jCues);
  private native long getElementStart(long jCues);
  private native long GetFirst(long jCues);
  private native long GetLast(long jCues);
  private native long GetNext(long jCues, long jCurrent);
  private native long getSegment(long jCues);
  private native long getSize(long jCues);
  private native long getStart(long jCues);
  private native boolean LoadCuePoint(long jCues);
}
