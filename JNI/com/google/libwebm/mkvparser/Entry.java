// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class Entry extends Common {

  public Entry() {
    nativePointer = newEntry();
  }

  public long getElementSize() {
    return getElementSize(nativePointer);
  }

  public long getElementStart() {
    return getElementStart(nativePointer);
  }

  public long getId() {
    return getId(nativePointer);
  }

  public long getPos() {
    return getPos(nativePointer);
  }

  public void setElementSize(long elementSize) {
    setElementSize(nativePointer, elementSize);
  }

  public void setElementStart(long elementStart) {
    setElementStart(nativePointer, elementStart);
  }

  public void setId(long id) {
    setId(nativePointer, id);
  }

  public void setPos(long pos) {
    setPos(nativePointer, pos);
  }

  protected Entry(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteEntry(nativePointer);
  }

  private native void deleteEntry(long jEntry);
  private native long getElementSize(long jEntry);
  private native long getElementStart(long jEntry);
  private native long getId(long jEntry);
  private native long getPos(long jEntry);
  private native long newEntry();
  private native void setElementSize(long jEntry, long element_size);
  private native void setElementStart(long jEntry, long element_start);
  private native void setId(long jEntry, long id);
  private native void setPos(long jEntry, long pos);
}
