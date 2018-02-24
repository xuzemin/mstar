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


#include <string.h>
#include "ms_io.h"
#include "mp4file.h"
#include "mp4track.h"

MP4FileHandle MP4Open(void *ctx, cb_io_st *input, int ringbuf_size, const mvc_callback_st *callback)
{
    MP4FILE *pFile = mdxalloc(ctx, sizeof(MP4FILE));

    if (!pFile) return (MP4FileHandle) 0;

    memset(pFile, 0, sizeof(MP4FILE));

    pFile->callback = *callback;
    if (!MP4FileOpen(pFile, input, ringbuf_size))
    {
        mdxfree(ctx, pFile);
        return (MP4FileHandle) 0;
    }

    return (MP4FileHandle) pFile;
}

uint8_t MP4Read(void *ctx, MP4FileHandle hFile)
{
    MP4FILE *pfile = (MP4FILE *)hFile;

    if (!MP4FileRead(ctx, pfile))
        return 0;

    return 1;
}

uint8_t MP4Close(void *ctx, MP4FileHandle hFile)
{
    uint8_t bRet = false;
    if (hFile)
    {
        bRet = MP4FileClose(ctx, (MP4FILE *)hFile);
        mdxfree(ctx, hFile);
    }

    return bRet;
}

uint32_t MP4GetNumberOfTracks(MP4FileHandle hFile)
{
    MP4FILE *pfile = (MP4FILE *)hFile;
    if (pfile)
        return MP4TracksGetSize(&pfile->m_pTracks);

    return 0;
}

int MP4DetectDiscontinuity(MP4FileHandle hFile)
{
    return MP4FileFindNext(hFile);
}

