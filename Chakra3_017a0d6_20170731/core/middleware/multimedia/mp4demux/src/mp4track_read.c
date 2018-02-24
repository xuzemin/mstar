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


#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "mp4track.h"
#include "mp4def.h"
#include "mp4file.h"
#include "mp4util.h"
#include "msmComm.h" //for MSMErrcode_e
#include "mvc_demuxer.h"
#ifdef SUPPORT_KMV

#include "kmv_api.h"
#endif

FILE_POS MP4TrackGetSampleFileOffset(MP4TRACK *pTrack, MP4SampleId sampleId);
FILE_POS MP4TrackGetSampleFileOffset_BufMode(MP4TRACK *pTrack, MP4SampleId sampleId);
FILE_POS MP4TrackGetSampleFileOffset_IdxMode(MP4TRACK *pTrack, MP4SampleId sampleId);
FILE_POS MP4TrackGetSampleFileOffset_Update(MP4TRACK *pTrack, MP4SampleId sampleId);
void MP4TrackGetSampleTimes_BufMode(MP4TRACK *pTrack, MP4SampleId sampleId,
                                    MP4Timestamp* pStartTime, MP4Duration* pDuration);
void MP4TrackGetSampleTimes_BufMode_Update(MP4TRACK *pTrack, MP4SampleId sampleId,
                                           uint32_t start_stscIndex, MP4SampleId start_sid, MP4Duration start_elapsed,
                                           MP4Timestamp* pStartTime, MP4Duration* pDuration);

void GetStcoEntry(MP4TRACK *pTrack, MP4SampleId chunk_idx, STCO_ENTRY *stco_entry);
void GetStszEntry(MP4TRACK *pTrack, MP4SampleId sampleId, STSZ_ENTRY *stsz_entry);
void GetSttsEntry(MP4TRACK *pTrack, uint32_t stts_idx, STTS_ENTRY *stts_entry);
void GetCttsEntry(MP4TRACK *pTrack, uint32_t ctts_idx, CTTS_ENTRY *ctts_entry);
FILE_POS GetStscEntry(MP4TRACK *pTrack, uint32_t stsc_index, STSC_ENTRY *stsc_entry);
int32_t MP4TrackGetSampleStscIndex(MP4TRACK *pTrack, MP4SampleId sampleId);
void MP4TrackGetSampleTimes(MP4TRACK *pTrack, MP4SampleId sampleId,
                            MP4Timestamp* pStartTime, MP4Duration* pDuration);
uint32_t MP4TrackGetSampleSize(MP4TRACK *pTrack, MP4SampleId sampleId);
uint32_t MP4TrackIsSyncSample(MP4TRACK *pTrack, MP4SampleId sampleId);
MP4SampleId MP4TrackGetKeyFrameBySampleIndex(MP4TRACK *pTrack, MP4SampleId sample_id,
                                             MP4SampleId *prev_key_frame_id);
int MP4TrackGetSampleIndex_byTime(MP4TRACK *pTrack, MP4Timestamp StartTime, MP4SampleId *sampleId);
MP4SampleId MP4TrackGetKeyFrameByTime(MP4TRACK *pTrack, MP4Timestamp StartTime, MP4SampleId *prev_key_frame_id);
int MP4TrackGetSampleIndex_byTime(MP4TRACK *pTrack, MP4Timestamp StartTime, MP4SampleId *sampleId);

//-----------------------------------------------------------------------------
//extern Variables or functions
//-----------------------------------------------------------------------------
extern int32_t MP4TrackGetSampleStscIndex_BufMode(MP4TRACK *pTrack, MP4SampleId sampleId);
//-----------------------------------------------------------------------------

#define PRECISE_DROP

void DtsToCts_BufMode(MP4TRACK *pTrack, MP4Timestamp* pStartTime, MP4SampleId sampleId)
{
    uint32_t numCtts = *(pTrack->m_pCttsCountProperty);
    MP4SampleId sid = 1;
    uint32_t cttsIndex = 0;
    CTTS_ENTRY curr_ctts_entry;
    uint8_t SampleOffsetFound = 0;
    MP4Timestamp temp_start_time = 0;

    if (pStartTime)
        temp_start_time = *pStartTime;

    if (pTrack->m_first_ctts_entry_value == (MP4Timestamp)-1)
    {
        GetCttsEntry(pTrack, 0, &curr_ctts_entry);
        pTrack->m_first_ctts_entry_value = curr_ctts_entry.sample_offset;
    }

    if (sampleId >= pTrack->m_cur_sampleID && pTrack->m_cur_ctts_SSID !=0)
    {
        if (sampleId < pTrack->m_cur_ctts_SSID + pTrack->m_cur_ctts_size)
        {
            temp_start_time += pTrack->m_cur_ctts_offset;
            SampleOffsetFound = 1;
        }
        else if (sampleId < pTrack->m_next_ctts_SSID + pTrack->m_next_ctts_size)
        {
            temp_start_time += pTrack->m_next_ctts_offset;
            // update
            pTrack->m_cur_ctts_SSID = pTrack->m_next_ctts_SSID;
            pTrack->m_cur_ctts = pTrack->m_next_ctts;
            pTrack->m_cur_ctts_size = pTrack->m_next_ctts_size;
            pTrack->m_cur_ctts_offset = pTrack->m_next_ctts_offset;

            GetCttsEntry(pTrack, pTrack->m_cur_ctts + 1, &curr_ctts_entry);
            pTrack->m_next_ctts_SSID = pTrack->m_cur_ctts_SSID + pTrack->m_cur_ctts_size;
            pTrack->m_next_ctts = pTrack->m_cur_ctts + 1;
            pTrack->m_next_ctts_size = curr_ctts_entry.sample_count;
            pTrack->m_next_ctts_offset = curr_ctts_entry.sample_offset;
            SampleOffsetFound = 1;
        }
        else
        {
            // moving far forward
            cttsIndex = pTrack->m_next_ctts + 1;
            sid = pTrack->m_next_ctts_SSID + pTrack->m_next_ctts_size;

            //continue to update
        }
    }
    else
    {
        //moving backward
        cttsIndex = 0;
        sid = 1;

        //continue to update
    }


    if (!SampleOffsetFound)
    {
        for (; cttsIndex < numCtts; cttsIndex++)
        {
            GetCttsEntry(pTrack, cttsIndex, &curr_ctts_entry);

            if (sampleId < sid + curr_ctts_entry.sample_count)
            {

                temp_start_time += curr_ctts_entry.sample_offset;

                // update
                pTrack->m_cur_ctts_SSID = sid;
                pTrack->m_cur_ctts = cttsIndex;
                pTrack->m_cur_ctts_size = curr_ctts_entry.sample_count;
                pTrack->m_cur_ctts_offset = curr_ctts_entry.sample_offset;

                GetCttsEntry(pTrack, pTrack->m_cur_ctts + 1, &curr_ctts_entry);
                pTrack->m_next_ctts_SSID = pTrack->m_cur_ctts_SSID + pTrack->m_cur_ctts_size;
                pTrack->m_next_ctts = pTrack->m_cur_ctts + 1;
                pTrack->m_next_ctts_size = curr_ctts_entry.sample_count;
                pTrack->m_next_ctts_offset = curr_ctts_entry.sample_offset;
                break;
            }
            sid += curr_ctts_entry.sample_count;
        }
    }

     /* make cts start from 0 */
    if (temp_start_time >= pTrack->m_first_ctts_entry_value)
        temp_start_time -= pTrack->m_first_ctts_entry_value;
    else
    {
        // avoid negative pts
        temp_start_time = 0;
    }

     if (pStartTime)
        *pStartTime = temp_start_time;
}

static void DtsToCts(MP4TRACK *pTrack, MP4Timestamp* pStartTime, MP4SampleId sampleId)
{
    uint32_t numCtts = *(pTrack->m_pCttsCountProperty);
    MP4SampleId sid = 1;
    uint32_t sampleCount=0;
    uint32_t cttsIndex;
    int32_t sampleOffset = 0;
    CTTS_ENTRY curr_ctts_entry;

    assert(pStartTime != 0);

    if(numCtts == 1) {
        sampleCount = *pTrack->m_pCttsSampleCountProperty;
        sampleOffset = *pTrack->m_pCttsSampleOffsetProperty;
    }

    if (pTrack->m_first_ctts_entry_value == (MP4Timestamp)-1)
    {
        GetCttsEntry(pTrack, 0, &curr_ctts_entry);
        pTrack->m_first_ctts_entry_value = curr_ctts_entry.sample_offset;
    }

    for (cttsIndex = 0; cttsIndex < numCtts; cttsIndex++) {
        if (numCtts != 1) {
            //diag_printf("MP4TrackGetSampleTimes\n");
            GetCttsEntry(pTrack, cttsIndex, &curr_ctts_entry);

            sampleCount = curr_ctts_entry.sample_count;
            sampleOffset = curr_ctts_entry.sample_offset;
        }

        if (sampleId < sid + sampleCount) {
            *pStartTime += sampleOffset;
            //diag_printf("set pStartTime:%lld\n", *pStartTime);
            break;
        }
        sid += sampleCount;
    }

    /* make cts start from 0 */
    if (*pStartTime >= pTrack->m_first_ctts_entry_value)
        *pStartTime -= pTrack->m_first_ctts_entry_value;
    else
    {
        // avoid negative pts
        *pStartTime = 0;
    }
}

static int MP4TrackUpdateNextChunkProp(MP4TRACK *pTrack)
{
    STSC_ENTRY next_stsc_entry;
    STCO_ENTRY next_stco_entry;

    if ((pTrack->m_cur_stsc + 1) < *pTrack->m_pStscCountProperty)
    {
        GetStscEntry(pTrack, pTrack->m_cur_stsc + 1, &next_stsc_entry);
        pTrack->m_next_chunkSSID = pTrack->m_cur_chunkSSID + (next_stsc_entry.first_chunk - pTrack->m_cur_chunkID) * pTrack->m_cur_SPC; //next chunk starting sample ID
        pTrack->m_next_chunkID = next_stsc_entry.first_chunk;
        GetStcoEntry(pTrack, next_stsc_entry.first_chunk, &next_stco_entry);
        pTrack->m_next_chunkFilePos = next_stco_entry.chunk_offset_e;
        pTrack->m_next_SPC = next_stsc_entry.samples_per_chunk; //next samples per chunk
    }
    else if ((pTrack->m_cur_stsc + 1) == *pTrack->m_pStscCountProperty)
    {
        next_stsc_entry.first_chunk = *pTrack->m_pChunkCountProperty + 1;
        next_stsc_entry.samples_per_chunk = 1;
        pTrack->m_next_chunkSSID = pTrack->m_cur_chunkSSID+(next_stsc_entry.first_chunk-pTrack->m_cur_chunkID)*pTrack->m_cur_SPC; //next chunnk starting sample ID
        pTrack->m_next_chunkID = next_stsc_entry.first_chunk;
        //GetStcoEntry(pTrack, next_stsc_entry.first_chunk, &curr_stco_entry);
        pTrack->m_next_chunkFilePos = pTrack->m_cur_chunkFilePos;
        pTrack->m_next_SPC = pTrack->m_cur_SPC; //next samples per chunk
    }
    else
        return MSMERR_FALSE;

    return MSMERR_OK;
}

