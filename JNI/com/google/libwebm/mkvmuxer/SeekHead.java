// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class SeekHead extends Common {

  public SeekHead() {
    nativePointer = newSeekHead();
  }

  public boolean addSeekEntry(int id, long pos) {
    return AddSeekEntry(nativePointer, id, pos);
  }

  public boolean finalizeSeekHead(IMkvWriter writer) {
    return Finalize(nativePointer, writer.getNativePointer());
  }

  public boolean write(IMkvWriter writer) {
    return Write(nativePointer, writer.getNativePointer());
  }

  protected SeekHead(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteSeekHead(nativePointer);
  }

  private native boolean AddSeekEntry(long jSeekHead, int id, long pos);
  private native void deleteSeekHead(long jSeekHead);
  private native boolean Finalize(long jSeekHead, long jWriter);
  private native long newSeekHead();
  private native boolean Write(long jSeekHead, long jWriter);
}
