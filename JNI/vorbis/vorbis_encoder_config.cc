#include "vorbis_encoder_config.h"

namespace vorbis {

VorbisEncoderConfig::VorbisEncoderConfig()
    : format_tag(kAudioFormatPcm),
      channels(2),
      sample_rate(44100),
      bytes_per_second(176400),
      block_align(4),
      bits_per_sample(16),
      timebase_numerator_(-1),
      timebase_denominator_(-1),
      average_bitrate(64000),
      minimum_bitrate(-1),
      maximum_bitrate(-1),
      bitrate_based_quality(true),
      impulse_block_bias(-7.5),
      lowpass_frequency(50.0) {
}

}  // namespace vorbis