void MP4TrackGetSampleFileOffset_BufModeInit(MP4TRACK *pTrack)
{
    MP4SampleId sampleId = 1; //this should be checked, maybe there are cases not starting from 1
    STSC_ENTRY curr_stsc_entry;
    STCO_ENTRY curr_stco_entry;

    GetStscEntry(pTrack, 0, &curr_stsc_entry);
    pTrack->m_cur_sampleID = sampleId;
    pTrack->m_cur_chunkSSID = sampleId; //current chunk starting sample ID
    pTrack->m_cur_chunkID = curr_stsc_entry.first_chunk;
    GetStcoEntry(pTrack, curr_stsc_entry.first_chunk, &curr_stco_entry);
    pTrack->m_cur_chunkFilePos = curr_stco_entry.chunk_offset_e;
    pTrack->m_cur_SPC = curr_stsc_entry.samples_per_chunk; //current samples per chunk
    pTrack->m_cur_sampleFilePos = pTrack->m_cur_chunkFilePos;
    pTrack->m_cur_stsc = 0;

    MP4TrackUpdateNextChunkProp(pTrack);
}

void MP4TrackGetSampleFileOffset_IdxModeInit(void *ctx, MP4TRACK *pTrack)
{
    uint32_t stsz_count = *pTrack->m_pStszSampleCountProperty;
    uint32_t stsz_idx_count;
    uint32_t i;
    uint32_t stsz_sum = 0;
    uint32_t stsz_idx = 0;
    STSZ_ENTRY curr_stsz_entry;
    STCO_ENTRY curr_stco_entry;

    //build file offset every 128 samples
    stsz_idx_count = (stsz_count >> 7) + 1;
    pTrack->m_stsz_offset = mdxalloc(ctx, stsz_idx_count * sizeof(FILE_POS));
    assert(stsz_idx_count * sizeof(FILE_POS) < 8 * 1024);
    assert(pTrack->m_stsz_offset);

    GetStcoEntry(pTrack, 1, &curr_stco_entry);

    // setup first frame
    pTrack->m_cur_sampleID = 1/*sampleId*/;
    pTrack->m_cur_sampleFilePos = curr_stco_entry.chunk_offset_e;

    if (!pTrack->m_stsz_offset)
        return;
    if (stsz_idx_count * sizeof(FILE_POS) >= 8 * 1024)
    {
        mdxfree(ctx, pTrack->m_stsz_offset);
        pTrack->m_stsz_offset = 0; // disable index mode
        return;
    }

    *pTrack->m_stsz_offset = curr_stco_entry.chunk_offset_e;

    for (i = 1; i <= stsz_count; i++)
    {
        GetStszEntry(pTrack, i, &curr_stsz_entry);
        stsz_sum += curr_stsz_entry.sample_size;
        if (((i - 1) & 0x7f) == 0x7f)
        {
            *(pTrack->m_stsz_offset + stsz_idx + 1) = *(pTrack->m_stsz_offset + stsz_idx) + stsz_sum;
            stsz_sum = 0;
            stsz_idx++;
        }
    }
}

static int MP4TrackAudioUncompressed(MP4TRACK *pTrack)
{
    switch (pTrack->m_pStsdProp->data_format)
    {
    case CODEC_TYPE_4CC('s','o','w','t'):
    case CODEC_TYPE_4CC('t','w','o','s'):
    case CODEC_TYPE_4CC('r','a','w',' '):
        return MSMERR_OK;
    }
    return MSMERR_FALSE;
}

int MP4TrackIsStsdUncompSample(MP4TRACK *pTrack)
{
    // if current audio is already uncompressed data
    // the meaning of bytesPerFrame and samplesPerPacket is different from compressed data
    if (MP4TrackAudioUncompressed(pTrack) == MSMERR_OK)
        return MSMERR_FALSE;

    if (pTrack->m_TrackType == MVC_STREAM_AUDIO
        && pTrack->m_pStsdProp->u.a_desc.bytesPerFrame
        && pTrack->m_pStsdProp->u.a_desc.samplesPerPacket
        )
        return MSMERR_OK;

    return MSMERR_FALSE;
}

void MP4TrackDeliverConfig(MP4TRACK *pTrack, ATTR_UNUSED uint32_t kmvType)
{
    void *packet_buf;
    const mvc_callback_st *callback = &pTrack->m_pFile->callback;

    if (!pTrack->need_deliver_config)
        return;

    if (pTrack->m_TrackType == MVC_STREAM_SUBTITLE)
    {
        void *cfg_buf = 0;
        uint8_t cfg_len = 0;
        int32_t codec_type = CLIP_SUBTITLE_TYPE_UNKNOWN;
        dvds_config_st config;

        memset(&config, 0, sizeof(dvds_config_st));

        if (pTrack->m_pStsdProp->data_format == CODEC_TYPE_4CC('m','p','4','s'))
        {
            codec_type = CLIP_SUBTITLE_TYPE_DVDS;
            config.width  = pTrack->stream_width;
            config.height = pTrack->stream_height;

            if (pTrack->m_pESDSProp && pTrack->m_pESDSProp->decoder_cfg && pTrack->m_pESDSProp->decoder_cfg_len)
            {
                // get palette info
                cfg_buf = pTrack->m_pESDSProp->decoder_cfg;
                cfg_len = pTrack->m_pESDSProp->decoder_cfg_len;
                if (cfg_len >= sizeof(config.palette))
                {
                    config.has_palette = 1;
                    memcpy(config.palette, cfg_buf, sizeof(config.palette));
                }
            }
            // overall config to mp4s
            cfg_buf = &config;
            cfg_len = sizeof(dvds_config_st);
        }
        else if (pTrack->m_pStsdProp->data_format == CODEC_TYPE_4CC('t','x','3','g'))
            codec_type = CLIP_SUBTITLE_TYPE_TX3G;
        else
            assert(0);

        if (callback->stream_alloc(callback->context, pTrack->m_TrackType, &packet_buf, sizeof(int32_t) + cfg_len) == MVC_OK)
        {
            memcpy(packet_buf, &codec_type, sizeof(int32_t));
            if (cfg_buf && cfg_len)
                memcpy((uint8_t *)packet_buf + sizeof(int32_t), cfg_buf, cfg_len);

            callback->stream_commit(callback->context, MVC_STREAM_SUBTITLE, sizeof(int32_t) + cfg_len, -1, 0, 1);
            pTrack->need_deliver_config = 0;
        }
    }
    else
    {
        uint8_t *config;
        uint32_t config_len;

        MP4TrackGetConfig(pTrack, &config, &config_len);
        if (callback->stream_alloc(callback->context, pTrack->m_TrackType, &packet_buf, sizeof(int32_t) + config_len) == MVC_OK)
        {
            int32_t codec_type;
#ifdef SUPPORT_KMV_DRM
            MP4FILE *pfile = pTrack->m_pFile;
            kmv_func_st *kmvhdr = Get_kmv_func();
#endif
            if (pTrack->m_TrackType == MVC_STREAM_VIDEO)
                codec_type = MP4UnifyVideo4cc(pTrack->m_pStsdProp->data_format);
            else
                codec_type = MP4UnifyAudio4cc(pTrack->m_pStsdProp->data_format);

            memcpy(packet_buf, &codec_type, sizeof(int32_t));
            if (config && config_len)
                memcpy((uint8_t *)packet_buf + sizeof(int32_t), config, config_len);
#ifdef SUPPORT_KMV_DRM
            if (config_len && kmvhdr && kmvhdr->KMV_IsDRM(kmvType) && !kmvhdr->KMV_IsM4vfmt(kmvType))
            {
                // decrypt is in-place, so only do it for the data in rbuf
                kmvhdr->KMV_AES_SPS_PPS((uint8_t *)packet_buf + sizeof(int32_t),
                                          config_len,
                                          pfile->m_KMVkey);
            }
#endif
            callback->stream_commit(callback->context, pTrack->m_TrackType, sizeof(int32_t) + config_len, -1, 0, 1);
            pTrack->need_deliver_config = 0;
        }
    }
}

