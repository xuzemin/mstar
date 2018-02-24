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
#include "mp4track.h"
#include "mp4file.h"
#include "mp4util.h"
#include "mp4property.h"
#include "ms_dprintf.h"
#include "mvc_demuxer.h"
#include "sys_common.h"

#define PARSE_VIDE_SOUN_ONLY

MP4TRACK *MP4TracksGet(MP4TRACKARRAY *pArray, uint32_t track_index)
{
    uint32_t i;
    MP4TRACK *pItem;

    if (!pArray)
        return 0;

    if (track_index > pArray->m_totalnum)
        return 0;

    pItem = pArray->m_pBegin;

    for (i = 0; i < track_index; i++)
    {
        pItem = pItem->m_pNextItem;
    }

    return pItem;

}

#ifdef MP4_SUPPORT_ROTATE
/*
 *    the content of transpose maxtirx is
 *    | a b u |
 *    | c d v |
 *    | x y w |
 *    each element is 4 bytes
 *    All the values in a matrix are stored as 16.16 fixed-point values,
 *    except for u, v and w, which are stored as 2.30 fixed-point values
 *    And (u,v,w) are restricted here to (0,0,1), hex (0,0,0x40000000).
 */
static int MP4TrackFix4ByteCmp(uint8_t *u8input, uint32_t cmp)
{
    uint32_t u32input = u8input[0] << 24 | u8input[1] << 16 | u8input[2] << 8 | u8input[3];
    return u32input == cmp;
}

static uint16_t MP4TrackMatrix2Mode(uint8_t matrix[36])
{
    // 0x40000000 is 1 for FIX30
    // 0x00010000 is 1 for FIX16
    // 0xffff0000 is -1 for FIX16
    // (u, v, w) must be (0, 0, 1)
    if (!MP4TrackFix4ByteCmp(matrix + 8, 0) || !MP4TrackFix4ByteCmp(matrix + 20, 0) || !MP4TrackFix4ByteCmp(matrix + 32, 0x40000000))
        return 0;

    // (a, b, c, d) = (1, 0, 0, 1)
    if (MP4TrackFix4ByteCmp(matrix, 0x00010000) && MP4TrackFix4ByteCmp(matrix + 4, 0) && MP4TrackFix4ByteCmp(matrix + 12, 0) && MP4TrackFix4ByteCmp(matrix + 16, 0x00010000))
        return 0;
    // (a, b, c, d) = (0, 1, -1, 0)
    if (MP4TrackFix4ByteCmp(matrix, 0) && MP4TrackFix4ByteCmp(matrix + 4, 0x00010000) && MP4TrackFix4ByteCmp(matrix + 12, 0xffff0000) && MP4TrackFix4ByteCmp(matrix + 16, 0))
        return 90;
    // (a, b, c, d) = (-1, 0, 0, -1)
    if (MP4TrackFix4ByteCmp(matrix, 0xffff0000) && MP4TrackFix4ByteCmp(matrix + 4, 0) && MP4TrackFix4ByteCmp(matrix + 12, 0) && MP4TrackFix4ByteCmp(matrix + 16, 0xffff0000))
        return 180;
    // (a, b, c, d) = (0, -1, 1, 0)
    if (MP4TrackFix4ByteCmp(matrix, 0) && MP4TrackFix4ByteCmp(matrix + 4, 0xffff0000) && MP4TrackFix4ByteCmp(matrix + 12, 0x00010000) && MP4TrackFix4ByteCmp(matrix + 16, 0))
        return 270;

    return 0;
}
#endif

