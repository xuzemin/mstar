////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2013 MStar Semiconductor, Inc.
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


#ifndef MP4PROPERTY_H
#define MP4PROPERTY_H

#include "mp4def.h"

struct tagATOM;
struct tagMOVATOM;

#define USE_ATOM_BUFFERRED_READ
#define ATOM_PAGE_SIZE 512
#define MP4DEMUX_BUFMODE
#define MP4DEMUX_BUFTIME
#define ATOM_CLUSTER_MAX_NUM    6
#define ATOM_CLUSTER_PAGE_NUM  1
#define ATOM_CLUSTER_PAGE_SIZE   (4096)

/* object types for AAC */
#define MAIN_AAC   1
#define LC_AAC     2
#define SSR_AAC    3
#define LTP_AAC    4
#define HE_AAC     5
#define ER_LC     17
#define ER_LTP    19
#define LD        23
#define DRM_ER_LC 27 /* special object type for DRM */

//
//  mvhd property
//
typedef struct tagmvhdprop_v0 { // for version 0
    int32_t     version_flag;
    uint32_t    creation_time;
    uint32_t    modification_time;
    uint32_t    timescale;
    uint32_t    duration;
    int32_t     rate;
    int16_t     volume;
    byte        reserved1[70];
    uint32_t   next_track_id;
} MVHDPROP_V0, *PMVHDPROP_V0;

typedef struct tagmvhdprop_v1 { // for version 1
    int32_t     version_flag;
    uint64_t    creation_time;
    uint64_t    modification_time;
    uint32_t    timescale;
    uint64_t    duration;
    int32_t     rate;
    int16_t     volume;
    byte        reserved1[70];
    uint32_t    next_track_id;
} MVHDPROP_V1, *PMVHDPROP_V1;

//
//  tkhd property
//
typedef struct tagtkhdprop_v0 {
    int32_t     version_flag;
    uint32_t    creation_time;
    uint32_t    modification_time;
    uint32_t    track_id;
    byte        reserved1[4];
    uint32_t    duration;
    byte        reserved2[12];
    uint16_t    volume;
    uint8_t     reserved3[38];
    uint32_t    width;
    uint32_t    height;
} TKHDPROP_V0, *PTKHDPROP_V0;

typedef struct tagtkhdprop_v1 {
    int32_t     version_flag;
    uint64_t    creation_time;
    uint64_t    modification_time;
    uint32_t    track_id;
    uint32_t    reserved1;
    uint64_t    duration;
    byte        reserved2[12];
    uint32_t    volume;
    byte        reserved3[2];
    int8_t      matrix[36];
    uint32_t    width;
    uint32_t    height;
} TKHDPROP_V1, *PTKHDPROP_V1;

//
//  mdhd property
//
typedef struct tagmdhdprop_v1 {
    int8_t      version;
    byte        flag[3];
    uint64_t    creation_time; // only use 32bit for v0
    uint64_t    modification_time; // only use 32bit for v0
    uint32_t    timescale;
    uint64_t    duration; // only use 32bit for v0
    uint16_t    language;
    byte        reserved[2];
} MDHDPROP_V1, *PMDHDPROP_V1;

//
//  hdlr property
//
typedef struct taghdlrprop {
    int32_t     version_flag;
    byte        reserved1[4];
    char        handler_type[5];
    byte        reserved2[12];
} HDLRPROP, *PHDLRPROP;

//
//  stts property
//
//
typedef struct tagSTTS_ENTRY {
    uint32_t    sample_count;
    uint32_t    sample_duration;
} STTS_ENTRY;

typedef struct tagsttsprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    uint32_t    *entry_sample;
    FILE_POS    sample_count_file_pos;

#ifdef USE_ATOM_BUFFERRED_READ
    uint8_t    *cache_page;
    uint32_t    page_idx;
    uint32_t    table_size;                     // cache page can not read beyond table
    uint32_t    cache_size;
#endif

    uint32_t    sample_count;   // array [], the size is entry_count
    uint32_t    sample_delta;   // array []
} STTSPROP, *PSTTSPROP;

