import com.google.libvorbis.AudioFrame;
import com.google.libvorbis.VorbisEncoderC;
import com.google.libvorbis.VorbisEncoderConfig;
import com.google.libvorbis.VorbisEncoderWrapper;
import com.google.libvpx.LibVpxEnc;
import com.google.libvpx.LibVpxEncConfig;
import com.google.libvpx.LibVpxException;
import com.google.libvpx.Rational;
import com.google.libvpx.VpxCodecCxPkt;
import com.google.libvpx.Y4MReader;
import com.google.libwebm.mkvmuxer.AudioTrack;
import com.google.libwebm.mkvmuxer.Cues;
import com.google.libwebm.mkvmuxer.MkvMuxer;
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
import java.nio.ByteBuffer;
import java.util.ArrayList;

/**
 * This class contains a bunch of examples to show different features of the bindings.
 */
public class BindingsSamples {
  static public String GetLibwebmVersionString() {
    int[] major = new int[2];
    int[] minor = new int[2];
    int[] build = new int[2];
    int[] revision = new int[2];
    MkvMuxer.getVersion(major, minor, build, revision);

    return new String(Integer.toString(major[0]) + "." + Integer.toString(minor[0]) + "."
        + Integer.toString(build[0]) + "." + Integer.toString(revision[0]));
  }

  /*
   * This function will parse a source WebM file and mux the audio and video frames from the source
   * file into another WebM file. |inputFileName| filename if the source WebM file. |outputFileName|
   * filename of the WebM file to write to. Returns "Success!" on success, an error string
   * otherwise.
   */
  static public String muxerDemuxerSample(String inputFileName, String outputFileName) {
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
      return new String("Input or output filename is null.");
    }

    MkvReader mkvReader = new MkvReader();
    if (mkvReader.open(inputFileName) != 0) {
      return new String("Input file is invalid or error while opening.");
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
      return new String("Segment.createInstance() failed.");
    }

    result = parserSegment.load();
    if (result < 0) {
      return new String("Segment.load() failed.");
    }

    com.google.libwebm.mkvparser.SegmentInfo parserSegmentInfo = parserSegment.getInfo();
    long timeCodeScale = parserSegmentInfo.getTimeCodeScale();

    MkvWriter mkvWriter = new MkvWriter();
    if (!mkvWriter.open(outputFileName)) {
      return new String("Output name is invalid or error while opening.");
    }

    Segment muxerSegment = new Segment();
    if (!muxerSegment.init(mkvWriter)) {
      return new String("Could not initialize muxer segment.");
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
          return new String("Could not add video track.");
        }

        VideoTrack muxerTrack = (VideoTrack) muxerSegment.getTrackByNumber(newVideoTrackNumber);
        if (muxerTrack == null) {
          return new String("Could not get video track.");
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
          return new String("Could not add audio track.");
        }

        AudioTrack muxerTrack = (AudioTrack) muxerSegment.getTrackByNumber(newAudioTrackNumber);
        if (muxerTrack == null) {
          return new String("Could not get audio track.");
        }

        if (trackName != null) {
          muxerTrack.setName(trackName);
        }
        long[] outputPrivateSize = {0};
        byte[] privateData = audioTrack.getCodecPrivate(outputPrivateSize);
        long privateSize = outputPrivateSize[0];
        if (privateSize > 0 && !muxerTrack.setCodecPrivate(privateData)) {
          return new String("Could not add audio private data.");
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
        return new String("Could not get first block of cluster.");
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
              return new String("Could not read frame.");
            }

