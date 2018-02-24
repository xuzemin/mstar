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
#include "mp4def.h"
#include "mp4util.h"
#include "mvc_demuxer.h"
#include "sys_common.h" // for wave format tag

/*lint -e514*/

void mdxInit(mp4_heap_st *ctx, unsigned char *heap, unsigned int size)
{
    unsigned char *pstart_addr =  (unsigned char *) heap;
    unsigned int u32addr = (unsigned int) pstart_addr;
    unsigned char u8size = 0;

    // initial first
    ctx->mdx_byteused = 0;
    ctx->mdx_ptr      = pstart_addr;
    ctx->mdx_maxbyte  = size;

    // to make the start_addr is 4-bytes alignment
    u8size = ((u32addr+3) & ~3) - u32addr;
    ctx->mdx_byteused    = u8size;
    ctx->mdx_ptr        += u8size;
}

void *_mdxalloc(mp4_heap_st *ctx, unsigned int size)
{
    uint8_t *ptr = ctx->mdx_ptr;
    uint32_t *block_size = (void *)ptr; // ptr is already 4-bytes alignment, cast to void * to aviod compile warning for alignment increase

    size = (size + 3) & ~3; // make it to word boundary
    size += 4;

    ctx->mdx_ptr      += size;
    ctx->mdx_byteused += size;

    if (ctx->mdx_byteused > ctx->mdx_maxbyte || ctx->mdx_byteused < 0)
    {
        MP4_DBG_MSG("======= OUT of MEMORY!!! =======\n");
        return 0;
    }

    *block_size = size;
    MP4_DBG_MSG("Mem alloc = %d, total usage[%d / %d], ptr 0x%x\n", size, ctx->mdx_byteused, ctx->mdx_maxbyte, ptr);

    return ptr + 4;
}

void _mdxfree(mp4_heap_st *ctx, void *ptr)
{
    uint32_t *block_size;
    uint8_t *base_prt = ptr; // ptr is already 4-bytes alignment

    // cast to void * to aviod compile warning for alignment increase
    block_size = (void *)(base_prt - 4);
    ctx->mdx_ptr        -= *block_size;
    ctx->mdx_byteused   -= *block_size;

    MP4_DBG_MSG("block size %d, used size %d, prt 0x%x\n", *block_size, ctx->mdx_byteused, ptr);
}

int MP4AudioFormatToTag(uint32_t format)
{
    switch (format)
    {
        case CODEC_TYPE_4CC('u','l','a','w'):  return MSFT_AUDIO_MULAW;
        case CODEC_TYPE_4CC('a','l','a','w'):  return MSFT_AUDIO_ALAW;
        case CODEC_TYPE_4CC('r','a','w',' '):  return MSFT_AUDIO_PCM;
        case CODEC_TYPE_4CC('m','s',  0,  1):  return MSFT_AUDIO_PCM;
        case CODEC_TYPE_4CC('m','s',  0,  2):  return MSFT_AUDIO_MS_ADPCM;
        case CODEC_TYPE_4CC('m','s',  0,0x11): return MSFT_AUDIO_IMA_ADPCM_MS;
        case CODEC_TYPE_4CC('i','m','a','4'):  return MSTAR_AUDIO_IMA_ADPCM_QT;
        case CODEC_TYPE_4CC('t','w','o','s'):  return MSTAR_AUDIO_PCM_S_LE;
        case CODEC_TYPE_4CC('s','o','w','t'):  return MSTAR_AUDIO_PCM_S_BE;
    }
    return 0;
}

