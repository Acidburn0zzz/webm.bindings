package com.google.libvorbis;

/**
 * Class to hold parameters for the Vorbis encoder.
 */
public class VorbisEncoderConfig {
  public enum Format {kAudioFormatPcm, kAudioFormatVorbis}

  public Format format_tag;            // Audio format.
  public short channels;              // Number of channels.
  public int sample_rate;             // Samples per second.
  public int bytes_per_second;        // Average bytes per second.
  public short block_align;           // Atomic audio unit size in bytes.
  public short bits_per_sample;       // Sample container size.

  // Rate control values. Set the min and max values to |kUseDefault| to
  // encode at an average bitrate. Use the same value for minimum, average, and
  // maximum to encode at a constant bitrate. Values are in kilobits.
  public int average_bitrate;
  public int minimum_bitrate;
  public int maximum_bitrate;

  // Advanced Vorbis encoding settings. More information about the effects and
  // usage of these settings can be found on the documentation page for the
  // libvorbis function vorbis_encode_ctl:
  // http://xiph.org/vorbis/doc/vorbisenc/vorbis_encode_ctl.html

  // Selects a quality mode based on |average_bitrate|, and disables libvorbis
  // rate control. In other words, this allows libvorbis to produce a (somewhat)
  // variable bitrate.
  // Note: The flag is ignored when minimum and maximum bitrates are not
  //       |kUseDefault| or -1.
  public boolean bitrate_based_quality;

  // Impulse block bias. Valid range is -15.0 to 0.0.
  public double impulse_block_bias;

  // Hard-lowpass frequency. Valid range is 2 to 99.
  public double lowpass_frequency;

  public VorbisEncoderConfig() {
    format_tag = Format.kAudioFormatPcm;
    channels = 2;
    bytes_per_second = 0;
    sample_rate = 44100;
    block_align = 0;
    bits_per_sample = 16;

    average_bitrate = 64000;
    minimum_bitrate = -1;
    maximum_bitrate = -1;

    bitrate_based_quality = true;
    impulse_block_bias = -7.5;
    lowpass_frequency = 50.0;
  }

  public VorbisEncoderConfig(VorbisEncoderConfig copy) {
    format_tag = copy.format_tag;
    channels = copy.channels;
    bytes_per_second = copy.bytes_per_second;
    sample_rate = copy.sample_rate;
    block_align = copy.block_align;
    bits_per_sample = copy.bits_per_sample;

    average_bitrate = copy.average_bitrate;
    minimum_bitrate = copy.minimum_bitrate;
    maximum_bitrate = copy.maximum_bitrate;

    bitrate_based_quality = copy.bitrate_based_quality;
    impulse_block_bias = copy.impulse_block_bias;
    lowpass_frequency = copy.lowpass_frequency;
  }

  public Format format_tag() {
    return format_tag;
  }

  public short channels() {
    return channels;
  }

  public int sample_rate() {
    return sample_rate;
  }

  public int bytes_per_second() {
    return bytes_per_second;
  }

  public short block_align() {
    return block_align;
  }

  public short bits_per_sample() {
    return bits_per_sample;
  }
}
