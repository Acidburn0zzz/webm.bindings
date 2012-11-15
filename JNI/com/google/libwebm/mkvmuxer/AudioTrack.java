// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;
import java.util.HashMap;
import java.util.Map;

public class AudioTrack extends Track {

  public AudioTrack(int seed) {
    nativePointer = newAudioTrack(seed);
  }

  public long bitDepth() {
    return bitDepth(nativePointer);
  }

  public long channels() {
    return channels(nativePointer);
  }

  public long payloadSize() {
    return PayloadSize(nativePointer);
  }

  public double sampleRate() {
    return sampleRate(nativePointer);
  }

  public void setBitDepth(long bitDepth) {
    setBitDepth(nativePointer, bitDepth);
  }

  public void setChannels(long channels) {
    setChannels(nativePointer, channels);
  }

  public void setSampleRate(double sampleRate) {
    setSampleRate(nativePointer, sampleRate);
  }

  public boolean write(IMkvWriter writer) {
    return Write(nativePointer, writer.getNativePointer());
  }

  protected AudioTrack(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteAudioTrack(nativePointer);
  }

  private native long bitDepth(long jAudioTrack);
  private native long channels(long jAudioTrack);
  private native void deleteAudioTrack(long jAudioTrack);
  private native long newAudioTrack(int jSeed);
  private native long PayloadSize(long jAudioTrack);
  private native double sampleRate(long jAudioTrack);
  private native void setBitDepth(long jAudioTrack, long bit_depth);
  private native void setChannels(long jAudioTrack, long channels);
  private native void setSampleRate(long jAudioTrack, double sample_rate);
  private native boolean Write(long jAudioTrack, long jWriter);
}
