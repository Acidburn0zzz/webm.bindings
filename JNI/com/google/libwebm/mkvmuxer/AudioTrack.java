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
    return bit_depth(nativePointer);
  }

  public long channels() {
    return channels(nativePointer);
  }

  public long payloadSize() {
    return PayloadSize(nativePointer);
  }

  public double sampleRate() {
    return sample_rate(nativePointer);
  }

  public void setBitDepth(long bitDepth) {
    set_bit_depth(nativePointer, bitDepth);
  }

  public void setChannels(long channels) {
    set_channels(nativePointer, channels);
  }

  public void setSampleRate(double sampleRate) {
    set_sample_rate(nativePointer, sampleRate);
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

  private native long bit_depth(long jAudioTrack);
  private native long channels(long jAudioTrack);
  private native void deleteAudioTrack(long jAudioTrack);
  private native long newAudioTrack(int jSeed);
  private native long PayloadSize(long jAudioTrack);
  private native double sample_rate(long jAudioTrack);
  private native void set_bit_depth(long jAudioTrack, long bit_depth);
  private native void set_channels(long jAudioTrack, long channels);
  private native void set_sample_rate(long jAudioTrack, double sample_rate);
  private native boolean Write(long jAudioTrack, long jWriter);
}