uint32_t MP4TrackReadSample(MP4TRACK *pTrack,
                        MP4SampleId sampleId,
                        uint32_t* pNumBytes,
                        MP4Timestamp* pStartTime,
                        MP4Duration* pDuration,
                        uint32_t *pIsSyncSample,
                        ATTR_UNUSED uint32_t kmvType)
{
    FILE_POS fileOffset;
    uint32_t sampleSize;
    uint32_t data_fmt = pTrack->m_pStsdProp->data_format;
    mvc_stream_type_et trackType = pTrack->m_TrackType;
    const mvc_callback_st *callback = &pTrack->m_pFile->callback;
    int64_t pts, duration;
    int ret;
    uint32_t kmv_offset = 0;
    void *pBuffer;
    uint8_t *pBytes;
#ifdef SUPPORT_KMV
    kmv_func_st *kmvhdr = Get_kmv_func();
    kmv_meta_st tmp_kmv;
    int kmvRtl;
#endif

#ifdef SUPPORT_KMV
    if (kmvType != KMV_NOT_KMV)
        kmv_offset = KMV_BUFFER_ELEMENT;

    if (callback->stream_alloc(callback->context, trackType, &pBuffer, kmv_offset) != MSMERR_OK)
        return MSMERR_OUT_OF_MEMORY;

    if (kmvhdr && kmvhdr->KMV_IsSEIfmt(kmvType))
    {
        memset(pBuffer, 0, sizeof(kmv_meta_st));
    }
    else if (kmvType != KMV_NOT_KMV)
    {

        memset(&tmp_kmv, 0, sizeof(kmv_meta_st));
        kmvRtl = kmvhdr->MP4DMX_ReadKMVMeta(pTrack->m_pFile, sampleId, &tmp_kmv.tType,
            &tmp_kmv.recH, &tmp_kmv.recW,
            tmp_kmv.kmvMeta, &tmp_kmv.nsize);
        if (kmvRtl != MSMERR_OK)
        {
            return kmvRtl;
        }
        memcpy(pBuffer, &tmp_kmv, KMV_BUFFER_ELEMENT);
    }
#endif

    ret = MP4TrackReadSampleInfo(pTrack, sampleId, &fileOffset, &sampleSize, pStartTime, pDuration, pIsSyncSample);
    if (ret != MSMERR_OK)
        return MSMERR_DMX_VDO_READ_INVLD;

    *pNumBytes = sampleSize;
    pts = (*pStartTime * 1000 + ((*pTrack->m_pTimeScaleProperty) >> 1)) / (*pTrack->m_pTimeScaleProperty);
    duration = (*pDuration * 1000 + ((*pTrack->m_pTimeScaleProperty) >> 1)) / (*pTrack->m_pTimeScaleProperty);
    if (MP4FileSetPosition(pTrack->m_pFile, fileOffset) == (FILE_OFF)-1)
        return MSMERR_DMX_VDO_READ_INVLD;

   // =====================================================

    if (data_fmt == CODEC_TYPE_4CC('a','v','c','1') || data_fmt == CODEC_TYPE_4CC('a','v','s','2')
     || data_fmt == CODEC_TYPE_4CC('h','v','c','1') || data_fmt == CODEC_TYPE_4CC('h','e','v','1'))
    {
        uint32_t j, nal_size, remain;
        AVCConfig *avcc = pTrack->m_pavcCProp;
        AVSConfig *avss = pTrack->m_pavssProp;
        HEVCConfig *hevc = pTrack->m_phevcProp;
        uint8_t  avccfgprefix[4] = {0, 0, 0, 1};
        uint8_t  avscfgprefix[3] = {0, 0, 1}; // also use this for HEVC
        uint32_t byte_count = 0;
        uint8_t nal_unit_size = 0;
        uint8_t *cfg_prefix = 0;
        uint8_t cfg_prefix_len = 0;
        uint32_t skip_nal_byte = 0;

        if (avcc)
        {
            cfg_prefix = avccfgprefix;
            cfg_prefix_len = sizeof(avccfgprefix);
            nal_unit_size = avcc->nal_unit_size;
        }
        else if (avss)
        {
            cfg_prefix = avscfgprefix;
            cfg_prefix_len = sizeof(avscfgprefix);
            nal_unit_size = avss->nal_unit_size;
            skip_nal_byte = 1;
        }
        else if (hevc)
        {
            cfg_prefix = avscfgprefix;
            cfg_prefix_len = sizeof(avscfgprefix);
            nal_unit_size = hevc->nal_unit_size;
        }
        else
            return MSMERR_DMX_VDO_READ_INVLD;

#ifdef SUPPORT_KMV
        byte_count += kmv_offset;
        if (callback->stream_realloc(callback->context, trackType, &pBuffer, byte_count) != MSMERR_OK)
#else
        if (callback->stream_alloc(callback->context, trackType, &pBuffer, byte_count) != MSMERR_OK)
#endif
            return MSMERR_OUT_OF_MEMORY;
        pBytes = pBuffer;

        remain = sampleSize;
        while (remain)
        {
            uint8_t b4[4];

            nal_size = 0;
            if(nal_unit_size > 4 || remain < nal_unit_size)
            {   /* we think nal_size_length should < 4 and remain data size should be larger than nal_size_length*/
                return MSMERR_DMX_RETRY;
            }

            if (MP4FileReadBytes(pTrack->m_pFile, b4, nal_unit_size) != nal_unit_size)
            {
                return MSMERR_DMX_VDO_READ_INVLD;
            }

            for (j = 0; j < nal_unit_size; j++)
            {
                nal_size |= b4[j];
                if (j + 1 < nal_unit_size)
                    nal_size <<= 8;
                remain--;
            }

            if (nal_size > remain)
            {
                if (MP4FileSkipBytes(pTrack->m_pFile, remain) == -1)
                    return MSMERR_DMX_VDO_READ_INVLD;
                else
                    return MSMERR_DMX_RETRY;
            }

            if (nal_size > skip_nal_byte)
            {
                if (MP4FileSkipBytes(pTrack->m_pFile, skip_nal_byte) == -1)
                    return MSMERR_DMX_VDO_READ_INVLD;
                // skip bytes in nal unit
                remain -= skip_nal_byte;
                nal_size -= skip_nal_byte;
            }
            else
                return MSMERR_DMX_RETRY; // skip this nalu

            if (callback->stream_realloc(callback->context, trackType, &pBuffer, byte_count + cfg_prefix_len + nal_size) != MSMERR_OK)
            {
                callback->stream_discard(callback->context, trackType);
                return MSMERR_OUT_OF_MEMORY;
            }
            pBytes = pBuffer;

            //add start code
            memcpy((pBytes + byte_count), cfg_prefix, cfg_prefix_len);
            byte_count += cfg_prefix_len;

            if (MP4FileReadBytes(pTrack->m_pFile, (pBytes + byte_count), nal_size) == 0)
            {
                callback->stream_discard(callback->context, trackType);
                return MSMERR_DMX_VDO_READ_INVLD;
            }
#ifdef SUPPORT_KMV
            if (kmvType != KMV_NOT_KMV)
            {
                if (kmvhdr->KMV_IsSEIfmt(kmvType))
                {
                    if (((pBytes + byte_count)[0] == 0x06) && ((pBytes + byte_count)[1] == 0x25))
                    {
                        assert(nal_size <= KMV_META_LEN);
                        memcpy(pBytes, (pBytes + byte_count+1), nal_size-1);
                        kmvhdr->KMV_InterpretSEIMessage(pBytes, nal_size);
                    }
                }
#ifdef SUPPORT_KMV_DRM
                if (kmvhdr->KMV_IsDRM(kmvType))
                {
                    kmvhdr->KMV_AES_Decode((pBytes + byte_count),nal_size, pTrack->m_pFile->m_KMVkey, pTrack->m_pFile->m_KMVAESCache);
                }
#endif
            }
#endif // SUPPORT_KMV
            byte_count += nal_size;
            remain -= MP4_MIN(nal_size, remain);
        }

#ifdef SUPPORT_KMV
        if (kmvType != KMV_NOT_KMV)
        {
            kmvhdr->KMV_DecryptFrame((uint8_t *) pBuffer + KMV_BUFFER_ELEMENT,
                                    byte_count - KMV_BUFFER_ELEMENT,
                                    pTrack->m_pFile->m_KMVscrm, kmvType);
        }
#endif

        // update the read size
        *pNumBytes = byte_count;
        callback->stream_commit(callback->context, trackType, *pNumBytes, pts * 1000, duration * 1000, 0);
    }
    else
    {
#ifdef SUPPORT_KMV
        if (callback->stream_realloc(callback->context, trackType, &pBuffer, sampleSize + kmv_offset) != MSMERR_OK)
#else
        if (callback->stream_alloc(callback->context, trackType, &pBuffer, sampleSize + kmv_offset) != MSMERR_OK)
#endif
            return MSMERR_OUT_OF_MEMORY;

        pBytes = pBuffer;

        if (MP4FileReadBytes(pTrack->m_pFile, pBytes + kmv_offset, sampleSize) == 0)
        {
            callback->stream_discard(callback->context, trackType);
            return MSMERR_DMX_VDO_READ_INVLD;
        }
#ifdef SUPPORT_KMV_DRM
        if (kmvType != KMV_NOT_KMV && kmvhdr && kmvhdr->KMV_IsDRM(kmvType)) {
            kmvhdr->KMV_AES_Decode(pBytes + kmv_offset, sampleSize, pTrack->m_pFile->m_KMVkey, pTrack->m_pFile->m_KMVAESCache);
        }
#endif
#ifdef SUPPORT_KMV
        if (kmvType != KMV_NOT_KMV)
        {
            kmvhdr->KMV_DecryptFrame(pBytes + kmv_offset, sampleSize, pTrack->m_pFile->m_KMVscrm, kmvType);
        }
#endif
        callback->stream_commit(callback->context, trackType, sampleSize + kmv_offset, pts * 1000, duration * 1000, 0);
    }

    return MSMERR_OK;
}

uint32_t MP4TrackReadSampleInfo(MP4TRACK *pTrack,
                        MP4SampleId sampleId,
                        FILE_POS* pOffset,
                        uint32_t* pNumBytes,
                        MP4Timestamp* pStartTime,
                        MP4Duration* pDuration,
                        uint32_t* pIsSyncSample)
{
    FILE_POS fileOffset;
    uint32_t sampleSize;
    //FILE_POS oldPos;

#ifdef MP4DEMUX_BUFMODE
    STSC_ENTRY curr_stsc_entry;
    STSZ_ENTRY curr_stsz_entry;
#endif

    if (pStartTime || pDuration)
    {
        MP4Timestamp pStartTime_tmp;
        MP4Duration  pDuration_tmp;
        if (!pStartTime) {
            pStartTime = &pStartTime_tmp;
        }
        if (!pDuration) {
            pDuration = &pDuration_tmp;
        }
#ifdef MP4DEMUX_BUFTIME
        if (*(pTrack->m_pSttsCountProperty) > 1) {
            if (/*sampleId == 1*/ pTrack->m_cur_stts_SSID == 0 ) {
                //setup stts
                STTS_ENTRY curr_stts_entry;
                //diag_printf("setup stts, Id==1, stts>1, track id:%d\n", pTrack->m_trackId);
                //stts index starts from 0;
                GetSttsEntry(pTrack, 0/*sttsIndex*/, &curr_stts_entry);
                pTrack->m_cur_stts_SSID = 1;
                pTrack->m_cur_stts_SSTime = 0;
                pTrack->m_cur_stts = 0;
                pTrack->m_cur_stts_size = curr_stts_entry.sample_count;
                pTrack->m_cur_stts_dur = curr_stts_entry.sample_duration;

                GetSttsEntry(pTrack, 1/*sttsIndex*/, &curr_stts_entry);
                pTrack->m_next_stts_SSID = 1 + pTrack->m_cur_stts_size;
                pTrack->m_next_stts_SSTime = pTrack->m_cur_stts_size * pTrack->m_cur_stts_dur;
                pTrack->m_next_stts = 1;
                pTrack->m_next_stts_size = curr_stts_entry.sample_count;
                pTrack->m_next_stts_dur = curr_stts_entry.sample_duration;

#if 0 //Not tested yet
                if (sampleId != 1) {
                    diag_printf("stts > 1, sampleId:%d\n", sampleId);
                    MP4TrackGetSampleTimes_BufMode_Update(pTrack, sampleId, 0, 1, 0,
                        pStartTime, pDuration);
                }
#endif
            }

            MP4TrackGetSampleTimes_BufMode(pTrack, sampleId, pStartTime, pDuration);

        } else {

#ifdef PRECISE_DROP
            //Sean
            if (/*sampleId == 1*/ pTrack->m_cur_stts_SSID == 0) {
                //setup stts
                STTS_ENTRY curr_stts_entry;
                //diag_printf("setup stts, Id==1, stts==1\n");
                //stts index starts from 0;
                GetSttsEntry(pTrack, 0/*sttsIndex*/, &curr_stts_entry);
                pTrack->m_cur_stts_SSID = 1;
                pTrack->m_cur_stts_SSTime = 0;
                pTrack->m_cur_stts = 0;
                pTrack->m_cur_stts_size = curr_stts_entry.sample_count;
                pTrack->m_cur_stts_dur = curr_stts_entry.sample_duration;

                GetSttsEntry(pTrack, 1/*sttsIndex*/, &curr_stts_entry);
                pTrack->m_next_stts_SSID = 1 + pTrack->m_cur_stts_size;
                pTrack->m_next_stts_SSTime = pTrack->m_cur_stts_size * pTrack->m_cur_stts_dur;
                pTrack->m_next_stts = 1;
                pTrack->m_next_stts_size = curr_stts_entry.sample_count;
                pTrack->m_next_stts_dur = curr_stts_entry.sample_duration;
            }
#endif // PRECISE_DROP
            MP4TrackGetSampleTimes(pTrack, sampleId, pStartTime, pDuration);
        }
#else // MP4DEMUX_BUFTIME
        MP4TrackGetSampleTimes(pTrack, sampleId, pStartTime, pDuration);
#endif // MP4DEMUX_BUFTIME
    }

    // handle unusual case of wanting to read a sample

#ifdef MP4DEMUX_BUFMODE
    if (*pTrack->m_pStscCountProperty > 1)
        fileOffset = MP4TrackGetSampleFileOffset_BufMode(pTrack, sampleId);
    else if (*pTrack->m_pChunkCountProperty == 1)
    {
        if (sampleId == pTrack->m_cur_sampleID + 1)
        {
            GetStszEntry(pTrack, pTrack->m_cur_sampleID, &curr_stsz_entry);
            fileOffset = pTrack->m_cur_sampleFilePos + curr_stsz_entry.sample_size;
        }
        else if (pTrack->m_stsz_offset)
            fileOffset = MP4TrackGetSampleFileOffset_IdxMode(pTrack, sampleId);
        else
            fileOffset = MP4TrackGetSampleFileOffset(pTrack, sampleId);

        //update current sample data
        //pTrack->m_cur_sampleID = sampleId;
        pTrack->m_cur_sampleFilePos = fileOffset;
    }
    else
    {
        fileOffset = MP4TrackGetSampleFileOffset(pTrack, sampleId);
        if (pTrack->pcm_chk_read && *pTrack->m_pStscCountProperty == 1)
        {
            if (GetStscEntry(pTrack, 0, &curr_stsc_entry) == (FILE_POS)-1)
                return MSMERR_DMX_VDO_READ_INVLD;
            else
            {
                pTrack->m_cur_sampleID = sampleId;
                //pTrack->m_cur_chunkSSID = sampleId; //current chunk starting sample ID
                pTrack->m_cur_chunkSSID = 1+((sampleId - 1)/curr_stsc_entry.samples_per_chunk)*curr_stsc_entry.samples_per_chunk;
                pTrack->m_cur_chunkID = curr_stsc_entry.first_chunk;
                pTrack->m_cur_SPC = curr_stsc_entry.samples_per_chunk;
            }
        }
    }
#else
    fileOffset = MP4TrackGetSampleFileOffset(pTrack, sampleId);
#endif

    if (fileOffset == (FILE_POS)-1)
        return MSMERR_DMX_VDO_READ_INVLD;
    if (pOffset)
        *pOffset = fileOffset;

    if (pTrack->pcm_chk_read)
    {
        STCO_ENTRY next_stco_entry;
        uint32_t chunk_count = 1;

        // if there is at least one extra chunk in this stsc
        while(pTrack->m_cur_chunkID + chunk_count < pTrack->m_next_chunkID)
        {
            FILE_POS cur_chunk_end = pTrack->m_cur_chunkFilePos + *pTrack->m_pStszFixedSampleSizeProperty * pTrack->m_cur_SPC * chunk_count;

            GetStcoEntry(pTrack, pTrack->m_cur_chunkID + chunk_count, &next_stco_entry);
            // max chunk size 10k
            if (next_stco_entry.chunk_offset_e == cur_chunk_end && cur_chunk_end - pTrack->m_cur_chunkFilePos < 10 * 1024)
                chunk_count++;
            else
                break;
        }

        if (sampleId < (pTrack->m_cur_chunkSSID + pTrack->m_cur_SPC * chunk_count))
            sampleSize = (pTrack->m_cur_chunkSSID + pTrack->m_cur_SPC * chunk_count - sampleId) * (*pTrack->m_pStszFixedSampleSizeProperty);
        else
            return MSMERR_DMX_VDO_READ_INVLD;
    }
    else
        sampleSize = MP4TrackGetSampleSize(pTrack, sampleId);

    // if the infos of stsz and stsc indicate the uncompressed data, we need to re-calculate sample size
    if (MP4TrackIsStsdUncompSample(pTrack) == MSMERR_OK)
        sampleSize = sampleSize / pTrack->m_pStsdProp->u.a_desc.samplesPerPacket * pTrack->m_pStsdProp->u.a_desc.bytesPerFrame;

    if (pNumBytes)
        *pNumBytes = sampleSize;

    if (pIsSyncSample)
        *pIsSyncSample = MP4TrackIsSyncSample(pTrack, sampleId);

    pTrack->m_cur_sampleID = sampleId;

    return MSMERR_OK;
}

