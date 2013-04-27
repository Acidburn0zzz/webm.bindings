package com.google.libvorbis;

import com.google.libogg.OggPacket;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.ShortBuffer;
import java.util.LinkedList;
import java.util.Queue;

/**
 * This class wraps Vorbis and Ogg JNI
 */
public class VorbisEncoderWrapper {
  private VorbisDspState dsp_state_;
  private VorbisInfo info_;
  private VorbisBlock block_;
  private OggPacket ident_packet;
  private OggPacket comments_packet;
  private OggPacket setup_packet;
  VorbisEncoderConfig config = null;

  private long lastGranulepos;
  private Queue<OggPacket> vorbisPackets;

  public VorbisEncoderWrapper() {
      info_ = new VorbisInfo();
      dsp_state_ = new VorbisDspState();
      block_ = new VorbisBlock();
      ident_packet = null;
      comments_packet = null;
      setup_packet = null;
      lastGranulepos = 0;
  }

  public boolean Init(VorbisEncoderConfig configArg) {
    config = new VorbisEncoderConfig(configArg);

    if (config.channels <= 0 || config.channels > 2)
      return false;

    if (config.format_tag != VorbisEncoderConfig.Format.kAudioFormatPcm)
      return false;

    if (config.format_tag == VorbisEncoderConfig.Format.kAudioFormatPcm &&
        config.bits_per_sample != 16)
      return false;

    Codec.vorbisInfoInit(info_);

    int status =
        VorbisEnc.vorbisEncodeSetupManaged(info_, config.channels, config.sample_rate,
            config.minimum_bitrate, config.average_bitrate, config.maximum_bitrate);
    if (status != 0)
      return false;

    if (config.minimum_bitrate == -1 && config.maximum_bitrate == -1 &&
        config.bitrate_based_quality) {
      // Enable VBR.
      if (!CodecControlSet(VorbisEnc.OV_ECTL_RATEMANAGE2_SET, 0)) {
        return false;
      }
    }

    status = VorbisEnc.vorbisEncodeSetupInit(info_);
    if (status != 0)
        return false;

    status = Codec.vorbisAnalysisInit(dsp_state_, info_);
    if (status != 0)
        return false;

    status = Codec.vorbisBlockInit(dsp_state_, block_);
    if (status != 0)
        return false;

    status = GenerateHeaders();
    if (status != 0)
      return false;

    config.format_tag = VorbisEncoderConfig.Format.kAudioFormatVorbis;
    vorbisPackets = new LinkedList<OggPacket>();
    return true;
  }

  public ByteBuffer getCodecPrivate() {
    // Perform minimal private data validation.
    if (ident_packet == null || comments_packet == null || setup_packet == null)
      return null;

    if (ident_packet.getBytes() > 255 || comments_packet.getBytes() > 255)
      return null;

    final long data_length =
        ident_packet.getBytes() + comments_packet.getBytes() + setup_packet.getBytes();

    // Calculate total bytes of storage required for the private data chunk.
    // 1 byte to store header count (total headers - 1 = 2).
    // 1 byte each for ident and comment length values.
    // The length of setup data is implied by the total length.
    final int header_length = 1 + 1 + 1 + (int)data_length;
    ByteBuffer data = ByteBuffer.allocate(header_length);

    // Write header count. As above, number of headers - 1.
    data.put((byte)2);

    // Write ident length, comment length.
    data.put((byte)ident_packet.getBytes());
    data.put((byte)comments_packet.getBytes());

    // Write the data blocks.
    byte[] indentData = ident_packet.getPacketData();
    data.put(indentData);

    byte[] commentsData = comments_packet.getPacketData();
    data.put(commentsData);

    byte[] setupData = setup_packet.getPacketData();
    data.put(setupData);

    return data;
  }

