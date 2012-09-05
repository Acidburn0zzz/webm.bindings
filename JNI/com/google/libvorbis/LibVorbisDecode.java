// Author: mszal@google.com (Michael Szal)

package com.google.libvorbis;

public class LibVorbisDecode {

  public native long vorbisPacketBlocksize(long vi, long op);
  public native int vorbisSynthesis(long vb, long op);
  public native int vorbisSynthesisBlockin(long v, long vb);
  public native int vorbisSynthesisHalfrate(long v, int flag);
  public native int vorbisSynthesisHalfrateP(long vi);
  public native int vorbisSynthesisHeaderin(long vi, long vc, long op);
  public native int vorbisSynthesisIdheader(long op);
  public native int vorbisSynthesisInit(long v, long vi);

  /**
   * For Lapout and Pcmout, the original functions are declared like this:
   *
   * int vorbis_synthesis_lapout(vorbis_dsp_state* v, float*** pcm);
   *
   * After calling the function, *pcm will be a 2D array of samples, indexed by channel then sample.
   * The return value is the number of samples (length of the inner array).  But you can also call
   * the function with pcm = NULL, in which case it returns the number of samples available but does
   * not get any samples.  In other words, the function can do two different things, and this is
   * difficult to translate into Java because Java does not have output parameters.  Instead, I made
   * separate functions for each behavior:
   *
   * Lapout returns the array of samples directly.  It needs to know the number of channels to do
   * this (available in the vorbis_info struct).
   * LapoutAvailable returns the number of samples available.
   */
  public native float[][] vorbisSynthesisLapout(long v, int channels);
  public native int vorbisSynthesisLapoutAvailable(long v);
  public native float[][] vorbisSynthesisPcmout(long v, int channels);
  public native int vorbisSynthesisPcmoutAvailable(long v);
  public native int vorbisSynthesisRead(long v, int samples);
  public native int vorbisSynthesisRestart(long v);
  public native int vorbisSynthesisTrackonly(long vb, long op);
}
