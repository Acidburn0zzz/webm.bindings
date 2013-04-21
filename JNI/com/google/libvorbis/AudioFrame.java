package com.google.libvorbis;

import java.nio.ByteBuffer;

public class AudioFrame {
  public long timestamp;
  public ByteBuffer frame;

  AudioFrame(long time, ByteBuffer data) {
    timestamp = time;
    frame = data;
  }
}
