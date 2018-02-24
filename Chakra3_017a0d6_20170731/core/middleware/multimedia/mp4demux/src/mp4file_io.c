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


#include "ms_io.h"
#include "mp4def.h"
#include "mp4file.h"

FILE_OFF MP4FileGetPosition(MP4FILE *pfile)
{
#ifdef USE_STREAM_LIB
    return pfile->cbuffer.cb_seek64(&pfile->cbuffer, 0, CB_SEEK_CUR);
#else
    return pfile->m_cbio->seek(pfile->m_cbio, 0, SEEK_CUR);
#endif
}

FILE_OFF MP4FileSetPosition(MP4FILE *pfile, FILE_POS pos)
{
#ifdef USE_STREAM_LIB
    return pfile->cbuffer.cb_seek64(&pfile->cbuffer, pos, CB_SEEK_SET);
#else
    return pfile->m_cbio->seek(pfile->m_cbio, pos, SEEK_SET);
#endif
}

FILE_POS MP4FileGetSize(MP4FILE *pfile)
{
    return pfile->m_fileSize;
}
