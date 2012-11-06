// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class CuePoint extends Common {

  public CuePoint() {
    nativePointer = newCuePoint();
  }

  public long blockNumber() {
    return block_number(nativePointer);
  }

  public long clusterPos() {
    return cluster_pos(nativePointer);
  }

  public long outputBlockNumber() {
    return output_block_number(nativePointer);
  }

  public void setBlockNumber(long blockNumber) {
    set_block_number(nativePointer, blockNumber);
  }

  public void setClusterPos(long clusterPos) {
    set_cluster_pos(nativePointer, clusterPos);
  }

  public void setOutputBlockNumber(long outputBlockNumber) {
    set_output_block_number(nativePointer, outputBlockNumber);
  }

  public void setTime(long time) {
    set_time(nativePointer, time);
  }

  public void setTrack(long track) {
    set_track(nativePointer, track);
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

  private native long block_number(long jCuePoint);
  private native long cluster_pos(long jCuePoint);
  private native void deleteCuePoint(long jCuePoint);
  private native long newCuePoint();
  private native long output_block_number(long jCuePoint);
  private native void set_block_number(long jCuePoint, long block_number);
  private native void set_cluster_pos(long jCuePoint, long cluster_pos);
  private native void set_output_block_number(long jCuePoint, long output_block_number);
  private native void set_time(long jCuePoint, long time);
  private native void set_track(long jCuePoint, long track);
  private native long Size(long jCuePoint);
  private native long time(long jCuePoint);
  private native long track(long jCuePoint);
  private native boolean Write(long jCuePoint, long jWriter);
}
