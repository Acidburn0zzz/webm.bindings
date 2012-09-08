// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

public class MkvReader extends IMkvReader {

  public MkvReader() {
    nativePointer = newMkvReader();
  }

  public void close() {
    Close(nativePointer);
  }

  public boolean isOpen() {
    return IsOpen(nativePointer);
  }

  public int length(long[] total, long[] available) {
    return Length(nativePointer, total, available);
  }

  public int open(String fileName) {
    return Open(nativePointer, fileName);
  }

  public int read(long position, long length, byte[][] buffer) {
    return Read(nativePointer, position, length, buffer);
  }

  protected MkvReader(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteMkvReader(nativePointer);
  }

  private native void Close(long jMkvReader);
  private native void deleteMkvReader(long jMkvReader);
  private native boolean IsOpen(long jMkvReader);
  private native int Length(long jMkvReader, long[] jTotal, long[] jAvailable);
  private native long newMkvReader();
  private native int Open(long jMkvReader, String jFileName);
  private native int Read(long jMkvReader, long position, long length, byte[][] jBuffer);
}
