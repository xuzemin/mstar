////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011-2013 MStar Semiconductor, Inc.
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


#include <assert.h>
#include <string.h>
#include "mvc_demuxer.h"
#include "ms_dprintf.h"
#include "sys_common.h"

#define SYS_PTS_DIFF_THRESHOLD        (10 * 1000000) // unit: us, 10 seconds

int sys_is_equal_guid(const guid_st *g1, const guid_st *g2)
{
    return !memcmp(g1, g2, sizeof(guid_st));
}

MVCAudioType sys_msft_format_tag_to_acodec(int format_tag)
{
    MVCAudioType acodec;

    switch (format_tag)
    {
    case MSFT_AUDIO_MS_ADPCM:
    case MSFT_AUDIO_IMA_ADPCM_MS:
    case MSTAR_AUDIO_IMA_ADPCM_QT:
        acodec = CLIP_AUDIO_TYPE_ADPCM;
        break;
    case MSFT_AUDIO_PCM:
    case MSTAR_AUDIO_PCM_U_LE:
    case MSTAR_AUDIO_PCM_U_BE:
    case MSTAR_AUDIO_PCM_S_LE:
    case MSTAR_AUDIO_PCM_S_BE:
        acodec = CLIP_AUDIO_TYPE_LPCM;
        break;
    case MSFT_AUDIO_MULAW:
    case MSFT_AUDIO_ALAW:
        acodec = CLIP_AUDIO_TYPE_PCM;
        break;
    case MSFT_AUDIO_MP3:
    case MSFT_AUDIO_MPG:
        acodec = CLIP_AUDIO_TYPE_MP3;
        break;
    case MSFT_AUDIO_AAC:
    case MSFT_AUDIO_FAAC:
        acodec = CLIP_AUDIO_TYPE_AAC;
        break;
    case MSFT_AUDIO_AMR:
        acodec = CLIP_AUDIO_TYPE_AMRNB;
        break;
    case MSFT_AUDIO_AC3:
    case MSFT_AUDIO_AC3_SPDIF:
        acodec = CLIP_AUDIO_TYPE_AC3;
        break;
    case MSFT_AUDIO_WMA1:
        acodec = CLIP_AUDIO_TYPE_WMA1;
        break;
    case MSFT_AUDIO_WMA2:
        acodec = CLIP_AUDIO_TYPE_WMA2;
        break;
    case MSFT_AUDIO_WMA3:
        acodec = CLIP_AUDIO_TYPE_WMA3;
        break;
    case MSFT_AUDIO_VORBIS:
        acodec = CLIP_AUDIO_TYPE_VORBIS;
        break;
    case MSFT_AUDIO_DTS:
        acodec = CLIP_AUDIO_TYPE_DTS;
        break;
    default:
        acodec = CLIP_AUDIO_TYPE_UNKNOWN;
        ms_dprintf(1, "[DMX] wFormatTag = %02X\n", format_tag);
        break;
    }

    return acodec;
}

static MVCAudioType sys_msft_format_extensible_to_acodec(const uint8_t *config, uint32_t config_len)
{
    // see <ksmedia.h> for more GUID definition
    static const guid_st wfex_guid = {0x00000000, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9b, 0x71}};
    guid_st guid;
    uint16_t format;

    if (config_len < sizeof(msft_audio_header_st) + 24)
    {
        ms_dprintf(1, "[DMX] Invalid WAVEFORMATEXTENSIBLE size = %d\n", config_len);
        return CLIP_AUDIO_TYPE_UNKNOWN;
    }

    memcpy(&guid, config + sizeof(msft_audio_header_st) + 8, sizeof(guid_st));

    format = guid.data1;
    guid.data1 = 0;

    if (!sys_is_equal_guid(&guid, &wfex_guid))
    {
        ms_dprintf(1, "[DMX] Unknown sub-format GUID\n");
        return CLIP_AUDIO_TYPE_UNKNOWN;
    }

    return sys_msft_format_tag_to_acodec(format);
}

