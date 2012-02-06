// Copyright 2012 Google Inc. All Rights Reserved.
// Author: frkoenig@google.com (Fritz Koenig)
package com.google.libvpx;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 *
 */
class Y4MHeader {
  /**
  *
  */
  class ChromaType {
    private final String type;

    public ChromaType() {
      this.type = new String("420");
    }

    public ChromaType(String type) {
      this.type = type;
    }

    public boolean is420() {
      return type.equals("420");
    }
  }

  /**
  *
  */
  class Interlaced {
    private final char interlaced;

    public Interlaced() {
      interlaced = '?';
    }

    public Interlaced(char interlaced) {
      this.interlaced = interlaced;
    }

    public boolean isProgressive() {
      if (interlaced == '?' || interlaced == 'p') {
        return true;
      }

      return false;
    }

    public String toString() {
      if (isProgressive()) {
        return new String("progressive");
      }

      return new String("interlaced");
    }
  }

  private static final byte[] cYUV4MPEG = {'Y', 'U', 'V', '4', 'M', 'P', 'E', 'G'};
  byte[]      header;
  int         width;
  int         height;
  Rational    fps;
  Rational    par;
  Interlaced  interlace;
  ChromaType  chromaType;

  public Y4MHeader(byte [] header) throws IOException {
    this.header = header;

    if (!Arrays.equals(Arrays.copyOfRange(this.header, 0, 8), cYUV4MPEG)) {
      throw new IOException("Incomplete magic for YUV4MPEG file.");
    }

    if (this.header[8] != '2') {
      throw new IOException("Incorrect YUV input file version; YUV4MPEG2 required.");
    }

    chromaType = new ChromaType();

    String tags = new String(Arrays.copyOfRange(this.header, 0, this.header.length));

    StringTokenizer st = new StringTokenizer (tags.trim());

    while (st.hasMoreTokens ()) {
      String token = st.nextToken();
      String[] parts;

      switch (token.charAt(0)) {
        case 'W':
          width = Integer.parseInt(token.substring(1));
          break;
        case 'H':
          height = Integer.parseInt(token.substring(1));
          break;
        case 'F':
          parts = token.substring(1).split(":");
          fps = new Rational (parts[0], parts[1]);
          break;
        case 'I':
          interlace = new Interlaced (token.charAt(1));
          break;
        case 'A':
          parts = token.substring(1).split(":");
          par = new Rational (parts[0], parts[1]);
          break;
        case 'C':
          chromaType = new ChromaType(token.substring(1));
          break;
        default:
        // Ignore unknown tags
          break;
      }
    }
    // TODO(frkoenig): throw something here is h/w/fps are == 0
  }

  public int getFrameSize() {
    if (chromaType.is420()) {
      return width * height + 2 * ((width + 1) / 2) * ((height + 1) / 2);
    }

    return 0;
  }
};

/**
 *
 */
public class Y4MReader {
  private FileInputStream is;
  private File file;
  Y4MHeader y4mHeader;
  private static final byte[] cFRAME = {'F', 'R', 'A', 'M', 'E', '\n'};

  public Y4MReader(File file) throws IOException {
    this.file = file;
    is = new FileInputStream(this.file);
    readHeader();
  }

  // TODO(frkoenig) : consider throwing OutOfMemory.
  private void readHeader() throws IOException {
    byte[] headerBuffer = new byte[80];

    // Read in the bytes
    int pos = 0;
    int numRead = 0;
    while (pos < (headerBuffer.length - 1)
            && (numRead = is.read(headerBuffer, pos, 1)) >= 0) {
      if (headerBuffer[pos] == '\n') {
        break;
      }
      pos += numRead;
    }

    headerBuffer[pos] = '\0';

    // Ensure all the bytes have been read in
    if (pos == (headerBuffer.length - 1)) {
      throw new IOException("Error parsing header; not a YUV2MPEG2 file? : " + file.getName());
    }

    try {
      y4mHeader = new Y4MHeader(headerBuffer);
    } catch (IOException e) {
      throw new IOException(e.getMessage() + " : " + file.getName());
    }
  }

  public byte[] getUncompressedFrame() throws IOException {
    byte[] header = readBuffer(6);

    if (header == null) {
      return null;
    }

    if (!Arrays.equals(header, cFRAME)) {
      throw new IOException("Loss of framing in Y4M input data.");
    }

    byte[] frame = readBuffer(y4mHeader.getFrameSize());

    return frame;
  }

  public Rational getFrameRate() {
    return y4mHeader.fps;
  }

  public int getWidth() {
    return y4mHeader.width;
  }

  public int getHeight() {
    return y4mHeader.height;
  }

  private byte[] readBuffer(int size) throws IOException {
    byte[] bytes = new byte[size];

    // Read in the bytes
    int offset = 0;
    int numRead = 0;
    while (offset < bytes.length
            && (numRead = is.read(bytes, offset, bytes.length - offset)) >= 0) {
      offset += numRead;
    }

    if (numRead != size) {
      return null;
    }

    return bytes;
  }
}
