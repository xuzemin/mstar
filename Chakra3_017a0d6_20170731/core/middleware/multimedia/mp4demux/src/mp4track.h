////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2012 MStar Semiconductor, Inc.
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


#ifndef MP4TRACK_H
#define MP4TRACK_H

#include "mp4def.h"
#include "mp4property.h"
#include "mvc_demuxer.h"
#include "sys_common.h"

#define MP4TRACK_SEEK_NO_KEYFRAME    0

struct tagMP4File;
struct tagATOM;
struct tagMP4Property;

typedef uint32_t MP4ChunkId;

typedef struct dvds_config_s
{
    uint32_t width;
    uint32_t height;
    uint8_t has_palette;
    uint8_t palette[64];
} dvds_config_st;

typedef struct tagMP4Track {
    struct tagMP4File       *m_pFile;
    struct tagATOM          *m_pTrakAtom;       // moov.trak[]
    MP4TrackId      m_trackId;          // moov.trak[].tkhd.trackId
    mvc_stream_type_et      m_TrackType;       // moov.trak[].mdia.hdlr.handlerType->mvc_stream_type_et

#ifdef MP4DEMUX_BUFMODE
    uint32_t        m_cur_sampleID;
    FILE_POS        m_cur_sampleFilePos;
    uint32_t        m_cur_chunkSSID; //current chunnk starting sample ID
    uint32_t        m_cur_chunkID;
    FILE_POS        m_cur_chunkFilePos;
    uint32_t        m_cur_SPC; //current samples per chunk
    uint32_t        m_cur_stsc;
    uint32_t        m_next_chunkSSID; //next chunnk starting sample ID
    uint32_t        m_next_chunkID;
    FILE_POS        m_next_chunkFilePos;
    uint32_t        m_next_SPC; //next samples per chunk

    FILE_POS       *m_stsz_offset; // used for stsz index mode

    uint32_t        m_cur_stts_SSID;
    MP4Timestamp    m_cur_stts_SSTime;
    uint32_t        m_cur_stts;
    uint32_t        m_cur_stts_size;
    MP4Duration     m_cur_stts_dur;

    uint32_t        m_next_stts_SSID;
    MP4Timestamp    m_next_stts_SSTime;
    uint32_t        m_next_stts;
    uint32_t        m_next_stts_size;
    MP4Duration     m_next_stts_dur;

    uint32_t        m_cur_ctts_SSID;
    uint32_t        m_cur_ctts;
    uint32_t        m_cur_ctts_size;
    MP4Duration     m_cur_ctts_offset;

    uint32_t        m_next_ctts_SSID;
    uint32_t        m_next_ctts;
    uint32_t        m_next_ctts_size;
    MP4Duration     m_next_ctts_offset;
#endif

    MP4Timestamp    m_first_ctts_entry_value;

    //sanity check
    uint8_t         legal_vendor;
    uint8_t         mace;

    // cached properties
    STSCPROP*       m_pStscProp;
    STSZPROP*       m_pStszProp;
    STTSPROP*       m_pSttsProp;
    STCOPROP*       m_pStcoProp;
    STSDPROP*       m_pStsdProp;
    CTTSPROP*       m_pCttsProp;
    D263PROP*       m_pD263Prop;
    DAMRPROP*       m_pDamrProp;
    MP4AV_ESDS*     m_pESDSProp;
    STSSPROP*       m_pStssProp;
    AVCConfig*      m_pavcCProp;
    AVSConfig*      m_pavssProp;
    HEVCConfig*     m_phevcProp;

    uint32_t*       m_pTimeScaleProperty;
    uint32_t*       m_pTrackDurationProperty;
    uint64_t*       m_pMediaDurationProperty;

    uint32_t*       m_pStszFixedSampleSizeProperty;
    uint32_t*       m_pStszSampleCountProperty;
    uint32_t**      m_pStszSampleSizeProperty;
    FILE_POS        m_pStszSampleSizeFilePos;

    uint32_t*       m_pStscCountProperty;
    //uint32_t**        m_pStscFirstChunkProperty;
    //uint32_t**        m_pStscSamplesPerChunkProperty;
    //uint32_t**        m_pStscSampleDescrIndexProperty;
    //uint32_t**        m_pStscFirstSampleProperty;
    FILE_POS        m_pStscSampleStartFilePos;
    FILE_POS        m_pStscSampleCurFilePos;
    uint32_t        m_pStscSampleIDPrev;
    uint32_t        m_pStscSampleIDNext;
    uint32_t        m_pStscFirstChunk;
    uint32_t        m_pStscSamplesPerChunk;
    uint32_t        m_pStscIndex;

    uint32_t*       m_pChunkCountProperty;
    FILE_POS        m_pChunkOffsetFilePos;

    uint32_t*       m_pSttsCountProperty;
    uint32_t*       m_pSttsSampleCountProperty;
    uint32_t*       m_pSttsSampleDeltaProperty;

    FILE_POS        m_pSttsSampleCountFilePos;
    FILE_POS        m_pCttsSampleCountFilePos;

    uint32_t*       m_pCttsCountProperty;
    uint32_t*       m_pCttsSampleCountProperty;
    int32_t*        m_pCttsSampleOffsetProperty;

    uint32_t        sample_rate;
    uint32_t        avg_bitrate;
    uint32_t        frame_rate;
    uint8_t         pcm_chk_read;
#ifdef MP4_SUPPORT_ROTATE
    uint16_t        rotate_angle;
#endif
    uint16_t        stream_width;
    uint16_t        stream_height;

    uint8_t         streamId; // the absolute index of this track according to file position, starting from 0

    struct tagMP4Track     *m_pNextItem;

    uint8_t         need_deliver_config;
} MP4TRACK, *PMP4TRACK;

