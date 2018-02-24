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


#ifndef MP4UTIL_H
#define MP4UTIL_H

#include <stdint.h>
#include "ms_string.h"
#include "mp4def.h"
#include "sys_common.h"

#define MAX_CMP_LEN 256
#define mp4_strcasecmp(arg1, arg2)  ms_strnicmp(arg1, arg2, MAX_CMP_LEN)

#if 0
#include "ms_dprintf.h"
#define MP4_DBG_MSG     diag_printf
#else
#define MP4_DBG_MSG(x, ...) ((void) 0)
#endif

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

typedef struct pcm_audio_header_s
{
    uint16_t format_tag;
    uint16_t channels;
    uint32_t sample_rate;
    uint32_t bit_rate;
    uint16_t block_align;
    uint16_t sample_depth;
    /* uint16_t size_extra; */
} ATTR_PACK pcm_audio_header_st;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

int MP4AudioFormatToTag(uint32_t format);
uint32_t MP4UnifyVideo4cc(uint32_t fmt);
uint32_t MP4UnifyAudio4cc(uint32_t fmt);

void mdxInit(mp4_heap_st *ctx, unsigned char *heap, unsigned int size);

#define MP4Tolower(c)  (((c) >= 'A') && ((c) <= 'Z'))? (c) + ('a' - 'A') : (c)
#define MP4_MIN(a,b)   ((a) < (b) ? (a) : (b))
#define MP4_MAX(a,b)   ((a) > (b) ? (a) : (b))

#endif /* MP4UTIL_H */
