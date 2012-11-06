// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class Chapter extends Common {

  public boolean addString(String title, String language, String country) {
    return add_string(nativePointer, title, language, country);
  }

  public boolean setId(String id) {
    return set_id(nativePointer, id);
  }

  public void setTime(Segment segment, long startTimeNs, long endTimeNs) {
    set_time(nativePointer, segment.getNativePointer(), startTimeNs, endTimeNs);
  }

  protected Chapter(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
  }

  private native boolean add_string(long jChapter, String jTitle, String jLanguage,
      String jCountry);
  private native boolean set_id(long jChapter, String jId);
  private native void set_time(long jChapter, long jSegment, long start_time_ns, long end_time_ns);
}
