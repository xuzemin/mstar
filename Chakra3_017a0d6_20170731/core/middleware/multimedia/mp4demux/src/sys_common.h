////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2013 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef SYS_COMMON_H
#define SYS_COMMON_H

#include <assert.h>
#include "mvc_demuxer.h"
#include "streaming.h"
#include "ms_drmkey.h"

/* demuxer common internal definitions */

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#define ATTR_PACK __attribute__ ((packed))
#define ATTR_UNUSED __attribute__((unused))
#else
#define ATTR_PACK
#define ATTR_UNUSED
#endif

/* maximum length for decoder specific configuration data */
#define MAX_CONFIG_LEN   (1024)

/* maximum length for trying to resync header */
#define MAX_RESYNC_SIZE  (1024 * 1024)

/* maximum PTS difference between consecutive frames (unit: us) */
#define MAX_PTS_DIFF     INT64_C(10000000)

/* macro for pointer alignment, n must be power of 2 */
#define ALIGN_PTR(p, n)  ((void *) (((intptr_t) (p) + ((n) - 1)) & -(n)))

/* min/max macros */
#define SYS_MIN(a, b)    ((a) < (b) ?  (a) : (b))
#define SYS_MAX(a, b)    ((a) > (b) ?  (a) : (b))
#define SYS_ABS(a)       ((a) <  0  ? -(a) : (a))

#define SYS_FCC(a, b, c, d) (((uint8_t) (a) << 24) | ((uint8_t) (b) << 16) | \
                             ((uint8_t) (c) <<  8) | ((uint8_t) (d)))

#define READ_BE16(a)     (uint32_t)((((uint8_t *) (a))[0] <<  8) | ((uint8_t *) (a))[1])
#define READ_BE32(a)     (uint32_t)((((uint8_t *) (a))[0] << 24) | (((uint8_t *) (a))[1] << 16) | \
                          (((uint8_t *) (a))[2] <<  8) | (((uint8_t *) (a))[3]))
#define READ_LE32(a)     (uint32_t)((((uint8_t *) (a))[3] << 24) | (((uint8_t *) (a))[2] << 16) | \
                          (((uint8_t *) (a))[1] <<  8) | (((uint8_t *) (a))[0]))
#define BE32_TO_NE32(a)  READ_BE32(a)
#define LE32_TO_NE32(a)  (a)

#define CONFORM_ASSERT(expr)   assert(expr)
/* demuxer common internal structures */

enum sys_stream_type_e
{
    AUD,
    VID,
    SUB,
    OTH,
};

typedef struct sys_aud_inf_s
{
    uint32_t            sample_rate;
    uint32_t            sample_size;
    uint32_t            bit_rate;
    uint32_t            ch_num;
    uint32_t            sample_depth;
} sys_aud_inf_st;

typedef struct sys_vid_inf_s
{
    uint16_t            width;
    uint16_t            height;
} sys_vid_inf_st;

typedef struct sys_stream_s
{
    mvc_stream_type_et  stream_type;
    int                 codec_type;
    uint8_t            *config;
    uint32_t            config_len;
    int                 config_sent;
    cb_fpos             next_pos;
    union
    {
        sys_aud_inf_st  aud;
        sys_vid_inf_st  vid;
    } info;
} sys_stream_st;

typedef struct sys_demuxer_s
{
    int64_t             duration;
    int                 seekable;
    int                 streaming;
    int                 total_streams;
    int                 num_streams[OTH + 1];
    int                 active_stream[SUB + 1];
    cb_buffer_st        cbuffer;
    mvc_callback_st     callback;
    mvc_drop_level_et   drop_level;
    int                 drop_ratio_num;
    int                 drop_ratio_den;
    int                 drop_index;
    int64_t             last_pts[SUB + 1];
    int64_t             last_dur[SUB + 1];
    int64_t             seek_time;
} sys_demuxer_st;

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

typedef struct guid_s
{
    uint32_t            data1;
    uint16_t            data2;
    uint16_t            data3;
    uint8_t             data4[8];
} ATTR_PACK guid_st;

typedef struct aac_parameter_s
{
    int object_type;
    int sample_rate;
    int channels;
    int sbr;
    int ext_object_type;
    int ext_sample_rate;
} aac_parameter_st;

/* BITMAPINFOHEADER structure */
typedef struct msft_video_header_s
{
    uint32_t            size;
    int32_t             width;
    int32_t             height;
    uint16_t            planes;
    uint16_t            bit_count;
    uint32_t            compression;
    uint32_t            size_image;
    int32_t             pel_per_meter_x;
    int32_t             pel_per_meter_y;
    uint32_t            color_used;
    uint32_t            color_required;
} ATTR_PACK msft_video_header_st;

