#ifndef LIBVORBIS_VORBIS_ENCODER_H_
#define LIBVORBIS_VORBIS_ENCODER_H_

#include "vorbis/codec.h"

namespace vorbis {

static const int kAudioFormatPcm = 1;

struct VorbisEncoderConfig {
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

// Libvorbis wrapper class providing a simplified interface to the Vorbis
// encoding library.
class VorbisEncoder {
 public:
  VorbisEncoder();
  ~VorbisEncoder();

  // Initializes libvorbis.
  bool Init();

  // Passes the samples in |buffer| to libvorbis. Returns true after
  // successful handoff of samples to the encoder.
  bool Encode(const unsigned char* buffer, int length);

  // Returns Vorbis audio samples via |data| when libvorbis is able to
  // provide compressed data. Returns length in bytes of |data| in |length|.
  // Returns the starting time in milliseconds in |timestamp|. Returns false
  // when libvorbis has no data ready.
  bool ReadCompressedAudio(unsigned char** data, int* length,
                           int64_t* timestamp);

  // Functions that get the characteristics of the input audio.
  int GetChannels() const;
  int GetSampleRate() const;
  int GetBitsPerSample() const;

  // Functions that get the characteristics of the Vorbis encoder.
  int GetAverageBitrate() const;
  int GetMinimumBitrate() const;
  int GetMaximumBitrate() const;

  // Functions that set the characteristics of the input audio. Must be called
  // before Init().
  void SetChannels(int channels);
  void SetSampleRate(int sample_rate);
  void SetBitsPerSample(int bits_per_sample);

  // Functions that set the characteristics of the Vorbis encoder. Must be
  // called before Init().
  void SetAverageBitrate(int bitrate);
  void SetMinimumBitrate(int bitrate);
  void SetMaximumBitrate(int bitrate);

  // Returns CodecPrivate data for WebM files. Must be called after Init().
  int codec_private_length() const { return codec_private_length_; }
  const unsigned char* codec_private() const { return codec_private_; }

 private:
  VorbisEncoderConfig config_;

  vorbis_info vi_;
  vorbis_dsp_state dsp_state_;
  vorbis_block block_;

  ogg_packet ident_packet_;
  ogg_packet comments_packet_;
  ogg_packet setup_packet_;

  int codec_private_length_;
  unsigned char* codec_private_;

  int64_t last_granulepos_;

  unsigned char* data_;
  int data_size_;
  int data_capacity_;

  bool CodecControlSet(int control_id, int val);

  // Creates the Vorbis headers used to generate the WebM CodecPrivate
  // element.
  bool GenerateHeaders();

  // Creates CodecPrivate data for WebM files.
  bool GenerateCodecPrivate();

  // Returns true when libvorbis has compressed samples available.
  bool SamplesAvailable();

  // Converts |num_samples| to milliseconds.
  int64_t SamplesToMilliseconds(int64_t num_samples) const;
};

}  // namespace vorbis

#endif  // LIBVORBIS_VORBIS_ENCODER_H_
