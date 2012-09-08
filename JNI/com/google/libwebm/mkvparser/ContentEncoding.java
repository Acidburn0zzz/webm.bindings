// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvparser;

import com.google.libwebm.Common;

public class ContentEncoding extends Common {

  public enum CipherMode {
    None,
    kCTR
  }

  public ContentEncoding() {
    nativePointer = newContentEncoding();
  }

  public ContentCompression getCompressionByIndex(long index) {
    long pointer = GetCompressionByIndex(nativePointer, index);
    return new ContentCompression(pointer);
  }

  public long getCompressionCount() {
    return GetCompressionCount(nativePointer);
  }

  public long getEncodingOrder() {
    return encoding_order(nativePointer);
  }

  public long getEncodingScope() {
    return encoding_scope(nativePointer);
  }

  public long getEncodingType() {
    return encoding_type(nativePointer);
  }

  public ContentEncryption getEncryptionByIndex(long index) {
    long pointer = GetEncryptionByIndex(nativePointer, index);
    return new ContentEncryption(pointer);
  }

  public long getEncryptionCount() {
    return GetEncryptionCount(nativePointer);
  }

  public long parseContentEncAesSettingsEntry(long start, long size, IMkvReader mkvReader,
      ContentEncAesSettings contentEncAesSettings) {
    return ParseContentEncAESSettingsEntry(nativePointer, start, size, mkvReader.getNativePointer(),
        contentEncAesSettings.getNativePointer());
  }

  public long parseContentEncodingEntry(long start, long size, IMkvReader mkvReader) {
    return ParseContentEncodingEntry(nativePointer, start, size, mkvReader.getNativePointer());
  }

  public long parseEncryptionEntry(long start, long size, IMkvReader mkvReader,
      ContentEncryption contentEncryption) {
    return ParseEncryptionEntry(nativePointer, start, size, mkvReader.getNativePointer(),
        contentEncryption.getNativePointer());
  }

  protected ContentEncoding(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteContentEncoding(nativePointer);
  }


  private native void deleteContentEncoding(long jContentEncoding);
  private native long encoding_order(long jContentEncoding);
  private native long encoding_scope(long jContentEncoding);
  private native long encoding_type(long jContentEncoding);
  private native long GetCompressionByIndex(long jContentEncoding, long idx);
  private native long GetCompressionCount(long jContentEncoding);
  private native long GetEncryptionByIndex(long jContentEncoding, long idx);
  private native long GetEncryptionCount(long jContentEncoding);
  private native long newContentEncoding();
  private native long ParseContentEncAESSettingsEntry(long jContentEncoding, long start, long size,
      long jMkvReader, long jContentEncAesSettings);
  private native long ParseContentEncodingEntry(long jContentEncoding, long start, long size,
      long jMkvReader);
  private native long ParseEncryptionEntry(long jContentEncoding, long start, long size,
      long jMkvReader, long jContentEncryption);
}
