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
#include <stdint.h>
#include <assert.h>
#include "mp4demux.h"
#include "mp4atom.h"
#include "mp4file.h"
#include "mp4property.h"
#include "mp4util.h"
#include "msmComm.h"//for MSMErrcode_e

#define MP4AtomSkip(pAtom)  MP4FileSetPosition(pAtom->m_pFile, pAtom->m_end)
#define STREAM_MOOV_SIZE_LIMIT (2 * 1024 * 1024) // 2M

int MP4AtomReadChildAtoms(void *ctx, MP4ATOM *pAtom);

static int mp4_get_bits_per_sample(uint32_t data_fmt)
{
    // ffmpeg set bits per sample for all pcm codec, currently we only set for mulaw and alaw
    if (MP4AudioFormatToTag(data_fmt) == MSFT_AUDIO_MULAW || MP4AudioFormatToTag(data_fmt) == MSFT_AUDIO_ALAW)
        return 8;

    return 0;
}

static MSMErrcode_e stsd_read(void *ctx, MP4ATOM *pAtom, uint32_t curr_hdlr_type)
{
    int i;
    STSDPROP *pstsd = (STSDPROP *)pAtom->m_pProperties;
    struct tagMP4File* pFile = pAtom->m_pFile;
    uint8_t fcc[4] = {0};

    pstsd->version_flag = MP4FileReadUInt32(pFile);
    pstsd->entry_count = MP4FileReadUInt32(pFile);
    pstsd->sample_dscription_size = MP4FileReadUInt32(pFile);

    // ================================
    // common part of class SampleEntry
    for (i = 0; i < 4; i++)
        if (MP4FileReadBytes(pFile, &fcc[i], 1) != 1)
            return MSMERR_FALSE;

    if (fcc[0] != 'm' || fcc[1] != 's')
    {
        // if the first 2 bytes are 'ms', which means the last 2 bytes are audio tag, we have to keep it unchanged
        for (i = 0; i < 4; i++)
            fcc[i] = MP4Tolower(fcc[i]);
    }
    pstsd->data_format = CODEC_TYPE_4CC(fcc[0], fcc[1], fcc[2], fcc[3]);
    MP4FileSkipBytes(pFile, 8);
    //Reserved(32), Reserved(16), Data-Reference index
    // end of common part
    // ===============================

    if (curr_hdlr_type == ATOMID("vide"))
    {
        //mp4v, s263
        MP4FileSkipBytes(pFile, 16);

        //
        //we have to use stream width, height, instead of track's width & height
        //or the decoder will fail for the wrong dimension!!
        //
        pstsd->u.v_desc.stream_width  = MP4FileReadUInt16(pAtom->m_pFile); //stream width
        pstsd->u.v_desc.stream_height = MP4FileReadUInt16(pAtom->m_pFile); //stream height

        MP4FileSkipBytes(pFile, 50);
        //
        // Read mp4v_esds, d263
        // Read directly could save some stack spaces
        MP4AtomReadChildAtoms(ctx, pAtom);
    }
    else if (curr_hdlr_type == ATOMID("soun"))
    {
        uint32_t data_fmt;
        uint16_t ver;
        uint16_t wBitsPerSample, bitsPerSampleCalulated;
        int16_t compressionID;

        data_fmt = pstsd->data_format;

        // alias same formats
        if (data_fmt == CODEC_TYPE_4CC('n','o','n','e') ||
            data_fmt == CODEC_TYPE_4CC( 0, 0, 0, 0)) // according to QT spec, it is "raw " or "twos". Now, assume "raw "
        {
            pstsd->data_format = data_fmt = CODEC_TYPE_4CC('r','a','w',' ');
        }

        pstsd->u.a_desc.version = ver = MP4FileReadUInt16(pFile);
        MP4FileReadUInt16(pFile);

        MP4FileReadUInt32(pFile);

        pstsd->u.a_desc.channels = MP4FileReadUInt16(pFile); //Reserved(16), channel count

        wBitsPerSample = MP4FileReadUInt16(pFile); //Reserved(16), samplesize

        compressionID = MP4FileReadUInt16(pFile);
        MP4FileReadUInt16(pFile); //Reserved(16), all 0

        pstsd->u.a_desc.samplerate = MP4FileReadUInt16(pFile); // FIX point 16.16, only read integer part
        MP4FileReadUInt16(pFile);

        // defined in QT spec
        if (ver == 1)
        {
            pstsd->u.a_desc.samplesPerPacket = MP4FileReadUInt32(pFile);
            pstsd->u.a_desc.bytesPerPacket   = MP4FileReadUInt32(pFile);
            pstsd->u.a_desc.bytesPerFrame    = MP4FileReadUInt32(pFile);
            pstsd->u.a_desc.bytesPerSample   = MP4FileReadUInt32(pFile);
            // compressionID = -2 -> use redefined sample size
            if (compressionID == -2)
            {
                pstsd->u.a_desc.version =
                pstsd->u.a_desc.samplesPerPacket = 0; // indicate that these fields should not be used
            }
        }
        else if (ver == 2)
        {
            for (i = 0; i < 9; i++)
                MP4FileReadUInt32(pFile);
        }

        bitsPerSampleCalulated = mp4_get_bits_per_sample(data_fmt);
        if (bitsPerSampleCalulated)
        {
            wBitsPerSample = bitsPerSampleCalulated;
            pstsd->u.a_desc.sampleSize = (wBitsPerSample >> 3) * pstsd->u.a_desc.channels;
        }
        //
        // Read mp4a_esds, damr
        // Read directly could save some stack spaces
        MP4AtomReadChildAtoms(ctx, pAtom);

        if (MP4AudioFormatToTag(data_fmt) != 0)
        {
            MP4ATOM *pWaveAtom = MP4AtomFindAtom(pAtom, "wave");

            if (pWaveAtom)
            {
                WAVEPROP *pWave = pWaveAtom->m_pProperties;
                if (pWave->type == data_fmt)
                {
                    pstsd->decoder_cfg     = pWave->u.wfex.data;
                    pstsd->decoder_cfg_len = pWave->u.wfex.len;
                }
            }

            if (pstsd->decoder_cfg == 0)
            {
                pcm_audio_header_st *pwavefmt = mdxalloc(ctx, sizeof(pcm_audio_header_st));
                pAtom->m_aux = pwavefmt;
                if (pwavefmt)
                {
                    memset(pwavefmt, 0, sizeof(pcm_audio_header_st));

                    pwavefmt->format_tag   = MP4AudioFormatToTag(data_fmt);
                    pwavefmt->channels     = pstsd->u.a_desc.channels;
                    pwavefmt->sample_rate  =
                    pwavefmt->bit_rate     = pstsd->u.a_desc.samplerate;
                    pwavefmt->block_align  = (pstsd->u.a_desc.channels * wBitsPerSample) >> 3;
                    pwavefmt->sample_depth = wBitsPerSample;
                    if (data_fmt == CODEC_TYPE_4CC('m','s',  0,  2) ||
                        data_fmt == CODEC_TYPE_4CC('m','s',  0,0x11))
                    {
                        if (pstsd->u.a_desc.version == 1)
                            pwavefmt->block_align = pstsd->u.a_desc.bytesPerFrame;
                        else
                            pwavefmt->block_align = 1024;
                        pwavefmt->sample_depth = 4;
                    } else if (data_fmt == CODEC_TYPE_4CC('i','m','a','4')) {
                        pwavefmt->sample_depth = 4;
                    }

                    pstsd->decoder_cfg     = pwavefmt;
                    pstsd->decoder_cfg_len = sizeof(pcm_audio_header_st);
                }
            }
        }
    }
#ifdef SUPPORT_SUBTITLE
    else if (curr_hdlr_type == ATOMID("subp"))
    {
        MP4AtomReadChildAtoms(ctx, pAtom);
    }
    else if ((curr_hdlr_type == ATOMID("text"))||(curr_hdlr_type == ATOMID("sbtl")))
    {
        // no parsing for textSampleEntry, the info in it not used so far
#if 0
        uint32_t displayFlag;
        int8_t h_justification, v_justification;
        uint32_t rgba, style_rgba;
        int16_t top, bottom, left, right;
        int16_t startChar, endChar, fontID;
        int8_t face_style_flag, font_size;

        displayFlag = MP4FileReadUInt32(pFile);
        h_justification = MP4FileReadUInt8(pFile);
        v_justification = MP4FileReadUInt8(pFile);
        rgba = MP4FileReadUInt32(pFile);
        // box record
        top = MP4FileReadUInt16(pFile);
        left = MP4FileReadUInt16(pFile);
        bottom = MP4FileReadUInt16(pFile);
        right = MP4FileReadUInt16(pFile);
        // style record
        startChar = MP4FileReadUInt16(pFile);
        endChar = MP4FileReadUInt16(pFile);
        fontID = MP4FileReadUInt16(pFile);
        face_style_flag = MP4FileReadUInt8(pFile);
        font_size = MP4FileReadUInt8(pFile);
        style_rgba = MP4FileReadUInt32(pFile);
        // FontTableBox
        MP4AtomReadChildAtoms(ctx, pAtom);
#endif
    }
#endif
    else
    {
        // return false, so the corresponding track will be released
        return MSMERR_FALSE;
    }

    return MSMERR_OK;
}

