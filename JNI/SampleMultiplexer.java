// Author: mszal@google.com (Michael Szal)

import com.google.libwebm.mkvparser.EbmlHeader;
import com.google.libwebm.mkvparser.MkvReader;
import com.google.libwebm.mkvparser.Segment;
import com.google.libwebm.mkvparser.SegmentInfo;

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
      System.out.println("\nFilename is invalid or error while opening.");
      System.exit(1);
    }

    EbmlHeader ebmlHeader = new EbmlHeader();
    long[] outputPosition = {0};
    ebmlHeader.parse(mkvReader, outputPosition);
    long position = outputPosition[0];

    Segment[] outputParserSegment = {null};
    long result = Segment.createInstance(mkvReader, position, outputParserSegment);
    Segment parserSegment = outputParserSegment[0];
    if (result != 0) {
      System.out.println("\nSegment.createInstance() failed.");
      System.exit(1);
    }

    result = parserSegment.load();
    if (result < 0) {
      System.out.println("\nSegment.load() failed.");
      System.exit(1);
    }

    SegmentInfo segmentInfo = parserSegment.getInfo();
    long timeCodeScale = segmentInfo.getTimeCodeScale();
  }

  private static void PrintUsage() {
    String usage = "Usage: java SampleMultiplexer -i inputFileName -o outputFileName [options]\n"
        + "\n"
        + "Main options:\n"
        + "  -h | -?   show help";
    System.out.println(usage);
  }
}
