# Build libwebm.a
include $(CLEAR_VARS)

include $(BINDINGS_DIR)/libwebm/Android.mk

#Build libwebmJNI.so
include $(CLEAR_VARS)
LOCAL_PATH := $(BINDINGS_DIR)/webm
LOCAL_MODULE    := webmJNI

LOCAL_C_INCLUDES := $(BINDINGS_DIR)/libwebm \
                    $(BINDINGS_DIR)/webm \
                    $(BINDINGS_DIR)/webm/mkvmuxer \
                    $(BINDINGS_DIR)/webm/mkvparser

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := common.cc \
                   mkvmuxer/AudioTrack.cc \
                   mkvmuxer/Chapter.cc \
                   mkvmuxer/Chapters.cc \
                   mkvmuxer/Cluster.cc \
                   mkvmuxer/ContentEncAESSettings.cc \
                   mkvmuxer/ContentEncoding.cc \
                   mkvmuxer/CuePoint.cc \
                   mkvmuxer/Cues.cc \
                   mkvmuxer/Frame.cc \
                   mkvmuxer/IMkvWriter.cc \
                   mkvmuxer/MkvWriter.cc \
                   mkvmuxer/SeekHead.cc \
                   mkvmuxer/Segment.cc \
                   mkvmuxer/SegmentInfo.cc \
                   mkvmuxer/Track.cc \
                   mkvmuxer/Tracks.cc \
                   mkvmuxer/VideoTrack.cc \
                   mkvmuxer/mkvmuxer.cc \
                   mkvmuxer/mkvmuxerutil.cc \
                   mkvparser/Atom.cc \
                   mkvparser/AudioTrack.cc \
                   mkvparser/Block.cc \
                   mkvparser/BlockEntry.cc \
                   mkvparser/BlockGroup.cc \
                   mkvparser/Chapters.cc \
                   mkvparser/Cluster.cc \
                   mkvparser/ContentCompression.cc \
                   mkvparser/ContentEncAESSettings.cc \
                   mkvparser/ContentEncoding.cc \
                   mkvparser/ContentEncryption.cc \
                   mkvparser/CuePoint.cc \
                   mkvparser/Cues.cc \
                   mkvparser/Display.cc \
                   mkvparser/EBMLHeader.cc \
                   mkvparser/Edition.cc \
                   mkvparser/Entry.cc \
                   mkvparser/Frame.cc \
                   mkvparser/IMkvReader.cc \
                   mkvparser/Info.cc \
                   mkvparser/MkvReader.cc \
                   mkvparser/SeekHead.cc \
                   mkvparser/Segment.cc \
                   mkvparser/SegmentInfo.cc \
                   mkvparser/Settings.cc \
                   mkvparser/SimpleBlock.cc \
                   mkvparser/Track.cc \
                   mkvparser/TrackPosition.cc \
                   mkvparser/Tracks.cc \
                   mkvparser/VideoTrack.cc \
                   mkvparser/VoidElement.cc \
                   mkvparser/mkvparser.cc

LOCAL_STATIC_LIBRARIES := libwebm

include $(BUILD_SHARED_LIBRARY)

# Build libogg.a
include $(CLEAR_VARS)
LOCAL_PATH := $(BINDINGS_DIR)/libogg-1.3.0/src
LOCAL_MODULE    := libogg
LOCAL_C_INCLUDES := $(BINDINGS_DIR)/libogg-1.3.0/include
LOCAL_CFLAGS := -DHAVE_CONFIG
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := bitwise.c \
                   framing.c

include $(BUILD_STATIC_LIBRARY)

# Build liboggJNI.so
include $(CLEAR_VARS)
LOCAL_PATH := $(BINDINGS_DIR)/ogg
LOCAL_MODULE    := oggJNI
LOCAL_C_INCLUDES := $(BINDINGS_DIR)/libogg-1.3.0/include
LOCAL_CFLAGS := -DHAVE_CONFIG
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := common.cc \
                   OggpackBuffer.cc \
                   OggPacket.cc

LOCAL_STATIC_LIBRARIES := libogg

include $(BUILD_SHARED_LIBRARY)

# Build libvorbis.a
include $(CLEAR_VARS)
LOCAL_PATH := $(BINDINGS_DIR)/libvorbis-1.3.3/lib
LOCAL_MODULE    := libvorbis
LOCAL_C_INCLUDES := $(BINDINGS_DIR)/libvorbis-1.3.3/include \
                    $(BINDINGS_DIR)/libogg-1.3.0/include
LOCAL_CFLAGS := -DHAVE_CONFIG
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := analysis.c \
                   bitrate.c \
                   block.c \
                   codebook.c \
                   envelope.c \
                   floor0.c \
                   floor1.c \
                   info.c \
                   lookup.c \
                   lpc.c \
                   lsp.c \
                   mapping0.c \
                   mdct.c \
                   psy.c \
                   registry.c \
                   res0.c \
                   sharedbook.c \
                   smallft.c \
                   synthesis.c \
                   vorbisenc.c \
                   vorbisfile.c \
                   window.c

LOCAL_STATIC_LIBRARIES := libogg

include $(BUILD_STATIC_LIBRARY)

# Build libvorbisJNI.so
include $(CLEAR_VARS)
LOCAL_PATH := $(BINDINGS_DIR)/vorbis

LOCAL_MODULE    := vorbisJNI
LOCAL_C_INCLUDES := $(BINDINGS_DIR)/libvorbis-1.3.3/include \
                    $(BINDINGS_DIR)/libogg-1.3.0/include
LOCAL_CFLAGS := -DHAVE_CONFIG
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := AllocChain.cc \
                   codec.cc \
                   common.cc \
                   vorbis_encoder.cc \
                   VorbisBlock.cc \
                   VorbisComment.cc \
                   VorbisDspState.cc \
                   vorbisenc.cc \
                   VorbisEncoder.cc \
                   VorbisInfo.cc

LOCAL_LDLIBS := -llog
LOCAL_STATIC_LIBRARIES := libvorbis

include $(BUILD_SHARED_LIBRARY)


# Build libvpx.so
include $(CLEAR_VARS)

# TODO(fgalligan): Change the build dir after libvpx can be built under JNI.
# For now libvpx must be built under <project>/jni.
#LOCAL_PATH := $(BINDINGS_DIR)/
#include $(BINDINGS_DIR)/libvpx/build/make/Android.mk
LOCAL_PATH := $(WORKING_DIR)
include $(WORKING_DIR)/libvpx/build/make/Android.mk


# Build libvpxJNI.so
include $(CLEAR_VARS)
LOCAL_PATH := $(BINDINGS_DIR)/vpx

LOCAL_MODULE    := vpxJNI

LOCAL_ARM_MODE := arm

# TODO(fgalligan) Change the include dirs after libvpx can be built under JNI.
#LOCAL_C_INCLUDES := webm.bindings/JNI/libvpx \
#                    webm.bindings/JNI/libvpx/vpx_ports \
#                    webm.bindings/JNI
LOCAL_C_INCLUDES := $(WORKING_DIR)/libvpx \
                    $(WORKING_DIR)/libvpx/vpx_ports \
                    $(WORKING_DIR)

LOCAL_SRC_FILES := libvpx_com_impl.cc \
                   libvpx_dec_impl.cc \
                   libvpx_enc_config_impl.cc \
                   libvpx_enc_impl.cc
                   #webm.bindings/JNI/vpx/libvpx_webm_muxer_impl.cc

LOCAL_LDLIBS := -llog
LOCAL_SHARED_LIBRARIES := libvpx

include $(BUILD_SHARED_LIBRARY)
