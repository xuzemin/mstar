//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MAPP_MUSIC_H
#define MAPP_MUSIC_H

//-------------------------------------------------------------------------------------------------
// Standard include files:
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "msAPI_Music.h"
#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "MApp_UiMediaPlayer_Define.h"
#include "msAPI_FSCommon.h"


#ifdef MAPP_MUSIC_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#ifndef M4APARSER
#define M4APARSER
#endif

#ifndef OGG_PARSER
#define OGG_PARSER
#endif

#ifndef DTS_PARSER
#define DTS_PARSER
#endif

#ifdef M4APARSER
#define M4APARSER_DBG
#define AAC_DBG(x) //x
#define AAC_ERR(x) //x
#define AAC_ERR2(x) //x
#define AAC_ERR3(x)  //x

#define STSC_ENTRY_LIMIT 128

#define MP3_TOC_LEN 100

#define STSC_INFO_ENTRY_INFO_COUNT 3  //for two dimesion array boxM4a.stscInfo.u32EntryInfo[u32totalEntry][2]

typedef enum
{
    EN_MUSIC_MP3,              /// MP3
    EN_MUSIC_AAC,              /// AAC
    EN_MUSIC_WAV,              /// WAV
    EN_MUSIC_LOAS,              /// LOAS
    EN_MUSIC_PCM,              /// PCM
#ifdef OGG_PARSER
    EN_MUSIC_OGG,              /// OGG
#endif
    EN_MUSIC_AMR,               /// AMR
    EN_MUSIC_AWB,               /// AWB
    EN_MUSIC_FLAC,              /// FLAC
    EN_MUSIC_AC3,              /// AC3
    EN_MUSIC_NUM,              /// Total Number
} EN_MUSIC_TYPE;


typedef struct
{
    U16 u16Channel;//now, for ogg and AC3 only
    U16 u16BitRate;
    U32 u32SampleRate;
    U8 u8Flag;
    EN_MP3_VERSION enVersion;
    EN_MP3_LAYER enLayer;

    BOOLEAN bID3TagV1;
    U16 u16ID3TagV1Size;
    BOOLEAN bID3TagV2;
    U32 u32ID3TagV2Size;
    BOOLEAN bCheckFfFb;
    MP3_INFO stID3v1;
    MP3_INFO stID3v2;

    U32 u32FileSize;
    U32 u32MusicDataBytesLeft;
    U32 u32Duration;
    U32 u32CurrentPlayTime;
    U32 u32PlayTimer;
    U16 u16TOCLength;
    U8 u8TOC[MP3_TOC_LEN]; // Table of Contents for VBR file seek
} ST_MP3_INFO;




#define PROBE_MUSIC_INFO_LENGTH 128
#define PROBE_MUSIC_INFO_YEAR_LENGTH 32

typedef struct
{
    U8 u8Title[PROBE_MUSIC_INFO_LENGTH];
    U8 u8Artist[PROBE_MUSIC_INFO_LENGTH];
    U8 u8Album[PROBE_MUSIC_INFO_LENGTH];
    U8 u8Year[PROBE_MUSIC_INFO_YEAR_LENGTH];
    U16 u16BitRate;
    U32 u32SampleRate;
    U32 u32Duration;
    U32 u32PicOffset;
    U32 u32PicSize;
} ST_MUSIC_PROBE_INFO;


typedef struct{
    U32 u32CurrentEntry;
    U32 u32TotalEntry;
    U32 *pu32EntryInfo; //[0]:first_chunk      [1]:samples_per_chunk   [2]:Total samples
} ST_STSC_INFO;


