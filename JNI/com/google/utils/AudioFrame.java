package com.google.utils;

public class AudioFrame {
  public long timestamp;
  public byte[] frame;

  public AudioFrame(long time, byte[] data) {
    timestamp = time;
    frame = data;
  }
}