#ifdef USE_ATOM_BUFFERRED_READ

void GetStcoEntry(MP4TRACK *pTrack,
                         MP4SampleId chunk_idx,
                         STCO_ENTRY *stco_entry
                         )
{
    uint32_t buffer_offset;
    STCOPROP *pstco = (STCOPROP *)pTrack->m_pStcoProp;  // pTrack->m_pStcoProp is not NULL since checking is done on atom init
    uint32_t *curr_page_idx;
    uint8_t *stco_page;

    assert(pstco != NULL);
    stco_page       = pstco->cache_page;
    curr_page_idx   = &pstco->page_idx;

    if(!stco_page)
    {
        stco_entry->chunk_offset_e = 0;
        return;
    }
    MP4FileCacheBufferredPage(pTrack->m_pFile, stco_page, curr_page_idx, pTrack->m_pChunkOffsetFilePos, pstco->table_size,
                              pstco->cache_size, pstco->entry_byte_count, (chunk_idx - 1)/*0 based*/, &buffer_offset);

    if (pstco->entry_byte_count == 4)
        stco_entry->chunk_offset_e = MP4FileReadBufferredUInt32(stco_page, &buffer_offset);
    else
        stco_entry->chunk_offset_e = MP4FileReadBufferredUInt64(stco_page, &buffer_offset);
}
#else
static void GetStcoEntry(MP4TRACK *pTrack,
                         MP4SampleId chunk_idx,
                         STCO_ENTRY *stco_entry
                         )
{
    FILE_POS pos;

    pos = pTrack->m_pChunkOffsetFilePos + (chunk_idx - 1) * sizeof(STCO_ENTRY); //0 based

    MP4FileSetPosition(pTrack->m_pFile, pos);
    stco_entry->chunk_offset_e = MP4FileReadUInt32(pTrack->m_pFile);
}
#endif

#ifdef MP4DEMUX_BUFMODE
FILE_POS MP4TrackGetSampleFileOffset_BufMode(MP4TRACK *pTrack, MP4SampleId sampleId)
{
    FILE_POS sampleFilePos;//, sampleFileOffset;
    MP4SampleId i;//, firstSampleInChunk;
    STCO_ENTRY curr_stco_entry;

    //diag_printf("sampleId:%d\n", sampleId);
    //diag_printf("pTrack->m_cur_sampleID:%d\n", pTrack->m_cur_sampleID);

    if (sampleId >= (pTrack->m_cur_sampleID)) {
        if (sampleId < (pTrack->m_cur_chunkSSID+pTrack->m_cur_SPC)) {
            // case 1: in current chunk
            //diag_printf("in MP4TrackGetSampleFileOffset_BufMode case 1\n");

            // need cumulative samples sizes from firstSample to sampleId - 1
            sampleFilePos = pTrack->m_cur_sampleFilePos;

            if (*(pTrack->m_pStszFixedSampleSizeProperty))
                sampleFilePos += (sampleId - pTrack->m_cur_sampleID) * (*pTrack->m_pStszFixedSampleSizeProperty);
            else {
                for (i = pTrack->m_cur_sampleID; i < sampleId; i++) {
                    sampleFilePos += MP4TrackGetSampleSize(pTrack, i);
                }
            }
            // update current sample data
            pTrack->m_cur_sampleID = sampleId;
            pTrack->m_cur_sampleFilePos = sampleFilePos;

            return sampleFilePos;
        } else if (sampleId < (pTrack->m_next_chunkSSID)) {
            // case 2: in current chunk group that share the same SPC
            // diag_printf("in MP4TrackGetSampleFileOffset_BufMode case 2\n");

            // update current chunk data
            while (sampleId >= (pTrack->m_cur_chunkSSID+pTrack->m_cur_SPC)) {
                pTrack->m_cur_chunkSSID += pTrack->m_cur_SPC;
                pTrack->m_cur_chunkID++;
            }
            GetStcoEntry(pTrack, pTrack->m_cur_chunkID, &curr_stco_entry);
            pTrack->m_cur_chunkFilePos = curr_stco_entry.chunk_offset_e;

            // need cumulative samples sizes from firstSample to sampleId - 1
            sampleFilePos = pTrack->m_cur_chunkFilePos;
            if (*(pTrack->m_pStszFixedSampleSizeProperty))
                sampleFilePos += (sampleId - pTrack->m_cur_chunkSSID) * (*pTrack->m_pStszFixedSampleSizeProperty);
            else {
                for (i = pTrack->m_cur_chunkSSID; i < sampleId; i++) {
                    sampleFilePos += MP4TrackGetSampleSize(pTrack, i);
                }
            }
            // update current sample data
            pTrack->m_cur_sampleID = sampleId;
            pTrack->m_cur_sampleFilePos = sampleFilePos;

            return sampleFilePos;
        } else if (sampleId < (pTrack->m_next_chunkSSID+pTrack->m_next_SPC)) {
            // case 4: next chunk group
            // diag_printf("in MP4TrackGetSampleFileOffset_BufMode case 4\n");
            // update stsc
            pTrack->m_cur_stsc++;
            pTrack->m_cur_chunkSSID = pTrack->m_next_chunkSSID;
            pTrack->m_cur_chunkID = pTrack->m_next_chunkID;
            pTrack->m_cur_chunkFilePos = pTrack->m_next_chunkFilePos;
            pTrack->m_cur_SPC = pTrack->m_next_SPC;

            if (MP4TrackUpdateNextChunkProp(pTrack) != MSMERR_OK)
                return (FILE_POS)-1;

            // need cumulative samples sizes from firstSample to sampleId - 1
            sampleFilePos = pTrack->m_cur_chunkFilePos;
            if (*(pTrack->m_pStszFixedSampleSizeProperty))
                sampleFilePos += (sampleId - pTrack->m_cur_chunkSSID) * (*pTrack->m_pStszFixedSampleSizeProperty);
            else {
                for (i = pTrack->m_cur_chunkSSID; i < sampleId; i++) {
                    sampleFilePos += MP4TrackGetSampleSize(pTrack, i);
                }
            }
            // update current sample data
            pTrack->m_cur_sampleID = sampleId;
            pTrack->m_cur_sampleFilePos = sampleFilePos;

            return sampleFilePos;

        } else {
            // case 3: other chunk group
            // diag_printf("in MP4TrackGetSampleFileOffset_BufMode case 3\n");

            // only test, need further improvement
            sampleFilePos = MP4TrackGetSampleFileOffset_Update(pTrack, sampleId);

            return sampleFilePos;

            // update current and next chunk data
        }

    } else {
        // (sampleId<(pTrack->m_cur_sampleID)), moving backward
        //diag_printf("in MP4TrackGetSampleFileOffset_BufMode case moving backward\n");

        // only test, need further improvement
        sampleFilePos = MP4TrackGetSampleFileOffset_Update(pTrack, sampleId);

        return sampleFilePos;
    }
}