MVCVideoType sys_msft_fourcc_to_vcodec(uint32_t fourcc)
{
    uint32_t fcc = READ_BE32(&fourcc);
    MVCVideoType vcodec;

    if (fcc == READ_BE32("MP4S")) {
        vcodec = CLIP_VIDEO_TYPE_MP4S;
    } else if (fcc == READ_BE32("M4S2")) {
        vcodec = CLIP_VIDEO_TYPE_M4S2;
    } else if (fcc == READ_BE32("MP4V")) {
        vcodec = CLIP_VIDEO_TYPE_M4V;
    } else if (fcc == READ_BE32("mp4v")) {
        vcodec = CLIP_VIDEO_TYPE_M4V;
    } else if (fcc == READ_BE32("FMP4")) {
        vcodec = CLIP_VIDEO_TYPE_M4V;
    } else if (fcc == READ_BE32("DX50")) {
        vcodec = CLIP_VIDEO_TYPE_DX50;
    } else if (fcc == READ_BE32("XVID")) {
        vcodec = CLIP_VIDEO_TYPE_M4V;
    } else if (fcc == READ_BE32("xvid")) {
        vcodec = CLIP_VIDEO_TYPE_M4V;
    } else if (fcc == READ_BE32("MPG4")) {
        vcodec = CLIP_VIDEO_TYPE_MP41;
    } else if (fcc == READ_BE32("MP42")) {
        vcodec = CLIP_VIDEO_TYPE_MP42;
    } else if (fcc == READ_BE32("MP43")) {
        vcodec = CLIP_VIDEO_TYPE_DIV3;
    } else if (fcc == READ_BE32("DIV3")) {
        vcodec = CLIP_VIDEO_TYPE_DIV3;
    } else if (fcc == READ_BE32("DIVX")) {
        vcodec = CLIP_VIDEO_TYPE_DIVX;
    } else if (fcc == READ_BE32("divx")) {
        vcodec = CLIP_VIDEO_TYPE_DIVX;
    } else if (fcc == READ_BE32("flv\0")) {
        vcodec = CLIP_VIDEO_TYPE_FLV1;
    } else if (fcc == READ_BE32("H263")) {
        vcodec = CLIP_VIDEO_TYPE_H263;
    } else if (fcc == READ_BE32("h263")) {
        vcodec = CLIP_VIDEO_TYPE_H263;
    } else if (fcc == READ_BE32("mjpg")) {
        vcodec = CLIP_VIDEO_TYPE_MJPG;
    } else if (fcc == READ_BE32("MJPG")) {
        vcodec = CLIP_VIDEO_TYPE_MJPG;
    } else if (fcc == READ_BE32("X264")) {
        vcodec = CLIP_VIDEO_TYPE_AVC1;
    } else if (fcc == READ_BE32("x264")) {
        vcodec = CLIP_VIDEO_TYPE_AVC1;
    } else if (fcc == READ_BE32("avc1")) {
        vcodec = CLIP_VIDEO_TYPE_AVC1;
    } else if (fcc == READ_BE32("H264")) {
        vcodec = CLIP_VIDEO_TYPE_AVC1;
    } else if (fcc == READ_BE32("h264")) {
        vcodec = CLIP_VIDEO_TYPE_AVC1;
    } else if (fcc == READ_BE32("mpg1")) {
        vcodec = CLIP_VIDEO_TYPE_MP2V;
    } else if (fcc == READ_BE32("mpg2")) {
        vcodec = CLIP_VIDEO_TYPE_MP2V;
    } else if (fcc == READ_BE32("MPEG")) {
        vcodec = CLIP_VIDEO_TYPE_MP2V;
    } else if (fcc == READ_BE32("CRAM")) {
        vcodec = CLIP_VIDEO_TYPE_MSVC;
    } else if (fcc == READ_BE32("VP6F")) {
        vcodec = CLIP_VIDEO_TYPE_VP60;
    } else if (fcc == READ_BE32("WMV3")) {
        vcodec = CLIP_VIDEO_TYPE_WMV3;
    } else if (fcc == READ_BE32("WMV2")) {
        vcodec = CLIP_VIDEO_TYPE_WMV2;
    } else if (fcc == READ_BE32("WMV1")) {
        vcodec = CLIP_VIDEO_TYPE_WMV1;
    } else if (fcc == READ_BE32("WMVA")) {
        vcodec = CLIP_VIDEO_TYPE_WMVA;
    } else if (fcc == READ_BE32("WVC1")) {
        vcodec = CLIP_VIDEO_TYPE_WVC1;
    } else if (fcc == READ_BE32("IV32")) {
        vcodec = CLIP_VIDEO_TYPE_IV32;
    } else if (fcc == READ_BE32("iv32")) {
        vcodec = CLIP_VIDEO_TYPE_IV32;
    } else if (fcc == READ_BE32("IV41")) {
        vcodec = CLIP_VIDEO_TYPE_IV41;
    } else if (fcc == READ_BE32("iv41")) {
        vcodec = CLIP_VIDEO_TYPE_IV41;
    } else if (fcc == READ_BE32("DVSD")) {
        vcodec = CLIP_VIDEO_TYPE_DVSD;
    } else if (fcc == READ_BE32("dvsd")) {
        vcodec = CLIP_VIDEO_TYPE_DVSD;
    } else {
        vcodec = CLIP_VIDEO_TYPE_UNKNOWN;
        ms_dprintf(1, "[DMX] %c %c %c %c\n", (char) (fcc >> 24), (char) (fcc >> 16), (char) (fcc >> 8), (char) fcc);
    }

    return vcodec;
}