typedef struct   {
    /// ftyp tag
    BOOLEAN bFoundftyp;
    /// moov tag
    BOOLEAN bFoundmoov;
    /// mvhd tag
    BOOLEAN bFoundmvhd;
    /// trak tag
    BOOLEAN bFoundtrak;
    /// mdia tag
    BOOLEAN bFoundmdia;
    /// mdhd tag
    BOOLEAN bFoundmdhd;
    /// duration from track
    U32 u32DurationFromTrack;
    /// hdlr_vide tag
    BOOLEAN bFoundhdlr_vide;
    /// udta tag
    BOOLEAN bFoundudta;
    /// meta hdlr tag
    BOOLEAN bFoundmeta_hdlr;
    /// minf tag
    BOOLEAN bFoundminf;
    /// stbl tag
    BOOLEAN bFoundstbl;
    /// stsd tag
    BOOLEAN bFoundstsd;
    /// stsd sample rate
    U32 u32StsdSampleRate;
    /// esds tag
    BOOLEAN bFoundesds;
    /// stsz tag
    BOOLEAN bFoundstsz;
    /// stsz location
    U32 u32stszLocation;
    /// stsz size
    U32 u32stszSize;
    /// stsc tag
    BOOLEAN bFoundstsc;
    /// stsc location
    U32 u32stscLocation;
    /// stsc size
    U32 u32stscSize;
    /// stsc info
    ST_STSC_INFO stscInfo;
    /// stco tag
    BOOLEAN bFoundstco;
    /// stco entry
    U32 u32stcoEntry;
    /// stco frame location
    U32 u32stcoFrameLocation;
    /// co64 tag
    BOOLEAN bFoundco64;
    /// co64 entry
    U32 u32co64Entry;
    /// co64 frame location
    U32 u32co64FrameLocation;
    /// mdat tag
    BOOLEAN bFoundmdat;
    /// mdat location
    U32 u32MdatLocation;
    /// mdat size
    U32 u32MdatSize;
    /// duration
    U32 u32Duration;
    /// sample rate index
    U8 u8SampleRateIndex;
    /// channel configuration
    U8 u8channelConfiguration;
    /// M4A header
    BOOLEAN bM4aHeader;
    /// frame jump
    BOOLEAN bFrameJump;
    /// m4a object type
    U8 u8object_type;
    /// codec type
    EN_MUSIC_TYPE enCodec;
    /// file size
    U32 u32FileSize;

} ST_M4A_INFO; //BoxInfo;

typedef enum
{
    E_MUSIC_ERR_NONE = 0,
    E_MUSIC_ERR_NOT_SUPPORT_CHANNEL_NUM,
    E_MUSIC_ERR_NOT_SUPPORT_SAMPLE_RATE,
    E_MUSIC_ERR_DECODE_HEADER_FAILURE,
    E_MUSIC_ERR_DECODE_FAILURE,
    E_MUSIC_ERR_DATA_OPERATION_FAILURE,
    E_MUSIC_ERR_NOT_SUPPORT_AAC_PROFILE,
} EN_MUSIC_ERRCODE;

//This enum definition is the same with enumMPlayerMusicInfo in mapp_mplayer.h
//You must sync these two enum
typedef enum
{
    E_MUSIC_INFO_BASIC = 0x01,
    E_MUSIC_INFO_DURATION = 0x02
} EN_MUSIC_INFO;

INTERFACE BOOLEAN M4AParser_Get_M4A_Info(ST_M4A_INFO *boxInfo);
U8 M4AParser_GetSampleRateIndex(U32 dwValue);
BOOLEAN M4AParser_WriteDSP(U32 dwReqAddress, U32 u32ReqBytes);
BOOLEAN M4AParser_WriteDSPNoHead(U32 dwReqAddress, U32 u32ReqBytes);
U32 M4AParser_SetCurrentFrameIndex(void);
BOOLEAN M4AParser_SetFrameIndexbyBtn(U8 u8Mode);
BOOLEAN M4AParser_SaveFrameLocation(void);
U32 M4aParser_GetOneStcoEntryFromDRAM(U32 u32Index);
U32 M4aParser_GetOneCo64EntryFromDRAM(U32 u32Index);
U32 M4aParser_GetOneStszEntryFromDRAM(U32 u32Index);

#endif

#ifdef OGG_PARSER
#define OGGPARSER_DBG
#define OGG_INFO(x)//x
#define OGG_DBG(x) //x
#define OGG_DBG2(x) //x
#define OGG_ERR(x) x
#endif
//WAV
#define WAV_DBG(x) //x
#define WAV_ERR(x) x


#define FLAC_DBG(x)  //x
#define FLAC_ERR(x)  x

#define AC3_DBG(x)  //x
#define AC3_ERR(x)  x

#define AMR_DBG(x)  //x
#define AMR_ERR(x)  x

#define RIFF_TAG_RIFF    0x52494646 // 'RIFF'
#define RIFF_TAG_WAVE    0x57415645 // 'WAVE'
#define RIFF_TAG_fmt    0x666D7420 // 'fmt '
#define RIFF_TAG_data    0x64617461 // 'data'

