// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class Track extends Common {

  public static Track newTrack(long nativePointer) {
    Track track = null;
    int type = getClassType(nativePointer);
    if (type == 1) {
      track = new AudioTrack(nativePointer);
    } else if (type == 2) {
      track = new Track(nativePointer);
    } else if (type == 3) {
      track = new VideoTrack(nativePointer);
    }
    return track;
  }

  public Track(int seed) {
    nativePointer = newTrack(seed);
  }

  public boolean addContentEncoding() {
    return AddContentEncoding(nativePointer);
  }

  public String codecId() {
    return codec_id(nativePointer);
  }

  public byte[] codecPrivate() {
    return codec_private(nativePointer);
  }

  public long codecPrivateLength() {
    return codec_private_length(nativePointer);
  }

  public int contentEncodingEntriesSize() {
    return content_encoding_entries_size(nativePointer);
  }

  public ContentEncoding getContentEncodingByIndex(int index) {
    long pointer = GetContentEncodingByIndex(nativePointer, index);
    return new ContentEncoding(pointer);
  }

  public String language() {
    return language(nativePointer);
  }

  public String name() {
    return name(nativePointer);
  }

  public long number() {
    return number(nativePointer);
  }

  public long payloadSize() {
    return PayloadSize(nativePointer);
  }

  public void setCodecId(String codecId) {
    set_codec_id(nativePointer, codecId);
  }

  public boolean setCodecPrivate(byte[] codecPrivate) {
    return SetCodecPrivate(nativePointer, codecPrivate, codecPrivate.length);
  }

  public void setLanguage(String language) {
    set_language(nativePointer, language);
  }

  public void setName(String name) {
    set_name(nativePointer, name);
  }

  public void setNumber(long number) {
    set_number(nativePointer, number);
  }

  public void setType(long type) {
    set_type(nativePointer, type);
  }

  public long size() {
    return Size(nativePointer);
  }

  public long type() {
    return type(nativePointer);
  }

  public long uid() {
    return uid(nativePointer);
  }

  public boolean write(IMkvWriter writer) {
    return Write(nativePointer, writer.getNativePointer());
  }

  protected Track() {
  }

  protected Track(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteTrack(nativePointer);
  }

  private static native int getClassType(long jTrack);

  private native boolean AddContentEncoding(long jTrack);
  private native int content_encoding_entries_size(long jTrack);
  private native String codec_id(long jTrack);
  private native byte[] codec_private(long jTrack);
  private native long codec_private_length(long jTrack);
  private native void deleteTrack(long jTrack);
  private native long GetContentEncodingByIndex(long jTrack, int index);
  private native String language(long jTrack);
  private native String name(long jTrack);
  private native long newTrack(int jSeed);
  private native long number(long jTrack);
  private native long PayloadSize(long jTrack);
  private native void set_codec_id(long jTrack, String jCodecId);
  private native void set_language(long jTrack, String jLanguage);
  private native void set_name(long jTrack, String jName);
  private native void set_number(long jTrack, long number);
  private native void set_type(long jTrack, long type);
  private native boolean SetCodecPrivate(long jTrack, byte[] jCodecPrivate, long length);
  private native long Size(long jTrack);
  private native long type(long jTrack);
  private native long uid(long jTrack);
  private native boolean Write(long jTrack, long jWriter);
}