int sys_is_codec_PCM(sys_stream_st *s)
{
    return s->codec_type == CLIP_AUDIO_TYPE_PCM || s->codec_type == CLIP_AUDIO_TYPE_LPCM || s->codec_type == CLIP_AUDIO_TYPE_ADPCM ;
}

int sys_msft_parse_audio_header(sys_demuxer_st *d, sys_stream_st *s, uint32_t *size)
{
    msft_audio_header_st aheader;
    uint8_t *config;
    int len;

    assert(s->config_len);
    // read WAVEFORMATEX (FIXME: not portable)
    if (d->cbuffer.cb_read(&d->cbuffer, &aheader, sizeof(aheader)) != sizeof(aheader))
        return MVC_EndOfStream;
    *size -= sizeof(aheader);

    s->info.aud.ch_num      = aheader.channels;
    s->info.aud.sample_rate = aheader.sample_rate;
    s->info.aud.sample_size = aheader.block_align;
    s->info.aud.sample_depth = aheader.sample_depth;
    s->info.aud.bit_rate    = aheader.bit_rate * 8;
    s->config_len           = SYS_MIN(*size + sizeof(aheader), s->config_len);

    memcpy(s->config, &aheader, sizeof(aheader));

    config = s->config;
    len = s->config_len - sizeof(aheader);

    if (s->config_len > sizeof(aheader))
    {
        if (d->cbuffer.cb_read(&d->cbuffer, config + sizeof(aheader), len) < len)
            return MVC_EndOfStream;
        *size -= len;
    }

    // determine codec type
    if (aheader.format_tag == MSFT_AUDIO_EXTENSIBLE)
    {
        s->codec_type = sys_msft_format_extensible_to_acodec(s->config, s->config_len);
    }
    else
    {
        s->codec_type = sys_msft_format_tag_to_acodec(aheader.format_tag);
    }

    // correct config data
    if (s->codec_type != CLIP_AUDIO_TYPE_PCM   &&
        s->codec_type != CLIP_AUDIO_TYPE_LPCM  &&
        s->codec_type != CLIP_AUDIO_TYPE_ADPCM &&
        s->codec_type != CLIP_AUDIO_TYPE_WMA1  &&
        s->codec_type != CLIP_AUDIO_TYPE_WMA2  &&
        s->codec_type != CLIP_AUDIO_TYPE_WMA3)
    {
        int offset = 2;

        if (aheader.format_tag == MSFT_AUDIO_EXTENSIBLE)
            offset = 24;

        if (len <= offset)
            s->config_len = 0;
        else
        {
            memmove(config, config + sizeof(aheader) + offset, len - offset);
            s->config_len = len - offset;
        }
    }

    // detect incorrectly encoded sample size
    if (s->info.aud.sample_size == (uint32_t)aheader.channels * aheader.sample_depth / 8 &&
        s->codec_type == CLIP_AUDIO_TYPE_AAC)
    {
        s->info.aud.sample_size = 0;
    }

    return MVC_OK;
}