typedef struct tagSoundSampleDesc {
    int         version;
    uint32_t    samplerate;
    uint32_t    samplesPerPacket;  // 0 if these 4 fields are not used, that is version = 0 or compressionID = -2
    uint32_t    bytesPerPacket;
    uint32_t    bytesPerFrame;
    uint32_t    bytesPerSample;
    uint16_t    channels;
    uint32_t    sampleSize; // used for PCM fixed sample size case, calculated from bits per sample and channel count
} SoundSampleDesc;

typedef struct tagVideoSampleDesc {
    int         version;
    int16_t     stream_width;
    int16_t     stream_height;
} VideoSampleDesc;
//
//  stsd property
//
typedef struct tagstsdprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    uint32_t    sample_dscription_size;
    uint32_t    data_format;
    uint8_t     decoder_cfg_len;
    void       *decoder_cfg;
    union {
        SoundSampleDesc a_desc;
        VideoSampleDesc v_desc;
    } u;
} STSDPROP, *PSTSDPROP;

//
//  ctts property
//
typedef struct tagCTTS_ENTRY {
    uint32_t    sample_count;
    int32_t    sample_offset;
} CTTS_ENTRY;

typedef struct tagcttsprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    FILE_POS    sample_count_file_pos;

#ifdef USE_ATOM_BUFFERRED_READ
    uint8_t    *cache_page;
    uint32_t    page_idx;
    uint32_t    table_size;                     // cache page can not read beyond table
    uint32_t    cache_size;
#endif

    uint32_t    sample_count;   // array [], the size is entry_count
    int32_t     sample_offset;   // array []
} CTTSPROP, *PCTTSPROP;

//
//  stsz property
//
typedef struct tagSTSZ_ENTRY {
    uint32_t sample_size;
} STSZ_ENTRY;

typedef struct tagstszprop {
    int32_t     version_flag;
    uint32_t    sample_size;
    uint32_t    sample_count;
    uint32_t    entry_array_size;
    uint32_t    *entry_size;                    // array
    FILE_POS    entry_file_pos;                 // remove malloc array to save dynamic memory space

#ifdef USE_ATOM_BUFFERRED_READ
    uint8_t    *cache_page;
    uint32_t    page_idx;
    uint32_t    table_size;                     // cache page can not read beyond table
    uint32_t    cache_size;
#endif
} STSZPROP, *PSTSZPROP;

//
//  stsc property
//
typedef struct tagSTSC_ENTRY {
    uint32_t first_chunk;
    uint32_t samples_per_chunk;
    uint32_t samples_desc_id; // size of STSC_ENTRY is used, can't remove this field
} STSC_ENTRY;

typedef struct tagstscprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    FILE_POS    entry_file_pos;

#ifdef USE_ATOM_BUFFERRED_READ
    uint8_t    *cache_page;
    uint32_t    page_idx;
    uint32_t    table_size;                     // cache page can not read beyond table
    uint32_t    cache_size;
#endif
} STSCPROP, *PSTSCPROP;

//
//  stco property
//
typedef struct tagSTCO_ENTRY {
    FILE_POS    chunk_offset_e;
} STCO_ENTRY;

typedef struct tagstcoprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    FILE_POS    entry_file_pos;
    uint32_t    entry_byte_count;
#ifdef USE_ATOM_BUFFERRED_READ
    uint8_t    *cache_page;
    uint32_t    page_idx;
    uint32_t    table_size;                     // cache page can not read beyond table
    uint32_t    cache_size;
#endif
} STCOPROP, *PSTCOPROP;

//
// stss property
//
typedef struct tagSTSS_ENTRY {
    uint32_t sync_sample_id;
} STSS_ENTRY;

typedef struct tagstssprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    uint32_t    *sync_sample;
    FILE_POS    entry_file_pos;

#ifdef USE_ATOM_BUFFERRED_READ
    uint8_t    *cache_page;
    uint32_t    page_idx;
    uint32_t    table_size;                     // cache page can not read beyond table
    uint32_t    cache_size;