#if 1
FILE_POS MP4TrackGetSampleFileOffset_Update(MP4TRACK *pTrack, MP4SampleId sampleId)
{
    FILE_POS sampleFilePos;
    MP4SampleId i;

    MP4TrackGetSampleStscIndex_BufMode(pTrack, sampleId);

    // chunkOffset is the file offset (absolute) for the start of the chunk
    if (pTrack->m_cur_chunkID > *(pTrack->m_pChunkCountProperty))
        return (FILE_POS)-1;

    // need cumulative samples sizes from firstSample to sampleId - 1
    sampleFilePos = pTrack->m_cur_chunkFilePos;

    if (*(pTrack->m_pStszFixedSampleSizeProperty)) {
        sampleFilePos += (sampleId-pTrack->m_cur_chunkSSID) * (*pTrack->m_pStszFixedSampleSizeProperty);
    } else {
        for (i = pTrack->m_cur_chunkSSID; i < sampleId; i++)
        {
            sampleFilePos += MP4TrackGetSampleSize(pTrack, i);
        }
    }

    // update current sample data
    pTrack->m_cur_sampleID = sampleId;
    pTrack->m_cur_sampleFilePos = sampleFilePos;

    return sampleFilePos;
}
#else
FILE_POS MP4TrackGetSampleFileOffset_Update(MP4TRACK *pTrack, MP4SampleId sampleId)
{
    FILE_POS sampleOffset;
    MP4SampleId i, firstSampleInChunk;
    FILE_POS chunkOffset;
    uint32_t stscIndex;
    uint32_t firstChunk;
    MP4SampleId firstSample;
    uint32_t samplesPerChunk;
    MP4ChunkId chunkId;
    FILE_POS  chunkFilePos;
    STSC_ENTRY next_stsc_entry;
    STCO_ENTRY curr_stco_entry;

    chunkFilePos = pTrack->m_pChunkOffsetFilePos;
    stscIndex = MP4TrackGetSampleStscIndex(pTrack, sampleId);

    //GetStscEntry(pTrack, stscIndex, &curr_stsc_entry);
    pTrack->m_cur_sampleID = sampleId;
    pTrack->m_cur_chunkSSID = pTrack->m_pStscSampleIDPrev; //current chunnk starting sample ID
    //pTrack->m_cur_chunkID = curr_stsc_entry.first_chunk;
    pTrack->m_cur_chunkID = pTrack->m_pStscFirstChunk;
    while (sampleId >= (pTrack->m_cur_chunkSSID+pTrack->m_pStscSamplesPerChunk)) {
        pTrack->m_cur_chunkSSID+=pTrack->m_pStscSamplesPerChunk;
        pTrack->m_cur_chunkID++;
    }
    GetStcoEntry(pTrack, pTrack->m_cur_chunkID, &curr_stco_entry);
    pTrack->m_cur_chunkFilePos = curr_stco_entry.chunk_offset_e;
    pTrack->m_cur_SPC = pTrack->m_pStscSamplesPerChunk; //current samples per chunk

    pTrack->m_cur_stsc = stscIndex-1;
    //stscIndex, already cur+1
    GetStscEntry(pTrack, stscIndex, &next_stsc_entry);
    pTrack->m_next_chunkSSID = pTrack->m_pStscSampleIDNext; //next chunnk starting sample ID
    pTrack->m_next_chunkID = next_stsc_entry.first_chunk;
    GetStcoEntry(pTrack, next_stsc_entry.first_chunk, &curr_stco_entry);
    pTrack->m_next_chunkFilePos = curr_stco_entry.chunk_offset_e;
    pTrack->m_next_SPC = next_stsc_entry.samples_per_chunk; //next samples per chunk

    // firstChunk is the chunk index of the first chunk with
    // samplesPerChunk samples in the chunk.  There may be multiples -
    // ie: several chunks with the same number of samples per chunk.
    firstChunk = pTrack->m_pStscFirstChunk;

    firstSample = pTrack->m_pStscSampleIDPrev;

    samplesPerChunk = pTrack->m_pStscSamplesPerChunk;

    // chunkId tells which is the absolute chunk number that this sample
    // is stored in.
    chunkId = firstChunk + ((sampleId - firstSample) / samplesPerChunk);

    // chunkOffset is the file offset (absolute) for the start of the chunk
    if ((chunkId -1) >= *(pTrack->m_pChunkCountProperty))
        return -1;

    MP4FileSetPosition(pTrack->m_pFile, chunkFilePos + (chunkId - 1) * sizeof(uint32_t));

    chunkOffset = MP4FileReadUInt32(pTrack->m_pFile);

    firstSampleInChunk = sampleId - ((sampleId - firstSample) % samplesPerChunk);

    // need cumulative samples sizes from firstSample to sampleId - 1
    sampleOffset = 0;
    for (i = firstSampleInChunk; i < sampleId; i++)
    {
        sampleOffset += MP4TrackGetSampleSize(pTrack, i);
    }

    pTrack->m_cur_sampleFilePos = chunkOffset + sampleOffset;

    return chunkOffset + sampleOffset;
}
#endif

FILE_POS MP4TrackGetSampleFileOffset_IdxMode(MP4TRACK *pTrack, MP4SampleId sampleId)
{
    FILE_POS sampleFilePos;
    uint32_t stsz_idx;
    MP4SampleId i;
    STSZ_ENTRY curr_stsz_entry;

    stsz_idx = (sampleId - 1) >> 7;

    // need cumulative samples sizes from firstSample to sampleId - 1
    sampleFilePos = *(pTrack->m_stsz_offset + stsz_idx);
    for (i = (stsz_idx << 7) + 1; i < sampleId; i++)
    {
        GetStszEntry(pTrack, i, &curr_stsz_entry);
        sampleFilePos += curr_stsz_entry.sample_size;
    }
    return sampleFilePos;
}
#endif

FILE_POS MP4TrackGetSampleFileOffset(MP4TRACK *pTrack, MP4SampleId sampleId)
{
    FILE_POS sampleOffset;
    MP4SampleId i, firstSampleInChunk;
    uint32_t firstChunk;
    MP4SampleId firstSample;
    uint32_t samplesPerChunk;
    MP4ChunkId chunkId;
    STCO_ENTRY curr_stco_entry;

    MP4TrackGetSampleStscIndex(pTrack, sampleId);

    // firstChunk is the chunk index of the first chunk with
    // samplesPerChunk samples in the chunk.  There may be multiples -
    // ie: several chunks with the same number of samples per chunk.
    firstChunk = pTrack->m_pStscFirstChunk;

    firstSample = pTrack->m_pStscSampleIDPrev;

    samplesPerChunk = pTrack->m_pStscSamplesPerChunk;

    if(!samplesPerChunk)
        return (FILE_POS)-1;
    // chunkId tells which is the absolute chunk number that this sample
    // is stored in.
    chunkId = firstChunk + ((sampleId - firstSample) / samplesPerChunk);

    // chunkOffset is the file offset (absolute) for the start of the chunk
    if (chunkId > *(pTrack->m_pChunkCountProperty))
        return (FILE_POS)-1;

    #if 0
    MP4FileSetPosition(pTrack->m_pFile, chunkFilePos + (chunkId - 1) * sizeof(uint32_t));
    chunkOffset = MP4FileReadUInt32(pTrack->m_pFile);
    #endif
    GetStcoEntry(pTrack, chunkId, &curr_stco_entry);

    firstSampleInChunk = sampleId - ((sampleId - firstSample) % samplesPerChunk);

    // need cumulative samples sizes from firstSample to sampleId - 1
    sampleOffset = 0;
    for (i = firstSampleInChunk; i < sampleId; i++)
    {
        sampleOffset += MP4TrackGetSampleSize(pTrack, i);
    }

    return curr_stco_entry.chunk_offset_e + sampleOffset;
}

#ifdef USE_ATOM_BUFFERRED_READ

static void GetStssEntry(MP4TRACK *pTrack,
                         uint32_t stss_index,
                         STSS_ENTRY *stss_entry
                         )
{
    uint32_t buffer_offset;
    STSSPROP *pstss = (STSSPROP *)pTrack->m_pStssProp; // pTrack->m_pStssProp is not NULL since checking is done on atom init
    uint32_t *curr_page_idx;
    uint8_t *stss_page;

    if (pTrack->m_pStssProp == NULL)
    {
        stss_entry->sync_sample_id = stss_index;
        return;
    }

    //
    // Check the incomming stss index. should be 1 based (sample id)
    //
    if (stss_index > pTrack->m_pStssProp->entry_count)
        stss_index = pTrack->m_pStssProp->entry_count;


    stss_page       = pstss->cache_page;
    curr_page_idx   = &pstss->page_idx;

    if(!stss_page)
    {
        stss_entry->sync_sample_id = stss_index;
        return;
    }

    MP4FileCacheBufferredPage(pTrack->m_pFile, stss_page, curr_page_idx, pTrack->m_pStssProp->entry_file_pos, pstss->table_size,
                              pstss->cache_size, sizeof(STSS_ENTRY), stss_index/*0 based*/, &buffer_offset);

    stss_entry->sync_sample_id = MP4FileReadBufferredUInt32(stss_page, &buffer_offset);
}
#else
static void GetStssEntry(MP4TRACK *pTrack,
                         uint32_t stss_index,
                         STSS_ENTRY *stss_entry
                         )
{
    FILE_POS pos;

    if (pTrack->m_pStssProp == NULL)
        return stss_index;

    //
    // Check the incomming stss index. should be 1 based (sample id)
    //
    if (stss_index > pTrack->m_pStssProp->entry_count)
        stss_index = pTrack->m_pStssProp->entry_count;

    pos = pTrack->m_pStssProp->entry_file_pos+ stss_index*sizeof(STSS_ENTRY);
    MP4FileSetPosition(pTrack->m_pFile, pos);
    stss_entry->sync_sample_id = MP4FileReadUInt32(pTrack->m_pFile);
}
#endif

int MP4TrackGetKeyframeIdx(MP4TRACK *pTrack, uint32_t idx, MP4SampleId *pframeidx)
{
    STSS_ENTRY curr_stss_entry;

    // all frames are key frame
    if (!pTrack->m_pStssProp)
    {
        if (idx > *pTrack->m_pStszSampleCountProperty)
            return MSMERR_DMX_EOF;
#ifdef MP4_MUST_HAVE_STSS
        if (MP4UnifyVideo4cc(pTrack->m_pStsdProp->data_format) != CLIP_VIDEO_TYPE_MJPG)
            return MSMERR_DMX_EOF;
#endif
        *pframeidx = idx + 1; // idx start from 0, MP4SampleId start from 1
        return MSMERR_OK;
    }

    if (idx >= pTrack->m_pStssProp->entry_count)
        return MSMERR_DMX_EOF;

    GetStssEntry(pTrack, idx, &curr_stss_entry);
    *pframeidx = curr_stss_entry.sync_sample_id;

    return MSMERR_OK;
}

//
// try to find the closest keyframe before & after sampleId by searching sync samples
//
MP4SampleId MP4TrackGetKeyFrameBySampleIndex(MP4TRACK *pTrack, MP4SampleId sample_id,
                                             MP4SampleId *prev_key_frame_id)
{
    uint32_t i, entry_count;
    MP4SampleId prev_key_frame = sample_id, key_frame = sample_id;
    STSS_ENTRY curr_stss_entry;

    //
    // return original stss index if stss is not exist
    //
    if (pTrack->m_pStssProp == NULL) {
        if (sample_id > 1)
            *prev_key_frame_id = sample_id-1;
        else
            *prev_key_frame_id = sample_id;

        return sample_id;
    }

    entry_count = pTrack->m_pStssProp->entry_count;

    //
    // every frame is key frame
    //
    if (entry_count == 0) {
        if (sample_id > 1)
            *prev_key_frame_id = sample_id-1;
        else
            *prev_key_frame_id = sample_id;

        return sample_id;
    }

    //
    // maybe binary-search is necessary
    //
    for(i=0; i<entry_count;i++) {
        GetStssEntry(pTrack, i, &curr_stss_entry);
        key_frame = curr_stss_entry.sync_sample_id;

        //sample id is "1" based
        if (key_frame > sample_id){
            //diag_printf("key_frame: %d, prev_key_frame: %d\n", key_frame, prev_key_frame);
            break;
        }

        prev_key_frame = key_frame;
        *prev_key_frame_id = prev_key_frame;
        //diag_printf("key_frame: %d, prev_key_frame: %d\n", key_frame, prev_key_frame);
    }

    return key_frame;
}

/**
 * Get the previous and next key frame (w.r.t pts) for specific time (unit : number), frame index is 1 based
 *
 * input  : pTrack               : track instance
 *          targetTime           : time to seek
 * output : prev_key_frame_id    : the previous key frame index
 * return : the next key frame index
 */