int sys_msft_parse_video_header(sys_demuxer_st *d, sys_stream_st *s, uint32_t *size, uint32_t *fourcc)
{
    msft_video_header_st vheader;

    assert(s->config_len);
    // read BITMAPINFO (FIXME: not portable)
    if (d->cbuffer.cb_read(&d->cbuffer, &vheader, sizeof(vheader)) != sizeof(vheader))
        return MVC_EndOfStream;
    *size -= sizeof(vheader);

    s->codec_type      = sys_msft_fourcc_to_vcodec(vheader.compression);
    s->config_len      = SYS_MIN(*size, s->config_len);
    s->info.vid.width  = vheader.width;
    s->info.vid.height = vheader.height;

    if (s->config_len)
    {
        int len = s->config_len;
        if (d->cbuffer.cb_read(&d->cbuffer, s->config, len) < len)
            return MVC_EndOfStream;
        *size -= len;
    }

    *fourcc = vheader.compression;

    return MVC_OK;
}

#ifdef __RTK_OS__
#include "bsp.h"
#include "md5.h"
#include "player_util.h"
#endif

#if defined(SUPPORT_RM_DRM) || defined(SUPPORT_ASF_DRM)
static int check_chipID(uint8_t *checkID)
{
#ifdef __RTK_OS__
    SysPlatformChipType_e chip_type;
    SysPlatformChipTypeGet(&chip_type);

    if (chip_type == SYS_PLATFORM_CHIPTYPE_8533C
        || chip_type == SYS_PLATFORM_CHIPTYPE_8533C1
        || chip_type == SYS_PLATFORM_CHIPTYPE_8533N
        || chip_type == SYS_PLATFORM_CHIPTYPE_8536N)
        return (checkID[0]==0x85 && checkID[1]==0x33);
    else if (chip_type == SYS_PLATFORM_CHIPTYPE_8533D)
        return (checkID[0]==0x85 && checkID[1]==0x34);
    else if (chip_type == SYS_PLATFORM_CHIPTYPE_8532B
        || chip_type == SYS_PLATFORM_CHIPTYPE_8532B2
        || chip_type == SYS_PLATFORM_CHIPTYPE_8533BD
        || chip_type == SYS_PLATFORM_CHIPTYPE_8533BN)
        return (checkID[0]==0x85 && checkID[1]==0x32);
    else if (chip_type == SYS_PLATFORM_CHIPTYPE_8556
        || chip_type == SYS_PLATFORM_CHIPTYPE_8556R
        || chip_type == SYS_PLATFORM_CHIPTYPE_8556R2
        || chip_type == SYS_PLATFORM_CHIPTYPE_8556M
        || chip_type == SYS_PLATFORM_CHIPTYPE_8556M2)
        return (checkID[0]==0x85 && checkID[1]==0x56);
    else if (chip_type == SYS_PLATFORM_CHIPTYPE_8830C
        || chip_type == SYS_PLATFORM_CHIPTYPE_8830N)
        return (checkID[0]==0x88 && checkID[1]==0x30);
    else {
        vm_dbgError(_CUSAVP, "Check_chipID error: %d 0x%x 0x%x\n", chip_type, checkID[0], checkID[1]);
        return 0;
    }
#endif

    return 1;
}
#endif

//ret: 1: drm pass
//     0: drm fail
int sys_check_drm(MMP_KEY_e type)
{
    int pass_drm = 1;
    uint8_t checkID[25];

    if (MMP_GetKey(checkID, type) < 0)
        return 0;

    switch (type)
    {
#ifdef SUPPORT_RM_DRM
        case KEY_RMVB:
            //vm_dbgError(_CUSAVP, "e2p value video %d %d %d %d\n", checkID[0], checkID[1], checkID[2], checkID[3]);
            //we don't decode any audio or video if RM license failed.
            if ((checkID[7]&1) == 0 || check_chipID(checkID) == 0 || MD_check_play(checkID) == 0)
                pass_drm = 0;
            break;
#endif
#ifdef SUPPORT_ASF_DRM
        case KEY_ASF:
            if ((checkID[7]&6) == 0 || check_chipID(checkID) == 0 || MD_check_play(checkID) == 0)
                pass_drm = 0;
            break;
#endif
        default:
            break;
    }
    return pass_drm;
}

