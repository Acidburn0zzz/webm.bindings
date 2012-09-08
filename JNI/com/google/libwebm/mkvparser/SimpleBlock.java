// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

public class SimpleBlock extends BlockEntry {

  public SimpleBlock(Cluster cluster, long index, long start, long size) {
    nativePointer = newSimpleBlock(cluster.getNativePointer(), index, start, size);
  }

  public Block getBlock() {
    long pointer = GetBlock(nativePointer);
    return new Block(pointer);
  }

  public Kind getKind() {
    int ordinal = GetKind(nativePointer);
    return Kind.values()[ordinal];
  }

  public long Parse() {
    return Parse(nativePointer);
  }

  protected SimpleBlock(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteSimpleBlock(nativePointer);
  }

  private native void deleteSimpleBlock(long jSimpleBlock);
  private native long GetBlock(long jSimpleBlock);
  private native int GetKind(long jSimpleBlock);
  private native long newSimpleBlock(long jCluster, long index, long start, long size);
  private native long Parse(long jSimpleBlock);
}