MP4SampleId MP4TrackGetKeyFrameByTime(MP4TRACK *pTrack, MP4Timestamp targetTime, MP4SampleId *prev_key_frame_id)
{
    uint32_t idx_mid, entry_count;
    MP4SampleId key_frame_id;
    STSS_ENTRY curr_stss_entry;
    MP4Timestamp curr_time;
    MP4Duration curr_dur;
    if (pTrack->m_pStssProp == NULL)
    {
        if(MP4TrackGetSampleIndex_byTime(pTrack, targetTime, prev_key_frame_id) == MSMERR_OK)
            return *prev_key_frame_id; // previous and next keyframe are the same
        else
        {
            *prev_key_frame_id = *pTrack->m_pStszSampleCountProperty;
            return MP4TRACK_SEEK_NO_KEYFRAME;
        }
    }
    entry_count = pTrack->m_pStssProp->entry_count;
    if(entry_count == 0) // all samples are key frames
    {
        if(MP4TrackGetSampleIndex_byTime(pTrack, targetTime, prev_key_frame_id) == MSMERR_OK)
            return *prev_key_frame_id; // previous and next keyframe are the same
        else
        {
            *prev_key_frame_id = *pTrack->m_pStszSampleCountProperty;
            return MP4TRACK_SEEK_NO_KEYFRAME;
        }
    }
#if 0
    for (idx_mid = 0; idx_mid < entry_count; idx_mid ++)
    {
        int pts;
        GetStssEntry(pTrack, idx_mid, &curr_stss_entry);
        MP4TrackGetSampleTimes(pTrack, curr_stss_entry.sync_sample_id,&curr_time,&curr_dur);
        pts = (curr_time * 1000 + ((*pTrack->m_pTimeScaleProperty) >> 1)) / (*pTrack->m_pTimeScaleProperty);
        printf("[MP4 KEY] keyframe(%d) idx = %d, pts = %d, size %d\n", idx_mid, curr_stss_entry.sync_sample_id, pts, MP4TrackGetSampleSize(pTrack, curr_stss_entry.sync_sample_id));
    }
#endif
    // check if there is key frame before target time
    GetStssEntry(pTrack, 0, &curr_stss_entry);
    MP4TrackGetSampleTimes(pTrack, curr_stss_entry.sync_sample_id, &curr_time, &curr_dur);
    // StartTime is before the time of the first keyframe
    if(curr_time > targetTime) // can't be >=,  usually the pts of the first keyframe is 0, if StartTime is 0 then prev_key_frame_id will be the first keyframe
    {
        *prev_key_frame_id = MP4TRACK_SEEK_NO_KEYFRAME;
        return curr_stss_entry.sync_sample_id; // key_frame_id = curr_stss_entry.sync_sample_id;
    }

    for (idx_mid = 0; idx_mid < entry_count; idx_mid++)
    {
        GetStssEntry(pTrack, idx_mid, &curr_stss_entry);
        MP4TrackGetSampleTimes_BufMode(pTrack, curr_stss_entry.sync_sample_id, &curr_time,&curr_dur);
        pTrack->m_cur_sampleID = curr_stss_entry.sync_sample_id;
        if (curr_time > targetTime)
        {
            key_frame_id = curr_stss_entry.sync_sample_id;
            GetStssEntry(pTrack, idx_mid - 1, &curr_stss_entry);
            *prev_key_frame_id = curr_stss_entry.sync_sample_id;
            return key_frame_id;
        }
    }
    // if reach here, target time is after the last key frame
    *prev_key_frame_id = curr_stss_entry.sync_sample_id;
    return MP4TRACK_SEEK_NO_KEYFRAME;
}

uint32_t MP4TrackIsSyncSample(MP4TRACK *pTrack, MP4SampleId sampleId)
{
    uint32_t i, entry_count;
    MP4SampleId key_frame;
    STSS_ENTRY curr_stss_entry;

    //
    // return original stss index if stss is not exist
    //
    if (pTrack->m_pStssProp == NULL)
        return 1;

    entry_count = pTrack->m_pStssProp->entry_count;

    //
    // every frame is key frame
    //
    if (entry_count == 0)
        return 1;

    //
    // maybe binary-search is necessary
    //
    for(i = 0; i < entry_count; i++)
    {
        GetStssEntry(pTrack, i, &curr_stss_entry);
        key_frame = curr_stss_entry.sync_sample_id;

        //sample id is "1" based
        if (key_frame == sampleId)
            return 1;

        if (key_frame > sampleId)
            break;
    }

    return 0;
}


#ifdef USE_ATOM_BUFFERRED_READ

FILE_POS GetStscEntry(MP4TRACK *pTrack,
                             uint32_t stsc_index,
                             STSC_ENTRY *stsc_entry
                             )
{
    uint32_t buffer_offset;
    uint8_t *stsc_page;
    uint32_t *curr_page_idx;
    STSCPROP *pstsc = (STSCPROP *)pTrack->m_pStscProp; // pTrack->m_pStscProp is not NULL since checking is done on atom init

    assert(pstsc != NULL);
    stsc_page       = pstsc->cache_page;
    curr_page_idx   = &pstsc->page_idx;
    memset(stsc_entry, 0, sizeof(STSC_ENTRY));

    if(!stsc_page)
        return (FILE_POS)-1;

    //
    // Check the incoming stsc index. should be 0 based
    //
    if (stsc_index > *(pTrack->m_pStscCountProperty))
        stsc_index = *(pTrack->m_pStscCountProperty) - 1;

    MP4FileCacheBufferredPage(pTrack->m_pFile, stsc_page, curr_page_idx, pTrack->m_pStscSampleCurFilePos, pstsc->table_size,
                              pstsc->cache_size, sizeof(STSC_ENTRY), stsc_index/*0 based*/, &buffer_offset);

    stsc_entry->first_chunk = MP4FileReadBufferredUInt32(stsc_page, &buffer_offset);

    stsc_entry->samples_per_chunk = MP4FileReadBufferredUInt32(stsc_page, &buffer_offset);
    if(!stsc_entry->samples_per_chunk)
        return (FILE_POS)-1;

    //stsc_entry->samples_desc_id = MP4FileReadBufferredUInt32(stsc_page, &buffer_offset);

    return 0;
}
#else
FILE_POS GetStscEntry(MP4TRACK *pTrack,
                             uint32_t stsc_index,
                             STSC_ENTRY *stsc_entry
                             )
{
    //
    // Check the incomming stsc index. should be 0 based
    //
    if (stsc_index > *(pTrack->m_pStscCountProperty))
        stsc_index = *(pTrack->m_pStscCountProperty) - 1;

    MP4FileSetPosition(pTrack->m_pFile,pTrack->m_pStscSampleCurFilePos + stsc_index*sizeof(STSC_ENTRY));
    stsc_entry->first_chunk = MP4FileReadUInt32(pTrack->m_pFile);
    stsc_entry->samples_per_chunk = MP4FileReadUInt32(pTrack->m_pFile);
    stsc_entry->samples_desc_id = MP4FileReadUInt32(pTrack->m_pFile);
    return MP4FileGetPosition(pTrack->m_pFile);
}
#endif

#ifdef MP4DEMUX_BUFMODE
int32_t MP4TrackGetSampleStscIndex_BufMode(MP4TRACK *pTrack, MP4SampleId sampleId)
{
    uint32_t stscIndex = 0;
    uint32_t numStscs = *(pTrack->m_pStscCountProperty);
    uint32_t sample_sums = 1;
    STSC_ENTRY curr_stsc_entry, next_stsc_entry;
    STCO_ENTRY curr_stco_entry;

    if (numStscs == 0)
        return -1;

    if (sampleId > pTrack->m_cur_sampleID) {
        stscIndex = pTrack->m_cur_stsc;
    }

    GetStscEntry(pTrack, stscIndex, &curr_stsc_entry);

    if (sampleId > pTrack->m_cur_sampleID) {
        sample_sums = pTrack->m_cur_chunkSSID - (pTrack->m_cur_chunkID - curr_stsc_entry.first_chunk) * curr_stsc_entry.samples_per_chunk;
    }

    stscIndex++;

    for (; stscIndex <= numStscs; stscIndex++) {

        uint32_t tmpsample_sums;

        if (stscIndex == numStscs) {
            next_stsc_entry.first_chunk = *pTrack->m_pChunkCountProperty+1;
            next_stsc_entry.samples_per_chunk = 1;
            tmpsample_sums = sample_sums + ((next_stsc_entry.first_chunk - curr_stsc_entry.first_chunk) * curr_stsc_entry.samples_per_chunk);
        } else {
            GetStscEntry(pTrack, stscIndex, &next_stsc_entry);
            tmpsample_sums = sample_sums + ((next_stsc_entry.first_chunk - curr_stsc_entry.first_chunk) * curr_stsc_entry.samples_per_chunk);
        }

        if (sampleId < tmpsample_sums) {
            pTrack->m_cur_chunkSSID = sample_sums; //current chunk starting sample ID
            pTrack->m_cur_chunkID = curr_stsc_entry.first_chunk;
            while (sampleId >= (pTrack->m_cur_chunkSSID+curr_stsc_entry.samples_per_chunk)) {
                pTrack->m_cur_chunkSSID+=curr_stsc_entry.samples_per_chunk;
                pTrack->m_cur_chunkID++;
            }
            GetStcoEntry(pTrack, pTrack->m_cur_chunkID, &curr_stco_entry);

            pTrack->m_cur_chunkFilePos = curr_stco_entry.chunk_offset_e;
            pTrack->m_cur_SPC = curr_stsc_entry.samples_per_chunk; //current samples per chunk

            pTrack->m_cur_stsc = stscIndex - 1;
            MP4TrackUpdateNextChunkProp(pTrack);
            break;
        }

        sample_sums +=
            ((next_stsc_entry.first_chunk - curr_stsc_entry.first_chunk) * curr_stsc_entry.samples_per_chunk);

        curr_stsc_entry.first_chunk = next_stsc_entry.first_chunk;
        curr_stsc_entry.samples_per_chunk = next_stsc_entry.samples_per_chunk;
    }
    if (stscIndex == (numStscs+1)) {
        stscIndex = numStscs-1;
    }

    return stscIndex;
}
#endif

int32_t MP4TrackGetSampleStscIndex(MP4TRACK *pTrack, MP4SampleId sampleId)
{
    uint32_t stscIndex=0;
    uint32_t numStscs = *(pTrack->m_pStscCountProperty);

    uint32_t cumulative_sample_counts=1;
    STSC_ENTRY curr_first_entry, curr_next_entry;

    if (numStscs == 0)
        return -1;

    GetStscEntry(pTrack, stscIndex, &curr_first_entry);

    for (stscIndex = 0; stscIndex < numStscs; ) {
        //
        //
        //
        pTrack->m_pStscSampleIDPrev = cumulative_sample_counts;
        pTrack->m_pStscFirstChunk = curr_first_entry.first_chunk;
        pTrack->m_pStscSamplesPerChunk = curr_first_entry.samples_per_chunk;
        stscIndex++;

        if (stscIndex < numStscs) {

            //
            // read the next sample-chunk entry
            //
            GetStscEntry(pTrack, stscIndex, &curr_next_entry);

            cumulative_sample_counts +=
                pTrack->m_pStscSamplesPerChunk *
                (curr_next_entry.first_chunk-curr_first_entry.first_chunk);

            curr_first_entry = curr_next_entry;

            pTrack->m_pStscSampleIDNext = cumulative_sample_counts;

            if (sampleId < cumulative_sample_counts) {
                //found the stsc Index
                break;
            }
        }
    }
    if (stscIndex == numStscs) {
        stscIndex -= 1;
    }

    return stscIndex;
}

#ifdef USE_ATOM_BUFFERRED_READ
void GetStszEntry(MP4TRACK *pTrack,
                  MP4SampleId sampleId,
                  STSZ_ENTRY *stsz_entry
                  )
{
    uint32_t buffer_offset;
    STSZPROP *pstsz = (STSZPROP *)pTrack->m_pStszProp; // pTrack->m_pStszProp is not NULL since checking is done on atom init
    uint32_t *curr_page_idx;
    uint8_t *stsz_page;
    uint32_t fixedSampleSize = *(pTrack->m_pStszFixedSampleSizeProperty);

    assert(pstsz != NULL);
    stsz_page       = pstsz->cache_page;
    curr_page_idx   = &pstsz->page_idx;

    if (fixedSampleSize != 0)
    {
        stsz_entry->sample_size = fixedSampleSize;
        return;
    }

    if(!stsz_page)
    {
        stsz_entry->sample_size = 0;
        return;
    }

    MP4FileCacheBufferredPage(pTrack->m_pFile, stsz_page, curr_page_idx, pTrack->m_pStszSampleSizeFilePos, pstsz->table_size,
                              pstsz->cache_size, sizeof(STSZ_ENTRY), (sampleId - 1)/*0 based*/, &buffer_offset);

    stsz_entry->sample_size = MP4FileReadBufferredUInt32(stsz_page, &buffer_offset);
}
#else
void GetStszEntry(MP4TRACK *pTrack,
                  MP4SampleId sampleId,
                  STSZ_ENTRY *stsz_entry
                  )
{
    FILE_POS pos;

    pos = pTrack->m_pStszSampleSizeFilePos + (sampleId - 1) * sizeof(STSZ_ENTRY); //0 based
    MP4FileSetPosition(pTrack->m_pFile, pos);
    stsz_entry->sample_size = MP4FileReadUInt32(pTrack->m_pFile);
}
#endif

