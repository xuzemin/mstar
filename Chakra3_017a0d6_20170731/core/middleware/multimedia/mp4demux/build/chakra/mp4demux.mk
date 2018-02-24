
CC_TVOPTS += \
        -D__CHAKRA__      \
        -DNDEBUG             \
        -DMP4_MULTI_TRACK    \
        -DMP4_MUST_HAVE_STSS \
        -DMP4DMX_HEAP_BUFFER_SIZE=50*1024 \
        -DUSE_STREAM_LIB     \
        -DNO_THREAD          \
        -DMSTAR_HEAP_EMU

MM_FILES += \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/ms_malloc.c  \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/input_protocol.c  \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/sys_common.c  \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/libstream/streaming.c  \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/libringbuf/ringbuffer_api.c  \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/atomarray.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4_read.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4atom.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4atom_read.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4extract.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4file.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4file_io.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4file_io_read.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4file_read.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4track.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4track_read.c \
    $(MIDDLE_LIB_PATH)/multimedia/mp4demux/src/mp4util.c

INC_DIR +=  \
    -I$(MIDDLE_LIB_PATH)/multimedia/mp4demux/src               \
    -I$(MIDDLE_LIB_PATH)/multimedia/mp4demux/include           \