typedef struct tagMP4TrackArray {
    uint32_t     m_totalnum;
    MP4TRACK    *m_pBegin;
    MP4TRACK    *m_pTail;
} MP4TRACKARRAY, *PMP4TRACKARRAY;

//-----------------------------------------------------------------------------
// for muxer
//-----------------------------------------------------------------------------
#if !defined(MP4REC_PLUGIN_EN)
// Tracks Array API
MP4TRACK *mxCreateMuxTrack(struct tagMP4File *pfile, struct tagATOM *pTrack);
#define mxMP4TracksGetSize(pArray) ((pArray)->m_totalnum)
MP4TRACK  *mxMP4TracksGet(MP4TRACKARRAY *pArray, uint32_t index);
uint8_t mxMP4TracksAdd(MP4TRACKARRAY *pArray, MP4TRACK *pTrack);
uint8_t mxMP4TracksFree(MP4TRACKARRAY *pArray);
uint8_t mxMP4TrackSetFixedSampleDuration(MP4TRACK *pTrack, MP4Duration duration);
// write out any remaining samples in chunk buffer
#define mxMP4TrackFinishWrite(pTrack) mxMP4TrackWriteChunkBuffer(pTrack)
void mxMP4TrackWriteChunkBuffer(MP4TRACK *pTrack);
void mxMP4TrackUpdateModificationTimes(MP4TRACK *pTrack);
#endif // MP4REC_PLUGIN_EN

//-----------------------------------------------------------------------------
// for demuxer
//-----------------------------------------------------------------------------
// Tracks Array API
MP4TRACK *CreateDmxTrack(void *ctx, struct tagMP4File *pfile, struct tagATOM *pTrack, int track_index);
#define MP4TracksGetSize(pArray) ((pArray)->m_totalnum)
MP4TRACK  *MP4TracksGet(MP4TRACKARRAY *pArray, uint32_t index);
uint8_t MP4TracksAdd(MP4TRACKARRAY *pArray, MP4TRACK *pTrack);
uint8_t MP4TracksFree(void *ctx, MP4TRACKARRAY *pArray);

// for read
uint32_t MP4TrackReadSample(MP4TRACK *pTrack,
                        MP4SampleId sampleId,
                        uint32_t* pNumBytes,
                        MP4Timestamp* pStartTime,
                        MP4Duration* pDuration,
                        uint32_t *pIsSyncSample,
                        ATTR_UNUSED uint32_t kmvType);
uint32_t MP4TrackReadSampleInfo(MP4TRACK *pTrack,
                        MP4SampleId sampleId,
                        FILE_POS*  pOffset,
                        uint32_t* pNumBytes,
                        MP4Timestamp* pStartTime,
                        MP4Duration* pDuration,
                        uint32_t* pIsSyncSample);

FILE_POS MP4TrackGetSampleFileOffset(MP4TRACK *pTrack, MP4SampleId sampleId);

void MP4TrackGetWidthHeight(MP4TRACK *pTrack, int *width, int *height);
void MP4TrackGetSampleRate(MP4TRACK *pTrack, uint32_t *samplerate);
void MP4TrackGetConfig(MP4TRACK *pTrack, uint8_t **config, uint32_t *config_len);
void MP4TrackDeliverConfig(MP4TRACK *pTrack, ATTR_UNUSED uint32_t kmvType);

#endif  /* MP4TRACK_H */
