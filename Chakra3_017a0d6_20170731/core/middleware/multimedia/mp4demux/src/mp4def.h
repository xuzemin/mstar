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


#ifndef MP4DEF_H
#define MP4DEF_H

#include <stdio.h>
#include <stdint.h>
#include "ms_input.h"

typedef unsigned char           byte;
typedef cb_fpos                 FILE_POS;
typedef cb_off_t                FILE_OFF;

#ifndef true
    #define true                1
#endif

#ifndef false
    #define false               0
#endif


/* MP4 API types */
typedef void*       MP4FileHandle;
typedef uint32_t    MP4TrackId;
typedef uint32_t    MP4SampleId;
typedef uint64_t    MP4Timestamp;
typedef uint64_t    MP4Duration;
typedef uint32_t    MP4EditId;

//#define ATOMID(type)      (*(uint32_t*)type)
#define ATOMID(a)           (((uint32_t) ((uint8_t *) a)[0] << 24) | ((uint32_t) ((uint8_t *) a)[1] << 16) | ((uint32_t) ((uint8_t *) a)[2] <<  8) | ((uint32_t) ((uint8_t *) a)[3]))
#define ATOM_ID(a,b,c,d)    (((a)<<24)|((b)<<16)|((c)<<8)|(d))
#define CODEC_TYPE_4CC      ATOM_ID

typedef struct mp4_heap_s
{
    int32_t  mdx_byteused;
    int32_t  mdx_maxbyte;
    uint8_t *mdx_ptr;
} mp4_heap_st;

/* replace malloc function by using sharing pool */
//#define USE_MALLOC
#ifdef USE_MALLOC
    #define mdxalloc(c, s) malloc(s)
    #define mdxfree(s)  free(s)
#else
    #define mdxalloc(c, s) _mdxalloc(c, s)
    #define mdxfree(c, s)  _mdxfree(c, s)
    extern void *_mdxalloc(mp4_heap_st *ctx, unsigned int size);
    extern void _mdxfree(mp4_heap_st *ctx, void *ptr);
#endif

#endif /* MP4DEF_H */
