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
import com.google.libvpx.Y4MReader;

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

    try {
      Rational frameRate = y4mReader.getFrameRate();
      encoderConfig = new LibVpxEncConfig(y4mReader.getWidth(),
                                          y4mReader.getHeight());
      int framesIn = 1;
      encoder = new LibVpxEnc(encoderConfig);

      long timebaseDen = 100;
      long timebaseNum = 1;

      ivfWriter = new IVFWriter(ivfFileName,
                                encoderConfig.getFourcc(),
                                encoderConfig.getWidth(),
                                encoderConfig.getHeight(),
                                encoderConfig.getTimebase());

      byte[] uncompressedFrame;
      while ((uncompressedFrame = y4mReader.getUncompressedFrame()) != null &&
              framesIn < maxFramesToDecode) {
        ArrayList<VpxCodecCxPkt> encPkt;
        long frameStart = (timebaseDen * (framesIn - 1)
                        * frameRate.den()) / timebaseNum / frameRate.num();
        long nextFrameStart = (timebaseDen * framesIn
                            * frameRate.den())
                            / timebaseNum / frameRate.num();

        encPkt = encoder.encodeFrame(uncompressedFrame, frameStart,
                                     nextFrameStart - frameStart);

        for (int i = 0; i < encPkt.size(); i++) {
          VpxCodecCxPkt pkt = encPkt.get(i);
          ivfWriter.writeFrame(pkt, 0L);
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
    }

    LibVpxDec decoder = null;
    try {
      IVFReader ivfReader = new IVFReader(ivfFileName);
      decoder = new LibVpxDec();

      byte[] compressedFrame;
      while ((compressedFrame = ivfReader.readNextFrame()) != null) {
        decoder.decodeFrame(compressedFrame);
        // TODO(frkoenig) : Write decoded frame to disk.
      }

      System.out.println("vpx version: " + decoder.versionString());
    } catch (IOException e) {
      System.err.println("Error reading " + ivfFileName + " : " + e);
    } finally {
      if (decoder != null) {
        decoder.close();
      }
    }
  }
}