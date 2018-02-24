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


#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "mp4demux.h"
#include "mp4m.h"
#include "mp4util.h"
#include "kmv_api.h"
#include "dmxinst.h"
#include "mp4file.h"
#include "mp4def.h"
#include "mp4track.h"
#include "msmComm.h"
#ifdef MIPSDEV
#include "functable.h"
#endif

#ifndef USE_M263_TAG
#define USE_M263_TAG 0
#endif
//-----------------------------------------------------------------------------
//extern Variables or functions
//-----------------------------------------------------------------------------
extern int MP4TrackGetSampleIndex_byTime(MP4TRACK *pTrack, MP4Timestamp StartTime, MP4SampleId *sampleId);
extern void GetSttsEntry(MP4TRACK *pTrack, uint32_t stts_idx, STTS_ENTRY *stts_entry);
extern void DtsToCts_BufMode (MP4TRACK *pTrack, MP4Timestamp* pStartTime, MP4SampleId sampleId);
extern uint32_t MP4TrackGetSampleSize(MP4TRACK *pTrack, MP4SampleId sampleId);
extern MP4SampleId MP4TrackGetKeyFrameByTime(MP4TRACK *pTrack, MP4Timestamp StartTime, MP4SampleId *prev_key_frame_id);
extern void MP4TrackGetSampleFileOffset_BufModeInit(MP4TRACK *pTrack);
extern void MP4TrackGetSampleFileOffset_IdxModeInit(void *ctx, MP4TRACK *pTrack);
extern FILE_POS MP4TrackGetSampleFileOffset_BufMode(MP4TRACK *pTrack, MP4SampleId sampleId);
extern FILE_POS MP4TrackGetSampleFileOffset_IdxMode(MP4TRACK *pTrack, MP4SampleId sampleId);
extern void MP4TrackGetSampleTimes_BufMode_Update(MP4TRACK *pTrack, MP4SampleId sampleId,
                                           uint32_t start_stscIndex, MP4SampleId start_sid, MP4Duration start_elapsed,
                                           MP4Timestamp *pStartTime, MP4Duration *pDuration);
extern int MP4TrackIsStsdUncompSample(MP4TRACK *pTrack);
extern int MP4TrackGetKeyframeIdx(MP4TRACK *pTrack, uint32_t idx, MP4SampleId *pframeidx);
static void MP4DMX_GetAvgBitrate(MP4TRACK *pTrack, uint32_t *AveBitrate);
static void MP4DMX_GetAudioSampleRate(MP4TRACK *pTrack, uint32_t *samplerate);
static void MP4DMX_GetFramerate(MP4TRACK *pTrack, uint32_t *avg_framerate);
//-----------------------------------------------------------------------------

static void mp4dmx_buf_mode_reset(MP4TRACK *pTrack)
{
    if (!pTrack)
        return;

    MP4TrackGetSampleTimes_BufMode_Update(pTrack, 1, 0, 1, 0, NULL, NULL);
    // if we use ctts cache mode, reset ctts cache
    if (pTrack->m_pCttsCountProperty && *pTrack->m_pCttsCountProperty > 1)
        DtsToCts_BufMode(pTrack, 0, 1);
    if (*(pTrack->m_pStscCountProperty) > 1)
        MP4TrackGetSampleFileOffset_BufModeInit(pTrack);
}