int sys_notify(sys_demuxer_st *d, mvc_stream_type_et type, mvc_event_et event)
{
    return d->callback.notify(d->callback.context, type, event);
}

void *sys_malloc(sys_demuxer_st *d, size_t size)
{
    return d->callback.malloc(d->callback.context, size);
}

void sys_freep(sys_demuxer_st *d, void **p)
{
    d->callback.freep(d->callback.context, p);
}

int sys_stream_alloc(sys_demuxer_st *d, mvc_stream_type_et type, void **buffer, int size)
{
    return d->callback.stream_alloc(d->callback.context, type, buffer, size);
}

int sys_stream_discard(sys_demuxer_st *d, mvc_stream_type_et type)
{
    return d->callback.stream_discard(d->callback.context, type);
}

int sys_stream_commit(sys_demuxer_st *d, mvc_stream_type_et type, int size, int64_t pts, int64_t duration, int packet_type)
{
    return d->callback.stream_commit(d->callback.context, type, size, pts, duration, packet_type);
}

int sys_stream_realloc(sys_demuxer_st *d, mvc_stream_type_et type, void **buffer, int size)
{
    return d->callback.stream_realloc(d->callback.context, type, buffer, size);
}

int sys_stream_send_config(sys_demuxer_st *d, sys_stream_st *s)
{
    void *buffer = NULL;

    if (sys_stream_alloc(d, s->stream_type, &buffer, s->config_len + 4) != MVC_OK)
        return MVC_NotEnoughMemory;

    memcpy(buffer, &s->codec_type, 4);
    if (s->config_len)
    {
        memcpy((uint8_t *) buffer + 4, s->config, s->config_len);
    }
    sys_stream_commit(d, s->stream_type, s->config_len + 4, 0, 0, 1);

    return MVC_OK;
}

void sys_set_info_from_string(mvc_data_info_st *info, char *string)
{
    info->length  = string ? strlen(string) + 1 : 0;  // 1 for terminate char in UTF8
    info->payload = (unsigned char *) string;
}

