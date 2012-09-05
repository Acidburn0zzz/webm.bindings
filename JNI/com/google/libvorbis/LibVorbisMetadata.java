// Author: mszal@google.com (Michael Szal)

package com.google.libvorbis;

public class LibVorbisMetadata {

  public native void vorbisCommentAdd(long vc, String comment);
  public native void vorbisCommentAddTag(long vc, String tag, String contents);
  public native void vorbisCommentClear(long vc);
  public native void vorbisCommentInit(long vc);
  public native String vorbisCommentQuery(long vc, String tag, int count);
  public native int vorbisCommentQueryCount(long vc, String tag);
  public native int vorbisCommentheaderOut(long vc, long op);
}