int MP4DMX_Open2(
        void **ppInst,
        unsigned char *heap_base,
        unsigned int heap_size,
        struct cb_io_s *cbio,
        int ringbuf_size, const mvc_callback_st *callback,
        uint32_t table_cache_size)
{
    MP4DMXInst *pInst;
    mp4_heap_st heap;
    uint32_t i;
    MP4FILE *pFile;
    MP4TRACK *pTrack, *pvtrack = 0;
    int vid_selected = 0, aud_selected = 0;
#ifdef SUPPORT_SUBTITLE
    int sub_selected = 0;
#endif

    // init mem sharing pool address
    mdxInit(&heap, heap_base, heap_size);

    *ppInst = 0;
    // init
    pInst = mdxalloc(&heap, sizeof(MP4DMXInst));

    if (!pInst) return MSMERR_OUT_OF_MEMORY;

    memset((void*)pInst, 0, sizeof(MP4DMXInst));

    pInst->m_mp4File = MP4Open(&heap, cbio, ringbuf_size, callback);
    pFile = pInst->m_mp4File;

    if (!pInst->m_mp4File) {
        MP4_DBG_MSG("Open 3gp file failed\n");
        mdxfree(&heap, pInst);
        //diag_printf("Open 3gp file failed\n");
        return MSMERR_DMX_OPEN_FAILED;
    }

    pFile->table_cache_size = table_cache_size;

    if (!MP4Read(&heap, pInst->m_mp4File)) {
        MP4_DBG_MSG("Read 3gp file failed\n");
        MP4Close(&heap, pInst->m_mp4File);
        mdxfree(&heap, pInst);
        //diag_printf("Open/Read 3gp file failed\n");
        return MSMERR_DMX_VDO_READ_INVLD;
    }

    pInst->m_numTracks = MP4GetNumberOfTracks(pFile);
    pInst->m_active_audio = pInst->m_active_video = pInst->m_active_subtitle = -1;

    if (!pInst->m_numTracks)
    {
        MP4_DBG_MSG("No track in thie file\n");
        MP4Close(&heap, pInst->m_mp4File);
        mdxfree(&heap, pInst);
        return MSMERR_DMX_OPEN_FAILED;
    }

    MP4_DBG_MSG("Number of tracks = %d\n", pInst->m_numTracks);

    for (i = 0; i< pInst->m_numTracks; i++)
    {
        pTrack = MP4TracksGet(&pFile->m_pTracks, i);

        if (!pTrack) continue;

        if (*(pTrack->m_pStscCountProperty) > 1)
            MP4TrackGetSampleFileOffset_BufModeInit(pTrack);
        else if (*(pTrack->m_pChunkCountProperty) == 1)
            MP4TrackGetSampleFileOffset_IdxModeInit(&heap, pTrack);

        if (pTrack->m_TrackType == MVC_STREAM_VIDEO)
        {
            if (!vid_selected)
            {
                pTrack->need_deliver_config = 1;
                pvtrack               = pTrack;
                pInst->m_pVTrack      = pTrack;
                pInst->m_numVSamples  = *pTrack->m_pStszSampleCountProperty;
                pInst->m_VTimeScale   = *pTrack->m_pTimeScaleProperty;
                pInst->m_active_video = i;
                vid_selected = 1;
            }
            MP4DMX_GetFramerate(pTrack, &pTrack->frame_rate);
            MP4DMX_GetAvgBitrate(pTrack, &pTrack->avg_bitrate);
#if USE_M263_TAG
            // for h263 hw I frame only CIF format
            if (pTrack->m_pStsdProp->data_format == CODEC_TYPE_4CC('s','2','6','3') && pTrack->legal_vendor)
            {
                // replace stsd data format as specific one 'm263' for recorded CIF clip
                pTrack->m_pStsdProp->data_format = CODEC_TYPE_4CC('m','2','6','3');
            }
#endif
            // fixed for mp2v with wrong data format in stsd.
            if (pTrack->m_pESDSProp != NULL &&
                (pTrack->m_pESDSProp->object_type_id == MP4_OBJECT_TYPE_ID_ISO11172_2 ||
                 pTrack->m_pESDSProp->object_type_id == MP4_OBJECT_TYPE_ID_ISO13818_2_SP ||
                 pTrack->m_pESDSProp->object_type_id == MP4_OBJECT_TYPE_ID_ISO13818_2_MP))
                pTrack->m_pStsdProp->data_format = CODEC_TYPE_4CC('m','p','2','v');
        }
        else if (pTrack->m_TrackType == MVC_STREAM_AUDIO)
        {
            unsigned char object_type_id = 0;

            if (!aud_selected)
            {
                pTrack->need_deliver_config = 1;
                pInst->m_pATrack      = pTrack;
                pInst->m_numASamples  = *pTrack->m_pStszSampleCountProperty;
                pInst->m_ATimeScale   = *pTrack->m_pTimeScaleProperty;
                pInst->m_active_audio = i;
                aud_selected = 1;
            }
            MP4DMX_GetAudioSampleRate(pTrack, &pTrack->sample_rate);
            MP4DMX_GetAvgBitrate(pTrack, &pTrack->avg_bitrate);
            if (pTrack->m_pESDSProp)
                object_type_id = pTrack->m_pESDSProp->object_type_id;
            //Sean_add : temp solution
            if (object_type_id == MP4_OBJECT_TYPE_MP3 || object_type_id == MP4_OBJECT_TYPE_MP2)
                pTrack->m_pStsdProp->data_format = CODEC_TYPE_4CC('m','p','3','a');
            if (object_type_id == MP4_OBJECT_TYPE_VORBIS)
                pTrack->m_pStsdProp->data_format = CODEC_TYPE_4CC('v','r','b','s');

            if (*pTrack->m_pStszFixedSampleSizeProperty != 0 &&
                (pTrack->m_pStsdProp->data_format == CODEC_TYPE_4CC('m','s', 0, 0x55) || MP4AudioFormatToTag(pTrack->m_pStsdProp->data_format) != 0))
            {
                // \\mspc5617\clips\mp4\mp4_pcm\0x55\Clip 04_CD.mov
                // even if "ms 0 0x55" is mp3, we need to combine packet
                pTrack->pcm_chk_read = 1;
            }
        }
#ifdef SUPPORT_SUBTITLE
        else if (pTrack->m_TrackType == MVC_STREAM_SUBTITLE && !sub_selected)
        {
            sub_selected = 1;
            pTrack->need_deliver_config = 1;
            pInst->m_active_subtitle = i;
            pInst->m_pSTrack         = pTrack;
            pInst->m_numSubSamples   = *pTrack->m_pStszSampleCountProperty;
            pInst->m_SubTimeScale    = *pTrack->m_pTimeScaleProperty;
        }
#endif
    }

    if (pvtrack)
    {
        // if there is only one I frame, the clip is not seekable
        // according to spec pvtrack->m_pStssProp == NULL means every sample is I frame
        if (pvtrack->m_pStssProp && pvtrack->m_pStssProp->entry_count == 1)
            pInst->m_seekable = 0;
        else
            pInst->m_seekable = 1;
#ifdef MP4_MUST_HAVE_STSS
        if (pInst->m_seekable && !pvtrack->m_pStssProp)
        {
            // do not allow seek when there is no index table unless codec is MJPG to avoid seek for IPPP case
            // mantis 350946, align vdplayer
            pInst->m_seekable = MP4UnifyVideo4cc(pvtrack->m_pStsdProp->data_format) == CLIP_VIDEO_TYPE_MJPG;
        }
#endif
    }
    else
    {
        // there is audio only clip, thus it should be seekable
        pInst->m_seekable = 1;
    }

    pInst->m_numVideoTracks = pFile->m_numVideoTracks;
    pInst->m_numAudioTracks = pFile->m_numAudioTracks;
#ifdef SUPPORT_SUBTITLE
    pInst->m_numSubtitleTracks = pFile->m_numSubtitleTracks;
#endif
    pInst->m_heap_ctx = heap;
    *ppInst = pInst;

    return MSMERR_OK;
}