//
//To separate the CreateTrack() into DMX and MUX 2 parts, to avoid affect each other.
//
MP4TRACK *CreateDmxTrack(void *ctx, MP4FILE *pfile, MP4ATOM *pTrackAtom, int track_index)
{
    MP4ATOM *pAtom;
    MDHDPROP_V1 *pmdhdprop;
    //HDLRPROP *phdlrprop = 0;
    STSDPROP *pStsdProp;
    //MP4AV_ESDS *pESDSProp = 0;
    MP4TRACK *pTrack;
    uint32_t codec_type;
    uint32_t atomId;
    mvc_stream_type_et track_type;

    #ifdef PARSE_VIDE_SOUN_ONLY
    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.hdlr");
    if (!pAtom)
        return 0;
    {
        HDLRPROP *phdlrprop;
        MP4AV_ESDS *pESDSProp;

        phdlrprop = (HDLRPROP *)pAtom->m_pProperties;


#if 0
        if( (ATOM_ID(phdlrprop->handler_type[0], phdlrprop->handler_type[1], phdlrprop->handler_type[2], phdlrprop->handler_type[3]) != ATOM_ID('v','i','d','e') &&
           ATOM_ID(phdlrprop->handler_type[0], phdlrprop->handler_type[1], phdlrprop->handler_type[2], phdlrprop->handler_type[3]) != ATOM_ID('s','o','u','n') ) ||
           pfile->m_pTracks.m_totalnum >= 2
        )
        {
            return 0;
        }

#endif

        atomId = ATOM_ID(phdlrprop->handler_type[0],
                         phdlrprop->handler_type[1],
                         phdlrprop->handler_type[2],
                         phdlrprop->handler_type[3]);

        if (atomId == ATOM_ID('v','i','d','e'))
        {
#ifndef MP4_MULTI_TRACK
            if (pfile->m_numVideoTracks >= 1)
                return 0;
#endif
            track_type = MVC_STREAM_VIDEO;
        }
        else if (atomId == ATOM_ID('s','o','u','n') )
        {
#ifndef MP4_MULTI_TRACK
            if (pfile->m_numAudioTracks >= 1)
                return 0;
#endif
            track_type = MVC_STREAM_AUDIO;

            //diag_printf("track is sound!\n");
            pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd.esds");
            if (pAtom)
            {
                pESDSProp = (MP4AV_ESDS *)pAtom->m_pProperties;
                //diag_printf("object_type_id:0x%x\n",pESDSProp->object_type_id);
                switch (pESDSProp->object_type_id)
                {
                    case MP4_OBJECT_TYPE_AAC:
                        if (pESDSProp->decoder_cfg)
                        {
                            codec_type = ((pESDSProp->decoder_cfg[0]>>3)&0x1F);
                            //diag_printf("audio, codec_type:%d,[0]:0x%x,[1]:0x%x,[2]:0x%x\n",codec_type,pESDSProp->decoder_cfg[0],pESDSProp->decoder_cfg[1],pESDSProp->decoder_cfg[2]);
                            if(codec_type != LC_AAC && codec_type != LTP_AAC && codec_type != HE_AAC)
                                return 0;
                        }
                        else
                        {
                            MP4ATOM *pStsdAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd");

                            if (pStsdAtom)
                            {
                                aac_parameter_st aac_par;

                                pStsdProp = (STSDPROP *)pStsdAtom->m_pProperties;
                                pAtom->m_aux = pESDSProp->decoder_cfg = mdxalloc(ctx, 2);
                                if (!pAtom->m_aux)
                                    return 0;
                                pESDSProp->decoder_cfg_len = 2;

                                aac_par.object_type = LC_AAC;
                                aac_par.sample_rate = pStsdProp->u.a_desc.samplerate;
                                aac_par.channels    = pStsdProp->u.a_desc.channels;
                                aac_par.sbr         = 0;
                                sys_update_aac_config(0, &pESDSProp->decoder_cfg, &pESDSProp->decoder_cfg_len, &aac_par);
                                break;
                            }
                            return 0;
                        }
                        break;
                    case MP4_OBJECT_TYPE_ID_ISO13818_7_MP: // no stream to test it
                    case MP4_OBJECT_TYPE_ID_ISO13818_7_LC:
                    case MP4_OBJECT_TYPE_MP3:
                    case MP4_OBJECT_TYPE_MP2:
                    case MP4_OBJECT_TYPE_VORBIS:
                        break;
                    default:
                        return 0;
                }
            }
        }
#ifdef SUPPORT_SUBTITLE
        else if (atomId == ATOM_ID('s','u','b','p'))
        {
            pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd");
            if (pAtom)
            {
                pStsdProp = (STSDPROP *)pAtom->m_pProperties;
                codec_type = pStsdProp->data_format;
                if (codec_type != ATOM_ID('m','p','4','s'))
                    return 0;
            }
            track_type = MVC_STREAM_SUBTITLE;
        }
        else if (atomId == ATOM_ID('t','e','x','t'))
        {
            track_type = MVC_STREAM_SUBTITLE;
        }
        else if (atomId == ATOM_ID('s','b','t','l'))
        {
            track_type = MVC_STREAM_SUBTITLE;
        }
#endif
        else
            return 0;
    }
    #endif

    pTrack = (MP4TRACK *)mdxalloc(ctx, sizeof(MP4TRACK));
    if(pTrack == 0 ) return 0;

    memset(pTrack, 0, sizeof(MP4TRACK));

    pTrack->m_pTrakAtom = pTrackAtom;
    pTrack->m_pFile     = pfile;
    pTrack->m_TrackType = track_type;

    pTrack->m_first_ctts_entry_value = (MP4Timestamp)-1; /* default to U64 max value */

    pAtom = MP4AtomFindAtom(pTrackAtom, "tkhd");
    if (!pAtom)
    {
        mdxfree(ctx, pTrack);
        return 0;
    }
    {
        TKHDPROP_V0 *ptkhdprop = (TKHDPROP_V0 *) pAtom->m_pProperties;
        pTrack->m_trackId                    = ptkhdprop->track_id;
        pTrack->m_pTrackDurationProperty     = &ptkhdprop->duration;
#ifdef MP4_SUPPORT_ROTATE
        pTrack->rotate_angle                 = MP4TrackMatrix2Mode(ptkhdprop->reserved3 + 2);
#endif
        pTrack->stream_width                 = ptkhdprop->width  >> 16;
        pTrack->stream_height                = ptkhdprop->height >> 16;
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.mdhd");
    if (!pAtom)
    {
        mdxfree(ctx, pTrack);
        return 0;
    }
    {
        pmdhdprop = (MDHDPROP_V1 *)pAtom->m_pProperties;
        pTrack->m_pMediaDurationProperty = &pmdhdprop->duration;
        if (pmdhdprop->timescale == 0) // pTrack->m_pTimeScaleProperty = 0 will cause divided by zero exception
        {
            mdxfree(ctx, pTrack);
            return 0;
        }
        pTrack->m_pTimeScaleProperty = &pmdhdprop->timescale;
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsz");
    if (!pAtom)
    {
        mdxfree(ctx, pTrack);
        return 0;
    }
    {
        MP4ATOM *pStsdAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd");

        pTrack->m_pStszProp = (STSZPROP *)pAtom->m_pProperties;
        pTrack->m_pStszFixedSampleSizeProperty = &pTrack->m_pStszProp->sample_size;
        if (pStsdAtom && pTrack->m_TrackType == MVC_STREAM_AUDIO)
        {
            pStsdProp = (STSDPROP *)pStsdAtom->m_pProperties;

            // use the sample size calculated from stsd info if exist
            if (pStsdProp->u.a_desc.sampleSize)
                pTrack->m_pStszFixedSampleSizeProperty = &pStsdProp->u.a_desc.sampleSize;
        }
        if (pTrack->m_pStszProp->sample_count == 0) // pTrack->m_pStszSampleCountProperty = 0 will cause divided by zero exception
        {
            mdxfree(ctx, pTrack);
            return 0;
        }
        pTrack->m_pStszSampleCountProperty = &pTrack->m_pStszProp->sample_count;
        pTrack->m_pStszSampleSizeProperty = &pTrack->m_pStszProp->entry_size;
        pTrack->m_pStszSampleSizeFilePos = pTrack->m_pStszProp->entry_file_pos;
    }

    // get handles on information needed to map sample id's to file offsets
    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsc");
    if (!pAtom)
    {
        mdxfree(ctx, pTrack);
        return 0;
    }
    {
           pTrack->m_pStscProp = (STSCPROP *)pAtom->m_pProperties;
           pTrack->m_pStscCountProperty = &pTrack->m_pStscProp->entry_count;
           pTrack->m_pStscSampleStartFilePos = pTrack->m_pStscProp->entry_file_pos;
           pTrack->m_pStscSampleCurFilePos = pTrack->m_pStscSampleStartFilePos;
           pTrack->m_pStscSampleIDPrev = pTrack->m_pStscSampleIDNext = 1;
           pTrack->m_pStscIndex = 0;
    }

    // both stco/co64 is chunk offset, there must be at least and only one atom
    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stco");
    if (!pAtom)
        pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.co64");
    if (!pAtom)
    {
        mdxfree(ctx, pTrack);
        return 0;
    }
    {
        pTrack->m_pStcoProp = (STCOPROP *)pAtom->m_pProperties;
        pTrack->m_pChunkCountProperty = &pTrack->m_pStcoProp->entry_count;
        pTrack->m_pChunkOffsetFilePos = pTrack->m_pStcoProp->entry_file_pos;
    }

    // get handles on sample timing info
    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stts");
    if (!pAtom)
    {
        mdxfree(ctx, pTrack);
        return 0;
    }
    {
           pTrack->m_pSttsProp = (STTSPROP *)pAtom->m_pProperties;
           if (pTrack->m_pSttsProp->entry_count == 0)
           {
               mdxfree(ctx, pTrack);
               return 0;
           }
           pTrack->m_pSttsCountProperty = &pTrack->m_pSttsProp->entry_count;
           pTrack->m_pSttsSampleCountProperty = &pTrack->m_pSttsProp->sample_count;
           pTrack->m_pSttsSampleDeltaProperty = &pTrack->m_pSttsProp->sample_delta;
           pTrack->m_pSttsSampleCountFilePos = pTrack->m_pSttsProp->sample_count_file_pos;
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.ctts");
    if (pAtom)
    {
           pTrack->m_pCttsProp = (CTTSPROP *)pAtom->m_pProperties;
           pTrack->m_pCttsCountProperty = &pTrack->m_pCttsProp->entry_count;
           pTrack->m_pCttsSampleCountProperty = &pTrack->m_pCttsProp->sample_count;
           pTrack->m_pCttsSampleOffsetProperty = &pTrack->m_pCttsProp->sample_offset;
           pTrack->m_pCttsSampleCountFilePos = pTrack->m_pCttsProp->sample_count_file_pos;
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd");
    if (!pAtom)
    {
        mdxfree(ctx, pTrack);
        return 0;
    }
    {
        uint32_t data_fmt;

        pStsdProp = pTrack->m_pStsdProp = (STSDPROP*) pAtom->m_pProperties;

        // ER: fix incorrect sample size in STSZ
        if (pStsdProp) {
            data_fmt = pStsdProp->data_format;
            if (data_fmt == CODEC_TYPE_4CC('r','a','w',' ') ||
                data_fmt == CODEC_TYPE_4CC('t','w','o','s') ||
                data_fmt == CODEC_TYPE_4CC('s','o','w','t')) {
                pcm_audio_header_st *pwavefmt = pStsdProp->decoder_cfg;

                if (*pTrack->m_pStszFixedSampleSizeProperty != (uint32_t)(pwavefmt->sample_depth >> 3) * pwavefmt->channels) {
                    ms_dprintf(1, "[MP4P] change STSZ samplesize to WAVEFMT depth (%d=>%d\n", *pTrack->m_pStszFixedSampleSizeProperty, (pwavefmt->sample_depth>>3)*pwavefmt->channels);
                    *pTrack->m_pStszFixedSampleSizeProperty = (pwavefmt->sample_depth>>3)*pwavefmt->channels;
                }
            }
        }
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stss");
    if (pAtom)
    {
        pTrack->m_pStssProp = (STSSPROP *)pAtom->m_pProperties;
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd.esds");
    if (pAtom)
    {
        pTrack->m_pESDSProp = (MP4AV_ESDS *)pAtom->m_pProperties;
    } else {
        pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd.glbl");
        if (pAtom)
        {
            pTrack->m_pESDSProp = (MP4AV_ESDS *)pAtom->m_pProperties;
        }
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd.wave");
    if (pAtom)
    {
        WAVEPROP *pwave = pAtom->m_pProperties;
        if (pwave->type == ATOMID("esds"))
        {
            pTrack->m_pESDSProp = &pwave->u.esds;
        }
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd.avcc");
    if (pAtom)
    {
        pTrack->m_pavcCProp = (AVCConfig *)pAtom->m_pProperties;
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd.avss");
    if (pAtom)
    {
        pTrack->m_pavssProp = (AVSConfig *)pAtom->m_pProperties;
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd.hvcc");
    if (pAtom)
    {
        pTrack->m_phevcProp = (HEVCConfig *)pAtom->m_pProperties;
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd.d263");
    if (pAtom)
    {
        uint32_t vendor;

        pTrack->m_pD263Prop = (D263PROP *)pAtom->m_pProperties;

        //diag_printf("pTrack->m_pD263Prop->vendor:%08X\n", pTrack->m_pD263Prop->vendor);

        vendor = pTrack->m_pD263Prop->vendor;

        if ( vendor == H263_VENDOR ) {
            pTrack->legal_vendor=1;
        }
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "udta.mstr");
    if (pAtom)
    {
        MSTRPROP *mstrprop = (MSTRPROP *)pAtom->m_pProperties;

        pTrack->mace = mstrprop->mace;
    }

    pAtom = MP4AtomFindAtom(pTrackAtom, "mdia.minf.stbl.stsd.damr");
    if (pAtom)
    {
        uint32_t vendor;

        pTrack->m_pDamrProp = (DAMRPROP *)pAtom->m_pProperties;

        //diag_printf("pTrack->m_pDamrProp->vendor:%08X\n", pTrack->m_pDamrProp->vendor);

        vendor = pTrack->m_pDamrProp->vendor;

        if (vendor == AMR_VENDOR)
            pTrack->legal_vendor = 1;
    }

    pTrack->streamId = track_index;
    // FIXME: number of each type of tracks should be calculated outside of this function.
    if (atomId == ATOM_ID('v','i','d','e'))
        pfile->m_numVideoTracks++;
    else if (atomId == ATOM_ID('s','o','u','n'))
        pfile->m_numAudioTracks++;
#ifdef SUPPORT_SUBTITLE
    else if (atomId == ATOM_ID('s','u','b','p') || atomId == ATOM_ID('t','e','x','t'))
        pfile->m_numSubtitleTracks++;
#endif

    return pTrack;
}

uint8_t MP4TracksAdd(MP4TRACKARRAY *pArray, MP4TRACK *pTrack)
{
    MP4TRACK *pTail;

    if (!pArray)
        return false;

    pTail = pArray->m_pTail;

    if (!pTail)
        pArray->m_pBegin = pTrack;  // is the first one added item
    else
        pTail->m_pNextItem = pTrack;

    pArray->m_pTail = pTrack;

    pArray->m_totalnum++;

    return true;
}


uint8_t MP4TracksFree(void *ctx, MP4TRACKARRAY *pArray)
{
    MP4TRACK *pItem = 0;

    pItem = pArray->m_pBegin;
    while (pItem)
    {
        MP4TRACK *pNext = 0;
        pNext = pItem->m_pNextItem;
        mdxfree(ctx, pItem);
        pItem = pNext;
    }

    return true;
}
