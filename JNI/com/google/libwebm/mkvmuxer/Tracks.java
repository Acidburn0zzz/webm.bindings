// Author: mszal@google.com (Michael Szal)

package com.google.libwebm.mkvmuxer;

import com.google.libwebm.Common;

public class Tracks extends Common {

  public enum Type {
    None,
    kVideo,
    kAudio
  }

  public static final String kVorbisCodecId = "A_VORBIS";
  public static final String kVp8CodecId = "V_VP8";

  public Tracks() {
    nativePointer = newTracks();
  }

  public boolean addTrack(Track track, int number) {
    return AddTrack(nativePointer, track.getNativePointer(), number);
  }

  public Track getTrackByIndex(int index) {
    long pointer = GetTrackByIndex(nativePointer, index);
    return Track.newTrack(pointer);
  }

  public Track getTrackByNumber(long trackNumber) {
    long pointer = GetTrackByNumber(nativePointer, trackNumber);
    return Track.newTrack(pointer);
  }

  public int trackEntriesSize() {
    return track_entries_size(nativePointer);
  }

  public boolean trackIsAudio(long trackNumber) {
    return TrackIsAudio(nativePointer, trackNumber);
  }

  public boolean trackIsVideo(long trackNumber) {
    return TrackIsVideo(nativePointer, trackNumber);
  }

  public boolean write(IMkvWriter writer) {
    return Write(nativePointer, writer.getNativePointer());
  }

  protected Tracks(long nativePointer) {
    super(nativePointer);
  }

  protected void deleteObject() {
    deleteTracks(nativePointer);
  }

  private native boolean AddTrack(long jTracks, long jTrack, int number);
  private native void deleteTracks(long jTracks);
  private native long GetTrackByIndex(long jTracks, int idx);
  private native long GetTrackByNumber(long jTracks, long track_number);
  private native long newTracks();
  private native int track_entries_size(long jTracks);
  private native boolean TrackIsAudio(long jTracks, long track_number);
  private native boolean TrackIsVideo(long jTracks, long track_number);
  private native boolean Write(long jTracks, long jWriter);
}
