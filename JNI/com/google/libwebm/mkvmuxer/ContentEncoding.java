// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class ContentEncoding extends Common {

  public ContentEncoding() {
    nativePointer = newContentEncoding();
  }

  public ContentEncAesSettings encAesSettings() {
    long pointer = enc_aes_settings(nativePointer);
    return new ContentEncAesSettings(pointer);
  }

  public long encAlgo() {
    return enc_algo(nativePointer);
  }

  public long encodingOrder() {
    return encoding_order(nativePointer);
  }

  public long encodingScope() {
    return encoding_scope(nativePointer);
  }

  public long encodingType() {
    return encoding_type(nativePointer);
  }

  public boolean setEncryptionId(byte[] id) {
    return SetEncryptionID(nativePointer, id, id.length);
  }

  public long size() {
    return Size(nativePointer);
  }

  public boolean write(IMkvWriter writer) {
    return Write(nativePointer, writer.getNativePointer());
  }

  protected ContentEncoding(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteContentEncoding(nativePointer);
  }

  private native void deleteContentEncoding(long jContentEncoding);
  private native long enc_aes_settings(long jContentEncoding);
  private native long enc_algo(long jContentEncoding);
  private native long encoding_order(long jContentEncoding);
  private native long encoding_scope(long jContentEncoding);
  private native long encoding_type(long jContentEncoding);
  private native long newContentEncoding();
  private native boolean SetEncryptionID(long jContentEncoding, byte[] jId, long length);
  private native long Size(long jContentEncoding);
  private native boolean Write(long jContentEncoding, long jWriter);
}