static int mp4_read_descr_len(struct tagMP4File* pFile)
{
    int len = 0;
    int count = 4;
    while (count--) {
        int c = MP4FileReadUInt8(pFile);
        len = (len << 7) | (c & 0x7f);
        if (!(c & 0x80))
            break;
    }
    return len;
}

static int mp4_read_descr_tag(struct tagMP4File* pFile, int *tag)
{
    int len;
    *tag = MP4FileReadUInt8(pFile);
    len = mp4_read_descr_len(pFile);

    return len;
}

static MSMErrcode_e esds_read(void *ctx, MP4ATOM *pAtom, MP4AV_ESDS *pesds)
{
    int tag, len;
    uint32_t flag, ocrflag, urlflag, streamdependflag;
    struct tagMP4File* pFile = pAtom->m_pFile;
    MSMErrcode_e retval = MSMERR_OK;

    //
    // Well, broken but sufficient for regular MP4 streams
    //
    MP4FileReadUInt32(pFile);  // version + flags 32 bits

    len = mp4_read_descr_tag(pFile, &tag);
    if (tag != MP4_ES_DESCR_TAG)
        return MSMERR_FALSE;

    MP4FileReadUInt16(pFile); // ID:ignore

    //
    // streamDependenceFlag:1 bit
    // URL_flag:1 bit
    // ocr_flag:1 bit
    // priority:5 bits
    //

    flag = MP4FileReadUInt8(pFile);
    streamdependflag    = flag & (1<<8);
    urlflag             = flag & (1<<7);
    ocrflag             = flag & (1<<6);
    //priority            = flag & (0x1F);

    if (streamdependflag) {
        //should be useless in our case
        MP4FileReadUInt16(pFile); // dependsOn_ES_ID:ignore
    }

    if (urlflag)
    {
        int url_len;
        url_len = MP4FileReadUInt8(pFile);

        //useless in our case
        MP4FileSkipBytes(pFile, url_len);
    }
    if (ocrflag)
    {
        //useless in our case
        MP4FileReadUInt16(pFile); // OCR_ES_ID:ignore
    }

    len = mp4_read_descr_tag(pFile, &tag);
    if (tag == MP4_DEC_CONFIG_DESCR_TAG) { //0x04
        // CHECK_ME
        // codec identity?
        //
        pesds->object_type_id = MP4FileReadUInt8(pFile);
        pesds->stream_type = MP4FileReadUInt8(pFile) >> 2;

        MP4FileSkipBytes(pFile, 3);

        pesds->max_bitrate = MP4FileReadUInt32(pFile);
        pesds->avg_bitrate = MP4FileReadUInt32(pFile);

        if (((pesds->stream_type == MP4_STREAM_TYPE_VISUAL) &&
                    ((pesds->object_type_id == MP4_OBJECT_TYPE_ID_ISO14496_2) ||
                     (pesds->object_type_id == MP4_OBJECT_TYPE_ID_ISO11172_2) ||
                     (pesds->object_type_id == MP4_OBJECT_TYPE_ID_ISO11172_2))) ||
            ((pesds->stream_type == MP4_STREAM_TYPE_AUDIO) &&
                    ((pesds->object_type_id == MP4_OBJECT_TYPE_ID_ISO14496_3)    ||
                     (pesds->object_type_id == MP4_OBJECT_TYPE_ID_ISO13818_7_MP) ||
                     (pesds->object_type_id == MP4_OBJECT_TYPE_ID_ISO13818_7_LC) ||
                     (pesds->object_type_id == MP4_OBJECT_TYPE_VORBIS))) ||
            (pesds->stream_type == MP4_STREAM_TYPE_NERO_SUBPIC))
        {
            len = mp4_read_descr_tag(pFile, &tag);
            if (tag == MP4_DEC_SPECIFIC_DESCR_TAG)
            { //0x05
                pAtom->m_aux = pesds->decoder_cfg = mdxalloc(ctx, len);
                if (pesds->decoder_cfg)
                {
                    pesds->decoder_cfg_len = len;
                    MP4FileReadBytes(pFile, (byte *)pesds->decoder_cfg, len);
                }
            }
        }
    }

    //
    // ignore
    //
    //len = mp4_read_descr_tag(pFile, &tag);
    //if (tag == MP4_SL_CONFIG_DESCR_TAG) { //0x06
    //
    //}

    //
    // ignore the other following fields or tags, we do not care!
    // maybe because we do not have that much memory!
    //

    return retval;
}

