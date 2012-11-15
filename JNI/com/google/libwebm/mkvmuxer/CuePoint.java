// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class CuePoint extends Common {

  public CuePoint() {
    nativePointer = newCuePoint();
  }

  public long blockNumber() {
    return blockNumber(nativePointer);
  }

  public long clusterPos() {
    return clusterPos(nativePointer);
  }

  public long outputBlockNumber() {
    return outputBlockNumber(nativePointer);
  }

  public void setBlockNumber(long blockNumber) {
    setBlockNumber(nativePointer, blockNumber);
  }

  public void setClusterPos(long clusterPos) {
    setClusterPos(nativePointer, clusterPos);
  }

  public void setOutputBlockNumber(long outputBlockNumber) {
    setOutputBlockNumber(nativePointer, outputBlockNumber);
  }

  public void setTime(long time) {
    setTime(nativePointer, time);
  }

  public void setTrack(long track) {
    setTrack(nativePointer, track);
  }

  public long size() {
    return Size(nativePointer);
  }

  public long time() {
    return time(nativePointer);
  }

  public long track() {
    return track(nativePointer);
  }

  public boolean write(IMkvWriter writer) {
    return Write(nativePointer, writer.getNativePointer());
  }

  protected CuePoint(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteCuePoint(nativePointer);
  }

  private native long blockNumber(long jCuePoint);
  private native long clusterPos(long jCuePoint);
  private native void deleteCuePoint(long jCuePoint);
  private native long newCuePoint();
  private native long outputBlockNumber(long jCuePoint);
  private native void setBlockNumber(long jCuePoint, long block_number);
  private native void setClusterPos(long jCuePoint, long cluster_pos);
  private native void setOutputBlockNumber(long jCuePoint, long output_block_number);
  private native void setTime(long jCuePoint, long time);
  private native void setTrack(long jCuePoint, long track);
  private native long Size(long jCuePoint);
  private native long time(long jCuePoint);
  private native long track(long jCuePoint);
  private native boolean Write(long jCuePoint, long jWriter);
}