int MP4DMX_Open(void **ppInst, unsigned char *heap, unsigned int heap_size,
                       struct cb_io_s *cbio, int ringbuf_size, const mvc_callback_st *callback)
{
    return MP4DMX_Open2(ppInst, heap, heap_size, cbio, ringbuf_size, callback, 0);
}

int MP4DMX_ReadSample(void *pInst, uint32_t frameidx, uint32_t *pnSize,
                      uint32_t *is_sync_sample, mvc_stream_type_et track_type)
{
    MP4DMXInst *pDmx = (MP4DMXInst *) pInst;
    int errRtl;
    MP4Timestamp Start;
    MP4Duration Duration;
    MP4FILE *pFile = (MP4FILE *) pDmx->m_mp4File;
    uint32_t numBytes;
    uint32_t num_samples, kmv_type = KMV_NOT_KMV;
    struct tagMP4Track *pTrack;

    *pnSize = 0;
    if (track_type == MVC_STREAM_VIDEO)
    {
        num_samples = pDmx->m_numVSamples;
        kmv_type    = pDmx->m_KMV_type;
        pTrack      = pDmx->m_pVTrack;
    }
#ifdef SUPPORT_SUBTITLE
    else if (track_type == MVC_STREAM_SUBTITLE)
    {
        num_samples = pDmx->m_numSubSamples;
        pTrack      = pDmx->m_pSTrack;
    }
#endif
    else
    {
        assert(track_type == MVC_STREAM_AUDIO);
        num_samples = pDmx->m_numASamples;
        pTrack      = pDmx->m_pATrack;
    }

    // deliver config data if it is not delivered yet
    if (pDmx->m_active_audio != -1)
        MP4TrackDeliverConfig(pDmx->m_pATrack, KMV_NOT_KMV);
    if (pDmx->m_active_video != -1)
        MP4TrackDeliverConfig(pDmx->m_pVTrack, pDmx->m_KMV_type);
    if (pDmx->m_active_subtitle != -1)
        MP4TrackDeliverConfig(pDmx->m_pSTrack, KMV_NOT_KMV);

    if (frameidx <= 0)
        return MSMERR_DMX_VDO_IDX_INVLD;

    if (frameidx > num_samples)
    {
        // TODO: use the same behavior of other demuxer, EOF should be the last packet
        // subtitle does not care end packet
        if (pTrack->m_TrackType != MVC_STREAM_SUBTITLE)
            pFile->callback.notify(pFile->callback.context, track_type, MVC_EVENT_EOS);
        return MSMERR_DMX_EOF;
    }

    errRtl = MP4TrackReadSample(pTrack, frameidx, &numBytes, &Start, &Duration,
                                is_sync_sample, kmv_type);

    if (errRtl != MSMERR_OK)
    {
        if (errRtl != MSMERR_OUT_OF_MEMORY && errRtl != MSMERR_DMX_RETRY)
        {
            pFile->callback.notify(pFile->callback.context, MVC_STREAM_VIDEO, MVC_EVENT_EOS);
            pFile->callback.notify(pFile->callback.context, MVC_STREAM_AUDIO, MVC_EVENT_EOS);
        }
        return errRtl;
    }

    // update the read size
    *pnSize = numBytes;

    return errRtl;
}

int MP4DMX_ReadSampleInfo(void *pInst, uint32_t frameidx, cb_fpos *pOffset, uint32_t *pnSize,
                     uint64_t *pStart, uint64_t *pDuration, uint32_t *is_sync_sample,
                     mvc_stream_type_et track_type)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    int errRtl;
    MP4Timestamp Start;
    MP4Duration Duration;
    uint64_t track_total_samples;
    uint32_t track_time_scale;
    struct tagMP4Track *pTrack;

    if (pnSize)
        *pnSize = 0;
    if (track_type == MVC_STREAM_VIDEO)
    {
        track_total_samples = pDmx->m_numVSamples;
        track_time_scale = pDmx->m_VTimeScale;
        pTrack  = pDmx->m_pVTrack;
    }
    else if (track_type == MVC_STREAM_AUDIO)
    {
        track_total_samples = pDmx->m_numASamples;
        track_time_scale = pDmx->m_ATimeScale;
        pTrack  = pDmx->m_pATrack;
    }
#ifdef SUPPORT_SUBTITLE
    else if (track_type == MVC_STREAM_SUBTITLE)
    {
        track_total_samples = pDmx->m_numSubSamples;
        track_time_scale = pDmx->m_SubTimeScale;
        pTrack  = pDmx->m_pSTrack;
    }
