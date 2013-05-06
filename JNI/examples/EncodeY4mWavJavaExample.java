import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;

import com.google.libvorbis.AudioFrame;
import com.google.libvorbis.VorbisEncoderConfig;
import com.google.libvorbis.VorbisEncoderWrapper;
import com.google.libvpx.LibVpxEnc;
import com.google.libvpx.LibVpxEncConfig;
import com.google.libvpx.Rational;
import com.google.libvpx.VpxCodecCxPkt;
import com.google.libwebm.mkvmuxer.AudioTrack;
import com.google.libwebm.mkvmuxer.MkvWriter;
import com.google.libwebm.mkvmuxer.Segment;
import com.google.libwebm.mkvmuxer.SegmentInfo;
import com.google.utils.WavReader;
import com.google.utils.Y4MReader;

public class EncodeY4mWavJavaExample {
  /*
   * This function will encode an audio and video WebM file. |y4mName| filename of the source video.
   * The source video must be a Y4M file with raw i420 frames. |wavName| filename of the source
   * audio. The source audio must be a WAV file with raw PCM data. |webmOutputName| filename of the
   * WebM file to write to. |framesToEncode| is the number of video frames to encode before
   * stopping. Returns true on success. If there is an error, |error| will be set to a descriptive
   * string.
   */
  static public boolean encodeY4mWavJavaExample(String y4mName, String wavName,
                                                String webmOutputName, int framesToEncode,
                                                StringBuilder error) {
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
        error.append("Error creating y4m file:" + y4mName + " : " + e);
        return false;
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
        error.append("Error creating wav file:" + wavName);
        return false;
      }

      vorbisConfig = new VorbisEncoderConfig();
      vorbisConfig.channels = wavReader.nChannels();
      vorbisConfig.sample_rate = wavReader.nSamplesPerSec();
      vorbisConfig.bytes_per_second = wavReader.nAvgBytesPerSec();
      vorbisConfig.block_align = wavReader.nBlockAlign();
      vorbisConfig.bits_per_sample = wavReader.wBitsPerSample();

      vorbisEncoder = new VorbisEncoderWrapper();
      if (!vorbisEncoder.Init(vorbisConfig)) {
        error.append("Could not initialize Vorbis encoder.");
        return false;
      }

      mkvWriter = new MkvWriter();
      if (!mkvWriter.open(webmOutputName)) {
        error.append("WebM Output name is invalid or error while opening.");
        return false;
      }

      Segment muxerSegment = new Segment();
      if (!muxerSegment.init(mkvWriter)) {
        error.append("Could not initialize muxer segment.");
        return false;
      }

      SegmentInfo muxerSegmentInfo = muxerSegment.getSegmentInfo();
      muxerSegmentInfo.setWritingApp("y4mwavEncodeSample");

      // Add video Track
      long newVideoTrackNumber =
          muxerSegment.addVideoTrack(vpxConfig.getWidth(), vpxConfig.getHeight(), 0);
      if (newVideoTrackNumber == 0) {
        error.append("Could not add video track.");
        return false;
      }

      // Add audio Track
      int channels = vorbisConfig.channels;
      int sampleRate = vorbisConfig.sample_rate;
      long newAudioTrackNumber = muxerSegment.addAudioTrack(sampleRate, channels, 0);
      if (newAudioTrackNumber == 0) {
        error.append("Could not add audio track.");
        return false;
      }

      AudioTrack muxerTrack = (AudioTrack) muxerSegment.getTrackByNumber(newAudioTrackNumber);
      if (muxerTrack == null) {
        error.append("Could not get audio track.");
        return false;
      }

      ByteBuffer privateData = vorbisEncoder.getCodecPrivate();
      if (!muxerTrack.setCodecPrivate(privateData.array())) {
        error.append("Could not add audio private data.");
        return false;
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
              error.append("Could not read audio samples.");
              return false;
            }

            if (!vorbisEncoder.encodeAudio(pcmArray)) {
              error.append("Error encoding audio samples.");
              return false;
            }

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
            error.append("Could not add video frame.");
            return false;
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
            error.append("Could not add audio frame.");
            return false;
          }

          // Read the next compressed audio frame.
          audioFrame = vorbisEncoder.readCompressedAudio();
          if (audioFrame != null) audioFrame.timestamp *= 1000000;
        }
      }

      if (!muxerSegment.finalizeSegment()) {
        error.append("Finalization of segment failed.");
        return false;
      }

    } catch (Exception e) {
      error.append("Caught error in main encode loop.");
      return false;
    } finally {
      if (mkvWriter != null) {
        mkvWriter.close();
      }
    }

    return true;
  }
}
