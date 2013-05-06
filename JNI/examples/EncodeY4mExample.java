import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import com.google.libvpx.LibVpxEnc;
import com.google.libvpx.LibVpxEncConfig;
import com.google.libvpx.LibVpxException;
import com.google.libvpx.Rational;
import com.google.libvpx.VpxCodecCxPkt;
import com.google.libwebm.mkvmuxer.MkvWriter;
import com.google.libwebm.mkvmuxer.Segment;
import com.google.libwebm.mkvmuxer.SegmentInfo;
import com.google.utils.Y4MReader;

public class EncodeY4mExample {
  /*
   * This function will encode a video WebM file. |y4mInputName| filename of the source video. The
   * source video must be a Y4M file with raw i420 frames. |webmOutputName| filename of the WebM
   * file to write to. |framesToEncode| is the number of frames to encode before stopping. Returns
   * true on success. If there is an error, |error| will be set to a descriptive string.
   */
  static public boolean encodeY4mExample(
      String y4mInputName, String webmOutputName, int framesToEncode, StringBuilder error) {
    File y4mFile = new File(y4mInputName);
    Y4MReader y4mReader;

    try {
      y4mReader = new Y4MReader(y4mFile);
    } catch (IOException e) {
      error.append("Error reading " + y4mFile + " : " + e);
      return false;
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
        error.append("WebM Output name is invalid or error while opening.");
        return false;
      }

      Segment muxerSegment = new Segment();
      if (!muxerSegment.init(mkvWriter)) {
        error.append("Could not initialize muxer segment.");
        return false;
      }

      SegmentInfo muxerSegmentInfo = muxerSegment.getSegmentInfo();
      muxerSegmentInfo.setWritingApp("y4mEncodeSample");

      long newVideoTrackNumber =
          muxerSegment.addVideoTrack(encoderConfig.getWidth(), encoderConfig.getHeight(), 0);
      if (newVideoTrackNumber == 0) {
        error.append("Could not add video track.");
        return false;
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
            error.append("Could not add frame.");
            return false;
          }
        }

        ++framesIn;
      }

      if (!muxerSegment.finalizeSegment()) {
        error.append("Finalization of segment failed.");
        return false;
      }

    } catch (IOException e) {
      error.append("IOException" + e);
      return false;
    } catch (LibVpxException e) {
      error.append("Encoder error : " + e);
      return false;
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

    return true;
  }
}
