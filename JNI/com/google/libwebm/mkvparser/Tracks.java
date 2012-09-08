// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class Tracks extends Common {

  public Tracks(Segment segment, long start, long size, long element_start, long element_size) {
    nativePointer = newTracks(segment.getNativePointer(), start, size, element_start, element_size);
  }

  public long getElementSize() {
    return getElementSize(nativePointer);
  }

  public long getElementStart() {
    return getElementStart(nativePointer);
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

  public Track getTrackByIndex(long idx) {
    long pointer = GetTrackByIndex(nativePointer, idx);
    return Track.newTrack(pointer);
  }

  public Track getTrackByNumber(long tn) {
    long pointer = GetTrackByNumber(nativePointer, tn);
    return Track.newTrack(pointer);
  }

  public long getTracksCount() {
    return GetTracksCount(nativePointer);
  }

  public long Parse() {
    return Parse(nativePointer);
  }

  protected Tracks(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteTracks(nativePointer);
  }

  private native void deleteTracks(long jTracks);
  private native long getElementSize(long jTracks);
  private native long getElementStart(long jTracks);
  private native long getSegment(long jTracks);
  private native long getSize(long jTracks);
  private native long getStart(long jTracks);
  private native long GetTrackByIndex(long jTracks, long idx);
  private native long GetTrackByNumber(long jTracks, long tn);
  private native long GetTracksCount(long jTracks);
  private native long newTracks(long jSegment, long start, long size, long element_start,
      long element_size);
  private native long Parse(long jTracks);
}