  public boolean encodeAudio(byte[] pcmArray) {
    // TODO(fgalligan): Check mod block_align

    final int channels = config.channels;
    final int num_blocks = pcmArray.length / config.block_align;

    ByteBuffer byteBuffer = ByteBuffer.wrap(pcmArray);
    byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
    ShortBuffer sampleBuffer = byteBuffer.asShortBuffer();

    float[][] float2dArray = new float[channels][num_blocks];

    for (int i = 0; i < num_blocks; ++i) {
      for (int c = 0; c < channels; ++c) {
        short sample = sampleBuffer.get();
        float2dArray[c][i] = sample / 32768.f;
      }
    }

    Codec.vorbisAnalysisBuffer(dsp_state_, float2dArray);
    int status = Codec.vorbisAnalysisWrote(dsp_state_, num_blocks);
    if (status != 0)
      return false;
    return true;
  }

  public AudioFrame readCompressedAudio() {
    if (samplesEncoded()) {
      // There's a compressed block available-- give libvorbis a chance to
      // optimize distribution of data for the current encode settings.
      OggPacket packet = new OggPacket();
      int status = Codec.vorbisAnalysis(block_, packet);
      if (status != 0)
        return null;

      status = Codec.vorbisBitrateAddblock(block_);
      if (status != 0)
        return null;

      while ((status = Codec.vorbisBitrateFlushpacket(dsp_state_, packet)) == 1) {
        //Using the add method to add items.
        //Should anything go wrong an exception will be thrown.
        if (packet.getGranulepos() > 0)
          vorbisPackets.add(packet);
      }
    }

    // Calculate size of data.
    int totalSize = 0;
    for(OggPacket p : vorbisPackets){
      totalSize += p.getBytes();
    }
    if (totalSize == 0)
      return null;

    ByteBuffer data = ByteBuffer.allocate(totalSize);

    long timestamp = (long)samplesToMilliseconds(lastGranulepos);

    while (vorbisPackets.size() > 0) {
      OggPacket packet = vorbisPackets.remove();
      lastGranulepos = packet.getGranulepos();

      byte[] packetData = packet.getPacketData();
      data.put(packetData);
    }

    AudioFrame frame = new AudioFrame(timestamp, data);
    return frame;
  }

  //When |SamplesAvailable()| returns true, the user must consume all samples
  //made available by libvorbis. Any compressed samples left unconsumed will be
  //lost.
  private boolean samplesEncoded() {
    final int kSamplesAvailable = 1;
    int status = Codec.vorbisAnalysisBlockout(dsp_state_, block_);
    if (status == kSamplesAvailable) {
      return true;
    }
    return false;
  }

  private int GenerateHeaders() {
    VorbisComment comments = new VorbisComment();
    Codec.vorbisCommentInit(comments);

    // Add app name and version to vorbis comments.
    String encoder_id = "WebM JNI bindings";
    String kVorbisEncoderTag = "encoder";

    Codec.vorbisCommentAddTag(comments, kVorbisEncoderTag, encoder_id);

    // Generate the vorbis header packets.
    ident_packet = new OggPacket();
    comments_packet = new OggPacket();
    setup_packet = new OggPacket();

    int status =
        Codec.vorbisAnalysisHeaderout(dsp_state_, comments, ident_packet, comments_packet,
            setup_packet);
    if (status != 0) return status;
    return 0;
  }

  private boolean CodecControlSet(int control_id, int val) {
    int status = 0;
    if (control_id == VorbisEnc.OV_ECTL_RATEMANAGE2_SET && val == 0) {
      // Special case disabling rate control-- libvorbis expects a NULL
      // pointer.
      status = VorbisEnc.vorbisEncodeCtlSetNull(info_, control_id);
    } else {
      status = VorbisEnc.vorbisEncodeCtlSetInt(info_, control_id, val);
    }
    if (status != 0)
      return false;
    return true;
  }

  private double samplesToMilliseconds(long numSamples) {
    final double sample_rate = config.sample_rate;
    double seconds = 0.0;
    if (sample_rate != 0) {
      seconds = numSamples / sample_rate;
    }
    return seconds * 1000.0;
  }
}