#endif
    else
        return MSMERR_DMX_VDO_IDX_INVLD;

    if (frameidx <= 0)
        return MSMERR_DMX_VDO_IDX_INVLD;

    if (frameidx > track_total_samples)
        return MSMERR_DMX_EOF;

    errRtl = MP4TrackReadSampleInfo(pTrack, frameidx, pOffset, pnSize, &Start, &Duration,
                                    is_sync_sample);

    if (errRtl != MSMERR_OK)
    {
        return errRtl;
    }

    // remove float usage but it may have problem, move x1000 to calc before divide operator
    // You need to use fixed point calculation
    //
    if (pStart)
        *pStart = (uint64_t)((Start * 1000 + (track_time_scale/2)) / track_time_scale);
    if (pDuration)
        *pDuration = (uint64_t)( (Duration * 1000 + (track_time_scale/2)) / track_time_scale);

    return errRtl;
}

void MP4DMX_Close(void *pInst)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;

    if (pDmx) {
        MP4Close(&pDmx->m_heap_ctx,pDmx->m_mp4File);
        mdxfree(&pDmx->m_heap_ctx, pDmx);
    }
}

static void MP4DMX_GetDuration(void *pInst, uint64_t *pU64TotalTime)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4TRACK *pV_Track;
    MP4TRACK *pA_Track;
    MP4Duration V_Duration = 0;
    MP4Duration A_Duration = 0;

    pV_Track = pDmx->m_pVTrack;
    pA_Track = pDmx->m_pATrack;

    if (pA_Track)
    {
        if (pA_Track->m_pMediaDurationProperty && pA_Track->m_pTimeScaleProperty)
        {
            if (*pA_Track->m_pTimeScaleProperty > 0)
                A_Duration = *pA_Track->m_pMediaDurationProperty * 1000 / *pA_Track->m_pTimeScaleProperty * 1000;
        }
    }

    if (pV_Track)
    {
        if (pV_Track->m_pMediaDurationProperty && pV_Track->m_pTimeScaleProperty)
        {
            if (*pV_Track->m_pTimeScaleProperty > 0)
                V_Duration = *pV_Track->m_pMediaDurationProperty * 1000 / *pV_Track->m_pTimeScaleProperty * 1000;
        }
    }

    if (A_Duration > V_Duration)
        *pU64TotalTime = A_Duration;
    else
        *pU64TotalTime = V_Duration;

}

int MP4DMX_GetVideoKeyFrameIdx(void *pInst, uint32_t idx, uint32_t *pframeidx)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4SampleId sampleID;
    int ret;

    if (pDmx->m_active_video == -1)
        return MSMERR_PARAMETER_NOT_VALID;

    ret = MP4TrackGetKeyframeIdx(pDmx->m_pVTrack, idx, &sampleID);
    if (ret == MSMERR_OK)
        *pframeidx = sampleID;

    return ret;
}

int MP4DMX_GetAudioIdx(void *pInst, uint32_t reftime, uint32_t *pframeidx)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4TRACK *pTrack;
    int ret;
    MP4Timestamp temp_reftime;

    if (pDmx->m_active_audio == -1)
        return MSMERR_DMX_VDO_IDX_INVLD;

    pTrack = pDmx->m_pATrack;
    temp_reftime = (((MP4Timestamp)reftime) * (*(pTrack->m_pTimeScaleProperty)) + 500) / 1000;

    // seek audio here
    ret = MP4TrackGetSampleIndex_byTime(pTrack, temp_reftime, (MP4SampleId*)pframeidx);

    // we have to align audio sample to the frame boundary
    if (ret == MSMERR_OK && MP4TrackIsStsdUncompSample(pTrack) == MSMERR_OK)
    {
        int frame_count = *pframeidx - 1; // sample ID base is 1
        frame_count = (frame_count + (pTrack->m_pStsdProp->u.a_desc.samplesPerPacket - 1)) / pTrack->m_pStsdProp->u.a_desc.samplesPerPacket;
        *pframeidx = frame_count * pTrack->m_pStsdProp->u.a_desc.samplesPerPacket + 1;
    }
    return ret;
}

int MP4DMX_GetAudioIdxGap(void *pInst, unsigned int sample_size)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4TRACK *pTrack;
    int32_t audioIdxGap = 1;
    pTrack = pDmx->m_pATrack;

    if (pTrack->pcm_chk_read)
        audioIdxGap = sample_size /(*pTrack->m_pStszFixedSampleSizeProperty);

    // if the infos of stsz and stsc indicate the uncompressed data, we need to re-calculate sample size
    if (MP4TrackIsStsdUncompSample(pTrack) == MSMERR_OK)
        audioIdxGap = audioIdxGap * pTrack->m_pStsdProp->u.a_desc.samplesPerPacket / pTrack->m_pStsdProp->u.a_desc.bytesPerFrame;

    return audioIdxGap;
}

int MP4DMX_GetSubtitleIdx(void *pInst, unsigned long int reftime, unsigned int *pframeidx)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4TRACK *pTrack;

    if (pDmx->m_active_subtitle == -1)
        return MSMERR_DMX_VDO_READ_INVLD;

    pTrack = pDmx->m_pSTrack;
    reftime = (((MP4Timestamp)reftime + 500)/1000)*(*(pTrack->m_pTimeScaleProperty));

    return MP4TrackGetSampleIndex_byTime(pTrack, (MP4Timestamp)reftime, (MP4SampleId*)pframeidx);
}

extern MP4SampleId MP4TrackGetKeyFrameBySampleIndex(
                                             MP4TRACK *pTrack, MP4SampleId sample_id,
                                             MP4SampleId *prev_key_frame_id);