static MSMErrcode_e glbl_read(void *ctx, MP4ATOM *pAtom)
{
    int len = (int)pAtom->m_size;
    MP4AV_ESDS *pesds = (MP4AV_ESDS *)pAtom->m_pProperties;
    struct tagMP4File* pFile = pAtom->m_pFile;

    pAtom->m_aux = pesds->decoder_cfg = mdxalloc(ctx, len);
    if (pesds->decoder_cfg)
    {
        pesds->decoder_cfg_len = len;
        MP4FileReadBytes(pFile, pesds->decoder_cfg, len);
    }

    return MSMERR_OK;
}

// return the length of parameter set
static uint32_t read_parameter_set(MP4FILE *pFile, uint8_t *buffer, int num_of_ps, uint8_t *prefix, uint8_t prefix_size, uint32_t *remaining_size)
{
    int i;
    uint16_t ps_length;
    uint32_t ps_size = 0;

    for (i = 0; i < num_of_ps && *remaining_size >= 2; i++)
    {
        uint32_t read_size;

        ps_length = MP4FileReadUInt16(pFile);
        *remaining_size -= MP4_MIN(2, *remaining_size);
        read_size = MP4_MIN(*remaining_size, ps_length);

        memcpy(buffer + ps_size, prefix, prefix_size);
        ps_size += prefix_size;

        read_size = MP4FileReadBytes(pFile, buffer + ps_size, read_size);
        *remaining_size -= read_size;
        ps_size += read_size;
    }

    return ps_size;
}

static MSMErrcode_e avcC_read(void *ctx, MP4ATOM *pAtom)
{
    AVCConfig *avcc = (AVCConfig *)pAtom->m_pProperties;
    MP4FILE* pFile = pAtom->m_pFile;
    uint8_t  numOfPictureParameterSets;
    uint16_t configlength = (uint16_t) pAtom->m_size + 32;
    uint8_t  avccfgprefix[4] = {0, 0, 0, 1};
    uint8_t data;
    uint8_t lengthSizeMinusOne;
    uint8_t numOfSequenceParameterSets;
    uint32_t remaining_size = (uint32_t) pAtom->m_size;

    pAtom->m_aux =
    avcc->decoder_cfg = mdxalloc(ctx, configlength);
    avcc->decoder_cfg_len = 0;
    if (!avcc->decoder_cfg)
        return MSMERR_DMX_READ_ATOM_FAILED;

    MP4FileSkipBytes(pFile, 4);
    /* 1 byte configurationVersion */
    /* 1 byte AVCProfileIndication */
    /* 1 byte profile_compatibility */
    /* 1 byte AVCLevelIndication */

    data = MP4FileReadUInt8(pFile);
    lengthSizeMinusOne = data & 0x3;

    avcc->nal_unit_size = lengthSizeMinusOne + 1;
    data      = MP4FileReadUInt8(pFile);
    numOfSequenceParameterSets = data & 0x1f;
    remaining_size -= 6;

    avcc->decoder_cfg_len += read_parameter_set(pFile, avcc->decoder_cfg, numOfSequenceParameterSets, avccfgprefix, 4, &remaining_size);

    numOfPictureParameterSets = MP4FileReadUInt8(pFile);
    remaining_size -= 1;

    avcc->decoder_cfg_len += read_parameter_set(pFile, avcc->decoder_cfg + avcc->decoder_cfg_len, numOfPictureParameterSets, avccfgprefix, 4, &remaining_size);

    if (remaining_size)
        MP4FileSkipBytes(pFile, remaining_size);

    return MSMERR_OK;
}

static MSMErrcode_e avss_read(void *ctx, MP4ATOM *pAtom)
{
    AVSConfig *avsc = (AVSConfig *)pAtom->m_pProperties;
    MP4FILE* pFile = pAtom->m_pFile;
    uint16_t configlength = (uint16_t) pAtom->m_size + 32;
    uint8_t avscfgprefix[3] = {0, 0, 1};
    uint8_t data;
    uint8_t lengthSizeMinusOne;
    uint8_t numOfSequenceParameterSets;
    uint32_t remaining_size = (uint32_t) pAtom->m_size;

    pAtom->m_aux =
    avsc->decoder_cfg = mdxalloc(ctx, configlength);
    avsc->decoder_cfg_len = 0;
    if (!avsc->decoder_cfg)
        return MSMERR_DMX_READ_ATOM_FAILED;

    MP4FileSkipBytes(pFile, 3);
    /* 1 byte configurationVersion */
    /* 1 byte AVSProfileIndication */
    /* 1 byte AVCLevelIndication */

    data = MP4FileReadUInt8(pFile);
    lengthSizeMinusOne = data & 0x3;

    avsc->nal_unit_size = lengthSizeMinusOne + 1;
    data      = MP4FileReadUInt8(pFile);
    numOfSequenceParameterSets = data & 0x1f; // should be 4 bits or 5 bits? sps number for AVSFileFormat.mp4 is 17 which is wrong...
    remaining_size -= MP4_MIN(5, remaining_size);

    avsc->decoder_cfg_len += read_parameter_set(pFile, avsc->decoder_cfg, numOfSequenceParameterSets, avscfgprefix, sizeof(avscfgprefix), &remaining_size);
    if (remaining_size)
        MP4FileSkipBytes(pFile, remaining_size);

    return MSMERR_OK;
}

static MSMErrcode_e hevcC_read(void *ctx, MP4ATOM *pAtom)
{
    HEVCConfig *hevcc = (HEVCConfig *)pAtom->m_pProperties;
    MP4FILE* pFile = pAtom->m_pFile;
    int i;
    uint16_t configlength = (uint16_t)pAtom->m_size + 32;
    uint8_t hevccfgprefix[3] = {0, 0, 1};
    uint8_t data;
    uint8_t lengthSizeMinusOne;
    uint8_t numOfArrays;
    uint16_t numNalus;
    uint32_t remaining_size = (uint32_t) pAtom->m_size;
    hevcc->decoder_cfg_len = 0;

    // similar to avc configure
    pAtom->m_aux = hevcc->decoder_cfg = mdxalloc(ctx, configlength);
    if(!pAtom->m_aux)
        return MSMERR_DMX_READ_ATOM_FAILED;

    MP4FileSkipBytes(pFile, 16);
    /* 1 byte configurationVersion */
    /* 1 byte , 2 bit profile_space, 1 bit tier_flag, 5 bit profile_idc */
    /* 4 byte profile_idc */
    /* 2 byte constraint_indicator_flags */
    /* 1 byte level_idc */
    /* 1 byte min_spatial_segmentation_idc */
    /* 4 byte parallelismType, chromaFormat, bitDepthLumaMinus8, bitDepthChromaMinus8 */
    /* 2 byte avgFrameRate*/

    /* read 1 byte constantFrameRate, numTemporalLayers, temporalIdNested, lengthSizeMinusOne */
    data = MP4FileReadUInt8(pFile);

    lengthSizeMinusOne = data & 0x3;
    hevcc->nal_unit_size = lengthSizeMinusOne + 1;

    numOfArrays = MP4FileReadUInt8(pFile);
    remaining_size -= MP4_MIN(18, remaining_size);

    for (i = 0; i < numOfArrays; i++)
    {
        /* 1 byte, 1 bit array_completeness, 1 bit reserved, 6 bit NAL_unit_type */
        MP4FileSkipBytes(pFile, 1);
        numNalus = MP4FileReadUInt16(pFile);
        remaining_size -= MP4_MIN(3, remaining_size);
        hevcc->decoder_cfg_len += read_parameter_set(pFile, hevcc->decoder_cfg + hevcc->decoder_cfg_len, numNalus, hevccfgprefix, sizeof(hevccfgprefix), &remaining_size);
    }
    if (remaining_size)
        MP4FileSkipBytes(pFile, remaining_size);

    return MSMERR_OK;
}

