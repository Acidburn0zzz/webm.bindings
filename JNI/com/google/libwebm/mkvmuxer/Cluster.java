// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class Cluster extends Common {

  public Cluster(long timecode, long cuesPos) {
    nativePointer = newCluster(timecode, cuesPos);
  }

  public boolean addFrame(byte[] frame, long trackNumber, long timecode, boolean isKey) {
    return AddFrame(nativePointer, frame, frame.length, trackNumber, timecode, isKey);
  }

  public boolean addMetadata(byte[] frame, long trackNumber, long timecode, long duration) {
    return AddMetadata(nativePointer, frame, frame.length, trackNumber, timecode, duration);
  }

  public void addPayloadSize(long size) {
    AddPayloadSize(nativePointer, size);
  }

  public int blocksAdded() {
    return blocks_added(nativePointer);
  }

  public boolean finalizeCluster() {
    return Finalize(nativePointer);
  }

  public boolean init(IMkvWriter writer) {
    return Init(nativePointer, writer.getNativePointer());
  }

  public long payloadSize() {
    return payload_size(nativePointer);
  }

  public long positionForCues() {
    return position_for_cues(nativePointer);
  }

  public long size() {
    return Size(nativePointer);
  }

  public long timecode() {
    return timecode(nativePointer);
  }

  protected Cluster(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteCluster(nativePointer);
  }

  private native boolean AddFrame(long jCluster, byte[] jFrame, long length, long track_number,
      long timecode, boolean is_key);
  private native boolean AddMetadata(long jCluster, byte[] jFrame, long length, long track_number,
      long timecode, long duration);
  private native void AddPayloadSize(long jCluster, long size);
  private native int blocks_added(long jCluster);
  private native void deleteCluster(long jCluster);
  private native boolean Finalize(long jCluster);
  private native boolean Init(long jCluster, long jWriter);
  private native long newCluster(long timecode, long cues_pos);
  private native long payload_size(long jCluster);
  private native long position_for_cues(long jCluster);
  private native long Size(long jCluster);
  private native long timecode(long jCluster);
}
