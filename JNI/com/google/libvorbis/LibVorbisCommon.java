// Author: mszal@google.com (Michael Szal)

package com.google.libvorbis;

public class LibVorbisCommon {

  static {
    System.loadLibrary("vorbisJNI");
  }

  public static final int OV_EBADHEADER = -133;
  public static final int OV_EBADLINK = -137;
  public static final int OV_EBADPACKET = -136;
  public static final int OV_EFAULT = -129;
  public static final int OV_EIMPL = -130;
  public static final int OV_EINVAL = -131;
  public static final int OV_ENOSEEK = -138;
  public static final int OV_ENOTAUDIO = -135;
  public static final int OV_ENOTVORBIS = -132;
  public static final int OV_EOF = -2;
  public static final int OV_EREAD = -128;
  public static final int OV_EVERSION = -134;
  public static final int OV_FALSE = -1;
  public static final int OV_HOLE = -3;

  public native void deleteVorbisBlock(long vb);
  public native void deleteVorbisComment(long vc);
  public native void deleteVorbisDspState(long v);
  public native void deleteVorbisInfo(long vi);
  public native long newVorbisBlock();
  public native long newVorbisComment();
  public native long newVorbisDspState();
  public native long newVorbisInfo();
  public native int vorbisBlockClear(long vb);
  public native int vorbisBlockInit(long v, long vb);
  public native void vorbisDspClear(long v);
  public native double vorbisGranuleTime(long v, long granulepos);
  public native int vorbisInfoBlockSize(long vi, int zo);
  public native void vorbisInfoClear(long vi);
  public native void vorbisInfoInit(long vi);
  public native String vorbisVersionString();
}
