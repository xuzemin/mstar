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


/*
 *  API Definition for MP4 Demux
 *
 */

#ifndef MP4DEMUX_H
#define MP4DEMUX_H

#include <stdint.h>
#include "mvc_demuxer.h"

#ifdef SUPPORT_KMV
struct kmv_func_s;
int Enable_kmv_demux_plugin(struct kmv_func_s *hdr);
#endif

struct cb_io_s;

/*
 * open mp4 demux instance
 * return: 0: Okay, < 0: fail
 *
 */

#define MP4DMX_SEEK_TYPE_PREV_I     0
#define MP4DMX_SEEK_TYPE_NEXT_I     1

typedef struct demux_buffer_s
{
    void *baseptr; // the allocated buffer pointer for demuxer context
    unsigned short mdx_byteused;
    unsigned short mdx_maxbyte;
    unsigned char *mdx_ptr;
} demux_buffer_st;

int MP4DMX_Open(void **ppInst, unsigned char *heap, unsigned int heap_size,
                       struct cb_io_s *cbio, int ringbuf_size, const mvc_callback_st *callback);

int MP4DMX_Open2(void **ppInst, unsigned char *heap, unsigned int heap_size,
                       struct cb_io_s *cbio, int ringbuf_size, const mvc_callback_st *callback, uint32_t table_cache_size);

/*
 * read video sample
 * input: pInst: instance,
 *        frameidx: the frame index want to read, 1 base
 *        pbuf: the read sample buffer (assigned from caller)
 *        pnSize: the size of read buffer
 *        pStart: playback start time (seconds * 1000)
 *        pDuration: playback duration (seconds * 1000)
 * return: 0: Okay, < 0: fail
 *
 */
int MP4DMX_ReadSample(void *pInst, uint32_t frameidx, uint32_t *pnSize,
                            uint32_t *is_sync_sample, mvc_stream_type_et track_type);

int MP4DMX_ReadSampleInfo(void *pInst, uint32_t frameidx, cb_fpos *pOffset, uint32_t *pnSize,
                               uint64_t *pStart, uint64_t *pDuration, uint32_t *is_sync_sample,
                               mvc_stream_type_et track_type);

/*
 * close mp4 demux instance
 * return: 0: Okay, < 0: fail
 *
 */
void MP4DMX_Close(void *pInst);

/*
 * get video key frame index by index
 * input: pInst: instance,
 *        idx : the index among all I frames in this track
 *        pframeidx : the frame index of idx-th I frame
 * return: MSMERR error code
 *
 */
int MP4DMX_GetVideoKeyFrameIdx(void *pInst, uint32_t idx, uint32_t *pframeidx);

int MP4DMX_GetAudioIdx(void *pInst, uint32_t reftime, uint32_t *pframeidx);
int MP4DMX_GetAudioIdxGap(void *pInst, unsigned int sample_size);
int MP4DMX_GetSubtitleIdx(void *pInst, unsigned long int reftime, unsigned int *pframeidx);
//
// when we need to resync audio's idx due to seeking to I(key) frame
// the reftime will output the keyframe time
//
int MP4DMX_SeekVideoIdx(void *pInst,
                                uint32_t *reftime,              //IN, OUT(when we need to resync audio's sample idx)
                                uint32_t *key_frameidx,         //OUT
                                uint32_t *prev_key_frameidx,    //OUT
                                int mode);

int MP4DMX_SetTrack(void *pInst, mvc_stream_type_et track_type, int track_id);
int MP4DMX_GetStreamIdByTrackId(void *pInst, mvc_stream_type_et track_type, int track_id);
int MP4DMX_GetTrackIdByStreamId(void *pInst, int stream_id, mvc_stream_type_et *track_type, int *track_id);

void MP4DMX_GetVideoRotateAngle(void *pInst, int *rotate_angle);
void MP4DMX_GetVideoMace(void *pInst, unsigned int *mace);
int MP4DMX_GetInfomation(void *pInst, mvc_stream_type_et type, int index, void *info);
#ifdef SUPPORT_KMV
unsigned int MP4DMX_getKMVtype(void *pInst);
unsigned int MP4DMX_remapKMVtype(void *pInst, uint32_t errRtl);
#endif
int MP4DMX_DetectDiscontinuity(void *pInst);
void MP4DMX_SeekToTargetHeader(void *pInst);
#endif /* MP4DEMUX_H */