#ifdef USE_ATOM_BUFFERRED_READ
static void update_atom_cache_and_table_size(void *mem_ctx, MP4ATOM *pAtom, uint8_t **cache_page, uint32_t *cache_size, uint32_t *table_size, uint32_t entry_size, uint32_t entry_count)
{
    *table_size = entry_size * entry_count;
#ifdef CACHE_ENTIRE_ATOM
    {
        mvc_callback_st *callback = &pAtom->m_pFile->callback;

        *cache_size = *table_size;
        pAtom->m_aux_ext = *cache_page = callback->malloc(callback->context, *cache_size + entry_size);
    }
#else
    {
        MP4FILE *pFile = pAtom->m_pFile;
        uint32_t table_cache_size;

        // use pFile->table_cache_size if it is set
        if (pFile->table_cache_size)
            table_cache_size = pFile->table_cache_size;
        else
            table_cache_size = ATOM_PAGE_SIZE;

        *cache_size = MP4_MIN(table_cache_size, *table_size);
        pAtom->m_aux = *cache_page = mdxalloc(mem_ctx, *cache_size + entry_size);
    }
#endif
}

static void read_first_atom_cache(MP4FILE *pFile, uint8_t *cache, uint32_t cache_size, uint32_t table_size, uint32_t *page_index)
{
    *page_index = (uint32_t)-1;
    if (!cache)
        return;

    MP4FileReadBytes(pFile, cache, MP4_MIN(cache_size, table_size));
    *page_index = 0;
}
#endif

static MSMErrcode_e stss_read(void *ctx, MP4ATOM *pAtom)
{
    STSSPROP *pstss = (STSSPROP *) pAtom->m_pProperties;

    pstss->version_flag     = MP4FileReadUInt32(pAtom->m_pFile);
    pstss->entry_count      = MP4FileReadUInt32(pAtom->m_pFile);
    pstss->entry_file_pos   = MP4FileGetPosition(pAtom->m_pFile);

#ifdef USE_ATOM_BUFFERRED_READ
    update_atom_cache_and_table_size(ctx, pAtom, &pstss->cache_page, &pstss->cache_size, &pstss->table_size, sizeof(STSS_ENTRY), pstss->entry_count);
    read_first_atom_cache(pAtom->m_pFile, pstss->cache_page, pstss->cache_size, pstss->table_size, &pstss->page_idx);
#endif

    //
    //to Save memory space, we use entry_file_pos to read the entries in run-time.
    //but we should be aware of reading errors (sd card pops out).
    //
    /*
    pstss->sample_number = (uint32_t *)mdxalloc(ctx, sizeof(uint32_t) * pstss->entry_count);
    for (i = 0; i < pstss->entry_count; i++)
        pstss->sample_number[i] = MP4FileReadUInt32(pAtom->m_pFile);
    */
    return MSMERR_OK;
}

static MSMErrcode_e wave_read(void *ctx, MP4ATOM *pAtom)
{
    WAVEPROP *pwave = pAtom->m_pProperties;
    uint32_t size = (uint32_t) pAtom->m_size;

    while (size >= 8)
    {
        FILE_POS cur_pos = MP4FileGetPosition(pAtom->m_pFile);
        uint32_t atom_size = MP4FileReadUInt32(pAtom->m_pFile);  // atom size
        uint32_t atom_type = MP4FileReadUInt32(pAtom->m_pFile);  // atom type

        if (atom_type == 0 || size < atom_size)
            break;

        if (atom_type == ATOMID("esds"))
        {
            pwave->type = atom_type;
            esds_read(ctx, pAtom, &pwave->u.esds);
        }
        else if ((atom_type >> 16) == 0x6D73)
        {
            pwave->type = atom_type;
            pAtom->m_aux =
            pwave->u.wfex.data = mdxalloc(ctx, atom_size - 8);
            pwave->u.wfex.len  = atom_size - 8;
            if (pwave->u.wfex.data)
            {
                MP4FileReadBytes(pAtom->m_pFile, pwave->u.wfex.data, atom_size - 8);
            }
        }

        if (MP4FileSetPosition(pAtom->m_pFile, cur_pos + atom_size) == (FILE_OFF) -1)
        {
            return MSMERR_DMX_READ_ATOM_FAILED;
        }
        size -= atom_size;
    }

    return MSMERR_OK;
}

static void *MP4AtomAllocateProp(void *ctx, MP4ATOM *pAtom, int prop_size)
{
    pAtom->m_pProperties = mdxalloc(ctx, prop_size);
    if (!pAtom->m_pProperties)
        return 0;

    memset(pAtom->m_pProperties, 0, prop_size);
    return pAtom->m_pProperties;
}

static int MP4ValidHDLRtype(uint32_t hdlr_type)
{
    if (hdlr_type != ATOMID("vide")
        && hdlr_type != ATOMID("soun")
#ifdef SUPPORT_SUBTITLE
        && hdlr_type != ATOMID("subp")
        && hdlr_type != ATOMID("text")
        && hdlr_type != ATOMID("sbtl")
#endif
        )
        return 0; // invalid hdlr

    return 1;
}

static void MP4AtomAssignHDLRtype(char hdlr[5], uint32_t *hdlr_type)
{
    // there may exist hdlr whose parent is not mdia (mdia.minf.hdlr), there type is not valid
    // \\mspc5617\clips\mp4\divx\COMEDYMOVIE540x364.mov
    if (MP4ValidHDLRtype(ATOMID(hdlr)) == 0)
        return; // invalid hdlr

    assert(*hdlr_type == 0 || *hdlr_type == ATOMID(hdlr));
    *hdlr_type = ATOMID(hdlr);
}

