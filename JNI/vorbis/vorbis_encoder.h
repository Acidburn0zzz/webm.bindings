#ifndef LIBVORBIS_VORBIS_ENCODER_H_
#define LIBVORBIS_VORBIS_ENCODER_H_

#include "vorbis/codec.h"

#include "vorbis_encoder_config.h"

namespace vorbis {

// Libvorbis wrapper class providing a simplified interface to the Vorbis
// encoding library.
class VorbisEncoder {
 public:
  VorbisEncoder();
  ~VorbisEncoder();

  // Initializes libvorbis.
  bool Init(const VorbisEncoderConfig& config);

  // Passes the samples in |buffer| to libvorbis. Returns true after
  // successful copy of samples to the encoder.
  bool Encode(const unsigned char* buffer, int length);

  // Returns Vorbis audio samples via |data| when libvorbis is able to
  // provide compressed data. Returns length in bytes of |data| in |length|.
  // Returns the starting time in timebase units in |timestamp|. Returns false
  // when libvorbis has no data ready.
  bool ReadCompressedAudio(unsigned char** data, int* length,
                           int64_t* timestamp);

  // Returns CodecPrivate data for WebM files. Must be called after Init().
  int codec_private_length() const { return codec_private_length_; }
  const unsigned char* codec_private() const { return codec_private_; }

  // Default timesbase is samples per second.
  int64_t timebase_numerator() const { return timebase_numerator_; }
  int64_t timebase_denominator() const { return timebase_denominator_; }

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

  bool timebase_set_;
  int64_t timebase_numerator_;
  int64_t timebase_denominator_;

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

  // Converts |num_samples| to timebase.
  int64_t SamplesToTimebase(int64_t num_samples) const;
};

}  // namespace vorbis

#endif  // LIBVORBIS_VORBIS_ENCODER_H_