#endif
} STSSPROP, *PSTSSPROP;

//
// for saving memory space, this is not used for now
//
//the default size is 64, cause we need to handle large boxes...
#define ISOM_BOX            \
    uint32_t type;          \
    uint64_t size;          \

//
// for saving memory space, this is not used for now
//
#define ISOM_SAMPLE_ENTRY_FIELDS        \
    ISOM_BOX                            \
    uint16_t dataReferenceIndex;        \
    char reserved[ 6 ];

//
// for saving memory space, this is not used for now
//
#define ISOM_VISUAL_SAMPLE_ENTRY        \
    ISOM_SAMPLE_ENTRY_FIELDS            \
    uint16_t version;                   \
    uint16_t revision;                  \
    uint32_t vendor;                    \
    uint32_t temporal_quality;          \
    uint32_t spacial_quality;           \
    uint16_t Width, Height;             \
    uint32_t horiz_res, vert_res;       \
    uint32_t entry_data_size;           \
    uint16_t frames_per_sample;         \
    unsigned char compressor_name[33];  \
    uint16_t bit_depth;                 \
    int16_t color_table_index;

//
// for saving memory space, this is not used for now
//
#define ISOM_AUDIO_SAMPLE_ENTRY     \
    ISOM_SAMPLE_ENTRY_FIELDS        \
    uint16_t version;               \
    uint16_t revision;              \
    uint32_t vendor;                \
    uint16_t channel_count;         \
    uint16_t bitspersample;         \
    uint16_t compression_id;        \
    uint16_t packet_size;           \
    uint16_t samplerate_hi;         \
    uint16_t samplerate_lo;

//
// esds property(Elementary stream descriptor)
// You have to parse tag to decide the type of descriptor
typedef struct {
    uint32_t version_flag;

    /* 0x03 ESDescrTag */
    uint16_t es_id;

#define MP4_O_DESCR_TAG                     0x01
#define MP4_IO_DESCR_TAG                    0x02
#define MP4_ES_DESCR_TAG                    0x03
#define MP4_DEC_CONFIG_DESCR_TAG            0x04
#define MP4_DEC_SPECIFIC_DESCR_TAG          0x05
#define MP4_SL_CONFIG_DESCR_TAG             0x06
#define MP4_CONTENT_ID_DESCR_TAG            0x07
#define MP4_SUPPL_CONTENT_ID_DESCR_TAG      0x08
#define MP4_IP_IPTR_DESCR_TAG               0x09
#define MP4_IP_MPPTR_DESCR_TAG              0x0A
#define MP4_IP_MP_DESCR_TAG                 0x0B
#define MP4_REGISTRATION_DESCR_TAG          0x0D
#define MP4_ES_IDINC_DESCR_TAG              0x0E
#define MP4_ES_IDREF_DESCR_TAG              0x0F
#define MP4_FILE_IOD_TAG                    0x10
#define MP4_FILE_OD_TAG                     0x11
#define MP4_EXT_PROFILE_LEVEL_DESCR_TAG     0x13
#define MP4_EXT_DESCR_TAGS_START            0x80
#define MP4_EXT_DESCR_TAGS_END              0xFE

#define MP4_STREAM_TYPE_VISUAL          0x04
#define MP4_STREAM_TYPE_AUDIO           0x05
#define MP4_STREAM_TYPE_NERO_SUBPIC     0x38

#define MP4_OBJECT_TYPE_ID_ISO14496_2   0x20
#define MP4_OBJECT_TYPE_ID_ISO14496_3   0x40
#define MP4_OBJECT_TYPE_ID_ISO11172_2   0x6A
#define MP4_OBJECT_TYPE_ID_ISO11172_3   0x6B
#define MP4_OBJECT_TYPE_ID_ISO13818_2_SP 0x60
#define MP4_OBJECT_TYPE_ID_ISO13818_2_MP 0x61
#define MP4_OBJECT_TYPE_ID_ISO13818_7_MP 0x66
#define MP4_OBJECT_TYPE_ID_ISO13818_7_LC 0x67

/* Codec type in object_type_id */
#define MP4_OBJECT_TYPE_M4V                MP4_OBJECT_TYPE_ID_ISO14496_2
#define MP4_OBJECT_TYPE_AAC                MP4_OBJECT_TYPE_ID_ISO14496_3
#define MP4_OBJECT_TYPE_MP3                MP4_OBJECT_TYPE_ID_ISO11172_3
#define MP4_OBJECT_TYPE_MP2                0x69
#define MP4_OBJECT_TYPE_VORBIS             0xDD /* qpac use it */

    uint8_t  stream_priority;

    /* 0x04 DecConfigDescrTag */
    uint8_t  object_type_id;
#define MP4Visual14496_2Object      0x20
#define MP4Audio14496_3Object       0x40
    uint8_t  stream_type;
    union
    {
        struct {
            uint8_t reserved : 1;
            uint8_t  up_stream : 1;
            uint8_t  stream_type : 6;
        }esds_dcd_bits;
        uint16_t esds_dcd_8;
    } esds_dcd;
#define MP4VisualStream                 0x04
#define MP4AudioStream                  0x05
    /* XXX: really streamType is
     * only 6bit, followed by:
     * 1bit  upStream
     * 1bit  reserved
     */
    uint32_t buffer_size_db; // 24
    uint32_t max_bitrate;
    uint32_t avg_bitrate;

    /* 0x05 DecSpecificDescrTag */
    uint32_t  decoder_cfg_len;
    uint8_t *decoder_cfg;

    /* 0x06 SLConfigDescrTag */
    uint8_t  sl_config_len;
    uint8_t *sl_config;

    //nal_unit_size, used by hevc
    uint8_t nal_unit_size;
} MP4AV_ESDS;