typedef enum
{
    WAVE_FORMAT_PCM = 0x0001, //PCM
    WAVE_FORMAT_M_ADPCM = 0x0002, //M ADPCM
    WAVE_FORMAT_IEEE_FLOAT = 0x0003, //IEEE float
    WAVE_FORMAT_ALAW = 0x0006, //8-bit ITU-T G.711 A-law
    WAVE_FORMAT_MULAW = 0x0007, //8-bit ITU-T G.711 g-law
    WAVE_FORMAT_IMA_ADPCM = 0x0011, //8-bit ITU-T G.711 g-law
    WAVE_FORMAT_EXTENSIBLE = 0xFFFE, //Determined by SubFormat
} EN_WAV_FORMAT_CODE;

typedef struct{
    //ckID;
    U32 u32HeaderSize;
    U32 u32RIFFChunkSize;
    U32 u32fmtChunkSize;
    U32 u32DataChunkSize;
    U16 u16FormatTag;
    U16 u16Channels;
    U32 u32SamplesPerSec;
    U32 u32AvgBytesPerSec;
    U16 u16BlockSize;
    U16 u16BitsPerSample;
    U16 u16CExtensionSize;
    BOOLEAN bIsDTS;
    BOOLEAN bDTSIsLittleEndian;
    //U16 u16ValidBitsPerSample;
    //dwChannelMask;
    //SubFormat;
} ST_WAV_CHUNK;

typedef struct{
    U16 u16FormatTag;
    U16 u16Channels;
    U32 u32SamplesPerSec;
    U32 u32AvgBytesPerSec;
    U16 u16BlockSize;
    U16 u16BitsPerSample;
    BOOLEAN bBigEndian;
    BOOLEAN bIsConfig;
} ST_PCM_PARAM;

//-------------------------------------------------------------------------------------------------
// Project include files:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------

#define USER_MP3_FLASH_END          (USER_LOGO_FLASH_START_ADDR-0x1000)//(FLASH_SIZE)
#define USER_MP3_CAPTURE_TIMEOUT    (8000)

typedef enum
{
    MP3_STATUS_STOP,
    MP3_STATUS_PLAYING,
    MP3_STATUS_PAUSE,
    MP3_STATUS_SCAN,
} MP3_PLAY_STATUS;

typedef enum
{
    STATE_MUSIC_INIT =0,
    STATE_MUSIC_OPEN_FILE,
    STATE_MUSIC_INPUT,
    STATE_MUSIC_WAIT_DECODE_DONE,
    STATE_MUSIC_WAIT,
    STATE_MUSIC_EXIT,
    STATE_MUSIC_STANDBY,
    STATE_MUSIC_SKIP_PLAY_NEXT,
    STATE_MUSIC_SKIP_PLAY_PREV,
    STATE_MUSIC_NONE,
} EN_MUSIC_STATE;

typedef enum
{
    MP3_RETURN_SUCCESS,
    MP3_RETURN_ERR_FILE,
    MP3_RETURN_ERR_NO_ID3,
} EN_MP3_RETURN;


typedef enum
{
    MP3_INFO_LAYER,
    MP3_INFO_BITRATE,
    MP3_INFO_SAMPLINGRATE,
    MP3_INFO_ALBUM,
    MP3_INFO_TITLE,
    MP3_INFO_ARTIST,
    MP3_INFO_YEAR,
    MP3_INFO_GENRE,
    MP3_INFO_COMMENT,
    MP3_INFO_CHECK_FF_FB,
    MP3_INFO_END,
} EN_MP3_INFO;

typedef enum
{
    EN_MP3_SPEED_X1 = 0,
    EN_MP3_SPEED_X2,
    EN_MP3_SPEED_X4,
    EN_MP3_SPEED_X8,
    EN_MP3_SPEED_X16,
    EN_MP3_SPEED_X32,
    EN_MP3_SPEED_MAX = EN_MP3_SPEED_X32,
} EN_MP3_SPEED;


//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef struct
{
    U32 u32Time;
    U16 u16LyricPos;
} Music_Lyric_Tag;