            long newTrackNumber = newVideoTrackNumber;
            if (trackType == Track.Type.kAudio) {
              newTrackNumber = newAudioTrackNumber;
            }
            if (!muxerSegment.addFrame(data, newTrackNumber, timeNs, isKey)) {
              return new String("Could not add frame.");
            }
          }
        }

        BlockEntry[] outputNext = {null};
        status = cluster.getNext(blockEntry, outputNext);
        blockEntry = outputNext[0];
        if (status != 0) {
          return new String("Could not get next block of cluster.");
        }
      }

      cluster = parserSegment.getNext(cluster);
    }

    if (!muxerSegment.finalizeSegment()) {
      return new String("Finalization of segment failed.");
    }

    mkvWriter.close();
    mkvReader.close();

    return new String("Success!");
  }

  /*
   * This function will encode a video WebM file. |y4mInputName| filename of the source video. The
   * source video must be a Y4M file with raw i420 frames. |webmOutputName| filename of the WebM
   * file to write to. |framesToEncode| is the number of frames to encode before stopping. Returns
   * "Success!" on success, an error string otherwise.
   */
  static public String videoEncodeSample(
      String y4mInputName, String webmOutputName, int framesToEncode) {
    File y4mFile = new File(y4mInputName);
    Y4MReader y4mReader;

    try {
      y4mReader = new Y4MReader(y4mFile);
    } catch (IOException e) {
      return new String("Error reading " + y4mFile + " : " + e);
    }

    LibVpxEncConfig encoderConfig = null;
    LibVpxEnc encoder = null;
    MkvWriter mkvWriter = null;

    try {
      encoderConfig = new LibVpxEncConfig(y4mReader.getWidth(), y4mReader.getHeight());
      encoder = new LibVpxEnc(encoderConfig);
      byte[] uncompressedFrame;

      // libwebm expects nanosecond units
      encoderConfig.setTimebase(1, 1000000000);
      Rational timeBase = encoderConfig.getTimebase();
      Rational timeMultiplier = timeBase.multiply(y4mReader.getFrameRate()).reciprocal();
      int framesIn = 1;

      mkvWriter = new MkvWriter();
      if (!mkvWriter.open(webmOutputName)) {
        return new String("WebM Output name is invalid or error while opening.");
      }

      Segment muxerSegment = new Segment();
      if (!muxerSegment.init(mkvWriter)) {
        return new String("Could not initialize muxer segment.");
      }

      SegmentInfo muxerSegmentInfo = muxerSegment.getSegmentInfo();
      muxerSegmentInfo.setWritingApp("y4mEncodeSample");

      long newVideoTrackNumber =
          muxerSegment.addVideoTrack(encoderConfig.getWidth(), encoderConfig.getHeight(), 0);
      if (newVideoTrackNumber == 0) {
        return new String("Could not add video track.");
      }

      while ((uncompressedFrame = y4mReader.getUncompressedFrame()) != null
          && framesIn < framesToEncode) {
        long frameStart = timeMultiplier.multiply(framesIn - 1).toLong();
        long nextFrameStart = timeMultiplier.multiply(framesIn).toLong();

        ArrayList<VpxCodecCxPkt> encPkt =
            encoder.encodeFrame(uncompressedFrame, LibVpxEnc.VPX_IMG_FMT_I420, frameStart, nextFrameStart - frameStart);

        for (int i = 0; i < encPkt.size(); i++) {
          VpxCodecCxPkt pkt = encPkt.get(i);
          final boolean isKey = (pkt.flags & 0x1) == 1;

          if (!muxerSegment.addFrame(pkt.buffer, newVideoTrackNumber, pkt.pts, isKey)) {
            return new String("Could not add frame.");
          }
        }

        ++framesIn;
      }

      if (!muxerSegment.finalizeSegment()) {
        return new String("Finalization of segment failed.");
      }

    } catch (IOException e) {
      return new String("IOException" + e);
    } catch (LibVpxException e) {
      return new String("Encoder error : " + e);
    } finally {
      if (encoder != null) {
        encoder.close();
      }
      if (encoderConfig != null) {
        encoderConfig.close();
      }
      if (mkvWriter != null) {
        mkvWriter.close();
      }
    }

    return new String("Success!");
  }

  /*
   * This function will encode an audio WebM file. |wavInputName| filename of the source audio. The
   * source audio must be a WAV file with raw PCM data. |webmOutputName| filename of the WebM
   * file to write to. Returns "Success!" on success, an error string otherwise.
   */
  static public String audioEncodeSampleJava(String wavInputName, String webmOutputName) {
    VorbisEncoderConfig vorbisConfig = null;
    VorbisEncoderWrapper vorbisEncoder = null;
    MkvWriter mkvWriter = null;

    try {
      File pcmFile = new File(wavInputName);
      WavReader wavReader = null;
      try {
        wavReader = new WavReader(pcmFile);
      } catch (Exception e) {
        return new String("Could not create wav reader.");
      }

      vorbisConfig = new VorbisEncoderConfig();
      vorbisConfig.channels = wavReader.nChannels();
      vorbisConfig.sample_rate = wavReader.nSamplesPerSec();
      vorbisConfig.bytes_per_second = wavReader.nAvgBytesPerSec();
      vorbisConfig.block_align = wavReader.nBlockAlign();
      vorbisConfig.bits_per_sample = wavReader.wBitsPerSample();

      vorbisEncoder = new VorbisEncoderWrapper();
      if (!vorbisEncoder.Init(vorbisConfig)) {
        return new String("Could not initialize Vorbis encoder.");
      }

      mkvWriter = new MkvWriter();
      if (!mkvWriter.open(webmOutputName)) {
        return new String("WebM Output name is invalid or error while opening.");
      }

      Segment muxerSegment = new Segment();
      if (!muxerSegment.init(mkvWriter)) {
        return new String("Could not initialize muxer segment.");
      }

      SegmentInfo muxerSegmentInfo = muxerSegment.getSegmentInfo();
      muxerSegmentInfo.setWritingApp("wavEncodeSample");

      // Add Audio Track
      int channels = vorbisConfig.channels;
      int sampleRate = vorbisConfig.sample_rate;
      long newAudioTrackNumber = muxerSegment.addAudioTrack(sampleRate, channels, 0);
      if (newAudioTrackNumber == 0) {
        return new String("Could not add audio track.");
      }

      AudioTrack muxerTrack = (AudioTrack) muxerSegment.getTrackByNumber(newAudioTrackNumber);
      if (muxerTrack == null) {
        return new String("Could not get audio track.");
      }

      ByteBuffer privateData = vorbisEncoder.getCodecPrivate();
      if (!muxerTrack.setCodecPrivate(privateData.array())) {
        return new String("Could not add audio private data.");
      }

      final int maxSamplesToRead = 1000;
      int samplesLeft = 0;
      while ((samplesLeft = wavReader.samplesRemaining()) > 0) {
        byte[] pcmArray = null;
        int samplesToRead = Math.min(samplesLeft, maxSamplesToRead);
        try {
          pcmArray = wavReader.readSamples(samplesToRead);
        } catch (Exception e) {
          return new String("Could not read samples.");
        }

        if (!vorbisEncoder.encodeAudio(pcmArray)) return new String("Error encoding samples.");

        AudioFrame frame = null;
        while ((frame = vorbisEncoder.readCompressedAudio()) != null) {
          if (!muxerSegment.addFrame(
              frame.frame.array(), newAudioTrackNumber, frame.timestamp * 1000000, true)) {
            return new String("Could not add audio frame.");
          }
        }
      }

      if (!muxerSegment.finalizeSegment()) {
        return new String("Finalization of segment failed.");
      }

    } finally {
      if (mkvWriter != null) {
        mkvWriter.close();
      }
    }

    return new String("Success!");
  }

  /*
   * This function will encode an audio WebM file. |wavInputName| filename of the source audio. The
   * source audio must be a WAV file with raw PCM data. |webmOutputName| filename of the WebM
   * file to write to. Returns "Success!" on success, an error string otherwise.
   */
  static public String audioEncodeSample(String wavInputName, String webmOutputName) {
    VorbisEncoderC vorbisEncoder = null;
    MkvWriter mkvWriter = null;

    try {
      File pcmFile = new File(wavInputName);
      WavReader wavReader = null;
      try {
        wavReader = new WavReader(pcmFile);
      } catch (Exception e) {
        return new String("Could not create wav reader.");
      }

      vorbisEncoder = new VorbisEncoderC();

      // The input characteristics must be set before Init() is called.
      int channels = wavReader.nChannels();
      int sampleRate = wavReader.nSamplesPerSec();
      vorbisEncoder.SetChannels(channels);
      vorbisEncoder.SetSampleRate(sampleRate);
      vorbisEncoder.SetBitsPerSample(wavReader.wBitsPerSample());

      if (!vorbisEncoder.Init()) {
        return new String("Could not initialize Vorbis encoder.");
      }

      mkvWriter = new MkvWriter();
      if (!mkvWriter.open(webmOutputName)) {
        return new String("WebM Output name is invalid or error while opening.");
      }

      Segment muxerSegment = new Segment();
      if (!muxerSegment.init(mkvWriter)) {
        return new String("Could not initialize muxer segment.");
      }

      SegmentInfo muxerSegmentInfo = muxerSegment.getSegmentInfo();
      muxerSegmentInfo.setWritingApp("wavEncodeSample");

      // Add Audio Track
      long newAudioTrackNumber = muxerSegment.addAudioTrack(sampleRate, channels, 0);
      if (newAudioTrackNumber == 0) {
        return new String("Could not add audio track.");
      }

      AudioTrack muxerTrack = (AudioTrack) muxerSegment.getTrackByNumber(newAudioTrackNumber);
      if (muxerTrack == null) {
        return new String("Could not get audio track.");
      }

      byte[] buffer = vorbisEncoder.CodecPrivate();
      if (buffer == null) {
        return new String("Could not get audio private data.");
      }
      if (!muxerTrack.setCodecPrivate(buffer)) {
        return new String("Could not add audio private data.");
      }

      final int maxSamplesToRead = 1000;
      int samplesLeft = 0;
      while ((samplesLeft = wavReader.samplesRemaining()) > 0) {
        byte[] pcmArray = null;
        int samplesToRead = Math.min(samplesLeft, maxSamplesToRead);
        try {
          pcmArray = wavReader.readSamples(samplesToRead);
        } catch (Exception e) {
          return new String("Could not read samples.");
        }

        if (!vorbisEncoder.Encode(pcmArray))
          return new String("Error encoding samples.");

        long[] timestamp = new long[2];

        byte[] frame = null;
        while ((frame = vorbisEncoder.ReadCompressedAudio(timestamp)) != null) {
          if (!muxerSegment.addFrame(
              frame, newAudioTrackNumber, timestamp[0] * 1000000, true)) {
            return new String("Could not add audio frame.");
          }
        }
      }

      if (!muxerSegment.finalizeSegment()) {
        return new String("Finalization of segment failed.");
      }

    } finally {
      if (mkvWriter != null) {
        mkvWriter.close();
      }
    }

    return new String("Success!");
  }

  /*
   * This function will encode an audio and video WebM file. |y4mName| filename of the source video.
   * The source video must be a Y4M file with raw i420 frames. |wavName| filename of the source
   * audio. The source audio must be a WAV file with raw PCM data. |webmOutputName| filename of the
   * WebM file to write to. |framesToEncode| is the number of video frames to encode before
   * stopping. Returns "Success!" on success, an error string otherwise.
   */
  static public String audioVideoEncodeSample(
      String y4mName, String wavName, String webmOutputName, int framesToEncode) {
    LibVpxEncConfig vpxConfig = null;
    LibVpxEnc vpxEncoder = null;
    VorbisEncoderConfig vorbisConfig = null;
    VorbisEncoderWrapper vorbisEncoder = null;
    MkvWriter mkvWriter = null;

    try {
      File y4mFile = new File(y4mName);
      Y4MReader y4mReader;
      try {
        y4mReader = new Y4MReader(y4mFile);
      } catch (IOException e) {
        return new String("Error creating y4m file:" + y4mName + " : " + e);
      }

      vpxConfig = new LibVpxEncConfig(y4mReader.getWidth(), y4mReader.getHeight());
      vpxEncoder = new LibVpxEnc(vpxConfig);

      // libwebm expects nanosecond units
      vpxConfig.setTimebase(1, 1000000000);
      Rational timeBase = vpxConfig.getTimebase();
      Rational timeMultiplier = timeBase.multiply(y4mReader.getFrameRate()).reciprocal();
      int framesIn = 1;

      File pcmFile = new File(wavName);
      WavReader wavReader = null;
      try {
        wavReader = new WavReader(pcmFile);
      } catch (Exception e) {
        return new String("Error creating wav file:" + wavName);
      }

      vorbisConfig = new VorbisEncoderConfig();
      vorbisConfig.channels = wavReader.nChannels();
      vorbisConfig.sample_rate = wavReader.nSamplesPerSec();
      vorbisConfig.bytes_per_second = wavReader.nAvgBytesPerSec();
      vorbisConfig.block_align = wavReader.nBlockAlign();
      vorbisConfig.bits_per_sample = wavReader.wBitsPerSample();

      vorbisEncoder = new VorbisEncoderWrapper();
      if (!vorbisEncoder.Init(vorbisConfig)) {
        return new String("Could not initialize Vorbis encoder.");
      }

      mkvWriter = new MkvWriter();
      if (!mkvWriter.open(webmOutputName)) {
        return new String("WebM Output name is invalid or error while opening.");
      }

      Segment muxerSegment = new Segment();
      if (!muxerSegment.init(mkvWriter)) {
        return new String("Could not initialize muxer segment.");
      }

      SegmentInfo muxerSegmentInfo = muxerSegment.getSegmentInfo();
      muxerSegmentInfo.setWritingApp("y4mwavEncodeSample");

      // Add video Track
      long newVideoTrackNumber =
          muxerSegment.addVideoTrack(vpxConfig.getWidth(), vpxConfig.getHeight(), 0);
      if (newVideoTrackNumber == 0) {
        return new String("Could not add video track.");
      }

      // Add audio Track
      int channels = vorbisConfig.channels;
      int sampleRate = vorbisConfig.sample_rate;
      long newAudioTrackNumber = muxerSegment.addAudioTrack(sampleRate, channels, 0);
      if (newAudioTrackNumber == 0) {
        return new String("Could not add audio track.");
      }

      AudioTrack muxerTrack = (AudioTrack) muxerSegment.getTrackByNumber(newAudioTrackNumber);
      if (muxerTrack == null) {
        return new String("Could not get audio track.");
      }

      ByteBuffer privateData = vorbisEncoder.getCodecPrivate();
      if (!muxerTrack.setCodecPrivate(privateData.array())) {
        return new String("Could not add audio private data.");
      }

      final int maxSamplesToRead = 1000;
      AudioFrame audioFrame = null;
      ArrayList<VpxCodecCxPkt> encPkt = null;
      VpxCodecCxPkt pkt = null;
      int pktIndex = 0;
      boolean audioDone = false;
      boolean videoDone = false;
      boolean encoding = true;
      while (encoding) {
        // Prime the audio encoder.
        while (audioFrame == null) {
          final int samplesLeft = wavReader.samplesRemaining();
          final int samplesToRead = Math.min(samplesLeft, maxSamplesToRead);
          if (samplesToRead > 0) {
            // Read raw audio data.
            byte[] pcmArray = null;
            try {
              pcmArray = wavReader.readSamples(samplesToRead);
            } catch (Exception e) {
              return new String("Could not read audio samples.");
            }

            if (!vorbisEncoder.encodeAudio(pcmArray))
              return new String("Error encoding audio samples.");

            audioFrame = vorbisEncoder.readCompressedAudio();

            // Video is in nanoseconds.
            if (audioFrame != null) audioFrame.timestamp *= 1000000;
          } else {
            audioDone = true;
            break;
          }
        }

        if (encPkt == null) {
          // Read raw video data.
          byte[] rawVideoArray = y4mReader.getUncompressedFrame();
          if (rawVideoArray != null) {
            long frameStart = timeMultiplier.multiply(framesIn - 1).toLong();
            long nextFrameStart = timeMultiplier.multiply(framesIn++).toLong();

            encPkt = vpxEncoder.encodeFrame(rawVideoArray, LibVpxEnc.VPX_IMG_FMT_I420, frameStart, nextFrameStart - frameStart);

            // Get the first vpx encoded frame.
            pktIndex = 0;
            pkt = encPkt.get(pktIndex++);
          } else {
            videoDone = true;
          }
        }

        if ((audioDone && videoDone) || framesIn >= framesToEncode) break;

        if (!videoDone && (audioDone || pkt.pts <= audioFrame.timestamp)) {
          final boolean isKey = (pkt.flags & 0x1) == 1;
          if (!muxerSegment.addFrame(pkt.buffer, newVideoTrackNumber, pkt.pts, isKey)) {
            return new String("Could not add video frame.");
          }

          // Get the next vpx encoded frame.
          if (pktIndex < encPkt.size()) {
            pkt = encPkt.get(pktIndex++);
          } else {
            // Read the next raw video frame.
            encPkt = null;
          }
        } else if (!audioDone) {
          if (!muxerSegment.addFrame(
              audioFrame.frame.array(), newAudioTrackNumber, audioFrame.timestamp, true)) {
            return new String("Could not add audio frame.");
          }

          // Read the next compressed audio frame.
          audioFrame = vorbisEncoder.readCompressedAudio();
          if (audioFrame != null) audioFrame.timestamp *= 1000000;
        }
      }

      if (!muxerSegment.finalizeSegment()) {
        return new String("Finalization of segment failed.");
      }

    } catch (Exception e) {
      return new String("Caught error in main encode loop.");
    } finally {
      if (mkvWriter != null) {
        mkvWriter.close();
      }
    }

    return new String("Success!");
  }

  /*
   * This function will encode a byte array to a video WebM file. |webmOutputName| filename of the
   * WebM file to write to. |srcFrame| is source frame to convert and encode multiple times.
   * |fourcc| LibVpxEnc fourcc of the source. |width| width of the source. |height| height of the
   * source. |rate| fps numerator of the output WebM. |scale| fps denominator of the output WebM.
   * |framesToEncode| is the number of video frames to encode before stopping. Returns "Success!"
   * on success, an error string otherwise.
   */
  static public String testVideoConvertEncode(String webmOutputName,
      byte[] srcFrame, long fourcc, int width, int height, int rate, int scale,
      int framesToEncode) {
    LibVpxEncConfig encoderConfig = null;
    LibVpxEnc encoder = null;
    MkvWriter mkvWriter = null;

    try {
      encoderConfig = new LibVpxEncConfig(width, height);
      encoder = new LibVpxEnc(encoderConfig);

      // libwebm expects nanosecond units
      encoderConfig.setTimebase(1, 1000000000);
      Rational timeBase = encoderConfig.getTimebase();
      Rational frameRate = new Rational(rate, scale);
      Rational timeMultiplier = timeBase.multiply(frameRate).reciprocal();
      int framesIn = 1;

      mkvWriter = new MkvWriter();
      if (!mkvWriter.open(webmOutputName)) {
        return new String("WebM Output name is invalid or error while opening.");
      }

      Segment muxerSegment = new Segment();
      if (!muxerSegment.init(mkvWriter)) {
        return new String("Could not initialize muxer segment.");
      }

      SegmentInfo muxerSegmentInfo = muxerSegment.getSegmentInfo();
      muxerSegmentInfo.setWritingApp("y4mEncodeSample");

      long newVideoTrackNumber = muxerSegment.addVideoTrack(width, height, 0);
      if (newVideoTrackNumber == 0) {
        return new String("Could not add video track.");
      }

      while (framesIn < framesToEncode) {
        long frameStart = timeMultiplier.multiply(framesIn - 1).toLong();
        long nextFrameStart = timeMultiplier.multiply(framesIn).toLong();

        ArrayList<VpxCodecCxPkt> encPkt = encoder.convertEncodeFrame(
            srcFrame, frameStart, nextFrameStart - frameStart, fourcc);
        for (int i = 0; i < encPkt.size(); i++) {
          VpxCodecCxPkt pkt = encPkt.get(i);
          final boolean isKey = (pkt.flags & 0x1) == 1;

          if (!muxerSegment.addFrame(pkt.buffer, newVideoTrackNumber, pkt.pts, isKey)) {
            return new String("Could not add frame.");
          }
        }

        ++framesIn;
      }

      if (!muxerSegment.finalizeSegment()) {
        return new String("Finalization of segment failed.");
      }

    } catch (LibVpxException e) {
      return new String("Encoder error : " + e);
    } finally {
      if (encoder != null) {
        encoder.close();
      }
      if (encoderConfig != null) {
        encoderConfig.close();
      }
      if (mkvWriter != null) {
        mkvWriter.close();
      }
    }

    return new String("Success!");
  }

  /*
   * This function will encode an int array to a video WebM file. |webmOutputName| filename of the
   * WebM file to write to. |srcFrame| is source frame to convert and encode multiple times.
   * |fourcc| LibVpxEnc fourcc of the source. |width| width of the source. |height| height of the
   * source. |rate| fps numerator of the output WebM. |scale| fps denominator of the output WebM.
   * |framesToEncode| is the number of video frames to encode before stopping. Returns "Success!"
   * on success, an error string otherwise.
   */
  static public String testVideoConvertEncode(String webmOutputName,
      int[] srcFrame, long fourcc, int width, int height, int rate, int scale,
      int framesToEncode) {
    LibVpxEncConfig encoderConfig = null;
    LibVpxEnc encoder = null;
    MkvWriter mkvWriter = null;

    try {
      encoderConfig = new LibVpxEncConfig(width, height);
      encoder = new LibVpxEnc(encoderConfig);

      // libwebm expects nanosecond units
      encoderConfig.setTimebase(1, 1000000000);
      Rational timeBase = encoderConfig.getTimebase();
      Rational frameRate = new Rational(rate, scale);
      Rational timeMultiplier = timeBase.multiply(frameRate).reciprocal();
      int framesIn = 1;

      mkvWriter = new MkvWriter();
      if (!mkvWriter.open(webmOutputName)) {
        return new String("WebM Output name is invalid or error while opening.");
      }

      Segment muxerSegment = new Segment();
      if (!muxerSegment.init(mkvWriter)) {
        return new String("Could not initialize muxer segment.");
      }

      SegmentInfo muxerSegmentInfo = muxerSegment.getSegmentInfo();
      muxerSegmentInfo.setWritingApp("y4mEncodeSample");

      long newVideoTrackNumber = muxerSegment.addVideoTrack(width, height, 0);
      if (newVideoTrackNumber == 0) {
        return new String("Could not add video track.");
      }

      while (framesIn < framesToEncode) {
        long frameStart = timeMultiplier.multiply(framesIn - 1).toLong();
        long nextFrameStart = timeMultiplier.multiply(framesIn).toLong();

        ArrayList<VpxCodecCxPkt> encPkt = encoder.convertIntEncodeFrame(
            srcFrame, frameStart, nextFrameStart - frameStart, fourcc);
        for (int i = 0; i < encPkt.size(); i++) {
          VpxCodecCxPkt pkt = encPkt.get(i);
          final boolean isKey = (pkt.flags & 0x1) == 1;

          if (!muxerSegment.addFrame(pkt.buffer, newVideoTrackNumber, pkt.pts, isKey)) {
            return new String("Could not add frame.");
          }
        }

        ++framesIn;
      }

      if (!muxerSegment.finalizeSegment()) {
        return new String("Finalization of segment failed.");
      }

    } catch (LibVpxException e) {
      return new String("Encoder error : " + e);
    } finally {
      if (encoder != null) {
        encoder.close();
      }
      if (encoderConfig != null) {
        encoderConfig.close();
      }
      if (mkvWriter != null) {
        mkvWriter.close();
      }
    }

    return new String("Success!");
  }
}