uint32_t MP4TrackGetSampleSize(MP4TRACK *pTrack, MP4SampleId sampleId)
{
    STSZ_ENTRY curr_stsz_entry;

    GetStszEntry(pTrack, sampleId, &curr_stsz_entry);

    return curr_stsz_entry.sample_size; //psamplesize[sampleId - 1];
}

#ifdef USE_ATOM_BUFFERRED_READ

void GetSttsEntry(MP4TRACK *pTrack,
                         uint32_t stts_idx,
                         STTS_ENTRY *stts_entry
                         )
{
    uint32_t buffer_offset;
    STTSPROP *pstts = (STTSPROP *)pTrack->m_pSttsProp; // pTrack->m_pSttsProp is not NULL since checking is done on atom init
    uint32_t *curr_page_idx;
    uint8_t *stts_page;

    uint32_t  tmp_sample_duration;

    assert(pstts != NULL);
    stts_page       = pstts->cache_page;
    curr_page_idx   = &pstts->page_idx;

    if(!stts_page)
    {
        stts_entry->sample_count = 0;
        stts_entry->sample_duration = 0;
        return;
    }

    if (stts_idx < pstts->entry_count)
    {
        MP4FileCacheBufferredPage(pTrack->m_pFile, stts_page, curr_page_idx, pTrack->m_pSttsSampleCountFilePos, pstts->table_size,
                                  pstts->cache_size, sizeof(STTS_ENTRY), stts_idx/*0 based*/, &buffer_offset);

        stts_entry->sample_count = MP4FileReadBufferredUInt32(stts_page, &buffer_offset);

        tmp_sample_duration = MP4FileReadBufferredUInt32(stts_page, &buffer_offset);
    }
    else
    {
        // fake for stts beyond scope
        stts_entry->sample_count = 1;
        tmp_sample_duration = 0;
    }
    //avoid sample duration is non-positive number
    if(tmp_sample_duration == 0)
    {
        stts_entry->sample_duration = (33 * *(pTrack->m_pTimeScaleProperty) + 500) / 1000;
        MP4_DBG_MSG("STTS_SD == 0\n");
    }
    else
        stts_entry->sample_duration = tmp_sample_duration;
}
#else
void GetSttsEntry(MP4TRACK *pTrack,
                         uint32_t stts_idx,
                         STTS_ENTRY *stts_entry
                         )
{
    FILE_POS pos;

    pos = pTrack->m_pSttsSampleCountFilePos + stts_idx * sizeof(STTS_ENTRY); //0 based
    MP4FileSetPosition(pTrack->m_pFile, pos);
    stts_entry->sample_count = MP4FileReadUInt32(pTrack->m_pFile);
    stts_entry->sample_duration = MP4FileReadUInt32(pTrack->m_pFile);
}
#endif

#ifdef USE_ATOM_BUFFERRED_READ

void GetCttsEntry(MP4TRACK *pTrack,
                         uint32_t ctts_idx,
                         CTTS_ENTRY *ctts_entry
                         )
{
    uint32_t buffer_offset;
    CTTSPROP *pctts = (CTTSPROP *)pTrack->m_pCttsProp; // pTrack->m_pCttsProp is not NULL since checking is done on atom init
    uint32_t *curr_page_idx;
    uint8_t *ctts_page;

    assert(pctts != NULL);
    ctts_page       = pctts->cache_page;
    curr_page_idx   = &pctts->page_idx;

    if(!ctts_page)
    {
        ctts_entry->sample_count = 0;
        ctts_entry->sample_offset = 0;
        return;
    }

    if (ctts_idx < pctts->entry_count)
    {
        MP4FileCacheBufferredPage(pTrack->m_pFile, ctts_page, curr_page_idx, pTrack->m_pCttsSampleCountFilePos, pctts->table_size,
                                  pctts->cache_size, sizeof(CTTS_ENTRY), ctts_idx/*0 based*/, &buffer_offset);

        ctts_entry->sample_count = MP4FileReadBufferredUInt32(ctts_page, &buffer_offset);
        ctts_entry->sample_offset = MP4FileReadBufferredUInt32(ctts_page, &buffer_offset);
    }
    else
    {
        // fake for stts beyond scope
        ctts_entry->sample_count = 1;
        ctts_entry->sample_offset = 0;
    }
}
#else
void GetCttsEntry(MP4TRACK *pTrack,
                         uint32_t ctts_idx,
                         CTTS_ENTRY *ctts_entry
                         )
{
    FILE_POS pos;

    pos = pTrack->m_pCttsSampleCountFilePos + ctts_idx * sizeof(CTTS_ENTRY); //0 based
    MP4FileSetPosition(pTrack->m_pFile, pos);
    ctts_entry->sample_count = MP4FileReadUInt32(pTrack->m_pFile);
    ctts_entry->sample_duration = MP4FileReadUInt32(pTrack->m_pFile);
}
#endif


#ifdef MP4DEMUX_BUFTIME
void MP4TrackGetSampleTimes_BufMode(MP4TRACK *pTrack, MP4SampleId sampleId,
                                    MP4Timestamp* pStartTime, MP4Duration* pDuration)
{
    uint32_t sttsIndex = 0;
    STTS_ENTRY curr_stts_entry;
    MP4SampleId sid = 0;
    MP4Duration elapsed = 0;
    uint8_t SampleTimeFound = 0;

    if ((sampleId >= (pTrack->m_cur_sampleID)) && (pTrack->m_cur_stts_SSID !=0) ) {
        if (sampleId < pTrack->m_cur_stts_SSID+pTrack->m_cur_stts_size) {
            *pStartTime = pTrack->m_cur_stts_SSTime + (sampleId-pTrack->m_cur_stts_SSID)*pTrack->m_cur_stts_dur;
            *pDuration = pTrack->m_cur_stts_dur;
            SampleTimeFound = 1;
        } else if (sampleId < pTrack->m_next_stts_SSID+pTrack->m_next_stts_size) {
            *pStartTime = pTrack->m_next_stts_SSTime + (sampleId-pTrack->m_next_stts_SSID)*pTrack->m_next_stts_dur;
            *pDuration = pTrack->m_next_stts_dur;
            // update
            pTrack->m_cur_stts_SSID = pTrack->m_next_stts_SSID;
            pTrack->m_cur_stts_SSTime = pTrack->m_next_stts_SSTime;
            pTrack->m_cur_stts = pTrack->m_next_stts;
            pTrack->m_cur_stts_size = pTrack->m_next_stts_size;
            pTrack->m_cur_stts_dur = pTrack->m_next_stts_dur;

            GetSttsEntry(pTrack, pTrack->m_cur_stts+1, &curr_stts_entry);
            pTrack->m_next_stts_SSID = pTrack->m_cur_stts_SSID + pTrack->m_cur_stts_size;
            pTrack->m_next_stts_SSTime = pTrack->m_cur_stts_SSTime + pTrack->m_cur_stts_size * pTrack->m_cur_stts_dur;
            pTrack->m_next_stts = pTrack->m_cur_stts+1;
            pTrack->m_next_stts_size = curr_stts_entry.sample_count;
            pTrack->m_next_stts_dur = curr_stts_entry.sample_duration;
            SampleTimeFound = 1;
        } else {
            // moving far foreward
            sttsIndex = pTrack->m_next_stts+1;
            sid = pTrack->m_next_stts_SSID+pTrack->m_next_stts_size;
            elapsed = pTrack->m_next_stts_SSTime + pTrack->m_next_stts_size * pTrack->m_next_stts_dur;

            //continue to update
        }
    } else {
        //moving backward
        sttsIndex = 0;
        sid = 1;
        elapsed = 0;

        //continue to update
    }

    if (!SampleTimeFound)
    {
        MP4TrackGetSampleTimes_BufMode_Update(pTrack, sampleId, sttsIndex, sid, elapsed,
                                              pStartTime, pDuration);
    }


    if (pTrack->m_pCttsCountProperty)
    {
        uint32_t numCtts = *(pTrack->m_pCttsCountProperty);
        if (numCtts == 1)
            DtsToCts(pTrack, pStartTime, sampleId);
        else if (numCtts > 1)
            DtsToCts_BufMode(pTrack, pStartTime, sampleId);
    }
}

void MP4TrackGetSampleTimes_BufMode_Update(MP4TRACK *pTrack, MP4SampleId sampleId,
                                           uint32_t start_stscIndex, MP4SampleId start_sid, MP4Duration start_elapsed,
                                           MP4Timestamp *pStartTime, MP4Duration *pDuration)
{
    uint32_t numStts = *pTrack->m_pSttsCountProperty;
    STTS_ENTRY curr_stts_entry;

    for (; start_stscIndex < numStts; start_stscIndex++)
    {
        GetSttsEntry(pTrack, start_stscIndex, &curr_stts_entry);

        if (sampleId < start_sid + curr_stts_entry.sample_count)
        {
            if (pStartTime)
                *pStartTime = start_elapsed + (sampleId - start_sid) * (MP4Duration)curr_stts_entry.sample_duration;
            if (pDuration)
                *pDuration = curr_stts_entry.sample_duration;

            // update
            pTrack->m_cur_stts_SSID = start_sid;
            pTrack->m_cur_stts_SSTime = start_elapsed;
            pTrack->m_cur_stts = start_stscIndex;
            pTrack->m_cur_stts_size = curr_stts_entry.sample_count;
            pTrack->m_cur_stts_dur = curr_stts_entry.sample_duration;

            GetSttsEntry(pTrack, pTrack->m_cur_stts+1, &curr_stts_entry);
            pTrack->m_next_stts_SSID = pTrack->m_cur_stts_SSID + pTrack->m_cur_stts_size;
            pTrack->m_next_stts_SSTime = pTrack->m_cur_stts_SSTime + pTrack->m_cur_stts_size * pTrack->m_cur_stts_dur;
            pTrack->m_next_stts = pTrack->m_cur_stts+1;
            pTrack->m_next_stts_size = curr_stts_entry.sample_count;
            pTrack->m_next_stts_dur = curr_stts_entry.sample_duration;
            return;
        }
        start_sid += curr_stts_entry.sample_count;
        start_elapsed += curr_stts_entry.sample_count * (MP4Duration)curr_stts_entry.sample_duration;
    }

    // current sample ID is larger than stts table entry count
    if (pStartTime)
        *pStartTime = start_elapsed;
    if (pDuration)
        *pDuration = 0;
}

#endif