//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Extern Functions
///-------------------------------------------------------------------------------------------------
INTERFACE void MApp_Music_SetFileEntry(FileEntry *pEntry);
INTERFACE EN_RET MApp_Music_Main(EN_MUSIC_TYPE enMusicType);
//INTERFACE BOOLEAN MApp_Music_ProcessKey (void);
INTERFACE EN_MP3_RETURN MApp_Music_GetInfo(MP3_INFO *pMp3InfoPtr);
INTERFACE U32 MApp_Music_GetTotalTime(void);
INTERFACE U32 MApp_Music_GetCurrentTime(void);
INTERFACE U32 MApp_Music_GetCurrentTimeMs(void);
INTERFACE U32 MApp_Music_GetPlayTick(void);
INTERFACE void MApp_Music_LyricInit(void);
INTERFACE BOOLEAN MApp_Music_GetLyricTag(Music_Lyric_Tag *pLyricTag, U32 u32Time);
INTERFACE BOOLEAN MApp_Music_LRC_Lyrics_Parser(U32 u32FileSize);
INTERFACE BOOLEAN MApp_Music_PCM_SetInfo(U16 u16FormatTag, U16 u16Channels, U32 u32SamplesPerSec, U16 u16BitsPerSample, BOOLEAN bBigEndian);
INTERFACE void MApp_Music_Stop(void);
INTERFACE BOOLEAN MApp_Music_Pause(void);
INTERFACE void MApp_Music_Resume(void);
//INTERFACE void MApp_Music_DrawEQ(void);
INTERFACE U8* MApp_Music_GetInfoString(EN_MP3_INFO enInfo, U8* pu8Length);
INTERFACE void MApp_Music_StartCapture(void);
INTERFACE void MApp_Music_StopCapture(void);
INTERFACE U32 MApp_Music_GetRecordingTime(void);

INTERFACE void MApp_Music_Init(void);

#if 0
INTERFACE void MApp_Music_KeySoundEffect_Initial(void);
INTERFACE void MApp_Music_KeySoundEffect_Play(void);
INTERFACE void MApp_Music_KeySoundEffect_Exit(void);
#endif

INTERFACE BOOLEAN MApp_Music_ProcessTimeOffset(U32 u32GotoTimeMs);
INTERFACE BOOLEAN MApp_Music_FastForwardBackward(BOOLEAN bForward, EN_MP3_SPEED eSpeed);
INTERFACE EN_MUSIC_ERRCODE MApp_Music_GetErrCode(void);
INTERFACE void MApp_Music_StopAfterFBBegin(BOOLEAN bEnabled);
INTERFACE void MApp_Music_GetRIFFTag(U8* buf, U32* tag, U32* tagsize);
INTERFACE void MApp_Music_InputBackGroundMusicData(void);
INTERFACE void MApp_Music_SetPlayQtFormat(BOOLEAN bPlayQTFormat);
INTERFACE BOOLEAN MApp_Music_MP3_Probe(U32 u32Hdl, ST_MUSIC_PROBE_INFO *pMusicProbeInfo, U32 u32InfoAttr);

INTERFACE BOOLEAN MApp_Music_WAV_Probe(U32 u32Hdl, ST_MUSIC_PROBE_INFO *pMusicProbeInfo, U32 u32InfoAttr);
INTERFACE BOOLEAN MApp_Music_AAC_Probe(U32 u32Hdl, ST_MUSIC_PROBE_INFO *pMusicProbeInfo, U32 u32InfoAttr);
INTERFACE BOOLEAN MApp_Music_M4A_Probe(U32 u32Hdl, ST_MUSIC_PROBE_INFO *pMusicProbeInfo, U32 u32InfoAttr);
INTERFACE BOOLEAN MApp_Music_FLAC_Probe(U32 u32Hdl, ST_MUSIC_PROBE_INFO *pMusicProbeInfo, U32 u32InfoAttr);
INTERFACE BOOLEAN MApp_Music_AC3_Probe(U32 u32Hdl, ST_MUSIC_PROBE_INFO *pMusicProbeInfo, U32 u32InfoAttr);
INTERFACE BOOLEAN MApp_Music_OGG_Probe(U32 u32Hdl, ST_MUSIC_PROBE_INFO *pMusicProbeInfo, U32 u32InfoAttr);

#undef INTERFACE

#endif // _MAPP_SUBTITLE_H

