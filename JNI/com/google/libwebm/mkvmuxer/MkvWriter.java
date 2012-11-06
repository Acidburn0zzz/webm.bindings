// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

public class MkvWriter extends IMkvWriter {

  public MkvWriter() {
    nativePointer = newMkvWriter();
  }

  public void close() {
    Close(nativePointer);
  }

  public void elementStartNotify(long elementId, long position) {
    ElementStartNotify(nativePointer, elementId, position);
  }

  public boolean open(String fileName) {
    return Open(nativePointer, fileName);
  }

  public long position() {
    return GetPosition(nativePointer);
  }

  public int position(long position) {
    return SetPosition(nativePointer, position);
  }

  public boolean seekable() {
    return Seekable(nativePointer);
  }

  public int write(byte[] buffer) {
    return Write(nativePointer, buffer, buffer.length);
  }

  protected MkvWriter(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteMkvWriter(nativePointer);
  }

  private native void Close(long jMkvWriter);
  private native void deleteMkvWriter(long jMkvWriter);
  private native void ElementStartNotify(long jMkvWriter, long element_id, long position);
  private native long GetPosition(long jMkvWriter);
  private native long newMkvWriter();
  private native boolean Open(long jMkvWriter, String jFilename);
  private native boolean Seekable(long jMkvWriter);
  private native int SetPosition(long jMkvWriter, long position);
  private native int Write(long jMkvWriter, byte[] jBuffer, int length);
}