int MP4DMX_SeekVideoIdx(
    void *pInst,
    uint32_t *reftime,                  //IN
    uint32_t *key_frameidx,         //OUT, the next keyframe index
    uint32_t *target_key_frameidx,  //OUT, the keyframe in target direction
    int mode)                           //IN
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4TRACK *pTrack = NULL;
    MP4SampleId frameidx;
    MP4SampleId prev_key_frameidx = 0;
    MSMErrcode_e errRtl=MSMERR_OK;
    MP4Timestamp key_frame_time;
    MP4Duration pDuration_tmp;
    uint64_t trackduration;

    pTrack = pDmx->m_pVTrack;

    trackduration = *(pTrack->m_pMediaDurationProperty);
    trackduration *= 1000; //1000 for ms
    trackduration += (*(pTrack->m_pTimeScaleProperty))/2;
    trackduration /= *(pTrack->m_pTimeScaleProperty);

    if (*reftime >= trackduration)
    {
        MP4Timestamp last_sample_time;
        MP4Duration duration;

        MP4TrackGetSampleTimes(pTrack, *pTrack->m_pStszSampleCountProperty, &last_sample_time, &duration);

        if (*reftime > ((uint64_t)(last_sample_time + duration) * 1000 / *(pTrack->m_pTimeScaleProperty)))
        {
            errRtl = MSMERR_DMX_EOF;
            return errRtl;
        }
    }

    // special case for seek 0
    if (*reftime == 0)
    {
        *target_key_frameidx = *key_frameidx = 1;
        return MSMERR_OK;
    }

    //key_frame_time = *reftime*(*(pTrack->m_pTimeScaleProperty))+500)/1000;
    // *reftime(ms)/1000 = *reftime(s)
    // key_frame_time(number) = *reftime(s)*(*(pTrack->m_pTimeScaleProperty)(number/s))
    key_frame_time = (((MP4Timestamp)*reftime) * (*pTrack->m_pTimeScaleProperty) + 500) / 1000;
    frameidx = MP4TrackGetKeyFrameByTime(pTrack,key_frame_time,&prev_key_frameidx);

    //
    // the index of next keyframe w.r.t reftime
    //
    *key_frameidx = frameidx;

    //diag_printf("frameidx:%d\n", frameidx);

    if (mode == MP4DMX_SEEK_TYPE_NEXT_I)
    {
        if (frameidx == MP4TRACK_SEEK_NO_KEYFRAME) // there is no next key frame
        {
            mp4dmx_buf_mode_reset(pTrack);
            return MSMERR_DMX_EOF;
        }
        *target_key_frameidx = frameidx;
    }
    else
    {
        if (prev_key_frameidx == MP4TRACK_SEEK_NO_KEYFRAME)
        {
            mp4dmx_buf_mode_reset(pTrack);
            return MSMERR_PLAY_SEEK_ERROR;
        }
        *target_key_frameidx = prev_key_frameidx;
    }

    //get the keyframe time in time scale unit by first latest frame index
    MP4TrackGetSampleTimes_BufMode(pTrack, *target_key_frameidx, &key_frame_time, &pDuration_tmp/*not used*&duration*/);

    //transfer the keyfame time in millisecond
    *reftime = (unsigned long int)((key_frame_time * 1000 + (pDmx->m_VTimeScale/2)) / pDmx->m_VTimeScale);

    //diag_printf("KFT2:%lld\n",key_frame_time);

    //Always restore to 1st frame cache after time-index seeking
    mp4dmx_buf_mode_reset(pTrack);

    // errRtl must be MSMERR_OK here
    return errRtl;
}

// estimate average video bitrate with file size and video track duration
static void MP4DMX_GetAvgBitrate2(MP4TRACK *pTrack, uint32_t *V_AveBitrate)
{
    MP4FILE *pFile = pTrack->m_pFile;
    MP4Duration V_Duration;

    *V_AveBitrate = 0;

    if (pTrack->m_TrackType == MVC_STREAM_VIDEO && pTrack->m_pMediaDurationProperty && pTrack->m_pTimeScaleProperty)
    {
        // get video duration in msec
        if (*pTrack->m_pTimeScaleProperty > 0)
        {
            V_Duration = (MP4Duration) *pTrack->m_pMediaDurationProperty * 1024 / *pTrack->m_pTimeScaleProperty; // m sec
            *V_AveBitrate = (((uint64_t)pFile->m_fileSize << 3) + (V_Duration >> 1)) / V_Duration * 1024; // kbps
        }
    }
}