/* http://www.loc.gov/standards/iso639-2/php/English_list.php */
static const char *lang_code[][2] =
{
    { "ab", "abk" },
    { "aa", "aar" },
    { "af", "afr" },
    { "ak", "aka" },
    { "sq", "alb" },
    { "am", "amh" },
    { "ar", "ara" },
    { "an", "arg" },
    { "hy", "arm" },
    { "as", "asm" },
    { "av", "ava" },
    { "ae", "ave" },
    { "ay", "aym" },
    { "az", "aze" },
    { "bm", "bam" },
    { "ba", "bak" },
    { "eu", "baq" },
    { "be", "bel" },
    { "bn", "ben" },
    { "bh", "bih" },
    { "bi", "bis" },
    { "nb", "nob" },
    { "bs", "bos" },
    { "br", "bre" },
    { "bg", "bul" },
    { "my", "bur" },
    { "es", "spa" },
    { "ca", "cat" },
    { "km", "khm" },
    { "ch", "cha" },
    { "ce", "che" },
    { "ny", "nya" },
    { "zh", "chi" },
    { "za", "zha" },
    { "cu", "chu" },
    { "cv", "chv" },
    { "kw", "cor" },
    { "co", "cos" },
    { "cr", "cre" },
    { "hr", "hrv" },
    { "cs", "cze" },
    { "da", "dan" },
    { "dv", "div" },
    { "nl", "dut" },
    { "dz", "dzo" },
    { "en", "eng" },
    { "eo", "epo" },
    { "et", "est" },
    { "ee", "ewe" },
    { "fo", "fao" },
    { "fj", "fij" },
    { "fi", "fin" },
    { "fr", "fre" },
    { "ff", "ful" },
    { "gd", "gla" },
    { "gl", "glg" },
    { "lg", "lug" },
    { "ka", "geo" },
    { "de", "ger" },
    { "ki", "kik" },
    { "el", "gre" },
    { "kl", "kal" },
    { "gn", "grn" },
    { "gu", "guj" },
    { "ht", "hat" },
    { "ha", "hau" },
    { "he", "heb" },
    { "hz", "her" },
    { "hi", "hin" },
    { "ho", "hmo" },
    { "hu", "hun" },
    { "is", "ice" },
    { "io", "ido" },
    { "ig", "ibo" },
    { "id", "ind" },
    { "ia", "ina" },
    { "ie", "ile" },
    { "iu", "iku" },
    { "ik", "ipk" },
    { "ga", "gle" },
    { "it", "ita" },
    { "ja", "jpn" },
    { "jv", "jav" },
    { "kn", "kan" },
    { "kr", "kau" },
    { "ks", "kas" },
    { "kk", "kaz" },
    { "rw", "kin" },
    { "ky", "kir" },
    { "kv", "kom" },
    { "kg", "kon" },
    { "ko", "kor" },
    { "kj", "kua" },
    { "ku", "kur" },
    { "lo", "lao" },
    { "la", "lat" },
    { "lv", "lav" },
    { "lb", "ltz" },
    { "li", "lim" },
    { "ln", "lin" },
    { "lt", "lit" },
    { "lu", "lub" },
    { "mk", "mac" },
    { "mg", "mlg" },
    { "ms", "may" },
    { "ml", "mal" },
    { "mt", "mlt" },
    { "gv", "glv" },
    { "mi", "mao" },
    { "mr", "mar" },
    { "mh", "mah" },
    { "ro", "rum" },
    { "mn", "mon" },
    { "na", "nau" },
    { "nv", "nav" },
    { "nd", "nde" },
    { "nr", "nbl" },
    { "ng", "ndo" },
    { "ne", "nep" },
    { "se", "sme" },
    { "no", "nor" },
    { "nn", "nno" },
    { "ii", "iii" },
    { "oc", "oci" },
    { "oj", "oji" },
    { "or", "ori" },
    { "om", "orm" },
    { "os", "oss" },
    { "pi", "pli" },
    { "pa", "pan" },
    { "ps", "pus" },
    { "fa", "per" },
    { "pl", "pol" },
    { "pt", "por" },
    { "qu", "que" },
    { "rm", "roh" },
    { "rn", "run" },
    { "ru", "rus" },
    { "sm", "smo" },
    { "sg", "sag" },
    { "sa", "san" },
    { "sc", "srd" },
    { "sr", "srp" },
    { "sn", "sna" },
    { "sd", "snd" },
    { "si", "sin" },
    { "sk", "slo" },
    { "sl", "slv" },
    { "so", "som" },
    { "st", "sot" },
    { "su", "sun" },
    { "sw", "swa" },
    { "ss", "ssw" },
    { "sv", "swe" },
    { "tl", "tgl" },
    { "ty", "tah" },
    { "tg", "tgk" },
    { "ta", "tam" },
    { "tt", "tat" },
    { "te", "tel" },
    { "th", "tha" },
    { "bo", "tib" },
    { "ti", "tir" },
    { "to", "ton" },
    { "ts", "tso" },
    { "tn", "tsn" },
    { "tr", "tur" },
    { "tk", "tuk" },
    { "tw", "twi" },
    { "ug", "uig" },
    { "uk", "ukr" },
    { "ur", "urd" },
    { "uz", "uzb" },
    { "ve", "ven" },
    { "vi", "vie" },
    { "vo", "vol" },
    { "wa", "wln" },
    { "cy", "wel" },
    { "fy", "fry" },
    { "wo", "wol" },
    { "xh", "xho" },
    { "yi", "yid" },
    { "yo", "yor" },
    { "zu", "zul" },
    {   "",    "" },
};

char *sys_alpha2_to_alpha3(const char *code)
{
    int i;

    for (i = 0; lang_code[i][0][0] != '\0'; i++)
    {
        if (!memcmp(code, lang_code[i][0], 2))
            return (char *) lang_code[i][1];
    }
    return 0;
}

int sys_get_cur_stream_num(sys_demuxer_st *d)
{
    return d->num_streams[AUD] + d->num_streams[VID] +
           d->num_streams[SUB] + d->num_streams[OTH];
}

