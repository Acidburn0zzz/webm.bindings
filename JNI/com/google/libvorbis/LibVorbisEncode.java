// Author: mszal@google.com (Michael Szal)

package com.google.libvorbis;

public class LibVorbisEncode {

  public native int vorbisAnalysis(long vb, long op);
  public native int vorbisAnalysisBlockout(long v, long vb);

  /**
   * The original function is declared like this:
   *
   * float** vorbis_analysis_buffer(vorbis_dsp_state* v, int vals);
   *
   * You're supposed to call the function with the number of samples you have.  It allocates
   * internal storage for the samples in the form of a 2D array, indexed by channel then sample.
   * You copy your samples into the array, then call vorbis_analysis_wrote to indicate the encoder
   * can analyze the samples.
   *
   * The Java version is simpler.  Just pass the samples you have to the function, then call
   * vorbis_analysis_wrote.
   */
  public native void vorbisAnalysisBuffer(long v, float[][] samples);
  public native int vorbisAnalysisHeaderout(long v, long vc, long op, long op_comm, long op_code);
  public native int vorbisAnalysisInit(long v, long vi);
  public native int vorbisAnalysisWrote(long v, int vals);
  public native int vorbisBitrateAdblock(long vb);
  public native int vorbisBitrateFlushpacket(long v, long op);
}
