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
#include "mp4file.h"
#include "mp4util.h"
#include "mp4atom.h"
#include "mp4property.h"
#include "msmComm.h"

#define PARSE_VIDE_SOUN_ONLY

static int probe_mp4(const uint8_t *header, int len)
{
    return len >= 8 &&
          ((memcmp(header + 4, "ftyp", 4) == 0) ||
           (memcmp(header + 4, "moov", 4) == 0) ||
           (memcmp(header + 4, "mdat", 4) == 0) ||
           (memcmp(header + 4, "pnot", 4) == 0));
}

static void MP4FileGenerateTracks(void *ctx, MP4FILE *pfile)
{
    MP4ATOM *pMoovAtom = MP4AtomFindAtom(pfile->m_pRootAtom, "moov");

    if (pMoovAtom)
    {
        int track_index = 0;
        MP4ATOM *pAtom = MP4AtomArrayEnumBegin(&pMoovAtom->m_pChildAtoms);

        while (pAtom)
        {
            if (ATOMID(pAtom->m_type) == ATOMID("trak"))
            {
                MP4TRACK *pTrack = CreateDmxTrack(ctx, pfile, pAtom, track_index);

                #ifdef PARSE_VIDE_SOUN_ONLY
                if (pTrack)
                    MP4TracksAdd(&pfile->m_pTracks, pTrack);
                #else
                    MP4TracksAdd(&pfile->m_pTracks, pTrack);
                #endif
                track_index++;
            }
            pAtom = MP4AtomArrayEnumNext(&pMoovAtom->m_pChildAtoms, pAtom);
        }
    }
}

static void MP4FileCacheProperties(MP4FILE *pfile)
{
    MP4ATOM *pAtom;
    MVHDPROP_V0 *pmvhdprop;

    pAtom = MP4AtomFindAtom(pfile->m_pRootAtom, "moov.mvhd");
    if (!pAtom)
        return;

    pmvhdprop = (MVHDPROP_V0 *) pAtom->m_pProperties;
    pfile->m_pTimeScaleProperty = &pmvhdprop->timescale;
}

static int MP4FileReadFromFile(void *ctx, MP4FILE *pfile)
{
    FILE_POS fileSize;
    int errRtl;

    // ensure we start at beginning of file
    if (MP4FileSetPosition(pfile, 0) == (FILE_OFF)-1)
        return MSMERR_FALSE;

    // create a new root atom
    pfile->m_pRootAtom = CreateAtom(ctx, "root");
    if(!pfile->m_pRootAtom)
        return MSMERR_DMX_READ_ATOM_FAILED;

    fileSize = MP4FileGetSize(pfile);

    pfile->m_pRootAtom->m_pFile = pfile;
    pfile->m_pRootAtom->m_start = 0;
    pfile->m_pRootAtom->m_size = fileSize;
    pfile->m_pRootAtom->m_end = fileSize;
    errRtl = MP4AtomRead(ctx, pfile->m_pRootAtom);

    if (errRtl == MSMERR_OK || errRtl == MSMERR_DMX_READ_ATOM_FINISHED)
    {
        // create MP4Track's for any tracks in the file
        MP4FileGenerateTracks(ctx, pfile);
    }

    return errRtl;
}

uint8_t MP4FileRead(void *ctx, MP4FILE *pfile)
{
    int ret = MP4FileReadFromFile(ctx, pfile);

    if (ret != MSMERR_OK && ret != MSMERR_DMX_READ_ATOM_FINISHED)
        return false;

    MP4FileCacheProperties(pfile);
    return true;
}

uint8_t MP4FileFindNext(MP4FILE *pfile)
{
    FILE_POS useful_atom_end = MP4_MAX(pfile->m_mdat_end, pfile->m_moov_end);
    uint8_t header[16];

    if (!pfile->m_cbio->detect_discontinuity)
        return 0;

    if (MP4FileSetPosition(pfile, useful_atom_end) == (FILE_OFF)-1)
        return 0;

#ifdef USE_STREAM_LIB
    while (1)
    {
        uint8_t hdrSize;
        char type[5];
        uint64_t dataSize;

        if (pfile->cbuffer.cb_peek(&pfile->cbuffer, header, 16) != 16)
            return 0;

        if (probe_mp4(header, 16))
        {
            pfile->cbuffer.input->discontinuity(pfile->cbuffer.input, MP4FileGetPosition(pfile));
            return 1;
        }

        // skip this atom
        hdrSize = MP4AtomReadAtomHeader(pfile, &dataSize, type);
        if (MP4FileSkipBytes(pfile, dataSize) == -1)
            return 0;
    }
#endif
    return 0;
}