static int MP4AtomReadProperties(void *ctx, MP4ATOM *pAtom)
{
    int expect_child = 0;

    // creat child atoms
    if (ATOMID(pAtom->m_type) ==  ATOMID("root"))
    {
        expect_child = 1;    // moov
    }
    else if (ATOMID(pAtom->m_type) ==  ATOMID("moov"))
    {
        expect_child = 1;    // mvhd, trak * n
    }
    else if (ATOMID(pAtom->m_type) ==  ATOMID("trak"))
    {
        expect_child = 1;    // tkhd, mdia
        pAtom->m_pFile->curr_hdlr_type = 0; // set to 0 since we need to read curr_hdlr_type
        pAtom->m_pFile->stsd_parsed = 0;
    }
    else if (ATOMID(pAtom->m_type) ==  ATOMID("mdia"))
    {
        expect_child = 1;    // mdhd, hdlr, minf
    }
    else if (ATOMID(pAtom->m_type) ==  ATOMID("minf"))
    {
        expect_child = 1;    // dinf, stbl
    }
    else if (ATOMID(pAtom->m_type) ==  ATOMID("dinf"))
    {
        expect_child = 1;    // dref
    }
    else if (ATOMID(pAtom->m_type) ==  ATOMID("stbl"))
    {
        expect_child = 1;    // stsd, stts, stss, stsz, stsc, stco, co64
    }
    else if (ATOMID(pAtom->m_type) ==  ATOMID("samr"))
    {
        expect_child = 1;    // damr
    }
    else if (ATOMID(pAtom->m_type) ==  ATOMID("s263"))
    {
        expect_child = 1;    // d263
    }
    // KMV movie use these atoms
    else if (ATOMID(pAtom->m_type) == ATOMID("udta"))
    {
        expect_child = 1;    // meta
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("meta")) // meta in udta
    {
        expect_child = 1;    // hdlr
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("ilst")) // ipod list
    {
        // the names of children of ilst are listed on http://atomicparsley.sourceforge.net/mpeg-4files.html
        expect_child = 1;    // ipod
    }
    else if ((unsigned char) pAtom->m_type[0] == 0xA9 || ATOMID(pAtom->m_type) == ATOMID("covr")) // 0xA9 is the copyright char for apple
    {
        expect_child = 1;    // ipod
    }
    // end of movie king KMV

    if (ATOMID(pAtom->m_type) == ATOMID("mvhd"))
    {
        MVHDPROP_V0 *pmvhd = MP4AtomAllocateProp(ctx, pAtom, sizeof(MVHDPROP_V0));

        if (!pmvhd)
            return MSMERR_OUT_OF_MEMORY;

        pmvhd->version_flag = MP4FileReadUInt32(pAtom->m_pFile);
        pmvhd->creation_time = MP4FileReadUInt32(pAtom->m_pFile);
        pmvhd->modification_time = MP4FileReadUInt32(pAtom->m_pFile);
        pmvhd->timescale = MP4FileReadUInt32(pAtom->m_pFile);
        pmvhd->duration = MP4FileReadUInt32(pAtom->m_pFile);
        pmvhd->rate = MP4FileReadUInt32(pAtom->m_pFile); // FIXED 16
        pmvhd->volume = MP4FileReadUInt16(pAtom->m_pFile); //FIXED 8
        MP4FileReadBytes(pAtom->m_pFile, pmvhd->reserved1, 70);
        pmvhd->next_track_id = MP4FileReadUInt32(pAtom->m_pFile);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("tkhd"))
    {
        TKHDPROP_V0 *ptkhd = MP4AtomAllocateProp(ctx, pAtom, sizeof(TKHDPROP_V0));

        if (!ptkhd)
            return MSMERR_OUT_OF_MEMORY;

        ptkhd->version_flag = MP4FileReadUInt32(pAtom->m_pFile);
        ptkhd->creation_time = MP4FileReadUInt32(pAtom->m_pFile);
        ptkhd->modification_time = MP4FileReadUInt32(pAtom->m_pFile);
        ptkhd->track_id = MP4FileReadUInt32(pAtom->m_pFile);
        MP4FileReadBytes(pAtom->m_pFile, ptkhd->reserved1, 4);
        ptkhd->duration = MP4FileReadUInt32(pAtom->m_pFile);
        MP4FileReadBytes(pAtom->m_pFile, ptkhd->reserved2, 12);
        ptkhd->volume = MP4FileReadUInt16(pAtom->m_pFile);
        MP4FileReadBytes(pAtom->m_pFile, ptkhd->reserved3, 38);
        ptkhd->width = MP4FileReadUInt32(pAtom->m_pFile);
        ptkhd->height = MP4FileReadUInt32(pAtom->m_pFile);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("mdhd"))
    {
        MDHDPROP_V1 *pmdhd = MP4AtomAllocateProp(ctx, pAtom, sizeof(MDHDPROP_V1));
        int version;

        if (!pmdhd)
            return MSMERR_OUT_OF_MEMORY;

        version = pmdhd->version = MP4FileReadUInt8(pAtom->m_pFile);
        MP4FileReadBytes(pAtom->m_pFile, pmdhd->flag, 3);
        pmdhd->creation_time = version == 1 ? MP4FileReadUInt64(pAtom->m_pFile):MP4FileReadUInt32(pAtom->m_pFile);
        pmdhd->modification_time = version == 1 ? MP4FileReadUInt64(pAtom->m_pFile):MP4FileReadUInt32(pAtom->m_pFile);
        pmdhd->timescale = MP4FileReadUInt32(pAtom->m_pFile);
        pmdhd->duration = version == 1 ? MP4FileReadUInt64(pAtom->m_pFile):MP4FileReadUInt32(pAtom->m_pFile);
        pmdhd->language = MP4FileReadUInt16(pAtom->m_pFile);
        MP4FileReadBytes(pAtom->m_pFile, pmdhd->reserved, 2);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("hdlr"))
    {
        HDLRPROP *phdlr = MP4AtomAllocateProp(ctx, pAtom, sizeof(HDLRPROP));

        if (!phdlr)
            return MSMERR_OUT_OF_MEMORY;

        phdlr->version_flag = MP4FileReadUInt32(pAtom->m_pFile);
        MP4FileReadBytes(pAtom->m_pFile, phdlr->reserved1, 4);
        MP4FileReadBytes(pAtom->m_pFile, (byte *)phdlr->handler_type, 4);

        MP4FileReadBytes(pAtom->m_pFile, phdlr->reserved2, 12);
        MP4AtomAssignHDLRtype(phdlr->handler_type, &pAtom->m_pFile->curr_hdlr_type);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("stts"))
    {
        STTSPROP *pstts = MP4AtomAllocateProp(ctx, pAtom, sizeof(STTSPROP));

        if (!pstts)
            return MSMERR_OUT_OF_MEMORY;

        pstts->version_flag = MP4FileReadUInt32(pAtom->m_pFile);
        pstts->entry_count = MP4FileReadUInt32(pAtom->m_pFile);
        pstts->sample_count_file_pos = MP4FileGetPosition(pAtom->m_pFile);

        //
        // special case: if entry count = 1, then we can bypass read this property
        // in MP4TrackGetSampleTimes every time
        //
#ifndef USE_ATOM_BUFFERRED_READ
        if (pstts->entry_count == 1) {
            pstts->sample_count = MP4FileReadUInt32(pAtom->m_pFile);
            pstts->sample_delta = MP4FileReadUInt32(pAtom->m_pFile);
        }
#else
        update_atom_cache_and_table_size(ctx, pAtom, &pstts->cache_page, &pstts->cache_size, &pstts->table_size, sizeof(STTS_ENTRY), pstts->entry_count);
        read_first_atom_cache(pAtom->m_pFile, pstts->cache_page, pstts->cache_size, pstts->table_size, &pstts->page_idx);
        if (pstts->entry_count == 1 && pstts->cache_page)
        {
            uint32_t offset = 0;
            pstts->sample_count = MP4FileReadBufferredUInt32(pstts->cache_page, &offset);
            pstts->sample_delta = MP4FileReadBufferredUInt32(pstts->cache_page, &offset);
        }
#endif
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("ctts"))
    {
        CTTSPROP *pctts = MP4AtomAllocateProp(ctx, pAtom, sizeof(CTTSPROP));

        if (!pctts)
            return MSMERR_OUT_OF_MEMORY;

        pctts->version_flag = MP4FileReadUInt32(pAtom->m_pFile);
        pctts->entry_count = MP4FileReadUInt32(pAtom->m_pFile);
        pctts->sample_count_file_pos = MP4FileGetPosition(pAtom->m_pFile);

        //
        //special case: if entry count = 1, then we can bypass read this property
        // in MP4TrackGetSampleTimes every time
        //
#ifndef USE_ATOM_BUFFERRED_READ
        if (pctts->entry_count == 1) {
            pctts->sample_count = MP4FileReadUInt32(pAtom->m_pFile);
            pctts->sample_offset = MP4FileReadUInt32(pAtom->m_pFile);
        }
#else
        update_atom_cache_and_table_size(ctx, pAtom, &pctts->cache_page, &pctts->cache_size, &pctts->table_size, sizeof(CTTS_ENTRY), pctts->entry_count);
        read_first_atom_cache(pAtom->m_pFile, pctts->cache_page, pctts->cache_size, pctts->table_size, &pctts->page_idx);
        if (pctts->entry_count == 1 && pctts->cache_page)
        {
            uint32_t offset = 0;
            pctts->sample_count = MP4FileReadBufferredUInt32(pctts->cache_page, &offset);
            pctts->sample_offset = MP4FileReadBufferredUInt32(pctts->cache_page, &offset);
        }
#endif

    }
    else if (ATOMID(pAtom->m_type) == ATOMID("stsd"))
    {
        if (!MP4AtomAllocateProp(ctx, pAtom, sizeof(STSDPROP)))
            return MSMERR_OUT_OF_MEMORY;
        if (pAtom->m_pFile->curr_hdlr_type != 0)
        {
            stsd_read(ctx, pAtom, pAtom->m_pFile->curr_hdlr_type);
            pAtom->m_pFile->stsd_parsed = 1;
        }
        else
            MP4AtomSkip(pAtom);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("stsz"))
    {
        STSZPROP *pstsz = MP4AtomAllocateProp(ctx, pAtom, sizeof(STSZPROP));

        if (!pstsz)
            return MSMERR_OUT_OF_MEMORY;

        pstsz->version_flag = MP4FileReadUInt32(pAtom->m_pFile);
        pstsz->sample_size = MP4FileReadUInt32(pAtom->m_pFile);
        pstsz->sample_count = MP4FileReadUInt32(pAtom->m_pFile);

        pstsz->entry_file_pos = MP4FileGetPosition(pAtom->m_pFile);
        pstsz->entry_size = 0;

#ifdef USE_ATOM_BUFFERRED_READ
        if (!pstsz->sample_size) // there is no stsz table if sample size is fixed
        {
            update_atom_cache_and_table_size(ctx, pAtom, &pstsz->cache_page, &pstsz->cache_size, &pstsz->table_size, sizeof(STSZ_ENTRY), pstsz->sample_count);
            read_first_atom_cache(pAtom->m_pFile, pstsz->cache_page, pstsz->cache_size, pstsz->table_size, &pstsz->page_idx);
        }
#endif
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("stsc"))
    {
        STSCPROP *pstsc = MP4AtomAllocateProp(ctx, pAtom, sizeof(STSCPROP));

        if (!pstsc)
            return MSMERR_OUT_OF_MEMORY;

        pstsc->version_flag = MP4FileReadUInt32(pAtom->m_pFile);
        pstsc->entry_count = MP4FileReadUInt32(pAtom->m_pFile);
        pstsc->entry_file_pos = MP4FileGetPosition(pAtom->m_pFile);

#ifdef USE_ATOM_BUFFERRED_READ
        update_atom_cache_and_table_size(ctx, pAtom, &pstsc->cache_page, &pstsc->cache_size, &pstsc->table_size, sizeof(STSC_ENTRY), pstsc->entry_count);
        read_first_atom_cache(pAtom->m_pFile, pstsc->cache_page, pstsc->cache_size, pstsc->table_size, &pstsc->page_idx);
#endif
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("stco") || ATOMID(pAtom->m_type) == ATOMID("co64"))
    {
        STCOPROP *pstco = MP4AtomAllocateProp(ctx, pAtom, sizeof(STCOPROP));

        if (!pstco)
            return MSMERR_OUT_OF_MEMORY;

        pstco->version_flag = MP4FileReadUInt32(pAtom->m_pFile);
        pstco->entry_count = MP4FileReadUInt32(pAtom->m_pFile);
        pstco->entry_file_pos = MP4FileGetPosition(pAtom->m_pFile);
        if (ATOMID(pAtom->m_type) == ATOMID("stco"))
            pstco->entry_byte_count = 4;
        else
            pstco->entry_byte_count = 8;
#ifdef USE_ATOM_BUFFERRED_READ
        update_atom_cache_and_table_size(ctx, pAtom, &pstco->cache_page, &pstco->cache_size, &pstco->table_size, pstco->entry_byte_count, pstco->entry_count);
        read_first_atom_cache(pAtom->m_pFile, pstco->cache_page, pstco->cache_size, pstco->table_size, &pstco->page_idx);
#endif

    }
    else if (ATOMID(pAtom->m_type) == ATOMID("samr"))
    {
        SAMRPROP *psamr = MP4AtomAllocateProp(ctx, pAtom, sizeof(SAMRPROP));

        if (!psamr)
            return MSMERR_OUT_OF_MEMORY;

        MP4FileReadBytes(pAtom->m_pFile, psamr->reserved1, 6);
        psamr->dataReferenceIndex = MP4FileReadUInt16(pAtom->m_pFile);
        MP4FileReadBytes(pAtom->m_pFile, psamr->reserved2, 16);
        psamr->timescale = MP4FileReadUInt16(pAtom->m_pFile);
        MP4FileReadBytes(pAtom->m_pFile, psamr->reserved3, 2);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("damr"))
    {
        DAMRPROP *pdamr = MP4AtomAllocateProp(ctx, pAtom, sizeof(DAMRPROP));

        if (!pdamr)
            return MSMERR_OUT_OF_MEMORY;

        pdamr->vendor = MP4FileReadUInt32(pAtom->m_pFile);
        pdamr->decoderVersion = MP4FileReadUInt8(pAtom->m_pFile);
        pdamr->modeSet = MP4FileReadUInt16(pAtom->m_pFile);
        pdamr->modeChangePeriod = MP4FileReadUInt8(pAtom->m_pFile);
        pdamr->framesPerSample = MP4FileReadUInt8(pAtom->m_pFile);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("s263"))
    {
        S263PROP *ps263 = MP4AtomAllocateProp(ctx, pAtom, sizeof(S263PROP));

        if (!ps263)
            return MSMERR_OUT_OF_MEMORY;

        MP4FileReadBytes(pAtom->m_pFile, ps263->reserved1, 6);
        ps263->dataReferenceIndex = MP4FileReadUInt16(pAtom->m_pFile);
        MP4FileReadBytes(pAtom->m_pFile, ps263->reserved2, 16);
        ps263->width = MP4FileReadUInt16(pAtom->m_pFile);
        ps263->height = MP4FileReadUInt16(pAtom->m_pFile);
        MP4FileReadBytes(pAtom->m_pFile, ps263->reserved3, 50);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("d263"))
    {
        D263PROP *pd263 = MP4AtomAllocateProp(ctx, pAtom, sizeof(D263PROP));

        if (!pd263)
            return MSMERR_OUT_OF_MEMORY;

        pd263->vendor = MP4FileReadUInt32(pAtom->m_pFile);
        pd263->decoderVersion = MP4FileReadUInt8(pAtom->m_pFile);
        pd263->h263Level = MP4FileReadUInt8(pAtom->m_pFile);
        pd263->h263Profile = MP4FileReadUInt8(pAtom->m_pFile);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("esds")) //for MP4V, MP4A
    {
        if (!MP4AtomAllocateProp(ctx, pAtom, sizeof(MP4AV_ESDS)))
            return MSMERR_OUT_OF_MEMORY;
        esds_read(ctx, pAtom, pAtom->m_pProperties);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("glbl")) //for DX50
    {
        if (!MP4AtomAllocateProp(ctx, pAtom, sizeof(MP4AV_ESDS)))
            return MSMERR_OUT_OF_MEMORY;
        glbl_read(ctx, pAtom);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("wave"))
    {
        if (!MP4AtomAllocateProp(ctx, pAtom, sizeof(WAVEPROP)))
            return MSMERR_OUT_OF_MEMORY;
        wave_read(ctx, pAtom);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("avcc")) //for AVC1
    {
        if (!MP4AtomAllocateProp(ctx, pAtom, sizeof(AVCConfig)))
            return MSMERR_OUT_OF_MEMORY;
        avcC_read(ctx, pAtom);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("avss")) //for AVS
    {
        if (!MP4AtomAllocateProp(ctx, pAtom, sizeof(AVSConfig)))
            return MSMERR_OUT_OF_MEMORY;
        avss_read(ctx, pAtom);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("hvcc")) //for HEVC
    {
        if (!MP4AtomAllocateProp(ctx, pAtom, sizeof(AVCConfig)))
            return MSMERR_OUT_OF_MEMORY;
        hevcC_read(ctx, pAtom);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("stss"))
    {
        if (!MP4AtomAllocateProp(ctx, pAtom, sizeof(STSSPROP)))
            return MSMERR_OUT_OF_MEMORY;
        stss_read(ctx, pAtom);
    }
    else if (ATOMID(pAtom->m_type) == ATOMID("meta"))
    {
        MP4FileReadUInt32(pAtom->m_pFile); // skip 4 NULL bytes , in order to let the following 4 bytes be atom size
    }
    else if (ATOMID(pAtom->m_type) ==  ATOMID("mstr"))
    {
        MSTRPROP *pmstr = MP4AtomAllocateProp(ctx, pAtom, sizeof(MSTRPROP));

        if (!pmstr)
            return MSMERR_OUT_OF_MEMORY;

        pmstr->mace = MP4FileReadUInt8(pAtom->m_pFile);
    }

    if (!expect_child)
    {
        if (MP4AtomSkip(pAtom) == (FILE_OFF) -1)
            return MSMERR_DMX_READ_ATOM_FAILED;
    }

    return MSMERR_OK;
}

