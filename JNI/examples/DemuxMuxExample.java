import com.google.libwebm.mkvmuxer.AudioTrack;
import com.google.libwebm.mkvmuxer.Cues;
import com.google.libwebm.mkvmuxer.MkvWriter;
import com.google.libwebm.mkvmuxer.Segment;
import com.google.libwebm.mkvmuxer.SegmentInfo;
import com.google.libwebm.mkvmuxer.VideoTrack;
import com.google.libwebm.mkvparser.Block;
import com.google.libwebm.mkvparser.BlockEntry;
import com.google.libwebm.mkvparser.Cluster;
import com.google.libwebm.mkvparser.EbmlHeader;
import com.google.libwebm.mkvparser.Frame;
import com.google.libwebm.mkvparser.MkvReader;
import com.google.libwebm.mkvparser.Track;
import com.google.libwebm.mkvparser.Tracks;

public class DemuxMuxExample {
  /*
   * This function will parse a source WebM file and mux the audio and video frames from the source
   * file into another WebM file. |inputFileName| is the filename of the source WebM file.
   * |outputFileName| is the filename of the WebM file to write to. Returns true on success. If
   * there is an error, |error| will be set to a descriptive string.
   */
  static public boolean demuxMuxExample(String inputFileName, String outputFileName,
                                        StringBuilder error) {
    int audioTrackNumber = 0;
    boolean chunking = false;
    String chunkName = null;
    boolean cuesOnAudioTrack = false;
    boolean cuesOnVideoTrack = true;
    long displayHeight = 0;
    long displayWidth = 0;
    boolean liveMode = false;
    long maxClusterDuration = 0;
    long maxClusterSize = 0;
    boolean outputCues = true;
    boolean outputAudio = true;
    boolean outputCuesBlockNumber = true;
    boolean outputVideo = true;
    VideoTrack.StereoMode stereoMode = VideoTrack.StereoMode.kMono;
    boolean switchTracks = false;

    if (inputFileName == null || outputFileName == null) {
      error.append("Input or output filename is null.");
      return false;
    }

    MkvReader mkvReader = new MkvReader();
    if (mkvReader.open(inputFileName) != 0) {
      error.append("Input file is invalid or error while opening.");
      return false;
    }

    EbmlHeader ebmlHeader = new EbmlHeader();
    long[] outputPosition = {0};
    ebmlHeader.parse(mkvReader, outputPosition);
    long position = outputPosition[0];
    com.google.libwebm.mkvparser.Segment[] outputParserSegment = {null};
    long result = com.google.libwebm.mkvparser.Segment.createInstance(
        mkvReader, position, outputParserSegment);
    com.google.libwebm.mkvparser.Segment parserSegment = outputParserSegment[0];
    if (result != 0) {
      error.append("Segment.createInstance() failed.");
      return false;
    }

    result = parserSegment.load();
    if (result < 0) {
      error.append("Segment.load() failed.");
      return false;
    }

    com.google.libwebm.mkvparser.SegmentInfo parserSegmentInfo = parserSegment.getInfo();
    long timeCodeScale = parserSegmentInfo.getTimeCodeScale();

    MkvWriter mkvWriter = new MkvWriter();
    if (!mkvWriter.open(outputFileName)) {
      error.append("Output name is invalid or error while opening.");
      return false;
    }

    Segment muxerSegment = new Segment();
    if (!muxerSegment.init(mkvWriter)) {
      error.append("Could not initialize muxer segment.");
      return false;
    }

    if (liveMode) {
      muxerSegment.setMode(Segment.Mode.kLive);
    } else {
      muxerSegment.setMode(Segment.Mode.kFile);
    }
    if (chunking) {
      muxerSegment.setChunking(true, chunkName);
    }
    if (maxClusterDuration > 0) {
      muxerSegment.setMaxClusterDuration(maxClusterDuration);
    }
    if (maxClusterSize > 0) {
      muxerSegment.setMaxClusterSize(maxClusterSize);
    }
    muxerSegment.outputCues(outputCues);
    SegmentInfo muxerSegmentInfo = muxerSegment.getSegmentInfo();
    muxerSegmentInfo.setTimecodeScale(timeCodeScale);
    muxerSegmentInfo.setWritingApp("SampleMultiplexer");

    Tracks parserTracks = parserSegment.getTracks();
    long i = 0;
    long newVideoTrackNumber = 0;
    long newAudioTrackNumber = 0;
    while (i != parserTracks.getTracksCount()) {
      int trackNumber = (int) i++;
      if (switchTracks) {
        trackNumber = (int) (i % parserTracks.getTracksCount());
      }
      Track parserTrack = parserTracks.getTrackByIndex(trackNumber);
      if (parserTrack == null) {
        continue;
      }

      String trackName = parserTrack.getNameAsUtf8();
      Track.Type trackType = parserTrack.getType();
      if (trackType == Track.Type.kVideo && outputVideo) {
        com.google.libwebm.mkvparser.VideoTrack videoTrack =
            (com.google.libwebm.mkvparser.VideoTrack) parserTrack;
        long width = videoTrack.getWidth();
        long height = videoTrack.getHeight();
        newVideoTrackNumber = muxerSegment.addVideoTrack((int) width, (int) height, 0);
        if (newVideoTrackNumber == 0) {
          error.append("Could not add video track.");
          return false;
        }

        VideoTrack muxerTrack = (VideoTrack) muxerSegment.getTrackByNumber(newVideoTrackNumber);
        if (muxerTrack == null) {
          error.append("Could not get video track.");
          return false;
        }

        if (trackName != null) {
          muxerTrack.setName(trackName);
        }
        if (displayWidth > 0) {
          muxerTrack.setDisplayWidth(displayWidth);
        }
        if (displayHeight > 0) {
          muxerTrack.setDisplayHeight(displayHeight);
        }
        if (stereoMode != VideoTrack.StereoMode.kMono) {
          muxerTrack.setStereoMode(stereoMode);
        }
        double rate = videoTrack.getFrameRate();
        if (rate > 0) {
          muxerTrack.setFrameRate(rate);
        }
      } else if (trackType == Track.Type.kAudio && outputAudio) {
        com.google.libwebm.mkvparser.AudioTrack audioTrack =
            (com.google.libwebm.mkvparser.AudioTrack) parserTrack;
        long channels = audioTrack.getChannels();
        double sampleRate = audioTrack.getSamplingRate();
        newAudioTrackNumber =
            muxerSegment.addAudioTrack((int) sampleRate, (int) channels, audioTrackNumber);
        if (newAudioTrackNumber == 0) {
          error.append("Could not add audio track.");
          return false;
        }

        AudioTrack muxerTrack = (AudioTrack) muxerSegment.getTrackByNumber(newAudioTrackNumber);
        if (muxerTrack == null) {
          error.append("Could not get audio track.");
          return false;
        }

        if (trackName != null) {
          muxerTrack.setName(trackName);
        }
        long[] outputPrivateSize = {0};
        byte[] privateData = audioTrack.getCodecPrivate(outputPrivateSize);
        long privateSize = outputPrivateSize[0];
        if (privateSize > 0 && !muxerTrack.setCodecPrivate(privateData)) {
          error.append("Could not add audio private data.");
          return false;
        }

        long bitDepth = audioTrack.getBitDepth();
        if (bitDepth > 0) {
          muxerTrack.setBitDepth(bitDepth);
        }
      }
    }

    Cues cues = muxerSegment.getCues();
    cues.setOutputBlockNumber(outputCuesBlockNumber);
    if (cuesOnVideoTrack && newVideoTrackNumber != 0) {
      muxerSegment.cuesTrack(newVideoTrackNumber);
    }
    if (cuesOnAudioTrack && newAudioTrackNumber != 0) {
      muxerSegment.cuesTrack(newAudioTrackNumber);
    }

    byte[] data = null;
    int dataLength = 0;
    Cluster cluster = parserSegment.getFirst();
    while (cluster != null && !cluster.eos()) {
      BlockEntry[] outputBlockEntry = {null};
      long status = cluster.getFirst(outputBlockEntry);
      BlockEntry blockEntry = outputBlockEntry[0];
      if (status != 0) {
        error.append("Could not get first block of cluster.");
        return false;
      }

      while (blockEntry != null && !blockEntry.eos()) {
        Block block = blockEntry.getBlock();
        long trackNumber = block.getTrackNumber();
        Track parserTrack = parserTracks.getTrackByNumber(trackNumber);
        Track.Type trackType = parserTrack.getType();
        long timeNs = block.getTime(cluster);
        if (trackType == Track.Type.kAudio && outputAudio || trackType == Track.Type.kVideo
            && outputVideo) {
          int frameCount = block.getFrameCount();
          boolean isKey = block.isKey();
          for (int j = 0; j < frameCount; ++j) {
            Frame frame = block.getFrame(j);
            if (frame.getLen() > dataLength) {
              dataLength = (int) frame.getLen();
            }
            byte[][] outputData = {null};
            result = frame.read(mkvReader, outputData);
            data = outputData[0];
            if (result != 0) {
              error.append("Could not read frame.");
              return false;
            }

            long newTrackNumber = newVideoTrackNumber;
            if (trackType == Track.Type.kAudio) {
              newTrackNumber = newAudioTrackNumber;
            }
            if (!muxerSegment.addFrame(data, newTrackNumber, timeNs, isKey)) {
              error.append("Could not add frame.");
              return false;
            }
          }
        }

        BlockEntry[] outputNext = {null};
        status = cluster.getNext(blockEntry, outputNext);
        blockEntry = outputNext[0];
        if (status != 0) {
          error.append("Could not get next block of cluster.");
          return false;
        }
      }

      cluster = parserSegment.getNext(cluster);
    }

    if (!muxerSegment.finalizeSegment()) {
      error.append("Finalization of segment failed.");
      return false;
    }

    mkvWriter.close();
    mkvReader.close();

    return true;
  }
}