static void MP4DMX_GetAvgBitrate(MP4TRACK *pTrack, uint32_t *AveBitrate)
{
#define Num_Video_Frame_Count 1800 //1s
#define Num_Audio_Frame_Count 1800 //1s
    uint64_t denominator, TrackDuration;
    unsigned int i;
    uint32_t v_ave_bitrate, a_ave_bitrate;
    uint32_t numStszs, numStszs1;
    MP4FILE *pFile = pTrack->m_pFile;
    uint32_t sampleSize, total_sampleSize = 0;

    *AveBitrate = 0;

    if (pTrack->m_TrackType == MVC_STREAM_AUDIO)
    {
        TrackDuration = *(pTrack->m_pMediaDurationProperty) + (*(pTrack->m_pTimeScaleProperty))/2;
        TrackDuration *= 1024; //1024 for kbps
        TrackDuration /= *(pTrack->m_pTimeScaleProperty);

        numStszs = numStszs1 = *pTrack->m_pStszSampleCountProperty;
        if (!numStszs)
        {
            // we guarantee that a track exists means non-zeor stsz count
            assert(0);
            return;
        }

        if (*pTrack->m_pStszFixedSampleSizeProperty)
            total_sampleSize = numStszs * (*pTrack->m_pStszFixedSampleSizeProperty);
        else
        {
            if (numStszs > Num_Audio_Frame_Count)
                numStszs = Num_Audio_Frame_Count;

            for (i = 1; i < numStszs + 1; i++)
            {
                sampleSize = MP4TrackGetSampleSize(pTrack, i);
                total_sampleSize += sampleSize;
            }
        }

        denominator = (TrackDuration * numStszs + (numStszs1 >> 1)) / numStszs1;

        a_ave_bitrate = (((uint64_t)total_sampleSize * 8 + denominator / 2) / denominator);
        *AveBitrate = a_ave_bitrate << 10;
    }
    else if (pTrack->m_TrackType == MVC_STREAM_VIDEO)
    {
        if (pFile->m_fileSize != (FILE_POS)-1 && pFile->m_fileSize > 100 << 20) // file size > 100M, estimate the bit rate according to file size
        {
            MP4DMX_GetAvgBitrate2(pTrack, AveBitrate);
            return;
        }

        TrackDuration = *(pTrack->m_pMediaDurationProperty) + (*(pTrack->m_pTimeScaleProperty))/2;
        TrackDuration *= 1024; //1024 for kbps
        TrackDuration /= *(pTrack->m_pTimeScaleProperty);

        numStszs = numStszs1 = *pTrack->m_pStszSampleCountProperty;
        if (!numStszs)
        {
            // we guarantee that a track exists means non-zeor stsz count
            assert(0);
            return;
        }

        for (i = 1; i < numStszs + 1; i++)
        {
            sampleSize = MP4TrackGetSampleSize(pTrack, i);
            total_sampleSize += sampleSize;
        }

        denominator = (TrackDuration * numStszs + (numStszs1 >> 1)) / numStszs1;

        v_ave_bitrate =(((uint64_t)total_sampleSize * 8 + denominator / 2) / denominator);

        *AveBitrate = v_ave_bitrate << 10;
    }
}

#ifdef MP4_SUPPORT_ROTATE
void MP4DMX_GetVideoRotateAngle(void *pInst, int *rotate_angle)
{
    MP4TRACK *pV_Track;
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    *rotate_angle = 0;

    pV_Track = pDmx->m_pVTrack;
    if (pV_Track)
        *rotate_angle = pV_Track->rotate_angle;
}
#endif

void MP4DMX_GetVideoMace(void *pInst, unsigned int *mace)
{
    MP4TRACK *pV_Track;
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    *mace = 0;

    pV_Track = pDmx->m_pVTrack;
    if (pV_Track)
        *mace = pV_Track->mace;
}

/*  find_index_with_track: get the index of n-th audio/video/subtitle track
*  input:     ctx : demuxer instance
*           index : the n-th track from total tracks (base is 0)
*  return: the index of specific track from corresponding track type
*/

static int mp4dmx_find_index_with_track(MP4DMXInst *pInst, int track)
{
    int i, count = 0;
    mvc_stream_type_et type;
    MP4FILE *pFile = pInst->m_mp4File;
    MP4TRACK *pTrack;

    if (track < 0 || (unsigned int)track >= pInst->m_numTracks)
        return -1;

    pTrack = MP4TracksGet(&pFile->m_pTracks, track);
    if (!pTrack)
        return -1;

    type = pTrack->m_TrackType;

    for (i = 0; i <= track; i++)
    {
        pTrack = MP4TracksGet(&pFile->m_pTracks, i);
        if (pTrack->m_TrackType == type)
            count++;
    }
    return count - 1;
}

static int mp4dmx_find_track_with_index(MP4DMXInst *pInst, mvc_stream_type_et type, int index_with_type)
{
    int track_index = 0;
    unsigned int i;
    MP4FILE *pFile = pInst->m_mp4File;
    MP4TRACK *pTrack;

    for (i = 0; i < pInst->m_numTracks; i++)
    {
        pTrack = MP4TracksGet(&pFile->m_pTracks, i);

        if (pTrack->m_TrackType == type)
        {
            if (track_index++ == index_with_type)
                return i;
        }
    }
    // no match track
    return -1;
}

static void MP4DMX_GetAudioSampleRate(MP4TRACK *pTrack, uint32_t *samplerate)
{
    *samplerate = 0;

    if (pTrack && pTrack->m_TrackType == MVC_STREAM_AUDIO)
        MP4TrackGetSampleRate(pTrack, samplerate);
}

int MP4DMX_GetStreamIdByTrackId(void *pInst, mvc_stream_type_et track_type, int track_id)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4FILE *pFile = pDmx->m_mp4File;
    MP4TRACK *pTrack;
    int i;

    i = mp4dmx_find_track_with_index(pInst, track_type, track_id);
    if (i == -1)
        return -1;

    pTrack = MP4TracksGet(&pFile->m_pTracks, i);
    if (!pTrack)
        return -1;

    return pTrack->streamId;
}