int MP4AtomRead(void *ctx, MP4ATOM *pAtom)
{
    int ret = MP4AtomReadProperties(ctx, pAtom);

    if (ret != MSMERR_OK)
    {
        return ret;
    }

    // the max m_level will be MP4_MAX_ATOM_DEPTH
    if (pAtom->m_level < MP4_MAX_ATOM_DEPTH)
    {
        ret = MP4AtomReadChildAtoms(ctx, pAtom);
        if (ret != MSMERR_OK)
        {
            return ret;
        }
        if (ATOMID(pAtom->m_type) == ATOMID("trak"))
        {
            // if we are not interested in this hdlr type, then it does not matter whether stsd is parsed
            if (MP4ValidHDLRtype(pAtom->m_pFile->curr_hdlr_type) == 0)
                MP4AtomFreeChild(ctx, &pAtom->m_pChildAtoms);
            else if (!pAtom->m_pFile->stsd_parsed)
            {
                MP4ATOM *pStsdAtom;

                pStsdAtom = MP4AtomFindAtom(pAtom, "mdia.minf.stbl.stsd");
                if (pStsdAtom)
                {
                    FILE_POS cur_pos = MP4FileGetPosition(pAtom->m_pFile);

                    // plus 8 byte for atom size and atom 4cc
                    if (MP4FileSetPosition(pAtom->m_pFile, pStsdAtom->m_start + 8) != (FILE_OFF)-1)
                    {
                        // only free all children of track atom, keep an empty track
                        if (stsd_read(ctx, pStsdAtom, pAtom->m_pFile->curr_hdlr_type) != MSMERR_OK)
                            MP4AtomFreeChild(ctx, &pAtom->m_pChildAtoms);
                    }
                    MP4FileSetPosition(pAtom->m_pFile, cur_pos);
                }
            }
        }
    }

    if (MP4AtomSkip(pAtom) == (FILE_OFF) -1) // to end of atom
        return MSMERR_DMX_READ_ATOM_FAILED;

    return MSMERR_OK;
}

