// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class ContentEncAesSettings extends Common {

  public enum CipherMode {
    None,
    kCTR
  }

  public ContentEncAesSettings() {
    nativePointer = newContentEncAesSettings();
  }

  public long cipher_mode() {
    return cipher_mode(nativePointer);
  }

  public long size() {
    return Size(nativePointer);
  }

  public boolean write(IMkvWriter writer) {
    return Write(nativePointer, writer.getNativePointer());
  }

  protected ContentEncAesSettings(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteContentEncAesSettings(nativePointer);
  }

  private native long cipher_mode(long jContentEncAesSettings);
  private native void deleteContentEncAesSettings(long jContentEncAesSettings);
  private native long newContentEncAesSettings();
  private native long Size(long jContentEncAesSettings);
  private native boolean Write(long jContentEncAesSettings, long jWriter);
}
