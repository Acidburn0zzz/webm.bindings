// Copyright 2012 Google Inc. All Rights Reserved.
// Author: frkoenig@google.com (Fritz Koenig)
import com.google.libvpx.IVFReader;
import com.google.libvpx.IVFWriter;
import com.google.libvpx.LibVpxDec;
import com.google.libvpx.LibVpxEnc;
import com.google.libvpx.LibVpxEncConfig;
import com.google.libvpx.LibVpxException;
import com.google.libvpx.Rational;
import com.google.libvpx.VpxCodecCxPkt;
import com.google.libvpx.WebmWriter;
import com.google.libvpx.Y4MReader;
import com.google.libvpx.Y4MWriter;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

 /**
  * Simple application that loads a file, compresses it and then
  * decompresses that file.
  */
public class Application {
  static int maxFramesToDecode = 30;

  public static void main(String[] args) {
    File y4mFileName = new File("input/foreman_cif.y4m");
    File ivfFileName = new File("output/foreman_cif_420p_352x288.ivf");
    File webmFileName = new File("output/foreman_cif_420p_352x288.webm");
    Y4MReader y4mReader;

    try {
      y4mReader = new Y4MReader(y4mFileName);
    } catch (IOException e) {
      System.err.println("Error reading " + y4mFileName + " : " + e);
      System.exit(-1);
      // TODO(frkoenig) : fix warning that y4mReader is not initialized when
      //                  System.exit(-1) is called without return;
      return;
    }

    LibVpxEncConfig encoderConfig = null;
    IVFWriter ivfWriter = null;
    LibVpxEnc encoder = null;
    WebmWriter webmWriter = null;

    try {
      encoderConfig = new LibVpxEncConfig(y4mReader.getWidth(),
                                          y4mReader.getHeight());
      encoder = new LibVpxEnc(encoderConfig);

      ivfWriter = new IVFWriter(ivfFileName,
                                encoderConfig.getFourcc(),
                                encoderConfig.getWidth(),
                                encoderConfig.getHeight(),
                                encoderConfig.getTimebase());

      byte[] uncompressedFrame;
      Rational timeBase = encoderConfig.getTimebase();
      Rational timeMultiplier = timeBase.multiply(y4mReader.getFrameRate()).reciprocal();
      int framesIn = 1;
      webmWriter = new WebmWriter(webmFileName,
                                  encoderConfig.getWidth(),
                                  encoderConfig.getHeight(),
                                  encoderConfig.getTimebase(),
                                  y4mReader.getFrameRate());

      while ((uncompressedFrame = y4mReader.getUncompressedFrame()) != null &&
              framesIn < maxFramesToDecode) {
        long frameStart = timeMultiplier.multiply(framesIn - 1).toLong();
        long nextFrameStart = timeMultiplier.multiply(framesIn).toLong();

        ArrayList<VpxCodecCxPkt> encPkt = encoder.encodeFrame(
            uncompressedFrame, frameStart, nextFrameStart - frameStart);

        for (int i = 0; i < encPkt.size(); i++) {
          VpxCodecCxPkt pkt = encPkt.get(i);
          ivfWriter.writeFrame(pkt, 0L);
          webmWriter.writeFrame(pkt);
        }

        ++framesIn;
      }

    } catch (IOException e) {
      System.err.println(e);
    } catch (LibVpxException e) {
      System.err.println("Encoder error : " + e);
    } finally {
      if (encoder != null) {
        encoder.close();
      }
      if (encoderConfig != null) {
        encoderConfig.close();
      }
      if (ivfWriter != null) {
        ivfWriter.close();
      }
      if (webmWriter != null) {
        webmWriter.close();
      }
    }

    File y4mOutputFileName = new File("output/foreman_cif.y4m");
    LibVpxDec decoder = null;
    Y4MWriter y4mWriter = null;
    try {
      IVFReader ivfReader = new IVFReader(ivfFileName);
      decoder = new LibVpxDec();

      y4mWriter = new Y4MWriter(y4mOutputFileName,
          ivfReader.getWidth(), ivfReader.getHeight(), y4mReader.getFrameRate());

      byte[] compressedFrame;
      while ((compressedFrame = ivfReader.readNextFrame()) != null) {
        byte[] uncompressedFrame = decoder.decodeFrameToBuffer(compressedFrame);
        if (uncompressedFrame != null) {
          y4mWriter.writeFrame(uncompressedFrame);
        }
      }

      System.out.println("vpx version: " + decoder.versionString());
    } catch (IOException e) {
      System.err.println("Error reading " + ivfFileName + " : " + e);
    } catch (LibVpxException e) {
      System.err.println("Decoder error : " + e);
    } finally {
      if (decoder != null) {
        decoder.close();
      }
      if (y4mWriter != null) {
        y4mWriter.close();
      }
    }

    if (LibVpxEnc.haveLibyuv()) {
      final int width = 320;
      final int height = 180;
      final int rate = 24;
      final int scale = 1;
      final int framesToEncode = 200;
      byte[] rgbFrame = new byte[width * height * 3];

      // Create a green gradiant.
      for (int y = 0; y < height; ++y) {
        final byte green = (byte)y;
        final int xStart = y * width * 3;
        for (int x = 0; x < width; ++x) {
          rgbFrame[xStart + (x * 3)] = 0;
          rgbFrame[xStart + (x * 3) + 1] = green;
          rgbFrame[xStart + (x * 3) + 2] = 0;
        }
      }

      String outputWebM = "output/rgbframe.webm";
      String outStr = BindingsSamples.testVideoConvertEncode(outputWebM,
          rgbFrame, LibVpxEnc.FOURCC_24BG, width, height, rate, scale, framesToEncode);
      if (outStr != "Success!")
        System.err.println(outStr);
    }
  }
}