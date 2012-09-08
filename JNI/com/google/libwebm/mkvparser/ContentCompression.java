// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class ContentCompression extends Common {

  public ContentCompression() {
    nativePointer = newContentCompression();
  }

  public long getAlgo() {
    return getAlgo(nativePointer);
  }

  public void setAlgo(long algo) {
    setAlgo(nativePointer, algo);
  }

  protected ContentCompression(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteContentCompression(nativePointer);
  }

  private native void deleteContentCompression(long jContentCompression);
  private native long getAlgo(long jContentCompression);
  private native long newContentCompression();
  private native void setAlgo(long jContentCompression, long algo);
}