int MP4DMX_GetTrackIdByStreamId(void *pInst, int stream_id, mvc_stream_type_et *track_type, int *track_id)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4FILE *pFile = pDmx->m_mp4File;
    MP4TRACK *pTrack;
    unsigned int i;

    *track_type = MVC_STREAM_NONE;
    *track_id = -1;

    for (i = 0; i < pFile->m_pTracks.m_totalnum; i++)
    {
        pTrack = MP4TracksGet(&pFile->m_pTracks, i);
        if (!pTrack)
            continue;
        if (pTrack->streamId == stream_id)
        {
            *track_type = pTrack->m_TrackType;
            *track_id = mp4dmx_find_index_with_track(pDmx, i);
            break;
        }
    }

    if (*track_id == -1 || *track_type == MVC_STREAM_NONE)
        return MSMERR_FALSE;

    return MSMERR_OK;
}

int MP4DMX_SetTrack(void *pInst, mvc_stream_type_et track_type, int track_id)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4FILE *pFile = pDmx->m_mp4File;
    MP4TRACK *pTrack;
    int ret = MVC_InvalidParam, i;

    if (track_id == -1)
    {
        if (track_type == MVC_STREAM_AUDIO)
            pDmx->m_active_audio = -1;
        else if (track_type == MVC_STREAM_VIDEO)
            pDmx->m_active_video = -1;
#ifdef SUPPORT_SUBTITLE
        else if (track_type == MVC_STREAM_SUBTITLE)
            pDmx->m_active_subtitle = -1;
#endif
        return MVC_OK;
    }

    i = mp4dmx_find_track_with_index(pInst, track_type, track_id);
    if (i == -1)
        return MVC_InvalidParam;

    pTrack = MP4TracksGet(&pFile->m_pTracks, i);
    if (!pTrack)
        return MVC_InvalidParam;

    if (track_type == MVC_STREAM_AUDIO)
    {
        pTrack->need_deliver_config = 1;
        pDmx->m_pATrack       = pTrack;
        pDmx->m_numASamples   = *pTrack->m_pStszSampleCountProperty;
        pDmx->m_ATimeScale    = *pTrack->m_pTimeScaleProperty;
        pDmx->m_active_audio  = i;
        ret = MVC_OK;
    }
#ifdef SUPPORT_SUBTITLE
    else if (track_type == MVC_STREAM_SUBTITLE)
    {
        pTrack->need_deliver_config = 1;
        pDmx->m_pSTrack         = pTrack;
        pDmx->m_numSubSamples   = *pTrack->m_pStszSampleCountProperty;
        pDmx->m_SubTimeScale    = *pTrack->m_pTimeScaleProperty;
        pDmx->m_active_subtitle = i;
        ret = MVC_OK;
    }
#endif

    return ret;
}

static void MP4DMX_GetFramerate(MP4TRACK *pTrack, uint32_t *avg_framerate)
{
    unsigned int j;
    uint32_t samplecount, total_samplecount = 0;
    uint32_t total_duration = 0;
    uint32_t stts_entry_count;
    uint32_t duration, sample_duration;
    STTS_ENTRY curr_stts_entry;

    *avg_framerate = 0;

    if (pTrack->m_TrackType == MVC_STREAM_VIDEO)
    {
        stts_entry_count = pTrack->m_pSttsProp->entry_count;

        for (j = 0; j < stts_entry_count; j++) //0 base
        {
            GetSttsEntry(pTrack, j, &curr_stts_entry);

            duration = curr_stts_entry.sample_duration;
            samplecount = curr_stts_entry.sample_count;

            sample_duration = (unsigned long int)( (duration * 1000 + (*pTrack->m_pTimeScaleProperty/2)) / *pTrack->m_pTimeScaleProperty);

            if (sample_duration == 0)
                continue;

            total_samplecount += samplecount;
            total_duration += (samplecount * sample_duration);

            if (total_samplecount >= 20000)
                break;
        }

        *avg_framerate = (1000 * total_samplecount + (total_duration >> 1)) / (total_duration + 1); /* force rounding */
    }
}

#ifdef SUPPORT_KMV
unsigned int MP4DMX_getKMVtype(void *pInst)
{
    return ((MP4DMXInst *) pInst)->m_KMV_type;
}
unsigned int MP4DMX_remapKMVtype(void *pInst, uint32_t errRtl)
{
    MP4DMXInst *pDMX = ((MP4DMXInst *) pInst);
    switch (errRtl) {
    case KMV_DMX_LICENSE_NOTEXIST:
        pDMX->m_KMV_type = KMV_DMX_LICENSE_NOTEXIST; break;
    case KMV_DMX_LICENSE_MISMATCH:
        pDMX->m_KMV_type = KMV_DMX_LICENSE_MISMATCH; break;
    case KMV_DMX_PASSWORD_MISMATCH:
        pDMX->m_KMV_type = KMV_DMX_PASSWORD_MISMATCH; break;
    default:
        if (pDMX->m_KMV_type == KMV_NORMAL ||
            pDMX->m_KMV_type == KMV_SEI)
        {
            pDMX->m_KMV_type = pDMX->m_KMV_type | KMV_AVC_FMT;
        }
        break;
    }
    return pDMX->m_KMV_type;
}
#endif

int MP4DMX_DetectDiscontinuity(void *pInst)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4FILE *pfile = (MP4FILE *)pDmx->m_mp4File;

    return MP4DetectDiscontinuity(pfile);
}

void MP4DMX_SeekToTargetHeader(void *pInst)
{
    MP4DMXInst *pDmx = (MP4DMXInst *)pInst;
    MP4FILE *pfile = (MP4FILE *)pDmx->m_mp4File;

    MP4FileSetPosition(pfile, pfile->m_moov_end);
}