static int MP4AtomReadEnd(MP4FILE* pFile)
{
    // only need to parse the whole moov and the header of mdat
    if (pFile->m_mdat_end && pFile->m_moov_end)
        return MSMERR_OK;
    return MSMERR_FALSE;
}

int MP4AtomReadAtomHeader(MP4FILE* pFile, uint64_t *dataSize, char type[5])
{
    uint8_t hdrSize = 8;
    uint8_t extendedType[16];
    int readsize;
    FILE_POS pos = MP4FileGetPosition(pFile);

    *dataSize = MP4FileReadUInt32(pFile);
    readsize = MP4FileReadBytes(pFile, (uint8_t*)&type[0], 4);
    if (readsize != 4)
        return 0;
    type[4] = '\0';

    // extended size
    if (*dataSize == 1)
    {
        *dataSize = MP4FileReadUInt64(pFile);
        hdrSize += 8;
    }

    // extended type
    if (ATOMID(type) == ATOMID("uuid"))
    {
        readsize = MP4FileReadBytes(pFile, extendedType, sizeof(extendedType));
        if (readsize != sizeof(extendedType))
            return 0;
        hdrSize += sizeof(extendedType);
    }

    if (*dataSize == 0)
    {
        // extends to EOF
        *dataSize = MP4FileGetSize(pFile) - pos;
    }

    *dataSize -= hdrSize;

    return hdrSize;
}

