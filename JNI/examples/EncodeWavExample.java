import java.io.File;

import com.google.libvorbis.VorbisEncConfig;
import com.google.libvorbis.VorbisEncoderC;
import com.google.libwebm.mkvmuxer.AudioTrack;
import com.google.libwebm.mkvmuxer.MkvWriter;
import com.google.libwebm.mkvmuxer.Segment;
import com.google.libwebm.mkvmuxer.SegmentInfo;
import com.google.utils.WavReader;

public class EncodeWavExample {
  /*
   * This function will encode an audio WebM file. |wavInputName| filename of the source audio. The
   * source audio must be a WAV file with raw PCM data. |webmOutputName| filename of the WebM
   * file to write to. Returns true on success. If there is an error, |error| will be set to a
   * descriptive string.
   */
  static public boolean encodeWavExample(String wavInputName, String webmOutputName,
                                         StringBuilder error) {
    VorbisEncoderC vorbisEncoder = null;
    VorbisEncConfig vorbisConfig = null;
    MkvWriter mkvWriter = null;

    try {
      File pcmFile = new File(wavInputName);
      WavReader wavReader = null;
      try {
        wavReader = new WavReader(pcmFile);
      } catch (Exception e) {
        error.append("Could not create wav reader.");
        return false;
      }

      int channels = wavReader.nChannels();
      int sampleRate = wavReader.nSamplesPerSec();

      vorbisConfig = new VorbisEncConfig();
      vorbisConfig.setChannels((short)channels);
      vorbisConfig.setSampleRate(sampleRate);
      vorbisConfig.setBitsPerSample(wavReader.wBitsPerSample());

      vorbisEncoder = new VorbisEncoderC();
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
      muxerSegmentInfo.setWritingApp("wavEncodeSample");

      // Add Audio Track
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

      byte[] buffer = vorbisEncoder.CodecPrivate();
      if (buffer == null) {
        error.append("Could not get audio private data.");
        return false;
      }
      if (!muxerTrack.setCodecPrivate(buffer)) {
        error.append("Could not add audio private data.");
        return false;
      }

      final int maxSamplesToRead = 1000;
      int samplesLeft = 0;
      while ((samplesLeft = wavReader.samplesRemaining()) > 0) {
        byte[] pcmArray = null;
        int samplesToRead = Math.min(samplesLeft, maxSamplesToRead);
        try {
          pcmArray = wavReader.readSamples(samplesToRead);
        } catch (Exception e) {
          error.append("Could not read samples.");
          return false;
        }

        if (!vorbisEncoder.Encode(pcmArray)) {
          error.append("Error encoding samples.");
          return false;
        }

        long[] timestamp = new long[2];

        byte[] frame = null;
        while ((frame = vorbisEncoder.ReadCompressedAudio(timestamp)) != null) {
          if (!muxerSegment.addFrame(
              frame, newAudioTrackNumber, timestamp[0] * 1000000, true)) {
            error.append("Could not add audio frame.");
            return false;
          }
        }
      }

      if (!muxerSegment.finalizeSegment()) {
        error.append("Finalization of segment failed.");
        return false;
      }

    } finally {
      if (mkvWriter != null) {
        mkvWriter.close();
      }
    }

    return true;
  }
}
