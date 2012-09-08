// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class ContentEncAesSettings extends Common {

  public ContentEncAesSettings() {
    nativePointer = newContentEncAesSettings();
  }

  public ContentEncoding.CipherMode getCipherMode() {
    int ordinal = (int) getCipherMode(nativePointer);
    return ContentEncoding.CipherMode.values()[ordinal];
  }

  public void setCipherMode(ContentEncoding.CipherMode cipherMode) {
    setCipherMode(nativePointer, cipherMode.ordinal());
  }

  protected ContentEncAesSettings(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteContentEncAesSettings(nativePointer);
  }

  private native void deleteContentEncAesSettings(long jContentEncAesSettings);
  private native long getCipherMode(long jContentEncAesSettings);
  private native long newContentEncAesSettings();
  private native void setCipherMode(long jContentEncAesSettings, long cipherMode);
}