void MP4TrackGetSampleTimes(MP4TRACK *pTrack, MP4SampleId sampleId,
    MP4Timestamp* pStartTime, MP4Duration* pDuration)
{
    uint32_t numStts = *(pTrack->m_pSttsCountProperty);
    MP4SampleId sid = 1;
    MP4Duration elapsed = 0;
    uint32_t sttsIndex, sampleCount=0, sampleDelta=0;
    STTS_ENTRY curr_stts_entry;

    assert(pStartTime && pDuration);

    *pStartTime = *pDuration = 0;
    //only re-read each time duration when numstts != 1
    if(numStts == 1) {
        sampleCount = *pTrack->m_pSttsSampleCountProperty;
        sampleDelta = *pTrack->m_pSttsSampleDeltaProperty;
    }

    for (sttsIndex = 0; sttsIndex < numStts; sttsIndex++) {
        if (numStts != 1) {
            //diag_printf("MP4TrackGetSampleTimes\n");
            GetSttsEntry(pTrack, sttsIndex, &curr_stts_entry);

            sampleCount = curr_stts_entry.sample_count;
            sampleDelta = curr_stts_entry.sample_duration;
        }

        if (sampleId <= sid + sampleCount - 1)
        {
            *pStartTime = (sampleId - sid);
            *pStartTime *= sampleDelta;
            *pStartTime += elapsed;
            //diag_printf("set pStartTime:%lld\n", *pStartTime);
            *pDuration = sampleDelta;
            //diag_printf("set pDuration:%d\n", *pDuration);
            break;
        }
        sid += sampleCount;
        elapsed += sampleCount * (MP4Duration)sampleDelta;
    }

    /* for the case that sampleId is larger than entry count of STTS, PR116799*/
    if ((*pStartTime == 0) && (sttsIndex == numStts))
    {
        *pStartTime = elapsed;
        *pDuration = 0;
    }

    if (pTrack->m_pCttsCountProperty)
    {
        uint32_t numCtts = *(pTrack->m_pCttsCountProperty);
        if (numCtts == 1)
            DtsToCts(pTrack, pStartTime, sampleId);
        else if (numCtts > 1)
            DtsToCts_BufMode(pTrack, pStartTime, sampleId);
    }
}

//#define DEBUG_SAMPLEID
int MP4TrackGetSampleIndex_byTime(MP4TRACK *pTrack, MP4Timestamp StartTime, MP4SampleId *sampleId)
{

    uint32_t numStts = *(pTrack->m_pSttsCountProperty);
    MP4Timestamp currTime;
    MP4SampleId  advance_count;
    STTS_ENTRY curr_stts_entry;
    uint32_t sttsIndex;
    MP4SampleId sid;
    MP4Duration elapsed;
    int found = 0;


    // (timescale/sample duration) == fps
    // pStarTime is the same unit of m_cur_stts_dur
    // *(pTrack->m_pStszSampleCountProperty) is total frame number.

    currTime = pTrack->m_cur_stts_SSTime + (pTrack->m_cur_sampleID - pTrack->m_cur_stts_SSID)*pTrack->m_cur_stts_dur;

    //diag_printf("SS_time:%lld,SSID:%d,Cur_ID:%d,Curr_T:%lld,Tar_T:%lld,S_Dur:%d!\n",pTrack->m_cur_stts_SSTime ,pTrack->m_cur_stts_SSID,pTrack->m_cur_sampleID,currTime, pStartTime, pTrack->m_cur_stts_dur);
    //diag_printf("in Cur_T:%lld,S_T:%lld!,T_S:%d!\n",currTime,pStartTime,(*(pTrack->m_pTimeScaleProperty)));
    //diag_printf("c_stts:%d,numStts:%d,stsz_count:%d\n",pTrack->m_cur_stts,numStts,*(pTrack->m_pStszSampleCountProperty));
    if ((StartTime > currTime) &&
        (!((pTrack->m_next_stts == pTrack->m_cur_stts) && (pTrack->m_cur_stts == 0))) )
    {
        if (StartTime < pTrack->m_cur_stts_SSTime + pTrack->m_cur_stts_size*pTrack->m_cur_stts_dur)
        {
            advance_count = (StartTime - pTrack->m_cur_stts_SSTime)/pTrack->m_cur_stts_dur;

            if (pTrack->m_cur_stts_SSTime + advance_count*pTrack->m_cur_stts_dur < StartTime)
                advance_count++;

            *sampleId = pTrack->m_cur_stts_SSID + advance_count;
            found = *sampleId < *(pTrack->m_pStszSampleCountProperty);

            #ifdef DEBUG_SAMPLEID
            {
                MP4Timestamp start_time,duration;
                MP4TrackGetSampleTimes(pTrack, *sampleId, &start_time, &duration);
                diag_printf("Tar_T:%lld,Tar_ID:%d,S_T:%lld,D:%lld,T_F:%d!\n",StartTime,*sampleId,start_time,duration,total_frame_num);
            }
            #endif

            //return;
            goto STTS_RESTORE;
        }
        else if(StartTime < pTrack->m_next_stts_SSTime + pTrack->m_next_stts_size*pTrack->m_next_stts_dur)
        {
            advance_count = (StartTime - pTrack->m_next_stts_SSTime)/pTrack->m_next_stts_dur;

            if (pTrack->m_next_stts_SSTime + advance_count*pTrack->m_next_stts_dur < StartTime)
                advance_count++;

            *sampleId = pTrack->m_next_stts_SSID + advance_count;
            found = *sampleId < *(pTrack->m_pStszSampleCountProperty);

            // update
            pTrack->m_cur_stts_SSID = pTrack->m_next_stts_SSID;
            pTrack->m_cur_stts_SSTime = pTrack->m_next_stts_SSTime;
            pTrack->m_cur_stts = pTrack->m_next_stts;
            pTrack->m_cur_stts_size = pTrack->m_next_stts_size;
            pTrack->m_cur_stts_dur = pTrack->m_next_stts_dur;

            GetSttsEntry(pTrack, pTrack->m_cur_stts+1, &curr_stts_entry);
            pTrack->m_next_stts_SSID = pTrack->m_cur_stts_SSID + pTrack->m_cur_stts_size;
            pTrack->m_next_stts_SSTime = pTrack->m_cur_stts_SSTime + pTrack->m_cur_stts_size * pTrack->m_cur_stts_dur;
            pTrack->m_next_stts = pTrack->m_cur_stts+1;
            pTrack->m_next_stts_size = curr_stts_entry.sample_count;
            pTrack->m_next_stts_dur = curr_stts_entry.sample_duration;

            #ifdef DEBUG_SAMPLEID
            {
                MP4Timestamp start_time,duration;
                MP4TrackGetSampleTimes(pTrack, *sampleId, &start_time, &duration);
                diag_printf("Tar_T:%lld,Tar_ID:%d,S_T:%lld,D:%lld,T_F:%d!\n",StartTime,*sampleId,start_time,duration,total_frame_num);
            }
            #endif

            //return;
            goto STTS_RESTORE;
        }
        else
        {
            // moving far forward
            sttsIndex = pTrack->m_next_stts+1;
            sid = pTrack->m_next_stts_SSID+pTrack->m_next_stts_size;
            elapsed = pTrack->m_next_stts_SSTime + pTrack->m_next_stts_size * pTrack->m_next_stts_dur;
        }
    }
    else
    {
        //moving backward
        sttsIndex = 0;
        sid = 1;
        elapsed = 0;
    }

    for (; sttsIndex < numStts; sttsIndex++) {

        GetSttsEntry(pTrack, sttsIndex, &curr_stts_entry);

        //diag_printf("pS_T:%lld,sam_count:%d,sam_D:%d,sttsIdx:%d,numStts:%d\n",pStartTime,curr_stts_entry.sample_count,curr_stts_entry.sample_duration,sttsIndex,numStts);

        if (StartTime < elapsed + curr_stts_entry.sample_count * (MP4Duration)curr_stts_entry.sample_duration) {

            // update
            pTrack->m_cur_stts_SSID = sid;
            pTrack->m_cur_stts_SSTime = elapsed;
            pTrack->m_cur_stts = sttsIndex;
            pTrack->m_cur_stts_size = curr_stts_entry.sample_count;
            pTrack->m_cur_stts_dur = curr_stts_entry.sample_duration;

            GetSttsEntry(pTrack, pTrack->m_cur_stts+1, &curr_stts_entry);
            pTrack->m_next_stts_SSID = pTrack->m_cur_stts_SSID + pTrack->m_cur_stts_size;
            pTrack->m_next_stts_SSTime = pTrack->m_cur_stts_SSTime + pTrack->m_cur_stts_size * pTrack->m_cur_stts_dur;
            pTrack->m_next_stts = pTrack->m_cur_stts+1;
            pTrack->m_next_stts_size = curr_stts_entry.sample_count;
            pTrack->m_next_stts_dur = curr_stts_entry.sample_duration;

            //get video index
            advance_count = (StartTime - pTrack->m_cur_stts_SSTime)/pTrack->m_cur_stts_dur;

            if (pTrack->m_cur_stts_SSTime + advance_count*pTrack->m_cur_stts_dur < StartTime)
                advance_count++;

            *sampleId = pTrack->m_cur_stts_SSID + advance_count;
            found = *sampleId < *(pTrack->m_pStszSampleCountProperty);

            #ifdef DEBUG_SAMPLEID
            {
                MP4Timestamp start_time,duration;
                MP4TrackGetSampleTimes(pTrack, *sampleId, &start_time, &duration);
                diag_printf("Tar_T:%lld,Tar_ID:%d,S_T:%lld,D:%lld,T_F:%d!\n",StartTime,*sampleId,start_time,duration,total_frame_num);
            }
            #endif

            //return;
            goto STTS_RESTORE;
        }
        sid += curr_stts_entry.sample_count;
        elapsed += curr_stts_entry.sample_count * (MP4Duration)curr_stts_entry.sample_duration;
    }

STTS_RESTORE:
    //Always restore to 1st frame cache after time-index seeking
    //This can ensure "MP4TrackGetSampleTimes_BufMode" get correct values after seek
    sttsIndex = 0;
    sid = 1;
    elapsed = 0;

    MP4TrackGetSampleTimes_BufMode_Update(pTrack, 1, sttsIndex, sid, elapsed,
                                          NULL, NULL);
    #ifdef DEBUG_SAMPLEID
    {
        diag_printf("No match SampleID!\n");
    }
    #endif

    if (found)
        return MSMERR_OK;

    return MSMERR_DMX_EOF;
}

void MP4TrackGetWidthHeight(MP4TRACK *pTrack, int *width, int *height)
{
    *width  = pTrack->m_pStsdProp->u.v_desc.stream_width;
    *height = pTrack->m_pStsdProp->u.v_desc.stream_height;

    if (*width == 0)
        *width = pTrack->stream_width;

    if (*height == 0)
        *height = pTrack->stream_height;
}

void MP4TrackGetSampleRate(MP4TRACK *pTrack, uint32_t *samplerate)
{
    *samplerate = pTrack->m_pStsdProp->u.a_desc.samplerate;

    if (*samplerate == 0)
        *samplerate = *pTrack->m_pTimeScaleProperty;
}

void MP4TrackGetConfig(MP4TRACK *pTrack, uint8_t **config, uint32_t *config_len)
{
    *config = 0;
    *config_len = 0;

    if (pTrack->m_pESDSProp)
    {
        *config_len = pTrack->m_pESDSProp->decoder_cfg_len;
        *config     = pTrack->m_pESDSProp->decoder_cfg;
    }
    else if (pTrack->m_pStsdProp && pTrack->m_TrackType == MVC_STREAM_AUDIO)
    {
        *config_len = pTrack->m_pStsdProp->decoder_cfg_len;
        *config     = pTrack->m_pStsdProp->decoder_cfg;
    }
    else if (pTrack->m_pavcCProp && pTrack->m_TrackType == MVC_STREAM_VIDEO)
    {
        *config_len = pTrack->m_pavcCProp->decoder_cfg_len;
        *config     = pTrack->m_pavcCProp->decoder_cfg;
    }
    else if (pTrack->m_pavssProp && pTrack->m_TrackType == MVC_STREAM_VIDEO)
    {
        *config_len = pTrack->m_pavssProp->decoder_cfg_len;
        *config     = pTrack->m_pavssProp->decoder_cfg;
    }
    else if (pTrack->m_phevcProp && pTrack->m_TrackType == MVC_STREAM_VIDEO)
    {
        *config_len = pTrack->m_phevcProp->decoder_cfg_len;
        *config     = pTrack->m_phevcProp->decoder_cfg;
    }
}

