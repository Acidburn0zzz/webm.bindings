// Author: mszal@google.com (Michael Szal)

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

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class SampleMultiplexer {

  public static void main(String[] args) {
    int audioTrackNumber = 0;
    boolean chunking = false;
    String chunkName = null;
    boolean cuesOnAudioTrack = false;
    boolean cuesOnVideoTrack = true;
    long displayHeight = 0;
    long displayWidth = 0;
    String inputFileName = null;
    boolean liveMode = false;
    long maxClusterDuration = 0;
    long maxClusterSize = 0;
    boolean outputCues = true;
    String outputFileName = null;
    boolean outputAudio = true;
    boolean outputCuesBlockNumber = true;
    boolean outputVideo = true;
    VideoTrack.StereoMode stereoMode = VideoTrack.StereoMode.kMono;
    boolean switchTracks = false;
    int videoTrackNumber = 0;

    int lastArg = args.length - 1;
    for (int i = 0; i < args.length; ++i) {
      if ("-h".equals(args[i]) || "-?".equals(args[i])) {
        PrintUsage();
        return;
      } else if ("-i".equals(args[i]) && i < lastArg) {
        inputFileName = args[++i];
      } else if ("-o".equals(args[i]) && i < lastArg) {
        outputFileName = args[++i];
      }
    }

    if (inputFileName == null || outputFileName == null) {
      PrintUsage();
      System.exit(1);
    }

    MkvReader mkvReader = new MkvReader();
    if (mkvReader.open(inputFileName) != 0) {
      System.out.println("\nFile name is invalid or error while opening.");
      System.exit(1);
    }

    EbmlHeader ebmlHeader = new EbmlHeader();
    long[] outputPosition = {0};
    ebmlHeader.parse(mkvReader, outputPosition);
    long position = outputPosition[0];
    com.google.libwebm.mkvparser.Segment[] outputParserSegment = {null};
    long result = com.google.libwebm.mkvparser.Segment.createInstance(mkvReader, position,
        outputParserSegment);
    com.google.libwebm.mkvparser.Segment parserSegment = outputParserSegment[0];
    if (result != 0) {
      System.out.println("\nSegment.createInstance() failed.");
      System.exit(1);
    }

    result = parserSegment.load();
    if (result < 0) {
      System.out.println("\nSegment.load() failed.");
      System.exit(1);
    }

    com.google.libwebm.mkvparser.SegmentInfo parserSegmentInfo = parserSegment.getInfo();
    long timeCodeScale = parserSegmentInfo.getTimeCodeScale();
    MkvWriter mkvWriter = new MkvWriter();
    if (!mkvWriter.open(outputFileName)) {
      System.out.println("\nFile name is invalid or error while opening.");
      System.exit(1);
    }

    Segment muxerSegment = new Segment();
    if (!muxerSegment.init(mkvWriter)) {
      System.out.println("\nCould not initialize muxer segment.");
      System.exit(1);
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
          System.out.println("\nCould not add video track.");
          System.exit(1);
        }

        VideoTrack muxerTrack = (VideoTrack) muxerSegment.getTrackByNumber(newVideoTrackNumber);
        if (muxerTrack == null) {
          System.out.println("\nCould not get video track.");
          System.exit(1);
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
          System.out.println("\nCould not add audio track.");
          System.exit(1);
        }

        AudioTrack muxerTrack = (AudioTrack) muxerSegment.getTrackByNumber(newAudioTrackNumber);
        if (muxerTrack == null) {
          System.out.println("\nCould not get audio track.");
          System.exit(1);
        }

        if (trackName != null) {
          muxerTrack.setName(trackName);
        }
        long[] outputPrivateSize = {0};
        byte[] privateData = audioTrack.getCodecPrivate(outputPrivateSize);
        long privateSize = outputPrivateSize[0];
        if (privateSize > 0 && !muxerTrack.setCodecPrivate(privateData)) {
          System.out.println("\nCould not add audio private data.");
          System.exit(1);
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
        System.out.println("\nCould not get first block of cluster.");
        System.exit(1);
      }

      while (blockEntry != null && !blockEntry.eos()) {
        Block block = blockEntry.getBlock();
        long trackNumber = block.getTrackNumber();
        Track parserTrack = parserTracks.getTrackByNumber(trackNumber);
        Track.Type trackType = parserTrack.getType();
        long timeNs = block.getTime(cluster);
        if (trackType == Track.Type.kAudio && outputAudio
            || trackType == Track.Type.kVideo && outputVideo) {
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
              System.out.println("\nCould not read frame.");
              System.exit(1);
            }

            long newTrackNumber = newVideoTrackNumber;
            if (trackType == Track.Type.kAudio) {
              newTrackNumber = newAudioTrackNumber;
            }
            if (!muxerSegment.addFrame(data, newTrackNumber, timeNs, isKey)) {
              System.out.println("\nCould not add frame.");
              System.exit(1);
            }
          }
        }

        BlockEntry[] outputNext = {null};
        status = cluster.getNext(blockEntry, outputNext);
        blockEntry = outputNext[0];
        if (status != 0) {
          System.out.println("\nCould not get next block of cluster.");
          System.exit(1);
        }
      }

      cluster = parserSegment.getNext(cluster);
    }

    if (!muxerSegment.finalizeSegment()) {
      System.out.println("\nFinalization of segment failed.");
      System.exit(1);
    }

    mkvWriter.close();
    mkvReader.close();
  }

  private static void PrintUsage() {
    String usage = "Usage: java SampleMultiplexer -i inputFileName -o outputFileName [options]\n"
        + "\n"
        + "Main options:\n"
        + "  -h | -?   show help";
    System.out.println(usage);
  }
}
