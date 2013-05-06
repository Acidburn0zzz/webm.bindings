import java.io.File;
import java.nio.ByteBuffer;

import com.google.libvorbis.AudioFrame;
import com.google.libvorbis.VorbisEncoderConfig;
import com.google.libvorbis.VorbisEncoderWrapper;
import com.google.libwebm.mkvmuxer.AudioTrack;
import com.google.libwebm.mkvmuxer.MkvWriter;
import com.google.libwebm.mkvmuxer.Segment;
import com.google.libwebm.mkvmuxer.SegmentInfo;
import com.google.utils.WavReader;

public class EncodeWavJavaExample {
  /*
   * This function will encode an audio WebM file. |wavInputName| filename of the source audio. The
   * source audio must be a WAV file with raw PCM data. |webmOutputName| filename of the WebM
   * file to write to. Returns true on success. If there is an error, |error| will be set to a
   * descriptive string.
   */
  static public boolean encodeWavJavaExample(String wavInputName, String webmOutputName,
                                             StringBuilder error) {
    VorbisEncoderConfig vorbisConfig = null;
    VorbisEncoderWrapper vorbisEncoder = null;
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
      muxerSegmentInfo.setWritingApp("wavEncodeSample");

      // Add Audio Track
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

        if (!vorbisEncoder.encodeAudio(pcmArray)) {
          error.append("Error encoding samples.");
          return false;
        }

        AudioFrame frame = null;
        while ((frame = vorbisEncoder.readCompressedAudio()) != null) {
          if (!muxerSegment.addFrame(
              frame.frame.array(), newAudioTrackNumber, frame.timestamp * 1000000, true)) {
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
