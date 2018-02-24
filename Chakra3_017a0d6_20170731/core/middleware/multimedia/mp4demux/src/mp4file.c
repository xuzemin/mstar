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
#include "mp4def.h"
#include "mp4file.h"
#include "mvc_demuxer.h"

uint8_t MP4FileOpen(MP4FILE *pfile, cb_io_st *input, int ringbuf_size)
{
    FILE_POS filesize;

    pfile->m_cbio = input;

#ifdef USE_STREAM_LIB
    if (OpenURL(&pfile->cbuffer, pfile->m_cbio, ringbuf_size, &pfile->callback)!= MVC_OK)
        return 0;

#endif

    if (input->streaming)
    {
        filesize = input->input_size;
#ifdef USE_STREAM_LIB
        cb_set_buffer_mode(&pfile->cbuffer, 0);
#endif
    }
    else
    {
#ifdef USE_STREAM_LIB
        filesize = pfile->cbuffer.cb_seek64(&pfile->cbuffer, 0, CB_SEEK_END);
        pfile->cbuffer.cb_seek64(&pfile->cbuffer, 0, CB_SEEK_SET);
#else
        filesize = pfile->m_cbio->seek(pfile->m_cbio, 0, SEEK_END);
        pfile->m_cbio->seek(pfile->m_cbio, 0, SEEK_SET);
#endif
    }
    pfile->m_fileSize = filesize;

    return true;
}

uint8_t MP4FileClose(void *ctx, MP4FILE *pfile)
{
    if (pfile->m_pRootAtom)
        MP4AtomFree(ctx, pfile->m_pRootAtom);

    MP4TracksFree(ctx, &pfile->m_pTracks);

#ifdef USE_STREAM_LIB
    CloseURL(&pfile->cbuffer, &pfile->callback);
#endif

    return true;
}