static int mp4_get_clip_info(MP4DMXInst *pInst, mvc_clip_info_st *info)
{
    MP4TRACK *pVTrack;

    pVTrack = pInst->m_pVTrack;
    info->seekable       = pInst->m_seekable;
    info->num_program    = 1;
    info->active_program = 0;
    if (pVTrack && pVTrack->m_pCttsProp)
        info->ts_type        = MVC_TS_PTS;
    else
        info->ts_type        = MVC_TS_DTS;

    return MVC_OK;
}

static int mp4_get_program_info(MP4DMXInst *pInst, ATTR_UNUSED int p_index, mvc_program_info_st *info)
{
    uint64_t duration;

    memset(info, 0, sizeof(*info));

    MP4DMX_GetDuration(pInst, &duration);
    info->duration             = duration;
    info->num_video_streams    = pInst->m_numVideoTracks;
    info->num_audio_streams    = pInst->m_numAudioTracks;
    info->num_subtitle_streams = pInst->m_numSubtitleTracks;
    info->active_video         = mp4dmx_find_index_with_track(pInst, pInst->m_active_video);
    info->active_audio         = mp4dmx_find_index_with_track(pInst, pInst->m_active_audio);
    info->active_subtitle      = mp4dmx_find_index_with_track(pInst, pInst->m_active_subtitle);

    return MVC_OK;
}

static int mp4_get_video_info(MP4DMXInst *pInst, int v_index, mvc_video_info_st *info)
{
    MP4FILE *pfile = (MP4FILE *)pInst->m_mp4File;
    MP4TRACK *pTrack;
    int width, height;

    if (v_index == -1)
    {
        if (pInst->m_active_video == -1)
            return MVC_InvalidParam;
        v_index = pInst->m_active_video;
    }
    else
        v_index = mp4dmx_find_track_with_index(pInst, MVC_STREAM_VIDEO, v_index);

    pTrack = MP4TracksGet(&pfile->m_pTracks, v_index);
    if (!pTrack)
        return MVC_InvalidParam;
    MP4TrackGetWidthHeight(pTrack, &width, &height);

    info->codec          = MP4UnifyVideo4cc(pTrack->m_pStsdProp->data_format);
    info->width          = width;
    info->height         = height;
    info->bit_rate       = pTrack->avg_bitrate;

    info->frame_rate_num = pTrack->frame_rate;
    info->frame_rate_den = 1;

    return MVC_OK;
}

static int mp4_get_audio_info(MP4DMXInst *pInst, int a_index, mvc_audio_info_st *info)
{
    MP4FILE *pfile = (MP4FILE *)pInst->m_mp4File;
    MP4TRACK *pTrack;

    if (a_index == -1)
    {
        if (pInst->m_active_audio == -1)
            return MVC_InvalidParam;
        a_index = pInst->m_active_audio;
    }
    else
        a_index = mp4dmx_find_track_with_index(pInst, MVC_STREAM_AUDIO, a_index);

    pTrack = MP4TracksGet(&pfile->m_pTracks, a_index);
    if (!pTrack)
        return MVC_InvalidParam;

    info->codec          = MP4UnifyAudio4cc(pTrack->m_pStsdProp->data_format);
    info->sample_rate    = pTrack->sample_rate;
    info->bit_rate       = pTrack->avg_bitrate;
    info->channel_num    = 0;

    return MVC_OK;
}

static int mp4_get_subtitle_info(MP4DMXInst *pInst, int s_index, mvc_subtitle_info_st *info)
{
    MP4FILE *pfile = (MP4FILE *)pInst->m_mp4File;
    MP4TRACK *pTrack;

    if (s_index == -1)
    {
        if (pInst->m_active_subtitle == -1)
            return MVC_InvalidParam;
        s_index = pInst->m_active_subtitle;
    }
    else
        s_index = mp4dmx_find_track_with_index(pInst, MVC_STREAM_SUBTITLE, s_index);

    pTrack = MP4TracksGet(&pfile->m_pTracks, s_index);
    if (!pTrack)
        return MVC_InvalidParam;

    switch (pTrack->m_pStsdProp->data_format)
    {
    case CODEC_TYPE_4CC('m','p','4','s'):
        info->codec = CLIP_SUBTITLE_TYPE_DVDS; break;
    case CODEC_TYPE_4CC('t','x','3','g'):
        info->codec = CLIP_SUBTITLE_TYPE_TX3G; break;
    default:
        info->codec = CLIP_SUBTITLE_TYPE_UNKNOWN; break;
    }

    return MVC_OK;
}

int MP4DMX_GetInfomation(void *pInst, mvc_stream_type_et type, int mp4_index, void *info)
{
    if (type == MVC_STREAM_NONE)
    {
        return mp4_get_clip_info(pInst, info);
    }
    else if (type == MVC_STREAM_PROG)
    {
        return mp4_get_program_info(pInst, mp4_index, info);
    }
    else if (type == MVC_STREAM_VIDEO)
    {
        return mp4_get_video_info(pInst, mp4_index, info);
    }
    else if (type == MVC_STREAM_AUDIO)
    {
        return mp4_get_audio_info(pInst, mp4_index, info);
    }
    else if (type == MVC_STREAM_SUBTITLE)
    {
        return mp4_get_subtitle_info(pInst, mp4_index, info);
    }

    return MVC_InvalidParam;
}