typedef struct
{
    //uint8_t configurationVersion;
    //uint8_t AVCProfileIndication;
    //uint8_t profile_compatibility;
    //uint8_t AVCLevelIndication;
    uint8_t nal_unit_size;

    uint8_t  decoder_cfg_len;
    uint8_t *decoder_cfg;
} AVCConfig, AVSConfig, HEVCConfig;

//
// for saving memory space, this is not used for now
//
typedef struct
{
    ISOM_VISUAL_SAMPLE_ENTRY
    MP4AV_ESDS *esds;
} MP4VPROP, *PMP4VPROP;

//
//  samr property
//
typedef struct tagsamrprop {
    byte        reserved1[6];
    uint16_t    dataReferenceIndex;
    byte        reserved2[16];
    uint16_t    timescale;
    byte        reserved3[2];
} SAMRPROP, *PSAMRPORP;

//
//  damr property
//
typedef struct tagdamrprop {
    uint32_t    vendor;
    uint8_t     decoderVersion;
    uint16_t    modeSet;
    uint8_t     modeChangePeriod;
    uint8_t     framesPerSample;
} DAMRPROP, *PDAMRPROP;

//
//  s263 property
//
typedef struct tags263prop {
    byte        reserved1[6];
    uint16_t    dataReferenceIndex;
    byte        reserved2[16];
    uint16_t    width;
    uint16_t    height;
    byte        reserved3[50];
} S263PROP, *P263PROP;

typedef struct tags263prop VIDEPROP;
typedef struct tags263prop *PVIDEPROP;

//
//  d263 property
//
typedef struct tagd263prop {
    uint32_t    vendor;
    uint8_t     decoderVersion;
    uint8_t     h263Level;
    uint8_t     h263Profile;
} D263PROP, *PD263PROP;

typedef struct tagmstrprop {
    uint8_t     mace;
} MSTRPROP;

typedef struct tagwfexprop {
    uint8_t     *data;
    int         len;
} WFEXPROP;

typedef struct tagwaveprop {
    uint32_t    type;
    union {
        MP4AV_ESDS  esds;
        WFEXPROP    wfex;
    } u;
} WAVEPROP;

#endif /* MP4PROPERTY_H */
