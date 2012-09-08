// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class Settings extends Common {

  public Settings() {
    nativePointer = newSettings();
  }

  public long getSize() {
    return getSize(nativePointer);
  }

  public long getStart() {
    return getStart(nativePointer);
  }

  public void setSize(long size) {
    setSize(nativePointer, size);
  }

  public void setStart(long start) {
    setStart(nativePointer, start);
  }

  protected Settings(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteSettings(nativePointer);
  }

  private native void deleteSettings(long jSettings);
  private native long getSize(long jSettings);
  private native long getStart(long jSettings);
  private native long newSettings();
  private native void setSize(long jSettings, long size);
  private native void setStart(long jSettings, long start);
}