// see <mmreg.h> for more format definition
enum msft_audio_format_e
{
    MSFT_AUDIO_PCM          = 1,
    MSFT_AUDIO_MS_ADPCM     = 2,
    MSFT_AUDIO_ALAW         = 6,
    MSFT_AUDIO_MULAW        = 7,
    MSFT_AUDIO_IMA_ADPCM_MS = 0x11,  // Microsoft IMA-ADPCM
    MSFT_AUDIO_MPG          = 0x50,
    MSFT_AUDIO_MP3          = 0x55,
    MSFT_AUDIO_AC3_SPDIF    = 0x92,
    MSFT_AUDIO_AMR          = 0xFE,
    MSFT_AUDIO_AAC          = 0xFF,
    MSFT_AUDIO_WMA1         = 0x160,
    MSFT_AUDIO_WMA2         = 0x161,
    MSFT_AUDIO_WMA3         = 0x162,
    MSFT_AUDIO_AC3          = 0x2000,
    MSFT_AUDIO_DTS          = 0x2001,
    MSFT_AUDIO_VORBIS       = 0x566f, // not official ID, it is 'V'<<8 + 'o' according to FFMPEG
    MSFT_AUDIO_FAAC         = 0x706D,
    MSFT_AUDIO_EXTENSIBLE   = 0xFFFE,
};

/* MStar proprietary extension */
#define MSTAR_AUDIO_PCM_U_LE        0x7653  /* unsigned, little endian format */
#define MSTAR_AUDIO_PCM_U_BE        0x7654  /* unsigned,    big endian format */
#define MSTAR_AUDIO_PCM_S_LE        0x7655  /*   signed, little endian format */
#define MSTAR_AUDIO_PCM_S_BE        0x7656  /*   signed,    big endian format */
#define MSTAR_AUDIO_IMA_ADPCM_QT    0x7657  // Quick time IMA-ADPCM

/* WAVEFORMATEX structure (without cbSize) */
typedef struct msft_audio_header_s
{
    uint16_t            format_tag;
    uint16_t            channels;
    uint32_t            sample_rate;
    uint32_t            bit_rate;
    uint16_t            block_align;
    uint16_t            sample_depth;
} ATTR_PACK msft_audio_header_st;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

int sys_is_equal_guid(const guid_st *g1, const guid_st *g2);
MVCAudioType sys_msft_format_tag_to_acodec(int format_tag);
MVCVideoType sys_msft_fourcc_to_vcodec(uint32_t fourcc);
int sys_msft_parse_audio_header(sys_demuxer_st *d, sys_stream_st *s, uint32_t *size);
int sys_msft_parse_video_header(sys_demuxer_st *d, sys_stream_st *s, uint32_t *size, uint32_t *fourcc);

int sys_notify(sys_demuxer_st *d, mvc_stream_type_et type, mvc_event_et event);
void *sys_malloc(sys_demuxer_st *d, size_t size);
void sys_freep(sys_demuxer_st *d, void **p);

int sys_stream_alloc(sys_demuxer_st *d, mvc_stream_type_et type, void **buffer, int size);
int sys_stream_discard(sys_demuxer_st *d, mvc_stream_type_et type);
int sys_stream_commit(sys_demuxer_st *d, mvc_stream_type_et type, int size, int64_t pts, int64_t duration, int packet_type);
int sys_stream_realloc(sys_demuxer_st *d, mvc_stream_type_et type, void **buffer, int size);
int sys_stream_send_config(sys_demuxer_st *d, sys_stream_st *s);

int sys_is_codec_PCM(sys_stream_st *s);
void sys_update_aac_config(sys_demuxer_st *d, uint8_t **config, uint32_t *config_len, aac_parameter_st *aac_par);

int sys_check_drm(MMP_KEY_e type);
/**
 * Check if current position is larger than drop target. Reset drop target if current position is larger than it
 * @param[in] d demuxer common instance
 * @param[in] s stream common instance
 * @retval 1 current frame shall be dropped
 * @retval 0 current frame shall be keeped
 */
int sys_check_drop(sys_demuxer_st *d, sys_stream_st *s);
/**
 * Set position for designated stream, all frame prior to that position shall be judged as dropped by sys_check_drop()
 * @param[in] target_type specified type whose drop target will be disabled
 * @param[in] s stream common instance
 * @param[in] current_pos drop target for this stream
 */
void sys_set_drop_target(mvc_stream_type_et target_type, sys_stream_st *s, cb_fpos current_pos);
/**
 * Disable drop for designated stream. Used between first read and seek
 * @param[in] s stream common instance
 */
void sys_reset_drop_target(sys_stream_st *s);

void sys_set_info_from_string(mvc_data_info_st *info, char *string);
char *sys_alpha2_to_alpha3(const char *in);
int sys_get_cur_stream_num(sys_demuxer_st *d);
// for pts info
void sys_set_pts_info(sys_demuxer_st *d, int64_t seek_time);
void sys_update_and_fix_pts_gap(sys_demuxer_st *d, int64_t *pts, mvc_stream_type_et type);

#endif /* SYS_COMMON_H */