uint32_t MP4UnifyVideo4cc(uint32_t fmt)
{
    switch (fmt)
    {
    case CODEC_TYPE_4CC('s','2','6','3'):
    case CODEC_TYPE_4CC('h','2','6','3'):
        return CLIP_VIDEO_TYPE_H263; /* h263 => s263 */
    case CODEC_TYPE_4CC('m','2','6','3'):
        return CLIP_VIDEO_TYPE_M263;
    case CODEC_TYPE_4CC('d','i','v','x'):
        return CLIP_VIDEO_TYPE_DIVX;
    case CODEC_TYPE_4CC('d','x','5','0'):
        return CLIP_VIDEO_TYPE_DX50;
    case CODEC_TYPE_4CC('x','v','i','d'):
    case CODEC_TYPE_4CC('m','p','4','v'):
        return CLIP_VIDEO_TYPE_M4V;
    case CODEC_TYPE_4CC('m','p','4','s'):
        return CLIP_VIDEO_TYPE_MP4S;
    case CODEC_TYPE_4CC('m','p','s','2'):
        return CLIP_VIDEO_TYPE_M4S2;
    case CODEC_TYPE_4CC('m','p','4','2'):
        return CLIP_VIDEO_TYPE_MP42;
    case CODEC_TYPE_4CC('d','i','v','3'):
        return CLIP_VIDEO_TYPE_DIV3;
    case CODEC_TYPE_4CC('w','m','v','2'):
        return CLIP_VIDEO_TYPE_WMV2;
    case CODEC_TYPE_4CC('w','m','v','3'):
        return CLIP_VIDEO_TYPE_WMV3;
    case CODEC_TYPE_4CC('w','v','c','1'):
        return CLIP_VIDEO_TYPE_WVC1;
    case CODEC_TYPE_4CC('a','v','s','2'):
        return CLIP_VIDEO_TYPE_AVS1;
    case CODEC_TYPE_4CC('a','v','c','1'):
        return CLIP_VIDEO_TYPE_AVC1;
    case CODEC_TYPE_4CC('m','p','e','g'):
    case CODEC_TYPE_4CC('m','p','g','1'):
    case CODEC_TYPE_4CC('m','p','2','v'): /* mpeg => mp2v */
        return CLIP_VIDEO_TYPE_MP2V;
    case CODEC_TYPE_4CC('j','p','e','g'):
    case CODEC_TYPE_4CC('m','j','p','g'):
    case CODEC_TYPE_4CC('m','j','p','a'):
        return CLIP_VIDEO_TYPE_MJPG;
    case CODEC_TYPE_4CC('i','4','2','0'):
        return CLIP_VIDEO_TYPE_I420;
    case CODEC_TYPE_4CC('s','v','q','3'):
        return CLIP_VIDEO_TYPE_SVQ3;
    case CODEC_TYPE_4CC('h','v','c','1'):
    case CODEC_TYPE_4CC('h','e','v','1'):
        return CLIP_VIDEO_TYPE_HEVC;
    default:
        return CLIP_VIDEO_TYPE_UNKNOWN;
    }
}

uint32_t MP4UnifyAudio4cc(uint32_t fmt)
{
    int a_format;
    switch (fmt)
    {
    case CODEC_TYPE_4CC('m','s', 0, 0x55):
    case CODEC_TYPE_4CC('m','s', 0, 0x50):
    case CODEC_TYPE_4CC('.','m','p','3'):
    case CODEC_TYPE_4CC('m','p','3','a'): /* ms 0x55 => mp3a */
        return CLIP_AUDIO_TYPE_MP3;
    case CODEC_TYPE_4CC('p','c','m','a'):
        return CLIP_AUDIO_TYPE_PCM;
    case CODEC_TYPE_4CC('a','c','-','3'):
    case CODEC_TYPE_4CC('s','a','c','3'):
        return CLIP_AUDIO_TYPE_AC3;
    case CODEC_TYPE_4CC('e','c','-','3'):
        return CLIP_AUDIO_TYPE_EAC3;
    case CODEC_TYPE_4CC('m','p','4','a'):
        return CLIP_AUDIO_TYPE_AAC;
    case CODEC_TYPE_4CC('s','a','m','r'):
        return CLIP_AUDIO_TYPE_AMRNB;
    case CODEC_TYPE_4CC('s','a','w','b'):
        return CLIP_AUDIO_TYPE_AMRWB;
    case CODEC_TYPE_4CC('v','r','b','s'):
        return CLIP_AUDIO_TYPE_VORBIS;
    default:
        a_format = MP4AudioFormatToTag(fmt);
        switch (a_format)
        {
            case MSFT_AUDIO_MS_ADPCM:
            case MSTAR_AUDIO_IMA_ADPCM_QT:
            case MSFT_AUDIO_IMA_ADPCM_MS:
                return CLIP_AUDIO_TYPE_ADPCM;
            case MSFT_AUDIO_PCM:
            case MSTAR_AUDIO_PCM_S_LE:
            case MSTAR_AUDIO_PCM_S_BE:
                return CLIP_AUDIO_TYPE_LPCM;
            case MSFT_AUDIO_MULAW:
            case MSFT_AUDIO_ALAW:
                return CLIP_AUDIO_TYPE_PCM;
            default:
                return CLIP_AUDIO_TYPE_UNKNOWN;
        }
    }
}
