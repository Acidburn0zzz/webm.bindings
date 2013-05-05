#include "vorbis_encoder.h"

#include <string.h>

#include "vorbis/vorbisenc.h"

#ifdef NDEBUG
# define printf(fmt, ...)
#else
# ifdef __ANDROID__
#  include <android/log.h>
#  define printf(fmt, ...) \
   __android_log_print(ANDROID_LOG_DEBUG, "VORBIS_ENC", fmt, ##__VA_ARGS__)
# else
#  define printf(fmt, ...) \
   printf(fmt "\n", ##__VA_ARGS__)
# endif
#endif

namespace vorbis {

VorbisEncoder::VorbisEncoder()
    : codec_private_length_(0),
      codec_private_(NULL),
      last_granulepos_(0),
      data_(NULL),
      data_size_(0),
      data_capacity_(2048) {
  memset(&ident_packet_, 0, sizeof(ident_packet_));
  memset(&comments_packet_, 0, sizeof(comments_packet_));
  memset(&setup_packet_, 0, sizeof(setup_packet_));
}

VorbisEncoder::~VorbisEncoder() {
  delete [] codec_private_;
  delete [] data_;
}

bool VorbisEncoder::Init(const VorbisEncoderConfig& config) {
  config_ = config;

  if (config_.channels <= 0 || config_.channels > 2)
    return false;

  if (config_.format_tag != kAudioFormatPcm)
    return false;

  if (config_.format_tag == kAudioFormatPcm && config_.bits_per_sample != 16)
    return false;

  vorbis_info_init(&vi_);
  int status = vorbis_encode_setup_managed(&vi_, config_.channels,
                                           config_.sample_rate,
                                           config_.minimum_bitrate,
                                           config_.average_bitrate,
                                           config_.maximum_bitrate);
  if (status != 0)
    return false;

  if (config_.minimum_bitrate == -1 && config_.maximum_bitrate == -1  &&
      config_.bitrate_based_quality) {
    // Enable VBR.
    if (!CodecControlSet(OV_ECTL_RATEMANAGE2_SET, 0)) {
      return false;
    }
  }

  status = vorbis_encode_setup_init(&vi_);
  if (status != 0)
    return false;

  status = vorbis_analysis_init(&dsp_state_, &vi_);
  if (status != 0)
    return false;

  status = vorbis_block_init(&dsp_state_, &block_);
  if (status != 0)
    return false;

  if (!GenerateHeaders())
    return false;

  if (!GenerateCodecPrivate())
    return false;

  data_ = new unsigned char[data_capacity_];
  return true;
}

bool VorbisEncoder::Encode(const unsigned char* buffer, int length) {
  if (!buffer || length <= 0) {
    //LOG(ERROR) << "cannot Encode empty input buffer!";
    return false;
  }

  const int channels = config_.channels;
  const int num_blocks = length / config_.block_align;

  float** const ptr_encoder_buffer = vorbis_analysis_buffer(&dsp_state_,
                                                            num_blocks);
  if (!ptr_encoder_buffer) {
    printf("cannot EncodeBuffer, no memory from libvorbis.");
    return false;
  }

  const short* const s16_pcm_samples = reinterpret_cast<const short*>(buffer);
  for (int i = 0; i < num_blocks; ++i) {
    for (int c = 0; c < channels; ++c) {
      ptr_encoder_buffer[c][i] = s16_pcm_samples[i * channels + c] / 32768.f;
    }
  }

  vorbis_analysis_wrote(&dsp_state_, num_blocks);
  return true;
}

bool VorbisEncoder::ReadCompressedAudio(unsigned char** data, int* length,
                                        int64_t* timestamp) {
  if (!data || !length || !timestamp)
    return false;

  *timestamp = SamplesToMilliseconds(last_granulepos_);

  ogg_packet packet = { 0 };
  while (SamplesAvailable()) {
    // There's a compressed block available-- give libvorbis a chance to
    // optimize distribution of data for the current encode settings.
    int status = vorbis_analysis(&block_, &packet);
    if (status) {
      printf("vorbis_analysis failed status:%d", status);
      return false;
    }
    status = vorbis_bitrate_addblock(&block_);
    if (status) {
      printf("vorbis_bitrate_addblock failed status:%d", status);
      return false;
    }
    while ((status = vorbis_bitrate_flushpacket(&dsp_state_, &packet)) == 1) {
      if (packet.granulepos > 0) {
        if (data_size_ + packet.bytes > data_capacity_) {
          data_capacity_ = data_size_ + packet.bytes + 1024;
          unsigned char* temp = new unsigned char[data_capacity_];
          memcpy(temp, data_, data_size_);
          delete [] data_;
          data_ = temp;
        }
        memcpy(data_ + data_size_, packet.packet, packet.bytes);
        data_size_ += packet.bytes;
        last_granulepos_ = packet.granulepos;
      }
    }
  }

  if (data_size_ == 0)
    return false;

  unsigned char* local_data = new unsigned char[data_size_];
  memcpy(local_data, data_, data_size_);
  *data = local_data;
  *length = data_size_;
  data_size_ = 0;
  return true;
}

bool VorbisEncoder::CodecControlSet(int control_id, int val) {
  int status = 0;
  if (control_id == OV_ECTL_RATEMANAGE2_SET && val == 0) {
    // Special case disabling rate control-- libvorbis expects a NULL
    // pointer.
    status = vorbis_encode_ctl(&vi_, control_id, NULL);
  } else {
    status = vorbis_encode_ctl(&vi_, control_id, reinterpret_cast<void*>(val));
  }
  if (status != 0)
    return false;
  return true;
}

bool VorbisEncoder::GenerateHeaders() {
  vorbis_comment comments = { 0 };
  vorbis_comment_init(&comments);

  // Add app name and version to vorbis comments.
  vorbis_comment_add_tag(&comments, "WebM JNI bindings", "encoder");

  // Generate the vorbis header packets.
  const int status = vorbis_analysis_headerout(&dsp_state_,
                                               &comments,
                                               &ident_packet_,
                                               &comments_packet_,
                                               &setup_packet_);
  if (status) {
    printf("vorbis_analysis_headerout failed status:%d", status);
    return false;
  }
  return true;
}

bool VorbisEncoder::GenerateCodecPrivate() {
  if (codec_private_length_ > 0 && codec_private_ != NULL)
    return false;

  // Perform minimal private data validation.
  if (ident_packet_.packet == NULL || comments_packet_.packet == NULL ||
      setup_packet_.packet == NULL)
    return false;

  if (ident_packet_.bytes > 255 || comments_packet_.bytes > 255)
    return false;

  const int data_length = ident_packet_.bytes + comments_packet_.bytes +
                          setup_packet_.bytes;

  // Calculate total bytes of storage required for the private data chunk.
  // 1 byte to store header count (total headers - 1 = 2).
  // 1 byte each for ident and comment length values.
  // The length of setup data is implied by the total length.
  codec_private_length_ = 1 + 1 + 1 + data_length;
  codec_private_ = new unsigned char[codec_private_length_];

  // Write header count. As above, number of headers - 1.
  int off = 0;
  codec_private_[off++] = 2;

  // Write ident length, comment length.
  codec_private_[off++] = ident_packet_.bytes;
  codec_private_[off++] = comments_packet_.bytes;

  // Write the data blocks.
  memcpy(codec_private_ + off, ident_packet_.packet, ident_packet_.bytes);
  off += ident_packet_.bytes;

  memcpy(codec_private_ + off, comments_packet_.packet, comments_packet_.bytes);
  off += comments_packet_.bytes;

  memcpy(codec_private_ + off, setup_packet_.packet, setup_packet_.bytes);
  return true;
}

bool VorbisEncoder::SamplesAvailable() {
  const int kSamplesAvailable = 1;
  if (vorbis_analysis_blockout(&dsp_state_, &block_) == kSamplesAvailable)
    return true;
  return false;
}

int64_t VorbisEncoder::SamplesToMilliseconds(int64_t num_samples) const {
  const double sample_rate = config_.sample_rate;
  const double sample_count = static_cast<double>(num_samples);
  double seconds = 0;
  if (sample_rate != 0)
    seconds = sample_count / sample_rate;
  return static_cast<int64_t>(seconds * 1000);
}

}  // namespace vorbis
