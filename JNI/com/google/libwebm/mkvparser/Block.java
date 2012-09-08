// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class Block extends Common {

  public enum Lacing {
    kLacingNone,
    kLacingXiph,
    kLacingFixed,
    kLacingEbml
  }

  public Block() {
    nativePointer = newBlock();
  }

  public Frame getFrame(int frameIndex) {
    long pointer = GetFrame(nativePointer, frameIndex);
    return new Frame(pointer);
  }

  public int getFrameCount() {
    return GetFrameCount(nativePointer);
  }

  public Lacing getLacing() {
    int ordinal = GetLacing(nativePointer);
    return Lacing.values()[ordinal];
  }

  public long getSize() {
    return getSize(nativePointer);
  }

  public long getStart() {
    return getStart(nativePointer);
  }

  public long getTimeCode(Cluster cluster) {
    return GetTimeCode(nativePointer, cluster.getNativePointer());
  }

  public long getTrackNumber() {
    return GetTrackNumber(nativePointer);
  }

  public boolean isInvisible() {
    return IsInvisible(nativePointer);
  }

  public boolean isKey() {
    return IsKey(nativePointer);
  }

  public long parse(Cluster cluster) {
    return Parse(nativePointer, cluster.getNativePointer());
  }

  public void setKey(boolean key) {
    SetKey(nativePointer, key);
  }

  protected Block(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteBlock(nativePointer);
  }

  private native void deleteBlock(long jBlock);
  private native long GetFrame(long jBlock, int frameIndex);
  private native int GetFrameCount(long jBlock);
  private native int GetLacing(long jBlock);
  private native long getSize(long jBlock);
  private native long getStart(long jBlock);
  private native long GetTimeCode(long jBlock, long jCluster);
  private native long GetTrackNumber(long jBlock);
  private native boolean IsInvisible(long jBlock);
  private native boolean IsKey(long jBlock);
  private native long newBlock();
  private native long Parse(long jBlock, long jCluster);
  private native void SetKey(long jBlock, boolean key);
}
