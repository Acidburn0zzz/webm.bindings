// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class Frame extends Common {

  public Frame() {
    nativePointer = newFrame();
  }

  public long getLen() {
    return getLen(nativePointer);
  }

  public long getPos() {
    return getPos(nativePointer);
  }

  public long Read(IMkvReader mkvReader, byte[][] buffer) {
    return Read(nativePointer, mkvReader.getNativePointer(), buffer);
  }

  public void setLen(long len) {
    setLen(nativePointer, len);
  }

  public void setPos(long pos) {
    setPos(nativePointer, pos);
  }

  protected Frame(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteFrame(nativePointer);
  }

  private native void deleteFrame(long jFrame);
  private native long getLen(long jFrame);
  private native long getPos(long jFrame);
  private native long newFrame();
  private native long Read(long jFrame, long jMkvReader, byte[][] jBuffer);
  private native void setLen(long jFrame, long len);
  private native void setPos(long jFrame, long pos);
}