static int MP4AtomReadAtom(void *ctx, MP4FILE* pFile, MP4ATOM* pParentAtom)
{
    uint8_t hdrSize;
    char type[5];
    MP4ATOM* pAtom;
    int ret;
    FILE_POS pos = MP4FileGetPosition(pFile);
    uint64_t dataSize;
    cb_io_st *cbio;

    hdrSize = MP4AtomReadAtomHeader(pFile, &dataSize, type);
    if (hdrSize == 0)
        return MSMERR_DMX_READ_ATOM_FAILED;

    if (pos + hdrSize + dataSize > pParentAtom->m_end)
    {
        // skip to end of atom
        dataSize = pParentAtom->m_end - pos - hdrSize;
    }

    pAtom = CreateAtom(ctx, type);
    if (!pAtom)
        return MSMERR_DMX_READ_ATOM_FAILED;
    pAtom->m_pFile = pFile;
    pAtom->m_start = pos;
    pAtom->m_end = pos + hdrSize + dataSize;
    pAtom->m_size = dataSize;
    pAtom->m_level = pParentAtom->m_level + 1;
#ifdef USE_STREAM_LIB
    cbio = pAtom->m_pFile->cbuffer.input;
#else
    cbio = pAtom->m_pFile->m_cbio;
#endif

    // if get mdat before moov
    if (ATOMID(pAtom->m_type) == ATOMID("mdat"))
    {
#ifdef CACHE_ENTIRE_ATOM
        // call open_done in advance to let streaming VFS could leave sequential download
        // in this way, mp4 demuxer could skip mdat to parse moov
        // bitrate and duration are unknown
        if (cbio->streaming)
            cbio->open_done(cbio, -1, -1, 0);
#endif
        pFile->m_mdat_end = pAtom->m_end;
        if (MP4AtomReadEnd(pFile) == MSMERR_OK)
            return MSMERR_DMX_READ_ATOM_FINISHED;
    }

    // read to the end of target atom in order to reduce rebuffer count
    if (ATOMID(pAtom->m_type) == ATOMID("moov"))
    {
        FILE_POS curpos = MP4FileGetPosition(pFile);

#ifdef CACHE_ENTIRE_ATOM
        // if moov atom is too large, memory 1 in streaming module may not be sufficient
        // so call open_done in advance to disable sequential download
        if (cbio->streaming && pAtom->m_end > STREAM_MOOV_SIZE_LIMIT)
            cbio->open_done(cbio, -1, -1, 0);
        else
#endif
        {
            if (MP4AtomSkip(pAtom) == (FILE_OFF) -1) // to end of atom
                return MSMERR_DMX_READ_ATOM_FAILED;
            // Streaming VFS will not enter rebuffer when demuxer seek
            // so we need to read extra bytes
            MP4FileReadUInt16(pAtom->m_pFile);
            MP4FileSetPosition(pAtom->m_pFile, curpos);
        }
    }

    ret = MP4AtomRead(ctx, pAtom);
    if (ret != MSMERR_OK && ret != MSMERR_DMX_READ_ATOM_FINISHED)
        return MSMERR_DMX_READ_ATOM_FAILED;

    MP4AtomArrayAdd(&pParentAtom->m_pChildAtoms, pAtom);

    if (ATOMID(pAtom->m_type) == ATOMID("moov"))
    {
        assert(ret == MSMERR_OK);
        pFile->m_moov_end = pAtom->m_end;
        if (MP4AtomReadEnd(pFile) == MSMERR_OK)
            return MSMERR_DMX_READ_ATOM_FINISHED;
    }
    return ret;
}

int MP4AtomReadChildAtoms(void *ctx, MP4ATOM *pAtom)
{
    FILE_POS position, ix;
    uint16_t this_is_udta = 0;
    uint32_t mbz;

    this_is_udta = ATOMID(pAtom->m_type) == ATOMID("udta");

    for (position = MP4FileGetPosition(pAtom->m_pFile); position < pAtom->m_end;
                                                                position = MP4FileGetPosition(pAtom->m_pFile))
    {
        int ret;
        // make sure that we have enough to read at least 8 bytes
        // size and type.
        if (pAtom->m_end - position < 2 * sizeof(uint32_t))
        {
            // if we're reading udta, it's okay to have 4 bytes of 0
            if (this_is_udta && pAtom->m_end - position == sizeof(uint32_t))
            {
                mbz = MP4FileReadUInt32(pAtom->m_pFile);
                if (mbz != 0)
                {
                    return MSMERR_DMX_READ_ATOM_FAILED; // need error handling in the future
                }
                continue;
            }

            for (ix = 0; ix < pAtom->m_end - position; ix++)
            {
                MP4FileReadUInt8(pAtom->m_pFile);
            }
            continue;
        }

        ret = MP4AtomReadAtom(ctx, pAtom->m_pFile, pAtom);

        // keep parsing the next atom if ret is MSMERR_OK
        // stop parsing the next atom if there is error or the target atom is parsed
        if (ret != MSMERR_OK)
        {
            return ret;
        }
    }

    return MSMERR_OK;
}
