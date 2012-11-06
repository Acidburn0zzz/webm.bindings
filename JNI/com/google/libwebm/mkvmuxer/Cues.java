// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class Cues extends Common {

  public Cues() {
    nativePointer = newCues();
  }

  public boolean addCue(CuePoint cue) {
    return AddCue(nativePointer, cue.getNativePointer());
  }

  public int cueEntriesSize() {
    return cue_entries_size(nativePointer);
  }

  public CuePoint getCueByIndex(int index) {
    long pointer = GetCueByIndex(nativePointer, index);
    return new CuePoint(pointer);
  }

  public boolean outputBlockNumber() {
    return output_block_number(nativePointer);
  }

  public void setOutputBlockNumber(boolean outputBlockNumber) {
    set_output_block_number(nativePointer, outputBlockNumber);
  }

  public boolean write(IMkvWriter writer) {
    return Write(nativePointer, writer.getNativePointer());
  }

  protected Cues(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteCues(nativePointer);
  }

  private native boolean AddCue(long jCues, long jCue);
  private native int cue_entries_size(long jCues);
  private native long GetCueByIndex(long jCues, int index);
  private native void deleteCues(long jCuePoint);
  private native long newCues();
  private native boolean output_block_number(long jCues);
  private native void set_output_block_number(long jCues, boolean output_block_number);
  private native boolean Write(long jCues, long jWriter);
}