void sys_set_pts_info(sys_demuxer_st *d, int64_t seek_time)
{
    int i;
    d->seek_time = seek_time;
    for (i = 0; i <= SUB; i++)
    {
        d->last_pts[i] = seek_time;
        d->last_dur[i] = -1;
    }
}

void sys_update_and_fix_pts_gap(sys_demuxer_st *d, int64_t *pts, mvc_stream_type_et type)
{
    int64_t *last_dur, *last_pts;

    if (type == MVC_STREAM_AUDIO)
    {
        last_dur = &d->last_dur[AUD];
        last_pts = &d->last_pts[AUD];
    }
    else if (type == MVC_STREAM_VIDEO)
    {
        last_dur = &d->last_dur[VID];
        last_pts = &d->last_pts[VID];
    }
    else
        return; // no pts correction for subtitle since subtitle pts will not be continuous naturally

    // can't judge for -1 pts
    if (*pts == -1)
        return;

    if (*last_dur == -1)
    {
        *last_dur = 0;
        if (SYS_ABS(*pts - d->seek_time) > SYS_PTS_DIFF_THRESHOLD)
            *pts = d->seek_time;
    }
    else
    {
        if (SYS_ABS(*pts - *last_pts) > SYS_PTS_DIFF_THRESHOLD)
        {
            if (*last_dur == 0) // can't decide next pts, we only know it is not valid
                *pts = -1;
            else
                *pts = *last_pts + *last_dur;
        }
        else
            *last_dur = *pts - *last_pts;
    }

    if (*pts != -1)
        *last_pts = *pts;
}

void sys_reset_drop_target(sys_stream_st *s)
{
    s->next_pos = -1;
}

void sys_set_drop_target(mvc_stream_type_et target_type, sys_stream_st *s, cb_fpos current_pos)
{
    if (s->stream_type == target_type)
    {
        if (s->next_pos != (cb_fpos) -1)
            s->next_pos = -1;
        return;
    }

    if (s->next_pos != (cb_fpos) -1)
        return;

    s->next_pos = current_pos;
    ms_dprintf(1, "[SYS] set drop target, target type %d, stream type %d, pos %lld\n", target_type, s->stream_type, s->next_pos);
}

int sys_check_drop(sys_demuxer_st *d, sys_stream_st *s)
{
    if (s->next_pos == (cb_fpos) -1)
        return 0;

    if (cb_tell64(&d->cbuffer) < s->next_pos)
        return 1;

    s->next_pos = -1;
    ms_dprintf(1, "[SYS] reset target pos for type %d\n", s->stream_type);
    return 0;
}

static const unsigned int aac_sample_rates[16] =
{
    96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050,
    16000, 12000, 11025,  8000,  7350,     0,     0,     0
};

static int sys_aac_get_sample_rate_index(uint32_t sample_rate)
{
    unsigned int i;

    for (i = 0; i < sizeof(aac_sample_rates) / sizeof(unsigned int); i++)
        if (sample_rate == aac_sample_rates[i])
            break;

    return i;
}

void sys_update_aac_config(sys_demuxer_st *d, uint8_t **config, uint32_t *config_len, aac_parameter_st *aac_par)
{
    // create 2byte/5byte config for AAC/AAC with SBR
    int sample_index;
    uint8_t *config_data;

    // if config already exist, trust original config length
    if (!*config)
    {
        if (aac_par->sbr)
            *config_len = 5;
        else
            *config_len = 2;

        if (d)
            *config = sys_malloc(d, *config_len);
    }

    if (!*config || *config_len < 2)
    {
        *config_len = 0;
        return;
    }

    config_data = *config;

    sample_index = sys_aac_get_sample_rate_index(aac_par->sample_rate);
    config_data[0] = (aac_par->object_type << 3) | ((sample_index & 0x0E) >> 1);
    config_data[1] = ((sample_index & 0x01) << 7) | (aac_par->channels << 3);

    if (aac_par->sbr && *config_len >= 5)
    {
        sample_index = sys_aac_get_sample_rate_index(aac_par->ext_sample_rate);
        config_data[2] = 0x56;
        config_data[3] = 0xE5;
        config_data[4] = 0x80 | (sample_index << 3);
    }
}

