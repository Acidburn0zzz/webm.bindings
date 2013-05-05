#ifndef LIBVORBIS_VORBIS_ENCODER_CONFIG_H_
#define LIBVORBIS_VORBIS_ENCODER_CONFIG_H_

namespace vorbis {

static const int kAudioFormatPcm = 1;

struct VorbisEncoderConfig {
  VorbisEncoderConfig();

  int format_tag;              // Audio format.
  short channels;              // Number of channels.
  int sample_rate;             // Samples per second.
  int bytes_per_second;        // Average bytes per second.
  short block_align;           // Atomic audio unit size in bytes.
  short bits_per_sample;       // Sample container size.

  // Rate control values. Set the min and max values to -1 to
  // encode at an average bitrate. Use the same value for minimum, average, and
  // maximum to encode at a constant bitrate. Values are in kilobits.
  int average_bitrate;
  int minimum_bitrate;
  int maximum_bitrate;

  // TODO(fgalligan): Decide if we need these variables.
  // Advanced Vorbis encoding settings. More information about the effects and
  // usage of these settings can be found on the documentation page for the
  // libvorbis function vorbis_encode_ctl:
  // http://xiph.org/vorbis/doc/vorbisenc/vorbis_encode_ctl.html

  // Selects a quality mode based on |average_bitrate|, and disables libvorbis
  // rate control. In other words, this allows libvorbis to produce a (somewhat)
  // variable bitrate.
  // Note: The flag is ignored when minimum and maximum bitrates are not
  //       |kUseDefault| or -1.
  bool bitrate_based_quality;

  // Impulse block bias. Valid range is -15.0 to 0.0.
  double impulse_block_bias;

  // Hard-lowpass frequency. Valid range is 2 to 99.
  double lowpass_frequency;
};

}  // namespace vorbis

#endif  // LIBVORBIS_VORBIS_ENCODER_CONFIG_H_
