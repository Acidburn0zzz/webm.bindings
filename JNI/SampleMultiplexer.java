// Author: mszal@google.com (Michael Szal)

import com.google.libwebm.mkvmuxer.MkvWriter;
import com.google.libwebm.mkvmuxer.Segment;
import com.google.libwebm.mkvmuxer.SegmentInfo;
import com.google.libwebm.mkvparser.EbmlHeader;
import com.google.libwebm.mkvparser.MkvReader;
import com.google.libwebm.mkvparser.Track;
import com.google.libwebm.mkvparser.Tracks;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

public class SampleMultiplexer {

  public static void main(String[] args) {
    String inputFileName = null;
    String outputFileName = null;

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
  }

  private static void PrintUsage() {
    String usage = "Usage: java SampleMultiplexer -i inputFileName -o outputFileName [options]\n"
        + "\n"
        + "Main options:\n"
        + "  -h | -?   show help";
    System.out.println(usage);
  }
}
