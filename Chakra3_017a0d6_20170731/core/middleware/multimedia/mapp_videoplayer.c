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

#define MAPP_VIDEOPLAYER_C
//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "mapp_videoplayer.h"
#include "MApp_UiMenuDef.h"

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "ctype.h"
#include "msIR.h"

// Global Layer
#include "MApp_Exit.h"
#include "sysinfo.h"
#include "SysInit.h"
#include "BinInfo.h"

// XC related include files
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "color_reg.h"

//Driver Layer
#include "drvUART.h"
#include "drvCPU.h"
#include "drvMIU.h"
#include "drvMVOP.h"
#include "drvPQ.h"

//panel module
#include "Panel.h"
#include "apiPNL.h"

// API Layer
#include "apiGOP.h"
#include "msAPI_MIU.h"
#include "msAPI_Memory.h"
#include "msAPI_MMap.h"
#include "msAPI_Timer.h"
#include "msAPI_WMA.h"
#include "apiXC_Ace.h"
#include "msAPI_FCtrl.h"
#if ENABLE_HK_MM
#include "mapi_VMBX.h"
#else
#include "msAPI_MailBox.h"
#endif
#include "msAPI_audio.h"
#include "msAPI_CPU.h"
#include "msAPI_FSCommon.h"
#include "msAPI_MPEG_Subtitle.h"

// AP Layer
#include "MApp_GlobalSettingSt.h"
#include "MApp_Scaler.h"
#include "MApp_XC_PQ.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Exit.h"
#include "mapp_videoplayer.h"
#include "MApp_ChannelChange.h"
#include "MApp_FileBrowser.h"
#include "MApp_SaveData.h"
#include "MApp_XC_Sys.h"

#include "MApp_PCMode.h"
#include "MApp_InputSource.h"
#include "MApp_Init.h"

#include "mapp_mplayer_subtitle.h"

#include "MApp_IR.h"
#include "MApp_MVDMode.h"
#include "MApp_ZUI_ACTdmp.h"
#include "mapp_mplayer.h"

#if (ENABLE_DMP)
#if ENABLE_WMDRMPD
#include "mapp_wmdrmpd.h"
#endif

#if ENABLE_DVD
#include "FSUtil.h"
#include "mapp_dvd.h"
#endif

#include "msAPI_DataStreamIO.h"

#if ENABLE_PIP
#include "MApp_PIP.h"
#endif

#include "msAPI_PVR.h"
BOOLEAN bIsPVR = FALSE;
//#ifndef ENABLE_PVR_AESDMA
//#define ENABLE_PVR_AESDMA 0
//#endif

#if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
enPvrEncryptType enEncryptType = E_PVR_ENCRYPTION_NONE;
#endif

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
#define VDPLAYER_MSG_ON     0

#if ( (MEMORY_MAP <= MMAP_32MB) || ENABLE_HK_LOAD_MM_VDEC )
    #define ENABLE_DYNAMIC_LOAD_VDECBIN     1
#else
    #define ENABLE_DYNAMIC_LOAD_VDECBIN     0
#endif // #if (MEMORY_MAP <= MMAP_32MB)

//#define _VDPLAYER_DUMP_RAW_
#define GetByte3(x)         (((x)&0xff000000)>>24)
#define GetByte2(x)         (((x)&0x00ff0000)>>16)
#define GetByte1(x)         (((x)&0x0000ff00)>>8)
#define GetByte0(x)         ((x)&0x000000ff)

#define COMBU16(hi,lo)          ((((U16)hi)<<8) | ((U16)lo))
#define COMBU32(hh,hl,lh,ll)    ((((U32)hh)<<24) | (((U32)hl)<<16) | (((U32)lh)<<8) | ((U32)ll))

#define VDPLAYER_DBG(x)         //x
#define VDPLAYER_DVD_DBG(x)     //x
#define ENABLE_TS_RADIO         1

//Black(30m) , Red(31m) , GREEN(32m) , YELLOW(33m) , BLUE(34m) , MAGENTA(35m) , CYAN(36m) , WHITE(37m)
#define VDPLAYER_ERROR(format,args...)  printf("\033[15;31m"format"\033[0m",##args)

#define VIDEO_SHIFT_UNIT_X              8
#define VIDEO_SHIFT_UNIT_Y              8
#define VIDEO_SHIFT_BOUNDARY_X          8
#define VIDEO_SHIFT_BOUNDARY_Y          8

#define U32_SWAP(x) ((((x)&0xFF000000)>>24) | (((x)&0x00FF0000)>>8) | (((x)&0x0000FF00)<<8) | (((x)&0x000000FF)<<24))

#define SVD_USING_MIU1                          0x80000000 //use bit31 to inform co-processor use MIU1

#define ENABLE_FBL_MODE                         0x01  //enable FBL mode
#define ENABLE_FDMASK_DELAY                     1

#define ENABLE_HEVC_1080P50_FBL_MODE            0

#if (MEMORY_MAP <= MMAP_32MB)   // 32M
#define ENABLE_FBL_MODE_THRESHOLD              (720UL*576UL + 1)
#elif (MEMORY_MAP == MMAP_64MB)  // 64M
#define ENABLE_FBL_MODE_THRESHOLD              (1800UL * 1000UL)
#else
    #if (ENABLE_HEVC_1080P50_FBL_MODE)
    #define ENABLE_FBL_MODE_THRESHOLD              (1920UL * 1080UL * 50UL - 1)
    #else
    #define ENABLE_FBL_MODE_THRESHOLD              (2200UL * 1125UL)
    #endif
#endif

#define HVD_BW_TUNING_THRESHOLD             (800UL*600UL)

#if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
#define DELAY_FOR_STABLE_CHANNELCHANGE          800
#else
#define DELAY_FOR_STABLE_CHANNELCHANGE          300
#endif

#if ENABLE_WMDRMPD
#define WMDRMPD_SHAREMEM_HEADER                  0x55AA1234
#define WMDRMPD_SHAREMEM_TAG_PROTECTED           0x55AA0001
#define WMDRMPD_SHAREMEM_TAG_PROTECTED_HEADER    0x55AA0002
#endif
#define WMDRMPD_PRIVATE_LENGTH                   0x20

//#define ENABLE_SUBTITLE_AutoShow 1
#define AUDIO_SPDIF_ENABLE                      1

#define ENABLE_AUDIO_HANDLER                    1

#if ENABLE_DIVX_TTF
#define ENABLE_ATTACHMENT_HANDLER               1
#else
#define ENABLE_ATTACHMENT_HANDLER               0
#endif
#define INVALID_HANDLE_IDX                      0xff

#define MOVIE_THUMB_DWIN_CAPTURE_TIMEOUT        100
#define DWIN_DONE_INT                           0

#ifndef ENABLE_HK_MP4
#define ENABLE_HK_MP4                           0
#endif

#ifndef ENABLE_HK_SUBTITLE
#define ENABLE_HK_SUBTITLE                      0
#endif

#if ENABLE_HK_MP4
#define ENABLE_HK_MP4_PERFORMANCE_IMPROVE       1
#endif
#define DISABLE_VE_VSIZE_CHECK                  1

#if ENABLE_HK_MM
#define TIMEOUT_TIMER_2000MS                    (2000)
#define NONBLOCKING_READ_SIZE                   0x1000
#define NONBLOCKING_READ_TIMEOUT                1
#define ENABLE_HK_AVI                           0
#else
#define ENABLE_HK_AVI                           1
#define ENABLE_HK_AVI_PERFORMANCE_IMPROVE       1
#endif

#ifndef ENABLE_HK_DRM_GENCODE
#define ENABLE_HK_DRM_GENCODE                   0
#endif

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)
    #define ENABLE_NEW_MM_AUDIO               0
#else
    #define ENABLE_NEW_MM_AUDIO               1
#endif

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)
    #define ENABLE_EVD_FEATURE               1
#else
    #define ENABLE_EVD_FEATURE               0
#endif


#define ENABLE_USB_READ_RATE_MEASURED           0

#if ENABLE_POWERON_VIDEO
BOOLEAN msAPI_Pan_Get_Status(void);
#endif

typedef struct
{
    BININFO BinInfo;
    U32 u32FlashReadPTR;
    BOOLEAN bValid;
}ST_FALSH_FILE_HANDLE_INFO;

#if ENABLE_HK_AVI
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "mapp_vdplayer_bm.h"

#if (defined(BIN_ID_CODE_AEON_VDPLAYER_32M) && defined(BIN_ID_CODE_VDPLAYER))
#if (BIN_ID_CODE_VDPLAYER==BIN_ID_CODE_AEON_VDPLAYER_32M)
#if ENABLE_HK_SUBTITLE
#define MAX_MP4_TABLES              (6)
#else
#define MAX_MP4_TABLES              (4)
#endif

#define MAX_VIDEO_TRACKS            (1)
#define MAX_AUDIO_TRACKS            (10)
#define MAX_SUBTITLE_TRACKS         (8)
#else
#if ENABLE_HK_SUBTITLE
#define MAX_MP4_TABLES              (6)
#else
#define MAX_MP4_TABLES              (4)
#endif

#define MAX_VIDEO_TRACKS            (4)
#define MAX_AUDIO_TRACKS            (10)
#define MAX_SUBTITLE_TRACKS         (16)
#endif
#else
#if ENABLE_HK_SUBTITLE
#define MAX_MP4_TABLES              (6)
#else
#define MAX_MP4_TABLES              (4)
#endif

#define MAX_VIDEO_TRACKS            (4)
#define MAX_AUDIO_TRACKS            (10)
#define MAX_SUBTITLE_TRACKS         (16)
#endif
#define MAX_TOTAL_TRACKS            (MAX_AUDIO_TRACKS + MAX_VIDEO_TRACKS + MAX_SUBTITLE_TRACKS)
#define INVALID_STREAM_ID           (20)    // (MAX_TOTAL_TRACKS)
#define MKTAG(a,b,c,d)              ((U32)a | ((U32)b << 8) | ((U32)c << 16) | ((U32)d << 24))
#define TIMEOUT_TIMER_2000MS        (2000)
#define EVEN_ALIGN(x)               (x + (x%2))
#define U32_MAX                     (0xFFFFFFFFUL)
#define U8_MAX                      (0xFF)
#define AAC_SAMPLE_PER_FRAME        (1024UL)
#define AVI_PRELOAD_SIZE            (4096 * 8)
#define AVIIF_KEYFRAME              (0x00000010)
// KeyFrame indicator in OpenDML standard index
#define AVI_NOT_KEYFRAME            (0x80000000L)
#define THUMBNAIL_JUMPTIME          (20000)

typedef enum
{
    E_AVI_DEMUX_SUCCESS = 0,
    E_AVI_DEMUX_ERR_FILE_OPEN_FAILED,
    E_AVI_DEMUX_ERR_UNSUPPORT,
    E_AVI_DEMUX_ERR_INIT_TIMEOUT,
    E_AVI_DEMUX_ERR_DEMUX_HEADER,
    E_AVI_DEMUX_ERR_DEMUX,
    E_AVI_DEMUX_ERR_INDEX,
} EN_AVI_DEMUX_RETURN;

typedef struct
{
    U64 u64Offset;
    U32 u32Size;
    U32 u32Pts;
    U32 u32Frm_Info_Idx;
    U32 u32AudioBitTime[MAX_AUDIO_TRACKS];
} ST_VDP_DEMUX_KEYINDEX, *PST_VDP_DEMUX_KEYINDEX;

/// Define the demux result of audio key index.
typedef struct
{
    U64 u64Offset;
    U32 u32Size;
    U32 u32Pts;
    U32 u32Frm_Info_Idx;
} ST_VDP_DEMUX_AUDIO_KEYINDEX, *PST_VDP_DEMUX_AUDIO_KEYINDEX;

typedef struct
{
    U64 u64IdxOffset;
    U32 u32Size;
} ST_OPEN_DML_IDX_INFO, *PST_OPEN_DML_IDX_INFO;

typedef struct
{
    ST_OPEN_DML_IDX_INFO *pstOpenDmlIdxInfo;
    U32 u32Cnt;
} ST_OPEN_DML_IDX_HEADER_INFO, *PST_OPEN_DML_IDX_HEADER_INFO;

typedef struct
{
    U32 u32Fcc;
    U32 u32Size;
} ST_RIFF_CHUNK_GENERAL, *PST_RIFF_CHUNK_GENERAL;

typedef struct
{
    ST_RIFF_CHUNK_GENERAL stRiffChunkGeneral;

    U16 u16LongsPerEntry;
    U8 u8IndexSubType;
    U8 u8IndexType;
    U32 u32EntriesInUse;
    U32 u32ChunkId;
    U64 u64BaseOffset;
    U32 u32Reserved3;
    struct
    {
        U32 u32Offset;
        U32 u32Size;
    } stAIndex;
} ST_AVI_STD_INDEX, *PST_AVI_STD_INDEX;

typedef struct
{
    ST_RIFF_CHUNK_GENERAL stRiffChunkGeneral;

    struct
    {
        U32 u32ChunkId;
        U32 u32Flags;
        U32 u32Offset;
        U32 u32Size;
    } stAIndex;
} ST_AVI_OLD_INDEX, *PST_AVI_OLD_INDEX;

typedef union
{
    U32 u32;
    struct {
        U16 u16_0;
        U16 u16_1;
    };
    struct {
        U8 u8_0;
        U8 u8_1;
        U8 u8_2;
        U8 u8_3;
    };
} UU32;

typedef union
{
    U64 u64;
    struct {
        U32 u32_0;
        U32 u32_1;
    };
    struct {
        U16 u16_0;
        U16 u16_1;
        U16 u16_2;
        U16 u16_3;
    };
    struct {
        U8 u8_0;
        U8 u8_1;
        U8 u8_2;
        U8 u8_3;
        U8 u8_4;
        U8 u8_5;
        U8 u8_6;
        U8 u8_7;
    };
} UU64;

//for 8bits in 32bits' byte value
#define u8u32_0(u)              (((UU32*)&(u))->u8_0)
#define u8u32_1(u)              (((UU32*)&(u))->u8_1)
#define u8u32_2(u)              (((UU32*)&(u))->u8_2)
#define u8u32_3(u)              (((UU32*)&(u))->u8_3)

//for 32bits in 64bits' byte value  (LO:0 ---> HI:1)
#define u32u64_0(u)             (((UU64*)&(u))->u32_0)
#define u32u64_1(u)             (((UU64*)&(u))->u32_1)

typedef enum
{
    E_VDP_DEMUX_BUD_INDEX_TAB_RET_SUCCESS = 0,
    E_VDP_DEMUX_BUD_INDEX_TAB_RET_FAILED,
    E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL,
} EN_VDP_DEMUX_INDEXTAB_RET;

typedef union
{
    struct
    {
        U32 u32Scale;               // AVI                      : MP2/ MP3
        U32 u32Rate;                // AVI                      : MP3
        U32 u32SampleSize;          // AVI/ RM                  : MP2/ MP3
        U32 u32BlockAlign;          // AVI                      : MP2/ MP3/ ADPCM
        U32 u32BitRate;             // AVI/ RM/ MPG             : MP2
        U32 u32Channel;
        U32 u32SamplesPerBlock;
        U32 u32SampleRate;
    } stMPEG;

    struct
    {
        U32 u32SampleRate;          // AVI/ MOV/ MKV/ RM/ MPG   : AAC/ PCM/ ADPCM
        U32 u32ObjectTypeID;        // AVI/ MOV/ MKV            : AAC
        U32 u32ChannelConfig;       // AVI/ MOV/ MKV            : AAC
        U32 u32BitRate;
    } stAAC;

    struct
    {
        U32 u32Channel;             // AVI/ MOV/ MKV/ RM/ MPG   : PCM/ ADPCM
        U32 u32SampleRate;          // AVI/ MOV/ MKV/ RM/ MPG   : AAC/ PCM/ ADPCM
        U32 u32BitsPerSample;       // AVI/ MOV/ MKV/ MPG       : PCM/ ADPCM
        U32 u32BitRate;
    } stPCM;

    struct
    {
        U32 u32Channel;             // AVI/ MOV/ MKV/ RM/ MPG   : PCM/ ADPCM
        U32 u32SampleRate;          // AVI/ MOV/ MKV/ RM/ MPG   : AAC/ PCM/ ADPCM
        U32 u32BlockAlign;          // AVI                      : MP2/ MP3/ ADPCM
        U32 u32BitsPerSample;       // AVI/ MOV/ MKV/ MPG       : PCM/ ADPCM
        U32 u32SamplesPerBlock;     // AVI/ MPG                 : ADPCM
    } stADPCM;

    struct
    {
        U32 u32Audio_Frame_Time;    //                          : AC3/ EAC3
        U16 u16Audio_Frame_TimeBase;//                          : AC3/ EAC3
        U16 u16Frame_Size;          //                          : AC3/ EAC3
        U32 u32BitRate;
        U32 u32SampleRate;
        U32 u32Channel;
        U8  u8ParsingCnt;
    } stAC3;

    struct
    {
        U32 u32Channel;
        U32 u32SampleRate;
    } stCOOK;

    struct
    {
        U32 u32Audio_Frame_Time;    //                          : DTS
        U16 u16Audio_Frame_TimeBase;//                          : DTS
        U16 u16Frame_Size;          //                          : DTS
    } stDTS;

    struct
    {
        U32 u8Version;
        U32 u32Channel;
        U32 u32SampleRate;
        U32 u32ByteRate;
        U32 u32BlockAlign;
        U16 u16EncodeOpt;
        U16 u16AdvanceEncodeOpt;
        U32 u32BitsPerSample;
        U32 u32ChannelMask;
        //--  WMA DRC Info -- //
        BOOL bWMADRCExist;
        U32 u32WMADRCPeakReference;
        U32 u32WMADRCPeakTarget;
        U32 u32WMADRCAverageReference;
        U32 u32WMADRCAverageTarget;
    } stWMA;

    struct
    {
        U16 u16HeaderSize;
        U32 u32HeaderAddr;
    } stVorbis;

    struct
    {
        U32 u32Channel;
        U32 u32SampleRate;
        U32 u32BitsPerSample;
        U32 u32BitRate;
        U32 u32FramePerSample;
        U32 u32BitsPerSec;
    } stAMR;
} UN_VDP_AUDIO_PARAM;

typedef struct
{
    UN_VDP_AUDIO_PARAM unAudioParam[MAX_AUDIO_TRACKS];
    EN_VDP_CODECID enAudioCodecID[MAX_AUDIO_TRACKS];
    PST_OPEN_DML_IDX_HEADER_INFO pstOpenDmlIdxHeaderInfo;
    U64 u64FileSize;
    U32 u32FirstMoviStartPos;
    U32 u32FirstMoviEndPos;
    U32 u32FirstRiffEndPos;
    U32 u32BitstreamAddr;
    U32 u32BitstreamSize;
    U32 u32IndexBuffAddr;
    U32 u32IndexBuffSize;
    U32 u32KeyIdxPeriod;
    U32 u32FrameRate;
    U32 u32FrameRateBase;
    U32 u32Video_IdxSize;
    U32 u32FirstVideoKeyFramePTS;
    U32 u32lastVideoKeyFramePTS;
    S8  s8Video_StreamId;
    S8  s8Audio_StreamId;
    U8  u8Nb_VideoTracks;
    U8  u8Nb_AudioTracks;
    U8  u8AudioTrackIDMap[MAX_AUDIO_TRACKS];
    U8  u8KeyIdxSize;
    U8  u8ThumbNailMode;
    /// Audio key frame buffer address
    U32 u32AudioKeyBufAddr[MAX_AUDIO_TRACKS];
    /// Audio key frame buffer size
    U32 u32AudioKeyBufSize[MAX_AUDIO_TRACKS];
    /// Audio key frame index size
    U32 u32Audio_IdxSize[MAX_AUDIO_TRACKS];
    /// Audio key index period
    U32 u32AudioKeyIdxPeriod;
    /// Audio key index size
    U8  u8AudioKeyIdxSize;
    /// has enable to use BitRate to calculate PTS
    BOOL bEnableCalcByBitRate;
    /// has enable Audio Handler or not
    BOOL bEnableAudioHandler;
} ST_HK_AVI_SCAN, *PST_HK_AVI_SCAN;

typedef struct
{
    struct _stVideoTrack
    {
        U32 u32FrameRate;
        U32 u32FrameRateBase;
    } VideoTracks[1];

    U64 u64FileSize;
    PST_OPEN_DML_IDX_HEADER_INFO pstOpenDmlIdxHeaderInfo;
    U32 u32FirstMoviStartPos;
    U32 u32FirstMoviEndPos;
    U32 u32FirstRiffEndPos;
    U32 u32VideoKeyIdxCnt;
} ST_CONTAINER_AVI, *PST_CONTAINER_AVI;

typedef struct
{
    union
    {
        ST_CONTAINER_AVI    stAVI;
    } Container;

    EN_VDP_CODECID enAudioCodecID[MAX_AUDIO_TRACKS];
    UN_VDP_AUDIO_PARAM unAudioParam[MAX_AUDIO_TRACKS];

    U8  u8Nb_AudioTracks;                           // Numbers of Audio Track. Start from 0
    U8  u8Nb_VideoTracks;                           // Numbers of Video Track. Start from 0
    S8  s8Video_StreamId;                           // Current Video Stream ID.
    S8  s8Audio_StreamId;                           // Current Audio Stream ID.
} ST_VDP_BITSCONTENT, *PST_VDP_BITSCONTENT;

typedef struct
{
    ST_VDP_BITSCONTENT      stBitsContent;
    struct
    {
        U32     u32SampleInfoAddr[MAX_MP4_TABLES]; // sample info table address
        U32     u32SampleInfoLen[MAX_MP4_TABLES];  // sample info table length
        U32     u32IndexBuffAddr;
        U32     u32IndexBuffSize;
        U32     u32FrameBufferAddr;
        U32     u32FrameBufferLen;
        U32     u32HKUsedAddr;
        U32     u32HKUsedLen;
    } stDataBuffer;

    /// Audio index buffer adress
    U32     u32AudioKeyBufAddr[MAX_AUDIO_TRACKS];
    /// Audio index buffer size
    U32     u32AudioKeyBufSize[MAX_AUDIO_TRACKS];
    U32     u32Video_IdxSize;
    U32     u32Audio_IdxSize[MAX_AUDIO_TRACKS];
    U32     u32KeyIdxPeriod;
    /// audio key index period
    U32     u32AudioKeyIdxPeriod;
    U32     u32lastVideoKeyFramePTS;     // Last Key Frame PTS.
    U32     u32FirstVideoKeyFramePTS;     // first Key Frame PTS.
    U8      u8AudioTrackIDMap[MAX_AUDIO_TRACKS];         // Stream ID = u8AudioTrackIDMap[Track]
    U8      u8KeyIdxSize;
    /// audio key index size
    U8      u8AudioKeyIdxSize;
    U8      u8ThumbNailMode;
    /// has enable to use BitRate to calculate PTS
    BOOL    bEnableCalcByBitRate;
    /// has enable Audio Handler
    BOOL    bEnableAudioHandler;
#if ENABLE_HK_SUBTITLE
    /// Subtitle index buffer adress
    U32     u32SubKeyBufAddr[MAX_SUBTITLE_TRACKS];
    /// Subtitle index buffer size
    U32     u32SubKeyBufSize[MAX_SUBTITLE_TRACKS];
    U32     u32Subtitle_IdxSize[MAX_SUBTITLE_TRACKS];
    U32     u32TotalPictures[MAX_SUBTITLE_TRACKS];
    U8      u8SubtitleTrackIDMap[MAX_SUBTITLE_TRACKS];         // Stream ID = u8SubtitleTrackIDMap[Track]
    U8      u8SubtitleKeyIdxSize;
#endif // #if ENABLE_HK_SUBTITLE
} ST_VDP_DEMUX_GLOBAL, *PST_VDP_DEMUX_GLOBAL;

ST_VDP_DEMUX_GLOBAL g_stDemuxer;

BOOL MApp_VDPlayer_AVIScanIndex(U8 u8FileHdl);

#if ENABLE_HK_MP4
typedef enum
{
    E_VDP_TIMESTAMP_NONE        = 0,
    E_VDP_TIMESTAMP_PTS,
    E_VDP_TIMESTAMP_DTS,
    E_VDP_TIMESTAMP_PTS_MPEG_DIRECTV_SD,
} EN_VDP_TIMESTAMP_TYPE;

typedef struct
{
    U64 u64Offset;   // file absolute offset
    U32 u32Index;    // sample index, and this value should be U32_MAX at EOS.
    U32 u32PTS;      // sample pts
    U32 u32Size;     // sample size
    U32 u32StreamID; // sample stream id
} MP4SampleInfo;

typedef struct
{
    U64 u64Offset_Min[MAX_TOTAL_TRACKS];   // index is stream id
    U32 u32SampleInfoAddr[MAX_MP4_TABLES]; // sample info table address (PA)
    U32 u32SampleInfoLen[MAX_MP4_TABLES];  // sample info table length
    U32 u32HKUsedAddr;
    U32 u32HKUsedLen;
    U8  u8TimeStampType;
} ST_HK_MP4_INIT;

typedef struct
{
    U32 u32FrameBufferAddr; // video frame buffer address (PA)
    U32 u32FrameBufferLen;  // video frame buffer length
    U32 u32IndexBuffAddr;
    U32 u32IndexBuffSize;
    U32 u32KeyIdxPeriod;
    U32 u32Video_IdxSize;
    U32 u32FirstVideoKeyFramePTS;
    U32 u32lastVideoKeyFramePTS;
    U8  u8Nb_AudioTracks;
    U8  u8AudioTrackIDMap[MAX_AUDIO_TRACKS];
    U8  u8KeyIdxSize;
    U32 u32AudioKeyBufAddr[MAX_AUDIO_TRACKS];
    U32 u32AudioKeyBufSize[MAX_AUDIO_TRACKS];
    U32 u32Audio_IdxSize[MAX_AUDIO_TRACKS];
    U32 u32AudioKeyIdxPeriod;
    U8  u8AudioKeyIdxSize;
#if ENABLE_HK_SUBTITLE
    U32 u32SubtitleKeyBufAddr[MAX_SUBTITLE_TRACKS];
    U32 u32SubtitleKeyBufSize;
    U32 u32Subtitle_IdxSize[MAX_SUBTITLE_TRACKS];
    U32 u32TotalPictures[MAX_SUBTITLE_TRACKS];
    U8  u8SubtitleTrackIDMap[MAX_SUBTITLE_TRACKS];
    U8  u8Nb_SubtitleTracks;
    U8  u8SubtitleKeyIdxSize;
#endif // #if ENABLE_HK_SUBTITLE
} ST_HK_MP4;

// EN_MOV_MEDIA_TYPE is also the index of array of sample info tables
typedef enum
{
    E_MOV_MEDIA_TYPE_VIDEO1 = 0,
    E_MOV_MEDIA_TYPE_AUDIO1,
#if ENABLE_HK_SUBTITLE
    E_MOV_MEDIA_TYPE_SUBTITLE1,
#endif
    E_MOV_MEDIA_TYPE_VIDEO2,
    E_MOV_MEDIA_TYPE_AUDIO2,
#if ENABLE_HK_SUBTITLE
    E_MOV_MEDIA_TYPE_SUBTITLE2,
#endif
    E_MOV_MEDIA_TYPE_MAX,
} EN_MOV_MEDIA_TYPE;
#endif

#endif

// Enhance the ability of A/V sync for some file.(Ex:Kufu panda)
#define ENABLE_AV_INTERLEAVE_ENHANCE            1

#ifndef ENABLE_MM_XC_FBL_MODE
    // ENABLE_MM_XC_FBL_MODE: Dynamic control xc using FBL mode for memory size and bandwidth issue.
    // If you are using MMAP_128MB, it will be advised that setting MIU clock to 1066MHz.
    #if( (ENABLE_MIU_1 == 0) && (MEMORY_MAP < MMAP_128MB) )
        #define ENABLE_MM_XC_FBL_MODE   1
    #else
        #if (ENABLE_HEVC_1080P50_FBL_MODE)
            #define ENABLE_MM_XC_FBL_MODE   1
        #else
            #define ENABLE_MM_XC_FBL_MODE   0
        #endif
    #endif
#endif

#if 0//ENABLE_ATTACHMENT_HANDLER
//timothy.h temp co-buffer with MHEG5_POOL
#define DIVX_ATTACHEDMENT_ADR                                  0x0002E00000  //Alignment 0x00010
#define DIVX_ATTACHEDMENT_LEN                                  0x0000480000
#define DIVX_STRING_ADR                                        (DIVX_ATTACHEDMENT_ADR + DIVX_ATTACHEDMENT_LEN)  //Alignment 0x00010
#define DIVX_STRING_LEN                                        0x0000080000
#define DIVX_ATTACHEDMENT_MEMORY_TYPE                          (MIU0 | SW | WRITE_BACK)
#define DIVX_STRING_MEMORY_TYPE                                (MIU0 | SW | WRITE_BACK)
#endif

#if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
#define AV_FILE_HANDLE                          0
#endif
static U32 u32OrgDivPlusPTS;

#define MAX_TEXT_SUBTITLE_TAG_COUNT             16
#if ENABLE_DIVX_PLUS
U8 g_u8TitleId = 0;
U8 g_u8EditionId = 0;
extern BOOL g_bChangeFile;
//extern enumMPlayerMoviePlayMode g_eMoviePlayMode;
extern U32 g_u32DivxPlusPTS;

#endif
#if ENABLE_DRM
    U8 u8DRM_LastData[DIVX_KEY_LEN] ={0};
#endif

#define INPUT_PIXEL_CLOCK_THRESHOLD (0xFFFFFFFF)

#define ds_dbg(x) //x

/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/
typedef enum
{
    E_ACKFLG_NULL = 0,
    E_ACKFLG_WAIT_INIT = BIT0,
    E_ACKFLG_WAIT_GET_DRM_REG_CODE = BIT1,
    E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION = BIT2,
    E_ACKFLG_WAIT_QUERY_DRM_RENTAL_STATUS = BIT3,
    E_ACKFLG_WAIT_STOP = BIT4,
    E_ACKFLG_WAIT_GET_SUBTITLE_STATE = BIT5,
    E_ACKFLG_WAIT_GET_DRM_REG_CODE_2 = BIT6,
    E_ACKFLG_WAIT_GET_DRM_DEACTIVATION_CODE = BIT7,
    E_ACKFLG_WAIT_PLAY = BIT8,
    E_ACKFLG_WAIT_REPEAT_AB = BIT9,
#if ENABLE_DVD
    E_ACKFLG_WAIT_SEEKPLAY = BIT10,
    E_ACKFLG_WAIT_DISCONTINUITY = BIT11,
    E_ACKFLG_WAIT_DONE = BIT12,
    E_ACKFLG_WAIT_SCANSYNC = BIT13,
    E_ACKFLG_WAIT_SCANDONE = BIT14,
    E_ACKFLG_WAIT_SCANEXIT = BIT15,
#endif
    E_ACKFLG_WAIT_SUBTITLE_TIMESHIFT = BIT16,
    E_ACKFLG_WAIT_PAUSE = BIT17,
    E_ACKFLG_WAIT_SET_TRICK_MODE = BIT18,
    E_ACKFLG_WAIT_SET_SET_PLAYER_POSITION = BIT19,
    E_ACKFLG_WAIT_STEP = BIT20,
#if ENABLE_DIVX_PLUS
    E_ACKFLG_WAIT_SET_CHAPTER_ID = BIT21,
    E_ACKFLG_WAIT_SET_AUTOGEN_CHAPTER_ID = BIT22,
    E_ACKFLG_WAIT_SET_TITLE_ID = BIT23,
    E_ACKFLG_WAIT_SET_EDITION_ID = BIT24,
#endif
    E_ACKFLG_WAIT_TS_SET_PROGRAM = BIT25,
    E_ACKFLG_WAIT_SET_AUDIO_TRACK_ID = BIT26,
    E_ACKFLG_WAIT_SET_SUBTITLE_TRACKID = BIT27,
} enumVDPlayerAckFlags;

#define  Remove_enumVDPlayerAckFlags(val, flag) \
   do{(val) = (enumVDPlayerAckFlags)(((U32)(val))&~(U32)(flag));}while(0)

#define VDPLAYER_MAILBOX_SEND(_class,_index,_type,_count,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10) _VDPlayer_SendMailboxMsg((U8)_class,(U8)_index,(MBX_MSG_Type)_type,(U8)_count,(U8) _p1,(U8) _p2,(U8) _p3,(U8) _p4,(U8) _p5,(U8) _p6,(U8) _p7,(U8) _p8,(U8) _p9,(U8) _p10)

#if ENABLE_HK_MP4
#include "ms_input.h"
#include "ms_open_input.h"
#include "ms_malloc.h"
#include "mp4demux.h"
#include "msmComm.h"

#define MP4_UPDATE_SAMPLE_THRESHOLD 100
#define MP4_ATOM_TABLE_CACHE_SIZE   1024*1024 // 1M
#define MP4_INVALID_IDX_GAP 0
#define MP4_INVALID_FRAME_IDX 0
#define MP4_FS_CACHE_SIZE 4096

typedef enum
{
    E_MP4_PACK_TYPE_UNKNOWN = 0,
    E_MP4_PACK_TYPE_UNPACKED,
    E_MP4_PACK_TYPE_PACKED,
} EN_MP4_PACK_TYPE;

typedef struct
{
    EN_MOV_MEDIA_TYPE type;
    U32 sample_index; // next frame to update, it is the index of packet that VDPlayer will get
    U32 max_count;
    U32 table_idx; // next index to update in sample info table
    U8 parsing;
    U8 stream_id;
} ST_SAMPLE_TABLE_INFO;

typedef struct
{
    U32 sample_id;        // the index coresponding to each sample that CP will get , base 1
    uint32_t frame_index; // the index of samples in mp4 demuxer track, base 1
    uint32_t index_gap;   // next frame_index is frame_index + index_gap -> sample_id[n] = frame_index[n-1] + index_gap[n-1]
    U8 stream_id;
} ST_FRAME_INDEX_INFO;

typedef struct
{
    cb_io_st *pcbio;
    void *mp4Inst;
    void *mp4BaseBuffer;
    ST_FRAME_INDEX_INFO last_audio;
    ST_SAMPLE_TABLE_INFO table_info[MAX_MP4_TABLES];
    EN_MP4_PACK_TYPE audio_pack_type[MAX_AUDIO_TRACKS];
    U8 file_handle;
} ST_CONTAINER_MP4;

#if ENABLE_HK_SUBTITLE
typedef struct
{
    U32 u32StartPTS;
    U32 u32EndPTS;
    U32 u32FrameInfoIndex;
    U32 u32Fileoffset;
    U16 u16FileoffsetHi;
    U16 u16Size;
} SubtitleMP4PTSEntry;
#endif  // #if ENABLE_HK_SUBTITLE

static void MApp_VDPlayer_MP4_Init(U32 u32Addr);
static void MApp_VDPlayer_MP4_GetIndexInfo(U32 u32Addr);
static void MApp_VDPlayer_MP4_StartGetSampleInfo(EN_MOV_MEDIA_TYPE enMediaType, U8 u8StreamID, U32 u32SampleIndex, U32 u32MaxSampleCount);
static void MApp_VDPlayer_MP4_UpdateSampleTable(ST_SAMPLE_TABLE_INFO *table_info);
static void MApp_VDPlayer_MP4_GetSampleInfoDone(EN_MOV_MEDIA_TYPE enMediaType, U32 u32SampleCount);
static void MApp_VDPlayer_MP4_ClearVideoSampleInfo(void);
static void MApp_VDPlayer_MP4_ClearAudioSampleInfo(void);
#if ENABLE_HK_SUBTITLE
static void MApp_VDPlayer_MP4_ClearSubtitleSampleInfo(void);
#endif

ST_CONTAINER_MP4 stMP4;

int dmx_notify(void *ctx, mvc_stream_type_et type, mvc_event_et event)
{
    UNUSED(ctx);
    UNUSED(type);
    UNUSED(event);
    return MVC_OK;
}

void *dmx_malloc(void *ctx, size_t size)
{
    void *ptr;

    UNUSED(ctx);
    ptr = ms_heap_malloc(size);
    VDPLAYER_DBG(printf("malloc size %d, ptr 0x%x\n", size, ptr));
    return ptr;
}

void dmx_freep(void *ctx, void *ptr)
{
    void **temp_ptr = ptr;

    UNUSED(ctx);
    VDPLAYER_DBG(printf("free ptr 0x%x\n", *temp_ptr));
    ms_heap_freep(ptr);
    *temp_ptr = 0;
}

static const mvc_callback_st mvc_callback =
{
    &dmx_notify,
    &dmx_malloc,
    &dmx_freep,
    0,
    0,
    0,
    0,
    0,
    0
};

static int probe_mp4(const U8 *header, int len)
{
    return len >= 8 &&
          ((memcmp(header + 4, "ftyp", 4) == 0) ||
           (memcmp(header + 4, "moov", 4) == 0) ||
           (memcmp(header + 4, "mdat", 4) == 0) ||
           (memcmp(header + 4, "pnot", 4) == 0) ||
           (memcmp(header + 4, "skip", 4) == 0));
}

static void reset_mp4_frame_index_info(ST_FRAME_INDEX_INFO *frame_info, U8 stream_id)
{
    frame_info->frame_index = 1;
    frame_info->index_gap = MP4_INVALID_IDX_GAP;
    frame_info->sample_id = 1;
    frame_info->stream_id = stream_id;
}

static void reset_mp4_audio_table_info(ST_CONTAINER_MP4 *pstMP4)
{
    if (pstMP4->table_info[E_MOV_MEDIA_TYPE_AUDIO1].parsing)
    {
        MApp_VDPlayer_MP4_GetSampleInfoDone(pstMP4->table_info[E_MOV_MEDIA_TYPE_AUDIO1].type, pstMP4->table_info[E_MOV_MEDIA_TYPE_AUDIO1].table_idx);
        pstMP4->table_info[E_MOV_MEDIA_TYPE_AUDIO1].parsing = 0;
    }

    if (pstMP4->table_info[E_MOV_MEDIA_TYPE_AUDIO2].parsing)
    {
        MApp_VDPlayer_MP4_GetSampleInfoDone(pstMP4->table_info[E_MOV_MEDIA_TYPE_AUDIO2].type, pstMP4->table_info[E_MOV_MEDIA_TYPE_AUDIO2].table_idx);
        pstMP4->table_info[E_MOV_MEDIA_TYPE_AUDIO2].parsing = 0;
    }
}

static void reset_mp4_video_table_info(ST_CONTAINER_MP4 *pstMP4)
{
    if (pstMP4->table_info[E_MOV_MEDIA_TYPE_VIDEO1].parsing)
    {
        MApp_VDPlayer_MP4_GetSampleInfoDone(pstMP4->table_info[E_MOV_MEDIA_TYPE_VIDEO1].type, pstMP4->table_info[E_MOV_MEDIA_TYPE_VIDEO1].table_idx);
        pstMP4->table_info[E_MOV_MEDIA_TYPE_VIDEO1].parsing = 0;
    }

    if (pstMP4->table_info[E_MOV_MEDIA_TYPE_VIDEO2].parsing)
    {
        MApp_VDPlayer_MP4_GetSampleInfoDone(pstMP4->table_info[E_MOV_MEDIA_TYPE_VIDEO2].type, pstMP4->table_info[E_MOV_MEDIA_TYPE_VIDEO2].table_idx);
        pstMP4->table_info[E_MOV_MEDIA_TYPE_VIDEO2].parsing = 0;
    }
}

#if ENABLE_HK_SUBTITLE
static void reset_mp4_subtitle_table_info(ST_CONTAINER_MP4 *pstMP4)
{
    if (pstMP4->table_info[E_MOV_MEDIA_TYPE_SUBTITLE1].parsing)
    {
        MApp_VDPlayer_MP4_GetSampleInfoDone(pstMP4->table_info[E_MOV_MEDIA_TYPE_SUBTITLE1].type, pstMP4->table_info[E_MOV_MEDIA_TYPE_SUBTITLE1].table_idx);
        pstMP4->table_info[E_MOV_MEDIA_TYPE_SUBTITLE1].parsing = 0;
    }

    if (pstMP4->table_info[E_MOV_MEDIA_TYPE_SUBTITLE2].parsing)
    {
        MApp_VDPlayer_MP4_GetSampleInfoDone(pstMP4->table_info[E_MOV_MEDIA_TYPE_SUBTITLE2].type, pstMP4->table_info[E_MOV_MEDIA_TYPE_SUBTITLE2].table_idx);
        pstMP4->table_info[E_MOV_MEDIA_TYPE_SUBTITLE2].parsing = 0;
    }
}
#endif

static void reset_mp4_table_info(ST_CONTAINER_MP4 *pstMP4)
{
    reset_mp4_audio_table_info(pstMP4);
    reset_mp4_video_table_info(pstMP4);
#if ENABLE_HK_SUBTITLE
    reset_mp4_subtitle_table_info(pstMP4);
#endif
}

static void release_mp4_resource(ST_CONTAINER_MP4 *pstMP4)
{
    if (pstMP4->file_handle != INVALID_FILE_HANDLE)
    {
        msAPI_DataStreamIO_Close(pstMP4->file_handle);
        VDPLAYER_DBG(printf("close file handle for mp4, id %d\n", pstMP4->file_handle));
        pstMP4->file_handle = INVALID_FILE_HANDLE;
    }
}

static void close_mp4_resource(ST_CONTAINER_MP4 *pstMP4)
{
    VDPLAYER_DBG(printf("close resource, pcbio 0x%x, mp4Inst 0x%x, mp4Buffer 0x%x\n", pstMP4->pcbio, pstMP4->mp4Inst, pstMP4->mp4Inst));
    if (pstMP4->pcbio)
        pstMP4->pcbio->close(&pstMP4->pcbio);
    if (pstMP4->mp4Inst)
    {
        MP4DMX_Close(pstMP4->mp4Inst);
        pstMP4->mp4Inst = 0;
    }
    if (pstMP4->mp4BaseBuffer)
    {
        ms_heap_freep(&pstMP4->mp4BaseBuffer);
    }
    ms_heap_free();
    reset_mp4_table_info(pstMP4);
}

static int open_mp4_resource(ST_CONTAINER_MP4 *pstMP4, const ST_HK_MP4_INIT *pstHK_MP4_INIT)
{
    int ret;
    U32 t1, t2;

    // we need 2 MP4_FS_CACHE_SIZE since we may have 2 mp4demux co-existed
    if (pstHK_MP4_INIT->u32HKUsedLen < MP4DMX_HEAP_BUFFER_SIZE + MP4_FS_CACHE_SIZE * 2)
    {
        printf("MP4 memory size %d < %d, error\n", pstHK_MP4_INIT->u32HKUsedLen, MP4DMX_HEAP_BUFFER_SIZE + MP4_FS_CACHE_SIZE * 2);
        return FALSE;
    }

    VDPLAYER_DBG(printf ("mp4 buffer base 0x%x, length %d\n", pstHK_MP4_INIT->u32HKUsedAddr, pstHK_MP4_INIT->u32HKUsedLen));
    ms_heap_init((char *)MS_PA2KSEG0(pstHK_MP4_INIT->u32HKUsedAddr), pstHK_MP4_INIT->u32HKUsedLen);
    ret = open_fd_input(&pstMP4->pcbio, pstMP4->file_handle, MP4_FS_CACHE_SIZE, CBIO_FO_RB);
    VDPLAYER_DBG(printf ("open_fd_input ret %d\n", ret));
    if (ret != CBIO_OK)
        return FALSE;

        pstMP4->mp4BaseBuffer = ms_heap_malloc(MP4DMX_HEAP_BUFFER_SIZE);
        if (!pstMP4->mp4BaseBuffer)
        {
        close_mp4_resource(pstMP4);
            return FALSE;
        }
        t1 = msAPI_Timer_GetTime0();
        ret = MP4DMX_Open(&pstMP4->mp4Inst, pstMP4->mp4BaseBuffer, MP4DMX_HEAP_BUFFER_SIZE, pstMP4->pcbio, 0, &mvc_callback);
        t2 = msAPI_Timer_GetTime0();
        VDPLAYER_DBG(printf ("MP4DMX_Open ret 0x%x, time %d\n", ret, t2 - t1));
        if (ret != MSMERR_OK)
        {
        close_mp4_resource(pstMP4);
            return FALSE;
        }

    reset_mp4_frame_index_info(&pstMP4->last_audio, INVALID_STREAM_ID);
        memset(pstMP4->audio_pack_type, E_MP4_PACK_TYPE_UNKNOWN, sizeof(pstMP4->audio_pack_type));
        reset_mp4_table_info(pstMP4);

#ifdef MP4_DBG_ALL_SAMPLE
        int i, j;
        cb_fpos pOffset;
        uint32_t pnSize;
        uint64_t pStart, pDuration;
        uint32_t is_sync_sample;
        i = 1;
        j = 0;
        t1 = msAPI_Timer_GetTime0();
        while (1)
        {
            ret = MP4DMX_ReadSampleInfo(pstMP4->mp4Inst, i, &pOffset, &pnSize, &pStart, &pDuration, &is_sync_sample, MVC_STREAM_VIDEO);
            if (ret != MSMERR_OK)
                break;
            if (j == 0)
            {
                t2 = msAPI_Timer_GetTime0();
                VDPLAYER_DBG(printf ("[MP4] video index %d, pts %lld ,size %d, offset %llx, sync sample %d, time %d\n", i, pStart, pnSize, pOffset, is_sync_sample, t2 - t1));
            }
            i++;
            j++;
            if (j == 100)
                j = 0;
        }
        t2 = msAPI_Timer_GetTime0();
        VDPLAYER_DBG(printf ("[MP4] video index count %d, time %d\n", i, t2 - t1));
        i = 1;
        j = 0;
        t1 = msAPI_Timer_GetTime0();
        while (1)
        {
            ret = MP4DMX_ReadSampleInfo(pstMP4->mp4Inst, i, &pOffset, &pnSize, &pStart, &pDuration, &is_sync_sample, MVC_STREAM_AUDIO);
            if (ret != MSMERR_OK)
                break;
            if (j == 0)
            {
                t2 = msAPI_Timer_GetTime0();
                VDPLAYER_DBG(printf ("[MP4] audio index %d, pts %lld ,size %d, offset %llx, sync sample %d, time %d\n", i, pStart, pnSize, pOffset, is_sync_sample, t2 - t1));
            }
            i += MP4DMX_GetAudioIdxGap(pstMP4->mp4Inst, pnSize);
            j++;
            if (j == 100)
                j = 0;
        }
        t2 = msAPI_Timer_GetTime0();
        VDPLAYER_DBG(printf ("[MP4] audio index count %d, time %d\n", i, t2 - t1));
#endif
    return TRUE;
}

static int init_mp4_resource(ST_CONTAINER_MP4 *pstMP4, FileEntry *pFileEntry)
{
    int ret;

    pstMP4->file_handle = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_BINARY_FOR_READ, E_DATA_STREAM_TYPE_VIDEO);
    if (pstMP4->file_handle == INVALID_FILE_HANDLE)
    {
        printf("open file handle for mp4 fail\n");
        return FALSE;
    }

    U8* header = (U8*)msAPI_Memory_Allocate(16,BUF_ID_FILEBROWER);

    VDPLAYER_DBG(printf("open file handle for mp4, id %d\n", pstMP4->file_handle));
    ret = msAPI_DataStreamIO_Read(pstMP4->file_handle, (void *)_VA2PA((U32)header), 16);
    if (ret == 0)
    {
        MsOS_Dcache_Flush((U32)header, 16);
        MsOS_FlushMemory();
        if (probe_mp4(header, 16) == 0)
        {
            VDPLAYER_DBG(printf("not mp4 file\n"));
            release_mp4_resource(pstMP4);
        }
    }
    else
    {
        VDPLAYER_DBG(printf("mp4 file read size %d, not 16\n", 16 - ret));
        release_mp4_resource(pstMP4);
    }

    msAPI_Memory_Free(header,BUF_ID_FILEBROWER);

    return TRUE;
}
#endif

#if ENABLE_DVD
extern BOOLEAN msAPI_MVF_init_mempool (void *pool, U32 size);
extern void *msAPI_MVF_malloc (U32 size);
extern void msAPI_MVF_free (void *memp);

static void _MB_SeekPlay(void);
static void _MB_WaitDone(void);
static void _MB_Play(U8 type);
static void _MB_ScanSync(void);
static void _MB_ScanExit(void);
#endif  // ENABLE_DVD


#if (SUPPERTED_SEAMLESS_SMOTH)
static E_DATA_STREAM_MODE m_eSeamlessPreStreamMode;
static U32 m_u32TableAddress = 0;
static U32 m_u32TableSize = 0;
#endif

static U32 _MApp_VDPlayer_CheckSupportedAudio(void);

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------
//static char g_MAPPregistrationCodeString[9] = {0};
static MS_WINDOW_TYPE g_DstWin;
static VIDEO_PLAYER_INPUT_SOURCE_TYPE g_InputSourceType=VIDEO_PLAYER_INPUT_SOURCE_INVALID;
static VIDEO_PLAYER_PLAYING_TYPE g_VideoPlayerPlayingType=VIDEO_PLAYER_PLAYING_TYPE_MPEG4;

#define ENABLE_NEW_FILE_HANDLER    1

#if  ENABLE_NEW_FILE_HANDLER
#define TotalHandlerCnt    4 // V + A + Subtitle + Attach
static U32 u32StreamHandleIdx[TotalHandlerCnt] = {INVALID_DATA_STREAM_HDL,INVALID_DATA_STREAM_HDL,INVALID_DATA_STREAM_HDL,INVALID_DATA_STREAM_HDL};
#else //ENABLE_NEW_FILE_HANDLER
static U32 u32VDPlayerStreamHandleIdx_Video = INVALID_DATA_STREAM_HDL;
static U32 u32VDPlayerStreamHandleIdx_Subtitle = INVALID_DATA_STREAM_HDL;
#define AVHandlerCnt 2

#if ENABLE_AUDIO_HANDLER
#define AudioHandlerCnt  1
static U32 u32VDPlayerStreamHandleIdx_Audio = INVALID_DATA_STREAM_HDL;
#else
#define AudioHandlerCnt  0
#endif

#if ENABLE_ATTACHMENT_HANDLER
#define AttachmentHandlerCnt   1
static U32 u32VDPlayerStreamHandleIdx_Attachment = INVALID_DATA_STREAM_HDL;
#else
#define AttachmentHandlerCnt   0
#endif

#define TotalHandlerCnt (AVHandlerCnt + AudioHandlerCnt + AttachmentHandlerCnt)

#endif //ENABLE_NEW_FILE_HANDLER


static BOOL bStrmHdlAssignTbl[TotalHandlerCnt]; // 1 for av, 1 for subtitle

#ifdef _VDPLAYER_DUMP_RAW_
static U8 VDPlayer_dump_id;
#endif // _VDPLAYER_DUMP_RAW_
FileEntry *g_pVDPlayerFileEntry;

BOOLEAN g_bFirstDRMRegCode=TRUE;

BOOLEAN g_bDrmRental=FALSE;
U8 g_u8DrmUseLimit=0;
U8 g_u8DrmUseCount=0;


#define DRM_REG_CODE_LENG       10
#define DRM_DEACT_CODE_LENG     8

// To prevent garbage after set scaler window, we need to wait 4 frames for clean memory.
#define DEFAULT_FIELD_COUNT 4

U8 g_DRMRegCode[DRM_REG_CODE_LENG] = {0};
U8 g_DRMDeactivationCode[9] = {DRM_DEACT_CODE_LENG};


extern BOOLEAN g_bOutputMMAliveMessage;
extern VDEC_DispInfo gstVidStatus;
EN_VDP_SHAREMEMORY ShareMemory;
extern BOOLEAN g_b2ndRunPreviewMute;

static BOOLEAN g_WMDRMPrivateReady = FALSE;
static U8 g_WMDRMPrivate[WMDRMPD_PRIVATE_LENGTH];
static BOOLEAN _gbCoprocessorEnable = FALSE;
static EN_BM_STREAM_MODE _geBMStreamMode = E_BM_STREAM_MODE_NORMAL;
static BOOLEAN _gbEnableInternalSubtitle = TRUE;
static pfnForceStopCallBack _gpfnForceStopCallBack = NULL;
static U16 _gu16PreviewX = 0xffff, _gu16PreviewY = 0xffff, _gu16PreviewWidth = 0xffff, _gu16PreviewHeight = 0xffff;
static EN_ASPECT_RATIO_TYPE _geAspectRatioType = VIDEOSCREEN_MM_FULL;

//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
static BOOLEAN          m_bSuspendInternalSubtitle2Queue=FALSE;
static BOOLEAN          m_bVDPlayerPreview=FALSE;
static BOOLEAN          m_bVDPlayerThumbnail=FALSE;
#if ENABLE_PROBE_MOVIE_HEADER
static BOOLEAN          m_bVDPlayerProbeHeaderOnly=FALSE;
#endif
static EN_VDPLAYER_FAIL_STATUS m_eFailStatus = E_VDPLAYER_FAIL_STATUS_VDPLAYER_ERROR;
static enumVDPlayerFlags  m_eVDPlayerFlgs=E_VDPLAYER_FLG_SHOWVIDEO;
#if ENABLE_POWERON_VIDEO
static BOOLEAN          m_bVDPlayerPowerOnVideo=FALSE;
#endif

#if ENABLE_USB_READ_RATE_MEASURED
static U32 m_u32ReadTimeMeasured = 0;
static U32 m_u32ReadSizeMeasured = 0;
#endif

static U32  m_u32CodecTimeOut[E_SHAREMEM_ESBUF_CTRL_TIMEOUT-E_SHAREMEM_BLOCK_FILEIO_TIMEOUT+1];
static U32 u8VDPlayerPlayTimeOut = 5000;
static U8 u8VDPlayerInitResult = 0;
static U8 u8VDPlayerStepPlayResult = 0;
static U8 u8VDPlayerSetTrickModeResult = 0;
static U8 u8VDPlayerSetAudioTrackResult = 0;
static U8 u8VDPlayerTsSetProgramResult = 0;

#if ENABLE_DRM
#include <time.h>

static BOOLEAN bDrmRegCode          = FALSE;
static BOOLEAN bDrmFileFormat       = FALSE;
static BOOLEAN bDrmActivationFile   = FALSE;
static BOOLEAN bDrmAuthorization    = FALSE;
static BOOLEAN bDrmRentalStatus     = FALSE;
static stDRMinfo DRMinfo ;
BOOLEAN g_bReplay = FALSE;
BOOLEAN g_bIsResumePlay = FALSE;

#endif
static EN_RET enVDPlayerRet = EXIT_NULL;
static enumVDPlayerAckFlags m_eVDPlayerAckFlags = E_ACKFLG_NULL;

#if ENABLE_DVD
static BOOLEAN bIsDVD;
#endif

U32 u32VdplayerShareMemAddr = 0;
static EN_VDPLAYER_VIDEO_TYPE enVDPlayerVideoType;
#if ENABLE_WMDRMPD
U32 u32WMDRMPDShareMemAddr;
#endif

// Use u32VDPlayerLoopWdtTimer for (1) Init timeout check (2) Runtime Aeon status timeout check
U32 u32VDPlayerLoopWdtTimer = 0;

#if (VDPLAYER_CHECK_COPROCESSOR_STATUS)
static U32 u32VDPlayerLoopCount = 0;
static U32 u32VDPlayerLoopPrevCount = 0;
#endif

static BOOLEAN bMovieAbort = FALSE;

// Subtitle flow control
U8 u8IssubtitleInit=FALSE;        // EN_SUBTITLE_INIT_COMMAND
U8 u8IsSubtitleInitfinish=FALSE;      // EN_SUBTITLE_INIT_COMMAND
U8 u8IsSubtitleBusy=FALSE;
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
U8 u8IsFontTableReady=FALSE;
#endif

//U8 u8gIsShowSubtitle = TRUE;
//U8 u8SubtitleTrackID =0;
U16 u16tagposition=0;
U16 u16SubtitleTagCnt=0;
#if (ENABLE_MPLAYER_MOVIE)
static U32 m_u32PreMovieRefreshTextTimer = 0; //recording previous entering time of MApp_VDPlayer_RefreshTextSubtitleTag()
#endif
U32 u32subtitletype=0;
U32 u32GetSubtitleStateBuf=0;
#if (ENABLE_SUBTITLE_DMP)
static S32 m_s32PreSubtitleTagIdx = -1;
#if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
static MPlayer_Subtitle_Tag m_astInternalTextSubtitleTag[MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT];
#endif
#endif //#if (ENABLE_SUBTITLE_DMP)

BOOLEAN g_bUnsupportAudio=FALSE;  //20100809EL
BOOLEAN m_bFLG_PREVIEW = FALSE;


#define PGS_DBG(x)    //x
#define BMP_DBG(x)    //x

#if (TS_INTERNAL_SUBTITLE_BMP || TS_INTERNAL_SUBTITLE_PGS)
static BOOLEAN _bSubtitleShow_User = DISABLE;      // control by user.
static BOOLEAN _bSubtitleShow_MW   = DISABLE;      // control by MW.
static U8 u8InternalST_Num = 0;
U16 u16CPageID,u16APageID;
#endif

// RM used
static U16 u16CodecNum = 0;
static U16 u16Samples_channel = 0;
static U16 u16CannelsA[5] ={0,0,0,0,0};
static U16 u16RegionsA[5] = {0,0,0,0,0};
static U16 u16cplStartA[5] ={0,0,0,0,0};
static U16 u16cplQbitsA[5] = {0,0,0,0,0};
static U16 u16FrameSizeA[5] = {0,0,0,0,0};

static BOOLEAN _bEnableVideoOnly = FALSE;

static U32 _gu32ResidualReadSize;
static U32 _gu32gStreamHdl;
static U32 _gu32BuffAddr;
static BOOLEAN _gbContinueBlockRead = FALSE;
static U32 _gu32BlockReadTimer;
static BOOLEAN _bStreamSeeked;  //when file be seeked, then blockreading until read some bytes

#if SEAMLESS_PLAYING_ENABLE
static BOOL _bEnableSeamlessPlaying = FALSE;
static U32 _u32SeamlessTimer;
#endif

#if ENABLE_AMR
    static U32 u32VDPlayerAudioSupportedFormat = E_VDP_AUDIO_SUPPORT_ALL;
#else
    static U32 u32VDPlayerAudioSupportedFormat = E_VDP_AUDIO_NO_SUPPORT_AMR_NB | E_VDP_AUDIO_NO_SUPPORT_AMR_WB;
#endif

#if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
static U8 u8Pre_StrmHdlIdx = AV_FILE_HANDLE; //Store previous stream file handle index
static LongLong u64BackupFilePosition[TotalHandlerCnt]={{0,0}}; //Store file position for each file handle
#endif
static BOOL gbStreamMode = FALSE;

#if ENABLE_HK_MM
static BOOLEAN m_bMM_Initial = FALSE;
extern U32 g_u32IOReadTimer;
#endif

#if ENABLE_HK_DRM_GENCODE
    extern BOOLEAN GetDRMRegistrationCode(U16 u16DrmModelID, U32 drmCodeAddr, U32 drmSysTime, U8 *drmData);
    extern BOOLEAN GetDRMDeactivationCode(U16 u16DrmModelID, U32 drmCodeAddr, U8 *drmData);
#endif

static U32 m_u32VideoSyncDelayMsTime = 0;

//For music init
#define INIT_VOLUME stGenSetting.g_SoundSetting.Volume

extern U16 MApp_Transfer2Unicode(U16 u16Code);
//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------
static void _VDPlayer_SendMailboxMsg(U8 _class, U8 _index, MBX_MSG_Type _type, U8 _count,
                                        U8 _p1, U8 _p2, U8 _p3, U8 _p4, U8 _p5, U8 _p6, U8 _p7, U8 _p8, U8 _p9, U8 _p10);

#if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
static U32 MApp_VDPlayer_GetStrmHandleForSimulateMultiFileHandler(U8 u8StrmHdlIdx, BOOLEAN bSeekToBackupFilePosition);
#endif

#if ENABLE_HK_MM
static U32 _MApp_VDPlyer_LimitedFileRead(U32 u32Hdl, void *pBuffAddr, U32 u32Length, U32 u32LimitSize, U16 u16LimitTime);
static void _MApp_VDPlyer_VMailboxCallback(MBX_Msg *pMsg, MS_BOOL *pbAddToQueue);
#endif
//-------------------------------------------------------------------------------------------------
// Function Implementation
//-------------------------------------------------------------------------------------------------
#if ENABLE_DVD

int opened = 0;
int IoCallback_Open(const char *filename, int mode)
{
    U16 i;
    U16 u16FileName[128];
    FileEntry entry;
    U16 len;
    U8 handle;

    len = strlen(filename);
    VDPLAYER_DVD_DBG(printf("IoCallback_Open: %s, opened = %d\n", filename, opened));

    for (i = 0; i < len; i++)
    {
        u16FileName[i] = (U16)filename[i];
    }
    u16FileName[len] = 0x0;

    if (MApp_FilrBrowser_GetNameExistedInCurrent(u16FileName, len, &entry))
    {
        U8 u8OpenMode = OPEN_MODE_BINARY_FOR_READ;

        mode = mode;
        handle = msAPI_FCtrl_FileOpen(&entry, u8OpenMode);
        if (handle != INVALID_FILE_HANDLE)
        {
            opened++;
            VDPLAYER_DVD_DBG(printf("open %s pass: %d. opned = %d\n", filename, handle, opened));
            return handle;
        }
    }

    VDPLAYER_DVD_DBG(printf("open %s fail\n", filename));
    return -1;
}

int IoCallback_Close(int handle)
{
    opened--;
    VDPLAYER_DVD_DBG(printf("IoCallback_Close: %d, opned = %d\n", handle, opened));
    msAPI_FCtrl_FileClose(handle);

    return 0;
}

#if FILE_SYSTEM_LONGLONG_API_ENABLE
LongLong IoCallback_Seek(int handle, LongLong offset, int whence)
{
    BOOLEAN ret;
    LongLong u64FileOffset;

    u64FileOffset.Hi = offset.Hi;
    u64FileOffset.Lo = offset.Lo;
    ret = msAPI_FCtrl_FileSeek_LongLong(handle, u64FileOffset, (EN_FILE_SEEK_OPTION)whence);
    //printf("IoCallback_Seek: %d %08x %08x %d. ret = %d\n", handle, offset.Hi, offset.Lo, whence, ret);

    if (ret)
    {
        if (whence == 0)
            return offset;
        else
        {
            LongLong ret1, ret2;

            ret1 = msAPI_FCtrl_FileTell_LongLong(handle);
            ret2 = LL_addLong(&ret1, &offset);
            return ret2;
        }
    }
    else
    {
        LongLong ret1;
        //return -1;
        ret1.Hi = 0xFFFFFFFF;
        ret1.Lo = 0xFFFFFFFF;
        return ret1;
    }
}
#else
int IoCallback_Seek(int handle, int offset, int whence)
{
    BOOLEAN ret;

    ret = msAPI_FCtrl_FileSeek(handle, (U32)offset, (EN_FILE_SEEK_OPTION)whence);
    //printf("IoCallback_Seek: %d %08x %08x %d. ret = %d\n", handle, offset.Hi, offset.Lo, whence, ret);

    if (ret)
    {
        if (whence == 0)
            return offset;
        else
            return msAPI_FCtrl_FileTell(handle) + offset;
    }
    else
        return -1;
}
#endif

int IoCallback_Read(int handle, void *buf, int count)
{
    int left;

    //printf("IoCallback_Read: addr = %08x, addr1 = %08x, count = %d\n", (U32)buf, _VA2PA((U32)buf), count);
    //left = msAPI_FCtrl_FileRead((U8)handle, _VA2PA((U32)buf), count);
    left = msAPI_FCtrl_FileRead((U8)handle, MP4_SUBTITLE_BUFFER_ADR, count);
    //VDPLAYER_DVD_DBG(printf("IoCallback_Read: want %d, read %d\n", count, count - left));
    //MsOS_Sync();
    MsOS_FlushMemory();
    memcpy(buf, (void *)_PA2VA(MP4_SUBTITLE_BUFFER_ADR), count - left);
    //MsOS_Sync();
    MsOS_FlushMemory();
    //msAPI_Timer_Delayms(100);

    return (count - left);
}

#if FILE_SYSTEM_LONGLONG_API_ENABLE
LongLong IoCallback_Size(int handle)
{
    LongLong size;

    size = msAPI_FCtrl_FileLength_LongLong(handle);
    //printf("IoCallback_Size: %08x %08x\n", size.Hi, size.Lo);
    return size;
}
#else
int IoCallback_Size(int handle)
{
    U32 size;

    size = msAPI_FCtrl_FileLength(handle);
    //printf("IoCallback_Size: %d\n", size);
    return (int)size;
}
#endif

void *MemCallback_Malloc(int size)
{
    void *p;

    size = (size + 4) & 0xFFFFFFFC;
    p = msAPI_MVF_malloc(size);
    //VDPLAYER_DVD_DBG(printf("MemCallback_Malloc: %d %08x\n", size, (U32)p));

    return p;
}

void *MemCallback_Realloc(void *ptr, int size)
{
    size = (size + 4) & 0xFFFFFFFC;

    //VDPLAYER_DVD_DBG(printf("MemCallback_Realloc: %d\n", size));
    msAPI_MVF_free(ptr);
    return msAPI_MVF_malloc(size);
}

void MemCallback_Free(void *ptr)
{
    //VDPLAYER_DVD_DBG(printf("MemCallback_Free: %08x %08x\n", (U32)ptr, *(U32 *)((U32)ptr - 4));
    msAPI_MVF_free(ptr);
}

int GenericCallback(int type, int subtype, int *ret1, int *ret2)
{
    ret2 = ret2;
    switch (type)
    {
        case DVD_CALLBACK_TYPE_MB:
            if (subtype == DVD_CALLBACK_SUBTYPE_MB_SEEKPLAY)
            {
                _MB_SeekPlay();
            }
            else if (subtype == DVD_CALLBACK_SUBTYPE_MB_WAITDONE)
            {
                _MB_WaitDone();
            }
            else if (subtype == DVD_CALLBACK_SUBTYPE_MB_PLAY)
            {
                _MB_Play(*ret1);
            }
            else if (subtype == DVD_CALLBACK_SUBTYPE_MB_SCANSYNC)
            {
                _MB_ScanSync();
            }
            else if (subtype == DVD_CALLBACK_SUBTYPE_MB_SCANEXIT)
            {
                _MB_ScanExit();
            }
            break;
        case DVD_CALLBACK_TYPE_WAIT:
            if (subtype == DVD_CALLBACK_SUBTYPE_WAIT_WAITDONE)
            {
                if (m_eVDPlayerAckFlags & E_ACKFLG_WAIT_DONE)
                {
                    return FALSE;
                }
                else
                {
                    return TRUE;
                }
            }
            else if (subtype == DVD_CALLBACK_SUBTYPE_WAIT_SCANDONE)
            {
                if (m_eVDPlayerAckFlags & E_ACKFLG_WAIT_SCANDONE)
                {
                    return FALSE;
                }
                else
                {
                    return TRUE;
                }
            }
            break;
        case DVD_CALLBACK_TYPE_MISC:
            if (subtype == DVD_CALLBACK_SUBTYPE_MISC_DVDSTOP)
            {
                enVDPlayerRet = EXIT_VDPLAYER_EXIT;
            }
            else if (subtype == DVD_CALLBACK_SUBTYPE_MISC_CURRENTTIME)
            {
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_TIME);
            }
            else if (subtype == DVD_CALLBACK_SUBTYPE_MISC_NOTIFY)
            {
                MApp_UiMediaPlayer_Notify(E_MPLAYER_NOTIFY_DVD_RESUME_NORMAL_PLAY, NULL);
            }
            break;
        default:
            break;
    }
    return 0;
}
#endif

static void _VDPlayer_SendMailboxMsg(U8 _class, U8 _index, MBX_MSG_Type _type, U8 _count,
                                        U8 _p1, U8 _p2, U8 _p3, U8 _p4, U8 _p5, U8 _p6, U8 _p7, U8 _p8, U8 _p9, U8 _p10)
{
    MBX_Msg m5_mbxMsg;
    MBX_Result mbxResult;

    m5_mbxMsg.u8MsgClass            = _class;
    m5_mbxMsg.u8Index               = _index;
    m5_mbxMsg.u8ParameterCount      = _count;
    m5_mbxMsg.eMsgType              = _type;
    m5_mbxMsg.u8Parameters[0]       = _p1;
    m5_mbxMsg.u8Parameters[1]       = _p2;
    m5_mbxMsg.u8Parameters[2]       = _p3;
    m5_mbxMsg.u8Parameters[3]       = _p4;
    m5_mbxMsg.u8Parameters[4]       = _p5;
    m5_mbxMsg.u8Parameters[5]       = _p6;
    m5_mbxMsg.u8Parameters[6]       = _p7;
    m5_mbxMsg.u8Parameters[7]       = _p8;
    m5_mbxMsg.u8Parameters[8]       = _p9;
    m5_mbxMsg.u8Parameters[9]       = _p10;

    do
    {
    #if ENABLE_HK_MM
        mbxResult = MDrv_VMBX_SendMsg(&m5_mbxMsg);
    #else
        mbxResult = MSApi_MBX_SendMsg(&m5_mbxMsg);
    #endif
        switch(mbxResult)
        {
            case E_MBX_ERR_PEER_CPU_BUSY:
            case E_MBX_ERR_PEER_CPU_NOTREADY:
            case E_MBX_ERR_PEER_CPU_NOT_ALIVE:
                //Error Handling here...
                break;
            case E_MBX_ERR_PEER_CPU_OVERFLOW:
                //MsOS_DelayTask(1);
                break;
            default:
                break;
        }
    }while(E_MBX_SUCCESS != mbxResult);
}

#if SEAMLESS_PLAYING_ENABLE
void MApp_VDPlayer_EnableSeamless(BOOL bEnableSeamless)
{
    _bEnableSeamlessPlaying = bEnableSeamless;
}

BOOL MApp_VDPlayer_GetSeamlessMode(void)
{
    return _bEnableSeamlessPlaying;
}
#endif

static BOOLEAN _MApp_VDPlayer_GetInterlace(void)
{
#if (ENABLE_MIU_1==0)
    U16 width,height;

    if(enVDPlayerVideoType==E_VDPLAYER_VIDEO_H264)
    {
        width =  _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
        height = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT);
        if(width>=1890 && height>=1000)
        {
           // return TRUE; //force MVOP to Interlace to reduce bandwidth in H264 FHD
        }
    }
#endif
    return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_INTERLACE);
}

//-------------------------------------------------------------------------------------------------
///
/// DRM functions
///
///
//-------------------------------------------------------------------------------------------------
U32 MApp_VDPlayer_GCD(U32 u32A, U32 u32B)
{
   S32 i;
   U32 x[4]; /* need x[0], x[1], x[i-1] */

   if (u32A > u32B)
   {
     x[0] = u32A; x[1] = u32B;
   }
   else
   {
     x[0] = u32B; x[1] = u32A;
   }
   i = 1;
   #define w(x) (((x)<4)?(x):(2+((x)&1)))
   while( x[w(i)] != 0 )
   {
       x[w(i+1)] = x[w(i-1)] % x[w(i)];
       i++;
   }
   return x[w(i-1)];
   #undef w
}


void MApp_VDPlayer_AdjustRatioByPAR(U32 u32Hsize, U32 u32Vsize, U32 u32DAR_H, U32 u32DAR_V, U32* u32TargetH, U32* u32TargetV,MS_WINDOW_TYPE stDisplayWin )
{  //DAR
    U32 u32ratio=0;
    U32 u32Gcd_DAR=MApp_VDPlayer_GCD(u32DAR_H,u32DAR_V);//Get Highest common factor

    VDPLAYER_DVD_DBG(printf("\n  u32DarW=%ld,u32DarH=%ld , u32Gcd_DAR=%ld", u32DAR_H, u32DAR_V, u32Gcd_DAR));
    if (u32Gcd_DAR==0)
    {
        *u32TargetH =u32Hsize;
        *u32TargetV =u32Vsize;
        VDPLAYER_DVD_DBG(printf("\n [error] GCD = 0"));
        return;
    }

    //check ptImageWin value
    if(stDisplayWin.height==0)
    {
        stDisplayWin.height= (U16)PANEL_HEIGHT;
    }
    if(stDisplayWin.width==0)
    {
        stDisplayWin.width= (U16)PANEL_WIDTH;
    }


    //calculate ratio
    if ( ( ( u32DAR_V/u32Gcd_DAR)* stDisplayWin.width) / (u32DAR_H/u32Gcd_DAR)< stDisplayWin.height)
    {
        u32ratio=(U32)stDisplayWin.width*1000/(u32DAR_H/u32Gcd_DAR);
    }
    else
    {
        u32ratio=(U32)stDisplayWin.height*1000/( u32DAR_V/u32Gcd_DAR);
    }

    *u32TargetH = (u32DAR_H/u32Gcd_DAR)*u32ratio/1000;//*u32Hsize;
    *u32TargetV = (u32DAR_V/u32Gcd_DAR)*u32ratio/1000;//*u32Vsize;
    VDPLAYER_DVD_DBG(printf("\nmodify W=%ld, H=%ld ", *u32TargetH, *u32TargetV));
    if (*u32TargetH==0)
    {
        *u32TargetH =u32Hsize;
        VDPLAYER_DVD_DBG(printf("\n [error] u16TargetH = 0"));
    }
    if (*u32TargetV==0)
    {
        *u32TargetV =u32Vsize;
        VDPLAYER_DVD_DBG(printf("\n [error] u16TargetV = 0"));
    }

#if 0 //transfer to PAR
    U32 u32Ret = 0;

    U32 u32DarW = 0;
    U32 u32DarH = 0;
    U32 u32SarW = 0;
    U32 u32SarH = 0;

    U32 u32ParW = 0;
    U32 u32ParH = 0;
    U32 u32Gcd = 0;
    //printf("\n  MApp_VDPlayer_AdjustRatioByPAR ");
    //WIDTH:
    U32 u32Gcd_PAR=MApp_VDPlayer_GCD(u32PAR_H,u32PAR_V);//Get Highest common factor
    U32 u32Gcd_Size=MApp_VDPlayer_GCD(u32Hsize, u32Vsize);//Get Highest common factor

    u32DarW = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_PAR_H_SIZE);
    u32DarH = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_PAR_H_SIZE);
    u32SarW = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_H_SIZE);
    u32SarH = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_V_SIZE);
    printf("\n u32DarW=%d,u32DarH=%d , u32SarW=%d, u32SarH=%d", u32DarW, u32DarH, u32SarW, u32SarH);

    u32ParW = (u32PAR_H/u32Gcd_PAR) * (u32Vsize/u32Gcd_Size);
    u32ParH = (u32PAR_V/u32Gcd_PAR) * (u32Hsize/u32Gcd_Size);
    printf("\n u32ParW=%d,u32ParH=%d ", (U32)u32ParW, (U32)u32ParH);

    if(u32ParW==0 || u32ParH==0)
    {
        u32Ret = 0;
        //__ASSERT(0);
        return;
    }

    u32Gcd=MApp_VDPlayer_GCD(u32ParW,u32ParH);//Get Highest common factor
    //printf("\n GCD=%ld ", (U32)u64Gcd);
    if(u32Gcd==0)
    {
        u32Ret=0;
        //__ASSERT(0);
    }
    else
    {
        u32Ret = (U32)(u32ParW/u32Gcd); //ans
    }
    *u16TargetV =(U16) u32Ret;
    //printf("\n modified width=%ld ", u32Ret);

    //HEIGHT:
    if(u32Gcd==0)
    {
        u32Ret=0;
        //__ASSERT(0);
    }
    else
    {
        u32Ret = (U32)(u32ParH/u32Gcd);
    }
    *u16TargetH =(U16) u32Ret;
    //printf("\n modified width=%d ", u32Ret);
#endif
#if 0 //use par to DAR
    U16 _u16TargetH, _u16TargetV, u16OriginalRatio, u16Temp;

    if ((u32PAR_H == 0xffffffff) && (u32PAR_V == 0xffffffff))
    {
        u32PAR_H = u32PAR_V = 1;
    }

    _u16TargetH = u16Hsize;
    _u16TargetV = u16Vsize;
    //printf(" par H : %lu  par V : %lu \n", u32PAR_H , u32PAR_V);
    if ( u32PAR_H > 0 &&  u32PAR_V > 0 )
    {
        /*
            If the source contain PAR information, the ratio of displaywindow have to be re-calculate again.
            The final displaywindow ratio should be equal to ( ( Hcap * Par_width ) / ( Vcap * Par_height ) )

            The algorithm : Change the current aspect ratio to ( ( Hcap * Par_width ) / ( Vcap * Par_height ) ) by using "decrease size"
                            If original ratio ( Hcap / Vcap )  <  target ratio ( ( Hcap * Par_width ) / ( Vcap * Par_height ) )
                               Decrease V size to meet target ratio
                            else
                               Decrease H size to meet target ratio.
        */
        u16OriginalRatio = ( (U32) _u16TargetH * 1000 ) /  ( (U32) _u16TargetV );

        u16Temp = ( (U32) _u16TargetH * u32PAR_H * 1000 ) / ( (U32) _u16TargetV * u32PAR_V );

        // Compare the ratio.
        if ( u16OriginalRatio > u16Temp ) //
        {
            _u16TargetH = ( ( (U32)_u16TargetH * u32PAR_H * 1000 ) / ( u32PAR_V ) ) / 1000;
        }
        else
        {
            _u16TargetV = ( ( (U32)_u16TargetV * u32PAR_V * 1000 ) / ( u32PAR_H ) ) / 1000;
        }

    }

    *u16TargetH = _u16TargetH;
    *u16TargetV = _u16TargetV;
#endif
}

#if ENABLE_DRM

#if 0
BOOLEAN MApp_VDPlayer_ClearDRMMemory_Demo(void)
{
    U32 i=0;

    for(i=0; i<48; i++)
    {
        stGenSetting.g_u8DRMMemory[i] = 0;
    }
#if 0
    stGenSetting.g_u8DRMMemory[0] = 0xCF;
    stGenSetting.g_u8DRMMemory[1] = 0xBC;
    stGenSetting.g_u8DRMMemory[2] = 0xFC;
#else//RegCode: TA5WB362
    stGenSetting.g_u8DRMMemory[0] = 0x5A;
    stGenSetting.g_u8DRMMemory[1] = 0x48;
    stGenSetting.g_u8DRMMemory[2] = 0xD1;
#endif
    MApp_SaveGenSetting();

    return TRUE;
}

BOOLEAN MApp_VDPlayer_ClearDRMMemory(void)
{
    U32 i;

    for (i = 0; i < 48; i++)
    {
        stGenSetting.g_u8DRMMemory[i] = 0;
    }

    MApp_SaveGenSetting();

    return TRUE;
}

BOOLEAN MApp_VDPlayer_GetDRMRegistrationCode_Demo(U32 drmCodeAddr)
{
    U32 u32DrmTimout = 0;

    MApp_VDPlayer_LoadDRMMemory();

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_GET_DRM_REG_CODE;

    if (msAPI_MailBox_WaitReady())
    {
        MailBoxPara.u8CmdClass      = MB_CLASS_VDPLAYER_FS;
        MailBoxPara.u8CmdIdx        = MB_VDPLAYER_GET_DRM_REG_CODE;
        MailBoxPara.ParamCnt        = 4;
        MailBoxPara.CMDType         = MB_CMD_TYPE_DEFAULT;
        MailBoxPara.u8Param[0] = (U8)((drmCodeAddr&0xFF000000)>>24);
        MailBoxPara.u8Param[1] = (U8)((drmCodeAddr&0x00FF0000)>>16);
        MailBoxPara.u8Param[2] = (U8)((drmCodeAddr&0x0000FF00)>>8);
        MailBoxPara.u8Param[3] = (U8)((drmCodeAddr&0x000000FF));
        msAPI_MailBox_SendMsg();
    }

    // Waiting for Aeon Video Player Ack
    u32DrmTimout = msAPI_Timer_GetTime0();
    bDrmRegCode = FALSE;

    do
    {
        MApp_VDPlayer_MailBoxHandler();
    }
    while ((m_eVDPlayerAckFlags & E_ACKFLG_WAIT_GET_DRM_REG_CODE) &&
                (msAPI_Timer_DiffTimeFromNow(u32DrmTimout)<VDPLAYER_COPROCESSOR_CHECK_TIMEOUT));

    *((char *)drmCodeAddr) = g_DRMRegCode[0];
    *((char *)drmCodeAddr+1) = g_DRMRegCode[1];
    *((char *)drmCodeAddr+2) = g_DRMRegCode[2];
    *((char *)drmCodeAddr+3) = g_DRMRegCode[3];
    *((char *)drmCodeAddr+4) = g_DRMRegCode[4];
    *((char *)drmCodeAddr+5) = g_DRMRegCode[5];
    *((char *)drmCodeAddr+6) = g_DRMRegCode[6];
    *((char *)drmCodeAddr+7) = g_DRMRegCode[7];

    MApp_VDPlayer_SaveDRMMemory();

    return bDrmRegCode;
}
#endif
//void MApp_WriteDatabase(U32 dstIndex, U8* srcAddr, U16 size);
//void MApp_ReadDatabase(U32 srcIndex, U8* dstAddr, U16 size);
static unsigned long next = 1;

int MApp_VDPlayer_Myrand(void)
{

    next = next * 1103515245 + 12345;

    return((unsigned)(next/65536) % 32768);

}

void MApp_VDPlayer_Mysrand(unsigned seed)
{
    next = seed;
}

#if(!ENABLE_HK_DRM_GENCODE)
//BOOLEAN MApp_VDPlayer_tmp_init(void);

BOOLEAN MApp_VDPlayer_tmp_init(void)
{
#if ENABLE_HK_MM
    //E_MBX_CLASS_VDPLAYER use callback function for immediately command
    if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSGWithCallBack(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE, _MApp_VDPlyer_VMailboxCallback))
    {
        if(E_MBX_SUCCESS != MDrv_VMBX_UnRegisterMSG(E_MBX_CLASS_VDPLAYER, TRUE))
        {
            VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSGWithCallBack(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE, _MApp_VDPlyer_VMailboxCallback))
            {
                VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER register failed\n"));
                return FALSE;
            }
        }
    }

    //E_MBX_CLASS_VDPLAYER_FS use queue and not immediately
    if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSG(E_MBX_CLASS_VDPLAYER_FS, MM_COMMON_MBX_QUEUESIZE))
    {
        if(E_MBX_SUCCESS != MDrv_VMBX_UnRegisterMSG(E_MBX_CLASS_VDPLAYER_FS, TRUE))
        {
            VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER_FS unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSG(E_MBX_CLASS_VDPLAYER_FS, MM_COMMON_MBX_QUEUESIZE))
            {
                VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER_FS register failed\n"));
                return FALSE;
            }
        }
    }
#else //#if ENABLE_HK_MM
    if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE))
    {
        if(E_MBX_SUCCESS != MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_VDPLAYER))
        {
            VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE))
            {
                VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER register failed\n"));
                return FALSE;
            }
        }
    }
#endif //#if ENABLE_HK_MM

    return TRUE;
}
#endif //(!ENABLE_HK_DRM_GENCODE)



BOOLEAN MApp_VDPlayer_CheckAndGenDRMData(void)
{
    //VDplayerDRMInfo DRM_info;
#if ENABLE_HK_DRM_GENCODE
    // In GetDRMRegistrationCode function, it would generate Registration code and add a zero bytes at the code end.
    U8 u8RegistrationCode[DIVX_REG_CODE_LEN+1]={0};
#else
    U8 u8RegistrationCode[DIVX_REG_CODE_LEN];
#endif
    BOOLEAN bNeedGenCode = FALSE;
    int i;

    //MApp_VDPlayer_OperateDRMData(E_DRM_LOAD, &DRM_info);
    MApp_LoadDrmSetting();
    printf("bIsKeyGenerated=%d\n", stGenSetting.g_VDplayerDRMInfo.bIsKeyGenerated);
    printf("bIsActivated=%d\n", stGenSetting.g_VDplayerDRMInfo.bIsActivated);
    printf("bIsDeactivated=%d\n", stGenSetting.g_VDplayerDRMInfo.bIsDeactivated);

    if(stGenSetting.g_VDplayerDRMInfo.bIsKeyGenerated == FALSE)
        bNeedGenCode = TRUE;

    if(stGenSetting.g_VDplayerDRMInfo.bIsActivated > 1)   // illegal value
        bNeedGenCode = TRUE;

    if(stGenSetting.g_VDplayerDRMInfo.bIsDeactivated > 1) // illegal value
        bNeedGenCode = TRUE;

    if(bNeedGenCode)
    {
        printf("Need to re-gen DRM key\n");
        BOOLEAN bDrmGenRegCode = FALSE;
        // generate DRM activation code
        //MApp_VDPlayer_OperateDRMData(E_DRM_INIT, NULL); // reset DRM data
#if ENABLE_HK_DRM_GENCODE
        U8 u8Random[4]={0};
        U32 u32SysTime = msAPI_Timer_GetTime0();
        extern U16 u16DRMModelID;

        MApp_VDPlayer_Mysrand(u32SysTime);
        for(i=0; i<4; i++)
        {
            u8Random[i]=(U8)MApp_VDPlayer_Myrand();
        }
        bDrmGenRegCode = GetDRMRegistrationCode(u16DRMModelID, (U32) u8RegistrationCode, (U32) u8Random, (U8*)&stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[0]);
#else
        MApp_VDPlayer_tmp_init();
        bDrmGenRegCode = MApp_VDPlayer_GetDRMRegistrationCode((U32) u8RegistrationCode);
#endif
        if(bDrmGenRegCode == TRUE)
        {
            printf("**\n");
            for(i = 0; i < 10; i++)
                printf("%c", u8RegistrationCode[i]);
            printf("**\n");

            //MApp_VDPlayer_OperateDRMData(E_DRM_LOAD, &DRM_info);

            stGenSetting.g_VDplayerDRMInfo.bIsKeyGenerated = TRUE;
            memcpy(stGenSetting.g_VDplayerDRMInfo.u8RegistrationCode, u8RegistrationCode, DIVX_REG_CODE_LEN);
            MApp_SaveDrmSetting();
            //MApp_VDPlayer_OperateDRMData(E_DRM_SAVE, &DRM_info);
            printf("Need to re-gen DRM key OK\n");
        }
        else
        {
            printf("Need to re-gen DRM key fail\n");

        }
        return TRUE;
    }

    return FALSE;
}

BOOLEAN MApp_VDPlayer_Deactivate(void)
{
    //VDplayerDRMInfo DRM_info;
#if ENABLE_HK_DRM_GENCODE
    // In GetDRMDeactivationCode and GetDRMRegistrationCode functions, they would generate codes and add a zero bytes at the code end.
    U8 u8DeActivationCode[DIVX_DEACT_CODE_LEN+1]={0};
    U8 u8RegistrationCode[DIVX_REG_CODE_LEN+1]={0};
#else
    U8 u8DeActivationCode[DIVX_DEACT_CODE_LEN];
    U8 u8RegistrationCode[DIVX_REG_CODE_LEN];
#endif
    BOOLEAN bDrmGenRegCode = FALSE;
    BOOLEAN bDrmDeRegCode = FALSE;

    //MApp_VDPlayer_OperateDRMData(E_DRM_LOAD, &DRM_info);
    MApp_LoadDrmSetting();
    printf("bIsKeyGenerated=%d\n", stGenSetting.g_VDplayerDRMInfo.bIsKeyGenerated);
    printf("bIsActivated=%d\n", stGenSetting.g_VDplayerDRMInfo.bIsActivated);
    printf("bIsDeactivated=%d\n", stGenSetting.g_VDplayerDRMInfo.bIsDeactivated);

    if(stGenSetting.g_VDplayerDRMInfo.bIsActivated)
    {
        printf("De-activate DRM\n");

#if ENABLE_HK_DRM_GENCODE
        extern U16 u16DRMModelID;
        bDrmDeRegCode = GetDRMDeactivationCode(u16DRMModelID, (U32) u8DeActivationCode, (U8*)&stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[0]);
#else
        MApp_VDPlayer_tmp_init();
        bDrmDeRegCode = MApp_VDPlayer_GetDRMDeactivationCode((U32) u8DeActivationCode);
#endif
        if(bDrmDeRegCode == FALSE)
        {
            printf(" De-active DRM generate code fail  \n");
        }

    #if 0
        printf("Deactivate code\n");
        for(i = 0; i<DIVX_DEACT_CODE_LEN; i++)
            printf("%c ", u8DeActivationCode[i]);
        printf("\nDeactivate done\n");
    #endif

#if ENABLE_HK_DRM_GENCODE
        U8 i;
        U8 u8Random[4]={0};
        U32 u32SysTime = msAPI_Timer_GetTime0();

        MApp_VDPlayer_Mysrand(u32SysTime);
        for(i=0; i<4; i++)
        {
            u8Random[i]=(U8)MApp_VDPlayer_Myrand();
        }
        bDrmGenRegCode = GetDRMRegistrationCode(u16DRMModelID, (U32) u8RegistrationCode, (U32) u8Random, (U8 *) &stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[0]);
#else
        MApp_VDPlayer_tmp_init();
        bDrmGenRegCode = MApp_VDPlayer_GetDRMRegistrationCode((U32) u8RegistrationCode);
#endif
        if(bDrmGenRegCode == TRUE)
        {

        #if 0
            printf("Reg code\n");
            for(i = 0; i<DIVX_REG_CODE_LEN; i++)
                printf("%c ", u8RegistrationCode[i]);
            printf("\n");
        #endif

            //MApp_VDPlayer_OperateDRMData(E_DRM_LOAD, &DRM_info);

            stGenSetting.g_VDplayerDRMInfo.bIsDeactivated = TRUE;
            stGenSetting.g_VDplayerDRMInfo.bIsActivated = FALSE;
            memcpy(stGenSetting.g_VDplayerDRMInfo.u8RegistrationCode, u8RegistrationCode, DIVX_REG_CODE_LEN);
            memcpy(stGenSetting.g_VDplayerDRMInfo.u8DeActivationCode, u8DeActivationCode, DIVX_DEACT_CODE_LEN);
            MApp_SaveDrmSetting();
            //MApp_VDPlayer_OperateDRMData(E_DRM_SAVE, &DRM_info);

        }
        else
        {
            printf("Gen DRM key fail\n");
        }
        return TRUE;
    }

    return FALSE;
}

#if 0
void MApp_VDPlayer_OperateDRMData(EN_DRM_OP_MODE eMode, VDplayerDRMInfo *pDRM_info)
{

    switch(eMode)
    {
        case E_DRM_INIT:
            {
                VDplayerDRMInfo DRM_info;
                memset(&DRM_info, 0, sizeof(VDplayerDRMInfo));

                MApp_WriteDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) &DRM_info, sizeof(VDplayerDRMInfo));
            }
            break;

        case E_DRM_SAVE:
            MApp_WriteDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) pDRM_info, sizeof(VDplayerDRMInfo));
            break;

        case E_DRM_LOAD:
            MApp_ReadDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) pDRM_info, sizeof(VDplayerDRMInfo));
            break;

        case E_DRM_CLEAR_MEMORY:
            {
                VDplayerDRMInfo DRM_info;
                U8 i;
                MApp_ReadDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) &DRM_info, sizeof(VDplayerDRMInfo));

                for(i = 0; i<DIVX_KEY_LEN; i++)
                    DRM_info.u8DRM_Data[i] = 0;
                MApp_WriteDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) &DRM_info, sizeof(VDplayerDRMInfo));
            }
            break;

        case E_DRM_CLEAR_MEMORY_DEMO:
            {
                VDplayerDRMInfo DRM_info;
                U8 i;
                MApp_ReadDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) &DRM_info, sizeof(VDplayerDRMInfo));

                for(i = 0; i<DIVX_KEY_LEN; i++)
                    DRM_info.u8DRM_Data[i] = 0;

                //RegCode: TA5WB362
                DRM_info.u8DRM_Data[0] = 0x5A;
                DRM_info.u8DRM_Data[1] = 0x48;
                DRM_info.u8DRM_Data[2] = 0xD1;
                MApp_WriteDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) &DRM_info, sizeof(VDplayerDRMInfo));
            }
            break;

        default:
            printf("[MApp_VDPlayer_OperateDRMData]Error\n");
            break;

    }
    /*
    if(eMode==E_DRM_INIT)
    {
        VDplayerDRMInfo DRM_info;

        memset(&DRM_info, 0, sizeof(VDplayerDRMInfo));
        MApp_WriteDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) &DRM_info, sizeof(VDplayerDRMInfo));

        return;
    }

    if(eMode==E_DRM_SAVE)
    {
        MApp_WriteDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) pDRM_info, sizeof(VDplayerDRMInfo));
    }
    else if(eMode==E_DRM_LOAD)
    {
        MApp_ReadDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) pDRM_info, sizeof(VDplayerDRMInfo));
    }
    else if(eMode==E_DRM_CLEAR_MEMORY)
    {
        VDplayerDRMInfo DRM_info;
        U8 i;

        MApp_ReadDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) &DRM_info, sizeof(VDplayerDRMInfo));

        for(i = 0; i<DIVX_KEY_LEN; i++)
            DRM_info.u8DRM_Data[i] = 0;

        MApp_WriteDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) &DRM_info, sizeof(VDplayerDRMInfo));
    }
    else if(eMode==E_DRM_CLEAR_MEMORY_DEMO)
    {
        VDplayerDRMInfo DRM_info;
        U8 i;

        MApp_ReadDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) &DRM_info, sizeof(VDplayerDRMInfo));

        for(i = 0; i<DIVX_KEY_LEN; i++)
            DRM_info.u8DRM_Data[i] = 0;

        //RegCode: TA5WB362
        DRM_info.u8DRM_Data[0] = 0x5A;
        DRM_info.u8DRM_Data[1] = 0x48;
        DRM_info.u8DRM_Data[2] = 0xD1;

        MApp_WriteDatabase(RM_DIVX_DRM_KEY_ADDR, (BYTE *) &DRM_info, sizeof(VDplayerDRMInfo));
    }
    */
}
#endif

BOOLEAN MApp_VDPlayer_ClearDRMMemory(void)
{
    U32 i;

    for (i = 0; i < 48; i++)
    {
//        stGenSetting.g_u8DRMMemory[i] = 0;
          stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[i] = 0;
    }
    MApp_SaveGenSetting();

    return TRUE;
}

BOOLEAN MApp_VDPlayer_LoadDRMMemory(void)
{
    U32 i;

    for (i = 0; i < 48; i++)
    {
        // VDPLAYER_DBG(printf("\n MApp_VDPlayer_LoadDRMMemory   stGenSetting.g_u8DRMMemory[i]=%d", stGenSetting.g_u8DRMMemory[i]));
        // _MApp_VDPlayer_SetShareMemoryDataByByte((E_SHAREMEM_DRM_BUFF_ADDR * 4 + i), stGenSetting.g_u8DRMMemory[i]);
        VDPLAYER_DBG(printf("\n MApp_VDPlayer_LoadDRMMemory   stGenSetting.g_u8DRMMemory[i]=%d", stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[i]));
        _MApp_VDPlayer_SetShareMemoryDataByByte((E_SHAREMEM_DRM_BUFF_ADDR * 4 + i), stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[i]);
    }

    return TRUE;
}

BOOLEAN MApp_VDPlayer_LoadVISUALDRMMemory(void)
{
    U32 i;

    for (i = 0; i < DIVX_KEY_LEN; i++)
    {
        _MApp_VDPlayer_SetShareMemoryDataByByte((E_SHAREMEM_DRM_BUFF_ADDR * 4 + i), u8DRM_LastData[i]);
    }

#if 0
    printf("Load DRM memory\r\n");
    for (i=0; i<48; i++)
    {
        if((i != 0) && (i % 16 == 0))
            printf("\r\n");

//        printf("%bx ", *(U8 *)(memory+i));
        printf("%02x ", stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[i]);
    }
    printf("\r\n");
#endif

    return TRUE;
}

BOOLEAN MApp_VDPlayer_SaveDRMMemory(void)
{
    U32 i;

    for (i = 0; i < 48; i++)
    {
//        stGenSetting.g_u8DRMMemory[i] = _MApp_VDPlayer_GetShareMemoryDataByByte((E_SHAREMEM_DRM_BUFF_ADDR * 4 + i));
//        VDPLAYER_DBG(printf("\n MApp_VDPlayer_SaveDRMMemory   stGenSetting.g_u8DRMMemory[i]=%d", stGenSetting.g_u8DRMMemory[i]));
        stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[i] = _MApp_VDPlayer_GetShareMemoryDataByByte((E_SHAREMEM_DRM_BUFF_ADDR * 4 + i));
        VDPLAYER_DBG(printf("\n MApp_VDPlayer_SaveDRMMemory   stGenSetting.g_u8DRMMemory[i]=%d", stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[i]));
    }

//    MApp_SaveGenSetting();
    MApp_SaveDrmSetting();

    return TRUE;
}

BOOLEAN MApp_VDPlayer_SaveVISUALDRMMemory(void)
{
    U32 i;
    for (i = 0; i < 48; i++)
    {
        u8DRM_LastData[i] = stGenSetting.g_VDplayerDRMInfo.u8DRM_Data[i];
    }

    return TRUE;
}

#if(!ENABLE_HK_DRM_GENCODE)
BOOLEAN MApp_VDPlayer_GetDRMRegistrationCode(U32 drmCodeAddr)
{
    extern U16 u16DRMModelID;
    U32 u32DrmTimout = 0;
    U8 u8Random[4]={0};
    U8 i;
    u32VdplayerShareMemAddr = VDPLAYER_SHAREMEM_ADDR;
    U32 u32SysTime = msAPI_Timer_GetTime0();

    MApp_VDPlayer_Mysrand(u32SysTime);
    for(i=0; i<4; i++)
    {
        u8Random[i]=(U8)MApp_VDPlayer_Myrand();
    }

#if( VD_PLAYER_IS_IN_CROP_CPU )
    MApp_VDPlayer_LoadBinToCrop();
#endif

    MApp_VDPlayer_LoadDRMMemory();

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_GET_DRM_REG_CODE;
    msAPI_Timer_Delayms(50); //for gen divX code UI
    bDrmRegCode = FALSE;

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_GET_DRM_REG_CODE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  , 10
    /*p1*/              ,GetByte3(u32VdplayerShareMemAddr)
    /*p2*/              ,GetByte2(u32VdplayerShareMemAddr)
    /*p3*/              ,GetByte1(u32VdplayerShareMemAddr)
    /*p4*/              ,GetByte0(u32VdplayerShareMemAddr)
    /*p5*/              ,u8Random[3]
    /*p6*/              ,u8Random[2]
    /*p7*/              ,u8Random[1]
    /*p8*/              ,u8Random[0]
    /*p9*/              ,GetByte0(u16DRMModelID)
    /*p10*/             ,GetByte1(u16DRMModelID));

    // Waiting for Aeon Video Player Ack
    u32DrmTimout = msAPI_Timer_GetTime0();

    do
    {
        MApp_VDPlayer_MailBoxHandler();
    } while ((m_eVDPlayerAckFlags & E_ACKFLG_WAIT_GET_DRM_REG_CODE) &&
                (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) < VDPLAYER_COPROCESSOR_CHECK_TIMEOUT));

    if (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) > VDPLAYER_COPROCESSOR_CHECK_TIMEOUT)
    {
        bDrmRegCode = FALSE;

        VDPLAYER_DBG(printf("Get DRM Registeration Code Timeout\r\n"));

        return bDrmRegCode;
    }

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_GET_DRM_REG_CODE_2;

    //second time
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_GET_DRM_REG_CODE_2
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    u32DrmTimout = msAPI_Timer_GetTime0();

    do
    {
        MApp_VDPlayer_MailBoxHandler();
    } while ((m_eVDPlayerAckFlags & E_ACKFLG_WAIT_GET_DRM_REG_CODE_2) &&
                (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) < VDPLAYER_COPROCESSOR_CHECK_TIMEOUT));

    if (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) > VDPLAYER_COPROCESSOR_CHECK_TIMEOUT)
    {
        bDrmRegCode = FALSE;

        VDPLAYER_DBG(printf("Get DRM Registeration Code Timeout\r\n"));

        return bDrmRegCode;
    }

    *((char *) drmCodeAddr)     = g_DRMRegCode[0];
    *((char *) drmCodeAddr + 1) = g_DRMRegCode[1];
    *((char *) drmCodeAddr + 2) = g_DRMRegCode[2];
    *((char *) drmCodeAddr + 3) = g_DRMRegCode[3];
    *((char *) drmCodeAddr + 4) = g_DRMRegCode[4];
    *((char *) drmCodeAddr + 5) = g_DRMRegCode[5];
    *((char *) drmCodeAddr + 6) = g_DRMRegCode[6];
    *((char *) drmCodeAddr + 7) = g_DRMRegCode[7];
    *((char *) drmCodeAddr + 8) = g_DRMRegCode[8];
    *((char *) drmCodeAddr + 9) = g_DRMRegCode[9];

    VDPLAYER_DBG(printf("\n g_DRMRegCode=%d ", g_DRMRegCode[0]));
    VDPLAYER_DBG(printf("\n g_DRMRegCode=%d ", g_DRMRegCode[1]));
    VDPLAYER_DBG(printf("\n g_DRMRegCode=%d ", g_DRMRegCode[2]));
    VDPLAYER_DBG(printf("\n g_DRMRegCode=%d ", g_DRMRegCode[3]));
    VDPLAYER_DBG(printf("\n g_DRMRegCode=%d ", g_DRMRegCode[4]));
    VDPLAYER_DBG(printf("\n g_DRMRegCode=%d ", g_DRMRegCode[5]));
    VDPLAYER_DBG(printf("\n g_DRMRegCode=%d ", g_DRMRegCode[6]));
    VDPLAYER_DBG(printf("\n g_DRMRegCode=%d ", g_DRMRegCode[7]));
    VDPLAYER_DBG(printf("\n g_DRMRegCode=%d ", g_DRMRegCode[8]));
    VDPLAYER_DBG(printf("\n g_DRMRegCode=%d ", g_DRMRegCode[9]));

    MApp_VDPlayer_SaveDRMMemory();

    bDrmRegCode = TRUE;
    g_bIsResumePlay = FALSE;

    return bDrmRegCode;
}

BOOLEAN MApp_VDPlayer_GetDRMDeactivationCode(U32 drmCodeAddr)
{
    U32 u32DrmTimout = 0;
    U32 u32SysTime = msAPI_Timer_GetTime0();

    u32VdplayerShareMemAddr = VDPLAYER_SHAREMEM_ADDR;

#if( VD_PLAYER_IS_IN_CROP_CPU )
    MApp_VDPlayer_LoadBinToCrop();
#endif

    msAPI_Timer_Delayms(50);

    MApp_VDPlayer_LoadDRMMemory();

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_GET_DRM_DEACTIVATION_CODE;

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_GET_DRM_DEACTIVATION_CODE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,8
    /*p1*/              ,GetByte3(u32VdplayerShareMemAddr)
    /*p2*/              ,GetByte2(u32VdplayerShareMemAddr)
    /*p3*/              ,GetByte1(u32VdplayerShareMemAddr)
    /*p4*/              ,GetByte0(u32VdplayerShareMemAddr)
    /*p5*/              ,GetByte3(u32SysTime)
    /*p6*/              ,GetByte2(u32SysTime)
    /*p7*/              ,GetByte1(u32SysTime)
    /*p8*/              ,GetByte0(u32SysTime)
    /*p9*/              ,0
    /*p10*/             ,0);

    u32DrmTimout = msAPI_Timer_GetTime0();

    do
    {
        MApp_VDPlayer_MailBoxHandler();
    } while ((m_eVDPlayerAckFlags & E_ACKFLG_WAIT_GET_DRM_DEACTIVATION_CODE) &&
                (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) < VDPLAYER_COPROCESSOR_CHECK_TIMEOUT));

    if (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) > VDPLAYER_COPROCESSOR_CHECK_TIMEOUT)
    {
        bDrmRegCode = FALSE;
        VDPLAYER_DBG(printf("Get DRM Registeration Code Timeout\r\n"));
        return bDrmRegCode;
    }

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_GET_DRM_DEACTIVATION_CODE;

    *((char *) drmCodeAddr)     = g_DRMDeactivationCode[0];
    *((char *) drmCodeAddr + 1) = g_DRMDeactivationCode[1];
    *((char *) drmCodeAddr + 2) = g_DRMDeactivationCode[2];
    *((char *) drmCodeAddr + 3) = g_DRMDeactivationCode[3];
    *((char *) drmCodeAddr + 4) = g_DRMDeactivationCode[4];
    *((char *) drmCodeAddr + 5) = g_DRMDeactivationCode[5];
    *((char *) drmCodeAddr + 6) = g_DRMDeactivationCode[6];
    *((char *) drmCodeAddr + 7) = g_DRMDeactivationCode[7];

    MApp_VDPlayer_SaveDRMMemory();

    bDrmRegCode = TRUE;
    g_bIsResumePlay = FALSE;
    return bDrmRegCode;
}
#endif //(!ENABLE_HK_DRM_GENCODE)

BOOLEAN MApp_VDPlayer_CheckDRMFileFormat(void)
{
    U32 u32DrmTimout = 0;

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION;
    bDrmFileFormat = FALSE;

    //Co-Command with MB_VDPLAYER_CHECK_DRM_AUTHORIZATION
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_CHECK_DRM_AUTHORIZATION
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    // Waiting for Aeon Video Player Ack

    u32DrmTimout = msAPI_Timer_GetTime0();
    do
    {
        MApp_VDPlayer_MailBoxHandler();
    } while ((m_eVDPlayerAckFlags & E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION) &&
                (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) < VDPLAYER_COPROCESSOR_CHECK_TIMEOUT));

    return bDrmFileFormat;
}

BOOLEAN MApp_VDPlayer_CheckDRMActivationFile(void)
{
    U32 u32DrmTimout = 0;

    VDPLAYER_DBG(printf("MApp_VDPlayer_CheckDRMActivationFile\n"));

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION;
    bDrmActivationFile = FALSE;

    // Co-Command with MB_VDPLAYER_CHECK_DRM_AUTHORIZATION
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_CHECK_DRM_AUTHORIZATION
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    // Waiting for Aeon Video Player Ack
    u32DrmTimout = msAPI_Timer_GetTime0();

    do
    {
        MApp_VDPlayer_MailBoxHandler();
    } while ((m_eVDPlayerAckFlags & E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION) &&
                (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) < VDPLAYER_COPROCESSOR_CHECK_TIMEOUT));

    return bDrmActivationFile;
}

BOOLEAN MApp_VDPlayer_CheckDRMAutuorization(void)
{
    U32 u32DrmTimout = 0;

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION;
    bDrmAuthorization = FALSE;

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_CHECK_DRM_AUTHORIZATION
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    // Waiting for Aeon Video Player Ack
    u32DrmTimout = msAPI_Timer_GetTime0();

    do
    {
        MApp_VDPlayer_MailBoxHandler();
    } while ((m_eVDPlayerAckFlags & E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION) &&
                (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) < VDPLAYER_COPROCESSOR_CHECK_TIMEOUT));

    return bDrmAuthorization;
}

BOOLEAN MApp_VDPlayer_QueryDRMRentalStatus(BOOLEAN *isRental, U8 *useLimit, U8 *useCount)
{
    U32 u32DrmTimout = 0;

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_QUERY_DRM_RENTAL_STATUS;
    bDrmRentalStatus = FALSE;

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_QUERY_DRM_RENTAL_STATUS
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    // Waiting for Aeon Video Player Ack
    u32DrmTimout = msAPI_Timer_GetTime0();

    do
    {
        MApp_VDPlayer_MailBoxHandler();
    } while ((m_eVDPlayerAckFlags & E_ACKFLG_WAIT_QUERY_DRM_RENTAL_STATUS) &&
                (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) < VDPLAYER_COPROCESSOR_CHECK_TIMEOUT));

    *isRental = g_bDrmRental;
    *useLimit = g_u8DrmUseLimit;
    *useCount = g_u8DrmUseCount;

    return bDrmRentalStatus;
}
#endif  // #if (ENABLE_DRM)


//-------------------------------------------------------------------------------------------------
///
/// WMDRMPD functions
///
///
//-------------------------------------------------------------------------------------------------

BOOLEAN MApp_VDPlayer_WMDRMPD_SavePrivate(U8 *pu8Private, U32 u32Size)
{
    if (u32Size > 32)
        u32Size = 32;

    memcpy(&g_WMDRMPrivate[0], pu8Private, u32Size);
    g_WMDRMPrivateReady = TRUE;

    return TRUE;
}

void MApp_VDPlayer_WMDRMPD_LoadPrivate(void)
{
    U8 *pu8Dst;
    U32 i;

    pu8Dst = (U8*)_PA2VA(VDPLAYER_SHAREMEM_ADDR);
    pu8Dst += E_SHAREMEM_DRM_BUFF_ADDR * 4;

    for (i = 0; i < 32; i++)
    {
        *(pu8Dst + i) = g_WMDRMPrivate[i];
    }
    //MsOS_Sync();
    MsOS_FlushMemory();
    g_WMDRMPrivateReady = FALSE;

    return;
}

#if ENABLE_WMDRMPD

BOOLEAN MApp_VDPlayer_WMDRMPD_QueryShareMemoryAddr(U32 *u32Addr)
{
    *u32Addr = 0x0;

    if (!u32WMDRMPDShareMemAddr)
        return FALSE;

    *u32Addr = u32WMDRMPDShareMemAddr;
    return TRUE;
}

BOOLEAN MApp_VDPlayer_WMDRMPD_IsProtected()
{
    if (!u32WMDRMPDShareMemAddr)
        return FALSE;
    else
    {
        U32 *ptr = (U32 *)u32WMDRMPDShareMemAddr;
        U32 u32TagCount;
        U32 size;
        U32 i;

        if (*ptr != WMDRMPD_SHAREMEM_HEADER)
            return FALSE;

        u32TagCount = *(ptr + 1);
        ptr += 2;

        for (i = 0; i < u32TagCount; i++)
        {
            if (*ptr == WMDRMPD_SHAREMEM_TAG_PROTECTED)
            {
                VDPLAYER_DBG(printf("WMDRMPD protected flag\n"));
                return (BOOLEAN)(*(ptr + 1));
            }
            size = *(ptr + 1);
            ptr += ((size + 0x3) >> 2) + 2;
        }

        return FALSE;
    }
}

BOOLEAN MApp_VDPlayer_WMDRMPD_QueryHeader(U32 *u32Addr, U32 *u32Size)
{
    *u32Addr = 0;
    *u32Size = 0;

    if (!u32WMDRMPDShareMemAddr)
        return FALSE;
    else
    {
        U32 *ptr = (U32 *)u32WMDRMPDShareMemAddr;
        U32 u32TagCount;
        U32 size;
        U32 i;

        if (*ptr != WMDRMPD_SHAREMEM_HEADER)
            return FALSE;

        u32TagCount = *(ptr + 1);
        ptr += 2;

        for (i = 0; i < u32TagCount; i++)
        {
            if (*ptr == WMDRMPD_SHAREMEM_TAG_PROTECTED_HEADER)
            {
                VDPLAYER_DBG(printf("WMDRMPD protected header\n"));
                *u32Addr = (U32)(ptr + 2);
                *u32Size = *(ptr + 1);
                return TRUE;
            }
            size = *(ptr + 1);
            ptr += ((size + 0x3) >> 2) + 2;
        }

        return FALSE;
    }
}

BOOLEAN MApp_VDPlayer_WMDRMPD_GetLicense(void)
{
    U32 u32Addr, u32Size;
    U8 retry = 0;

    if (MApp_VDPlayer_WMDRMPD_QueryHeader(&u32Addr, &u32Size))
    {
        if (MApp_WMDRMPD_Initialize(E_WMDRMPD_MEDIA_TYPE_WMV))
        {
            switch (MApp_WMDRMPD_GetLicense((void *)u32Addr, (int)u32Size))
            {
                case E_WMDRMPD_LICENSE_OK:
                    break;
                case E_WMDRMPD_LICENSE_RETRY:
                    retry = 1;
                    break;
                case E_WMDRMPD_LICENSE_INVALID:
                    return FALSE;
            }
        }
        else
        {
            return FALSE;
        }

        if (retry)
        {
            int sizeXML, sizeUrl;
            char url[128];
            void *pXML = NULL;
            void *pUrl = (void *)&url[0];
            //U32 u32DrmTimout = 0;

            // Send LicenseChallengeReq to network module
            MApp_WMDRMPD_QueryLicenseChallenge(&sizeXML, &sizeUrl);
            MApp_WMDRMPD_GetLicenseChallenge(pXML, pUrl, sizeXML, sizeUrl);

        #if 0
            if (msAPI_MailBox_WaitReady())
            {
                MailBoxPara.u8CmdClass      = MB_CLASS_VDPLAYER_FS;
                MailBoxPara.u8CmdIdx        = MB_VDPLAYER_CHECK_DRM_AUTHORIZATION;
                MailBoxPara.ParamCnt        = 0;
                MailBoxPara.CMDType         = MB_CMD_TYPE_DEFAULT;
                msAPI_MailBox_SendMsg();
            }

            // Waiting for Ack from network module
            u32DrmTimout = msAPI_Timer_GetTime0();
            bDrmAuthorization = FALSE;

            do
            {
                MApp_VDPlayer_MailBoxHandler();
            } while ((m_eVDPlayerAckFlags & E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION) &&
                        (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) < VDPLAYER_COPROCESSOR_CHECK_TIMEOUT));
        #endif

            MApp_WMDRMPD_SetLicenseResponse(pXML, sizeXML);
            switch (MApp_WMDRMPD_GetLicense((void *)pXML, sizeXML))
            {
                case E_WMDRMPD_LICENSE_OK:
                    break;
                case E_WMDRMPD_LICENSE_RETRY:
                    return FALSE;
                case E_WMDRMPD_LICENSE_INVALID:
                    return FALSE;
            }
        }
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

#endif

BOOLEAN MApp_VDPlayer_SetSubtitleShow( EN_SUBTITLE_STATE_COMMAND setting)
{
    if( u8IsSubtitleBusy ==FALSE)
    {
#if (TS_INTERNAL_SUBTITLE_BMP)
        if(u32subtitletype== E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
        {
            BMP_DBG(printf("@@BMP MApp_VDPlayer_SetSubtitleShow\n"));
            switch( setting )
            {
                case    E_SUBTITLE_STATE_COMMAND_SHOW:
                case    E_SUBTITLE_STATE_COMMAND_ENABLE_ALL_SUBTITLE:
                case    E_SUBTITLE_STATE_COMMAND_ENABLE_PICT_SUBTITLE:
                case    E_SUBTITLE_STATE_COMMAND_ENABLE_TEXT_SUBTITLE:
                    _bSubtitleShow_User = ENABLE;
                    break;

                case    E_SUBTITLE_STATE_COMMAND_NOT_SHOW:
                case    E_SUBTITLE_STATE_COMMAND_DISABLE_ALL_SUBTITLE:
                    _bSubtitleShow_User = DISABLE;
                    break;

                default:
                    break;
            }

            u8InternalST_Num =_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_SUBTITLE);

            if(!(_bSubtitleShow_MW && _bSubtitleShow_User && (u8InternalST_Num>0)))
            {
                MApp_VDPlayer_TS_SubtitleErase();
            }
        }
    #endif
#if (TS_INTERNAL_SUBTITLE_PGS)
       if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
       {
            PGS_DBG(printf("@@PGS MApp_VDPlayer_SetSubtitleShow\n"));
            switch( setting )
            {
                case    E_SUBTITLE_STATE_COMMAND_SHOW:
                case    E_SUBTITLE_STATE_COMMAND_ENABLE_ALL_SUBTITLE:
                case    E_SUBTITLE_STATE_COMMAND_ENABLE_PICT_SUBTITLE:
                case    E_SUBTITLE_STATE_COMMAND_ENABLE_TEXT_SUBTITLE:
                    _bSubtitleShow_User = ENABLE;
                    break;

                case    E_SUBTITLE_STATE_COMMAND_NOT_SHOW:
                case    E_SUBTITLE_STATE_COMMAND_DISABLE_ALL_SUBTITLE:
                    _bSubtitleShow_User = DISABLE;
                    break;

                default:
                    break;
            }

            u8InternalST_Num =_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_SUBTITLE);

            if(!(_bSubtitleShow_MW && _bSubtitleShow_User && (u8InternalST_Num>0)))
            {
                MApp_VDPlayer_TS_SubtitleErase();
            }
       }
#endif
        if( u8IsSubtitleInitfinish == TRUE )
        {
            //==> Send mail.
            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
            /*Index*/           ,MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW
            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
            /*ParameterCount*/  ,1
            /*p1*/              ,(U8)setting
            /*p2*/              ,0
            /*p3*/              ,0
            /*p4*/              ,0
            /*p5*/              ,0
            /*p6*/              ,0
            /*p7*/              ,0
            /*p8*/              ,0
            /*p9*/              ,0
            /*p10*/             ,0);
            return TRUE;
        }
        else
        {
            switch( setting )
            {
                case    E_SUBTITLE_STATE_COMMAND_NOT_SHOW:
                case    E_SUBTITLE_STATE_COMMAND_SHOW:
                case    E_SUBTITLE_STATE_COMMAND_ENABLE_ALL_SUBTITLE:
                case    E_SUBTITLE_STATE_COMMAND_ENABLE_PICT_SUBTITLE:
                case    E_SUBTITLE_STATE_COMMAND_ENABLE_TEXT_SUBTITLE:
                case    E_SUBTITLE_STATE_COMMAND_DISABLE_ALL_SUBTITLE:
                case    E_SUBTITLE_STATE_COMMAND_DISABLE_TS_SUBTITLE:
                    //==> Send mail.
                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
                    /*Index*/           ,MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW
                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                    /*ParameterCount*/  ,1
                    /*p1*/              ,(U8)setting
                    /*p2*/              ,0
                    /*p3*/              ,0
                    /*p4*/              ,0
                    /*p5*/              ,0
                    /*p6*/              ,0
                    /*p7*/              ,0
                    /*p8*/              ,0
                    /*p9*/              ,0
                    /*p10*/             ,0);
                    return TRUE;
                    break;
                default:
                    break;
            }
        }
    }
    return FALSE;
}

#if ENABLE_SUBTITLE_DMP
//-------------------------------------------------------------------------------------------------
///
/// Subtitle functions
///
///
//-------------------------------------------------------------------------------------------------
void MApp_VDPlayer_GetSubtitleSettings( U8 *nowtrack , U8 *nbtrack)
{
    *nowtrack= (U8)_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TRACK_ID);//((u16GetSubtitleSettingsBuf&0xFF00)>>8);//msAPI_VDPlayer_GetShareMemoryDataInfo(SHAREMEMORY_MCU_CURRENT_SUBTITLE_TRACK_ID);
    *nbtrack= (U8)_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_SUBTITLE);//(u16GetSubtitleSettingsBuf&0xFF);//msAPI_VDPlayer_GetShareMemoryDataInfo(SHAREMEMORY_MCU_TOTAL_SUBTITLE);
}

// Useless
#if 0
void MApp_VDPlayer_GetSubtitleState( U8 *Isshow , U8 *IsExternal)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_GET_SUBTITLE_STATE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_GET_SUBTITLE_STATE;
    do
    {
        MApp_VDPlayer_MailBoxHandler();
    }
    while(m_eVDPlayerAckFlags&E_ACKFLG_WAIT_GET_SUBTITLE_STATE);
    *Isshow = (U8)( (u32GetSubtitleStateBuf&0xFF0000)>>16 );
    switch(u32GetSubtitleStateBuf&0xFFFF)
    {
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT :
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA :
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF :
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
            if(u8IsFontTableReady)
            {
                *IsExternal=FALSE;
            }
            else
#endif
            {
                *IsExternal=TRUE;
            }
            break;
        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_KATE:
        default:
            *IsExternal=FALSE;
            break;
    }
}
#endif

U32 MApp_VDPlayer_GetSubtitleInfo(EN_SUBTITLE_INFO eInfo)
{
    switch(eInfo)
    {
    case E_SUBTITLE_INFO_NB_TRACK:
        return (U32)_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_SUBTITLE);

    case E_SUBTITLE_INFO_TRACK_ID:
        return (U32)_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TRACK_ID);

    case E_SUBTITLE_INFO_TYPE:
        return (U32)u32subtitletype;

    default:
        break;
    }
    return 0;
}

void MApp_VDPlayer_ShowTSSubtitle(BOOLEAN bEnable)
{
#if (TS_INTERNAL_SUBTITLE_BMP || TS_INTERNAL_SUBTITLE_PGS)

    _bSubtitleShow_User = bEnable;
    _bSubtitleShow_MW = bEnable;
    if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
    {
        if(!_bSubtitleShow_User)
        {
            MApp_VDPlayer_TS_SubtitleErase();
        }
        else
        {
            MApp_TS_Subtitle_Remove();
        }
    }

    if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
    {
        if(!_bSubtitleShow_User)
        {
            MApp_VDPlayer_TS_SubtitleErase();
        }
        else
        {
            MApp_TS_Subtitle_Remove();
        }
    }
#else
    UNUSED(bEnable);
#endif
}

void MApp_VDPlayer_TS_SubtitleErase(void)
{
#if (TS_INTERNAL_SUBTITLE_BMP)
    /// if subtitle on, clear GWIN buffer of GOP.
    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
    {
        BMP_DBG(printf("@@BMP SubtitleErase\n"));
        if(MApp_TS_Subtitle_Get_SubtitleOSDState())
        {
            MApp_TS_Subtitle_Switch2IP();
            MApp_TS_Subtitle_Exit();       // clear old track subtitle
            MApp_TS_Subtitle_Switch2OP();
        }
    }
#endif

#if (TS_INTERNAL_SUBTITLE_PGS)
    /// if subtitle on, clear GWIN buffer of GOP.
    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
    {
        PGS_DBG(printf("@@PGS SubtitleErase\n"));
        if(MApp_TS_Subtitle_Get_SubtitleOSDState())
        {
            MApp_TS_Subtitle_Switch2IP();
            MApp_TS_Subtitle_Exit();       // clear old track subtitle
            MApp_TS_Subtitle_Switch2OP();
        }
    }
#endif

}
void MApp_VDPlayer_SubtitleDraw(void)
{

#if (ENABLE_INTERNAL_SUBTITLE)
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
    U32 t = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
#endif
    U32 u32Stc = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_SYSTEM_CLOCK_REFERENCE);
#endif

    if (u8IssubtitleInit == TRUE && u32subtitletype != 0)
    {
        switch (u32subtitletype)
        {
            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
              #if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, MAX_SPU_QUEUE_SIZE - msAPI_MpegSP_SpuQueue_GetCount());
              #else
                _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, 0);
              #endif

            #if ENABLE_DVD
                if (bIsDVD)
                {
                  #if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                    if (MApp_DVD_IsPredecodeDone())
                        msAPI_MpegSP_Main(t * 90);
                  #endif
                }
                else
            #endif
              #if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                msAPI_MpegSP_Main(u32Stc);
              #endif
                break;

            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS:
#if (TS_INTERNAL_SUBTITLE_BMP)
                if ((u8IssubtitleInit == TRUE) && _bSubtitleShow_User && _bSubtitleShow_MW)
                {
                    if(u8InternalST_Num>0)
                    {
                            MApp_TS_Subtitle_Main(u32Stc);
                    }
                }
#endif
                break;

                case E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS:
#if (TS_INTERNAL_SUBTITLE_PGS)
                if ((u8IssubtitleInit == TRUE) && _bSubtitleShow_User && _bSubtitleShow_MW)
                {
                    if(u8InternalST_Num>0)
                    {
                             MApp_TS_Subtitle_Main(u32Stc);
                        }
                    }
                }
#endif
                break;

            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
              #if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, MAX_SPU_QUEUE_SIZE - msAPI_MpegSP_SpuQueue_GetCount());
                msAPI_MpegSP_Main(t);
              #else
                _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, 0);
              #endif
                break;

        #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                if(u8IsFontTableReady)
                {
                  #if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, MAX_SPU_QUEUE_SIZE - msAPI_MpegSP_SpuQueue_GetCount());
                    msAPI_MpegSP_Main(t);
                  #else
                    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, 0);
                  #endif
                }
                break;
        #endif

            default:
                //_Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_QUEUE_CNT, TRUE );
                break;
        }
    }
}

BOOL MApp_VDPlayer_SubtitleTimeShift(BOOL bDirection, U16 u16TimeShift)
{
    U32 m_u32PlayTimer;

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_SUBTITLE_TIMESHIFT;
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_SUBTITLE_TIMESHIFT
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,3
    /*p1*/              ,bDirection
    /*p2*/              ,(U8)(u16TimeShift>>8)
    /*p3*/              ,(U8)u16TimeShift
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    m_u32PlayTimer = msAPI_Timer_GetTime0();
    while(m_eVDPlayerAckFlags & E_ACKFLG_WAIT_SUBTITLE_TIMESHIFT)
    {
       if (msAPI_Timer_DiffTimeFromNow(m_u32PlayTimer) > 5000)
       {
           return FALSE;
       }

       MApp_VDPlayer_MailBoxHandler();
    }
    return TRUE;

}

void MApp_VDPlayer_TextSubtitleInit(void)
{
    u16tagposition=0;
    u16SubtitleTagCnt=0;
    m_s32PreSubtitleTagIdx = -1;
    m_u32PreMovieRefreshTextTimer=0;
}

//******************************************************************************
/// Refresh internal text subtitle tag queue, skip expired tags.
/// @param  u32Time \b IN  Specify the time in milliseconds.
/// @return void
//******************************************************************************
void MApp_VDPlayer_RefreshTextSubtitleTag(U32 u32Time)
{
    U8 u8Count, u8SkipCnt=0;
    U16 u16TagIdx=0xFFFF, u16TagIdx2;
    U16 u16TempSubtitleTagCnt;
    MPlayer_Subtitle_Tag Tag;

    if(u16SubtitleTagCnt>0)
    {
        //u16tagposition is end of the ring queue.
        //u16SubtitleTagCnt is number of tags in ring queue.
        u16TagIdx = ((u16tagposition+MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT - u16SubtitleTagCnt)%MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT);

        //skip expired tags which have a larger start time than the next tag.
        if(u16SubtitleTagCnt>1)
        {
            for(u8Count=0; u8Count<u16SubtitleTagCnt-1; u8Count++)
            {
                u16TagIdx2 = (u16TagIdx+1)%MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT;

                if(m_astInternalTextSubtitleTag[u16TagIdx2].u32TimeStart
                 < m_astInternalTextSubtitleTag[u16TagIdx].u32TimeStart)
                {
                    u8SkipCnt = u8Count+1; //max skip count = u16SubtitleTagCnt-1
                }
                u16TagIdx = u16TagIdx2;
            }
            u16SubtitleTagCnt -= u8SkipCnt;
        }

        //senario: When queue is full and then rewind/jump backward, new tag from VDPlayer cannot push to queue.
        //solution: if queue is full and previous time > current time(after rewind/jump backward), will clear queue buffer
        if(u16SubtitleTagCnt >= MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT && m_u32PreMovieRefreshTextTimer > u32Time)
        {
            MApp_VDPlayer_TextSubtitleInit();
        }
        m_u32PreMovieRefreshTextTimer = u32Time;

        u16TagIdx = ((u16tagposition+MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT - u16SubtitleTagCnt)%MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT);
        u16TempSubtitleTagCnt = u16SubtitleTagCnt;

        //skip expired tags which have a smaller end time than current time.
        for(u8Count=0; u8Count<u16TempSubtitleTagCnt; u8Count++)
        {
            Tag = m_astInternalTextSubtitleTag[u16TagIdx];

            if(Tag.u32TimeEnd <= u32Time)
            {
                u16SubtitleTagCnt--;
            }
            else
            {
                break;
            }
            u16TagIdx = (u16TagIdx+1)%MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT;
        }
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT,(U32)(MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT-u16SubtitleTagCnt));
    }
}

//******************************************************************************
/// Get alive internal text subtitle tags.
/// @param  u32Time             \b IN  Specify the time in milliseconds.
/// @param  pu8AliveSubtitleNum \b OUT Return the number of alive internal text subtitle
/// @param  pAliveSubtitles     \b OUT Return the alive internal text subtitle tags.
/// @param  bSubtitleShownFLG   \b IN  Specify the text subtitle is shown or not.
/// @return number of alive internal text subtitle tags.
//******************************************************************************
BOOLEAN MApp_VDPlayer_GetAliveTextSubtitleTag(U32 u32Time, U8* pu8AliveSubtitleNum, MPlayer_Subtitle_Tag *pAliveSubtitles, BOOLEAN bSubtitleShownFLG)
{
    U8 u8Count, u8AliveSubtitleNum = 0;
    U16 u16TagIdx=0xFFFF;
    U16 u16CurSubtitleTagIdx=0xFFFF;
    MPlayer_Subtitle_Tag Tag;

    MApp_VDPlayer_RefreshTextSubtitleTag(u32Time);

    if(u16SubtitleTagCnt > 0)
    {
        //u16tagposition is end of the ring queue.
        //u16SubtitleTagCnt is number of tags in ring queue.
        u16TagIdx = ((u16tagposition+MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT - u16SubtitleTagCnt)%MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT);

        //find current tag.
        for(u8Count=0; u8Count<u16SubtitleTagCnt; u8Count++)
        {
            Tag = m_astInternalTextSubtitleTag[u16TagIdx];

            if(Tag.u32TimeStart <= u32Time)
            {
                u16CurSubtitleTagIdx = u16TagIdx;
            }
            else
            {
                if(u8Count==0)
                {
                    //Can not find the subtitle which time is less or equal to u32Time.
                    return FALSE;
                }
                break;
            }
            u16TagIdx = (u16TagIdx+1)%MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT;
        }

        if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_TEXT_SMI)
        {
            //SMI doesn't have end time stamp.
            //skip expired tags before current tag.
            u16SubtitleTagCnt -= (u8Count-1);
        }

        if(bSubtitleShownFLG)
        {
            if(m_s32PreSubtitleTagIdx == u16CurSubtitleTagIdx)
            {
                //if current tag is equal to previous tag, no need to refresh subtitle.
                return FALSE;
            }
        }
        m_s32PreSubtitleTagIdx = u16CurSubtitleTagIdx;

        if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_TEXT_SMI)
        {
            if(u16CurSubtitleTagIdx < MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT)
            {
                //SMI doesn't have end time stamp.
                //SMI can not support multiple subtitle.
                Tag = m_astInternalTextSubtitleTag[u16CurSubtitleTagIdx];
                pAliveSubtitles[0] = Tag;
                u8AliveSubtitleNum = 1;
            }
        }
        else
        {
            u16TagIdx = ((u16tagposition+MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT - u16SubtitleTagCnt)%MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT);

            //find alive internal text subtitle tags.
            for(u8Count=0; u8Count<u16SubtitleTagCnt; u8Count++)
            {
                Tag = m_astInternalTextSubtitleTag[u16TagIdx];

                if(Tag.u32TimeStart <= u32Time)
                {
                    if(Tag.u32TimeEnd > u32Time)
                    {
                        pAliveSubtitles[u8AliveSubtitleNum] = Tag;
                        u8AliveSubtitleNum++;

                        if(u8AliveSubtitleNum >= MAX_ALIVE_SUBTITLE_NUM)
                        {
                            break;
                        }
                    }
                }
                u16TagIdx = (u16TagIdx+1)%MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT;
            }
        }
    }

    *pu8AliveSubtitleNum = u8AliveSubtitleNum;

    if(*pu8AliveSubtitleNum)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

U16 MApp_VDPlayer_GetTextSubtitleTag(MPlayer_Subtitle_Tag *pTag,U32 u32Time)
{
    U16 u16TagIdx=0xFFFF;
    MPlayer_Subtitle_Tag Tag;

    if(u16SubtitleTagCnt>0)
    {
        u16TagIdx = ((u16tagposition+MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT - u16SubtitleTagCnt)%MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT);
    #if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
        Tag = m_astInternalTextSubtitleTag[u16TagIdx];
    #else
        Tag = *(MPlayer_Subtitle_Tag *)_PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+(U32)u16TagIdx*sizeof(MPlayer_Subtitle_Tag));
    #endif
        if(Tag.u32TimeStart <= u32Time)
        {
            u16SubtitleTagCnt--;

            *pTag = Tag;
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT,(U32)(MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT-u16SubtitleTagCnt));
        }
        else
        {
            u16TagIdx=0xFFFF;
        }
    }
    return u16TagIdx;
}


void _MApp_Parse_InternalASSSubtitle(U32 u32TextDataAddress, U16 u16Len)
{
    BOOLEAN bFound = FALSE;
    BOOLEAN bRet = FALSE;
    U8* pSrcAddr = (U8*)u32TextDataAddress;
    U8* pDstAddr = (U8*)u32TextDataAddress;
    U16 u16CacheParsed = 0;
    U16 u16NewPos = 0;

    for(;!bFound && (u16CacheParsed<u16Len);u16CacheParsed++)
    {
        switch(pSrcAddr[u16CacheParsed])
        {
        case '{':
            // Skip SSA instructions.
            for(;u16CacheParsed<u16Len;u16CacheParsed++)
            {
                if(pSrcAddr[u16CacheParsed] == '}')
                {
                    break;
                }
            }
            break;
            // if find \N, need add a Line Feed
        case '\\':
            {
                if(pSrcAddr[u16CacheParsed + 1] == 'N')
                {
                    pDstAddr[u16NewPos++] = 0x0D;
                    pDstAddr[u16NewPos++] = 0x0A;
                    u16CacheParsed ++;
                }
                else
                {
                    pDstAddr[u16NewPos++] = pSrcAddr[u16CacheParsed];
                }
            }
            break;
        case 0:
        case 0x0D:
        case 0x0A:
            // Fill 0 to the end of subtitle.
            pDstAddr[u16NewPos] = '\0';
            pDstAddr[u16NewPos+1] = '\0';
            u16CacheParsed++;
            bRet = TRUE;
            bFound = TRUE;
            break;
        default:
            pDstAddr[u16NewPos++] = pSrcAddr[u16CacheParsed];
            break;
        }
    }

    if( !bFound && (u16CacheParsed<u16Len - 2))
    {
        pDstAddr[u16NewPos] = '\0';
        pDstAddr[u16NewPos+1] = '\0';
    }

}

#if (ENABLE_INTERNAL_TEXT_SUBTITLE)
void msAPI_VDPlayer_SubtitleTextPushQueue(   U32 PTSstart  , U32 PTSend  , U32 addr )
{
    MPlayer_Subtitle_Tag *pTag;
    U32 u32SubtitleTagLeft;

    //Let Tag be stable after trick mode -> NPF
    if((u16SubtitleTagCnt == 1)&&(u16tagposition==1))
    {
    #if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
        pTag = &m_astInternalTextSubtitleTag[0];
    #else
        pTag = (MPlayer_Subtitle_Tag *)_PA2VA((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR));
    #endif
        if(pTag->u32TimeStart > PTSstart)
        {
            u16tagposition = 0;
            u16SubtitleTagCnt = 0;
        }
    }
    if(u16SubtitleTagCnt >= MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT)
    {
        u32SubtitleTagLeft = 0;
    }
    else
    {
    #if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
        pTag = &m_astInternalTextSubtitleTag[u16tagposition];
    #else
        pTag = (MPlayer_Subtitle_Tag *)_PA2VA(((MP4_SUBTITLE_TAG_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_TAG_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_TAG_ADR))+ (u16tagposition)*(sizeof(MPlayer_Subtitle_Tag)));
    #endif
        pTag->u32TimeStart = PTSstart ;
        pTag->u32TimeEnd = PTSend;
        pTag->u32SubtitlePos = addr -INTERNAL_TEXT_SUBTITLE_BUFFER_ADR; // ((U32)MAX_INTERNAL_TEXT_SUBTITLE_LEN)*((U32) (u16tagposition-1));
        if((u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS) ||
            (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA))
        {
            U32 u32VirAddr;
            U32 u32TextDataAddress;
            u32TextDataAddress = INTERNAL_TEXT_SUBTITLE_BUFFER_ADR+pTag->u32SubtitlePos;
            u32VirAddr = _PA2VA(u32TextDataAddress);

            _MApp_Parse_InternalASSSubtitle(u32VirAddr, SUBTITLE_MAX_SIZE);
        }

        u16tagposition++;
        u16SubtitleTagCnt++;
        u16tagposition%= MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT;
        u32SubtitleTagLeft = MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT-u16SubtitleTagCnt;
    }

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, u32SubtitleTagLeft);
    //printf("%d push %d --> %d u16tagposition %d, u16SubtitleTagCnt %d\n", MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME),PTSstart, PTSend,u16tagposition, u16SubtitleTagCnt);
}
#endif //#if (ENABLE_INTERNAL_TEXT_SUBTITLE)

#if (ENABLE_INTERNAL_SUBTITLE)
void msAPI_VDPlayer_SubtitlePushQueue(EN_VDP_CODECID sb_type, U32 adr, U32 len, U32 pts_start, U32 pts_end)
{
#if 0
    U32 i, j;
    U8 *u8Ptr = NULL;

    for(i = 0; i < len; i++)
    {
        u8Ptr = (U8 *) (adr + i);

        if (i % 8 == 0)
            printf("\r\n0x%08X: ", u8Ptr);

        printf("%02x", *u8Ptr);

        for (j = 0; j < 1; j++)
            printf (" ");
    }

    printf("\r\n");

    while (1) ;
#endif

    switch (sb_type)
    {
        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
        //divX
          #if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
            msAPI_MpegSP_SpuQueue_Push(sb_type, adr, (U16) len, 0, 0);
          #else
            len=0;
          #endif
            //printf(" sub-divx push queue:add%x len:%d\n" , adr  , len  );
            break;

        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
            pts_start *= 90;
          #if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
            msAPI_MpegSP_SpuQueue_Push(sb_type , adr, (U16) len, pts_start, 0);
          #endif
            //printf(" sub-vob push queue:add%x len:%d\n" , adr  , len  );
            break;

        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
        case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
            //printf(" [Aeon 51] text SubtitlePushQueue:   pts_start: 0x%lx ; pts_end: 0x%lx ;addr:0x%lx \n", pts_start , pts_end,adr);
            //printf(" text-vob push queue:add%x len:%d TrackNum:%d TextEnable:%d Uni:%d \n" , adr  , len , MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK), MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_TEXT), MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_ISUNICODE) );
#if (ENABLE_INTERNAL_TEXT_SUBTITLE)
          #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
            if(u8IsFontTableReady)
            {
              #if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                msAPI_MpegSP_SpuQueue_Push(sb_type , adr, (U16) len, pts_start, pts_end-pts_start);
              #endif
            }
            else
          #endif
            {
                msAPI_VDPlayer_SubtitleTextPushQueue(pts_start , pts_end , adr);
            }
#endif //#if (ENABLE_INTERNAL_TEXT_SUBTITLE)
            break;

        default:
            break;
    }

    return;
}
#endif //#if (ENABLE_INTERNAL_SUBTITLE)


BOOLEAN MApp_VDPlayer_SetSubtitleTrackID(U8 u8TrackId)
{
    U32 u32VDPlayer_init_timeout=VDPLAYER_INIT_TIMEOUT;

    if(u32subtitletype == 0)
    {
        return FALSE;
    }

    if(u8TrackId < MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK))
    {
        if( u8IsSubtitleBusy==FALSE)
        {
            // Is this flag necessary ?
            //u8IsSubtitleBusy=TRUE;
//            printf("[Aeon 51] subtitile set trackID: %d\n" , (U16)u8TrackId);
            //==> Send mail.
            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
            /*Index*/           ,MB_VDPLAYER_SET_SUBTITLE_TRACKID
            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
            /*ParameterCount*/  ,1
            /*p1*/              ,(U8)u8TrackId
            /*p2*/              ,0
            /*p3*/              ,0
            /*p4*/              ,0
            /*p5*/              ,0
            /*p6*/              ,0
            /*p7*/              ,0
            /*p8*/              ,0
            /*p9*/              ,0
            /*p10*/             ,0);

            u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
            m_eVDPlayerAckFlags=(m_eVDPlayerAckFlags|E_ACKFLG_WAIT_SET_SUBTITLE_TRACKID);

            do
            {
            #if (VDPLAYER_CHECK_PREVIEW_ABORT)
                if(_MApp_VDPlayer_CheckPreviewAbortKey())
                {
                    MApp_VDPlayer_Stop(); //fix preview next file it will show "un-support file" after abort(need to issue STOP CMD to co-processor)
                    // _MApp_VDPlayer_Exit();

                    // Return value to MPlayer, and abort the remaining process
                    bMovieAbort = TRUE;
                    return TRUE;
                }
            #endif
                VDPLAYER_DBG(printf("\n wait subtitle change coprocessor ack ing... "));
                MApp_VDPlayer_MailBoxHandler();
            }
            while((m_eVDPlayerAckFlags&E_ACKFLG_WAIT_SET_SUBTITLE_TRACKID) &&
                (msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)<u32VDPlayer_init_timeout));            //update share memory for ZUI subtitle track info refresh

            if(msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)>u32VDPlayer_init_timeout)
            {
                VDPLAYER_DVD_DBG(printf("ST: chg track time out\n"));
                Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_SUBTITLE_TRACKID);
            }

            //update share memory for ZUI subtitle track info refresh
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TRACK_ID, (U32)u8TrackId);

            return TRUE;
        }
        else
            return FALSE;
    }
    else
    {
        return FALSE;
    }
}
#endif //ENABLE_SUBTITLE_DMP

//-------------------------------------------------------------------------------------------------
///
/// APP functions
/// Processed by Aeon. Do not need to wait Ack message
///
//-------------------------------------------------------------------------------------------------
/*
void MApp_VDPlayer_Reset()
{
    if (msAPI_MailBox_WaitReady())
    {
        MailBoxPara.u8CmdClass      = MB_CLASS_VDPLAYER_FS;
        MailBoxPara.u8CmdIdx        = MB_VDPLAYER_RESET;
        MailBoxPara.ParamCnt        = 0;
        MailBoxPara.CMDType         = MB_CMD_TYPE_DEFAULT;
        msAPI_MailBox_SendMsg();
    }
}
*/

#if (0) //(ENABLE_MOVIE_PREVIEW)
void MApp_VDPlayer_StateInit(void)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_STATE_INIT
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}
#endif  // #if (ENABLE_MOVIE_PREVIEW)

static U8 MApp_VDPlayer_GetFreeFileHandleIdx(void)
{
    U8 u8Idx, u8CheckCnt = sizeof(bStrmHdlAssignTbl)/sizeof(bStrmHdlAssignTbl[0]);

    for (u8Idx = 0; u8Idx < u8CheckCnt; u8Idx++)
    {
        if (bStrmHdlAssignTbl[u8Idx] == FALSE)
        {
            if (u8Idx == 0)
            {
                bStrmHdlAssignTbl[u8Idx] = TRUE;
                return u8Idx;
            }
            else if (u8Idx == 1)
            {
                bStrmHdlAssignTbl[u8Idx] = TRUE;
                return u8Idx;
            }
#if ENABLE_NEW_FILE_HANDLER
            else if (u8Idx == 2)
            {
                bStrmHdlAssignTbl[u8Idx] = TRUE;
                return u8Idx;
            }
            else if (u8Idx == 3)
            {
                bStrmHdlAssignTbl[u8Idx] = TRUE;
                return u8Idx;
            }
#else //ENABLE_NEW_FILE_HANDLER
        #if ENABLE_AUDIO_HANDLER
            else if (u8Idx == AVHandlerCnt)
            {
                bStrmHdlAssignTbl[u8Idx] = TRUE;
                return u8Idx;
            }
        #endif
        #if ENABLE_ATTACHMENT_HANDLER
            else if (u8Idx == (AVHandlerCnt + AudioHandlerCnt))
            {
                bStrmHdlAssignTbl[u8Idx] = TRUE;
                return u8Idx;
            }
        #endif
#endif //ENABLE_NEW_FILE_HANDLER
        }
    }

    return INVALID_HANDLE_IDX;
}

static void MApp_VDPlayer_StrmHandleAssignTblInit(void)
{
    U8 u8Idx, u8Cnt = sizeof(bStrmHdlAssignTbl)/sizeof(bStrmHdlAssignTbl[0]);

    for (u8Idx = 0; u8Idx < u8Cnt; u8Idx++)
    {
        bStrmHdlAssignTbl[u8Idx] = FALSE;
    }
}

static void MApp_VDPlayer_ReleaseStrmHandleByIdx(U8 u8HdlIdx)
{
    if (u8HdlIdx >= (sizeof(bStrmHdlAssignTbl)/sizeof(bStrmHdlAssignTbl[0])))
    {
        return;
    }

    bStrmHdlAssignTbl[u8HdlIdx] = FALSE;
}

U32 MApp_VDPlayer_GetStrmHandleByIdx(U8 u8HdlIdx)
{
    switch (u8HdlIdx)
    {
#if ENABLE_NEW_FILE_HANDLER
        case 0:
        case 1:
        case 2:
        case 3:
            return u32StreamHandleIdx[u8HdlIdx];
        default:
            printf("Error, No free file handler. Need increase Total file handler\n");
            break;
#else //ENABLE_NEW_FILE_HANDLER
        case 0:
            return u32VDPlayerStreamHandleIdx_Video;

        case 1:
            return u32VDPlayerStreamHandleIdx_Subtitle;

    #if ENABLE_AUDIO_HANDLER
        case AVHandlerCnt:
            return u32VDPlayerStreamHandleIdx_Audio;
    #endif // #if ENABLE_AUDIO_HANDLER

    #if ENABLE_ATTACHMENT_HANDLER
        case (AVHandlerCnt + AudioHandlerCnt):
            return u32VDPlayerStreamHandleIdx_Attachment;
    #endif // #if ENABLE_ATTACHMENT_HANDLER

        default:
            break;
#endif //ENABLE_NEW_FILE_HANDLER
    }

    return INVALID_DATA_STREAM_HDL;
}

//-------------------------------------------------------------------------------------------------
///
/// APP functions
/// Processed by Aeon. And need to wait Ack message
///
//-------------------------------------------------------------------------------------------------
BOOLEAN MApp_VDPlayer_SetPlayPosition(U32 timeInMs, BOOL IsResumePlay)
{
#if ENABLE_DVD
    if (bIsDVD)
    {
        MApp_DVD_SetPlayPosition(timeInMs);
        return TRUE;
    }
#endif
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_SET_PLAYER_POSITION
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,8
    /*p1*/              ,(U8)((timeInMs&0xFF000000)>>24)
    /*p2*/              ,(U8)((timeInMs&0x00FF0000)>>16)
    /*p3*/              ,(U8)((timeInMs&0x0000FF00)>>8)
    /*p4*/              ,(U8)((timeInMs&0x000000FF))
    /*p5*/              ,0
    /*p6*/              ,IsResumePlay
    /*p7*/              ,(U8)((u32OrgDivPlusPTS&0xFF000000)>>24)
    /*p8*/              ,(U8)((u32OrgDivPlusPTS&0x00FF0000)>>16)
    /*p9*/              ,0
    /*p10*/             ,0);

    MApp_VDPlayer_TextSubtitleInit();
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, MAX_TEXT_SUBTITLE_TAG_COUNT);

    return TRUE;
}


BOOLEAN MApp_VDPlayer_SetTrickMode(EN_VDP_PLAY_MODE ePlayMode, EN_VDP_PLAY_SPEED ePlaySpeed)
{
    U8 idx = MB_VDPLAYER_SET_TRICK_MODE;

    if(enVDPlayerRet == EXIT_VDPLAYER_EXIT || enVDPlayerRet == EXIT_VDPLAYER_WAIT)
    {
        //printf("MApp_VDPlayer_SetTrickMode cannot set, video is finished.\n");
        return FALSE;
    }

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,idx
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,2
    /*p1*/              ,(U8)(ePlayMode)
    /*p2*/              ,(U8)(ePlaySpeed)
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

#if ENABLE_DVD
    if (bIsDVD)
    {
        MApp_DVD_SetTrickMode(ePlayMode, ePlaySpeed);
    }
#endif

    {
    #if ENABLE_TS_RADIO
        u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
        m_eVDPlayerAckFlags=(m_eVDPlayerAckFlags|E_ACKFLG_WAIT_SET_TRICK_MODE);
        u8VDPlayerSetTrickModeResult = 0; // ack return value.
        do
        {
            //VDPLAYER_DBG
            //(printf("wait MApp_VDPlayer_SetTrickMode coprocessor ack ing... \n"));
            MApp_VDPlayer_MailBoxHandler();
        }
        while((m_eVDPlayerAckFlags&E_ACKFLG_WAIT_SET_TRICK_MODE) &&
            (msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)<5000));

        if (m_eVDPlayerAckFlags&E_ACKFLG_WAIT_SET_TRICK_MODE)
        {
            //VDPLAYER_DVD_DBG
            (printf("MApp_VDPlayer_SetTrickMode timeout!\n"));
            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_TRICK_MODE);
            return FALSE;
        }
        else if (u8VDPlayerSetTrickModeResult == 0)
        {
            //VDPLAYER_DVD_DBG
            (printf("MApp_VDPlayer_SetTrickMode return False!\n"));
            return FALSE;
        }
    #endif

        return TRUE;
    }
}

BOOLEAN MApp_VDPlayer_SetRepeatAB(EN_SET_REPEATAB enAction)
{
    U32 u32Timer;

    if(enVDPlayerRet == EXIT_VDPLAYER_EXIT || enVDPlayerRet == EXIT_VDPLAYER_WAIT)
    {
        //printf("MApp_VDPlayer_SetRepeatAB cannot set, video is finished.\n");
        return FALSE;
    }

#if ENABLE_DVD
    if (bIsDVD)
    {
        MApp_DVD_SetRepeatAB(enAction);
        return TRUE;
    }
#endif

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_REPEAT_AB;

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_REPEAT_AB
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,(U8)(enAction)
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    u32Timer = msAPI_Timer_GetTime0();
    while(m_eVDPlayerAckFlags & E_ACKFLG_WAIT_REPEAT_AB)
    {
        if (msAPI_Timer_DiffTimeFromNow(u32Timer) > 2000)
        {
            break;
        }

        MApp_VDPlayer_MailBoxHandler();
    }

    return TRUE;
}

BOOLEAN MApp_VDPlayer_SetStep(void)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_STEP
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

#if ENABLE_TS_RADIO
    u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
    m_eVDPlayerAckFlags=(m_eVDPlayerAckFlags|E_ACKFLG_WAIT_STEP);
    u8VDPlayerStepPlayResult = 0; // ack return value.
    do
    {
        //VDPLAYER_DBG
        (printf("wait MApp_VDPlayer_SetStep coprocessor ack ing... \n"));
        MApp_VDPlayer_MailBoxHandler();
    }
    while((m_eVDPlayerAckFlags&E_ACKFLG_WAIT_STEP) &&
        (msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)<5000));

    if (m_eVDPlayerAckFlags&E_ACKFLG_WAIT_STEP)
    {
        //VDPLAYER_DVD_DBG
        (printf("MApp_VDPlayer_SetStep timeout!\n"));
        Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_STEP);
        return FALSE;
    }
    else if (u8VDPlayerStepPlayResult == 0)
    {
        //VDPLAYER_DVD_DBG
        (printf("MApp_VDPlayer_SetStep reutrn False!\n"));
        return FALSE;
    }
#endif

    return TRUE;

}

BOOL MApp_VDPlayer_SetRatingCtrl(U16 u16CtrlFlag)
{
    BOOL bRet = TRUE;
    U8 u8Data[MAX_MBX_PARAM_SIZE];
    memset(u8Data, 0, MAX_MBX_PARAM_SIZE);
    u8Data[0] = (U8)(u16CtrlFlag & 0xFF);
    u8Data[1] = (U8)((u16CtrlFlag >> 8) & 0xFF);
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
    /*Index*/           ,MB_VDPLAYER_RATING_CONTROL
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,2
    /*p1*/              ,u8Data[0]
    /*p2*/              ,u8Data[1]
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
    return bRet;
}
void MApp_VDPlayer_SetRatingLimitation(U8 u8RatingLimit)
{
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RATING_LIMITATION, u8RatingLimit);
}

BOOLEAN MApp_VDPlayer_SetAudioTrackID(U8 u8TrackId)
{
    m_eVDPlayerAckFlags=(m_eVDPlayerAckFlags|E_ACKFLG_WAIT_SET_AUDIO_TRACK_ID);
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_SET_AUDIO_TRACK_ID
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,(U8)(u8TrackId)
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    g_bUnsupportAudio = FALSE;
    u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
    u8VDPlayerSetAudioTrackResult = 0; // ack return value.
    do
    {
        //VDPLAYER_DBG(printf("wait MApp_VDPlayer_SetAudioTrackID coprocessor ack ing... \n"));
        MApp_VDPlayer_MailBoxHandler();
    }
    while((m_eVDPlayerAckFlags&E_ACKFLG_WAIT_SET_AUDIO_TRACK_ID) &&
        (msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)<1000));

    if (m_eVDPlayerAckFlags&E_ACKFLG_WAIT_SET_AUDIO_TRACK_ID)
    {
        //VDPLAYER_DVD_DBG(printf("MApp_VDPlayer_SetAudioTrackID timeout!\n"));
        Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_AUDIO_TRACK_ID);
        return FALSE;
    }
    else if (u8VDPlayerSetAudioTrackResult == 0)
    {
        //VDPLAYER_DVD_DBG(printf("MApp_VDPlayer_SetAudioTrackID reutrn False!\n"));
        return FALSE;
    }

    return TRUE;
}

//******************************************************************************
/// Force stop current video stream
/// @param  N/A
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN MApp_VDPlayer_VideoForceFileEnd(void)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_FORCE_FILE_END
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    return TRUE;

}

#if (ENABLE_DIVX_PLUS == 1)

U8 MApp_VDPlayer_GetTitleID(void)
{
    return g_u8TitleId;
}

U8 MApp_VDPlayer_GetEditionID(void)
{
    return g_u8EditionId;
}

BOOLEAN MApp_VDPlayer_SetTitleID(U8 u8TitleId)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_SET_TITLE_ID
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,u8TitleId
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    m_eVDPlayerAckFlags=(m_eVDPlayerAckFlags|E_ACKFLG_WAIT_SET_TITLE_ID);
    u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
    do
    {
        VDPLAYER_DBG(printf("wait MApp_VDPlayer_SetChapterID coprocessor ack ing... \n"));
        MApp_VDPlayer_MailBoxHandler();
    }
    while((m_eVDPlayerAckFlags&E_ACKFLG_WAIT_SET_TITLE_ID) &&
        (msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)<1000));

    if (m_eVDPlayerAckFlags&E_ACKFLG_WAIT_SET_TITLE_ID)
    {
        printf("MApp_VDPlayer_SetChapterID timeout!\n");
        Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_TITLE_ID);
        return FALSE;
    }

       g_u8TitleId = u8TitleId;
    return TRUE;

}

BOOLEAN MApp_VDPlayer_SetEditionID(U8 u8EditionId)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_SET_EDITION_ID
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,u8EditionId
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    m_eVDPlayerAckFlags=(m_eVDPlayerAckFlags|E_ACKFLG_WAIT_SET_EDITION_ID);
    u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
    do
    {
        VDPLAYER_DBG(printf("wait MApp_VDPlayer_SetChapterID coprocessor ack ing... \n"));
        MApp_VDPlayer_MailBoxHandler();
    }
    while((m_eVDPlayerAckFlags&E_ACKFLG_WAIT_SET_EDITION_ID) &&
        (msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)<1000));

    if (m_eVDPlayerAckFlags&E_ACKFLG_WAIT_SET_EDITION_ID)
    {
        printf("MApp_VDPlayer_SetChapterID timeout!\n");
        Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_EDITION_ID);
        return FALSE;
    }

    g_u8EditionId = u8EditionId;
    return TRUE;

}

BOOLEAN MApp_VDPlayer_SetChapterID(U8 u8ChapterId)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_SET_CHAPTER_ID
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,(U8)(u8ChapterId)
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    return TRUE;
}

BOOLEAN MApp_VDPlayer_SetAutoGenChapterID(U8 u8ChapterId)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_SET_AUTOGEN_CHAPTER_ID
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,(U8)(u8ChapterId)
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    return TRUE;
}
#endif

#if DYNSCALING
typedef enum
{
    MM_DS_XC_CMD_UPDATE_ZOOM_INFO = 1,
    MM_DS_XC_CMD_UPDATE_XC_INFO = 2,
} MM_DS_XC_CMD;

typedef struct
{
    // 0x000
    unsigned char u8DSVersion;                  // Versin
    unsigned char bHKIsUpdating;                // House keeping is writing
    unsigned char bFWIsUpdating;                // firmware is reading
    unsigned char bFWGotXCInfo;                 // for firmware internal use, indicate that firmware received XC current setting
    unsigned char u8XCInfoUpdateIdx;            //
    unsigned char bFWGotNewSetting;             // for firmware internal use, indicate that firmware received XC current setting
    unsigned char u8Dummy_3;
    unsigned char u8Dummy_2;

    // 0x008
    MS_WINDOW_TYPE stCapWin;
    MS_WINDOW_TYPE stCropWin;

    // 0x018
    MS_WINDOW_TYPE stDispWin;
    unsigned short u16H_SizeAfterPreScaling;
    unsigned short u16V_SizeAfterPreScaling;
    unsigned long u32Dummy;

    // 0x028
    unsigned long u32IPMBase0;                  ///<IPM base 0
    unsigned long u32IPMBase1;                  ///<IPM base 1
    unsigned long u32IPMBase2;                  ///<IPM base 2

    // 0x034
    MS_WINDOW_TYPE stNewCropWin;                ///< Zoom in/out new crop win
    MS_WINDOW_TYPE stNewDispWin;                ///< Zoom in/out new disp win

    // 0x044
    unsigned char bLinearMode;                  ///<Is current memory format LinearMode?
    unsigned char u8BitPerPixel;                ///<Bits number Per Pixel
    unsigned char bInterlace;                   ///<Interlaced or Progressive
    unsigned char u8Dummy1;

    // 0x048
    unsigned short u16IPMOffset;                ///<IPM offset
    unsigned short u16Dummy0;

    // 0x04C
    unsigned char bMirrorMode;                  ///<mirror mode
    unsigned char u8Dummy2[3];

    // internal use only
    // 0x050
    MS_WINDOW_TYPE stDSScaledCropWin;

    // 0x054
    unsigned short u16SizeAfterPreScaling;
    unsigned short u16Fetch;
    unsigned short u16Offset;
    unsigned short u16PixelOffset;
    unsigned short u16LineBufOffset;
    unsigned short u16Dummy1;

    // 0x060
    unsigned long u32CropOffset;

#if 1//DS_DEBUG
    // for debugging, 0x64
    unsigned char OPRegMaxDepth;                // point to record max OP reg depth
    unsigned char IPRegMaxDepth;                // point to record max IP reg depth
    unsigned char ErrorCode;                    // point to record error code
    unsigned char u8Dummy3;

    // 0x68
    unsigned short u16CodedWidth;
    unsigned short u16CodedHeight;
    unsigned short u16DSBufIdx;
    MS_WINDOW_TYPE stDSCropWin;
#endif
} MM_DS_XC_STATUS;

BOOLEAN MApp_VDPlayer_DS_UpdateXCStatus(MM_DS_XC_CMD eCmd)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_SETDYNSCALINGPARAMS
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,10
    /*p1*/              ,(U8) eCmd      // 0th byte, command
    /*p2*/              ,0              // 1th byte
    /*p3*/              ,1
    /*p4*/              ,3
    /*p5*/              ,5
    /*p6*/              ,7
    /*p7*/              ,2
    /*p8*/              ,4
    /*p9*/              ,6
    /*p10*/             ,8);           // 10th byte

    return TRUE;
}
#endif

#if 0
BOOLEAN MApp_VDPlayer_BeforeCaptureVideo(void)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_BEFORE_CAPTURE_VIDEO
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    return TRUE;
}

BOOLEAN MApp_VDPlayer_AfterCaptureVideo(void)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_AFTER_CAPTURE_VIDEO
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    return TRUE;
}
#endif

BOOLEAN MApp_VDPlayer_SetCfg(EN_VDPLAYER_CFG eCfg, U32 u32Value)
{
    switch (eCfg)
    {
        case E_VDPLAYER_CFG_BM_STREAM_MODE:
            _geBMStreamMode = (EN_BM_STREAM_MODE)u32Value;
            break;

        case E_VDPLAYER_CFG_ENABLE_INTERNAL_SUBTITLE:
            _gbEnableInternalSubtitle = (BOOLEAN)u32Value;
            break;

        case E_VDPLAYER_CFG_FORCE_STOP_CALLBACK:
            _gpfnForceStopCallBack = (pfnForceStopCallBack)u32Value;
            break;

        default:
            return FALSE;
    }

    return TRUE;
}

#if ENABLE_DRM
void MApp_VDPlayer_SaveDRMInfo(void)
{
    DRMinfo.u8DrmAuthorization= (bool) MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_AUTHORIZATION_STATUS);
    DRMinfo.u8DrmRentalStatus= (bool) MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_RENTAL_EXPIRE_STATUS);
    DRMinfo.u8DrmFileFormat= (bool) MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_FILE_FORMAT);
    DRMinfo.u32VDPlayerErrCode=MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_ERROR_INFO);

    DRMinfo.u32DrmRentalCode=  MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_RETURN_CODE);
    DRMinfo.u32DrmRentalFile= MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_RENTAL_FILE);
    DRMinfo.u32DrmRentalLimit= MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_RENTAL_USE_LIMIT);
    DRMinfo.u32DrmRentalUseCount= MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_RENTAL_USE_COUNT);
}
stDRMinfo MApp_VDPlayer_GetDRMInfo(void)
{
    return DRMinfo;
}
U32 MApp_VDPlayer_GetDRMErrCode(void)
{
    return DRMinfo.u32VDPlayerErrCode;
}
#endif

void _MApp_VDPlayer_SetScalerMemoryToDefault(void)
{
    //printf("_MApp_VDPlayer_SetScalerMemoryToDefault()\n");

#if( (MEMORY_MAP <= MMAP_32MB)&&(defined(SCALER_DNR_BUF_SDMM_ADR)) ) // 32M
    //printf("Set FB = SDMM %X %X\n", SCALER_DNR_BUF_SDMM_ADR, SCALER_DNR_BUF_SDMM_LEN );
    MApi_XC_SetFrameBufferAddress( SCALER_DNR_BUF_SDMM_ADR, SCALER_DNR_BUF_SDMM_LEN, MAIN_WINDOW);

    MApi_XC_SetAutoPreScaling(DISABLE, MAIN_WINDOW);

#else

    if (m_eVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW)
    {
        #if ( defined(SCALER_DNR_BUF_PREV_ADR))
        //printf("Set FB = DNR_Prev %X %X\n", SCALER_DNR_BUF_PREV_ADR, SCALER_DNR_BUF_PREV_LEN );
        MApi_XC_SetFrameBufferAddress(SCALER_DNR_BUF_PREV_ADR, SCALER_DNR_BUF_PREV_LEN, MAIN_WINDOW);
        #else
        MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, MAIN_WINDOW);
        #endif
    }
    else
    {
        // In signal memory model, MM will adjust scaler framebuffer for memory utilization.
        // We must restore the framebuffer setting to default here.
        MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, MAIN_WINDOW);
        //printf("Set FB = %X %X\n", ((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN);
    }
    MApi_XC_SetAutoPreScaling(DISABLE, MAIN_WINDOW);
#endif

    MApi_XC_EnableFrameBufferLess(DISABLE);
}

void _MApp_VDPlayer_VarInit(void)
{
    // Subtitle flow control
    u8IssubtitleInit=FALSE;        // EN_SUBTITLE_INIT_COMMAND
    u8IsSubtitleInitfinish=FALSE;      // EN_SUBTITLE_INIT_COMMAND
    u8IsSubtitleBusy=FALSE;
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
    u8IsFontTableReady=FALSE;
#endif

    u16tagposition=0;
    u16SubtitleTagCnt=0;
    u32subtitletype=0;
    u32GetSubtitleStateBuf=0;
#if ENABLE_SUBTITLE_DMP
#if (TS_INTERNAL_SUBTITLE_BMP || TS_INTERNAL_SUBTITLE_PGS)
    _bSubtitleShow_User = DISABLE;      // control by user.
    _bSubtitleShow_MW   = DISABLE;      // control by MW.
    u8InternalST_Num = 0;
#endif
    //set off by default and check if on for SUBIDX after play init OK.
    MApp_VDPlayer_SetSuspendInternalSubtitle2Queue(FALSE);
#endif //ENABLE_SUBTITLE_DMP
}

BOOLEAN MApp_VDPlayer_Init(VIDEO_PLAYER_INPUT_SOURCE_TYPE eInSrcType, VIDEO_PLAYER_PLAYING_TYPE eType, FileEntry *pFileEntry)
{
    extern unsigned char Customer_info[];
    extern unsigned char Customer_hash[];
#if ENABLE_DRM
    extern U16 u16DRMModelID;
#endif
    U8 u8Count;
    //U8 u8MailBox[12];
    U32 i,u32VDPlayer_init_timeout=VDPLAYER_INIT_TIMEOUT;
    MBX_MSGQ_Status Mstatus;
    MBX_Msg MB_Message;

    memset(&Mstatus,0,sizeof(MBX_MSGQ_Status));

#if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
    memset(u64BackupFilePosition,0,sizeof(u64BackupFilePosition));
#endif

#if (SUPPERTED_SEAMLESS_SMOTH)
    MApp_VDPlayer_SetSeamlessSmoth(ENABLE);
#endif
#if (DISABLE_VE_VSIZE_CHECK)
    MS_BOOL bVSizeMinIs576 = FALSE;
    MVOP_Handle stMvopHd = { E_MVOP_MODULE_MAIN };

    MDrv_MVOP_SetCommand(&stMvopHd, E_MVOP_CMD_SET_VSIZE_MIN, &bVSizeMinIs576);
#endif // #if (DISABLE_VE_VSIZE_CHECK)


    //MDrv_PQ_MADiForceMotionY(PQ_MAIN_WINDOW, FALSE);

    //MApp_VDPlayer_ClearDRMMemory();
    _MApp_VDPlayer_SetScalerMemoryToDefault();
    _MApp_VDPlayer_VarInit();
    MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_DecOutMode, AU_DVB_MODE_STEREO, 0);
    g_InputSourceType = eInSrcType;
    g_VideoPlayerPlayingType = eType;
    _gbCoprocessorEnable = TRUE;
    m_eFailStatus = E_VDPLAYER_FAIL_STATUS_VDPLAYER_ERROR;

#if( TS_INTERNAL_SUBTITLE_BMP || TS_INTERNAL_SUBTITLE_PGS)
    msAPI_Subtitle_SetFreeRunTime(35);
#endif

#if ENABLE_HK_MM
    //E_MBX_CLASS_VDPLAYER use callback function for immediately command
    if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSGWithCallBack(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE, _MApp_VDPlyer_VMailboxCallback))
    {
        if(E_MBX_SUCCESS != MDrv_VMBX_UnRegisterMSG(E_MBX_CLASS_VDPLAYER, TRUE))
        {
            VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSGWithCallBack(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE, _MApp_VDPlyer_VMailboxCallback))
            {
                VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER register failed\n"));
                return FALSE;
            }
        }
    }

    //E_MBX_CLASS_VDPLAYER_FS use queue and not immediately
    if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSG(E_MBX_CLASS_VDPLAYER_FS, MM_COMMON_MBX_QUEUESIZE))
    {
        if(E_MBX_SUCCESS != MDrv_VMBX_UnRegisterMSG(E_MBX_CLASS_VDPLAYER_FS, TRUE))
        {
            VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER_FS unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSG(E_MBX_CLASS_VDPLAYER_FS, MM_COMMON_MBX_QUEUESIZE))
            {
                VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER_FS register failed\n"));
                return FALSE;
            }
        }
    }

#else //#if ENABLE_HK_MM

    if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE))
    {
        if(E_MBX_SUCCESS != MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_VDPLAYER))
        {
            VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE))
            {
                VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER register failed\n"));
                return FALSE;
            }
        }
    }
#endif //#if ENABLE_HK_MM

#ifdef _VDPLAYER_DUMP_RAW_
    {
        U16 u16FileName[7] = {'D', 'U', 'M', 'P', '1', '6', 0};
        VDPlayer_dump_id = MApp_FileBrowser_OpenNewFileForWrite(u16FileName, 7);
        if (VDPlayer_dump_id == INVALID_FILE_HANDLE)
        {
            VDPLAYER_DBG(printf ("[ERROR] dump file open error\n"));
        }
    }
#endif // _VDPLAYER_DUMP_RAW_

#if ENABLE_HK_MP4
    if (init_mp4_resource(&stMP4, pFileEntry) != TRUE)
        return FALSE;
#endif

#if (SUPPERTED_SEAMLESS_SMOTH == DISABLE)
  #if (ENABLE_INTERNAL_SUBTITLE)
    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_ENABLE_INTERNAL_SUBTITLE, TRUE);
  #else
    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_ENABLE_INTERNAL_SUBTITLE, FALSE);
  #endif
#endif

#if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
    U32 u32StreamHandle0, u32read_size0, u32Read0 = 0x1000;
    U8 *ptr;
    u32StreamHandle0 = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_VIDEO);
    u32read_size0 =msAPI_DataStreamIO_Read(u32StreamHandle0, (void*)((VDPLAYER_BITSTREAM_BUFF_MEMORY_TYPE & MIU1) ? (VDPLAYER_BITSTREAM_BUFF_ADR | MIU_INTERVAL) : (VDPLAYER_BITSTREAM_BUFF_ADR)), u32Read0);

    if (u32Read0 - u32read_size0 > 4)
    {
        ptr = (U8*)_PA2VA((U32)((VDPLAYER_BITSTREAM_BUFF_MEMORY_TYPE & MIU1) ? (VDPLAYER_BITSTREAM_BUFF_ADR | MIU_INTERVAL) : (VDPLAYER_BITSTREAM_BUFF_ADR)));

        if ((ptr[0]==0x2)&&
            (ptr[1]==0x1E)&&
            (ptr[2]==0x15)&&
            (ptr[3]==0x76))
        {
            bIsPVR = TRUE;
            enEncryptType = msAPI_PVR_GetEncryptType(pFileEntry);
            printf("<<<<<<<<<<<<<<<enEncryptType=%d>>>>>>>>>>\n",enEncryptType);
        }
        else
        {
            bIsPVR = FALSE;
        }
    }
    if (u32StreamHandle0 != INVALID_DATA_STREAM_HDL)
    {
        // in case the file wasn't closed by previous play
        msAPI_DataStreamIO_Close(u32StreamHandle0);
        u32StreamHandle0 = INVALID_DATA_STREAM_HDL;
    }
#endif

#if ENABLE_NEW_FILE_HANDLER
    U8 u8Idx;
    for (u8Idx=0; u8Idx<TotalHandlerCnt; u8Idx++)
    {
        if (u32StreamHandleIdx[u8Idx] != INVALID_DATA_STREAM_HDL)
        {
            msAPI_DataStreamIO_Close(u32StreamHandleIdx[u8Idx]);
            u32StreamHandleIdx[u8Idx] = INVALID_DATA_STREAM_HDL;
        }

        switch (u8Idx)
        {
            case 0:
               u32StreamHandleIdx[u8Idx] = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_VIDEO);
               break;
            case 1:
               u32StreamHandleIdx[u8Idx] = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_IN_SUB);
               break;
            case 2:
               u32StreamHandleIdx[u8Idx] = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_AUDIO);
               break;
            case 3:
               u32StreamHandleIdx[u8Idx] = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_ATTACHMENT);
               break;
            default:
                printf("Error!!! over total file handler\n");
                break;
        }

        if (u32StreamHandleIdx[0] ==  INVALID_DATA_STREAM_HDL)
        {
        #if ENABLE_HK_MP4
            release_mp4_resource(&stMP4);
        #endif
            return FALSE;
        }
    }

    u8IssubtitleInit=FALSE;//Need to check this
    MApp_VDPlayer_StrmHandleAssignTblInit();

#else //ENABLE_NEW_FILE_HANDLER
    if (u32VDPlayerStreamHandleIdx_Video != INVALID_DATA_STREAM_HDL)
    {
        // in case the file wasn't closed by previous play
        msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Video);
        u32VDPlayerStreamHandleIdx_Video = INVALID_DATA_STREAM_HDL;
    }
    u32VDPlayerStreamHandleIdx_Video = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_VIDEO);

    if (u32VDPlayerStreamHandleIdx_Subtitle != INVALID_DATA_STREAM_HDL)
    {
        // in case the file wasn't closed by previous play
        msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Subtitle);
        u32VDPlayerStreamHandleIdx_Subtitle = INVALID_DATA_STREAM_HDL;
    }

    if (_gbEnableInternalSubtitle)
    {
        u32VDPlayerStreamHandleIdx_Subtitle = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_IN_SUB);
    }
    else
    {
        u32VDPlayerStreamHandleIdx_Subtitle = INVALID_DATA_STREAM_HDL;
    }

    u8IssubtitleInit=FALSE;//Need to check this
#if ENABLE_AUDIO_HANDLER
        if (u32VDPlayerStreamHandleIdx_Audio != INVALID_DATA_STREAM_HDL)
        {
            // in case the file wasn't closed by previous play
            msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Audio);
        }
        u32VDPlayerStreamHandleIdx_Audio = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_AUDIO);
#endif

#if ENABLE_ATTACHMENT_HANDLER
        if (u32VDPlayerStreamHandleIdx_Attachment != INVALID_DATA_STREAM_HDL)
        {
            // in case the file wasn't closed by previous play
            msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Attachment);
        }
        u32VDPlayerStreamHandleIdx_Attachment = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_ATTACHMENT);
#endif  //#if ENABLE_ATTACHMENT_HANDLER
    MApp_VDPlayer_StrmHandleAssignTblInit();

    if ( (u32VDPlayerStreamHandleIdx_Video == INVALID_DATA_STREAM_HDL)
      || (_gbEnableInternalSubtitle && (u32VDPlayerStreamHandleIdx_Subtitle == INVALID_DATA_STREAM_HDL))
     #if ENABLE_AUDIO_HANDLER
      || (u32VDPlayerStreamHandleIdx_Audio == INVALID_DATA_STREAM_HDL)
     #endif //#if ENABLE_AUDIO_HANDLER
     #if ENABLE_ATTACHMENT_HANDLER
      || (u32VDPlayerStreamHandleIdx_Attachment == INVALID_DATA_STREAM_HDL)
     #endif //#if ENABLE_ATTACHMENT_HANDLER
        )
    {
#if ENABLE_HK_MP4
        release_mp4_resource(&stMP4);
#endif
        return FALSE;
    }
#endif //ENABLE_NEW_FILE_HANDLER

    //Clear Command in Queue
#if ENABLE_HK_MM
    MDrv_VMBX_GetMsgQueueStatus(E_MBX_CLASS_VDPLAYER, &Mstatus);
    u8Count=(U8)Mstatus.u32NormalMsgCount;
    //u8Count = msAPI_MailBox_GetMsgCount(Q_VDPLAYER);
    for (i=0; i<u8Count; i++)
    {
        //msAPI_MailBox_GetMsg(Q_VDPLAYER, &u8MailBox[0]);
        MDrv_VMBX_RecvMsg(E_MBX_CLASS_VDPLAYER, &MB_Message, 0,MBX_CHECK_NORMAL_MSG);
    }

    MDrv_VMBX_GetMsgQueueStatus(E_MBX_CLASS_VDPLAYER_FS, &Mstatus);
    u8Count=(U8)Mstatus.u32NormalMsgCount;
    //u8Count = msAPI_MailBox_GetMsgCount(Q_VDPLAYER);
    for (i=0; i<u8Count; i++)
    {
        //msAPI_MailBox_GetMsg(Q_VDPLAYER, &u8MailBox[0]);
        MDrv_VMBX_RecvMsg(E_MBX_CLASS_VDPLAYER_FS, &MB_Message, 0,MBX_CHECK_NORMAL_MSG);
    }
#else //#if ENABLE_HK_MM
    MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_VDPLAYER, &Mstatus);
    u8Count=(U8)Mstatus.u32NormalMsgCount;
    //u8Count = msAPI_MailBox_GetMsgCount(Q_VDPLAYER);
    for (i=0; i<u8Count; i++)
    {
        //msAPI_MailBox_GetMsg(Q_VDPLAYER, &u8MailBox[0]);
       MSApi_MBX_RecvMsg(E_MBX_CLASS_VDPLAYER, &MB_Message, 0,MBX_CHECK_NORMAL_MSG);
    }
#endif //#if ENABLE_HK_MM

    u32VdplayerShareMemAddr = VDPLAYER_SHAREMEM_ADDR;

    for (i = 0; i < E_SHAREMEM_NUM; i++)
    {
        _Mapp_VDPlayer_SetShareMemData(i, 0);
    }

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_NUM, E_SHAREMEM_MAGICKEY);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_VERSION_NUM, SHAREMEM_VERSION_NUM);

    if (m_bVDPlayerPreview == TRUE)
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_PREVIEW_MODE, E_VDP_PREVIEW_VIDEO | E_VDP_PREVIEW_AUDIO | E_VDP_PREVIEW_INFO_INDEXTABLE);
    }
    else if (m_bVDPlayerThumbnail == TRUE)
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_PREVIEW_MODE, E_VDP_PREVIEW_VIDEO | E_VDP_PREVIEW_THUMBNAIL);
    }
#if ENABLE_POWERON_VIDEO
    else if (m_bVDPlayerPowerOnVideo == TRUE)
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_PREVIEW_MODE, E_VDP_PREVIEW_VIDEO | E_VDP_PREVIEW_AUDIO);
    }
#endif
#if ENABLE_PROBE_MOVIE_HEADER
    else if (m_bVDPlayerProbeHeaderOnly == TRUE)
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_PREVIEW_MODE, E_VDP_PREVIEW_INFO_DURATION | E_VDP_PREVIEW_INFO_RESOLUTION);
    }
#endif
    else
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_PREVIEW_MODE, E_VDP_PREVIEW_NONE);
    }

    if(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_PREVIEW_MODE) & E_VDP_PREVIEW_VIDEO)
    {
   #if ENABLE_DRM
        #if ENABLE_DIVX_PLUS
            g_u8TitleId = 0;
            g_u8EditionId = 0;
            g_bChangeFile = FALSE;
        #endif
        //g_bIsResumePlay = FALSE;
    #endif
    }

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_DBGINFO, TRUE);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SET_VDEC_DBGLEVEL, 0);    //0 -> E_VDEC_EX_DBG_LEVEL_NONE
                                                                        //1 -> E_VDEC_EX_DBG_LEVEL_ERR
                                                                        //2 -> E_VDEC_EX_DBG_LEVEL_INFO
                                                                        //3 -> E_VDEC_EX_DBG_LEVEL_DBG
                                                                        //4 -> E_VDEC_EX_DBG_LEVEL_TRACE
                                                                        //5 -> E_VDEC_EX_DBG_LEVEL_FW
#if( ENABLE_AV_INTERLEAVE_ENHANCE && defined(VDPLAYER_BITSTREAM_BUFF_EXT_LEN) && (VDPLAYER_BITSTREAM_BUFF_EXT_LEN!=0) )
    // When enable AUDIO_MOVE, vdplayer will need another buffer:VDPLAYER_BITSTREAM_BUFF_EXT
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BITSREAM_BUFF_EXT_ADDR, VDPLAYER_BITSTREAM_BUFF_EXT_ADR);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BITSREAM_BUFF_EXT_LEN, VDPLAYER_BITSTREAM_BUFF_EXT_LEN);
#endif

    // Always Turn ON Audio Move
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_AUDIO_MOVE, TRUE);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_NETWORKSTREAM_MODE, _geBMStreamMode); // not seekable imply network stream?

#if(ENABLE_MIU_1==0)
    //only one MIU, setup decoder's parameters, needs to fine-tune HVD_BW_TUNING_SETTING for each project
    //_Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SETBALANCEBW, HVD_BW_TUNING_SETTING);
#endif

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DATA_BUFF_ADDR, VDPLAYER_AEON_DATABUFF_ADDR);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BITSREAM_BUFF_ADDR, ((VDPLAYER_BITSTREAM_BUFF_MEMORY_TYPE & MIU1) ? (VDPLAYER_BITSTREAM_BUFF_ADR | MIU_INTERVAL) : (VDPLAYER_BITSTREAM_BUFF_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MAD_BUFF_ADDR, (msAPI_AUD_GetDspMadBaseAddr(DSP_DEC)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD3_FW_ADDR, ((VDEC_AEON_MEMORY_TYPE & MIU1) ? (VDEC_AEON_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_AEON_ADR)));
#if ENABLE_MVC
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_ADR, ((VDEC_MVC_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VDEC_MVC_FRAMEBUFFER_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_MVC_FRAMEBUFFER_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_ADR, ((VDEC_MVC_BITSTREAM_MEMORY_TYPE & MIU1) ? (VDEC_MVC_BITSTREAM_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_MVC_BITSTREAM_ADR)));
#else
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_ADR, ((VDEC_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_FRAMEBUFFER_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_ADR, ((VDEC_BITSTREAM_MEMORY_TYPE & MIU1) ? (VDEC_BITSTREAM_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_BITSTREAM_ADR)));
#endif
  #if ENABLE_ATTACHMENT_HANDLER
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_ATTACHEDFILE_BUFF_ADDR, ((DIVX_ATTACHEDMENT_MEMORY_TYPE & MIU1) ? (DIVX_ATTACHEDMENT_ADR | MIU_INTERVAL) : (DIVX_ATTACHEDMENT_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DIVX_TITLE_STRINGNAME_ADDR, ((DIVX_STRING_MEMORY_TYPE & MIU1) ? (DIVX_STRING_ADR | MIU_INTERVAL) : (DIVX_STRING_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_ATTACHEDFILE_BUFF_LEN,DIVX_ATTACHEDMENT_LEN);
  #endif

  #if ENABLE_INTERNAL_SUBTITLE
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_BITSREAM_BUFF_ADDR,
        ((VDPLAYER_SUBTITLE_BITSTREAM_BUFF_MEMORY_TYPE & MIU1) ? (VDPLAYER_SUBTITLE_BITSTREAM_BUFF_ADR | MIU_INTERVAL) : (VDPLAYER_SUBTITLE_BITSTREAM_BUFF_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_BITSREAM_BUFF_LEN, VDPLAYER_SUBTITLE_BITSTREAM_BUFF_LEN);
  #endif

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DATA_BUFF_LEN, VDPLAYER_AEON_DATABUFF_SIZE);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BITSREAM_BUFF_LEN, VDPLAYER_BITSTREAM_BUFF_LEN);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MAD_BUFF_LEN, MAD_BASE_BUFFER_LEN);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD3_FW_LEN, VDEC_AEON_LEN);

#if ENABLE_MVC
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN, VDEC_MVC_FRAMEBUFFER_LEN);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_LEN, VDEC_MVC_BITSTREAM_LEN);
#else
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN, VDEC_FRAMEBUFFER_LEN);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_LEN, VDEC_BITSTREAM_LEN);
#endif

#if (defined(SECBUF_START_ADR)&&defined(SECBUF_START_LEN)&&(SECBUF_START_LEN != 0))
    //This is a temp buffer used for loading TSP bin file to TSP internal sram in init state
    //After init state , xdemux will release this buffer , so it can co-buffer with other memory
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_TSP_FW_ADDR, ((SECBUF_START_MEMORY_TYPE & MIU1) ? (SECBUF_START_ADR | MIU_INTERVAL) : (SECBUF_START_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_TSP_FW_LEN, SECBUF_START_LEN);
#else
    //This is a temp buffer used for loading TSP bin file to TSP internal sram in init state
    //After init state , xdemux will release this buffer , so it can co-buffer with other memory
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_TSP_FW_ADDR, ((MAD_BASE_BUFFER_MEMORY_TYPE & MIU1) ? (MAD_BASE_BUFFER_ADR | MIU_INTERVAL) : (MAD_BASE_BUFFER_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_TSP_FW_LEN, MAD_BASE_BUFFER_LEN);
#endif

#if( ENABLE_MM_XC_FBL_MODE )
    if(m_bVDPlayerPreview)
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE_CHECKING, (U32)DISABLE); //disable FBL checking
    }
    else
    {
    #if( (ENABLE_MM_HD_FB&&(MEMORY_MAP == MMAP_64MB)) || (MM_1080I_USE_FB))
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE_CHECKING, (U32)DISABLE); //disable FBL checking
    #else
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE_CHECKING, (U32)ENABLE); //enable FBL checking
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FBL_MODE_THRESHOLD, (U32)ENABLE_FBL_MODE_THRESHOLD); //set FBL threshold
        #if (ENABLE_HEVC_1080P50_FBL_MODE)
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FBL_MODE_THRESHOLD_WITH_FRAMERATE, (U32)ENABLE); //enable FBL threshold with framerate
        #endif
    #endif
    }
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FBL_FORCE_PROGRESS,(U32)DISABLE); // disable force progress mode

    #ifdef VDEC_FRAMEBUFFER_SD_ADR
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_ADR_SD, ((VDEC_FRAMEBUFFER_SD_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_SD_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_FRAMEBUFFER_SD_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN_SD, VDEC_FRAMEBUFFER_SD_LEN);
    #else
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_ADR_SD, ((VDEC_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_FRAMEBUFFER_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN_SD, VDEC_FRAMEBUFFER_LEN);
    #endif

    #ifdef VDEC_BITSTREAM_SD_ADR
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_ADR_SD, ((VDEC_BITSTREAM_SD_MEMORY_TYPE& MIU1) ? (VDEC_BITSTREAM_SD_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_BITSTREAM_SD_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_LEN_SD, VDEC_BITSTREAM_SD_LEN);
    #else
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_ADR_SD, ((VDEC_BITSTREAM_MEMORY_TYPE& MIU1) ? (VDEC_BITSTREAM_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_BITSTREAM_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_LEN_SD, VDEC_BITSTREAM_LEN);
    #endif
#else
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE_CHECKING, (U32)DISABLE); //disable FBL checking
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FBL_FORCE_PROGRESS,(U32)DISABLE); // disable force progress mode
#endif

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPOS_LOW, 0);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPOS_HIGH, 0);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPTS, 0);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_AUDIO_TRACK_ID, 0);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_SUBTITLE_TRACK_ID, 0);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PROGRAM_IDX, 0);

#if ENABLE_DRM
    //not to re-init vdplayer while FB to file begin to avoid rental count was decreased
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BACKWARD_REPLAY_MODE, (U32)ENABLE);
#endif

#if (VDPLAYER_VERIFY_SCALER_FPGA)
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DISABLE_AVSYNC, (U32)ENABLE);
#endif

#if (ENABLE_AUDIO_HANDLER)
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_AUDIO_HANDLER, (U32)ENABLE);
#endif //
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_NEW_AUDIO_MM_MODE, ENABLE_NEW_MM_AUDIO);

#if 0//ENABLE_LAST_MEMORY==1
    if ((m_u8LastMemoryCheck==TRUE) && (m_u8LastMemorySearchHit==TRUE))
    {
        U32 u32ResumeTimeMs, u32ResumePosL, u32ResumePosH;

        MApp_MPlayer_LastMemory_GetResumePos(&u32ResumeTimeMs, &u32ResumePosL, &u32ResumePosH);
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPOS_LOW, u32ResumePosL);
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPOS_HIGH, u32ResumePosH);
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPTS, u32ResumeTimeMs);
        VDPLAYER_DBG(printf("MApp_VDPlayer_Init, LastMemory, idx=%d, pos=0x%x%x, pts=%dms\n", m_u32LastMemoryCurIdx, u32ResumePosH, u32ResumePosL, u32ResumeTimeMs););
    }
#endif

    for(i = 0; i < E_SHAREMEM_CUSTOMER_INFO_SIZE; i++)
    {
        U32 u32Info;
        u32Info = Customer_info[i*4] + (Customer_info[i*4 + 1] << 8) +
            (Customer_info[i*4 + 2] << 16) + (Customer_info[i*4 + 3] << 24);
        _Mapp_VDPlayer_SetShareMemData((EN_VDP_SHAREMEMORY)(E_SHAREMEM_CUSTOMER_INFO + i), u32Info);
    }

    for(i = 0; i < E_SHAREMEM_CUSTOMER_HASH_SIZE; i++)
    {
        U32 u32Hash;
        u32Hash = Customer_hash[i*4] + (Customer_hash[i*4 + 1] << 8) +
            (Customer_hash[i*4 + 2] << 16) + (Customer_hash[i*4 + 3] << 24);
        _Mapp_VDPlayer_SetShareMemData((EN_VDP_SHAREMEMORY)(E_SHAREMEM_CUSTOMER_HASH + i), u32Hash);
    }


    u32VDPlayerAudioSupportedFormat|=_MApp_VDPlayer_CheckSupportedAudio();
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUPPORTED_AUDIO, u32VDPlayerAudioSupportedFormat);
    if(u32VDPlayerAudioSupportedFormat & E_VDP_AUDIO_NO_SUPPORT_DTS)
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUPPORT_DTS_DECODE, FALSE);
    }
    else
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUPPORT_DTS_DECODE, TRUE);
    }


#ifdef ENABLE_KTV
    if( g_InputSourceType == VIDEO_PLAYER_INPUT_SOURCE_KTV)
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_ADR, VDEC_BITSTREAM_SD_ADR);
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN, VDEC_FRAMEBUFFER_SD_LEN);
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_LEN, VDEC_BITSTREAM_SD_LEN);
    }
#endif

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DISABLE_AUDIO, _bEnableVideoOnly);
#if ENABLE_TS_RADIO
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_RADIO, TRUE);
#endif


    U32 u32EnTSIntSubtitle = 0;
#if TS_INTERNAL_SUBTITLE_BMP
    u32EnTSIntSubtitle |= E_TS_INTERNAL_SUBTITLE_BMP;    /// enable TS BMP parser
#endif
#if TS_INTERNAL_SUBTITLE_PGS
    u32EnTSIntSubtitle |= E_TS_INTERNAL_SUBTITLE_PGS;    /// enable TS PGS parser
#endif
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_TS_INTERNAL_SUBTITLE, u32EnTSIntSubtitle);

    /// If not mvc case, vdplayer bitstream co-buffer with VDEC and buffer size less than 4M
    /// MVC transfer to H264 will not smooth, because AV interleave will be easily appeared in experience test
    /// bistream buffer is 4M (or less), AV interleave problem will easily to reproduce.
    /// But buffer size is 8M (or more), AV interleave problem will hard to reproduce.
    #define MVC_BITSTREAMERBUF_AVINTERLEAVE_THRESHOLD 0X800000
    if(((VDPLAYER_BITSTREAM_BUFF_ADR == VDEC_BITSTREAM_ADR) &&
        (VDPLAYER_BITSTREAM_BUFF_LEN <= MVC_BITSTREAMERBUF_AVINTERLEAVE_THRESHOLD)) ||
       ((VDPLAYER_BITSTREAM_BUFF_LEN == 0) ||
        (VDEC_BITSTREAM_LEN == 0)))
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVC_NOT_TRANSFER_TO_H264,TRUE);
    }


#if (ENABLE_FDMASK_DELAY == 1)
{
    const XC_ApiInfo *pXC_ApiInfo;

    pXC_ApiInfo = MApi_XC_GetInfo();
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SCALER_MAX_FRAMENUM, pXC_ApiInfo->u8MaxFrameNumInMem);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SCALER_MAX_FIELDNUM, pXC_ApiInfo->u8MaxFieldNumInMem);
}
#endif  // #if (ENABLE_FDMASK_DELAY == 1)

#if DYNSCALING
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING, 1);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DYNSCALING_WIDTH , DYNAMIC_SCALING_VB_H);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DYNSCALING_HEIGHT , DYNAMIC_SCALING_VB_V);
#else
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING, 0);
#endif

    for (i = E_SHAREMEM_BLOCK_FILEIO_TIMEOUT; i <= E_SHAREMEM_ESBUF_CTRL_TIMEOUT; i++)
    {
        _Mapp_VDPlayer_SetShareMemData(i, m_u32CodecTimeOut[i-E_SHAREMEM_BLOCK_FILEIO_TIMEOUT]);
    }

#if (SUPPERTED_SEAMLESS_SMOTH)
    if (m_u32TableSize != 0)
    {
        if (m_u32TableAddress == 0)
        {
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN) - m_u32TableSize);
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FRAME_TABLE_ADDRESS, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_ADR) + _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN) - m_u32TableSize);
        }
        else
        {
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FRAME_TABLE_ADDRESS, m_u32TableAddress);
        }
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FRAME_TABLE_SIZE, m_u32TableSize);
    }
#endif

#if DYNSCALING
    XC_DynamicScaling_Info stDS_Info;
    memset(&stDS_Info, 0, sizeof(XC_DynamicScaling_Info));
    stDS_Info.bOP_DS_On = FALSE;
    stDS_Info.bIPS_DS_On = FALSE;
    stDS_Info.bIPM_DS_On = FALSE;
    if(TRUE != MApi_XC_SetDynamicScaling(&stDS_Info, sizeof(XC_DynamicScaling_Info), MAIN_WINDOW))
    {
        printf("Set DS error\n");
    }
    MDrv_PQ_SetDS_OnOFF(PQ_MAIN_WINDOW,  FALSE);
#endif

#if ENABLE_HK_MM
    MApp_VDPlayer_UartSwitch(E_UART_SWITCH_TO_HK);
#else
    MApp_VDPlayer_UartSwitch(E_UART_SWITCH_TO_COPROCESSOR);
#endif

#if 0
      MApp_VDPlayer_ClearDRMMemory();
//for LG demo only.
    if(g_bFirstDRMRegCode == TRUE)
    {
        g_bFirstDRMRegCode = FALSE;
        MApp_VDPlayer_GetDRMRegistrationCode_Demo((U32)g_DRMRegCode);
        printf("DRMRegCode: %s\r\n", g_DRMRegCode);
        MApp_VDPlayer_SaveDRMMemory();
    }
#endif
#if ENBALE_PARENTALRATING_MM
        if(stGenSetting.g_BlockSysSetting.u8BlockSysLockMode==1)
        {
            if(stGenSetting.g_BlockSysSetting.u8ParentalControl > EN_F4_LockSystem_Min)
            {
               _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_RATING_CONTROL, TRUE);
               MApp_VDPlayer_SetRatingLimitation(stGenSetting.g_BlockSysSetting.u8ParentalControl);
            }
        }
#endif

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DRM_CHECK_STATUS, TRUE);

#if ENABLE_DRM

    MApp_LoadDrmSetting();
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DRM_CHECK_STATUS, TRUE);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DRM_MODEL_ID, ((GetByte0(u16DRMModelID)<<8))|GetByte1(u16DRMModelID));
#if ENABLE_LAST_MEMORY==1
    if(m_u8LastMemorySearchHit)
    {
        if(g_bIsResumePlay) // ggg
        {
            MApp_VDPlayer_LoadVISUALDRMMemory();
        }
        else
        {
            MApp_VDPlayer_LoadDRMMemory();
        }
#if ENABLE_DIVX_PLUS
        if(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_PREVIEW_MODE)  == FALSE)
        {
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DIVX_CURRENT_STATUS, g_u32DivxPlusPTS);
            u32OrgDivPlusPTS = g_u32DivxPlusPTS;
            //g_u8TitleId = (U8)(g_u32DivxPlusPTS >> 24);      //0913
    }
#endif
    }
    else
#endif
        MApp_VDPlayer_LoadDRMMemory();
    g_bReplay = FALSE;
#endif
    if (g_WMDRMPrivateReady)
        MApp_VDPlayer_WMDRMPD_LoadPrivate();

#if ENABLE_HK_MM
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DISABLE_DMXINIT, TRUE);
#endif

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SET_VIDEO_SYNCDELAY, m_u32VideoSyncDelayMsTime);

#if ENABLE_WMDRMPD
    u32WMDRMPDShareMemAddr = 0x0;
#endif

    g_bUnsupportAudio = FALSE;  //20100809EL

#if SEAMLESS_PLAYING_ENABLE
    if (!_bEnableSeamlessPlaying || !MApi_XC_IsFreezeImg(MAIN_WINDOW))
#endif
    {
        msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        //msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 300, MAIN_WINDOW); // DELAY_FOR_STABLE_CHANNELCHANGE);
        MDrv_MVOP_Enable(FALSE);
    }

    if (_gu16PreviewX == 0xffff)
    {
        _gu16PreviewX = MOVIE_PREVIEW_X;
        _gu16PreviewY = MOVIE_PREVIEW_Y;
        _gu16PreviewWidth  = MOVIE_PREVIEW_WIDTH;
        _gu16PreviewHeight = MOVIE_PREVIEW_HEIGHT;
    }
    _gbContinueBlockRead = FALSE;
    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_INIT;


#if ENABLE_DIVX_PLUS
        if(g_bChangeFile == FALSE)
        {
            //g_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
        }

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_INIT
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,8
    /*p1*/              ,(U8)(u32VdplayerShareMemAddr>>24)
    /*p2*/              ,(U8)(u32VdplayerShareMemAddr>>16)
    /*p3*/              ,(U8)(u32VdplayerShareMemAddr>>8)
    /*p4*/              ,(U8)(u32VdplayerShareMemAddr&0x000000FF)
    /*p5*/              ,g_bChangeFile
    /*p6*/              ,FALSE  // ggg
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
#else
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_INIT
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,8
    /*p1*/              ,(U8)(u32VdplayerShareMemAddr>>24)
    /*p2*/              ,(U8)(u32VdplayerShareMemAddr>>16)
    /*p3*/              ,(U8)(u32VdplayerShareMemAddr>>8)
    /*p4*/              ,(U8)(u32VdplayerShareMemAddr&0x000000FF)
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
#endif
    // Waiting for Aeon Video Player initialization done
    bMovieAbort = FALSE;

    u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
    u8VDPlayerInitResult = FALSE;
    enVDPlayerRet = EXIT_VDPLAYER_DECODING;

    do
    {
        if (_gpfnForceStopCallBack != NULL)
        {
            EN_VDPLAYER_FORCE_STOP_RESULT eRet = (*_gpfnForceStopCallBack)(E_FORCE_STOP_INIT);
            if (eRet != E_VDPLAYER_CONTINUE_PLAYING)
            {
              #if ENABLE_DRM
                MApp_VDPlayer_SaveDRMInfo();
              #endif
                MApp_VDPlayer_Stop(); //fix preview next file it will show "un-support file" after abort(need to issue STOP CMD to co-processor)

                if(eRet == E_VDPLAYER_USER_EXIT)
                {
                    bMovieAbort = TRUE;
                    m_eFailStatus = E_VDPLAYER_FAIL_STATUS_USER_EXIT;
                    return FALSE;
                }
                else if(eRet == E_VDPLAYER_ERROR_EXIT)
                {
#if ENABLE_HK_MP4
                    release_mp4_resource(&stMP4);
#endif
                    return FALSE;
                }
            }
        }
    #if (VDPLAYER_CHECK_PREVIEW_ABORT)
        else
        {
            if(_MApp_VDPlayer_CheckPreviewAbortKey())
            {
              #if ENABLE_DRM
                MApp_VDPlayer_SaveDRMInfo();
              #endif
                MApp_VDPlayer_Stop(); //fix preview next file it will show "un-support file" after abort(need to issue STOP CMD to co-processor)

                // Return value to MPlayer, and abort the remaining process
                bMovieAbort = TRUE;
                m_eFailStatus = E_VDPLAYER_FAIL_STATUS_NONE;
                return TRUE;
            }
        }
    #endif

        MApp_VDPlayer_MailBoxHandler();

    #if (WATCH_DOG == ENABLE)
        if ((msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer) % 5000) == 0) //should reset WTD in 5s
        {
            msAPI_Timer_ResetWDT();
        }
    #endif

        //Check USB connected directly
#if(ENABLE_POWERON_VIDEO)
        if(!msAPI_Pan_Get_Status())
        {
            if(!MApp_MPlayer_QueryCurrentDeviceIsConnected())
            {
               #if ENABLE_DRM
                  MApp_VDPlayer_SaveDRMInfo();
                #endif
#if ENABLE_HK_MP4
                    release_mp4_resource(&stMP4);
#endif
                return FALSE;
            }
        }
#endif
    }
    while((m_eVDPlayerAckFlags&E_ACKFLG_WAIT_INIT) &&
                (msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)<u32VDPlayer_init_timeout));

    U32 u32InputPixelClock;
    u32InputPixelClock = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DEMUX_H_SIZE)* MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DEMUX_V_SIZE)* (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DEMUX_FRM_RATE)/1000);
    if( u32InputPixelClock >= INPUT_PIXEL_CLOCK_THRESHOLD)
    {
        printf("Init Fail: input pixel clock is over threshold (%d)\n", INPUT_PIXEL_CLOCK_THRESHOLD);
        u8VDPlayerInitResult = FALSE;
    }

    // if init failed, close file and disable VOP
    if(u8VDPlayerInitResult == FALSE)
    {
      #if ENABLE_DRM
        MApp_VDPlayer_SaveDRMInfo();
      #endif
        MApp_VDPlayer_Stop(); //fix preview next file it will show "un-support file" after abort(need to issue STOP CMD to co-processor)
//        _MApp_VDPlayer_Exit();
    }
    else
    {
      #if ENABLE_DRM
        MApp_VDPlayer_SaveDRMInfo();
      #endif
      #if (VDPLAYER_CHECK_COPROCESSOR_STATUS)
        // If init successed, start to check AEON status
        u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
      #endif
    }

#if (ENABLE_INTERNAL_SUBTITLE == 0)
    //disable internal subtitle parsing
    MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_DISABLE_ALL_SUBTITLE);
#else
  #if (ENABLE_INTERNAL_TS_SUBTITLE == 0)
    //disable internal TS subtitle parsing
    MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_DISABLE_TS_SUBTITLE);
  #endif
  #if (ENABLE_INTERNAL_BMP_SUBTITLE == 0)
    //disable internal bmp subtitle parsing
    MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_DISABLE_BMP_SUBTITLE);
  #endif
#endif //#if (ENABLE_INTERNAL_SUBTITLE == 0)

#if (ENABLE_SUBTITLE_SUB)
    MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime();
#endif

#if ENABLE_DVD
    bIsDVD = FALSE;
#endif
    if(u8VDPlayerInitResult == TRUE)
    {
        m_eFailStatus = E_VDPLAYER_FAIL_STATUS_NONE;
    }
    return u8VDPlayerInitResult;
}

#if ENABLE_DVD

BOOLEAN MApp_VDPlayer_DVD_Init(VIDEO_PLAYER_INPUT_SOURCE_TYPE eInSrcType, VIDEO_PLAYER_PLAYING_TYPE eType, FileEntry *pFileEntry)
{
    extern unsigned char Customer_info[];
    extern unsigned char Customer_hash[];
    U8 u8Count;
    U32 i,u32VDPlayer_init_timeout = VDPLAYER_INIT_TIMEOUT;
    MBX_MSGQ_Status Mstatus;
    MBX_Msg MB_Message;

    U8 u8Len;
    U16 u16LongFileName[FILE_INFO_LONG_FILENAME_SIZE >> 1];
    U8 *u8FileName = (U8 *)u16LongFileName;
    U32 u32Val;

    _MApp_VDPlayer_SetScalerMemoryToDefault();

    g_InputSourceType = eInSrcType;
    g_VideoPlayerPlayingType = eType;

    _gbCoprocessorEnable = TRUE;

#if ENABLE_HK_MM
    //E_MBX_CLASS_VDPLAYER use callback function for immediately command
    if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSGWithCallBack(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE, _MApp_VDPlyer_VMailboxCallback))
    {
        if(E_MBX_SUCCESS != MDrv_VMBX_UnRegisterMSG(E_MBX_CLASS_VDPLAYER, TRUE))
        {
            VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSGWithCallBack(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE, _MApp_VDPlyer_VMailboxCallback))
            {
                VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER register failed\n"));
                return FALSE;
            }
        }
    }

    //E_MBX_CLASS_VDPLAYER_FS use queue and not immediately
    if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSG(E_MBX_CLASS_VDPLAYER_FS, MM_COMMON_MBX_QUEUESIZE))
    {
        if(E_MBX_SUCCESS != MDrv_VMBX_UnRegisterMSG(E_MBX_CLASS_VDPLAYER_FS, TRUE))
        {
            VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER_FS unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MDrv_VMBX_RegisterMSG(E_MBX_CLASS_VDPLAYER_FS, MM_COMMON_MBX_QUEUESIZE))
            {
                VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER_FS register failed\n"));
                return FALSE;
            }
        }
    }
#else //#if ENABLE_HK_MM
    if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE))
    {
        if(E_MBX_SUCCESS != MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_VDPLAYER))
        {
            VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_VDPLAYER, MM_COMMON_MBX_QUEUESIZE))
            {
                VDPLAYER_DBG(printf("E_MBX_CLASS_VDPLAYER register failed\n"));
                return FALSE;
            }
        }
    }
#endif //#if ENABLE_HK_MM

    //Clear Command in Queue
#if ENABLE_HK_MM
    MDrv_VMBX_GetMsgQueueStatus(E_MBX_CLASS_VDPLAYER, &Mstatus);
    u8Count=(U8)Mstatus.u32NormalMsgCount;
    for (i=0; i<u8Count; i++)
    {
        MDrv_VMBX_RecvMsg(E_MBX_CLASS_VDPLAYER, &MB_Message, 0,MBX_CHECK_NORMAL_MSG);
    }

    MDrv_VMBX_GetMsgQueueStatus(E_MBX_CLASS_VDPLAYER_FS, &Mstatus);
    u8Count=(U8)Mstatus.u32NormalMsgCount;
    for (i=0; i<u8Count; i++)
    {
        MDrv_VMBX_RecvMsg(E_MBX_CLASS_VDPLAYER_FS, &MB_Message, 0,MBX_CHECK_NORMAL_MSG);
    }
#else //#if ENABLE_HK_MM
    MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_VDPLAYER, &Mstatus);
    u8Count=(U8)Mstatus.u32NormalMsgCount;
    for (i=0; i<u8Count; i++)
    {
       MSApi_MBX_RecvMsg(E_MBX_CLASS_VDPLAYER, &MB_Message, 0,MBX_CHECK_NORMAL_MSG);
    }
#endif //#if ENABLE_HK_MM

    u32VdplayerShareMemAddr = VDPLAYER_SHAREMEM_ADDR;

    for (i = 0; i < E_SHAREMEM_NUM; i++)
    {
        _Mapp_VDPlayer_SetShareMemData(i, 0);
    }

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_NUM, E_SHAREMEM_MAGICKEY);
    if (m_bVDPlayerPreview == TRUE)
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_PREVIEW_MODE, E_VDP_PREVIEW_VIDEO | E_VDP_PREVIEW_AUDIO);
    }
    else
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_PREVIEW_MODE, E_VDP_PREVIEW_NONE);
    }
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_DBGINFO, TRUE);

#if( ENABLE_AV_INTERLEAVE_ENHANCE && defined(VDPLAYER_BITSTREAM_BUFF_EXT_LEN) && (VDPLAYER_BITSTREAM_BUFF_EXT_LEN!=0) )
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_AUDIO_MOVE, TRUE);
    // When enable AUDIO_MOVE, vdplayer will need another buffer:VDPLAYER_BITSTREAM_BUFF_EXT
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BITSREAM_BUFF_EXT_ADDR, VDPLAYER_BITSTREAM_BUFF_EXT_ADR);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BITSREAM_BUFF_EXT_LEN, VDPLAYER_BITSTREAM_BUFF_EXT_LEN);
#else
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_ENABLE_AUDIO_MOVE, FALSE);
#endif

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_NETWORKSTREAM_MODE, _geBMStreamMode); // not seekable imply network stream?

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DATA_BUFF_ADDR, VDPLAYER_AEON_DATABUFF_ADDR);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BITSREAM_BUFF_ADDR, ((VDPLAYER_BITSTREAM_BUFF_MEMORY_TYPE & MIU1) ? (VDPLAYER_BITSTREAM_BUFF_ADR | MIU_INTERVAL) : (VDPLAYER_BITSTREAM_BUFF_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MAD_BUFF_ADDR, ((MAD_BASE_BUFFER_MEMORY_TYPE & MIU1) ? (MAD_BASE_BUFFER_ADR | MIU_INTERVAL) : (MAD_BASE_BUFFER_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD3_FW_ADDR, ((VDEC_AEON_MEMORY_TYPE & MIU1) ? (VDEC_AEON_ADR | MIU_INTERVAL) : (VDEC_AEON_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_ADR, ((VDEC_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_ADR | MIU_INTERVAL) : (VDEC_FRAMEBUFFER_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_ADR, ((VDEC_BITSTREAM_MEMORY_TYPE & MIU1) ? (VDEC_BITSTREAM_ADR | MIU_INTERVAL) : (VDEC_BITSTREAM_ADR)));

  #if ENABLE_ATTACHMENT_HANDLER
      #if(ENABLE_API_MMAP_GET_BUF) // Use MMAP API
        U32 u32SubtitleBufAddr = 0, u32SubtitleBufSize = 0;
        msAPI_MMAP_Get_BufInfo(E_BUFID_SUBTITLE, &u32SubtitleBufAddr, &u32SubtitleBufSize );
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_ATTACHEDFILE_BUFF_ADDR, u32SubtitleBufAddr);
      #else
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_ATTACHEDFILE_BUFF_ADDR, ((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR)));
      #endif
  #endif

  #if ENABLE_INTERNAL_SUBTITLE
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_BITSREAM_BUFF_ADDR,
        ((VDPLAYER_SUBTITLE_BITSTREAM_BUFF_MEMORY_TYPE & MIU1) ? (VDPLAYER_SUBTITLE_BITSTREAM_BUFF_ADR | MIU_INTERVAL) : (VDPLAYER_SUBTITLE_BITSTREAM_BUFF_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_BITSREAM_BUFF_LEN, VDPLAYER_SUBTITLE_BITSTREAM_BUFF_LEN);
  #endif

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_DATA_BUFF_LEN, VDPLAYER_AEON_DATABUFF_SIZE);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BITSREAM_BUFF_LEN, VDPLAYER_BITSTREAM_BUFF_LEN);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MAD_BUFF_LEN, MAD_BASE_BUFFER_LEN);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD3_FW_LEN, VDEC_AEON_LEN);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN, VDEC_FRAMEBUFFER_LEN);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_LEN, VDEC_BITSTREAM_LEN);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_TSP_FW_ADDR, SECBUF_START_ADR /*u32SecbufAddr*/ );
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_TSP_FW_LEN, SECBUF_START_LEN /*u32SecbufSize*/ );
    // timothy for true type test
  #if ENABLE_ATTACHMENT_HANDLER
    #if(ENABLE_API_MMAP_GET_BUF) // Use MMAP API
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_ATTACHEDFILE_BUFF_LEN,u32SubtitleBufSize);
    #else
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUBTITLE_ATTACHEDFILE_BUFF_LEN,SUBTITLE_LEN);
    #endif
  #endif

#if( ENABLE_MM_XC_FBL_MODE )
    if(m_bVDPlayerPreview)
    {
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE_CHECKING, (U32)DISABLE); //disable FBL checking
    }
    else
    {
    #if( ENABLE_MM_HD_FB&&(MEMORY_MAP == MMAP_64MB))
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE_CHECKING, (U32)DISABLE); //disable FBL checking
    #else
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FBL_MODE_THRESHOLD, (U32)ENABLE_FBL_MODE_THRESHOLD); //set FBL threshold
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE_CHECKING, (U32)ENABLE); //enable FBL checking
        #if (ENABLE_HEVC_1080P50_FBL_MODE)
        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FBL_MODE_THRESHOLD_WITH_FRAMERATE, (U32)ENABLE); //enable FBL threshold with framerate
        #endif
    #endif
    }
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FBL_FORCE_PROGRESS,(U32)DISABLE); // disable force progress mode

    #ifdef VDEC_FRAMEBUFFER_SD_ADR
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_ADR_SD, ((VDEC_FRAMEBUFFER_SD_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_SD_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_FRAMEBUFFER_SD_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN_SD, VDEC_FRAMEBUFFER_SD_LEN);
    #else
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_ADR_SD, ((VDEC_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_FRAMEBUFFER_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_LEN_SD, VDEC_FRAMEBUFFER_LEN);
    #endif

    #ifdef VDEC_BITSTREAM_SD_ADR
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_ADR_SD, ((VDEC_BITSTREAM_SD_MEMORY_TYPE& MIU1) ? (VDEC_BITSTREAM_SD_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_BITSTREAM_SD_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_LEN_SD, VDEC_BITSTREAM_SD_LEN);
    #else
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_ADR_SD, ((VDEC_BITSTREAM_MEMORY_TYPE& MIU1) ? (VDEC_BITSTREAM_ADR|MIU_INTERVAL|SVD_USING_MIU1) : (VDEC_BITSTREAM_ADR)));
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_BITSTREAM_LEN_SD, VDEC_BITSTREAM_LEN);
    #endif

#else
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE_CHECKING, (U32)DISABLE); //disable FBL checking
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FBL_FORCE_PROGRESS,(U32)DISABLE); // disable force progress mode
#endif

    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPOS_LOW, 0);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPOS_HIGH, 0);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPTS, 0);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_AUDIO_TRACK_ID, 0);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_SUBTITLE_TRACK_ID, 0);
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_RESUME_PROGRAM_IDX, 0);

    for(i = 0; i < E_SHAREMEM_CUSTOMER_INFO_SIZE; i++)
    {
        U32 u32Info;
        u32Info = Customer_info[i*4] + (Customer_info[i*4 + 1] << 8) +
            (Customer_info[i*4 + 2] << 16) + (Customer_info[i*4 + 3] << 24);
        _Mapp_VDPlayer_SetShareMemData((EN_VDP_SHAREMEMORY)(E_SHAREMEM_CUSTOMER_INFO + i), u32Info);
    }

    for(i = 0; i < E_SHAREMEM_CUSTOMER_HASH_SIZE; i++)
    {
        U32 u32Hash;
        u32Hash = Customer_hash[i*4] + (Customer_hash[i*4 + 1] << 8) +
            (Customer_hash[i*4 + 2] << 16) + (Customer_hash[i*4 + 3] << 24);
        _Mapp_VDPlayer_SetShareMemData((EN_VDP_SHAREMEMORY)(E_SHAREMEM_CUSTOMER_HASH + i), u32Hash);
    }

    u32VDPlayerAudioSupportedFormat|=_MApp_VDPlayer_CheckSupportedAudio();
    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SUPPORTED_AUDIO, u32VDPlayerAudioSupportedFormat);

    msAPI_MVF_init_mempool((void*)_PA2VA(VDPLAYER_SUBTITLE_BITSTREAM_BUFF_ADR), VDPLAYER_SUBTITLE_BITSTREAM_BUFF_LEN);

    // Get long file name from file entry.
    u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                    pFileEntry,
                    (U32)(&u8FileName[0]),
                    (FILE_INFO_LONG_FILENAME_SIZE/2-1));
    u8Len = (u8Len > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
                    FILE_INFO_LONG_FILENAME_SIZE/2-1: u8Len;
    u8FileName[u8Len*2] = 0;
    u8FileName[u8Len*2+1] = 0;
    FS_Unicode2ASCII(&u16LongFileName[0]);
    VDPLAYER_DVD_DBG(printf("MApp_VDPlayer_DVD_Init -> name = %s, len = %d\n", (U8 *)&u16LongFileName[0], u8Len));

    MApp_DVD_Setup(DVD_SETUP_TYPE_FILENAME, &u16LongFileName[0]);

    u32Val = _PA2VA(u32VdplayerShareMemAddr + E_SHAREMEM_DRM_BUFF_ADDR * 4);
    MApp_DVD_Setup(DVD_SETUP_TYPE_SHAREMEMADDR, &u32Val);
    u32Val = _PA2VA(VDPLAYER_BITSTREAM_BUFF_ADR + 0x80000);
    MApp_DVD_Setup(DVD_SETUP_TYPE_BITSTREAMBUFADDR, &u32Val);
    u32Val = VDPLAYER_BITSTREAM_BUFF_LEN - 0x80000;
    MApp_DVD_Setup(DVD_SETUP_TYPE_BITSTREAMBUFLEN, &u32Val);

    MApp_DVD_Setup_Callback(GenericCallback);
    MApp_DVD_Setup_Mem_Callback(MemCallback_Malloc, MemCallback_Realloc, MemCallback_Free);
    MApp_DVD_Setup_IO_Callback(IoCallback_Open, IoCallback_Close, IoCallback_Seek, IoCallback_Read, IoCallback_Size);
    if (!MApp_DVD_Open())
    {
        VDPLAYER_DVD_DBG(printf("Error on MApp_DVD_Open\n"));
        enVDPlayerRet = EXIT_VDPLAYER_EXIT;
        return FALSE;
    }

    msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    //msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 300, MAIN_WINDOW); // DELAY_FOR_STABLE_CHANNELCHANGE);
    MDrv_MVOP_Enable(FALSE);

#if 1
    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_INIT;

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_DVD_INIT
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,8
    /*p1*/              ,(U8)(u32VdplayerShareMemAddr>>24)
    /*p2*/              ,(U8)(u32VdplayerShareMemAddr>>16)
    /*p3*/              ,(U8)(u32VdplayerShareMemAddr>>8)
    /*p4*/              ,(U8)(u32VdplayerShareMemAddr&0x000000FF)
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
    u8VDPlayerInitResult = FALSE;
    enVDPlayerRet = EXIT_VDPLAYER_DECODING;

    do
    {
        MApp_VDPlayer_MailBoxHandler();

        //Check USB connected directly
        if(!MApp_MPlayer_QueryCurrentDeviceIsConnected())
        {
            return FALSE;
        }

    }
    while((m_eVDPlayerAckFlags&E_ACKFLG_WAIT_INIT) &&
                (msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)<u32VDPlayer_init_timeout));

    // if init failed, close file and disable VOP
    if(u8VDPlayerInitResult == FALSE)
    {
        MApp_VDPlayer_Stop(); //fix preview next file it will show "un-support file" after abort(need to issue STOP CMD to co-processor)
//        _MApp_VDPlayer_Exit();
    }
    else
    {
      #if (VDPLAYER_CHECK_COPROCESSOR_STATUS)
        // If init successed, start to check AEON status
        u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
      #endif
    }

#else
    u8VDPlayerInitResult = TRUE;
    enVDPlayerRet = EXIT_VDPLAYER_DECODING;
#endif

    bIsDVD = TRUE;

    return u8VDPlayerInitResult;
}
#endif  // ENABLE_DVD

BOOLEAN MApp_VDPlayer_Play(void)
{
    U32 m_u32PlayTimer;
    m_eFailStatus = E_VDPLAYER_FAIL_STATUS_VDPLAYER_ERROR;

    if(bMovieAbort)
    {
        bMovieAbort = FALSE;
        return FALSE;
    }

#if ENABLE_DRM
    if(bDrmFileFormat == TRUE)
    {
        if(MApp_VDPlayer_CheckDRMAutuorization() == TRUE)
            MApp_VDPlayer_SaveDRMMemory();
    }
#endif

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_PLAY;
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_PLAY
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

#ifdef ENABLE_KTV
// KTV disable audio,so can't get message of removing E_ACKFLG_WAIT_PLAY
    if( g_InputSourceType == VIDEO_PLAYER_INPUT_SOURCE_KTV)
        m_eVDPlayerAckFlags &= (enumVDPlayerAckFlags)(~E_ACKFLG_WAIT_PLAY);
#endif

    m_u32PlayTimer = msAPI_Timer_GetTime0();
    while(m_eVDPlayerAckFlags&E_ACKFLG_WAIT_PLAY)
    {
       if (msAPI_Timer_DiffTimeFromNow(m_u32PlayTimer) > u8VDPlayerPlayTimeOut)
       {
           return FALSE;
       }

        if (_gpfnForceStopCallBack != NULL)
        {
            EN_VDPLAYER_FORCE_STOP_RESULT eRet = (*_gpfnForceStopCallBack)(E_FORCE_STOP_INIT);

            if (eRet != E_VDPLAYER_CONTINUE_PLAYING)
            {
                MApp_VDPlayer_Stop();

                if(eRet == E_VDPLAYER_USER_EXIT)
                {
                    m_eFailStatus = E_VDPLAYER_FAIL_STATUS_USER_EXIT;
                    return FALSE;
                }
                else if(eRet == E_VDPLAYER_ERROR_EXIT)
                {
                    return FALSE;
                }
            }
        }

       MApp_VDPlayer_MailBoxHandler();
    }

    /// Patch code when FD_mask was enabled.
    /// Send pause command when initial one stream(before VDPlayer_Play)
    /// The 1st displayed frame would be least 2 frames of previous stream . (Becaues the FD_mask)
    /// Add 150ms delay to display the frames of previous stream at blue screen.
    if (!MApi_XC_IsCurrentFrameBufferLessMode())
    {
        MsOS_DelayTask(150);
    }
    m_eFailStatus = E_VDPLAYER_FAIL_STATUS_NONE;
    return TRUE;
}

void MApp_VDPlayer_Stop(void)
{
    U8 i;
    U32 m_u32StopTimer;

#if ENABLE_LAST_MEMORY==1
    if (m_u8LastMemoryCheck==TRUE)
    {
        MApp_MPlayer_LastMemory_SetResumePlayAttribute(0);
        m_u8LastMemoryCheck=FALSE;
    }
#endif

#if (DISABLE_VE_VSIZE_CHECK)
    // We will always enable the VE check when STOP, and then disable it when Init.
    MS_BOOL bVSizeMinIs576 = TRUE;
    MVOP_Handle stMvopHd = { E_MVOP_MODULE_MAIN };

    MDrv_MVOP_SetCommand(&stMvopHd, E_MVOP_CMD_SET_VSIZE_MIN, &bVSizeMinIs576);
#endif // #if (DISABLE_VE_VSIZE_CHECK)

#if 0// DYNSCALING
    XC_DynamicScaling_Info stDS_Info;
    memset(&stDS_Info, 0, sizeof(XC_DynamicScaling_Info));
    stDS_Info.bOP_DS_On = FALSE;
    stDS_Info.bIPS_DS_On = FALSE;
    stDS_Info.bIPM_DS_On = FALSE;
    if(TRUE != MApi_XC_SetDynamicScaling(&stDS_Info, sizeof(XC_DynamicScaling_Info), MAIN_WINDOW))
    {
        printf("Set DS error\n");
    }
#endif
#if ENABLE_MVC
    if ((EN_VDP_CODECID) _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CODEC_ID) == E_VDP_CODEC_ID_MVCTS )
    {
        //1. close FRC mode to normal and close 3D mode.
        printf("close FRC mode to normal and close 3D mode.\n");
        SC_FRC_SETTING sFRC_Tbl_Temp[5] =
        {
             {0, 160, 1, 4, MS_FRC_1_4},
             {160, 245, 2, 5, MS_FRC_2_5},
             {245, 260, 1, 2, MS_FRC_1_2},
             {260, 400, 1, 2, MS_FRC_1_2},
             {400, 0xFFFF, 1, 1, MS_FRC_1_1},
        };

        MApi_XC_CustomizeFRCTable(sFRC_Tbl_Temp);
        MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_MODE_NONE,E_XC_3D_OUTPUT_FRAME_ALTERNATIVE,E_XC_3D_PANEL_NONE, MAIN_WINDOW);
    }
#endif

    if ((EN_VDP_CODECID) _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_CODEC_ID) == E_VDP_CODEC_ID_AAC
        ||(EN_VDP_CODECID) _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_CODEC_ID) == E_VDP_CODEC_ID_MPEG4AAC
        ||(EN_VDP_CODECID) _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_CODEC_ID) == E_VDP_CODEC_ID_RAAC
        ||(EN_VDP_CODECID) _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_CODEC_ID) == E_VDP_CODEC_ID_RACP
        )
    {
        MApi_AUDIO_SetAACInfo(Audio_AAC_mm_single_frame_mode, FALSE, 0);  //FALSE means AAC single frame
    }

    MApp_VDPlayer_StopThumbnail();

    // Disable scaler periodic task
    MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), DISABLE);
    //MDrv_PQ_MADiForceMotionY(PQ_MAIN_WINDOW, FALSE);

    //_MApp_VDPlayer_ClearShareMem();

    //no need to un-freeze when ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME is enabled
//    if(!m_bVDPlayerPreview)
//    {
        //fix PAUSE -> other play mode display abnormal.
//        #if SEAMLESS_PLAYING_ENABLE
//        if (!_bEnableSeamlessPlaying)
//        #endif
//            MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
//    }

    MApi_XC_set_FD_Mask(DISABLE);

#if (SUPPERTED_ADVERTISEMENT_MODE == DISABLE)
    _MApp_VDPlayer_SetScalerMemoryToDefault();
#endif

    if(_gbCoprocessorEnable==FALSE)
    {
        return;
    }
    _gbCoprocessorEnable = FALSE;

//move before cmd VDPLAYER stop to avoid screen has green garbage
#if SEAMLESS_PLAYING_ENABLE
    if (!_bEnableSeamlessPlaying || !MApi_XC_IsFreezeImg(MAIN_WINDOW))
#endif
    {
        MDrv_MVOP_Enable(FALSE);
        MDrv_MVOP_Exit();
    }

    {
        m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_STOP;
        //==> Send mail.
#if ENABLE_DIVX_PLUS
        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
        /*Index*/           ,MB_VDPLAYER_STOP
        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
        /*ParameterCount*/  ,0
        /*p1*/              ,0
        /*p2*/              ,0
        /*p3*/              ,0
        /*p4*/              ,0
        /*p5*/              ,0
        /*p6*/              ,0
        /*p7*/              ,0
        /*p8*/              ,0
        /*p9*/              ,0
        /*p10*/             ,0);


#else
        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
        /*Index*/           ,MB_VDPLAYER_STOP
        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
        /*ParameterCount*/  ,1
        /*p1*/              ,0
        /*p2*/              ,0
        /*p3*/              ,0
        /*p4*/              ,0
        /*p5*/              ,0
        /*p6*/              ,0
        /*p7*/              ,0
        /*p8*/              ,0
        /*p9*/              ,0
        /*p10*/             ,0);
#endif

        m_u32StopTimer = msAPI_Timer_GetTime0();
        while(m_eVDPlayerAckFlags & E_ACKFLG_WAIT_STOP)
        {
            if (msAPI_Timer_DiffTimeFromNow(m_u32StopTimer) > 2000)
            {
                msAPI_Timer_ResetWDT(); //prevent WDT

        #ifdef ENABLE_KTV
                if( g_InputSourceType != VIDEO_PLAYER_INPUT_SOURCE_KTV)
            #endif
                {
                #if( VD_PLAYER_IS_IN_CROP_CPU )
                    MApp_VDPlayer_LoadBinToCrop();
                    //Note:
                    //In co-processor side , it will do MApi_DMX_Init()/MApi_DMX_Exit() in each movie.
                    //XDemux will do MApi_DMX_Init() in xdemux init state , and do MApi_DMX_Exit() in xdemux stop state.
                    //In MApi_DMX_Init() , it will re-load TSP Firmware. In MApi_DMX_Exit() it will disable TSP.
                    //If Co-processor abnormal , we have to reload co-processor Firmware
                    //When reload co-processor Fireware during playing movie, co-processor will not do MApi_DMX_Exit()
                    //If co-processor not do MApi_DMX_Exit() then UI enter DTV mode , TSP will NOT re-load FW.
                    //This means TSP FW is still same which loaded by XDemux.
                    //This is a big problem , if DTV vs XDemux TSP Firmware is different.
                    //That is the reason , why we have to do MApi_DMX_ForceExit().
                    MApi_DMX_ForceExit();
#endif
                    msAPI_Timer_Delayms(20);
                    VDPLAYER_DBG(printf("Aeon abnormal, reset it\n"));
                }
                break;
            }

            MApp_VDPlayer_MailBoxHandler();
        }
    }
    //MDrv_COPRO_Disable();
#if ENABLE_NEW_FILE_HANDLER
    U8 u8Idx;
    for (u8Idx=0; u8Idx<TotalHandlerCnt; u8Idx++)
    {
        if (u32StreamHandleIdx[u8Idx] != INVALID_DATA_STREAM_HDL)
        {
            msAPI_DataStreamIO_Close(u32StreamHandleIdx[u8Idx]);
            u32StreamHandleIdx[u8Idx] = INVALID_DATA_STREAM_HDL;
        }

    }
#else
    if(u32VDPlayerStreamHandleIdx_Video!=INVALID_DATA_STREAM_HDL)
    {
        msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Video);
        u32VDPlayerStreamHandleIdx_Video = INVALID_DATA_STREAM_HDL;
    }

    if(u32VDPlayerStreamHandleIdx_Subtitle!=INVALID_DATA_STREAM_HDL)
    {
        msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Subtitle);
        u32VDPlayerStreamHandleIdx_Subtitle = INVALID_DATA_STREAM_HDL;
    }
#if ENABLE_AUDIO_HANDLER
    if(u32VDPlayerStreamHandleIdx_Audio!=INVALID_DATA_STREAM_HDL)
    {
        msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Audio);
        u32VDPlayerStreamHandleIdx_Audio = INVALID_DATA_STREAM_HDL;
    }
#endif
#if ENABLE_ATTACHMENT_HANDLER
    if(u32VDPlayerStreamHandleIdx_Attachment!=INVALID_DATA_STREAM_HDL)
    {
        msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Attachment);
        u32VDPlayerStreamHandleIdx_Attachment = INVALID_DATA_STREAM_HDL;
    }
#endif
#endif //ENABLE_NEW_FILE_HANDLER

#if ENABLE_HK_MP4
    close_mp4_resource(&stMP4);
    release_mp4_resource(&stMP4);
#endif

#if (SUPPERTED_SEAMLESS_SMOTH)
    MApp_VDPlayer_SetSeamlessSmoth(DISABLE);
#endif

    MApp_VDPlayer_StrmHandleAssignTblInit();

#ifdef _VDPLAYER_DUMP_RAW_
    if(VDPlayer_dump_id!=INVALID_FILE_HANDLE)
    {
        msAPI_FCtrl_FileClose(VDPlayer_dump_id);
        VDPlayer_dump_id = INVALID_FILE_HANDLE;
    }
#endif // _VDPLAYER_DUMP_RAW_

#if (TS_INTERNAL_SUBTITLE_BMP)
    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
    {
        BMP_DBG(printf("@@BMP stop\n"));
        MApp_VDPlayer_TS_SubtitleErase();

        u8InternalST_Num = 0;
        _bSubtitleShow_User = ENABLE;      // control by user.
        _bSubtitleShow_MW   = ENABLE;      // control by MW.
        u8IsSubtitleInitfinish = FALSE;
    }
#endif

#if (TS_INTERNAL_SUBTITLE_PGS)
    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
    {
        PGS_DBG(printf("@@PGS stop\n"));
        MApp_VDPlayer_TS_SubtitleErase();

        u8InternalST_Num = 0;
        _bSubtitleShow_User = ENABLE;      // control by user.
        _bSubtitleShow_MW   = ENABLE;      // control by MW.
        u8IsSubtitleInitfinish = FALSE;
    }
#endif

#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
    msAPI_MpegSP_Dinit();
#endif

    if (enVDPlayerVideoType == E_VDPLAYER_VIDEO_MJPEG)
    {
        #if (ENABLE_MIU_1 == ENABLE)
        MDrv_MVOP_MiuSwitch(1);
        #endif
    }

#if ENABLE_WMDRMPD
    if (MApp_VDPlayer_WMDRMPD_IsProtected())
    {
        MApp_WMDRMPD_Finalize();
    }
#endif

    _geBMStreamMode = E_BM_STREAM_MODE_NORMAL;
    _gbEnableInternalSubtitle = TRUE;
    //_gpfnForceStopCallBack = NULL;
    _gu16PreviewX = MOVIE_PREVIEW_X;
    _gu16PreviewY = MOVIE_PREVIEW_Y;
    _gu16PreviewWidth  = MOVIE_PREVIEW_WIDTH;
    _gu16PreviewHeight = MOVIE_PREVIEW_HEIGHT;
    _gbContinueBlockRead = FALSE;
    for (i = 0; i < (E_SHAREMEM_ESBUF_CTRL_TIMEOUT-E_SHAREMEM_BLOCK_FILEIO_TIMEOUT+1); i++)
    {
        m_u32CodecTimeOut[i] = 0;   //set default timeout
    }
#if (ENABLE_SMALL_BUF_SUBTITLE)
#if ENABLE_MPLAYER_MOVIE
    MApp_MPlayer_CloseSubtitleFileHandle();
#endif
#endif
}

#if ENABLE_DVD
void MApp_VDPlayer_DVD_Stop(void)
{
    U32 m_u32StopTimer;

    VDPLAYER_DVD_DBG(printf("MApp_VDPlayer_DVD_Stop ->\n"));

    MApp_DVD_Close();

    //no need to un-freeze when ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME is enabled
    if(!m_bVDPlayerPreview)
    {
        //fix PAUSE -> other play mode display abnormal.
//        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
    }

    _MApp_VDPlayer_SetScalerMemoryToDefault();

    if(_gbCoprocessorEnable==FALSE)
    {
        return;
    }

#if 1
    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_STOP;
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_STOP
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    m_u32StopTimer = msAPI_Timer_GetTime0();
    while(m_eVDPlayerAckFlags&E_ACKFLG_WAIT_STOP)
    {
        if (msAPI_Timer_DiffTimeFromNow(m_u32StopTimer) > 2000)
        {
            msAPI_Timer_ResetWDT(); //prevent WDT
    #ifdef ENABLE_KTV
            if( g_InputSourceType != VIDEO_PLAYER_INPUT_SOURCE_KTV)
        #endif
            {
            #if(VD_PLAYER_IS_IN_CROP_CPU)
                MApp_VDPlayer_LoadBinToCrop();
                //Note:
                //In co-processor side , it will do MApi_DMX_Init()/MApi_DMX_Exit() in each movie.
                //XDemux will do MApi_DMX_Init() in xdemux init state , and do MApi_DMX_Exit() in xdemux stop state.
                //In MApi_DMX_Init() , it will re-load TSP Firmware. In MApi_DMX_Exit() it will disable TSP.
                //If Co-processor abnormal , we have to reload co-processor Firmware
                //When reload co-processor Fireware during playing movie, co-processor will not do MApi_DMX_Exit()
                //If co-processor not do MApi_DMX_Exit() then UI enter DTV mode , TSP will NOT re-load FW.
                //This means TSP FW is still same which loaded by XDemux.
                //This is a big problem , if DTV vs XDemux TSP Firmware is different.
                //That is the reason , why we have to do MApi_DMX_ForceExit().
                MApi_DMX_ForceExit();
              #endif

                msAPI_Timer_Delayms(20);
                VDPLAYER_DBG(printf("Aeon abnormal, reset it\n"));
            }
            break;
        }

        MApp_VDPlayer_MailBoxHandler();
    }
#endif
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
    msAPI_MpegSP_Dinit();
#endif
    MDrv_MVOP_Enable(FALSE);

    _geBMStreamMode = E_BM_STREAM_MODE_NORMAL;
    _gbEnableInternalSubtitle = TRUE;
    //_gpfnForceStopCallBack = NULL;
    _gu16PreviewX = MOVIE_PREVIEW_X;
    _gu16PreviewY = MOVIE_PREVIEW_Y;
    _gu16PreviewWidth  = MOVIE_PREVIEW_WIDTH;
    _gu16PreviewHeight = MOVIE_PREVIEW_HEIGHT;
    _gbContinueBlockRead = FALSE;
}
#endif

void MApp_VDPlayer_StopAndCloseDisplay(void)
{
    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
    MApp_VDPlayer_Stop();
}

BOOLEAN MApp_VDPlayer_Pause(void)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_PAUSE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    {
        u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
        m_eVDPlayerAckFlags=(m_eVDPlayerAckFlags|E_ACKFLG_WAIT_PAUSE);
        do
        {
            VDPLAYER_DBG(printf("wait MApp_VDPlayer_SetTrickMode coprocessor ack ing... \n"));
            MApp_VDPlayer_MailBoxHandler();
        }
        while((m_eVDPlayerAckFlags&E_ACKFLG_WAIT_PAUSE) &&
            (msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)<5000));

        if (m_eVDPlayerAckFlags&E_ACKFLG_WAIT_PAUSE)
        {
            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_PAUSE);
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}


BOOLEAN MApp_VDPlayer_Resume(void)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_RESUME
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

#if ENABLE_DVD
    if (bIsDVD)
    {
        MApp_DVD_Resume();
    }
#endif

    return TRUE;
}

BOOLEAN MApp_VDPlayer_ChangeProgam(U8 u8ProgramIdx)
{
    u8ProgramIdx = u8ProgramIdx;

#if (TS_INTERNAL_SUBTITLE_BMP)
    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
    {
        BMP_DBG(printf("@@BMP ChangeProgram\n"));
    #if(ENABLE_API_MMAP_GET_BUF) // Use MMAP API
        U32 u32SubtitleBufAddr = 0, u32SubtitleBufSize = 0;
        msAPI_MMAP_Get_BufInfo(E_BUFID_SUBTITLE, &u32SubtitleBufAddr, &u32SubtitleBufSize );
        msAPI_Subtitle_Init_Queue(_PA2VA(u32SubtitleBufAddr), u32SubtitleBufSize);
    #else
        msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN); // clr Q
    #endif
        MApp_VDPlayer_TS_SubtitleErase();
    }
#endif

#if (TS_INTERNAL_SUBTITLE_PGS)
    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
    {
        PGS_DBG(printf("@@PGS ChangeProgram\n"));
    #if(ENABLE_API_MMAP_GET_BUF) // Use MMAP API
        U32 u32SubtitleBufAddr = 0, u32SubtitleBufSize = 0;
        msAPI_MMAP_Get_BufInfo(E_BUFID_SUBTITLE, &u32SubtitleBufAddr, &u32SubtitleBufSize );
        msAPI_Subtitle_Init_Queue(_PA2VA(u32SubtitleBufAddr), u32SubtitleBufSize);
    #else
        msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN); // clr Q
    #endif
        MApp_VDPlayer_TS_SubtitleErase();
    }
#endif

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_TS_SET_PROGRAM
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,(U8)u8ProgramIdx
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    {
        u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
        m_eVDPlayerAckFlags=(m_eVDPlayerAckFlags|E_ACKFLG_WAIT_TS_SET_PROGRAM);
        u8VDPlayerTsSetProgramResult = 0; // ack return value.
        do
        {
            //VDPLAYER_DBG(printf("1.wait MApp_VDPlayer_ChangeProgam coprocessor ack ing... \n"));
            MApp_VDPlayer_MailBoxHandler();
        }
        while((m_eVDPlayerAckFlags&E_ACKFLG_WAIT_TS_SET_PROGRAM) &&
            (msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer)<5000));

        if (m_eVDPlayerAckFlags&E_ACKFLG_WAIT_TS_SET_PROGRAM)
        {
            //VDPLAYER_DBG(printf("1.MApp_VDPlayer_ChangeProgam timeout!\n"));
            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_TS_SET_PROGRAM);
            return FALSE;
        }
        else if (u8VDPlayerTsSetProgramResult == 0)
        {
            //VDPLAYER_DBG(printf("1.MApp_VDPlayer_ChangeProgam return False!\n"));
            return FALSE;
        }
        else
        {
            //VDPLAYER_DBG(printf("1.MApp_VDPlayer_ChangeProgam return True!\n"));
            return TRUE;
        }
    }
    return FALSE;  //False: not change icon, True:change icon.
}


//-------------------------------------------------------------------------------------------------
///
/// APP functions
/// Processed by HK51.
///
//-------------------------------------------------------------------------------------------------
void MApp_VDPlayer_UartSwitch(U8 u8Switch)
{
#if (VDPLAYER_MSG_ON == 1)
    /*  set UART0_SEL to Co-Processor */
    if (u8Switch == E_UART_SWITCH_TO_COPROCESSOR)
    {
        if(!g_bOutputMMAliveMessage)
        {
            VDPLAYER_DBG(printf("Uart switch to Co-Processor\n"));
          #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)
            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
          #elif (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET)
            mdrv_uart_connect(E_UART_PORT0, E_UART_SECURE_R2);
          #else
            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);
          #endif
        }
    }
    else if(u8Switch == E_UART_SWITCH_TO_HK)
    {
        UNUSED(u8Switch);
     #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_M10) || \
          (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
          (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) || \
          (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER))
        mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
      #else
        mdrv_uart_connect(E_UART_PORT0, E_UART_PIU_UART0);
      #endif

        VDPLAYER_DBG(printf("Uart switch to HK\n"));
    }
    else if(u8Switch == E_UART_SWITCH_TO_VDEC)
    {
        UNUSED(u8Switch);
        VDPLAYER_DBG(printf("Uart switch to VDEC\n"));
        mdrv_uart_connect(E_UART_PORT0, E_UART_VDEC);
    }
    else
    {
        UNUSED(u8Switch);
        mdrv_uart_connect(E_UART_PORT0, E_UART_TSP); //tmp solution
        VDPLAYER_DBG(printf("Uart switch to OFF\n"));
    }
#else
    UNUSED(u8Switch);
#endif
}


U32 _MApp_VDPlayer_GetShareMemData(U16 idx_ptr)
{
    U32 idx_data = 0;
    U32 addr = (u32VdplayerShareMemAddr) + (idx_ptr << 2);

    if(u32VdplayerShareMemAddr!=0)
    {
        MsOS_ReadMemory();
        idx_data = *(U32 *)_PA2VA(addr) ;

        //return U32_SWAP(idx_data);
    }
    else
    {
        VDPLAYER_DBG(printf("error! u32VdplayerShareMemAddr=NULL\n"));
    }
    return idx_data;
}

void _Mapp_VDPlayer_SetShareMemData(U16 idx_ptr, U32 idx_data)
{
    U32 addr = (u32VdplayerShareMemAddr) + (idx_ptr << 2);

    if(u32VdplayerShareMemAddr!=0)
    {
        //*(U32 *)addr = U32_SWAP(idx_data);
        *(U32 *)_PA2VA(addr) = idx_data;

        //MsOS_Sync();
        MsOS_FlushMemory();
    }
    else
    {
        VDPLAYER_DBG(printf("error! u32VdplayerShareMemAddr=NULL\n"));
    }
}

U8 _MApp_VDPlayer_GetShareMemoryDataByByte(U16 idx_ptr)
{
    U8 ShareMemDataInfo = 0;
    U32 addr = (u32VdplayerShareMemAddr) + (idx_ptr);

    if(u32VdplayerShareMemAddr!=0)
    {
        MsOS_ReadMemory();
        ShareMemDataInfo = *(U8 *)_PA2VA(addr) ;
        //printf("get addr:%lx data:%bx",addr,ShareMemDataInfo);
    }
    else
    {
        VDPLAYER_DBG(printf("error! u32VdplayerShareMemAddr=NULL\n"));
    }

    return ShareMemDataInfo;
}

void _MApp_VDPlayer_SetShareMemoryDataByByte(U16 idx_ptr,U8 idx_data)
{
    U32 addr = (u32VdplayerShareMemAddr) + (idx_ptr);

    if(u32VdplayerShareMemAddr!=0)
    {
        //printf("set addr:%lx data:%bx\r\n",addr,idx_data);
        *(U8 *)_PA2VA(addr) = idx_data;

        //MsOS_Sync();
        MsOS_FlushMemory();
    }
    else
    {
        VDPLAYER_DBG(printf("error! u32VdplayerShareMemAddr=NULL\n"));
    }
}

void _MApp_VDPlayer_ClearShareMem(void)
{
    U32 addr, addr1;

    if(u32VdplayerShareMemAddr!=0)
    {
        for(addr=0;addr<E_SHAREMEM_NUM;addr++)
        {
            addr1 = (u32VdplayerShareMemAddr)+(addr<<2);
            *(U32 *)_PA2VA(addr1) = 0;
        }

        //MsOS_Sync();
        MsOS_FlushMemory();
    }
    else
    {
        VDPLAYER_DBG(printf("error! u32VdplayerShareMemAddr=NULL\n"));
    }
}

U32 MApp_VDPlayer_GetInfo(EN_VDPLAYER_INFO enInfo)
{
    switch(enInfo)
    {
        case E_VDPLAYER_INFO_TOTAL_TIME:
            if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_TIME_ISVALID))
            {
                return 0xffffffff;
            }
            else
            {
                return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_TIME);
            }
        case E_VDPLAYER_INFO_CUR_TIME:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_TIME);
        case E_VDPLAYER_INFO_FRM_PER_SEC:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAME_RATE);
        case E_VDPLAYER_INFO_DEMUX_FRM_RATE:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DEMUX_FRAME_RATE);
        case E_VDPLAYER_INFO_DEMUX_H_SIZE:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DEMUX_WIDTH);
        case E_VDPLAYER_INFO_DEMUX_V_SIZE:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DEMUX_HEIGHT);
        case E_VDPLAYER_INFO_H_SIZE:
            {
                U32 u32Width = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
                if(u32Width > (gstVidStatus.u16CropLeft + gstVidStatus.u16CropRight)
                    && (gstVidStatus.u16CropLeft + gstVidStatus.u16CropRight) > 0)
                {
                    u32Width -= (gstVidStatus.u16CropLeft + gstVidStatus.u16CropRight);
                }
                return u32Width;
            }
        case E_VDPLAYER_INFO_V_SIZE:
            {
                U32 u32Height = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT);
                if(u32Height > (gstVidStatus.u16CropTop + gstVidStatus.u16CropBottom)
                    && (gstVidStatus.u16CropTop + gstVidStatus.u16CropBottom) > 0)
                {
                    u32Height -= (gstVidStatus.u16CropTop + gstVidStatus.u16CropBottom);
                }
                return u32Height;
            }
        case E_VDPLAYER_INFO_NB_AUDIO_TRACK:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_AUDIO_TRACK);
        case E_VDPLAYER_INFO_AUDIO_TRACK_ID:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_AUDIO_TRACK_ID);
        case E_VDPLAYER_INFO_NB_SUBTITLE_TRACK:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_SUBTITLE);
        case E_VDPLAYER_INFO_SUBTITLE_TRACK_ID:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TRACK_ID);
        case E_VDPLAYER_INFO_CURRENT_SUBTITLE_TEXT:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TEXT);
        case E_VDPLAYER_INFO_CURRENT_SUBTITLE_TAGCOUNT:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT);
        case E_VDPLAYER_INFO_CURRENT_SUBTITLE_ISUNICODE:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_ISUNICODE);
    #if (ENABLE_DIVX_PLUS == 1)
        case E_VDPLAYER_INFO_NB_TITLE:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_TITLE);
        case E_VDPLAYER_INFO_NB_EDITION:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_EDITION);
        case E_VDPLAYER_INFO_NB_CHAPTER:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_CHAPTER);
    #endif
        case E_VDPLAYER_INFO_ERROR_INFO:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ERROR_INFO);
        case E_VDPLAYER_INFO_MAX_FB_SPEED:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_MAX_FAST_BACKWARD_SPEED);
        case E_VDPLAYER_INFO_PAR_H_SIZE:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_PAR_WIDTH);
        case E_VDPLAYER_INFO_PAR_V_SIZE:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_PAR_HEIGHT);
        case E_VDPLAYER_INFO_NB_PROGRAM:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TS_PROGRAM_NUM);
        case E_VDPLAYER_INFO_PROGRAM_ID:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TS_CUR_PROGRAM_IDX);
        case E_VDPLAYER_INFO_Audio_Request_Size:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_REQUEST_SIZE);
    #if ENABLE_DRM
        case E_VDPLAYER_INFO_DRM_FILE_FORMAT:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DRM_FILE_FORMAT);
        case E_VDPLAYER_INFO_DRM_RENTAL_EXPIRE_STATUS:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DRM_RENTAL_EXPIRE_STATUS);
        case E_VDPLAYER_INFO_DRM_AUTHORIZATION_STATUS:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DRM_AUTHORIZATION_STATUS);
        case E_VDPLAYER_INFO_DRM_RETURN_CODE:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DRM_RETURN_CODE);
        case E_VDPLAYER_INFO_DRM_RENTAL_FILE:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DRM_RENTAL_FILE);
        case E_VDPLAYER_INFO_DRM_RENTAL_USE_LIMIT:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DRM_RENTAL_USE_LIMIT);
        case E_VDPLAYER_INFO_DRM_RENTAL_USE_COUNT:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DRM_RENTAL_USE_COUNT);
    #endif
        case E_VDPLAYER_INFO_FRAMEINFO_WIDTH:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_WIDTH);
        case E_VDPLAYER_INFO_FRAMEINFO_HEIGHT:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_HEIGHT);
    #if ENABLE_LAST_MEMORY==1
        case E_VDPLAYER_INFO_RESUME_PLAY_SEEKPOS_LOW:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPOS_LOW);
        case E_VDPLAYER_INFO_RESUME_PLAY_SEEKPOS_HIGH:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPOS_HIGH);
        case E_VDPLAYER_INFO_RESUME_PLAY_SEEKPTS:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RESUME_PLAY_SEEKPTS);
        case E_VDPLAYER_INFO_RESUME_PLAY_PROGRAM_IDX:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RESUME_PROGRAM_IDX);
        case E_VDPLAYER_INFO_RESUME_PLAY_AUDIO_TRACK_ID:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RESUME_AUDIO_TRACK_ID);
        case E_VDPLAYER_INFO_RESUME_PLAY_SUBTITLE_TRACK_ID:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RESUME_SUBTITLE_TRACK_ID);
    #endif
        case E_VDPLAYER_INFO_CURRENT_PROGRAME_RATING:
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_PROGRAME_RATING);
        case E_VDPLAYER_INFO_VIDEO_CODEC:
            {
                U32 u32VideoCodecID =_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CODEC_ID);
                U32 u32VideoAttribute =u32VideoCodecID & E_VDP_CODEC_ATTRIBUTE_MASK;
                u32VideoAttribute &= (~E_VDP_CODEC_TS);
                U32 u32VideoType = E_VDPLAYER_VIDEO_UNKNOW;

                switch(u32VideoAttribute)
                {
                    case E_VDP_CODEC_MPG_VIDEO:
                        u32VideoType = E_VDPLAYER_VIDEO_MPG;
                        break;
                    case E_VDP_CODEC_MPEG4:
                        u32VideoType = E_VDPLAYER_VIDEO_MPEG4;
                        break;
                    case E_VDP_CODEC_VC1:
                        u32VideoType = E_VDPLAYER_VIDEO_VC1;
                        break;
                    case E_VDP_CODEC_FLV:
                        u32VideoType = E_VDPLAYER_VIDEO_FLV;
                        break;
                    case E_VDP_CODEC_H264:
                        if((u32VideoCodecID == E_VDP_CODEC_ID_AVS) ||
                           (u32VideoCodecID == E_VDP_CODEC_ID_AVSTS))
                        {
                            u32VideoType = E_VDPLAYER_VIDEO_AVS;
                        }
                        else if(u32VideoCodecID == E_VDP_CODEC_ID_MVCTS)
                        {
                            u32VideoType = E_VDPLAYER_VIDEO_MVC;
                        }
                        else
                        {
                            u32VideoType = E_VDPLAYER_VIDEO_H264;
                        }
                        break;
                    case E_VDP_CODEC_RM_VIDEO:
                        u32VideoType = E_VDPLAYER_VIDEO_RM;
                        break;
                    case E_VDP_CODEC_JPEG:
                        u32VideoType = E_VDPLAYER_VIDEO_MJPEG;
                        break;
                    case E_VDP_CODEC_VP6:
                        u32VideoType = E_VDPLAYER_VIDEO_VP6;
                        break;
                    case E_VDP_CODEC_VP8:
                        u32VideoType = E_VDPLAYER_VIDEO_VP8;
                        break;
                    default:
                        break;
                }
                return u32VideoType;
            }
            break;

        case E_VDPLAYER_INFO_AUDIO_CODEC:
            {
                U32 u32AudioCodecID =_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_CODEC_ID);
                U32 u32AudioType = E_VDPLAYER_AUDIO_UNKNOW;

                switch(u32AudioCodecID)
                {
                    case E_VDP_CODEC_ID_WMAV1:
                    case E_VDP_CODEC_ID_WMAV2:
                    case E_VDP_CODEC_ID_WMAV3:
                        u32AudioType = E_VDPLAYER_AUDIO_WMA;
                        break;
                    case E_VDP_CODEC_ID_DTS:
                        u32AudioType = E_VDPLAYER_AUDIO_DTS;
                        break;
                    case E_VDP_CODEC_ID_MP3:
                        u32AudioType = E_VDPLAYER_AUDIO_MP3;
                        break;
                    case E_VDP_CODEC_ID_MP2:
                        u32AudioType = E_VDPLAYER_AUDIO_MPEG;
                        break;
                    case E_VDP_CODEC_ID_AC3:
                        u32AudioType = E_VDPLAYER_AUDIO_AC3;
                        break;
                    case E_VDP_CODEC_ID_EAC3:
                        u32AudioType = E_VDPLAYER_AUDIO_AC3_PLUS;
                        break;
                    case E_VDP_CODEC_ID_AAC:
                    case E_VDP_CODEC_ID_MPEG4AAC:
                        u32AudioType = E_VDPLAYER_AUDIO_AAC;
                        break;
                    case E_VDP_CODEC_ID_FLAC:
                        u32AudioType = E_VDPLAYER_AUDIO_FLAC;
                        break;
                    case E_VDP_CODEC_ID_PCM_S16LE:
                    case E_VDP_CODEC_ID_PCM_S16BE:
                    case E_VDP_CODEC_ID_PCM_U16LE:
                    case E_VDP_CODEC_ID_PCM_U16BE:
                    case E_VDP_CODEC_ID_PCM_S8:
                    case E_VDP_CODEC_ID_PCM_U8:
                    case E_VDP_CODEC_ID_PCM_MULAW:
                    case E_VDP_CODEC_ID_PCM_ALAW:
                        u32AudioType = E_VDPLAYER_AUDIO_PCM;
                        break;

                    case E_VDP_CODEC_ID_ADPCM_IMA_QT:
                    case E_VDP_CODEC_ID_ADPCM_IMA_WAV:
                    case E_VDP_CODEC_ID_ADPCM_IMA_DK3:
                    case E_VDP_CODEC_ID_ADPCM_IMA_DK4:
                    case E_VDP_CODEC_ID_ADPCM_IMA_WS:
                    case E_VDP_CODEC_ID_ADPCM_IMA_SMJPEG:
                    case E_VDP_CODEC_ID_ADPCM_MS:
                    case E_VDP_CODEC_ID_ADPCM_4XM:
                    case E_VDP_CODEC_ID_ADPCM_XA:
                    case E_VDP_CODEC_ID_ADPCM_ADX:
                    case E_VDP_CODEC_ID_ADPCM_EA:
                    case E_VDP_CODEC_ID_ADPCM_G726:
                        u32AudioType = E_VDPLAYER_AUDIO_ADPCM;
                        break;
                    case E_VDP_CODEC_ID_RAAC:
                    case E_VDP_CODEC_ID_RACP:
                        u32AudioType = E_VDPLAYER_AUDIO_RAAC;
                        break;
                    case E_VDP_CODEC_ID_COOK:
                        u32AudioType = E_VDPLAYER_AUDIO_COOK;
                        break;
                    case E_VDP_CODEC_ID_VORBIS:
                        u32AudioType = E_VDPLAYER_AUDIO_VORBIS;
                        break;
                    case E_VDP_CODEC_ID_AMR_NB:
                        u32AudioType = E_VDPLAYER_AUDIO_AMR_NB;
                        break;
                    case E_VDP_CODEC_ID_AMR_WB:
                        u32AudioType = E_VDPLAYER_AUDIO_AMR_WB;
                        break;
                    case E_VDP_CODEC_ID_DRA:
                        u32AudioType = E_VDPLAYER_AUDIO_DRA;
                        break;
                    default:
                        u32AudioType = E_VDPLAYER_AUDIO_UNKNOW;
                        break;
                }
                return u32AudioType;
            }
            break;
        case E_VDPLAYER_INFO_AUDIO_LANGUAGE:
            {
                U32 u32CurAudioTrack = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_AUDIO_TRACK_ID);
                return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_LANGUAGE+u32CurAudioTrack);
            }
            break;
        case E_VDPLAYER_INFO_SUBTITLE_LANGUAGE:
            {
                U32 u32CurSubtitleTrack = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TRACK_ID);
                return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_SUBTITLE_LANGUAGE+u32CurSubtitleTrack);
            }
            break;
        case E_VDPLAYER_INFO_AUDIO_CHANNEL:
            {
                return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_CHANNEL_CONFIGURATION);
            }
            break;
        case E_VDPLAYER_INFO_PLAY_MODE:
            {
                return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_PLAY_MODE);
            }
            break;
        case E_VDPLAYER_INFO_PLAY_SPEED:
            {
                return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_PLAY_SPEED);
            }
            break;
        default:
            return 0;
    }
}

void MApp_VDPlayer_EnableVideoOnly(BOOLEAN bEnable)
{
    if(bEnable)
    {
        VDPLAYER_DBG(printf("enable video only mode\n"));
    }
    else
    {
        VDPLAYER_DBG(printf("disable video only mode\n"));
    }
    _bEnableVideoOnly = bEnable;
}

void msAPI_VDPlayer_ScreenDisplaySetting( EN_VDPLAYER_SCREEN_SETTINGS type , U8 value, U16 delay)
{
    switch(type)
    {
    case E_SCREEN_SETTINGS_SCALER_BLUESCREEN:
      #if SEAMLESS_PLAYING_ENABLE
        if (!_bEnableSeamlessPlaying || !MApi_XC_IsFreezeImg(MAIN_WINDOW))
      #endif
        {
            if( value == FALSE )
            {

                msAPI_Scaler_SetBlueScreen( DISABLE,E_XC_FREE_RUN_COLOR_BLACK,  delay, MAIN_WINDOW);
            }
            else if( value == TRUE )
            {
                msAPI_Scaler_SetBlueScreen( ENABLE,E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            }
        }
        break;
    case E_SCREEN_SETTINGS_SCALER_FREEZESCREEN:
//        if( value == FALSE )
//        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
//        else if( value == TRUE )
//        MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
        break;
    case E_SCREEN_SETTINGS_SCALER_ACE_PATCHTRICKMODE:
        //if( value == FALSE )
        //MApi_XC_Sys_PQ_PatchFastPlayback(MAIN_WINDOW, FALSE, FALSE);
        //else if( value == TRUE )
        //MApi_XC_Sys_PQ_PatchFastPlayback(MAIN_WINDOW,TRUE, FALSE);
        break;
    case E_SCREEN_SETTINGS_SCALER_ACE_FILMMODE    :
//[TODO] enable it later
//        if( value == FALSE )
//        msAPI_ACE_RestoreFilmMode();
//        else if( value == TRUE )
//        msAPI_ACE_DisableFilmMode();
        break;
    case E_SCREEN_SETTINGS_SCALER_PQ_Y_MOTION:
        if( value == FALSE )
        {
            //MDrv_PQ_MADiForceMotionY(PQ_MAIN_WINDOW, FALSE);
        }
        else if( value == TRUE )
        {
            //MDrv_PQ_MADiForceMotionY(PQ_MAIN_WINDOW, TRUE);
        }
        break;
    case E_SCREEN_SETTINGS_NONE:
    default:
        break;
    }

}

void MApp_VDPlayer_GetMVOPBlackSize(U32 width, U32 Height, U32* p_black_width , U32* p_black_height)
{
    U32 u32modifiedH,u32modifiedV;
    MS_WINDOW_TYPE stDisplayWin = {0, 0, PANEL_WIDTH, PANEL_HEIGHT};

    // Get source ratio by PAR
    MApp_VDPlayer_AdjustRatioByPAR(width , Height,
                                   MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_PAR_H_SIZE) ,
                                   MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_PAR_V_SIZE),
                                   &u32modifiedH, &u32modifiedV,stDisplayWin);

    if (((float)devPanel_WIDTH()/u32modifiedH)>((float)devPanel_HEIGHT()/u32modifiedV))
    {
        //VDPLAYER_DBG(printf("\n left-right black"));
        * p_black_height=0;
        * p_black_width= ((float)(devPanel_WIDTH()-(u32modifiedH*((float)devPanel_HEIGHT()/u32modifiedV)))/((float)devPanel_HEIGHT()/u32modifiedV)) / 2;
        //VDPLAYER_DBG(printf("\n mvideo_pnl_get_height()=%u, mvideo_pnl_get_width()=%u\n",devPanel_HEIGHT(), devPanel_WIDTH()));
        //VDPLAYER_DBG(printf("\n Height=%lu,  width=%lu\n",Height, width));
    }
    else
    {
        //VDPLAYER_DBG(printf("\n top-down black"));
        * p_black_width=0;
        * p_black_height= ((float)((devPanel_HEIGHT()-((u32modifiedV*(((float)devPanel_WIDTH())/u32modifiedH)))))/(((float)devPanel_WIDTH()/u32modifiedH))) / 2;
        //* p_black_height= (((devPanel_HEIGHT()-((Height*((devPanel_WIDTH()*1000)/width))/1000))*1000)/((devPanel_WIDTH()*1000/width)/1000))/1000;
        //VDPLAYER_DBG(printf("\n mvideo_pnl_get_height()=%u, mvideo_pnl_get_width()=%u\n",devPanel_HEIGHT(), devPanel_WIDTH()));
        //VDPLAYER_DBG(printf("\n Height=%lu,  width=%lu\n",Height, width));
        //VDPLAYER_DBG(printf("\n (Height*(mvideo_pnl_get_width()/width))=%lu",(U32)(Height*(((float)devPanel_WIDTH()*1000)/width))/1000));
        //VDPLAYER_DBG(printf("\n (mvideo_pnl_get_width()/width)=%lu",(U32)(((float)devPanel_WIDTH()*1000)/width)/1000));
    }
}

void MApp_VDPlayer_GetMVOPBlackSizeOnDest(U32 width, U32 Height, U32* p_black_width , U32* p_black_height)
{
    if (((float)devPanel_WIDTH()/width)>((float)devPanel_HEIGHT()/Height))
    {
        //printf("\n left-right black");
        * p_black_height=0;
        * p_black_width= ((float)(devPanel_WIDTH()-(width*((float)devPanel_HEIGHT()/Height))))/2;
    }
    else
    {
        //printf("\n top-down black");
        * p_black_width=0;
        * p_black_height= ((float)((devPanel_HEIGHT()-((Height*((float)devPanel_WIDTH()/width))))))/2;
        //* p_black_height= (((devPanel_HEIGHT()-((Height*((devPanel_WIDTH()*1000)/width))/1000))*1000)/((devPanel_WIDTH()*1000/width)/1000))/1000;
        //printf("\n mvideo_pnl_get_height()=%u ,, mvideo_pnl_get_width()=%u",devPanel_HEIGHT(), devPanel_WIDTH());
        //printf("\n Height=%lu,  width=%lu",Height, width);
        //printf("\n (Height*(mvideo_pnl_get_width()/width))=%lu",(U32)(Height*(((float)devPanel_WIDTH()*1000)/width))/1000);
        //printf("\n (mvideo_pnl_get_width()/width)=%lu",(U32)(((float)devPanel_WIDTH()*1000)/width)/1000);
    }
}

static void _MApp_VDPlayer_GetVDPlayerInfo(U16 *u16Width, U16 *u16Height)
{
    *u16Width = (U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_H_SIZE);
    *u16Height = (U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_V_SIZE);
}

static void _MApp_VDPlayer_CalCropDisplayWin(MS_WINDOW_TYPE *ptCropWin, MS_WINDOW_TYPE *ptDstWin, VDPLAYER_ZOOM_FACT eZoom,MS_WINDOW_TYPE stDisplayWin)
{
    U8 u8numerator = 1;
    U8 u8denominator = 1;
    U32 u32HSize = 0;
    U32 u32HStart = 0;
    U32 u32VSize = 0;
    U32 u32VStart = 0;
    U32 u32modifiedH,u32modifiedV;
    U32 u32Temp;
    U32 u32HRatio, u32VRatio;

    U16 u16Width = 0;
    U16 u16Height = 0;

    //check ptImageWin value
    if(stDisplayWin.height==0)
    {
        stDisplayWin.height= (U16)PANEL_HEIGHT;
    }
    if(stDisplayWin.width==0)
    {
        stDisplayWin.width= (U16)PANEL_WIDTH;
    }

    switch (eZoom)
    {
    case VDPLAYER_ZOOM_FACT_1_DIV_4:
    case VDPLAYER_ZOOM_FACT_1_DIV_2:
    case VDPLAYER_ZOOM_FACT_NORMAL:
        u8numerator = 1;
        u8denominator = 1;
        break;
    case VDPLAYER_ZOOM_FACT_2X:
        u8numerator = 5;
        u8denominator = 7;
        break;
    case VDPLAYER_ZOOM_FACT_4X:
        u8numerator = 1;
        u8denominator = 2;
        break;
    case VDPLAYER_ZOOM_FACT_8X:
        u8numerator = 5;
        u8denominator = 14;
        break;
    default:
        break;
    }

    _MApp_VDPlayer_GetVDPlayerInfo(&u16Width,  &u16Height);
    //printf("  ZOOM: u16Width=%x ,  u16Height=%x \n", u16Width, u16Height);

    // Get source ratio by PAR
    MApp_VDPlayer_AdjustRatioByPAR(u16Width , u16Height,
                                   MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_PAR_H_SIZE) ,
                                   MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_PAR_V_SIZE),
                                   &u32modifiedH, &u32modifiedV,stDisplayWin);
    //printf("  u32modifiedH=%x ,  u32modifiedV=%x\n", u32modifiedH, u32modifiedV);

#if 0
    if ((u8numerator == 1) && (u8denominator == 1))
    {
        u16HSize = u16Width;
        u16VSize = u16Height;
        u16HStart = 0;
        u16VStart = 0;
    }
    else
    {
        u16HSize = ((u16Width*u8numerator)/u8denominator);
        u16HSize = (u16HSize>>1)<<1;
        u16VSize = ((u16Height*u8numerator)/u8denominator);
        u16VSize = ((u16VSize>>1)<<1);

        u16HStart = (((u16Width*(u8denominator - u8numerator))/u8denominator)>>2)<<1;
        u16VStart = (((u16Height*(u8denominator - u8numerator))/u8denominator)>>2)<<1;
    }

    tCropWin.x = u16HStart;
    tCropWin.y = u16VStart;
    tCropWin.width = u16HSize;
    tCropWin.height = u16VSize;
#else
    if ((u8numerator == 1) && (u8denominator == 1))
    {
        u32HSize = u32modifiedH;
        u32VSize = u32modifiedV;
        //u16HStart = 0;
        //u16VStart = 0;
    }
    else
    {
        u32HSize = ((u32modifiedH*u8numerator)/u8denominator);
        //u16HSize = (u16HSize>>1)<<1;
        u32VSize = ((u32modifiedV*u8numerator)/u8denominator);
        //u16VSize = ((u16VSize>>1)<<1);

        //u16HStart = (((u16modifiedH*(u8denominator - u8numerator))/u8denominator)>>2)<<1;
        //u16VStart = (((u16modifiedV*(u8denominator - u8numerator))/u8denominator)>>2)<<1;
    }

    //printf("\n u16HSize=%d ", u32HSize);
    //printf("\n u16VSize=%d ", u32VSize);
    //printf("\n u16HStart=%d ", u32HStart);
    //printf("\n u16VStart=%d ", u32VStart);

    //tCropWin.x = u16HStart;
    //tCropWin.y = u16VStart;
    //tCropWin.width = u16HSize;
    //tCropWin.height = u16VSize;

    // Mapping crop ratio into really source ratio.
    ptCropWin->width = ( (U32)u16Width * (U32)u32HSize ) / ( (U32) u32modifiedH );
    ptCropWin->height = ( (U32)u16Height * (U32)u32VSize ) / ( (U32) u32modifiedV );

    // Boundary check
    if ( u16Width >= ptCropWin->width )
    {
        ptCropWin->x = ( u16Width - ptCropWin->width ) / 2 ;
    }
    else
    {
        ptCropWin->x = 0;
    }
    // Boundary check
    if ( u16Height >= ptCropWin->height )
    {
        ptCropWin->y = ( u16Height - ptCropWin->height ) / 2;
    }
    else
    {
        ptCropWin->y = 0;
    }

    //ptCropWin->x = (ptCropWin->x >> 1) << 1;
#endif

    // Stretch source to panel size and keep it ratio.
    ptDstWin->width = u32modifiedH;
    ptDstWin->height = u32modifiedV;

    ptDstWin->x = stDisplayWin.x;
    ptDstWin->y = stDisplayWin.y;

    u32Temp = ( (U32)ptDstWin->width * 1000) / ptDstWin->height ;


    if ( u32Temp  >=  ( ( (U32)stDisplayWin.width * 1000 )/ stDisplayWin.height)  )
    {
        // Keep width information
        ptDstWin->height = ( (U32)ptDstWin->height * stDisplayWin.width ) / ptDstWin->width;
        // Boundary check
        if ( ptDstWin->height < stDisplayWin.height )
            ptDstWin->y += ( stDisplayWin.height   -  ptDstWin->height ) / 2 ;
        ptDstWin->width = stDisplayWin.width;
    }
    else
    {
        ptDstWin->width = ( (U32)ptDstWin->width * stDisplayWin.height ) / ptDstWin->height;
        // Boundary check
        if ( stDisplayWin.width > ptDstWin->width )
            ptDstWin->x += ( stDisplayWin.width   -   ptDstWin->width ) / 2 ;
        ptDstWin->height = stDisplayWin.height;
        // 2 Alignment
        ptDstWin->x = (ptDstWin->x >> 1) << 1;
    }

    switch (eZoom)
    {
    case VDPLAYER_ZOOM_FACT_1_DIV_4:
     #if 1 // For post scaling down issue
        u32HSize = (((U32)ptDstWin->width * 66 / 100) >> 1) << 1;
        u32VSize = (((U32)ptDstWin->height * 66 / 100) >> 1) << 1;
     #else
        u32HSize = ((ptDstWin->width * 1 / 2) >> 1) << 1;
        u32VSize = ((ptDstWin->height * 1 / 2) >> 1) << 1;
     #endif
        u32HStart = (stDisplayWin.width - u32HSize) >> 1;
        u32VStart = (stDisplayWin.height - u32VSize) >> 1;
        //msAPI_Scaler_SetCustomerDisplayWindow(TRUE, u16HStart, u16VStart, u16HSize, u16VSize);
        ptDstWin->x = u32HStart;
        ptDstWin->y = u32VStart;
        ptDstWin->width = u32HSize;
        ptDstWin->height = u32VSize;
        break;

    case VDPLAYER_ZOOM_FACT_1_DIV_2:
     #if 1 // For post scaling down issue
        u32HSize = (((U32)ptDstWin->width * 83 / 100) >> 1) << 1;
        u32VSize = (((U32)ptDstWin->height * 83 / 100) >> 1) << 1;
     #else
        u32HSize = ((ptDstWin->width * 5 / 7) >> 1) << 1;
        u32VSize = ((ptDstWin->height * 5 / 7) >> 1) << 1;
     #endif
        u32HStart = (stDisplayWin.width - u32HSize) >> 1;
        u32VStart = (stDisplayWin.height - u32VSize) >> 1;
        //msAPI_Scaler_SetCustomerDisplayWindow(TRUE, u16HStart, u16VStart, u16HSize, u16VSize);
        ptDstWin->x = u32HStart;
        ptDstWin->y = u32VStart;
        ptDstWin->width = u32HSize;
        ptDstWin->height = u32VSize;
        break;

    case VDPLAYER_ZOOM_FACT_2X:
    case VDPLAYER_ZOOM_FACT_4X:
    case VDPLAYER_ZOOM_FACT_8X:
        u32HRatio = (u32modifiedH * u16Height) / 100;
        u32VRatio = (u32modifiedV * u16Width) / 100;
        if(ptDstWin->width == stDisplayWin.width)
        {
            u32Temp = (u16Height * (U32)stDisplayWin.width) / ptCropWin->width;
            u32Temp = (u32Temp * u32VRatio) / u32HRatio;
            if(u32Temp <= stDisplayWin.height)
            {
                ptCropWin->y = 0;
                ptCropWin->height = (U16)u16Height;

                ptDstWin->height = (u32Temp >> 1) << 1;
                ptDstWin->y = ((stDisplayWin.height - ptDstWin->height) >> 1); //<<1;
            }
            else
            {
                ptCropWin->height = ((U32)stDisplayWin.height * (U32)ptCropWin->width) / stDisplayWin.width;
                ptCropWin->height = ((U32)ptCropWin->height * u32HRatio) / u32VRatio;
                ptCropWin->y = (u16Height - ptCropWin->height) >> 1;

                ptDstWin->y = 0;
                ptDstWin->height = stDisplayWin.height;
            }
        }
        else if(ptDstWin->height == stDisplayWin.height)
        {
            u32Temp = (u16Width * (U32)stDisplayWin.height) / ptCropWin->height;
            u32Temp = (u32Temp * u32HRatio) / (u32VRatio);
            if(u32Temp <= stDisplayWin.width)
            {
                ptCropWin->x = 0;
                ptCropWin->width = (U16)u16Width;

                ptDstWin->width = (u32Temp >> 1) << 1;
                ptDstWin->x = (((stDisplayWin.width - ptDstWin->width) - 1) >> 1); //<<1;
            }
            else
            {
                ptCropWin->width = ((U32)stDisplayWin.width * (U32)ptCropWin->height) / stDisplayWin.height;
                ptCropWin->width = ((U32)ptCropWin->width * u32VRatio) / u32HRatio;
                ptCropWin->x = (u16Width - ptCropWin->width) >> 1;

                ptDstWin->x = 0;
                ptDstWin->width = stDisplayWin.width;
            }
        }

    default:
        break;
    }

    // printf("2. Crop X: %d, Y: %d, W: %d, H: %d.\n", ptCropWin->x, ptCropWin->y, ptCropWin->width, ptCropWin->height);
    // printf("2. Disp X: %d, Y: %d, W: %d, H: %d.\n", ptDstWin->x, ptDstWin->y, ptDstWin->width, ptDstWin->height);

}

static void _MApp_VDPlayer_ProcessBlockingRead(void)
{
    U32 read_size;

    read_size = msAPI_DataStreamIO_Read(_gu32gStreamHdl, (void *)_gu32BuffAddr, _gu32ResidualReadSize);
    MsOS_FlushMemory();

    if(read_size != 0) //need continue read in next loop
    {
        _gu32BuffAddr = _gu32BuffAddr + _gu32ResidualReadSize - read_size;
        _gu32ResidualReadSize = read_size;
        _gbContinueBlockRead = TRUE;
    }
    else   //finish blocking read, send ack msg
    {
        _bStreamSeeked = FALSE;
        _gbContinueBlockRead = FALSE;
        //==> Send mail.
        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
        /*ParameterCount*/  ,6
        /*p1*/              ,MB_VDPLAYER_FILE_READ
        /*p2*/              ,(U8)((read_size&0xFF000000)>>24)
        /*p3*/              ,(U8)((read_size&0x00FF0000)>>16)
        /*p4*/              ,(U8)((read_size&0x0000FF00)>>8)
        /*p5*/              ,(U8)(read_size&0x000000FF)
        /*p6*/              ,_gu32gStreamHdl
        /*p7*/              ,0
        /*p8*/              ,0
        /*p9*/              ,0
        /*p10*/             ,0);
    }
}

void MApp_VDPlayer_SetQuarterPixel(XC_SETWIN_INFO* pstXC_SetWin_Info)
{
    if(enVDPlayerVideoType == E_VDPLAYER_VIDEO_H264) // MM
    {
        if(pstXC_SetWin_Info->bPreHCusScaling && (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_H_SIZE) >= 1200))   // 1 DDR H.264 Deblocking/Quarter Pixel Off
        {
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_SETBALANCEBW, 0x0101FF00);
        }
    }
}

#if DYNSCALING
void MApp_VDPlayer_SetVirtualBox(XC_SETWIN_INFO* pstXC_SetWin_Info, MS_WINDOW_TYPE *ptSrcWin, MS_WINDOW_TYPE *ptDstWin)
{
    if(ptSrcWin == NULL)
    {
        ds_dbg(printf("!!!ERROR SetVB without SrcWin!!!\n"));
        return;
    }

    if(ptDstWin == NULL)
    {
        ds_dbg(printf("!!!ERROR SetVB without DstWin!!!\n"));
        return;
    }

    if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING)==1)
    {
        pstXC_SetWin_Info->bHCusScaling = FALSE;
        //pstXC_SetWin_Info->u16HCusScalingSrc = DYNAMIC_SCALING_VB_H;//pstXC_SetWin_Info->stCapWin.width;
        //pstXC_SetWin_Info->u16HCusScalingDst = ptDstWin->width;

        pstXC_SetWin_Info->bVCusScaling = FALSE;
        //pstXC_SetWin_Info->u16VCusScalingSrc = DYNAMIC_SCALING_VB_V;//pstXC_SetWin_Info->stCapWin.height;
        //pstXC_SetWin_Info->u16VCusScalingDst = ptDstWin->height;

        pstXC_SetWin_Info->bPreHCusScaling = TRUE;
        pstXC_SetWin_Info->u16PreHCusScalingSrc = DYNAMIC_SCALING_VB_H;
        pstXC_SetWin_Info->u16PreHCusScalingDst = DYNAMIC_SCALING_VB_H;

        pstXC_SetWin_Info->bPreVCusScaling = TRUE;
        pstXC_SetWin_Info->u16PreVCusScalingSrc = DYNAMIC_SCALING_VB_V;

        //printf("[DBG] ptDstWin->height = %d, pstXC_SetWin_Info->stCapWin.height = %d, ptSrcWin->height = %d, gstVidStatus.u16CropBottom = %d\n"
        //    , ptDstWin->height, pstXC_SetWin_Info->stCapWin.height, ptSrcWin->height, gstVidStatus.u16CropBottom);
        // force vertical pre-scaling down
        if(ptDstWin->height > DYNAMIC_SCALING_VB_V)
        {
            pstXC_SetWin_Info->u16PreVCusScalingDst = ptDstWin->height;//DYNAMIC_SCALING_VB_V;
        }
        else
        {
            //pstXC_SetWin_Info->u16PreVCusScalingDst = pstXC_SetWin_Info->stCapWin.height- 1;
            pstXC_SetWin_Info->u16PreVCusScalingDst = (ptSrcWin->height - gstVidStatus.u16CropBottom) - 1;
            //printf("[DBG] (ptSrcWin->height - gstVidStatus.u16CropBottom) = %d\n", (ptSrcWin->height - gstVidStatus.u16CropBottom));
        }

        //printf("=================\n");
        //printf("==========DYNAMIC_SCALING_VB_V %d=======\n",DYNAMIC_SCALING_VB_V);
    }
}

static void _MApp_VDPlayer_SendZoomInfo2Firmware(U32 u32FM_Buf_Base, MS_WINDOW_TYPE *stNewCropWin, MS_WINDOW_TYPE *stNewDispWin, SCALER_WIN eWin)
{
    UNUSED(eWin);

    MM_DS_XC_STATUS *pstMMDS_Status;

    ds_dbg(printf("_MApp_VDPlayer_SendZoomInfo2Firmware %x\n", u32FM_Buf_Base));

    // direct write to shared memory with firmware
    //pstMMDS_Status = (MM_DS_XC_STATUS *) MsOS_PA2KSEG1(u32FM_Buf_Base + (1024*3));
    pstMMDS_Status = (MM_DS_XC_STATUS *) MsOS_PA2KSEG1(u32FM_Buf_Base);

    // copy scaler related information
    pstMMDS_Status->bFWGotNewSetting = FALSE;
    pstMMDS_Status->bHKIsUpdating = TRUE;
    MsOS_FlushMemory();

    pstMMDS_Status->stNewCropWin.x      = stNewCropWin->x;
    pstMMDS_Status->stNewCropWin.y      = stNewCropWin->y;
    pstMMDS_Status->stNewCropWin.width  = stNewCropWin->width;
    pstMMDS_Status->stNewCropWin.height = stNewCropWin->height;

    pstMMDS_Status->stNewDispWin.x      = stNewDispWin->x;
    pstMMDS_Status->stNewDispWin.y      = stNewDispWin->y;
    pstMMDS_Status->stNewDispWin.width  = stNewDispWin->width;
    pstMMDS_Status->stNewDispWin.height = stNewDispWin->height;

    ds_dbg(printf("NewCrop %d, %d, %d, %d\n", pstMMDS_Status->stNewCropWin.x, pstMMDS_Status->stNewCropWin.y,
        pstMMDS_Status->stNewCropWin.width, pstMMDS_Status->stNewCropWin.height));
    ds_dbg(printf("NewDisp %d, %d, %d, %d\n", pstMMDS_Status->stNewDispWin.x, pstMMDS_Status->stNewDispWin.y,
        pstMMDS_Status->stNewDispWin.width, pstMMDS_Status->stNewDispWin.height));

    pstMMDS_Status->bHKIsUpdating = FALSE;
    MsOS_FlushMemory();

    MApp_VDPlayer_DS_UpdateXCStatus(MM_DS_XC_CMD_UPDATE_ZOOM_INFO);
}

static void _MApp_VDPlayer_SendXCStatus2Firmware(U32 u32FM_Buf_Base, SCALER_WIN eWin)
{
    XC_ApiStatus stXCStatus;
    MM_DS_XC_STATUS *pstMMDS_Status;

    ds_dbg(printf("_MApp_VDPlayer_SendXCStatus2Firmware %x\n", u32FM_Buf_Base));

    // direct write to shared memory with firmware
    pstMMDS_Status = (MM_DS_XC_STATUS *) MsOS_PA2KSEG1(u32FM_Buf_Base);

    // get scaler information
    MApi_XC_GetStatus(&stXCStatus, eWin);

    // copy scaler related information
    while(pstMMDS_Status->bFWIsUpdating);
    pstMMDS_Status->bFWGotXCInfo = FALSE;
    pstMMDS_Status->bHKIsUpdating = TRUE;
    MsOS_FlushMemory();

    //memcpy(&pstMMDS_Status->stCapWin, &stXCStatus.stCapWin, sizeof(MS_WINDOW_TYPE));
    //memcpy(&pstMMDS_Status->stCropWin, &stXCStatus.stCropWin, sizeof(MS_WINDOW_TYPE));

    stXCStatus.stCapWin.height = DYNAMIC_SCALING_VB_V;
    stXCStatus.stCapWin.width = DYNAMIC_SCALING_VB_H;
    stXCStatus.stCropWin.height = DYNAMIC_SCALING_VB_V;
    stXCStatus.stCropWin.width = DYNAMIC_SCALING_VB_H;

    memcpy(&pstMMDS_Status->stCapWin, &stXCStatus.stCapWin, sizeof(MS_WINDOW_TYPE));
    memcpy(&pstMMDS_Status->stCropWin, &stXCStatus.stCropWin, sizeof(MS_WINDOW_TYPE));
    memcpy(&pstMMDS_Status->stDispWin, &stXCStatus.stDispWin, sizeof(MS_WINDOW_TYPE));

    pstMMDS_Status->u16H_SizeAfterPreScaling = stXCStatus.u16H_SizeAfterPreScaling;
    pstMMDS_Status->u16V_SizeAfterPreScaling = stXCStatus.u16V_SizeAfterPreScaling;
    ds_dbg(printf("before modify u32IPMBase0 %lx,u32IPMBase1 %lx,u32IPMBase2, %lx---\n",
           pstMMDS_Status->u32IPMBase0,pstMMDS_Status->u32IPMBase1,pstMMDS_Status->u32IPMBase2));

    if(MApi_XC_GetMirrorModeType())
    {
        pstMMDS_Status->u32IPMBase0 = stXCStatus.u32IPMBase0 - MApi_XC_Get_DNRBaseOffset(eWin);
        pstMMDS_Status->u32IPMBase1 = stXCStatus.u32IPMBase1 - MApi_XC_Get_DNRBaseOffset(eWin);
        pstMMDS_Status->u32IPMBase2 = stXCStatus.u32IPMBase2 - MApi_XC_Get_DNRBaseOffset(eWin);
    }
    else
    {
    pstMMDS_Status->u32IPMBase0 = stXCStatus.u32IPMBase0;
    pstMMDS_Status->u32IPMBase1 = stXCStatus.u32IPMBase1;
    pstMMDS_Status->u32IPMBase2 = stXCStatus.u32IPMBase2;
    }

    pstMMDS_Status->bLinearMode = stXCStatus.bLinearMode;
    pstMMDS_Status->u8BitPerPixel = stXCStatus.u8BitPerPixel;
    pstMMDS_Status->bInterlace = stXCStatus.bInterlace;
    pstMMDS_Status->bMirrorMode = MApi_XC_GetMirrorModeType();
    pstMMDS_Status->u16IPMOffset = stXCStatus.u16IPMOffset;

    ds_dbg(printf("Cap  %d, %d, %d, %d\n", pstMMDS_Status->stCapWin.x, pstMMDS_Status->stCapWin.y,
        pstMMDS_Status->stCapWin.width, pstMMDS_Status->stCapWin.height));
    ds_dbg(printf("Crop %d, %d, %d, %d\n", pstMMDS_Status->stCropWin.x, pstMMDS_Status->stCropWin.y,
        pstMMDS_Status->stCropWin.width, pstMMDS_Status->stCropWin.height));
    ds_dbg(printf("Disp %d, %d, %d, %d\n", pstMMDS_Status->stDispWin.x, pstMMDS_Status->stDispWin.y,
        pstMMDS_Status->stDispWin.width, pstMMDS_Status->stDispWin.height));

    ds_dbg(printf("IPMBase 0/1/2 = %x, %x, %x\n", pstMMDS_Status->u32IPMBase0,
        pstMMDS_Status->u32IPMBase1, pstMMDS_Status->u32IPMBase2));
    ds_dbg(printf("Linear %d, Bit/Pixel %d, Interlace %d\n", pstMMDS_Status->bLinearMode,
        pstMMDS_Status->u8BitPerPixel, pstMMDS_Status->bInterlace));

    pstMMDS_Status->bHKIsUpdating = FALSE;
    MsOS_FlushMemory();

    MApp_VDPlayer_DS_UpdateXCStatus(MM_DS_XC_CMD_UPDATE_XC_INFO);
/*
    while(pstMMDS_Status->bFWGotXCInfo!= TRUE)
    {
        MsOS_FlushMemory();
        //printf("FWIsUpdating %d\n", pstMMDS_Status->bFWIsUpdating);
    }
*/
}
#endif

static void _MApp_VDPlayer_ScaleScalerWindows(VDPLAYER_ZOOM_FACT eZoom, BOOLEAN bIsFirstTimeSetup)
{
    MS_WINDOW_TYPE tCapWin, tCropWin, tDstWin;

    memset(&tCapWin, 0, sizeof(tCapWin));
    memset(&tCropWin, 0, sizeof(tCropWin));
    memset(&tDstWin, 0, sizeof(tDstWin));

    MS_WINDOW_TYPE stDisplayWin = {0, 0, PANEL_WIDTH, PANEL_HEIGHT};

    _MApp_VDPlayer_CalCropDisplayWin(&tCropWin, &tDstWin, eZoom,stDisplayWin);

#if DYNSCALING
    if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING)==1)
    {
        if(bIsFirstTimeSetup)
        {
            tCapWin.x = MDrv_MVOP_GetHStart();
            tCapWin.y = MDrv_MVOP_GetVStart();
            tCapWin.width =  _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
            tCapWin.height = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT);
            MApp_Scaler_SetWindow(&tCapWin,  &tCropWin, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                                                   SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW); //?? aspect ration??
            //_MApp_VDPlayer_SendXCStatus2Firmware(
            //    _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DYNSCALING_ADDRESS) + (1024*3), MAIN_WINDOW);
        }
        else
        {
            MS_WINDOW_TYPE stDispWin;

            stDispWin.x = tDstWin.x + g_IPanel.HStart();
            stDispWin.y = tDstWin.y + g_IPanel.VStart();
            stDispWin.width = tDstWin.width;
            stDispWin.height = tDstWin.height;
            MApi_XC_SetDispWinToReg(&stDispWin, MAIN_WINDOW);

            ds_dbg(printf("---crop before recaluate x=%d, y=%d, w=%d, h=%d\n", tCropWin.x, tCropWin.y, tCropWin.width, tCropWin.height));
            tCropWin.width = (MS_U16)DYNAMIC_SCALING_VB_H*tCropWin.width/_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
            tCropWin.x = (MS_U16)DYNAMIC_SCALING_VB_H*tCropWin.x/_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);

            ds_dbg(printf("----[DBG] (V, crop_h, h, crop_b) (%d,%d,%d,%d)\n", DYNAMIC_SCALING_VB_V, tCropWin.height, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT), _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_BOTTOM)));

            tCropWin.height = (MS_U16)DYNAMIC_SCALING_VB_V* tCropWin.height/(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT) - _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_BOTTOM));
            tCropWin.y = (MS_U16)DYNAMIC_SCALING_VB_V* tCropWin.y/(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT) - _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_BOTTOM));

            ds_dbg(printf("---crop after reclauate x=%d, y=%d, w=%d, h=%d\n", tCropWin.x, tCropWin.y, tCropWin.width, tCropWin.height));
            ds_dbg(printf("---decoded, w=%d, h=%d\n", _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH), _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT)));

            // if screen mute disabled, change zoom info only
            _MApp_VDPlayer_SendZoomInfo2Firmware(
                _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DYNSCALING_ADDRESS) + (1024*3),
                &tCropWin, &tDstWin, MAIN_WINDOW);
        }
    }
    else
#endif
    {

    /*
        MS_WINDOW_TYPE *pDispWin, *pCropWin;

        pCropWin = &tCropWin;
        pDispWin = &tDstWin;

        // Get Crop Win
        printf("VDP:CropWin:X=0x%X,Y=0x%X, W=%d, H=%d\n", pCropWin->x, pCropWin->y, pCropWin->width, pCropWin->height);

        // Get Display Win
        printf("VDP:DispWin:X=0x%X,Y=0x%X, W=%d, H=%d\n", pDispWin->x, pDispWin->y, pDispWin->width, pDispWin->height);
    */
        MApp_Scaler_SetWindow(NULL,  &tCropWin, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                              SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW); //?? aspect ration??
    }
    UNUSED(bIsFirstTimeSetup);
}

void _MApp_VDPlayer_SetupDisplayPath(U8 u8VideoType,
        U16 u16Width, U16 u16Height,  //--> VDPlayerInfo.u16Width, VDPlayerInfo.u16Height
        U16 u16DisplayX, U16 u16DisplayY, // --> u16VDPlayerDisplayInfoX, u16VDPlayerDisplayInfoY
        U16 u16DisplayWidth, U16 u16DisplayHeight, U32 u32BuffAddr, // --> u16VDPlayerDisplayInfoWidth, u16VDPlayerDisplayInfoHeight
        U8 u8TSStream)
{
    MVOP_Timing stMVOPTiming;
    MVOP_VidStat stMvopVidSt;
    XC_SetTiming_Info stTimingInfo;

    UNUSED(u8TSStream);
    g_enVDPlayerVideoType = (EN_VDPLAYER_VIDEO_TYPE)u8VideoType;


#if (FBL_ZOOM==1)
    g_bForceToFB = FALSE;
#endif

#if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
    MS_WINDOW_TYPE tSrcWin;
    MVOP_InputCfg dc_param;
    memset(&tSrcWin, 0, sizeof(MS_WINDOW_TYPE));
    memset(&dc_param, 0, sizeof(MVOP_InputCfg));

    g_bApplyMVOPCrop = FALSE;
    g_u16HorOffset = 0;
    g_u16VerOffset = 0;

    if((u8VideoType == E_VDPLAYER_VIDEO_VC1) || (u8VideoType == E_VDPLAYER_VIDEO_FLV))
    {
        enMVOPVideoType = MVOP_MPG;
    }
    else if(u8VideoType == E_VDPLAYER_VIDEO_AVS)
    {
        enMVOPVideoType = MVOP_H264;
    }
    else
    {
        enMVOPVideoType = (MVOP_VIDEO_TYPE)u8VideoType;
    }
#endif

#if DYNSCALING
    XC_DynamicScaling_Info stDS_Info;
    memset(&stDS_Info, 0, sizeof(XC_DynamicScaling_Info));

    if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING)==1)
    {
        stDS_Info.u32DS_Info_BaseAddr = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DYNSCALING_ADDRESS); //pDispinfo->u32DynScalingAdd;
        stDS_Info.u8MIU_Select =_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DYNSCALING_MIUSEL);  //pDispinfo->bEnableMIUSel;
        stDS_Info.u8DS_Index_Depth = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DYNSCALING_DEPTH); //pDispinfo->u8DynScalingDepth;
        stDS_Info.bOP_DS_On = TRUE;
        stDS_Info.bIPS_DS_On = FALSE;
        stDS_Info.bIPM_DS_On = TRUE;
    }
    else
    {
        stDS_Info.bOP_DS_On = FALSE;
        stDS_Info.bIPS_DS_On = FALSE;
        stDS_Info.bIPM_DS_On = FALSE;
    }

    //printf("\n DS:IP on %d, OP on %d, depth=%d\n", stDS_Info.bIPM_DS_On, stDS_Info.bOP_DS_On, stDS_Info.u8DS_Index_Depth);

    if(TRUE != MApi_XC_SetDynamicScaling(&stDS_Info, sizeof(XC_DynamicScaling_Info), MAIN_WINDOW))
    {
        printf("Set DS error\n");
    }

    if(stDS_Info.bOP_DS_On)
    {
        MDrv_PQ_SetDS_OnOFF(PQ_MAIN_WINDOW,  TRUE);
    }
    else
    {
        MDrv_PQ_SetDS_OnOFF(PQ_MAIN_WINDOW,  FALSE);
    }
#endif // #if DYNSCALING

    if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_RANGE) == 1)
    {
        MDrv_PQ_SetSelectCSC(1, PQ_MAIN_WINDOW);
    }
    else
    {
        MDrv_PQ_SetSelectCSC(0, PQ_MAIN_WINDOW);
    }

    if(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAME_RATE)<22000)
    {
        gstVidStatus.u32FrameRate = 30000;
    }
    else
    {
        gstVidStatus.u32FrameRate = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAME_RATE);
    }

    gstVidStatus.u8Interlace = _MApp_VDPlayer_GetInterlace();
    gstVidStatus.u16HorSize =  _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
    gstVidStatus.u16VerSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT);
    //printf("MM: %ux%u %lu%s\n", gstVidStatus.u16HorSize, gstVidStatus.u16VerSize, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAME_RATE),
           //(gstVidStatus.u8Interlace)? "i":"p");
    u16Width =  gstVidStatus.u16HorSize;
    u16Height = gstVidStatus.u16VerSize;

    MDrv_MVOP_Init();
#if (MJPEG_HARDWARE_MODE_ENABLED == DISABLE)
    if (u8VideoType == E_VDPLAYER_VIDEO_MJPEG)
    {
        MVOP_InputCfg dc_param1;
        //MS_SYS_INFO enMsSysInfo;

        memset(&dc_param1, 0, sizeof(MVOP_InputCfg));
        // Enable Blue Screen
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);

        //Refine: When we enter MM, input source type already be set to INPUT_SOURCE_STORAGE and
        //          msAPI_Scaler_SetSourceType() was called. So, we don't need to set source type again.
#if 0
        // set Scaler input source
        SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) = INPUT_SOURCE_STORAGE;
        g_enDataInputSourceType[MAIN_WINDOW] = DATA_INPUT_SOURCE_STORAGE;
        enMsSysInfo.enInputSourceType = INPUT_SOURCE_STORAGE;
        enMsSysInfo.enAspectRatio = VIDEOSCREEN_NORMAL;
        msAPI_Scaler_SetSourceType(enMsSysInfo.enInputSourceType);
#endif
        // set mvop parameters
        MDrv_MVOP_EnableBlackBG();
        dc_param1.u16HSize = u16Width;
        dc_param1.u16VSize = u16Height;
        dc_param1.u32YOffset = u32BuffAddr;
        dc_param1.u32UVOffset = dc_param.u32YOffset+ 8; //No Use, in MDrv_VOP_Input_Mode, it will be reset
        dc_param1.bSD = 1;
        dc_param1.bYUV422 = 1;
        dc_param1.bProgressive = 1;
        dc_param1.bUV7bit = 0;
        dc_param1.bDramRdContd = 1;
        dc_param1.bField = 0;
        dc_param1.b422pack = 1;
        dc_param1.u16StripSize = dc_param1.u16HSize;
        MDrv_MVOP_SetInputCfg(MVOP_INPUT_DRAM, &dc_param1);

        gstVidStatus.u8AspectRate = ASP_4TO3;   //ASP_16TO9;
    }
#endif // #if (MJPEG_HARDWARE_MODE_ENABLED == DISABLE)
#if (MirrorEnable)
    MApp_MVOP_SetMirrorMode(ENABLE);
#endif

#if (ENABLE_MM_XC_FBL_MODE)
    if (u8TSStream)
    {
        /// Disable it for program change
        MApi_XC_EnableFrameBufferLess(DISABLE);
    }

    if ((m_eVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW) != E_VDPLAYER_FLG_PREVIEW)
    {
        if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE) == (U32)ENABLE_FBL_MODE)
        {
            MApi_XC_EnableFrameBufferLess(ENABLE);
        }
    #if( ENABLE_MM_HD_FB && (MEMORY_MAP == MMAP_64MB) )
        MApi_XC_EnableFrameBufferLess(DISABLE);
    #endif
    }
#endif // #if (ENABLE_MM_XC_FBL_MODE)

#if (MM_1080I_USE_FB)
    if((u16Width>=1920||u16Height>=1080) && _MApp_VDPlayer_GetInterlace())
    {
        printf("\r\n AUS 1080i MM USE FB!\n");
        MApi_XC_EnableFrameBufferLess(DISABLE);
    }
#endif

    if(MApi_XC_IsCurrentFrameBufferLessMode()) //Bright@20080905 FBL
    {
        //printf(" FBL=1\n");
        MApi_XC_set_FD_Mask(DISABLE);
/*
        if(((gstVidStatus.u32FrameRate > 24500)&&(gstVidStatus.u32FrameRate <= 25000)) ||((gstVidStatus.u32FrameRate > 49500)&&(gstVidStatus.u32FrameRate <= 50000)))
            gstVidStatus.u32FrameRate = 25000;
        else
            gstVidStatus.u32FrameRate = 30000;
*/
        if((gstVidStatus.u32FrameRate > 24500)&&(gstVidStatus.u32FrameRate <= 25000))
        {
            //stVidStatus.u32FrameRate = 25000;
        }
        else if((gstVidStatus.u32FrameRate > 49500)&&(gstVidStatus.u32FrameRate <= 50000))
        {
            gstVidStatus.u32FrameRate=gstVidStatus.u32FrameRate/2; //25
        }
        else if((gstVidStatus.u32FrameRate > 23500)&&(gstVidStatus.u32FrameRate <= 24000) )
        {
            gstVidStatus.u32FrameRate = (U32)gstVidStatus.u32FrameRate*5/4; //30
        }
        else if((gstVidStatus.u32FrameRate > 29500)&&(gstVidStatus.u32FrameRate <= 30000))
        {
            //~30
        }
        else
        {
            gstVidStatus.u32FrameRate = 30000;
        }

        if (gstVidStatus.u8Interlace == FALSE)   // progressive
        {
            gstVidStatus.u32FrameRate *= 2;
        }

#if (MM_1080I_USE_FB)
    if((u16Width>=1920||u16Height>=1080) && !_MApp_VDPlayer_GetInterlace())
    {
        if(gstVidStatus.u32FrameRate == 25000 || gstVidStatus.u32FrameRate == 50000)
        {
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FRC_OUTPUT_FORMAT, (U32)50);
        }
        else
        {
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_FRC_OUTPUT_FORMAT, (U32)60);
        }
    }
#endif



    }
    else
    {
        //printf(" FBL=0\n");

        MApi_XC_set_FD_Mask(ENABLE);
        if ((u8VideoType == E_VDPLAYER_VIDEO_RM)
#if (VDPLAYER_MVOP_REAL_FRAMERATE == DISABLE)
            || (!u8TSStream)
#endif // #if (VDPLAYER_MVOP_REAL_FRAMERATE == DISABLE)
            )
        {
            if (((U32)u16Width*(U32)u16Height >= 1300UL*1080UL) || (gstVidStatus.u8Interlace == TRUE))
                gstVidStatus.u32FrameRate = 30000;
            else
                gstVidStatus.u32FrameRate = 60000;
        }

#if (VDPLAYER_VERIFY_SCALER_FPGA)
        if (gstVidStatus.u8Interlace)
            gstVidStatus.u32FrameRate = VDPLAYER_VSYNC_RATE * 500;
        else
            gstVidStatus.u32FrameRate = VDPLAYER_VSYNC_RATE * 1000;
#endif
    }

#if ENABLE_DVD
    if (bIsDVD)
        MApi_XC_set_FD_Mask(DISABLE);
#endif

    memset(&stMvopVidSt, 0, sizeof(MVOP_VidStat));
    // Crop Info
    gstVidStatus.u16CropRight  = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_RIGHT);
    gstVidStatus.u16CropLeft   = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_LEFT);
    gstVidStatus.u16CropBottom = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_BOTTOM);
    gstVidStatus.u16CropTop    = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_TOP);

  #if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
    if(MApi_XC_IsCurrentFrameBufferLessMode())
    {
        MApp_Scaler_Adjust_AspectRatio_FBL(stSystemInfo[MAIN_WINDOW].enAspectRatio, &tSrcWin);
        U16 u16VDE = gstVidStatus.u16VerSize - (gstVidStatus.u16CropTop + gstVidStatus.u16CropBottom) + 2 * g_u16VerOffset;
        MApp_Scaler_SetFixVtotal(gstVidStatus.u8Interlace, (U16)gstVidStatus.u32FrameRate, u16VDE);
        stMvopVidSt.u16HorOffset = g_u16HorOffset;
        stMvopVidSt.u16VerOffset = g_u16VerOffset;
    }
  #endif

  #if DYNSCALING
    if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING)==1)
    {
        stMvopVidSt.u16HorSize   =DYNAMIC_SCALING_VB_H;
        stMvopVidSt.u16VerSize   =DYNAMIC_SCALING_VB_V;
    }
    else
  #endif
    {
        stMvopVidSt.u16HorSize   = gstVidStatus.u16HorSize;
        stMvopVidSt.u16VerSize   = gstVidStatus.u16VerSize;
    }
    stMvopVidSt.u16FrameRate = gstVidStatus.u32FrameRate;
    stMvopVidSt.u8AspectRate = gstVidStatus.u8AspectRate;
    stMvopVidSt.u8Interlace  = gstVidStatus.u8Interlace;

  #if !ENABLE_FBL_ASPECT_RATIO_BY_MVOP
    if (MApi_XC_IsCurrentFrameBufferLessMode())
    {
        U32 u32MVOP_Black_Width = 0;
        U32 u32MVOP_Black_Height = 0;
        //for FBL set MVOP for maintain video ratio
        MApp_VDPlayer_GetMVOPBlackSize((U32)u16Width, (U32)u16Height, &u32MVOP_Black_Width, &u32MVOP_Black_Height);
        VDPLAYER_DBG(printf("\n w=%u, h=%u,  black_W=%lu, black_H=%lu \n",u16Width, u16Height, u32MVOP_Black_Width, u32MVOP_Black_Height));
        stMvopVidSt.u16HorOffset = u32MVOP_Black_Width;
        stMvopVidSt.u16VerOffset = u32MVOP_Black_Height;
    }
    else
    {
        stMvopVidSt.u16HorOffset = 0;
        stMvopVidSt.u16VerOffset = 0;
    }
  #endif

    if(MApi_XC_IsCurrentFrameBufferLessMode() && ((stMvopVidSt.u16HorOffset > 0) || (stMvopVidSt.u16VerOffset > 0)))
    {
        if ( !MDrv_MVOP_CheckCapability(stMvopVidSt.u16HorSize + stMvopVidSt.u16HorOffset * 2,
                                        stMvopVidSt.u16VerSize + stMvopVidSt.u16VerOffset * 2,
                                        stMvopVidSt.u16FrameRate / 1000) )
        {
            VDPLAYER_DBG(printf("MVOP can not support this large timing and reset offset!\n");)
            stMvopVidSt.u16HorOffset = 0;
            stMvopVidSt.u16VerOffset = 0;
        }
    }

    // MVOP setting flow start:
    // 1. MDrv_MVOP_SetInputCfg

    switch (u8VideoType)
    {
        case E_VDPLAYER_VIDEO_MPEG4:
        case E_VDPLAYER_VIDEO_MPG:
        case E_VDPLAYER_VIDEO_VC1:
          #if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
            if(MApi_XC_IsCurrentFrameBufferLessMode() && g_bApplyMVOPCrop)
            {
                dc_param.u16CropWidth = tSrcWin.width;
                dc_param.u16CropHeight = tSrcWin.height;
                dc_param.u16CropX = tSrcWin.x;
                dc_param.u16CropY = tSrcWin.y;
                dc_param.enVideoType = MVOP_MPG;
              #if (VIDEO_FIRMWARE_CODE >= VIDEO_FIRMWARE_CODE_HD)
                dc_param.u16StripSize = 1920;
              #else
                dc_param.u16StripSize = 720;
              #endif
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &dc_param);
            }
            else
          #endif
            {
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_MVD, NULL);
            }
            break;

        case E_VDPLAYER_VIDEO_H264:
        case E_VDPLAYER_VIDEO_AVS:
          #if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
            if (MApi_XC_IsCurrentFrameBufferLessMode() && g_bApplyMVOPCrop)
            {
                dc_param.u16CropWidth = tSrcWin.width;
                dc_param.u16CropHeight = tSrcWin.height;
                dc_param.u16CropX = tSrcWin.x;
                dc_param.u16CropY = tSrcWin.y;
                dc_param.enVideoType = MVOP_H264;
                dc_param.u16StripSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &dc_param);
            }
            else
          #endif
            {
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_H264, NULL);
            }
            break;
        case E_VDPLAYER_VIDEO_HEVC:
            {
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_EVD, NULL);
            }
            break;
#if ENABLE_MVC
        case E_VDPLAYER_VIDEO_MVC:
            {
                SC_FRC_SETTING sFRC_Tbl_Temp[5] =
                {
                    {0, 160, 1, 4, MS_FRC_1_4},
                    {160, 245, 1, 2, MS_FRC_1_2},
                    {245, 260, 1, 2, MS_FRC_1_2},
                    {260, 400, 1, 2, MS_FRC_1_2},
                    {400, 0xFFFF, 1, 1, MS_FRC_1_1},
                };

                printf(" ********************** Setting for MVC ****************************\n");
                MApi_XC_CustomizeFRCTable(sFRC_Tbl_Temp);
                if(gstVidStatus.u32FrameRate < 30000)
                    MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING,E_XC_3D_OUTPUT_FRAME_ALTERNATIVE,E_XC_3D_PANEL_NONE, MAIN_WINDOW);
                //else
                //    MApi_XC_Set_3D_Mode(E_XC_3D_INPUT_FRAME_PACKING,E_XC_3D_OUTPUT_TOP_BOTTOM,E_XC_3D_PANEL_NONE, MAIN_WINDOW);

                MDrv_MVOP_SetInputCfg(MVOP_INPUT_HVD_3DLR, NULL);
            }
            break;
#endif
        case E_VDPLAYER_VIDEO_RM:
          #if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
            if (MApi_XC_IsCurrentFrameBufferLessMode() && g_bApplyMVOPCrop)
            {
                dc_param.u16CropWidth = tSrcWin.width;
                dc_param.u16CropHeight = tSrcWin.height;
                dc_param.u16CropX = tSrcWin.x;
                dc_param.u16CropY = tSrcWin.y;
                dc_param.enVideoType = MVOP_RM;
                dc_param.u16StripSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &dc_param);
            }
            else
          #endif
            {
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_RVD, NULL);
            }
            break;

        case E_VDPLAYER_VIDEO_MJPEG:
          #if (MJPEG_HARDWARE_MODE_ENABLED)
            UNUSED(u16DisplayX);
            UNUSED(u16DisplayY);
            UNUSED(u16DisplayWidth);
            UNUSED(u16DisplayHeight);
            UNUSED(u32BuffAddr);

            MDrv_MVOP_SetInputCfg(MVOP_INPUT_JPD, NULL);
            break;

          #else // #if (MJPEG_HARDWARE_MODE_ENABLED)
            {
                U16 displayX, displayY, displayHSize, displayVSize;
                MS_WINDOW_TYPE tDstWin;
                S32 s32QuotientDiff, s32RemainderDiff;

                // set scaling aspect to program
                // [071017 Andy] set to original aspect
                stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_ORIGIN;

                if(m_eVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW)
                {
                    u16DisplayX = _gu16PreviewX;
                    u16DisplayY = _gu16PreviewY;
                    u16DisplayWidth  = _gu16PreviewWidth;
                    u16DisplayHeight = _gu16PreviewHeight;
                }

                // Set to the original aspect ratio
                s32QuotientDiff = ((((U32)u16DisplayWidth * 32) / (U32)u16DisplayHeight) - (((U32)u16Width * 32) / (U32)u16Height));
                s32RemainderDiff = ((((U32)u16DisplayWidth * 32) % (U32)u16DisplayHeight) - (((U32)u16Width * 32) % (U32)u16Height));
                // Set to the original aspect ratio
                if ( (s32QuotientDiff > 0)
                  || ((s32QuotientDiff == 0) && (s32RemainderDiff > 0)) )
                {
                    // Height major
                    displayHSize = (U16)(((U32)u16DisplayHeight * 32 / (U32)u16Height) *
                                          (U32)u16Width / 32) & 0xFFFE;
                    displayX = u16DisplayX + (u16DisplayWidth - displayHSize) / 2;
                    displayY = u16DisplayY;
                    displayVSize = u16DisplayHeight;
                }
                else
                {
                    // Width major
                    displayVSize = (U16)(((U32)u16DisplayWidth * 32 / (U32)u16Width) *
                                          (U32)u16Height / 32) & 0xFFFE;
                    displayY = u16DisplayY + (u16DisplayHeight - displayVSize) / 2;
                    displayX = u16DisplayX;
                    displayHSize = u16DisplayWidth;
                }

                {
                    tDstWin.x = displayX;
                    tDstWin.y = displayY;
                    tDstWin.width = displayHSize;
                    tDstWin.height = displayVSize;

                    MApp_Scaler_EnableOverScan(FALSE);
                    g_DstWin = tDstWin;
                    MApp_Scaler_SetWindow(NULL, NULL, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                                          SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                }

                //switch MIU to 0
                MDrv_MVOP_MiuSwitch(0);

                MDrv_MVOP_Enable(TRUE);
            }

            return;
          #endif // #if (MJPEG_HARDWARE_MODE_ENABLED)

        default:
            break;
    }

    // MVOP setting flow:
    // 2. MDrv_MVOP_Enable(FALSE)
    MDrv_MVOP_Enable(FALSE);

    // MVOP setting flow:
    // 3. MDrv_MVOP_SetOutputCfg
    MDrv_MVOP_SetOutputCfg(&stMvopVidSt, FALSE);

    //Get VOP timing for FBL
    MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
    //printf("--versize %d framerate %d\n",stMVOPTiming.u16V_TotalCount,stMVOPTiming.u16ExpFrameRate);

    stTimingInfo.bFastFrameLock= FALSE;

    if (stMVOPTiming.bInterlace)
    {
        stTimingInfo.u16InputVFreq = (U16)((stMVOPTiming.u16ExpFrameRate * 2 + 50) / 100);
    }
    else
    {
        stTimingInfo.u16InputVFreq = (U16)((stMVOPTiming.u16ExpFrameRate + 50) / 100);
    }
    stTimingInfo.bMVOPSrc = TRUE;
    stTimingInfo.u16InputVTotal = stMVOPTiming.u16V_TotalCount;
    stTimingInfo.bInterlace = stMVOPTiming.bInterlace;

    if (m_eVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW)
    {
        MS_WINDOW_TYPE tDstWin = {_gu16PreviewX, _gu16PreviewY, _gu16PreviewWidth, _gu16PreviewHeight};

    #if ( defined(SCALER_DNR_BUF_PREV_ADR))
        //printf("Set FB=DNR_Prev %X %X\n", SCALER_DNR_BUF_PREV_ADR, SCALER_DNR_BUF_PREV_LEN);
        MApi_XC_SetFrameBufferAddress(SCALER_DNR_BUF_PREV_ADR, SCALER_DNR_BUF_PREV_LEN, MAIN_WINDOW);
        MApi_XC_SetAutoPreScaling(ENABLE, MAIN_WINDOW);
    #else
        // printf("Set FB=DNR %X %X\n", SCALER_DNR_BUF_ADR, SCALER_DNR_BUF_LEN);
        MApi_XC_SetFrameBufferAddress(SCALER_DNR_BUF_ADR, SCALER_DNR_BUF_LEN, MAIN_WINDOW);
    #endif

    #if (MEMORY_MAP <= MMAP_64MB)   //ATV_MM 64M
        //preview mode force quad pixel and deblocking off
        MApp_VDPlayer_QuarterPixel(DISABLE);
        MApp_VDPlayer_DeBlocking(DISABLE);
    #endif
        m_bFLG_PREVIEW = TRUE;
        MApp_Scaler_EnableOverScan(FALSE);

    #if DYNSCALING
        if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING)==1)
        {
            MS_WINDOW_TYPE tCapWin;
            tCapWin.x = MDrv_MVOP_GetHStart();
            tCapWin.y = MDrv_MVOP_GetVStart();
            tCapWin.width = gstVidStatus.u16HorSize;
            tCapWin.height = gstVidStatus.u16VerSize;
            MApp_Scaler_SetWindow(&tCapWin, NULL, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                                           SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW); //?? aspect ration??
            //_MApp_VDPlayer_SendXCStatus2Firmware(stDS_Info.u32DS_Info_BaseAddr + (1024*3), MAIN_WINDOW);
        }
        else
    #endif
        {
            MS_WINDOW_TYPE tCropWin;
            memset(&tCropWin, 0, sizeof(tCropWin));
            MS_WINDOW_TYPE stDisplayWin;
            memset(&stDisplayWin, 0, sizeof(stDisplayWin));

            switch(_geAspectRatioType)
            {
                case VIDEOSCREEN_MM_KEEP_RATIO_AND_SCALE:
                    stDisplayWin.x = _gu16PreviewX;
                    stDisplayWin.y = _gu16PreviewY;
                    stDisplayWin.height = _gu16PreviewHeight;
                    stDisplayWin.width = _gu16PreviewWidth;
                    _MApp_VDPlayer_CalCropDisplayWin(&tCropWin, &tDstWin, VDPLAYER_ZOOM_FACT_NORMAL,stDisplayWin);
                    break;

                case VIDEOSCREEN_MM_CAL_BY_VIDEOPLAYER:
                case VIDEOSCREEN_MM_FULL:    // H and V scale to fit panel
                case VIDEOSCREEN_MM_1_1:     // Bypass scale
                case VIDEOSCREEN_MM_16_9:    // Display window: H:V=16:9
                case VIDEOSCREEN_MM_4_3:     // Display window: H:V=4:3
                case VIDEOSCREEN_MM_ZOOM1:   // TO BE defined
                case VIDEOSCREEN_MM_ZOOM2:   // TO BE defined
                    break;

                default:
                    break;
            }

            MApp_Scaler_SetWindow(NULL, NULL, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                                      SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW); //?? aspect ration?

        }
    }
    else // Not Preview
    {
        m_bFLG_PREVIEW = FALSE;
        MApp_Scaler_EnableOverScan(FALSE);

    #if ( ENABLE_MM_HD_FB && (MEMORY_MAP == MMAP_64MB) )
      #ifdef SCALER_DNR_BUF_MM_HD_ADR
        // printf("[Not Preview]Set FB=MM_HD_ADR %X %X\n", SCALER_DNR_BUF_MM_HD_ADR, SCALER_DNR_BUF_MM_HD_LEN);
        MApi_XC_SetFrameBufferAddress(SCALER_DNR_BUF_MM_HD_ADR, SCALER_DNR_BUF_MM_HD_LEN, MAIN_WINDOW);
        MApi_XC_SetAutoPreScaling(ENABLE, MAIN_WINDOW);
      #else
        MApi_XC_SetFrameBufferAddress(SCALER_DNR_BUF_PREV_ADR, SCALER_DNR_BUF_PREV_LEN, MAIN_WINDOW);
        MApi_XC_SetAutoPreScaling(ENABLE, MAIN_WINDOW);
      #endif
    #endif

        if (MApi_XC_IsCurrentFrameBufferLessMode())
        {
            // NOTE: RM and VC1 not concider FB case
            MApp_Scaler_SetWindow(NULL, NULL, NULL,
                            stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        }
        else
        {
            #if (ENABLE_PIP)
            if(MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL || MApp_Get_PIPMode() == EN_PIP_MODE_POP)
            {
                MS_WINDOW_TYPE stWinRect;
                if(MApp_InputSource_PIP_GetMainWinRect(&stWinRect))
                {
                    MApp_Scaler_SetWindow(NULL, NULL, &stWinRect,
                                stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                }
                else
                {
                    _MApp_VDPlayer_ScaleScalerWindows(VDPLAYER_ZOOM_FACT_NORMAL, TRUE);
                }
            }
            else
            #endif
            {
                _MApp_VDPlayer_ScaleScalerWindows(VDPLAYER_ZOOM_FACT_NORMAL, TRUE);
            }
        }
    }

#if ENABLE_MVC
    if (u8VideoType == E_VDPLAYER_VIDEO_MVC)
        MApi_XC_W2BYTEMSK(REG_SC_BK01_72_L, 0x2D, 0xFFFF);  /// MVC patch
#endif

    // MVOP setting flow end:
    // 4. MDrv_MVOP_Enable(TRUE)
    MDrv_MVOP_Enable(TRUE);

    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
#if(CHAKRA3_AUTO_TEST)
    MApi_SC_ForceFreerun(TRUE);
    MApi_SC_SetFreerunVFreq(VFREQ_60HZ);
#endif
    MApi_XC_SetPanelTiming(&stTimingInfo, MAIN_WINDOW);


    MApi_XC_DisableInputSource(DISABLE, MAIN_WINDOW);

#if ENABLE_3D_PROCESS
    if((E_XC_3D_OUTPUT_LINE_ALTERNATIVE == MApi_XC_Get_3D_Output_Mode())
           || (E_XC_3D_OUTPUT_TOP_BOTTOM == MApi_XC_Get_3D_Output_Mode())
           || (E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF == MApi_XC_Get_3D_Output_Mode()))
    {
        if(MApi_XC_Get_3D_HW_Version() < 2)
        {
            MApi_XC_DisableInputSource(FALSE, SUB_WINDOW);
        }
        MApi_XC_3D_PostPQSetting(MAIN_WINDOW);
    }
#endif

#if ENABLE_BACKLIGHT_PWM_SYNC_WITH_FRAMERATE
    SetPWMto2PanelVFreq(RATIO_OF_BACKLIGHT_FREQ_OVER_FRAMERATE);
#endif

    if (E_VDPLAYER_VIDEO_H264 == u8VideoType)
    {
        gstVidStatus.bWithChroma = (BOOL)_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CHROMA_FORMAT);
        MDrv_MVOP_SetMonoMode(!gstVidStatus.bWithChroma);
    }

    // Enable scaler periodic task
    MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), ENABLE);

 #if (ENABLE_VE)
    //config and enable VE output
    {
        //U8 u8TurnOffDestination = ENABLE;
        MAPI_XC_MUX_TRIGGER_PATH_SYNC_EVENT(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), NULL);
        //Skip on here to avoid garbage, turn it on with the on of main window screen
        //MAPI_XC_MUX_TRIGGER_DEST_ON_OFF_EVENT(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),&u8TurnOffDestination);
    }
#endif
    // It's for temp patch. It was set by GOP callback, but will be overwritten by scaler.
    MApi_XC_Sys_PQ_ReduceBW_ForOSD(MAIN_WINDOW, MApi_GOP_GWIN_IsEnabled());
    MApi_XC_Enable_TwoInitFactor(TRUE, MAIN_WINDOW);

    g_DstWin.x = 0;
    g_DstWin.y = 0;
    g_DstWin.height = g_IPanel.Height();
    g_DstWin.width = g_IPanel.Width();
}

void MApp_VDPlayer_MailBoxHandler(void)
{
    U8 u8Count;
    U8 u8Index;
    //U8 u8MailBox[12];
    U32 tmpvar = 0;
    U8 u8StrmHdlIdx;
    U32 u32StrmHdl;
#if ENABLE_USB_READ_RATE_MEASURED
    U32 u32ReadTimer;
#endif

    static U32 spuqueueaddr;
    static U16 spuqueuesize;
    MBX_MSGQ_Status Mstatus;
    MBX_Msg MB_Message;
#if (!FILE_SYSTEM_LONGLONG_API_ENABLE)
    U32 u32Offset;
#endif
    memset(&Mstatus,0,sizeof(MBX_MSGQ_Status));
    memset(&MB_Message,0,sizeof(MBX_Msg));

    if (_gbContinueBlockRead)
    {
        //for stream mode, support blocking read
        _MApp_VDPlayer_ProcessBlockingRead();
    }
#if ENABLE_HK_MM
    MApp_MediaCodecTask();
    //E_MBX_CLASS_VDPLAYER_FS use queue and not immediately
    //E_MBX_CLASS_VDPLAYER use callback function for immediately command
    MDrv_VMBX_GetMsgQueueStatus(E_MBX_CLASS_VDPLAYER_FS, &Mstatus);
#else //#if ENABLE_HK_MM
    MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_VDPLAYER, &Mstatus);
#endif //#if ENABLE_HK_MM

    u8Count = (U8)Mstatus.u32NormalMsgCount;

   // u8Count = msAPI_MailBox_GetMsgCount(Q_VDPLAYER);
    for(u8Index=0;u8Index<u8Count;u8Index++)
    {
#if ENABLE_HK_MM
        if(MDrv_VMBX_RecvMsg(E_MBX_CLASS_VDPLAYER_FS, &MB_Message, 0,MBX_CHECK_NORMAL_MSG)==E_MBX_SUCCESS)
#else //#if ENABLE_HK_MM
        if(MSApi_MBX_RecvMsg(E_MBX_CLASS_VDPLAYER, &MB_Message, 0,MBX_CHECK_NORMAL_MSG)==E_MBX_SUCCESS)
#endif //#if ENABLE_HK_MM
        //if (msAPI_MailBox_GetMsg(Q_VDPLAYER, &u8MailBox[0]) == MB_GET_MSG_OK)
        {
            //MailBox MB;
            //MailBox* pMB = NULL;

            // Fix compiling warning.
          #if 0
            pMB = (MailBox*)&u8MailBox[0];
          #else
            //memcpy(&MB, &u8MailBox[0], 12);
            //pMB = (MailBox *)&MB;
          #endif
            if (MB_Message.u8MsgClass == E_MBX_CLASS_VDPLAYER)
            {
                U32 u32Addr = 0;
                U32 u32Size = 0;
                //U32 u32Offset = 0;
                U8 i;
                U32 read_size;
              #if FILE_SYSTEM_LONGLONG_API_ENABLE
                LongLong u64FileSize;
                LongLong u64FileOffset;
              #endif
                switch(MB_Message.u8Index)
                {
                    // MB_VDPLAYER_RET_STATE_WAIT ----------------------------------------------
                    case MB_VDPLAYER_STATE_RET_WAIT:
                        enVDPlayerRet = EXIT_VDPLAYER_WAIT;
                        #if ENABLE_DIVX_PLUS
                        g_bChangeFile = FALSE;
                        #endif
                        m_eVDPlayerAckFlags = (enumVDPlayerAckFlags)E_ACKFLG_NULL;
                        break;

                    // MB_VDPLAYER_RET_STATE_EXIT ----------------------------------------------
                    case MB_VDPLAYER_STATE_RET_EXIT:
                        enVDPlayerRet = EXIT_VDPLAYER_EXIT;
                        #if ENABLE_DIVX_PLUS
                        g_bChangeFile = FALSE;
                        #endif
                        m_eVDPlayerAckFlags = (enumVDPlayerAckFlags)E_ACKFLG_NULL;
                        break;

                    // MB_VDPLAYER_FILE_OPEN ----------------------------------------------
                    case MB_VDPLAYER_FILE_OPEN:
                    {
                        u8StrmHdlIdx = MApp_VDPlayer_GetFreeFileHandleIdx();
                        if (u8StrmHdlIdx == INVALID_HANDLE_IDX)
                        {
                            VDPLAYER_DBG(printf ("[ERROR] out of free file handle\n"));
                            return;
                        }

                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                        if (u32StrmHdl != INVALID_DATA_STREAM_HDL)
                        {
                            u64FileSize = msAPI_DataStreamIO_Length_LongLong(u32StrmHdl);
                            VDPLAYER_DVD_DBG(printf("StrmHdl[%lu], FileSize[%lu]\n", u32StrmHdl, u64FileSize.Lo));
                        }
                        else
                        {
                            u64FileSize.Hi = 0;
                            u64FileSize.Lo = 0;
                            u8StrmHdlIdx = 0xFF;
                        }

                        //==> Send mail.
                    #if FILE_SYSTEM_LONGLONG_API_ENABLE
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,10
                        /*p1*/              ,MB_VDPLAYER_FILE_OPEN
                        /*p2*/              ,(U8)((u64FileSize.Hi&0xFF000000)>>24)
                        /*p3*/              ,(U8)((u64FileSize.Hi&0x00FF0000)>>16)
                        /*p4*/              ,(U8)((u64FileSize.Hi&0x0000FF00)>>8)
                        /*p5*/              ,(U8)(u64FileSize.Hi&0x000000FF)
                        /*p6*/              ,(U8)((u64FileSize.Lo&0xFF000000)>>24)
                        /*p7*/              ,(U8)((u64FileSize.Lo&0x00FF0000)>>16)
                        /*p8*/              ,(U8)((u64FileSize.Lo&0x0000FF00)>>8)
                        /*p9*/              ,(U8)(u64FileSize.Lo&0x000000FF)
                        /*p10*/             ,u8StrmHdlIdx);
                    #else
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,10
                        /*p1*/              ,MB_VDPLAYER_FILE_OPEN
                        /*p2*/              ,0
                        /*p3*/              ,0
                        /*p4*/              ,0
                        /*p5*/              ,0
                        /*p6*/              ,(U8)((msAPI_DataStreamIO_Length(u32StrmHdl)&0xFF000000)>>24)
                        /*p7*/              ,(U8)((msAPI_DataStreamIO_Length(u32StrmHdl)&0x00FF0000)>>16)
                        /*p8*/              ,(U8)((msAPI_DataStreamIO_Length(u32StrmHdl)&0x0000FF00)>>8)
                        /*p9*/              ,(U8)(msAPI_DataStreamIO_Length(u32StrmHdl)&0x000000FF)
                        /*p10*/             ,u8StrmHdlIdx);
                    #endif

                    }
                        break;

                    // MB_VDPLAYER_FILE_READ ----------------------------------------------
                    case MB_VDPLAYER_FILE_READ:
                        g_bNonBlockingRead = FALSE;
                        for(i=0; i<4; i++)
                        {
                            u32Addr = (u32Addr<<8) | MB_Message.u8Parameters[i];
                        }
//                        u32Addr = (u32Addr & 0x7FFFFFFF);
                        // u32Addr = (u32Addr & 0x1FFFFFFF) | 0x80000000;

                        for(i=4; i<8; i++)
                        {
                            u32Size = (u32Size<<8) | MB_Message.u8Parameters[i];
                        }

                        u8StrmHdlIdx = MB_Message.u8Parameters[8];
                    #if ENABLE_USB_READ_RATE_MEASURED
                        u32ReadTimer = msAPI_Timer_GetTime0();
                    #endif
                    #if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleForSimulateMultiFileHandler(u8StrmHdlIdx, TRUE);
                    #else
                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                    #endif
                        read_size = msAPI_DataStreamIO_Read(u32StrmHdl, (void *)u32Addr, u32Size);
                    #if ENABLE_USB_READ_RATE_MEASURED
                        m_u32ReadTimeMeasured += (msAPI_Timer_DiffTimeFromNow(u32ReadTimer));
                        m_u32ReadSizeMeasured += u32Size-read_size;
                        printf("\x1b[31m" "Blocking Read: size:%d, time: %d" "\x1b[0m""\n",m_u32ReadSizeMeasured,m_u32ReadTimeMeasured);
                    #endif
                    #if 0//for debug
                        printf("    u32Addr=0x%lx,u32Size=%ld , read_size=%ld\n",u32Addr,u32Size,read_size);
                        u64FileOffset = msAPI_DataStreamIO_Tell_LongLong(u32StrmHdl);
                        printf("    Pos.Hi=0x%lx,Pos.Lo=%lx\n",u64FileOffset.Hi,u64FileOffset.Lo);
                    #endif
                        MsOS_FlushMemory();

                    #if (ENABLE_PVR_AESDMA || (ENABLE_CI_PLUS && ENABLE_CIPLUS_PVR))
                        if ( (bIsPVR == TRUE)
                             && (enEncryptType != E_PVR_ENCRYPTION_CIPLUS)
                             && (enEncryptType != E_PVR_ENCRYPTION_NONE) )
                        {
                            msAPI_PVR_AESDMAEncryptDecrypt(MS_PA2KSEG1(u32Addr), u32Size-read_size, E_DECRYPT);
                        }
                    #endif

                        // __asm__ volatile ("l.msync;");
                        _gu32BlockReadTimer = msAPI_Timer_GetTime0();

                        if(read_size == 0)   //finish blocking read, send ack msg
                        {
                            _gbContinueBlockRead = FALSE;
                            //==> Send mail.
                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                            /*ParameterCount*/  ,6
                            /*p1*/              ,MB_VDPLAYER_FILE_READ
                            /*p2*/              ,(U8)((read_size&0xFF000000)>>24)
                            /*p3*/              ,(U8)((read_size&0x00FF0000)>>16)
                            /*p4*/              ,(U8)((read_size&0x0000FF00)>>8)
                            /*p5*/              ,(U8)(read_size&0x000000FF)
                            /*p6*/              ,u8StrmHdlIdx
                            /*p7*/              ,0
                            /*p8*/              ,0
                            /*p9*/              ,0
                            /*p10*/             ,0);
                        }
                        else
                        {
                            if(gbStreamMode)
                            {
                                if ((u8StrmHdlIdx == 0) || _gbEnableInternalSubtitle)
                                {
                                    u64FileSize = msAPI_DataStreamIO_Length_LongLong(u32StrmHdl);
                                }
                                else
                                {
                                    u64FileSize.Hi = 0;
                                    u64FileSize.Lo = 0;
                                    u8StrmHdlIdx = 0xFF;
                                }

                                if(msAPI_DataStreamIO_Tell(u32StrmHdl) >= u64FileSize.Lo)
                                {
                                    _gbContinueBlockRead = FALSE;
                                    //==> Send mail.
                                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                    /*ParameterCount*/  ,6
                                    /*p1*/              ,MB_VDPLAYER_FILE_READ
                                    /*p2*/              ,(U8)((read_size&0xFF000000)>>24)
                                    /*p3*/              ,(U8)((read_size&0x00FF0000)>>16)
                                    /*p4*/              ,(U8)((read_size&0x0000FF00)>>8)
                                    /*p5*/              ,(U8)(read_size&0x000000FF)
                                    /*p6*/              ,u8StrmHdlIdx
                                    /*p7*/              ,0
                                    /*p8*/              ,0
                                    /*p9*/              ,0
                                    /*p10*/             ,0);
                                }
                                else  //need continue read in next loop
                                {
                                    _gu32ResidualReadSize = read_size;
                                    _gu32gStreamHdl = u32StrmHdl;
                                    _gu32BuffAddr = u32Addr + u32Size - read_size;
                                    _gbContinueBlockRead = TRUE;
                                }
                            }
                            else
                            {
                                // VDPlayer might request the size more than the rest size to the file end.
                                // Thus, we add this patch to fix the file end read problem.
                                u64FileSize = msAPI_DataStreamIO_Length_LongLong(u32StrmHdl);
                                if(msAPI_DataStreamIO_Tell(u32StrmHdl) >= u64FileSize.Lo)
                                {
                                    //==> Send mail.
                                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                    /*ParameterCount*/  ,6
                                    /*p1*/              ,MB_VDPLAYER_FILE_READ
                                    /*p2*/              ,(U8)((read_size&0xFF000000)>>24)
                                    /*p3*/              ,(U8)((read_size&0x00FF0000)>>16)
                                    /*p4*/              ,(U8)((read_size&0x0000FF00)>>8)
                                    /*p5*/              ,(U8)(read_size&0x000000FF)
                                    /*p6*/              ,u8StrmHdlIdx
                                    /*p7*/              ,0
                                    /*p8*/              ,0
                                    /*p9*/              ,0
                                    /*p10*/             ,0);
                                }
                                else
                                {
                                    //==> Send mail.
                                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                    /*ParameterCount*/  ,6
                                    /*p1*/              ,MB_VDPLAYER_FILE_READ
                                    /*p2*/              ,0
                                    /*p3*/              ,0
                                    /*p4*/              ,0
                                    /*p5*/              ,0
                                    /*p6*/              ,u8StrmHdlIdx
                                    /*p7*/              ,0
                                    /*p8*/              ,0
                                    /*p9*/              ,0
                                    /*p10*/             ,0);

                                    if(m_eVDPlayerAckFlags&E_ACKFLG_WAIT_INIT)
                                    {
                                        Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_INIT);
                                        u8VDPlayerInitResult = FALSE;
                                    }
                                }
                            }
                        }
                        break;


                    case MB_VDPLAYER_FILE_READ_NONBLOCKING:
                        g_bNonBlockingRead = TRUE;
                        for(i=0; i<4; i++)
                        {
                            u32Addr = (u32Addr<<8) | MB_Message.u8Parameters[i];
                        }
                        //u32Addr = (u32Addr & 0x7FFFFFFF); //co-processor will return PA
                        // u32Addr = (u32Addr & 0x1FFFFFFF) | 0x80000000;

                        for(i=4; i<8; i++)
                        {
                            u32Size = (u32Size<<8) | MB_Message.u8Parameters[i];
                        }

                        u8StrmHdlIdx = MB_Message.u8Parameters[8];
                    #if ENABLE_USB_READ_RATE_MEASURED
                        u32ReadTimer = msAPI_Timer_GetTime0();
                    #endif
                    #if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleForSimulateMultiFileHandler(u8StrmHdlIdx, TRUE);
                    #else
                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                    #endif
                    #if ENABLE_HK_MM
                        read_size = _MApp_VDPlyer_LimitedFileRead(u32StrmHdl, (void *)u32Addr, u32Size, NONBLOCKING_READ_SIZE, NONBLOCKING_READ_TIMEOUT);
                    #else
                        read_size = msAPI_DataStreamIO_Read(u32StrmHdl, (void *)u32Addr, u32Size);
                    #endif
                    #if ENABLE_USB_READ_RATE_MEASURED
                        m_u32ReadTimeMeasured += (msAPI_Timer_DiffTimeFromNow(u32ReadTimer));
                        m_u32ReadSizeMeasured += u32Size-read_size;
                        printf("\x1b[31m" "Non-Blocking Read: size:%d, time: %d" "\x1b[0m""\n",m_u32ReadSizeMeasured,m_u32ReadTimeMeasured);
                    #endif
                    #if 0
                        printf("    u32Addr=0x%lx,u32Size=%ld , read_size=%ld\n",u32Addr,u32Size,read_size);
                        u64FileOffset = msAPI_DataStreamIO_Tell_LongLong(u32StrmHdl);
                        printf("    Pos.Hi=0x%lx,Pos.Lo=%lx\n",u64FileOffset.Hi,u64FileOffset.Lo);
                    #endif
                        MsOS_FlushMemory();
                    #if (ENABLE_PVR_AESDMA)
                        if (bIsPVR == TRUE)
                        msAPI_PVR_AESDMAEncryptDecrypt(MS_PA2KSEG1(u32Addr), u32Size-read_size, E_DECRYPT);
                    #endif
                        // __asm__ volatile ("l.msync;");
                        //==> Send mail.
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
                        /*Index*/           ,MB_VDPLAYER_FILE_READ_NONBLOCKING_DONE
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,5
                        /*p1*/              ,(U8)((read_size&0xFF000000)>>24)
                        /*p2*/              ,(U8)((read_size&0x00FF0000)>>16)
                        /*p3*/              ,(U8)((read_size&0x0000FF00)>>8)
                        /*p4*/              ,(U8)(read_size&0x000000FF)
                        /*p5*/              ,u8StrmHdlIdx
                        /*p6*/              ,0
                        /*p7*/              ,0
                        /*p8*/              ,0
                        /*p9*/              ,0
                        /*p10*/             ,0);
                        break;
                #if ENABLE_HK_AVI
                    case MB_VDPLAYER_AVI_SCAN_INDEX:
                        {
                            BOOL bRet;
                            U8 u8FileHdl = MB_Message.u8Parameters[0];
                            bRet = MApp_VDPlayer_AVIScanIndex(u8FileHdl);
                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                            /*ParameterCount*/  ,2
                            /*p1*/              ,MB_VDPLAYER_AVI_SCAN_INDEX
                            /*p2*/              ,bRet
                            /*p3*/              ,0
                            /*p4*/              ,0
                            /*p5*/              ,0
                            /*p6*/              ,0
                            /*p7*/              ,0
                            /*p8*/              ,0
                            /*p9*/              ,0
                            /*p10*/             ,0);
                        }
                        break;
                #endif

                    // MB_VDPLAYER_FILE_SEEK ----------------------------------------------
                    case MB_VDPLAYER_FILE_SEEK:
                        _bStreamSeeked = TRUE;
                        g_bNonBlockingSeek = FALSE;
                    #if FILE_SYSTEM_LONGLONG_API_ENABLE
                        u64FileOffset.Hi = 0;
                        u64FileOffset.Lo = 0;
                        for(i=0; i<4; i++)
                        {
                            u64FileOffset.Hi = (u64FileOffset.Hi<<8) | MB_Message.u8Parameters[i];
                        }
                        for(i=4; i<8; i++)
                        {
                            u64FileOffset.Lo = (u64FileOffset.Lo<<8) | MB_Message.u8Parameters[i];
                        }

                        u8StrmHdlIdx = MB_Message.u8Parameters[8];

                    #if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleForSimulateMultiFileHandler(u8StrmHdlIdx, FALSE);
                    #else
                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                    #endif
                        msAPI_DataStreamIO_Seek_LongLong(u32StrmHdl, u64FileOffset, E_DATA_STREAM_SEEK_SET);
                    #else
                        for(i=4; i<8; i++)
                        {
                            u32Offset = (u32Offset<<8) |MB_Message.u8Parameters[i];
                        }

                        u8StrmHdlIdx = MB_Message.u8Parameters[8];
                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                        msAPI_DataStreamIO_Seek(u32StrmHdl, u32Offset, E_DATA_STREAM_SEEK_SET);
                    #endif
                        //==> Send mail.
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,2
                        /*p1*/              ,MB_VDPLAYER_FILE_SEEK
                        /*p2*/              ,u8StrmHdlIdx
                        /*p3*/              ,0
                        /*p4*/              ,0
                        /*p5*/              ,0
                        /*p6*/              ,0
                        /*p7*/              ,0
                        /*p8*/              ,0
                        /*p9*/              ,0
                        /*p10*/             ,0);
                        break;

                    // MB_VDPLAYER_FILE_SEEK_NONBLOCKING ----------------------------------------------
                    case MB_VDPLAYER_FILE_SEEK_NONBLOCKING:
                        g_bNonBlockingSeek = TRUE;
                    #if FILE_SYSTEM_LONGLONG_API_ENABLE
                        u64FileOffset.Hi = 0;
                        u64FileOffset.Lo = 0;
                        for(i=0; i<4; i++)
                        {
                            u64FileOffset.Hi = (u64FileOffset.Hi<<8) | MB_Message.u8Parameters[i];
                        }
                        for(i=4; i<8; i++)
                        {
                            u64FileOffset.Lo = (u64FileOffset.Lo<<8) | MB_Message.u8Parameters[i];
                        }

                        u8StrmHdlIdx = MB_Message.u8Parameters[8];
                    #if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleForSimulateMultiFileHandler(u8StrmHdlIdx, FALSE);
                    #else
                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                    #endif
                        msAPI_DataStreamIO_Seek_LongLong(u32StrmHdl, u64FileOffset, E_DATA_STREAM_SEEK_SET);
                    #else
                        for(i=4; i<8; i++)
                        {
                            u32Offset = (u32Offset<<8) | MB_Message.u8Parameters[i];
                        }
                        u8StrmHdlIdx = MB_Message.u8Parameters[8];
                        u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                        msAPI_DataStreamIO_Seek(u32StrmHdl, u32Offset, E_DATA_STREAM_SEEK_SET);
                    #endif
                        //==> Send mail.
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
                        /*Index*/           ,MB_VDPLAYER_FILE_SEEK_NONBLOCKING_DONE
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,1
                        /*p1*/              ,u8StrmHdlIdx
                        /*p2*/              ,0
                        /*p3*/              ,0
                        /*p4*/              ,0
                        /*p5*/              ,0
                        /*p6*/              ,0
                        /*p7*/              ,0
                        /*p8*/              ,0
                        /*p9*/              ,0
                        /*p10*/             ,0);
                        break;

                #ifdef _VDPLAYER_DUMP_RAW_
                    // MB_VDPLAYER_FILE_DUMP_RAW ----------------------------------------------
                    case MB_VDPLAYER_FILE_DUMP_RAW:
                        {
                            U32 u32Buffer = VDPLAYER_DUMP_RAW_ADR;

                            U8 idx = MB_Message.u8Parameters[0];
                            for(i=1; i<5; i++)
                            {
                                u32Size = (u32Size<<8) | MB_Message.u8Parameters[i];
                            }
                            //printf ("src %lX, dst %lX, size %lX\n", VDEC_FRAMEBUFFER_ADR + u32Size*idx, u32Buffer, u32Size);
                            msAPI_MIU_Copy(VDEC_FRAMEBUFFER_ADR + u32Size*idx, u32Buffer, u32Size, MIU_SDRAM12SDRAM0);
                            msAPI_FCtrl_FileWrite(VDPlayer_dump_id, u32Buffer, u32Size);

                            //==> Send mail.
                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                            /*ParameterCount*/  ,1
                            /*p1*/              ,MB_VDPLAYER_FILE_DUMP_RAW
                            /*p2*/              ,0
                            /*p3*/              ,0
                            /*p4*/              ,0
                            /*p5*/              ,0
                            /*p6*/              ,0
                            /*p7*/              ,0
                            /*p8*/              ,0
                            /*p9*/              ,0
                            /*p10*/             ,0);
                        }
                        break;
                #endif // _VDPLAYER_DUMP_RAW_

                    // MB_VDPLAYER_FILE_CLOSE ----------------------------------------------
                    case MB_VDPLAYER_FILE_CLOSE:
                        u32StrmHdl = MB_Message.u8Parameters[0];
                        MApp_VDPlayer_ReleaseStrmHandleByIdx(u32StrmHdl);

#if ENABLE_NEW_FILE_HANDLER
                        U8 u8Idx;
                        for (u8Idx=0; u8Idx<TotalHandlerCnt; u8Idx++)
                        {
                            if (u32StreamHandleIdx[u8Idx] != INVALID_DATA_STREAM_HDL)
                            {
                                msAPI_DataStreamIO_Close(u32StreamHandleIdx[u8Idx]);
                                u32StreamHandleIdx[u8Idx] = INVALID_DATA_STREAM_HDL;
                            }
                        }
#else //ENABLE_NEW_FILE_HANDLER
                        if (u32VDPlayerStreamHandleIdx_Video != INVALID_DATA_STREAM_HDL)
                        {
                            msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Video);
                            u32VDPlayerStreamHandleIdx_Video = INVALID_DATA_STREAM_HDL;
                        }

                        if(u32VDPlayerStreamHandleIdx_Subtitle != INVALID_DATA_STREAM_HDL)
                        {
                            msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Subtitle);
                            u32VDPlayerStreamHandleIdx_Subtitle = INVALID_DATA_STREAM_HDL;
                        }

                    #if ENABLE_AUDIO_HANDLER
                        if(u32VDPlayerStreamHandleIdx_Audio != INVALID_DATA_STREAM_HDL)
                        {
                            msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Audio);
                            u32VDPlayerStreamHandleIdx_Audio = INVALID_DATA_STREAM_HDL;
                        }
                    #endif
                    #if ENABLE_ATTACHMENT_HANDLER
                        if(u32VDPlayerStreamHandleIdx_Attachment != INVALID_DATA_STREAM_HDL)
                        {
                            msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Attachment);
                            u32VDPlayerStreamHandleIdx_Attachment = INVALID_DATA_STREAM_HDL;
                        }
                    #endif

#endif

                    #ifdef _VDPLAYER_DUMP_RAW_
                        if(VDPlayer_dump_id != INVALID_FILE_HANDLE)
                        {
                            msAPI_FCtrl_FileClose(VDPlayer_dump_id);
                            VDPlayer_dump_id = INVALID_FILE_HANDLE;
                        }
                    #endif // _VDPLAYER_DUMP_RAW_
                        break;

                    // MB_VDPLAYER_AUDIO_START ----------------------------------------------
                    case MB_VDPLAYER_AUDIO_START:
                    {
                        //printf("------> MB_VDPLAYER_AUDIO_START\n");
                        BOOLEAN bIsTSAudio =  MB_Message.u8Parameters[0];
                        if(bIsTSAudio == TRUE)
                        {
                            /// Enable Audio parser to play TS-stream
                            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILETSP);
                            MApi_AUDIO_SetAACInfo(Audio_AAC_mm_single_frame_mode, FALSE, 0);
                        }
                        else
                        {
                            //msAPI_Music_StartDecode();
                            msAPI_Music_StartDecodeEnhance(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_NEW_AUDIO_MM_MODE));
                            MApi_AUDIO_SetAACInfo(Audio_AAC_mm_single_frame_mode, TRUE, 0);
                        }
#if  AUDIO_SPDIF_ENABLE
                        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                        }
                        else if(stGenSetting.g_SysSetting.fSPDIFMODE == 1)
                        {
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                        }
#endif
                        if (g_b2ndRunPreviewMute ==  TRUE)
                        {
                            // patch dolphin.flv preview 2nd run video black screen but audio has sound.
                            // 2nd run black screen is disable by mplayer, but audio start mute control by
                            // videoplayer. Use this variable to control mute and unmute by mplayer value.
                            //printf("preview 2nd run audio mute\n");
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        }
                        else
                        {
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        }
                        MsOS_DelayTask(20);

                        //==> Send mail.
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,1
                        /*p1*/              ,MB_VDPLAYER_AUDIO_INIT
                        /*p2*/              ,0
                        /*p3*/              ,0
                        /*p4*/              ,0
                        /*p5*/              ,0
                        /*p6*/              ,0
                        /*p7*/              ,0
                        /*p8*/              ,0
                        /*p9*/              ,0
                        /*p10*/             ,0);
                        break;
                    }

                    // MB_VDPLAYER_AUDIO_INIT ----------------------------------------------
                    case MB_VDPLAYER_AUDIO_INIT:
                        tmpvar = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_CODEC_ID);
                        //printf("------> MB_VDPLAYER_AUDIO_INIT(Audio CodecID=0x%lx)\n",tmpvar);

                        switch (tmpvar)
                        {
                            case E_VDP_CODEC_ID_WMAV1:
                            case E_VDP_CODEC_ID_WMAV2:
                                msAPI_Music_Init(MSAPI_AUD_DVB_WMA, INIT_VOLUME);
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_PARSINGBYAPP, 0x1);
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_VERSION, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_VERSION));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_CHANNELS, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_CHANNELS));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_SAMPLERATE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_SAMPLERATE));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BYTERATE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_BYTERATE));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BLOCKALIGN, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_BLOCKALIGN));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_ENCOPT, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_ENCODEOPT));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_MAX_PACKET_SIZE, 0);
                                break;

                            case E_VDP_CODEC_ID_WMAV3:
                                msAPI_Music_Init(MSAPI_AUD_DVB_WMA_PRO, INIT_VOLUME);
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_PARSINGBYAPP, 0x1);
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_VERSION, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_VERSION));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_CHANNELS, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_CHANNELS));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_SAMPLERATE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_SAMPLERATE));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BYTERATE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_BYTERATE));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BLOCKALIGN, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_BLOCKALIGN));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_ENCOPT, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_ENCODEOPT));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_MAX_PACKET_SIZE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_ADVANCE_ENCODEOPT)); //check if wma lbr
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BITS_PER_SAMPLE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_BIT_PER_SAMPLE));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_CHANNELMASK, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_CHANNEL_MASK));
                                msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_PARAM_EXIST, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_PARAM_EXIST));
                                if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_PARAM_EXIST))
                                {
                                    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_PEAK_AMP_REF, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_PEEK_REF));
                                    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_PEAK_AMP_TARGET, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_PEEK_TARGET));
                                    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_RMS_AMP_REF, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_AVE_REF));
                                    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_RMS_AMP_TARGET, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_AVE_TARGET));
                                }
                                break;

                            case E_VDP_CODEC_ID_DTS:
                            case E_VDP_CODEC_ID_DTS_HD://AUDIO_SPDIF_ENABLE
                                msAPI_Music_Init(MSAPI_AUD_DVB_DTS, INIT_VOLUME);
                               break;

                            case E_VDP_CODEC_ID_DTS_EXPRESS:
                                msAPI_Music_Init(MSAPI_AUD_DVB_DTSLBR, INIT_VOLUME);
                               break;

                            case E_VDP_CODEC_ID_MP3:
                                msAPI_Music_Init(MSAPI_AUD_DVB_MP3, INIT_VOLUME);
                                if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_Audio_Request_Size) == E_VDP_AUDIO_REQUIRE_SIZE_1KB)
                                    MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_1KB, 0);
                                else if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_Audio_Request_Size) == E_VDP_AUDIO_REQUIRE_SIZE_2KB)
                                    MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_2KB, 0);
                                else
                                    MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_4KB, 0);
                                break;
                            case E_VDP_CODEC_ID_MP2:
                                msAPI_Music_Init(MSAPI_AUD_DVB_MPEG, INIT_VOLUME);
                                if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_Audio_Request_Size) == E_VDP_AUDIO_REQUIRE_SIZE_1KB)
                                    MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_1KB, 0);
                                else if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_Audio_Request_Size) == E_VDP_AUDIO_REQUIRE_SIZE_2KB)
                                    MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_2KB, 0);
                                else
                                    MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_4KB, 0);
                                break;
                            case E_VDP_CODEC_ID_AC3:
                            case E_VDP_CODEC_ID_EAC3:
                                msAPI_Music_Init(MSAPI_AUD_DVB_AC3P, INIT_VOLUME);
                                if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_Audio_Request_Size))
                                {
                                    msAPI_Music_StopDecode();
                                    MApi_AUDIO_SetAC3PInfo(Audio_AC3P_infoType_MMFileSize, FILE_SIZE_16KB, 0);
                                }
                                break;
                            case E_VDP_CODEC_ID_AAC:
                            case E_VDP_CODEC_ID_MPEG4AAC:
                                msAPI_Music_Init(MSAPI_AUD_DVB_AAC, INIT_VOLUME);
                                break;

                            case E_VDP_CODEC_ID_FLAC:
                                msAPI_Music_Init(MSAPI_AUD_DVB_FLAC, INIT_VOLUME);
                                break;

                            case E_VDP_CODEC_ID_AMR_NB:
                                msAPI_Music_Init(MSAPI_AUD_DVB_AMR_NB, INIT_VOLUME);
                                break;

                            case E_VDP_CODEC_ID_AMR_WB:
                                msAPI_Music_Init(MSAPI_AUD_DVB_AMR_WB, INIT_VOLUME);
                                break;

                            case E_VDP_CODEC_ID_PCM_S16LE:
                            case E_VDP_CODEC_ID_PCM_S16BE:
                            case E_VDP_CODEC_ID_PCM_U16LE:
                            case E_VDP_CODEC_ID_PCM_U16BE:
                            case E_VDP_CODEC_ID_PCM_S8:
                            case E_VDP_CODEC_ID_PCM_U8:
                            case E_VDP_CODEC_ID_PCM_MULAW:
                            case E_VDP_CODEC_ID_PCM_ALAW:
                            {
                                U32 u32SampleRate;
                                U16 u16BitsPerSample;
                                U8  u8CannelNumber;
                                U32 tmpvartemp=tmpvar;

                                u32SampleRate  = (((U32)MB_Message.u8Parameters[1]<<8)&0xFF00) |
                                                 (((U32)MB_Message.u8Parameters[2])&0x00FF);

                                u16BitsPerSample  = (((U16)MB_Message.u8Parameters[3]<<8)&0xFF00) |
                                                    (((U16)MB_Message.u8Parameters[4])&0x00FF);

                                u8CannelNumber  = ((U16)(MB_Message.u8Parameters[5])&0x00FF);

                                if (tmpvar == E_VDP_CODEC_ID_PCM_U16BE || tmpvar == E_VDP_CODEC_ID_PCM_S16BE ||
                                    tmpvar == E_VDP_CODEC_ID_PCM_ALAW  || tmpvar == E_VDP_CODEC_ID_PCM_MULAW)
                                {
                                    tmpvar = 0xFF;
                                }
                                else if(tmpvar == E_VDP_CODEC_ID_PCM_U8)// Confirmed with audio team, format pcm U8 can't determine the endianness
                                {
                                    tmpvar = 0x77;
                                }
                                else
                                {
                                    tmpvar = 0x0;
                                }

                                msAPI_Music_Init(MSAPI_AUD_DVB_XPCM, INIT_VOLUME);
                                if(tmpvartemp==E_VDP_CODEC_ID_PCM_MULAW)
                                {
                                    MApi_AUDIO_XPCM_Param(G711_u_LAW, u8CannelNumber - 1, u32SampleRate, u16BitsPerSample,0, tmpvar);
                                }
                                else if(tmpvartemp==E_VDP_CODEC_ID_PCM_ALAW)
                                {
                                    MApi_AUDIO_XPCM_Param(G711_A_LAW, u8CannelNumber - 1, u32SampleRate, u16BitsPerSample,0, tmpvar);
                                }
                                else
                                {
                                    MApi_AUDIO_XPCM_Param(LPCM, u8CannelNumber - 1, u32SampleRate, u16BitsPerSample,0, tmpvar);
                                }
                            }
                            break;

                            case E_VDP_CODEC_ID_ADPCM_IMA_QT:
                            case E_VDP_CODEC_ID_ADPCM_IMA_WAV:
                            case E_VDP_CODEC_ID_ADPCM_IMA_DK3:
                            case E_VDP_CODEC_ID_ADPCM_IMA_DK4:
                            case E_VDP_CODEC_ID_ADPCM_IMA_WS:
                            case E_VDP_CODEC_ID_ADPCM_IMA_SMJPEG:
                            case E_VDP_CODEC_ID_ADPCM_MS:
                            case E_VDP_CODEC_ID_ADPCM_4XM:
                            case E_VDP_CODEC_ID_ADPCM_XA:
                            case E_VDP_CODEC_ID_ADPCM_ADX:
                            case E_VDP_CODEC_ID_ADPCM_EA:
                            case E_VDP_CODEC_ID_ADPCM_G726:
                            {
                                U32 u32SampleRate;
                                U16 u16BitsPerSample;
                                U8 u8CannelNumber;
                                U16 u16BlockSize;
                                U16 u16SamplePerBlock;
                                u32SampleRate  = (((U32)MB_Message.u8Parameters[1]<<8)&0xFF00) |
                                                                (((U32)MB_Message.u8Parameters[2])&0x00FF);

                                u16BitsPerSample  = (((U16)MB_Message.u8Parameters[3]<<8)&0xFF00) |
                                                                    (((U16)MB_Message.u8Parameters[4])&0x00FF);

                                u8CannelNumber  = ((MB_Message.u8Parameters[5])&0x00FF);

                                u16BlockSize  = (((U16)MB_Message.u8Parameters[6]<<8)&0xFF00) |
                                                                (((U16)MB_Message.u8Parameters[7])&0x00FF);

                                u16SamplePerBlock  = (((U16)MB_Message.u8Parameters[8]<<8)&0xFF00) |
                                                                (((U16)MB_Message.u8Parameters[9])&0x00FF);

                                if (tmpvar == E_VDP_CODEC_ID_ADPCM_MS)
                                {
                                    tmpvar = MS_ADPCM;//2;
                                }
                                else
                                {
                                    tmpvar = IMA_ADPCM;//17;
                                }
                                msAPI_Music_Init(MSAPI_AUD_DVB_XPCM, INIT_VOLUME);
                                MApi_AUDIO_XPCM_Param((XPCM_TYPE)tmpvar, u8CannelNumber - 1, u32SampleRate, u16BitsPerSample,u16BlockSize, u16SamplePerBlock);
                            }
                                break;

                            case E_VDP_CODEC_ID_RAAC:
                            case E_VDP_CODEC_ID_RACP:
                            {
                                U16 u16Index;
                                for(i=1; i<5; i++)
                                {
                                    tmpvar = (tmpvar<<8) | MB_Message.u8Parameters[i];
                                }
                                VDPLAYER_DBG(printf("SampleRate: %lu\n", tmpvar));
                                u16Index = M4AParser_GetSampleRateIndex(tmpvar) ;
                                VDPLAYER_DBG(printf("SampleRate Index: %u\n", u16Index));

                                for(i=5; i<9; i++)
                                {
                                    tmpvar = (tmpvar<<8) | MB_Message.u8Parameters[i];
                                }
                                VDPLAYER_DBG(printf("AAC Stream Type: 0x%lx\n", tmpvar));

                                msAPI_Music_Init(MSAPI_AUD_DVB_AAC, INIT_VOLUME);  // Initail AAC
                            }
                            break;

                            case E_VDP_CODEC_ID_COOK:
                            {
                                U32 u32SampleRate;

                                VDPLAYER_DBG(printf("Share Memory Address :%lu\n",u32VdplayerShareMemAddr));
                                u16CodecNum=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_NUM_CODECID);
                                u16Samples_channel=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_SAMPLE_CHANNEL);
                                u32SampleRate=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_SAMPLE_RATE);
                                for(i=0;u16CodecNum>i;i++ )
                                {
                                    u16CannelsA[i]=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_NUM_CHANNEL+i);
                                    u16RegionsA[i]=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_NUM_REGIONS+i);
                                    u16cplStartA[i]=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_NUM_CPLSTART+i);
                                    u16cplQbitsA[i]=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_NUM_CPLQBITS+i);
                                    u16FrameSizeA[i]=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_FRAMESIZE+i);
                                }

                                VDPLAYER_DBG(printf("u16CodecNum %u\n",u16CodecNum));
                                VDPLAYER_DBG(printf("u16Samples_channel %u\n",u16Samples_channel));
                                VDPLAYER_DBG(printf("u32SampleRate %u\n",u32SampleRate));
                                for(i=0;u16CodecNum>i;i++ )
                                {
                                    // Modified by coverity_0442
                                    VDPLAYER_DBG(printf("u16CannelsA[%d] %u\n",i,u16CannelsA[i]));
                                    VDPLAYER_DBG(printf("u16RegionsA[%d] %u\n",i,u16RegionsA[i]));
                                    VDPLAYER_DBG(printf("u16cplStartA[%d] %u\n",i,u16cplStartA[i]));
                                    VDPLAYER_DBG(printf("u16cplQbitsA[%d] %u\n",i,u16cplQbitsA[i]));
                                    VDPLAYER_DBG(printf("u16FrameSizeA[%d] %u\n",i,u16FrameSizeA[i]));
                                }
                                msAPI_Music_Init(MSAPI_AUD_DVB_RA8LBR, INIT_VOLUME);
                                MApi_AUDIO_RA8_Param(u16CodecNum, u16Samples_channel, u32SampleRate, &u16CannelsA[0], &u16RegionsA[0], &u16cplStartA[0], &u16cplQbitsA[0], &u16FrameSizeA[0]);

                                MDrv_AUDIO_WriteDecMailBox(5, 0x00);
                            }
                            break;

                            case E_VDP_CODEC_ID_VORBIS:
                                msAPI_Music_Init(MSAPI_AUD_DVB_VORBIS, INIT_VOLUME);
                                break;
                            case E_VDP_CODEC_ID_DRA:
                                msAPI_Music_Init(MSAPI_AUD_DVB_DRA, INIT_VOLUME);
                                break;

                            default:
                                //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                //printf("          NOT SUPPORT AUDIO CODEC     \n");
                                //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                            break;
                        }
                    #if  AUDIO_SPDIF_ENABLE
                        if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                        else if(stGenSetting.g_SysSetting.fSPDIFMODE == 1)
                            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                    #endif
                        BOOL AutoSyncSTC;
                        AutoSyncSTC = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_AUDIO_AUTO_SYNC_STC);
                        if (!AutoSyncSTC)
                        {
                            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
                        }

                        break;

                        // MB_VDPLAYER_ACK_COPROCESSOR_TO_HK ----------------------------------------------
                        case MB_VDPLAYER_ACK_COPROCESSOR_TO_HK:
                            VDPLAYER_DVD_DBG(printf("MB_VDPLAYER_ACK_COPROCESSOR_TO_HK[0x%x][0x%x]\n", MB_Message.u8Parameters[0], MB_Message.u8Parameters[1]));
                            switch(MB_Message.u8Parameters[0])
                            {
                                case MB_VDPLAYER_INIT:
                                    u8VDPlayerInitResult = MB_Message.u8Parameters[1];
                                    if (u8VDPlayerInitResult == 0xFF)
                                        break;
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_INIT);
                                    enVDPlayerVideoType = (EN_VDPLAYER_VIDEO_TYPE)MB_Message.u8Parameters[2];

                                #if ENABLE_WMDRMPD
                                    u32WMDRMPDShareMemAddr = 0; //_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMDRMPD_SHAREMEM);
                                    VDPLAYER_DBG(printf("WMDRMPD share memory addr = %08x\n", u32WMDRMPDShareMemAddr));
                                  #if 0
                                    // For test only.
                                    if (MApp_VDPlayer_WMDRMPD_IsProtected())
                                    {
                                        if (!MApp_VDPlayer_WMDRMPD_GetLicense())
                                        {
                                            printf("GetLicense fail\n");
                                        }
                                    }
                                  #endif
                                #endif
                                    break;

                            #if ENABLE_DVD
                                case MB_VDPLAYER_DVD_INIT:
                                    u8VDPlayerInitResult = MB_Message.u8Parameters[1];
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_INIT);
                                    VDPLAYER_DVD_DBG(printf("Got DVD Init Ack\n"));
                                    break;

                                case MB_VDPLAYER_DVD_PREDECODE:
                                    VDPLAYER_DVD_DBG(printf("Got DVD Predecode Ack: pts = %d\n", _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_TIME)));
                                    MApp_DVD_SetValue(0, TRUE);
                                    break;

                                case MB_VDPLAYER_DVD_SEEKPLAY:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SEEKPLAY);
                                    VDPLAYER_DVD_DBG(printf("Got DVD SeekPlay Ack\n"));
                                    break;

                                case MB_VDPLAYER_DVD_WAITDONE:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_DONE);
                                    VDPLAYER_DVD_DBG(printf("Got DVD WaitDone Ack: pts = %d\n", _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_TIME)));
                                    break;

                                case MB_VDPLAYER_DVD_SCANSYNC:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SCANSYNC);
                                    VDPLAYER_DVD_DBG(printf("ScanSync Ack: pts = %d\n", _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_TIME)));
                                    break;

                                case MB_VDPLAYER_DVD_SCANDONE:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SCANDONE);
                                    VDPLAYER_DVD_DBG(printf("ScanDone Ack: pts = %d\n", _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_TIME)));
                                    break;

                                case MB_VDPLAYER_DVD_SCANEXIT:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SCANEXIT);
                                    VDPLAYER_DVD_DBG(printf("ScanExit Ack\n"));
                                    break;
                            #endif  // ENABLE_DVD
                                case MB_VDPLAYER_STOP:
                                    enVDPlayerVideoType = (EN_VDPLAYER_VIDEO_TYPE)MB_Message.u8Parameters[1];
                                    m_eVDPlayerAckFlags &=(enumVDPlayerAckFlags) ~E_ACKFLG_WAIT_STOP;
                                    #if ENABLE_DIVX_PLUS
                                    g_bChangeFile = FALSE;
                                    #endif
                                    break;

                                case MB_VDPLAYER_PLAY:
                                    m_eVDPlayerAckFlags &=(enumVDPlayerAckFlags) ~E_ACKFLG_WAIT_PLAY;
                                    break;

                                case MB_VDPLAYER_SET_AUDIO_TRACK_ID:
                                    u8VDPlayerSetAudioTrackResult = MB_Message.u8Parameters[1];
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_AUDIO_TRACK_ID);
                                    break;

                                case MB_VDPLAYER_SET_SUBTITLE_TRACKID:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_SUBTITLE_TRACKID);
                                    break;

                                case MB_VDPLAYER_TS_SET_PROGRAM:
                                    m_eVDPlayerAckFlags &=(enumVDPlayerAckFlags) ~E_ACKFLG_WAIT_TS_SET_PROGRAM;
                                    u8VDPlayerTsSetProgramResult = MB_Message.u8Parameters[1];
                                    break;
                            #if ENABLE_DRM
                                case MB_VDPLAYER_GET_DRM_REG_CODE:
                                    bDrmRegCode = MB_Message.u8Parameters[1];

                                    g_DRMRegCode[0] = MB_Message.u8Parameters[2];
                                    g_DRMRegCode[1] = MB_Message.u8Parameters[3];
                                    g_DRMRegCode[2] = MB_Message.u8Parameters[4];
                                    g_DRMRegCode[3] = MB_Message.u8Parameters[5];
                                    g_DRMRegCode[4] = MB_Message.u8Parameters[6];
                                    g_DRMRegCode[5] = MB_Message.u8Parameters[7];
                                    g_DRMRegCode[6] = MB_Message.u8Parameters[8];
                                    g_DRMRegCode[7] = MB_Message.u8Parameters[9];

                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_GET_DRM_REG_CODE);

                                    break;

                                case MB_VDPLAYER_GET_DRM_REG_CODE_2:
                                    g_DRMRegCode[8] = MB_Message.u8Parameters[1];
                                    g_DRMRegCode[9] = MB_Message.u8Parameters[2];

                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_GET_DRM_REG_CODE_2);

                                    break;

                                case MB_VDPLAYER_GET_DRM_DEACTIVATION_CODE:
                                    //bDrmRegCode =  pMB->u8Param[1];
                                    g_DRMDeactivationCode[0] = MB_Message.u8Parameters[2];
                                    g_DRMDeactivationCode[1] = MB_Message.u8Parameters[3];
                                    g_DRMDeactivationCode[2] = MB_Message.u8Parameters[4];
                                    g_DRMDeactivationCode[3] = MB_Message.u8Parameters[5];
                                    g_DRMDeactivationCode[4] = MB_Message.u8Parameters[6];
                                    g_DRMDeactivationCode[5] = MB_Message.u8Parameters[7];
                                    g_DRMDeactivationCode[6] = MB_Message.u8Parameters[8];
                                    g_DRMDeactivationCode[7] = MB_Message.u8Parameters[9];

                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_GET_DRM_DEACTIVATION_CODE);

                                    break;

                                case MB_VDPLAYER_CHECK_DRM_AUTHORIZATION:
                                    bDrmAuthorization   = MB_Message.u8Parameters[1];
                                    bDrmFileFormat      = MB_Message.u8Parameters[2];
                                    bDrmActivationFile  = MB_Message.u8Parameters[3];

                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION);

                                    break;

                                case MB_VDPLAYER_QUERY_DRM_RENTAL_STATUS:
                                    bDrmRentalStatus =MB_Message.u8Parameters[0];

                                    g_bDrmRental    = MB_Message.u8Parameters[1];
                                    g_u8DrmUseLimit = MB_Message.u8Parameters[2];
                                    g_u8DrmUseCount = MB_Message.u8Parameters[3];

                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_QUERY_DRM_RENTAL_STATUS);

                                    break;
                            #endif
                            /*
                                case MB_VDPLAYER_GET_SUBTITLE_STATE:
                                    u32GetSubtitleStateBuf = (((U32)MB_Message.u8Parameters[1]<<16)&0xFF0000) | (((U32)MB_Message.u8Parameters[2]<<8)&0xFF00)| (((U32)MB_Message.u8Parameters[3])&0xFF);

                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_GET_SUBTITLE_STATE);

                                    break;
                            */
                                case MB_VDPLAYER_REPEAT_AB:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_REPEAT_AB);
                                    break;
                                case MB_VDPLAYER_SUBTITLE_TIMESHIFT:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SUBTITLE_TIMESHIFT);
                                    break;
                                case MB_VDPLAYER_PAUSE:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_PAUSE);
                                    break;
                                case MB_VDPLAYER_SET_TRICK_MODE:
                                    u8VDPlayerSetTrickModeResult = MB_Message.u8Parameters[1];
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_TRICK_MODE);
                                    break;
                                case MB_VDPLAYER_SET_PLAYER_POSITION:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_SET_PLAYER_POSITION);
                                    break;
                                case MB_VDPLAYER_STEP:
                                    u8VDPlayerStepPlayResult = MB_Message.u8Parameters[1];
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_STEP);
                                    break;
                            #if ENABLE_DIVX_PLUS
                                case MB_VDPLAYER_SET_CHAPTER_ID:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_CHAPTER_ID);
                                    break;
                                case MB_VDPLAYER_SET_AUTOGEN_CHAPTER_ID:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_AUTOGEN_CHAPTER_ID);
                                    break;
                                case MB_VDPLAYER_SET_TITLE_ID:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_TITLE_ID);
                                    break;
                                case MB_VDPLAYER_SET_EDITION_ID:
                                    Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_EDITION_ID);
                                    break;
                            #endif
                                default:
                                    //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                    //printf("          Unkow Co-processor ACK(0x%x)        \n",MB_Message.u8Parameters[0]);
                                    //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                    break;

                            }
                        break;

                        // MB_VDPLAYER_SETUP_DISPLAY ----------------------------------------------
                        case MB_VDPLAYER_SETUP_DISPLAY:
                            {
                                U32 u32VdplayerBuffY0 = 0;
                                U8  u8TSStream = 0;
                                EN_VDPLAYER_VIDEO_TYPE enVideoType = (EN_VDPLAYER_VIDEO_TYPE)MB_Message.u8Parameters[0];
                                if(enVideoType == E_VDPLAYER_VIDEO_MJPEG)
                                {
                                    u32VdplayerBuffY0  = (((U32)MB_Message.u8Parameters[5]<<24)&0xFF000000) |
                                                         (((U32)MB_Message.u8Parameters[6]<<16)&0x00FF0000) |
                                                         (((U32)MB_Message.u8Parameters[7]<<8)&0x0000FF00) |
                                                         (((U32)MB_Message.u8Parameters[8])&0x000000FF);
                                }
                                else
                                {
                                    u8TSStream = MB_Message.u8Parameters[5];
                                }

                            #if SEAMLESS_PLAYING_ENABLE
                                if (!_bEnableSeamlessPlaying || !MApi_XC_IsFreezeImg(MAIN_WINDOW))
                            #endif
                                {
                                    _MApp_VDPlayer_SetupDisplayPath(MB_Message.u8Parameters[0],
                                        ((U16)(MB_Message.u8Parameters[1]<<8)&0xFF00)|(MB_Message.u8Parameters[2]&0x00FF),
                                        ((U16)(MB_Message.u8Parameters[3]<<8)&0xFF00)|(MB_Message.u8Parameters[4]&0x00FF),
                                        0,0,
                                        PANEL_WIDTH,PANEL_HEIGHT, u32VdplayerBuffY0,u8TSStream);
                                }

                            #if SEAMLESS_PLAYING_ENABLE
                                if (_bEnableSeamlessPlaying)
                                    _u32SeamlessTimer = (U32)MsOS_GetSystemTime();
                            #endif

                            #if ENABLE_DVD
                                VDPLAYER_DVD_DBG(printf("SetupDisp\n"));
                                if (bIsDVD)
                                    MApp_MPlayer_DVD_StartPlay();
                            #endif
                            }
                            if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE) == (U32)ENABLE_FBL_MODE)
                            {
                                printf("FBL mode: Ummute need to wait fpll done\n");
                                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, ENABLE, 0, MAIN_WINDOW);
                                U32 u32WhileEnteredTime = msAPI_Timer_GetTime0();
                                while(msAPI_Scaler_GetScreenMute(MAIN_WINDOW)&E_SCREEN_MUTE_BY_SCALER_FPLL)
                                {
                                    MApi_XC_Sys_CheckFpllStatusTask();
                                    if( msAPI_Timer_DiffTimeFromNow(u32WhileEnteredTime) > 3000 )
                                    {
                                        //Time out
                                        break;
                                    }
                                }
                            }
                            //==> Send mail.
                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                            /*ParameterCount*/  ,1
                            /*p1*/              ,MB_VDPLAYER_SETUP_DISPLAY
                            /*p2*/              ,0
                            /*p3*/              ,0
                            /*p4*/              ,0
                            /*p5*/              ,0
                            /*p6*/              ,0
                            /*p7*/              ,0
                            /*p8*/              ,0
                            /*p9*/              ,0
                            /*p10*/             ,0);

                            #if DYNSCALING
                            //send DS status mailbox to co-p after MB_VDPLAYER_SETUP_DISPLAY ack
                            if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING)==1)
                            {
                                _MApp_VDPlayer_SendXCStatus2Firmware(
                                    _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DYNSCALING_ADDRESS) + (1024*3), MAIN_WINDOW);
                            }
                            #endif

                            if(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_FRC_MODE))
                            {
                                MDrv_PQ_DisableFilmMode(PQ_MAIN_WINDOW,FALSE);
                            }
                            else
                            {
                                MDrv_PQ_DisableFilmMode(PQ_MAIN_WINDOW,TRUE);
                            }

                            MApp_UiMediaPlayer_Notify(E_MPLAYER_NOTIFY_SETUP_DISPLAY, NULL);
               #if (SUPPERTED_ADVERTISEMENT_MODE)
                            if ((m_eVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW) == 0)
                            {
                                MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                                msAPI_Scaler_SetBlueScreen( DISABLE,E_XC_FREE_RUN_COLOR_BLACK,  0, MAIN_WINDOW);
                                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, MAIN_WINDOW);
                                MM_TRACE();
                            }
                        #endif
                            break;

                        // MB_VDPLAYER_SET_DISPLAY_INFO ----------------------------------------------
                        case MB_VDPLAYER_SET_DISPLAY_INFO:
                        #if (SUPPERTED_ADVERTISEMENT_MODE)
                            if ((m_eVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW) == 0)
                                break;
                        #endif

                            if (gstVidStatus.u32FrameRate > 0)
                            {
                            #if (ENABLE_FDMASK_DELAY == ENABLE)
                                const XC_ApiInfo *pXC_ApiInfo;
                                U16 u16Delay;

                                pXC_ApiInfo = MApi_XC_GetInfo();
                                if (gstVidStatus.u8Interlace)
                                {
                                    u16Delay = (1000000UL * DEFAULT_FIELD_COUNT) / gstVidStatus.u32FrameRate;
                                }
                                else
                                {
                                    u16Delay = (1000000UL * DEFAULT_FIELD_COUNT) / gstVidStatus.u32FrameRate;
                                }
                            #else
                                U16 u16Delay = (1000000UL * DEFAULT_FIELD_COUNT) / gstVidStatus.u32FrameRate;
                            #endif  // #if (ENABLE_FDMASK_DELAY == ENABLE)

                                if (u16Delay >= 1000)
                                    u16Delay = 1000;
                                msAPI_VDPlayer_ScreenDisplaySetting( (EN_VDPLAYER_SCREEN_SETTINGS)MB_Message.u8Parameters[0] ,MB_Message.u8Parameters[1], u16Delay );
                            }
                            else
                            {
                                msAPI_VDPlayer_ScreenDisplaySetting( (EN_VDPLAYER_SCREEN_SETTINGS)MB_Message.u8Parameters[0] , MB_Message.u8Parameters[1],  DEFAULT_SCREEN_UNMUTE_TIME );
                            }
                            break;

                        // MB_VDPLAYER_CLOSE_DISPLAY ----------------------------------------------
                        case MB_VDPLAYER_CLOSE_DISPLAY:
                            {
                            #if SEAMLESS_PLAYING_ENABLE
                                if (_bEnableSeamlessPlaying)
                                {
                                    _u32SeamlessTimer = (U32)MsOS_GetSystemTime()+100000;
                                    MApi_XC_FreezeImg(ENABLE, MAIN_WINDOW);
                                }
                                else
                            #endif
                                {
                                    // Disable scaler periodic task
                                    MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), DISABLE);

                                    msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                                    //MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
                                    MDrv_MVOP_Enable(FALSE);
                                }
                                EN_VDPLAYER_VIDEO_TYPE enVideoType = (EN_VDPLAYER_VIDEO_TYPE)MB_Message.u8Parameters[0];
                                if(enVideoType== E_VDPLAYER_VIDEO_MJPEG)
                                {
                                    #if (ENABLE_MIU_1 == ENABLE)
                                    MDrv_MVOP_MiuSwitch(1);
                                    #endif
                                }
                            }
                        break;

                        // MB_VDPLAYER_MPEG_SUBTITLE_SETHEADERINFO ----------------------------------------------
                        case MB_VDPLAYER_MPEG_SUBTITLE_SETHEADERINFO:
                            {
                                U32 numb;
                                U32 addr;

                                //printf("Subtitle set header information: sbtype:%d; videotype:%d\n", (U16)pMB->u8Param[0] , (U16)pMB->u8Param[1]);
                                 switch ( u32subtitletype)
                                {
                                    case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
                                        numb = MB_Message.u8Parameters[2];
                                        addr = COMBU32(MB_Message.u8Parameters[3], MB_Message.u8Parameters[4], MB_Message.u8Parameters[5], MB_Message.u8Parameters[6]);
                                        addr = _PA2VA(addr);

                                        if (numb && addr)
                                        {
                                            U32 buf[16];

                                            memset(buf, 0, sizeof(buf));
                                            memcpy(&buf,(U8*)addr,64);
                                        #if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)
                                            msAPI_MpegSP_SetPalette(buf,  numb);
                                        #endif
                                        }
                                        break;


                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
                                        break;

                                    default:
                                        break;
                                }
                                break;
                            }

                        // MB_VDPLAYER_SPUQUEUE_PUSH ----------------------------------------------
                        case MB_VDPLAYER_SPUQUEUE_PUSH:
                    #if (ENABLE_INTERNAL_SUBTITLE)
                        {
                            U32 u32PTS1;
                            U32 u32PTS2;

                            switch (u32subtitletype)
                            {
                            #if (TS_INTERNAL_SUBTITLE_BMP)
                                case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS:
                                    {
                                        U32 u32SdramAddr=0;
                                        U16 u16PesLen=0;

                                        u32SdramAddr = COMBU32(MB_Message.u8Parameters[0], MB_Message.u8Parameters[1], MB_Message.u8Parameters[2],MB_Message.u8Parameters[3]);
                                        u16PesLen = COMBU16(MB_Message.u8Parameters[4], MB_Message.u8Parameters[5]);
                                        u32PTS1 = COMBU32(MB_Message.u8Parameters[6], MB_Message.u8Parameters[7], MB_Message.u8Parameters[8], MB_Message.u8Parameters[9]);
                                        BMP_DBG(printf("@@BMP pushQ, PTS:%d, Addr:0x%x, Len:0x%x\n",u32PTS1,u32SdramAddr,u16PesLen));
                                        msAPI_Subtitle_Queue_Push(_PA2VA(u32SdramAddr), u16PesLen, u32PTS1); //msAPI_Subtitle_Queue_Push use VA
                                    #if 0
                                        //==> Send mail.
                                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                        /*ParameterCount*/  ,1
                                        /*p1*/              ,MB_VDPLAYER_SPUQUEUE_PUSH
                                        /*p2*/              ,0
                                        /*p3*/              ,0
                                        /*p4*/              ,0
                                        /*p5*/              ,0
                                        /*p6*/              ,0
                                        /*p7*/              ,0
                                        /*p8*/              ,0
                                        /*p9*/              ,0
                                        /*p10*/             ,0);
                                    #endif
                                    }
                                    break;
                            #endif

                            #if (TS_INTERNAL_SUBTITLE_PGS)
                                case E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS:
                                    {
                                        U32 u32SdramAddr=0;
                                        U16 u16PesLen=0;

                                        u32SdramAddr = COMBU32(MB_Message.u8Parameters[0], MB_Message.u8Parameters[1], MB_Message.u8Parameters[2],MB_Message.u8Parameters[3]);
                                        u16PesLen = COMBU16(MB_Message.u8Parameters[4], MB_Message.u8Parameters[5]);
                                        u32PTS1 = COMBU32(MB_Message.u8Parameters[6], MB_Message.u8Parameters[7], MB_Message.u8Parameters[8], MB_Message.u8Parameters[9]);
                                        PGS_DBG(printf("@@PGS PushQ, PTS:%d, Addr:0x%x, Len:0x%x\n",u32PTS1,u32SdramAddr,u16PesLen));
                                        msAPI_Subtitle_Queue_Push(_PA2VA(u32SdramAddr), u16PesLen, u32PTS1); //msAPI_Subtitle_Queue_Push use VA
                                    }
                                    break;
                            #endif

                                case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
                                  #if (ENABLE_INTERNAL_BMP_SUBTITLE)
                                    spuqueuesize = (((U16) MB_Message.u8Parameters[4] << 8) & 0xFF00) | (((U16)MB_Message.u8Parameters[5])&0x00FF);
                                    u32PTS1 = (((U32)MB_Message.u8Parameters[6]<<24)&0xFF000000) |
                                              (((U32)MB_Message.u8Parameters[7]<<16)&0x00FF0000) |
                                              (((U32)MB_Message.u8Parameters[8]<<8)&0x0000FF00) |
                                              (((U32)MB_Message.u8Parameters[9])&0x000000FF);

                                    msAPI_VDPlayer_SubtitlePushQueue((EN_VDP_CODECID)u32subtitletype, spuqueueaddr, (U32)spuqueuesize, u32PTS1, 0);

                                    //u8subtitletype = pMB->u8Param[0];
                                  #endif
                                    break;

                                case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:    //divx
                                  #if (ENABLE_INTERNAL_BMP_SUBTITLE)
                                    {
                                        U16 len = COMBU16(MB_Message.u8Parameters[2], MB_Message.u8Parameters[3]);
                                        U32 adr = COMBU32(MB_Message.u8Parameters[4], MB_Message.u8Parameters[5],MB_Message.u8Parameters[6], MB_Message.u8Parameters[7]);

                                        msAPI_VDPlayer_SubtitlePushQueue((EN_VDP_CODECID)u32subtitletype, adr, len, 0, 0);

                                        //u8subtitletype = pMB->u8Param[0];
                                    }
                                  #endif
                                    break;
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
                                  #if (ENABLE_INTERNAL_TEXT_SUBTITLE)
                                    spuqueuesize = (((U16) MB_Message.u8Parameters[8] << 8) & 0xFF00) | (((U16)MB_Message.u8Parameters[9])&0x00FF);
                                    u32PTS1 = (((U32)MB_Message.u8Parameters[2]<<24)&0xFF000000) |
                                              (((U32)MB_Message.u8Parameters[3]<<16)&0x00FF0000) |
                                              (((U32)MB_Message.u8Parameters[4]<<8)&0x0000FF00) |
                                              (((U32)MB_Message.u8Parameters[5])&0x000000FF);
                                    u32PTS2 = (((U32)MB_Message.u8Parameters[6]<<8)&0x0000FF00) | (((U32)MB_Message.u8Parameters[7])&0x000000FF);
                                    u32PTS2 += u32PTS1;

                                    msAPI_VDPlayer_SubtitlePushQueue( (EN_VDP_CODECID)u32subtitletype, /*pMB->u8Param[1],*/ spuqueueaddr,spuqueuesize, u32PTS1  , u32PTS2 );
                                  #endif
                                    break;

                                default:// unknow format
                                    break;
                            }

                            spuqueueaddr=0;
                            spuqueuesize=0;

                        }
                    #endif //#if (ENABLE_INTERNAL_SUBTITLE)
                            break;
                        // MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR ----------------------------------------------
                        case MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR:
                          #if (TS_INTERNAL_SUBTITLE_BMP)
                            if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
                            {
                                /// provide subtitle decoder PES Queue buffer.
                                {
                                    BMP_DBG(printf("@@BMP get Q SDRAM addr\n"));
                                    U32 u32SDRAMAddress = msAPI_Subtitle_Queue_GetSDRAMAddress(0);
                                    u32SDRAMAddress = _VA2PA(u32SDRAMAddress);
                                    U32 u32ST_QLength = msAPI_Subtitle_GetQueueLength();

                                    VDPLAYER_DBG(printf("\tsubtitle queue buffer addr:0x%x  len:0x%x\n",u32SDRAMAddress,u32ST_QLength));
                                    //==> Send mail.
                                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                    /*ParameterCount*/  ,10
                                    /*p1*/              ,MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR
                                    /*p2*/              ,GetByte3(u32SDRAMAddress)
                                    /*p3*/              ,GetByte2(u32SDRAMAddress)
                                    /*p4*/              ,GetByte1(u32SDRAMAddress)
                                    /*p5*/              ,GetByte0(u32SDRAMAddress)
                                    /*p6*/              ,GetByte3(u32ST_QLength)
                                    /*p7*/              ,GetByte2(u32ST_QLength)
                                    /*p8*/              ,GetByte1(u32ST_QLength)
                                    /*p9*/              ,GetByte0(u32ST_QLength)
                                    /*p10*/             ,(U8)EN_VDP_FILE_FORMAT_TS);
                                }
                                break;
                            }
                          #endif
                          #if (TS_INTERNAL_SUBTITLE_PGS)
                            if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
                            {
                                /// provide subtitle decoder PES Queue buffer.
                                {
                                    PGS_DBG(printf("@@PGS get Q SDRAM addr\n"));
                                    U32 u32SDRAMAddress = msAPI_Subtitle_Queue_GetSDRAMAddress(0);
                                    u32SDRAMAddress = _VA2PA(u32SDRAMAddress);
                                    U32 u32ST_QLength = msAPI_Subtitle_GetQueueLength();

                                    VDPLAYER_DBG(printf("\tsubtitle queue buffer addr:0x%x  len:0x%x\n",u32SDRAMAddress,u32ST_QLength));
                                    //==> Send mail.
                                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                    /*ParameterCount*/  ,10
                                    /*p1*/              ,MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR
                                    /*p2*/              ,GetByte3(u32SDRAMAddress)
                                    /*p3*/              ,GetByte2(u32SDRAMAddress)
                                    /*p4*/              ,GetByte1(u32SDRAMAddress)
                                    /*p5*/              ,GetByte0(u32SDRAMAddress)
                                    /*p6*/              ,GetByte3(u32ST_QLength)
                                    /*p7*/              ,GetByte2(u32ST_QLength)
                                    /*p8*/              ,GetByte1(u32ST_QLength)
                                    /*p9*/              ,GetByte0(u32ST_QLength)
                                    /*p10*/             ,(U8)EN_VDP_FILE_FORMAT_TS);
                                }
                                break;
                            }
                          #endif
                            {
                                switch (u32subtitletype)
                                {
                                    case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
                                    case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
                                        {
                                            U16 len = COMBU16(MB_Message.u8Parameters[2], MB_Message.u8Parameters[3]);
                                            U32 adr = 0;

                                            //Because internal image subtitle and external image subtitle using the same SPU Queue,
                                            //it needs to suspend image subtitle which is given 0 address from coprocessor while SUBIDX enable.
                                            if(m_bSuspendInternalSubtitle2Queue)
                                            {
                                                adr = 0;
                                            }
                                            else
                                            {
                                              #if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)
                                                adr = msAPI_MpegSP_SpuQueue_GetSDRAMAddress(len);
                                              #else
                                                adr = 0xFFFFFFFFUL;
                                              #endif
                                            }

                                            //==> Send mail.
                                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                            /*ParameterCount*/  ,5
                                            /*p1*/              ,MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR
                                            /*p2*/              ,GetByte3(adr)
                                            /*p3*/              ,GetByte2(adr)
                                            /*p4*/              ,GetByte1(adr)
                                            /*p5*/              ,GetByte0(adr)
                                            /*p6*/              ,0
                                            /*p7*/              ,0
                                            /*p8*/              ,0
                                            /*p9*/              ,0
                                            /*p10*/             ,0);
                                            spuqueueaddr = adr;
                                            spuqueuesize = len;
                                        }
                                        break;

                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
#if (ENABLE_INTERNAL_TEXT_SUBTITLE)
                                      #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                        if(u8IsFontTableReady)
                                        {
                                            U16 len = COMBU16(MB_Message.u8Parameters[2], MB_Message.u8Parameters[3]);
                                        #if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)
                                            U32 adr = msAPI_MpegSP_SpuQueue_GetSDRAMAddress(len);
                                        #else
                                            U32 adr=0;
                                        #endif
                                            //==> Send mail.
                                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                            /*ParameterCount*/  ,5
                                            /*p1*/              ,MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR
                                            /*p2*/              ,GetByte3(adr)
                                            /*p3*/              ,GetByte2(adr)
                                            /*p4*/              ,GetByte1(adr)
                                            /*p5*/              ,GetByte0(adr)
                                            /*p6*/              ,0
                                            /*p7*/              ,0
                                            /*p8*/              ,0
                                            /*p9*/              ,0
                                            /*p10*/             ,0);
                                            spuqueueaddr = adr;
                                            spuqueuesize = len;
                                        }
                                        else
                                      #endif
                                        {
                                            static U32 u32SizeAlloc = 0;

                                            u32SizeAlloc += MAX_INTERNAL_TEXT_SUBTITLE_LEN;
                                        #if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
                                            if(u32SizeAlloc >= INTERNAL_TEXT_SUBTITLE_BUFFER_SIZE)
                                        #else
                                            if(u32SizeAlloc >= MP4_SUBTITLE_BUFFER_LEN / 2)
                                        #endif
                                            {
                                                u32SizeAlloc = 0;
                                            }
                                            spuqueueaddr= INTERNAL_TEXT_SUBTITLE_BUFFER_ADR+u32SizeAlloc;
                                            spuqueuesize=MAX_INTERNAL_TEXT_SUBTITLE_LEN;

                                            //==> Send mail.
                                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                            /*ParameterCount*/  ,5
                                            /*p1*/              ,MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR
                                            /*p2*/              ,(U8)((spuqueueaddr&0xFF000000)>>24)
                                            /*p3*/              ,(U8)((spuqueueaddr&0x00FF0000)>>16)
                                            /*p4*/              ,(U8)((spuqueueaddr&0x0000FF00)>>8)
                                            /*p5*/              ,(U8)(spuqueueaddr&0x000000FF)
                                            /*p6*/              ,0
                                            /*p7*/              ,0
                                            /*p8*/              ,0
                                            /*p9*/              ,0
                                            /*p10*/             ,0);
                                        }
#endif //(ENABLE_INTERNAL_TEXT_SUBTITLE)
                                        break;

                                    default:
                                        break;
                                }

                                break;
                            }

                        // MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW ----------------------------------------------
                        case MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW:
                        {
                        #if (TS_INTERNAL_SUBTITLE_BMP)
                            if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
                            {
                                BMP_DBG(printf("@@BMP MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW\n"));
                                _bSubtitleShow_MW = MB_Message.u8Parameters[2];

                                if (!(_bSubtitleShow_MW && _bSubtitleShow_User && (u8InternalST_Num>0)))
                                {
                                    MApp_VDPlayer_TS_SubtitleErase();
                                }
                                break;
                            }
                        #endif
                        #if (TS_INTERNAL_SUBTITLE_PGS)
                            if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
                            {
                                PGS_DBG(printf("@@PGS MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW\n"));
                                _bSubtitleShow_MW = MB_Message.u8Parameters[2];

                                if (!(_bSubtitleShow_MW && _bSubtitleShow_User && (u8InternalST_Num>0)))
                                {
                                    MApp_VDPlayer_TS_SubtitleErase();
                                }
                                break;
                            }
                        #endif

                            switch (u32subtitletype)
                            {
                                case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
                                case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
                                  #if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)
                                    /*  mark internal subtitle controlled by Coprocessor, only controlled by UI
                                    if (MB_Message.u8Parameters[2] == TRUE)
                                    {
                                        msAPI_MpegSP_Show();
                                    }
                                    else
                                    {
                                        msAPI_MpegSP_Unshow();
                                    }
                                    */
                                    /*
                                    if (msAPI_MailBox_WaitReady())
                                    {
                                        MailBoxPara.u8CmdClass  = MB_CLASS_VDPLAYER;
                                        MailBoxPara.u8CmdIdx    = MB_VDPLAYER_ACK_HK_TO_COPROCESSOR;
                                        MailBoxPara.ParamCnt    = 1;
                                        MailBoxPara.CMDType     = MB_CMD_TYPE_DEFAULT;
                                        MailBoxPara.u8Param[0]  = MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW;
                                        msAPI_MailBox_SendMsg();
                                    }
                                    */
                                  #endif
                                    break;

                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                                case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
                                {
#if (ENABLE_INTERNAL_TEXT_SUBTITLE)
                                    BOOLEAN bSUBTITLE_SHOW = MB_Message.u8Parameters[2];
                                    // need to check timothy.h
                                    if (bSUBTITLE_SHOW == ENABLE)
                                    {
                                    #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                        if(u8IsFontTableReady)
                                        {
                                          #if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)
                                        /*  mark internal subtitle controlled by Coprocessor, only controlled by UI
                                            msAPI_MpegSP_Show();
                                        */
                                          #endif
                                        }
                                        else
                                    #endif
                                        {
                                            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT,(U32)(MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT-u16SubtitleTagCnt));
                                        }
                                    }
                                    else
                                    {
                                    #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                        if(u8IsFontTableReady)
                                        {
                                        #if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)
                                        /*  mark internal subtitle controlled by Coprocessor, only controlled by UI
                                            msAPI_MpegSP_Unshow();
                                        */
                                        #endif
                                        }
                                        else
                                    #endif
                                        {
                                            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, 0 );
                                        }
                                    }
                                    /*
                                    if (msAPI_MailBox_WaitReady())
                                    {
                                        MailBoxPara.u8CmdClass  = MB_CLASS_VDPLAYER;
                                        MailBoxPara.u8CmdIdx    = MB_VDPLAYER_ACK_HK_TO_COPROCESSOR;
                                        MailBoxPara.ParamCnt    = 1;
                                        MailBoxPara.CMDType     = MB_CMD_TYPE_DEFAULT;
                                        MailBoxPara.u8Param[0]  = MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW;
                                        msAPI_MailBox_SendMsg();
                                    }
                                    */
#endif //(ENABLE_INTERNAL_TEXT_SUBTITLE)
                                    break;
                                }

                                default:
                                    break;
                            }

                            break;
                        }


                        // MB_VDPLAYER_MPEG_SUBTITLE_RESET ----------------------------------------------
                        case MB_VDPLAYER_MPEG_SUBTITLE_RESET:
                            //==> Send mail.
                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                            /*ParameterCount*/  ,1
                            /*p1*/              ,MB_VDPLAYER_MPEG_SUBTITLE_RESET
                            /*p2*/              ,0
                            /*p3*/              ,0
                            /*p4*/              ,0
                            /*p5*/              ,0
                            /*p6*/              ,0
                            /*p7*/              ,0
                            /*p8*/              ,0
                            /*p9*/              ,0
                            /*p10*/             ,0);
                            break;

                        case MB_VDPLAYER_SET_SUBTITLE_TRACKID:
                          #if (TS_INTERNAL_SUBTITLE_BMP)
                            if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
                            {
                                BMP_DBG(printf("@@BMP Set subtitle trackid\n"));
                                u16CPageID = COMBU16(MB_Message.u8Parameters[0], MB_Message.u8Parameters[1]);
                                u16APageID = COMBU16(MB_Message.u8Parameters[2], MB_Message.u8Parameters[3]);

                            #if(ENABLE_API_MMAP_GET_BUF) // Use MMAP API
                                U32 u32SubtitleBufAddr = 0, u32SubtitleBufSize = 0;
                                msAPI_MMAP_Get_BufInfo(E_BUFID_SUBTITLE, &u32SubtitleBufAddr, &u32SubtitleBufSize );
                                msAPI_Subtitle_Init_Queue(_PA2VA(u32SubtitleBufAddr), u32SubtitleBufSize);
                            #else
                                msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN);
                            #endif

                                MApp_TS_Subtitle_SetVideoInfo(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH),_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT));
                                msAPI_Subtitle_SetPageIDs(u16CPageID, u16APageID);

                                MApp_VDPlayer_TS_SubtitleErase();
                            }
                          #endif
                          #if (TS_INTERNAL_SUBTITLE_PGS)
                            if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
                            {
                                PGS_DBG(printf("@@PGS set subtitle trackid\n"));
                                u16CPageID = COMBU16(MB_Message.u8Parameters[0], MB_Message.u8Parameters[1]);
                                u16APageID = COMBU16(MB_Message.u8Parameters[2], MB_Message.u8Parameters[3]);

                            #if(ENABLE_API_MMAP_GET_BUF) // Use MMAP API
                                U32 u32SubtitleBufAddr = 0, u32SubtitleBufSize = 0;
                                msAPI_MMAP_Get_BufInfo(E_BUFID_SUBTITLE, &u32SubtitleBufAddr, &u32SubtitleBufSize );
                                msAPI_Subtitle_Init_Queue(_PA2VA(u32SubtitleBufAddr), u32SubtitleBufSize);
                            #else
                                msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN);
                            #endif

                                MApp_TS_Subtitle_SetVideoInfo(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH),_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT));
                                msAPI_Subtitle_SetPageIDs(u16CPageID, u16APageID);

                                MApp_VDPlayer_TS_SubtitleErase();
                            }
                          #endif
                            break;

                        // MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT ----------------------------------------------
                        case MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT:
                        {
#if ENABLE_SUBTITLE_DMP
                            U8 u8Cmd = MB_Message.u8Parameters[0];
                            u32subtitletype = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_SUBTITLE_CODEC_ID);
                          #if (TS_INTERNAL_SUBTITLE_BMP)
                            if ((u8Cmd == E_SUBTITLE_INIT_COMMAND_INIT) && (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS))
                            {
                                BMP_DBG(printf("@@BMP init\n"));
                                //(printf("\tTS subtitle init \n"));
                                //(printf("\tMB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT \n"));
                                //(printf("\tSubtitle Init Queue,SUBTITLE_ADR:0x%x, SUBTITLE_LEN:0x%x\n",SUBTITLE_ADR, SUBTITLE_LEN));
                                //(printf("\tTSP subtitle buffer addr:0x%x, len:0x%x\n",u32SubtitleAddr,u32SubtitleSize));

                            #if(ENABLE_API_MMAP_GET_BUF) // Use MMAP API
                                U32 u32SubtitleBufAddr = 0, u32SubtitleBufSize = 0;
                                msAPI_MMAP_Get_BufInfo(E_BUFID_SUBTITLE, &u32SubtitleBufAddr, &u32SubtitleBufSize );
                                msAPI_Subtitle_Init_Queue(_PA2VA(u32SubtitleBufAddr), u32SubtitleBufSize);
                            #else
                                msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN);
                            #endif

                                MApp_TS_Subtitle_SetVideoInfo(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH),_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT));
                                /// Init ack
                                //==> Send mail.
                                VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                /*ParameterCount*/  ,2
                                /*p1*/              ,MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT
                                /*p2*/              ,(U8)EN_VDP_FILE_FORMAT_TS
                                /*p3*/              ,0
                                /*p4*/              ,0
                                /*p5*/              ,0
                                /*p6*/              ,0
                                /*p7*/              ,0
                                /*p8*/              ,0
                                /*p9*/              ,0
                                /*p10*/             ,0);

                                //Control Subtitle
                                _bSubtitleShow_MW = ENABLE;
                                u8IsSubtitleBusy = FALSE;
                                u8IssubtitleInit = TRUE;
                                u8IsSubtitleInitfinish = TRUE;

                                VDPLAYER_DBG(printf( " [Aeon OS] TS subtitle init success \n"));
                                u8InternalST_Num = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_SUBTITLE);
                                break;
                            }
                            else if ((u8Cmd == E_SUBTITLE_INIT_COMMAND_DEINIT) && (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS))
                            {
                                BMP_DBG(printf("@@BMP deinit\n"));
                                MApp_VDPlayer_TS_SubtitleErase();
                                MApp_TS_Subtitle_SetVideoInfo(0,0);
                                u8IssubtitleInit = FALSE;
                                _bSubtitleShow_MW   = DISABLE;      // control by MW.
                                u8InternalST_Num = 0;
                                u8IsSubtitleInitfinish = FALSE;
                                break;
                            }
                          #else
                            if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
                            {
                                return;
                            }
                          #endif //#if (TS_INTERNAL_SUBTITLE_BMP)

                          #if (TS_INTERNAL_SUBTITLE_PGS)
                            if ((u8Cmd == E_SUBTITLE_INIT_COMMAND_INIT) && (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS))
                            {
                                PGS_DBG(printf("@@PGS init\n"));
                                //(printf("\t@@PGS TS subtitle init \n"));
                                //(printf("\t@@PGS MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT \n"));
                                //(printf("\t@@PGS Subtitle Init Queue,SUBTITLE_ADR:0x%x, SUBTITLE_LEN:0x%x\n",SUBTITLE_ADR, SUBTITLE_LEN));
                                //(printf("\t@@PGS TSP subtitle buffer addr:0x%x, len:0x%x\n",u32SubtitleAddr,u32SubtitleSize));

                                msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN);
                                MApp_TS_Subtitle_SetVideoInfo(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH),_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT));
                                /// Init ack
                                //==> Send mail.
                                VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                /*ParameterCount*/  ,2
                                /*p1*/              ,MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT
                                /*p2*/              ,(U8)EN_VDP_FILE_FORMAT_TS
                                /*p3*/              ,0
                                /*p4*/              ,0
                                /*p5*/              ,0
                                /*p6*/              ,0
                                /*p7*/              ,0
                                /*p8*/              ,0
                                /*p9*/              ,0
                                /*p10*/             ,0);

                                //Control Subtitle
                                _bSubtitleShow_MW = ENABLE;
                                u8IsSubtitleBusy = FALSE;
                                u8IssubtitleInit = TRUE;
                                u8IsSubtitleInitfinish = TRUE;

                                VDPLAYER_DBG(printf( " [Aeon OS] TS subtitle init success \n"));
                                u8InternalST_Num = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_SUBTITLE);
                                break;
                            }
                            else if ((u8Cmd == E_SUBTITLE_INIT_COMMAND_DEINIT) && (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS))
                            {
                                PGS_DBG(printf("@@PGS deinit\n"));
                                MApp_VDPlayer_TS_SubtitleErase();
                                MApp_TS_Subtitle_SetVideoInfo(0,0);
                                u8IssubtitleInit = FALSE;
                                _bSubtitleShow_MW   = DISABLE;      // control by MW.
                                u8InternalST_Num = 0;
                                u8IsSubtitleInitfinish = FALSE;
                                break;
                            }
                          #else
                            if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
                            {
                                return;
                            }
                          #endif //#if (TS_INTERNAL_SUBTITLE_PGS)

                            if (u8Cmd == E_SUBTITLE_INIT_COMMAND_INIT)
                            {
                                switch( u32subtitletype )
                                {
                                    case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
                                    case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
                                      #if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)
                                        if (!msAPI_MpegSP_Init())
                                        {
                                            VDPLAYER_DBG(printf("subtitle picture init failed\n"));

                                            return;
                                        }
                                        MApp_MPlayer_EnableInternalSubtitle(TRUE);
                                        u8IssubtitleInit = TRUE;

                                        //if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)
                                        {
                                            msAPI_MpegSP_SetSubtitleDimension(COMBU16(MB_Message.u8Parameters[5], MB_Message.u8Parameters[6]), COMBU16(MB_Message.u8Parameters[7], MB_Message.u8Parameters[8]));
                                        }
                                        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT,MAX_SPU_QUEUE_SIZE);
                                        break;
                                      #else
                                        return;
                                      #endif //#if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)

                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                                    case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
                                    {
#if (ENABLE_INTERNAL_TEXT_SUBTITLE)
                                    #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                        U32 u32FontTableSize;
                                        u32FontTableSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_SUBTITLE_ATTACHEDFILE_SIZE);

                                        if( u32FontTableSize > 0 )
                                        {
                                            U32 u32FontTableAddr;
                                            u32FontTableAddr = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_SUBTITLE_ATTACHEDFILE_BUFF_ADDR);
                                            u32FontTableAddr = _PA2VA(u32FontTableAddr);
                                        #if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)
                                            if (!msAPI_MpegSP_Init())
                                        #endif
                                            {
                                                VDPLAYER_DBG(printf("subtitle picture init failed\n"));

                                                return;
                                            }
                                            MApp_MPlayer_EnableInternalSubtitle(TRUE);

                                            if (!msAPI_DivXTTF_InitTTF(u32FontTableAddr,u32FontTableSize))
                                            {
                                                VDPLAYER_DBG(printf("True type font init failed\n"));
                                                return;
                                            }

                                            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT,MAX_SPU_QUEUE_SIZE);
                                            u8IssubtitleInit = TRUE;
                                            u8IsFontTableReady = TRUE;
                                        }
                                        else
                                    #endif
                                        {

                                        #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                            u8IsFontTableReady = FALSE;
                                        #endif
                                            MApp_VDPlayer_TextSubtitleInit();
                                            //MApp_MPlayer_SubtitleInit();
                                            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT);
                                            spuqueueaddr= (((U32)u16tagposition)<<8) + INTERNAL_TEXT_SUBTITLE_BUFFER_ADR;
                                            //spulen=MP4_SUBTITLE_BUFFER_LEN;
                                        }
#endif //(ENABLE_INTERNAL_TEXT_SUBTITLE)
                                    }
                                        break;
                                    default:// unknow format
                                        break;
                                }

                                //==> Send mail.
                                VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                /*ParameterCount*/  ,1
                                /*p1*/              ,MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT
                                /*p2*/              ,0
                                /*p3*/              ,0
                                /*p4*/              ,0
                                /*p5*/              ,0
                                /*p6*/              ,0
                                /*p7*/              ,0
                                /*p8*/              ,0
                                /*p9*/              ,0
                                /*p10*/             ,0);

                                VDPLAYER_DBG(printf( " [Aeon OS] subtitle init success \n"));

                                u8IsSubtitleBusy        = FALSE;
                            }
                            else if (u8Cmd == E_SUBTITLE_INIT_COMMAND_DEINIT)
                            {
                                //if (pMB->u8Param[1] == TRUE)
                                {
                                  #if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)
                                    msAPI_MpegSP_Dinit();
                                  #endif
                                }

                                //if (pMB->u8Param[2] == TRUE)
                                {
//                                    MApp_MPlayer_SubtitleInit();
                                    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT,0);
                                }

                                u8IssubtitleInit        = FALSE;
                                u32subtitletype          = 0;
                                u8IsSubtitleBusy        = FALSE;
                                u8IsSubtitleInitfinish  = FALSE;
                                u32GetSubtitleStateBuf  = 0;
                              #if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                u8IsFontTableReady=FALSE;
                              #endif
                            }
                            else
                            {
                                u8IsSubtitleInitfinish = TRUE;
                            }

                            break;
#endif //ENABLE_SUBTITLE_DMP
                        }

                    case MB_VDPLAYER_MPEG_SUBTITLE_GETQUEUEINFO:
                    {
                    #if (ENABLE_INTERNAL_BMP_SUBTITLE==ENABLE)
                        U8 queuecount = msAPI_MpegSP_SpuQueue_GetCount();
                    #else
                        U8 queuecount = 0;
                    #endif
                        //==> Send mail.
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,2
                        /*p1*/              ,MB_VDPLAYER_MPEG_SUBTITLE_GETQUEUEINFO
                        /*p2*/              ,queuecount
                        /*p3*/              ,0
                        /*p4*/              ,0
                        /*p5*/              ,0
                        /*p6*/              ,0
                        /*p7*/              ,0
                        /*p8*/              ,0
                        /*p9*/              ,0
                        /*p10*/             ,0);
                    }
                        break;
#if ENABLE_DRM
                    case MB_VDPLAYER_SET_REPLAYBACK:
                        g_bReplay = TRUE;
                        break;
#endif
                    case MB_VDPLAYER_AUDIO_UNSUPPORT:  //20100809EL
                        g_bUnsupportAudio = TRUE;
                        //printf(">>>>>111  MB_VDPLAYER_AUDIO_UNSUPPORT\n");
                        break;
        case MB_VDPLAYER_RATING_CONTROL:
#if ENBALE_PARENTALRATING_MM
            MApp_UiMediaPlayer_Notify(E_MPLAYER_NOTIFY_MOVIE_RATING_CONTROL,NULL);
#endif
            break;

                    case MB_VDPLAYER_LOAD_VDECBIN:
                      #if (ENABLE_DYNAMIC_LOAD_VDECBIN)
                        {
                            BOOLEAN bResult=FALSE;
                            BININFO BinInfo;
                            U32 u32FWBinSize=0;
                            U32 u32VLCBinSize = 0;
                            memset(&BinInfo,0,sizeof(BININFO));
#if ENABLE_VDEC_2_0
                            BinInfo.B_ID = BIN_ID_MM_VPU;
                            u32VLCBinSize = 0;
#else

                            switch (MB_Message.u8Parameters[0])
                            {
                                case E_VDP_VIDEO_H264:
                                case E_VDP_VIDEO_MJPEG:
                                case E_VDP_VIDEO_RM:
                                case E_VDP_VIDEO_AVS:
                                case E_VDP_VIDEO_VP8:
                                case E_VDP_VIDEO_MVC:
                                    BinInfo.B_ID = BIN_ID_MM_HVD;
                                    break;

                                case E_VDP_VIDEO_MPEG4:
                                case E_VDP_VIDEO_MPG:
                                case E_VDP_VIDEO_VC1:
                                case E_VDP_VIDEO_FLV:
                                    BinInfo.B_ID = BIN_ID_MM_MVD;
                                    u32VLCBinSize = 0;
                                    break;

                                #if (ENABLE_H265)
                                case E_VDP_VIDEO_HEVC:
                                    BinInfo.B_ID = BIN_ID_MM_EVD;
                                    u32VLCBinSize = 0;
                                    break;
                                #endif

                                case E_VDP_VIDEO_TS:
                                case E_VDP_VIDEO_VP6:
                                case E_VDP_VIDEO_VP9:
                                default:
                                    printf("[Warning] Not support HK load VDEC bin for codec(%d)\n",MB_Message.u8Parameters[0]);
                                    break;
                            }
#endif

                            for(i=1; i<5; i++)
                            {
                                u32Addr = (u32Addr<<8) | MB_Message.u8Parameters[i];
                            }

                            MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);

                            if (bResult == PASS)
                            {
                                if (SUCCESS == MDrv_DMA_LoadBin(&BinInfo, _PA2VA(u32Addr),
                                    _PA2VA((VDEC_FRAMEBUFFER_MEMORY_TYPE& MIU1) ? ((VDEC_FRAMEBUFFER_ADR+BUF_FOR_VDEC_DECOMPRESS_OFFSET1) | MIU_INTERVAL) : (VDEC_FRAMEBUFFER_ADR+BUF_FOR_VDEC_DECOMPRESS_OFFSET1)),
                                    _PA2VA((VDEC_FRAMEBUFFER_MEMORY_TYPE& MIU1) ? ((VDEC_FRAMEBUFFER_ADR+BUF_FOR_VDEC_DECOMPRESS_OFFSET2) | MIU_INTERVAL) : (VDEC_FRAMEBUFFER_ADR+BUF_FOR_VDEC_DECOMPRESS_OFFSET2)) ))

                                {
                                    u32FWBinSize = BinInfo.B_Len;
                                    switch(BinInfo.B_IsComp)
                                    {
                                    case LZSS_COMPRESS:
                                    case MS_COMPRESS:
                                    case MS_COMPRESS7:
                                        break;

                                    default:
                                        MApi_BDMA_CopyFromResource(BinInfo.B_FAddr, _PA2VA(u32Addr), BinInfo.B_Len);
                                        break;
                                    }
                                    EN_VDP_VIDEO_TYPE enVideoType;
                                    enVideoType = (EN_VDP_VIDEO_TYPE)MB_Message.u8Parameters[0];
                                    if (enVideoType  == E_VDP_VIDEO_RM)
                                    {
#if ENABLE_VDEC_2_0
                                        BinInfo.B_ID = BIN_ID_MM_VPU_VLC;
#else
                                        BinInfo.B_ID = BIN_ID_MM_HVD_VLC;
#endif
                                        u32Addr += u32FWBinSize;
                                        MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
                                        if (bResult == PASS)
                                        {
                                            if (SUCCESS == MDrv_DMA_LoadBin(&BinInfo, _PA2VA(u32Addr),
                                                _PA2VA((VDEC_FRAMEBUFFER_MEMORY_TYPE& MIU1) ? ((VDEC_FRAMEBUFFER_ADR+BUF_FOR_VDEC_DECOMPRESS_OFFSET1) | MIU_INTERVAL) : (VDEC_FRAMEBUFFER_ADR+BUF_FOR_VDEC_DECOMPRESS_OFFSET1)),
                                                _PA2VA((VDEC_FRAMEBUFFER_MEMORY_TYPE& MIU1) ? ((VDEC_FRAMEBUFFER_ADR+BUF_FOR_VDEC_DECOMPRESS_OFFSET2) | MIU_INTERVAL) : (VDEC_FRAMEBUFFER_ADR+BUF_FOR_VDEC_DECOMPRESS_OFFSET2)) ))
                                            {
                                                u32VLCBinSize = BinInfo.B_Len;
                                                switch(BinInfo.B_IsComp)
                                                {
                                                case LZSS_COMPRESS:
                                                case MS_COMPRESS:
                                                case MS_COMPRESS7:
                                                    break;

                                                default:
                                                    MApi_BDMA_CopyFromResource(BinInfo.B_FAddr, _PA2VA(u32Addr), BinInfo.B_Len);
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                bResult = FALSE;
                                            }
                                        }
                                    }

                                    MsOS_FlushMemory();
                                }
                                else
                                {
                                    bResult = FALSE;
                                }
                            }

                            if (bResult == TRUE)
                            {
                                VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                /*ParameterCount*/  ,9
                                /*p1*/              ,MB_VDPLAYER_LOAD_VDECBIN
                                /*p2*/              ,GetByte3(u32FWBinSize)
                                /*p3*/              ,GetByte2(u32FWBinSize)
                                /*p4*/              ,GetByte1(u32FWBinSize)
                                /*p5*/              ,GetByte0(u32FWBinSize)
                                /*p6*/              ,GetByte3(u32VLCBinSize)
                                /*p7*/              ,GetByte2(u32VLCBinSize)
                                /*p8*/              ,GetByte1(u32VLCBinSize)
                                /*p9*/              ,GetByte0(u32VLCBinSize)
                                /*p10*/             ,0);
                            }
                            else
                            {
                                VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                /*ParameterCount*/  ,9
                                /*p1*/              ,MB_VDPLAYER_LOAD_VDECBIN
                                /*p2*/              ,0
                                /*p3*/              ,0
                                /*p4*/              ,0
                                /*p5*/              ,0
                                /*p6*/              ,0
                                /*p7*/              ,0
                                /*p8*/              ,0
                                /*p9*/              ,0
                                /*p10*/             ,0);
                            }
                        }
#else
                        VDPLAYER_DBG(printf("Not Support Dynamic load VDEC Code!!\n"));
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,9
                        /*p1*/              ,MB_VDPLAYER_LOAD_VDECBIN
                        /*p2*/              ,0xFF
                        /*p3*/              ,0xFF
                        /*p4*/              ,0xFF
                        /*p5*/              ,0xFF
                        /*p6*/              ,0xFF
                        /*p7*/              ,0xFF
                        /*p8*/              ,0xFF
                        /*p9*/              ,0xFF
                        /*p10*/             ,0);
#endif // #if (ENABLE_DYNAMIC_LOAD_VDECBIN)
                        break;

                #if ENABLE_HK_MP4
                    case MB_VDPLAYER_MP4_INIT:
                        VDPLAYER_DBG(printf("MB_VDPLAYER_MP4_INIT\n"));
                        {
                            u32Addr = 0;
                            for (i = 0; i < 4; i++)
                            {
                                u32Addr = (u32Addr << 8) | MB_Message.u8Parameters[i];
                            }

                            MApp_VDPlayer_MP4_Init(_PA2VA(u32Addr));

                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                            /*ParameterCount*/  ,1
                            /*p1*/              ,MB_VDPLAYER_MP4_INIT
                            /*p2*/              ,0
                            /*p3*/              ,0
                            /*p4*/              ,0
                            /*p5*/              ,0
                            /*p6*/              ,0
                            /*p7*/              ,0
                            /*p8*/              ,0
                            /*p9*/              ,0
                            /*p10*/             ,0);
                            break;
                        }

                    case MB_VDPLAYER_MP4_GET_INDEX:
                        VDPLAYER_DBG(printf("MB_VDPLAYER_MP4_GET_INDEX\n"));
                        {
                            u32Addr = 0;
                            for (i = 0; i < 4; i++)
                            {
                                u32Addr = (u32Addr << 8) | MB_Message.u8Parameters[i];
                            }

                            MApp_VDPlayer_MP4_GetIndexInfo(_PA2VA(u32Addr));

                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                            /*ParameterCount*/  ,1
                            /*p1*/              ,MB_VDPLAYER_MP4_GET_INDEX
                            /*p2*/              ,0
                            /*p3*/              ,0
                            /*p4*/              ,0
                            /*p5*/              ,0
                            /*p6*/              ,0
                            /*p7*/              ,0
                            /*p8*/              ,0
                            /*p9*/              ,0
                            /*p10*/             ,0);
                            break;
                        }

                    case MB_VDPLAYER_MP4_GET_SAMPLE:
                        {
                            EN_MOV_MEDIA_TYPE enMediaType = E_MOV_MEDIA_TYPE_VIDEO1;
                            enMediaType = (EN_MOV_MEDIA_TYPE)MB_Message.u8Parameters[0];

                            U8 u8StreamID = 0;
                            u8StreamID = MB_Message.u8Parameters[1];

                            U32 u32SampleIndex = 0;
                            for (i = 2; i < 6; i++)
                            {
                                u32SampleIndex = (u32SampleIndex << 8) | MB_Message.u8Parameters[i];
                            }

                            U32 u32MaxSampleCount = 0;
                            for (i = 6; i < 10; i++)
                            {
                                u32MaxSampleCount = (u32MaxSampleCount << 8) | MB_Message.u8Parameters[i];
                            }
                            VDPLAYER_DBG(printf("MB_VDPLAYER_MP4_GET_SAMPLE, type %d, stream ID %d, sample ID %d, max count %d\n", enMediaType, u8StreamID, u32SampleIndex, u32MaxSampleCount));
                            MApp_VDPlayer_MP4_StartGetSampleInfo(enMediaType, u8StreamID, u32SampleIndex, u32MaxSampleCount);

                            break;
                        }

                    case MB_VDPLAYER_MP4_CLEAR_SAMPLE:
                        VDPLAYER_DBG(printf("MB_VDPLAYER_MP4_CLEAR_SAMPLE\n"));
                        EN_MOV_MEDIA_TYPE enMediaType = E_MOV_MEDIA_TYPE_VIDEO1;
                        enMediaType = (EN_MOV_MEDIA_TYPE)MB_Message.u8Parameters[0];

                        if (enMediaType == E_MOV_MEDIA_TYPE_VIDEO1)
                        {
                            MApp_VDPlayer_MP4_ClearVideoSampleInfo();
                        }
                        else if (enMediaType == E_MOV_MEDIA_TYPE_AUDIO1)
                        {
                            MApp_VDPlayer_MP4_ClearAudioSampleInfo();
                        }
#if ENABLE_HK_SUBTITLE
                        else if (enMediaType == E_MOV_MEDIA_TYPE_SUBTITLE1)
                        {
                            MApp_VDPlayer_MP4_ClearSubtitleSampleInfo();
                        }
#endif // #if ENABLE_HK_SUBTITLE
                        else if (enMediaType == E_MOV_MEDIA_TYPE_MAX)
                        {
                            MApp_VDPlayer_MP4_ClearVideoSampleInfo();
                            MApp_VDPlayer_MP4_ClearAudioSampleInfo();
#if ENABLE_HK_SUBTITLE
                            MApp_VDPlayer_MP4_ClearSubtitleSampleInfo();
#endif // #if ENABLE_HK_SUBTITLE
                        }

                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                            /*ParameterCount*/  ,2
                            /*p1*/              ,MB_VDPLAYER_MP4_CLEAR_SAMPLE
                            /*p2*/              ,enMediaType
                            /*p3*/              ,0
                            /*p4*/              ,0
                            /*p5*/              ,0
                            /*p6*/              ,0
                            /*p7*/              ,0
                            /*p8*/              ,0
                            /*p9*/              ,0
                            /*p10*/             ,0);
                        break;
                #endif
                     default:
                        //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                        //printf("          Unkown Co-processor MAILBOX(0x%x)       \n",MB_Message.u8Index);
                        //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                                                    break;
//****************************************************************************************
                }

                // Update u32VDPlayerLoopWdtTimer if receive Mailbox in init process, used for Init timeout checking
                if(m_eVDPlayerAckFlags&E_ACKFLG_WAIT_INIT)
                    u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();

            }
        }
        else
        {
            //printf("No Message\n");
        }
    }
#if ENABLE_HK_MP4
    int table_idx;
    // update one table at a time
    for (table_idx = 0; table_idx < MAX_MP4_TABLES; table_idx++)
    {
        //printf("[MP4] table idx %d, parsing %d\n", table_idx, stMP4.table_info[table_idx].parsing);
        if (stMP4.table_info[table_idx].parsing)
        {
            MApp_VDPlayer_MP4_UpdateSampleTable(&stMP4.table_info[table_idx]);
            break;
        }
    }
#endif
}


#if (VDPLAYER_CHECK_PREVIEW_ABORT)
BOOLEAN _MApp_VDPlayer_CheckPreviewAbortKey(void)
{
    MApp_ProcessUserInput();

    if (((u8KeyCode== KEY_UP)
        ||(u8KeyCode== KEY_DOWN)
        ||(u8KeyCode== KEY_EXIT))&&(m_bVDPlayerPreview==TRUE))
    {
        VDPLAYER_DBG(printf("_MApp_VDPlayer_CheckPreviewAbortKey Abort ...\n"));
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif


#if (VDPLAYER_CHECK_COPROCESSOR_STATUS)
// For robust: read VDPlayer count value to check if it is alive
BOOLEAN _Mapp_VDPlayer_CheckCoprocessorStatus(void)
{
    static U32 u32Timer=0;

    // If Coprocessor is Stoping now, no need to check Coprocessor status
//useless since co-rpcessor's CLK is always on(it's to detect whether co-processor's CLK is on)
//    if(MDrv_ReadByte(0x1E36) == 0x0)
//    {
//        return TRUE;
//    }

    if(msAPI_Timer_DiffTimeFromNow(u32Timer)<1000)
    {
        return TRUE;
    }

    u32Timer = msAPI_Timer_GetTime0();

    u32VDPlayerLoopCount =  _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WDT_TIMER);
    //printf("[_Mapp_VDPlayer_CheckCoprocessorStatus] %x %x %x\n",u32VDPlayerLoopPrevCount,u32VDPlayerLoopCount,
                                        //msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer));

    if(u32VDPlayerLoopPrevCount != u32VDPlayerLoopCount)
    {
        u32VDPlayerLoopPrevCount = u32VDPlayerLoopCount;
        u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
    }

    if(msAPI_Timer_DiffTimeFromNow(u32VDPlayerLoopWdtTimer) > VDPLAYER_COPROCESSOR_CHECK_TIMEOUT)
    {
        //printf("_Mapp_VDPlayer_CheckCoprocessorStatus return FALSE\n");
        MApp_VDPlayer_Stop();
        return FALSE;
    }
    else
    {
        if (g_bOutputMMAliveMessage)
        {
            static U32 u32AliveTimer = 0;

            if (msAPI_Timer_DiffTimeFromNow(u32AliveTimer) > 10000)
            {
                VDPLAYER_DBG(printf("MM alive !\n"));
                u32AliveTimer = msAPI_Timer_GetTime0();
            }
        }

        return TRUE;
    }
}
#endif

#if ENABLE_DVD
void _MApp_VDPlayer_DVD_Exit(void)
{
    _MApp_VDPlayer_ClearShareMem();

    MApp_DVD_Close();

    _gbCoprocessorEnable = FALSE;

    _MApp_VDPlayer_SetScalerMemoryToDefault();
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
    msAPI_MpegSP_Dinit();
#endif
    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
    MDrv_MVOP_Enable(FALSE);

    if (MApp_MPlayer_QueryMoviePlayMode() == E_MPLAYER_MOVIE_PAUSE)
    {
//        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
    }

}
#endif

EN_RET MApp_VDPlayer_Main (void)
{
    //enVDPlayerRet = EXIT_VDPLAYER_DECODING;
    MApp_VDPlayer_MailBoxHandler();

    //MApp_VDPlayer_SubtitleDraw();

#if SEAMLESS_PLAYING_ENABLE
    if (_bEnableSeamlessPlaying && MApi_XC_IsFreezeImg(MAIN_WINDOW))
    {
        if ((U32)MsOS_GetSystemTime()>_u32SeamlessTimer + 250)
        {
            MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
            //printf("seamless unfreeze(%ld)!\n", (U32)MsOS_GetSystemTime()-_u32SeamlessTimer);
        }
    }
#endif

    if(bMovieAbort)
    {
        enVDPlayerRet = EXIT_VDPLAYER_WAIT;
        bMovieAbort = FALSE;
    }

#if (VDPLAYER_CHECK_COPROCESSOR_STATUS)
    if(_Mapp_VDPlayer_CheckCoprocessorStatus() == FALSE)
    {
    #if ENABLE_LAST_MEMORY==1
        if (m_u8LastMemoryCheck==TRUE)
        {
            MApp_MPlayer_LastMemory_SetResumePlayAttribute(1);
            m_u8LastMemoryCheck=FALSE;
        }
    #endif
        MApp_VDPlayer_Stop(); //fix preview next file it will show "un-support file" after abort(need to issue STOP CMD to co-processor)
//        _MApp_VDPlayer_Exit();
        enVDPlayerRet = EXIT_VDPLAYER_EXIT;
        return enVDPlayerRet;
    }
#endif

    if((enVDPlayerRet==EXIT_VDPLAYER_WAIT)||(enVDPlayerRet==EXIT_VDPLAYER_EXIT))
    {
    #if ENABLE_LAST_MEMORY==1
        if (m_u8LastMemoryCheck==TRUE)
        {
            MApp_MPlayer_LastMemory_SetResumePlayAttribute(1);
            m_u8LastMemoryCheck=FALSE;
        }
    #endif
        MApp_VDPlayer_Stop(); //fix preview next file it will show "un-support file" after abort(need to issue STOP CMD to co-processor)
//        _MApp_VDPlayer_Exit();
    }

    return enVDPlayerRet;
}

#if ENABLE_DVD


static void _MB_SeekPlay(void)
{
    U32 u32Timer;

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_SEEKPLAY;

    VDPLAYER_DVD_DBG(printf("Hop Channel ->\n"));
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_DVD_SEEKPLAY
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    u32Timer = msAPI_Timer_GetTime0();
    while(m_eVDPlayerAckFlags & E_ACKFLG_WAIT_SEEKPLAY)
    {
        if (msAPI_Timer_DiffTimeFromNow(u32Timer) > 2000)
        {
            VDPLAYER_DVD_DBG(printf("Hop Channel timeout\n"));
            break;
        }

        MApp_VDPlayer_MailBoxHandler();
    }
}

static void _MB_WaitDone(void)
{
    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_DONE;

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_DVD_WAITDONE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

static void _MB_Play(U8 type)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_DVD_PLAY
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,2
    /*p1*/              ,type
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

static void _MB_ScanSync(void)
{
    U32 u32Timer;

    m_eVDPlayerAckFlags |= (E_ACKFLG_WAIT_SCANSYNC | E_ACKFLG_WAIT_SCANDONE);

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_DVD_SCANSYNC
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    u32Timer = msAPI_Timer_GetTime0();
    while(m_eVDPlayerAckFlags & E_ACKFLG_WAIT_SCANSYNC)
    {
        if (msAPI_Timer_DiffTimeFromNow(u32Timer) > 2000)
        {
            VDPLAYER_DVD_DBG(printf("Scan sync timeout\n"));
            break;
        }

        MApp_VDPlayer_MailBoxHandler();
    }

    VDPLAYER_DVD_DBG(printf("ScanSync <-\n"));
}

static void _MB_ScanExit(void)
{
    U32 u32Timer;

    m_eVDPlayerAckFlags |= E_ACKFLG_WAIT_SCANEXIT;

    VDPLAYER_DVD_DBG(printf("ScanExit ->\n"));
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_DVD_SCANEXIT
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    u32Timer = msAPI_Timer_GetTime0();
    while(m_eVDPlayerAckFlags & E_ACKFLG_WAIT_SCANEXIT)
    {
        if (msAPI_Timer_DiffTimeFromNow(u32Timer) > 2000)
        {
            VDPLAYER_DVD_DBG(printf("Scan exit timeout\n"));
            break;
        }

        MApp_VDPlayer_MailBoxHandler();
    }

    VDPLAYER_DVD_DBG(printf("ScanExit <-\n"));
}


EN_RET MApp_VDPlayer_DVD_Main(void)
{
    MApp_VDPlayer_MailBoxHandler();

    //MApp_VDPlayer_SubtitleDraw();

    if((enVDPlayerRet==EXIT_VDPLAYER_WAIT)||(enVDPlayerRet==EXIT_VDPLAYER_EXIT))
    {
        _MApp_VDPlayer_DVD_Exit();
        return enVDPlayerRet;
    }

    // State machine
    MApp_DVD_Task();

    return enVDPlayerRet;
}

U8 MApp_VDPlayer_DVD_Command(enumMPlayerDVDCmdType cmd)
{
    return MApp_DVD_Command(cmd);
}

BOOLEAN MApp_VDPlayer_DVD_IsAllowed(enumMPlayerDVDCmdType cmd)
{
    return MApp_DVD_IsAllowed(cmd);
}
#endif  // ENABLE_DVD

BOOLEAN MApp_VDPlayer_SetFileEntry(FileEntry *pEntry)
{
    g_pVDPlayerFileEntry = pEntry;

    return TRUE;
}

void MApp_VDPlayer_BeginThumbnail(void)
{
    m_bVDPlayerThumbnail = TRUE;
}

void MApp_VDPlayer_StopThumbnail(void)
{
    m_bVDPlayerThumbnail = FALSE;
}

void MApp_VDPlayer_BeginPreview(void)
{
    m_bVDPlayerPreview = TRUE;
    m_eVDPlayerFlgs |= E_VDPLAYER_FLG_PREVIEW;
}


void MApp_VDPlayer_StopPreview(void)
{
    m_bVDPlayerPreview = FALSE;
    m_eVDPlayerFlgs &= (enumVDPlayerFlags)~E_VDPLAYER_FLG_PREVIEW;
}

BOOLEAN MApp_VDPlayer_IsPreview(void)
{
    if((m_bVDPlayerPreview == TRUE)&&(m_eVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
void MApp_VDPlayer_SetPreviewWindow(U16 u16X, U16 u16Y, U16 u16Width, U16 u16Height, EN_ASPECT_RATIO_TYPE eAspectRatioType)
{
    _gu16PreviewX = u16X;
    _gu16PreviewY = u16Y;
    _gu16PreviewWidth  = u16Width;
    _gu16PreviewHeight = u16Height;
    _geAspectRatioType = eAspectRatioType;
}

BOOLEAN MApp_VDPlayer_IsTextSubtitle(void)
{
    if((u32subtitletype>= E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT)&&
       (u32subtitletype<= E_VDP_CODEC_ID_SUBTITLE_TEXT_USF))
    {
        return TRUE;
    }
    return FALSE;
}


BOOLEAN MApp_VDPlayer_EnableVideoOutputFlag(BOOLEAN bEnable)
{
    if(bEnable)
    {
        m_eVDPlayerFlgs |= E_VDPLAYER_FLG_SHOWVIDEO;
    }
    else
    {
        m_eVDPlayerFlgs &= (enumVDPlayerFlags)~E_VDPLAYER_FLG_SHOWVIDEO;
    }
    return TRUE;
}

void MApp_VDPlayer_SetCodecTimeout(U32 * u32TimeOut)
{
    U32 i;
    for (i = 0; i < (E_SHAREMEM_ESBUF_CTRL_TIMEOUT-E_SHAREMEM_BLOCK_FILEIO_TIMEOUT+1); i++)
    {
        m_u32CodecTimeOut[i] = u32TimeOut[i];
    }
}

void MApp_VDPlayer_SetPlayTimeOut(U32 u32TimeOut)
{
    u8VDPlayerPlayTimeOut = u32TimeOut;
}

void MApp_VDPlayer_CodecDbgMsg(BOOL bEnable)
{
    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
    /*Index*/           ,MB_VDPLAYER_DBGINFO
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,1
    /*p1*/              ,bEnable
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

#if (FBL_ZOOM==1)
void MApp_VDPlayer_ScaleVideo_FBL(VDPLAYER_ZOOM_FACT eZoom)
{
    U16 u16Width = 0;
    U16 u16Height = 0;
    U32 u32MVOP_Black_Width = 0;
    U32 u32MVOP_Black_Height = 0;
    MS_WINDOW_TYPE tZoomedSrcWin;
    MS_WINDOW_TYPE tZoomedDstWin;
    MVOP_VidStat stMvopVidSt;
    XC_SetTiming_Info stTimingInfo;
    MVOP_Timing stMVOPTiming;
    U16 u16HorOffset = 0;
    U16 u16VerOffset = 0;

    if(enVDPlayerVideoType == E_VDPLAYER_VIDEO_MJPEG)
    {
        //no FBL case
        __ASSERT(0);
        return;
    }

    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    g_bForceToFB = FALSE;
    memset(&stMvopVidSt, 0, sizeof(MVOP_VidStat));
    memset(&stTimingInfo, 0, sizeof(XC_SetTiming_Info));
    memset(&stMVOPTiming, 0, sizeof(MVOP_Timing));
    memset(&tZoomedSrcWin, 0, sizeof(tZoomedSrcWin));
    memset(&tZoomedDstWin, 0, sizeof(tZoomedDstWin));
    if(enVDPlayerVideoType != E_VDPLAYER_VIDEO_RM)
    {
        gstVidStatus.u32FrameRate = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAME_RATE);
        gstVidStatus.u8Interlace = _MApp_VDPlayer_GetInterlace();
    }
    gstVidStatus.u16HorSize =  _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
    gstVidStatus.u16VerSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT);
    u16Width=gstVidStatus.u16HorSize;
    u16Height=gstVidStatus.u16VerSize;
    tZoomedSrcWin.width = u16Width;
    tZoomedSrcWin.height = u16Height;
    gstVidStatus.u16CropRight = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_RIGHT);
    gstVidStatus.u16CropLeft = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_LEFT);
    gstVidStatus.u16CropBottom = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_BOTTOM);
    gstVidStatus.u16CropTop = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CROP_TOP);

    switch(eZoom)
    {
    case VDPLAYER_ZOOM_FACT_1_DIV_4:
        tZoomedSrcWin.height = u16Height * 14 / 16;
        //printf("in 1_DIV_4 mode!\n");
        break;
    case VDPLAYER_ZOOM_FACT_1_DIV_2:
        tZoomedSrcWin.height = u16Height * 15 / 16;
        //printf("in 1_DIV_2 mode!\n");
        break;
    case VDPLAYER_ZOOM_FACT_NORMAL:
        //printf("in Normal mode!\n");
        break;
    case VDPLAYER_ZOOM_FACT_2X:
        // zoom in, get part rect of src
        tZoomedSrcWin.width = u16Width * 5 / 7;
        tZoomedSrcWin.height = u16Height * 5 / 7;
        //printf("in zoom_fact_2x mode!\n");
        break;
    case VDPLAYER_ZOOM_FACT_4X:
        // zoom in, get part rect of src
        tZoomedSrcWin.width = u16Width >> 1;
        tZoomedSrcWin.height = u16Height >> 1;
        //printf("in zoom_fact_4x mode!\n");
        break;
    case VDPLAYER_ZOOM_FACT_8X:
        // zoom in, get part rect of src
        tZoomedSrcWin.width = u16Width * 5 / 14;
        tZoomedSrcWin.height = u16Height * 5 / 14;
        //printf("in zoom_fact_8x mode!\n");
        break;
    default:
        break;
    }
    tZoomedSrcWin.width = (tZoomedSrcWin.width >> 3) << 3; // 8 bytes align
    tZoomedSrcWin.height = (tZoomedSrcWin.height>> 1) << 1; // even

    //for FBL set MVOP for maintain video ratio
    MApp_VDPlayer_GetMVOPBlackSize((U32)tZoomedSrcWin.width, (U32)tZoomedSrcWin.height, &u32MVOP_Black_Width, &u32MVOP_Black_Height);
    VDPLAYER_DVD_DBG(printf("w=%u, h=%u,  black_W=%lu, black_H=%lu\n",tZoomedSrcWin.width, tZoomedSrcWin.height, u32MVOP_Black_Width, u32MVOP_Black_Height));
    switch (eZoom)
    {
    case VDPLAYER_ZOOM_FACT_1_DIV_4:
        u16HorOffset = u32MVOP_Black_Width * 16 / 14;
        u16VerOffset = u32MVOP_Black_Height * 16 / 14;
        break;
    case VDPLAYER_ZOOM_FACT_1_DIV_2:
        u16HorOffset = u32MVOP_Black_Width * 16 / 15;
        u16VerOffset = u32MVOP_Black_Height * 16 / 15;
        break;
    case VDPLAYER_ZOOM_FACT_2X:
    case VDPLAYER_ZOOM_FACT_4X:
    case VDPLAYER_ZOOM_FACT_8X:
        u16HorOffset = u32MVOP_Black_Width;
        u16VerOffset = u32MVOP_Black_Height;
        gstVidStatus.u16HorSize = tZoomedSrcWin.width;
        gstVidStatus.u16VerSize = tZoomedSrcWin.height;
        break;
    case VDPLAYER_ZOOM_FACT_NORMAL:
    default:
        u16HorOffset = u32MVOP_Black_Width;
        u16VerOffset = u32MVOP_Black_Height;
        break;
    }

    if(tZoomedSrcWin.height + u32MVOP_Black_Height * 2 < 550) // to cover all case of mvop known patch
    {
        g_bForceToFB = TRUE;

        //assign smaller buffer for scaler.
        MApi_XC_SetFrameBufferAddress(SCALER_DNR_BUF_ADR, SCALER_DNR_BUF_LEN, MAIN_WINDOW);

    #if(ENABLE_MM_XC_FBL_MODE)
        MApi_XC_EnableFrameBufferLess(DISABLE);
    #endif

    #if (MEMORY_MAP <= MMAP_64MB)   //ATV_MM 64M
        //preview force quad pixel and deblocking off
        MApp_VDPlayer_QuarterPixel(DISABLE);
        MApp_VDPlayer_DeBlocking(DISABLE);
    #endif

        u16HorOffset = 0;
        u16VerOffset = 0;
        gstVidStatus.u16HorSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
        gstVidStatus.u16VerSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT);
        MApp_VDPlayer_GetMVOPBlackSizeOnDest((U32)tZoomedSrcWin.width, (U32)tZoomedSrcWin.height,&u32MVOP_Black_Width,  &u32MVOP_Black_Height);
        tZoomedDstWin.x = u32MVOP_Black_Width;
        tZoomedDstWin.y = u32MVOP_Black_Height;
        tZoomedDstWin.width = devPanel_WIDTH() - u32MVOP_Black_Width * 2;
        tZoomedDstWin.height= devPanel_HEIGHT() - u32MVOP_Black_Height * 2;
        VDPLAYER_DVD_DBG(printf("zoomeddst: x,y,w,h=%u,%u,%u,%u\n", tZoomedDstWin.x, tZoomedDstWin.y, tZoomedDstWin.width, tZoomedDstWin.height));
    }
    else
    {
        g_bForceToFB = FALSE;
    #if(ENABLE_MM_XC_FBL_MODE)
      #if( ENABLE_MM_HD_FB && (MEMORY_MAP == MMAP_64MB) )
        MApi_XC_EnableFrameBufferLess(DISABLE);
        g_bForceToFB = TRUE;
      #else
        MApi_XC_EnableFrameBufferLess(ENABLE);
      #endif
    #endif
    }

    if(eZoom > VDPLAYER_ZOOM_FACT_NORMAL)
    {
        if(u16Width > tZoomedSrcWin.width)
        {
            tZoomedSrcWin.x = (u16Width - tZoomedSrcWin.width ) >> 1;
        }
        if(u16Height > tZoomedSrcWin.height)
        {
            tZoomedSrcWin.y = (u16Height - tZoomedSrcWin.height ) >> 1;
        }
        if(!g_bForceToFB)
        {
            if((enVDPlayerVideoType == E_VDPLAYER_VIDEO_MPG) || (enVDPlayerVideoType == E_VDPLAYER_VIDEO_MPEG4))
            {
                tZoomedSrcWin.x = (tZoomedSrcWin.x >> 3) << 3; // 8 bytes align
            }
            else
            {
                tZoomedSrcWin.x = (tZoomedSrcWin.x >> 4) << 4; // 16 bytes align
            }
            tZoomedSrcWin.y = (tZoomedSrcWin.y >> 6) << 6; // 64 bytes align
        }
    }

    VDPLAYER_DVD_DBG(printf("tZoomedSrcWin.x=%u, tZoomedSrcWin.y=%u, tZoomedSrcWin.width=%u,tZoomedSrcWin.height=%u\n", tZoomedSrcWin.x, tZoomedSrcWin.y, tZoomedSrcWin.width, tZoomedSrcWin.height));

    if(!g_bForceToFB) //Bright@20080905 FBL
    {
/*
        if(((gstVidStatus.u32FrameRate > 24500) && (gstVidStatus.u32FrameRate <= 25000))
            || ((gstVidStatus.u32FrameRate > 49500) && (gstVidStatus.u32FrameRate <= 50000)))
        {
            gstVidStatus.u32FrameRate = 25000;
        }
        else
        {
            gstVidStatus.u32FrameRate = 30000;
        }
*/
        if((gstVidStatus.u32FrameRate > 24500)&&(gstVidStatus.u32FrameRate <= 25000))
        {
            //stVidStatus.u32FrameRate = 25000;
        }
        else if((gstVidStatus.u32FrameRate > 49500)&&(gstVidStatus.u32FrameRate <= 50000))
        {
            gstVidStatus.u32FrameRate=gstVidStatus.u32FrameRate/2; //25
        }
        else if((gstVidStatus.u32FrameRate > 23500)&&(gstVidStatus.u32FrameRate <= 24000) )
        {
            gstVidStatus.u32FrameRate = (U32)gstVidStatus.u32FrameRate*5/4; //30
        }
        else if((gstVidStatus.u32FrameRate > 29500)&&(gstVidStatus.u32FrameRate <= 30000))
        {
            //~30
        }
        else
        {
            gstVidStatus.u32FrameRate = 30000;
        }

        if(gstVidStatus.u8Interlace == FALSE) //progressive
        {
            gstVidStatus.u32FrameRate *= 2;
        }
    }

    MApp_Scaler_EnableOverScan(FALSE);
    MDrv_MVOP_Init();
    stMvopVidSt.u16HorSize   = gstVidStatus.u16HorSize;
    stMvopVidSt.u16VerSize   = gstVidStatus.u16VerSize;
    stMvopVidSt.u16FrameRate = gstVidStatus.u32FrameRate;
    stMvopVidSt.u8AspectRate = gstVidStatus.u8AspectRate;
    stMvopVidSt.u8Interlace  = gstVidStatus.u8Interlace;
    stMvopVidSt.u16HorOffset = u16HorOffset;
    stMvopVidSt.u16VerOffset = u16VerOffset;
    MDrv_MVOP_SetOutputCfg(&stMvopVidSt, FALSE);

    //Get VOP timing for FBL
    MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
    stTimingInfo.bFastFrameLock = FALSE;
    if(stMVOPTiming.bInterlace)
    {
        stTimingInfo.u16InputVFreq = (U16)((stMVOPTiming.u16ExpFrameRate * 2 + 50) / 100);
    }
    else
    {
        stTimingInfo.u16InputVFreq = (U16)((stMVOPTiming.u16ExpFrameRate + 50) / 100);
    }

    stTimingInfo.bMVOPSrc = TRUE;
    stTimingInfo.u16InputVTotal = stMVOPTiming.u16V_TotalCount;
    stTimingInfo.bInterlace = stMVOPTiming.bInterlace;

    MDrv_MVOP_Enable(FALSE);

    switch (enVDPlayerVideoType)
    {
        case E_VDPLAYER_VIDEO_MPEG4:
        case E_VDPLAYER_VIDEO_MPG:
        case E_VDPLAYER_VIDEO_VC1:
            if((eZoom > VDPLAYER_ZOOM_FACT_NORMAL) && !g_bForceToFB)
            {
                MVOP_InputCfg dc_param;
                memset(&dc_param, 0, sizeof(MVOP_InputCfg));
                dc_param.u16CropWidth = tZoomedSrcWin.width;
                dc_param.u16CropHeight = tZoomedSrcWin.height;
                dc_param.u16CropX = tZoomedSrcWin.x;
                dc_param.u16CropY = tZoomedSrcWin.y;
                dc_param.enVideoType = MVOP_MPG;
              #if (VIDEO_FIRMWARE_CODE >= VIDEO_FIRMWARE_CODE_HD)
                dc_param.u16StripSize = 1920;
              #else
                dc_param.u16StripSize = 720;
              #endif
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &dc_param);
            }
            else
            {
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_MVD, NULL);
            }
            break;

        case E_VDPLAYER_VIDEO_H264:
        case E_VDPLAYER_VIDEO_AVS:
            if((eZoom > VDPLAYER_ZOOM_FACT_NORMAL) && !g_bForceToFB)
            {
                MVOP_InputCfg dc_param;
                memset(&dc_param, 0, sizeof(MVOP_InputCfg));
                dc_param.u16CropWidth = tZoomedSrcWin.width;
                dc_param.u16CropHeight = tZoomedSrcWin.height;
                dc_param.u16CropX = tZoomedSrcWin.x;
                dc_param.u16CropY = tZoomedSrcWin.y;
                dc_param.enVideoType = MVOP_H264;
                dc_param.u16StripSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &dc_param);
            }
            else
            {
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_H264, NULL);
            }
            break;

        case E_VDPLAYER_VIDEO_RM:
            if((eZoom > VDPLAYER_ZOOM_FACT_NORMAL) && !g_bForceToFB)
            {
                MVOP_InputCfg dc_param;
                memset(&dc_param, 0, sizeof(MVOP_InputCfg));
                dc_param.u16CropWidth = tZoomedSrcWin.width;
                dc_param.u16CropHeight = tZoomedSrcWin.height;
                dc_param.u16CropX = tZoomedSrcWin.x;
                dc_param.u16CropY = tZoomedSrcWin.y;
                dc_param.enVideoType = MVOP_RM;
                dc_param.u16StripSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &dc_param);
            }
            else
            {
                MDrv_MVOP_SetInputCfg(MVOP_INPUT_RVD, NULL);
            }
            break;
        default:
            break;
    }

    MDrv_MVOP_Enable(TRUE);

    if(g_bForceToFB)
    {
        MApp_Scaler_SetWindow(&tZoomedSrcWin, NULL, &tZoomedDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
    }
    else
    {
        MApp_Scaler_SetWindow(NULL, NULL, NULL, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
    }

#if(CHAKRA3_AUTO_TEST)
    MApi_SC_ForceFreerun(TRUE);
    MApi_SC_SetFreerunVFreq(VFREQ_60HZ);
#endif
    MApi_XC_SetPanelTiming(&stTimingInfo, MAIN_WINDOW);


#if ENABLE_BACKLIGHT_PWM_SYNC_WITH_FRAMERATE
    SetPWMto2PanelVFreq(RATIO_OF_BACKLIGHT_FREQ_OVER_FRAMERATE);
#endif

    msAPI_Timer_Delayms(100);
    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, 0, MAIN_WINDOW);
}
#endif

void MApp_VDPlayer_ScaleVideo(VDPLAYER_ZOOM_FACT eZoom)
{
    BOOLEAN bMVopEnabled;

    if (  (enVDPlayerRet != EXIT_VDPLAYER_DECODING)
       || (MDrv_MVOP_GetIsEnable(&bMVopEnabled) != E_MVOP_OK)
       || (bMVopEnabled != TRUE)
       )
    {
        return;
    }

    MS_U16 u16PQDelyaTime = MDrv_PQ_GetDelayTime();

//    MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_FREERUN, ENABLE, 0, MAIN_WINDOW);

    _MApp_VDPlayer_ScaleScalerWindows(eZoom, FALSE);
    MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

//    MApi_XC_WaitFPLLDone();
//    MApi_XC_GenerateBlackVideo(DISABLE, MAIN_WINDOW);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, u16PQDelyaTime, MAIN_WINDOW);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_FREERUN, DISABLE, 0, MAIN_WINDOW);
}

BOOLEAN MApp_VDPlayer_ShiftVideo(S16 *ps16OffsetX, S16 *ps16OffsetY,
                               U16 u16BoundaryX, U16 u16BoundaryY, VDPLAYER_ZOOM_FACT eZoomFact)
{
    U16 u16HSize = 0;
    U16 u16HStart = 0;
    U16 u16VSize = 0;
    U16 u16VStart = 0;

    U16 u16Width = 0;
    U16 u16Height = 0;

    MS_WINDOW_TYPE tCropWin, tDstWin;
    BOOLEAN bMVopEnabled;

    if ( (enVDPlayerRet != EXIT_VDPLAYER_DECODING)
      || (MDrv_MVOP_GetIsEnable(&bMVopEnabled) != E_MVOP_OK)
      || (bMVopEnabled != TRUE) )
    {
        return FALSE;
    }

    memset(&tCropWin, 0, sizeof(tCropWin));
    memset(&tDstWin, 0, sizeof(tDstWin));

    MS_WINDOW_TYPE stDisplayWin = {0, 0, PANEL_WIDTH, PANEL_HEIGHT};

    _MApp_VDPlayer_GetVDPlayerInfo(&u16Width, &u16Height);
    _MApp_VDPlayer_CalCropDisplayWin(&tCropWin, &tDstWin, eZoomFact,stDisplayWin);
    u16HStart = tCropWin.x;
    u16VStart = tCropWin.y;
    u16HSize = tCropWin.width;
    u16VSize = tCropWin.height;

    if ((S32)u16HStart + (S32)*ps16OffsetX <= (S32)u16BoundaryX)
    {
        *ps16OffsetX = (S16)((S32)u16BoundaryX - (S32)u16HStart);
    }
    else if (u16HStart + *ps16OffsetX + u16HSize >= u16Width - u16BoundaryX)
    {
        *ps16OffsetX = u16Width - u16BoundaryX - (u16HStart + u16HSize);
    }

    if ((S32)u16VStart + (S32)*ps16OffsetY <= (S32)u16BoundaryY)
    {
        *ps16OffsetY = (S16)((S32)u16BoundaryY - (S32)u16VStart);
    }
    else if (u16VStart + *ps16OffsetY + u16VSize >= u16Height - u16BoundaryY)
    {
        *ps16OffsetY = u16Height - u16BoundaryY - (u16VStart + u16VSize)-1;
    }

    u16HStart += *ps16OffsetX;
    u16VStart += *ps16OffsetY;

    tCropWin.x = u16HStart;
    tCropWin.y = u16VStart;
    tCropWin.width = u16HSize;
    tCropWin.height = u16VSize;

#if DYNSCALING//++TPT function start
    if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING)==1)
    {
        tCropWin.width = (MS_U16)DYNAMIC_SCALING_VB_H*tCropWin.width/_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
        tCropWin.x = (MS_U16)DYNAMIC_SCALING_VB_H*tCropWin.x/_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH);
        tCropWin.height = (MS_U16)DYNAMIC_SCALING_VB_V* tCropWin.height/_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT);
        tCropWin.y = (MS_U16)DYNAMIC_SCALING_VB_V* tCropWin.y/_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT);

        _MApp_VDPlayer_SendZoomInfo2Firmware(
            _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DYNSCALING_ADDRESS) + (1024*3),
            &tCropWin, &tDstWin, MAIN_WINDOW);
    }
    else
#endif
    {

        MDrv_PQ_Set_NOLoadScalingTable(TRUE);
        MApp_Scaler_SetWindow(NULL, &tCropWin, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                              SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        MDrv_PQ_Set_NOLoadScalingTable(FALSE);
    }
    return TRUE;
}
#if DWIN_MOVIE_PREVIEW
void MApp_VDPlayer_PreviewGWIN_Create(GOP_GwinFBAttr* pstFbAttr)
{
    U8 u8FbId = MApi_GOP_GWIN_GetFreeFBID();
    U8 u8GwinId = MApi_GOP_GWIN_GetFreeWinID();

    if ((u8FbId == 0xFF) || (u8GwinId >= GWIN_ID_INVALID))
    {
        VDPLAYER_DVD_DBG(printf("No FB or GW\n"));
        return;
    }

    VDPLAYER_DVD_DBG(printf("\n MApp_VDPlayer_CreateGWIN , u8FbId=%x , u8GwinId=%x\n",u8FbId, u8GwinId));
    if (MApi_GOP_GWIN_CreateFB(u8FbId, 0, 0, MOVIE_PREVIEW_WIDTH, MOVIE_PREVIEW_HEIGHT, GFX_FMT_ARGB8888) == FALSE)
    {
        VDPLAYER_DVD_DBG(printf("error Insufficient Buffer\n"));
        return;
    }

    MApi_GOP_GWIN_MapFB2Win(u8FbId, u8GwinId);
    MApi_GOP_GWIN_GetFBInfo(u8FbId, pstFbAttr);
    MApi_GOP_GWIN_SetBlending(u8GwinId, TRUE, 0x3F);
    MApi_GFX_ClearFrameBuffer(pstFbAttr->addr, (U32)MOVIE_PREVIEW_WIDTH * (U32)MOVIE_PREVIEW_HEIGHT * 4 /* 4 for GFX_FMT_ARGB8888*/, 0x00); // fill frame buffer with 0, black
    // after clear frame buffer, flush cmd
    MApi_GFX_FlushQueue();
    MApi_GOP_GWIN_EnableTransClr((EN_GOP_TRANSCLR_FMT) 0, FALSE);
    MApi_GOP_GWIN_SetWinPosition(u8GwinId, MOVIE_PREVIEW_X, MOVIE_PREVIEW_Y);  //ori preview position
    MApi_GOP_GWIN_Enable(u8GwinId, TRUE);

/*
    // set gwin to solid
    MApi_GOP_GWIN_GetAlphaValue(&u16Alpha01, &u16Alpha23);
    switch (u8GwinId)
    {
        case 0:
            u16Alpha01 |= 0x00ff;
            break;
        case 1:
            u16Alpha01 |= 0xff00;
            break;
        case 2:
            u16Alpha23 |= 0x00ff;
            break;
        case 3:
            u16Alpha23 |= 0xff00;
            break;
    }
    MApi_GOP_GWIN_SetAlphaValue(&u16Alpha01, &u16Alpha23);
*/

}
void MApp_VDPlayer_DWINMoviePreview(GOP_GwinFBAttr stFbAttr)
{
    GOP_DwinProperty dwinProperty;
    U32 dwinCapTime=0;
    U8 gopBank = MApi_GOP_GWIN_GetCurrentGOP();

    //printf("\n MApp_VDPlayer_DWINVideo \n");
    MApi_GOP_GWIN_SwitchGOP(E_GOP_CAP);
#if ((ENABLE_DMP) || (DISPLAY_LOGO))
    // set GOPD clock
    MApi_GOP_SetClkForCapture();
#endif //#if ENABLE_DMP

    MApi_GOP_DWIN_Init();

    MApi_GOP_DWIN_SelectSourceScanType((EN_GOP_DWIN_SCAN_MODE)MDrv_MVOP_GetIsInterlace());
    MApi_GOP_DWIN_SetDataFmt((EN_GOP_DWIN_DATA_FMT)DWIN_DATA_FMT_ARGB8888);
    dwinProperty.u16x = 0;
    dwinProperty.u16y = 0;
    dwinProperty.u16h = MOVIE_PREVIEW_HEIGHT ;
    dwinProperty.u32fbaddr0 = stFbAttr.addr;
/*
    if (enGopDFormat == DWIN_DATA_FMT_RGB565)
    {
        dwinProperty.u32fbaddr1 = u32DestAddr + u32DestSize * 2UL + 64; // 64-byte is safe margin
        dwinProperty.u16w = (u16OutputWidth & 0xfffc);
        dwinProperty.u16fbw = u16LineSize & 0xfffc;
    }
    else if (enGopDFormat == DWIN_DATA_FMT_ARGB8888)
*/
    {
        dwinProperty.u32fbaddr1 = stFbAttr.addr + stFbAttr.size * 4UL + 64; // 64-byte is safe margin
        dwinProperty.u16w = (MOVIE_PREVIEW_WIDTH & 0xfffe);
        dwinProperty.u16fbw = MOVIE_PREVIEW_WIDTH & 0xfffe;
    }

    //printf("\n w=%x   ,    fbW=%x  \n", dwinProperty.u16w , dwinProperty.u16fbw );

    // enable DWIN progressive INT
    MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, TRUE);

    MApi_GOP_DWIN_SetWinProperty(&dwinProperty);
    MApi_GOP_DWIN_SetAlphaValue(0x0f); // set to solid
    msAPI_Timer_Delayms(10);
    //MApi_GOP_DWIN_CaptureOneFrame();

    dwinCapTime = msAPI_Timer_GetTime0();

    while ((MApi_GOP_DWIN_GetIntrStatus() & GOPDWIN_INT_MASK_PROG) == 0)
    {
        if (msAPI_Timer_DiffTimeFromNow(dwinCapTime) >= 50)
        {

            break; //wait for DWIN capture done(fix RGB mode slide show cannot display some pics randomly)
        }
    }

    MApi_GOP_DWIN_ClearIntr(GOPDWIN_INT_MASK_PROG);
    MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, FALSE);
    MApi_GOP_DWIN_Enable(TRUE);
    MApi_GOP_GWIN_SwitchGOP(gopBank);

}
#endif // DWIN_MOVIE_PREVIEW

U32 MApp_VDPlayer_Get_Buffer_Info(EN_BUFFER_INFO_INDEX eIndex)
{
    if (eIndex == E_BUFFER_INFO_BITRATE)
    {
        if ((enVDPlayerVideoType == E_VDPLAYER_VIDEO_RM) || (enVDPlayerVideoType == E_VDPLAYER_VIDEO_FLV))
            return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_BUFFER_INFO+eIndex);
        else
            return 0;
    }
    else
    {
        return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_BUFFER_INFO+eIndex);
    }
}

BOOLEAN MApp_VDPlayer_DeBlocking(BOOLEAN bEnable)
{
    if((U32)gstVidStatus.u16HorSize*(U32)gstVidStatus.u16VerSize <= HVD_BW_TUNING_THRESHOLD)
    {
        //keep deblocking on.
        return FALSE;
    }

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_HVD_FEATURE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,2
    /*p1*/              ,E_VDP_HVD_DISABLE_DEBLOCKING
    /*p2*/              ,!bEnable
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    return TRUE;
}

BOOLEAN MApp_VDPlayer_QuarterPixel(BOOLEAN bEnable)
{
    if((U32)gstVidStatus.u16HorSize*(U32)gstVidStatus.u16VerSize <= HVD_BW_TUNING_THRESHOLD)
    {
        //keep quarterpixel on.
        return FALSE;
    }

    //==> Send mail.
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
    /*Index*/           ,MB_VDPLAYER_HVD_FEATURE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,2
    /*p1*/              ,E_VDP_HVD_DISABLE_QUARTERPIXEL
    /*p2*/              ,!bEnable
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    return TRUE;
}

#if 1//MOVIE_THUMBNAIL
bool MApp_VDPlayer_MovieThumbnail_SetMVOP(void)
{
    #define MVOP_WIDTH_UPPER_BOUND      7890    // The upper and lower bound is suggested from MVOP expert
    #define MVOP_HEIGHT_UPPER_BOUND     8145
    #define MVOP_WIDTH_LOWER_BOUND      32      //MJPEG and JEPG support above 2, other codecs support above 32
    #define MVOP_HEIGHT_LOWER_BOUND     32      //HEVC and VP9 will support above 8

    #define MVOP_JPEG_WIDTH_LOWER_BOUND       2
    #define MVOP_JPEG_HEIGHT_LOWER_BOUND       2

    MVOP_VidStat stVidStatus;
    MVOP_InputCfg MVOP_Param;
    EN_VDP_CODECID enVideoType=E_VDP_CODEC_ID_NONE;
    #if ENABLE_EVD_FEATURE
    MVOP_EVDFeature stEVDfeature;
    #endif
#if ENABLE_MVC
    U32 u32FBAddr=((VDEC_MVC_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VDEC_MVC_FRAMEBUFFER_ADR | MIU_INTERVAL) : (VDEC_MVC_FRAMEBUFFER_ADR));
#else
    U32 u32FBAddr=((VDEC_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_ADR | MIU_INTERVAL) : (VDEC_FRAMEBUFFER_ADR));
#endif

    memset(&stVidStatus,0,sizeof(stVidStatus));
    memset(&MVOP_Param,0,sizeof(MVOP_Param));

    stVidStatus.u8Interlace  = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_INTERLACE);
    stVidStatus.u16HorSize   = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_WIDTH);
    stVidStatus.u16HorSize=((stVidStatus.u16HorSize+7)>>3)<<3;
    //if(stVidStatus.u8Interlace)
    //    stVidStatus.u16VerSize   = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_HEIGHT);
    //else
        stVidStatus.u16VerSize   = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_HEIGHT);
    if((stVidStatus.u16HorSize * stVidStatus.u16VerSize) > 1920*1088)
    {
        //In some case with HxW > 1920x1088, if frame rate set 60 fps, it will exceed mvop limit
        stVidStatus.u16FrameRate = 30000;
    }
    else
    {
        //set 60fps is for movie thumbnail seed up about 10ms
        stVidStatus.u16FrameRate = 60000;
    }
    MDrv_MVOP_Init();
    VDPLAYER_DBG(printf("u16CapWidth [%d] \n",stVidStatus.u16HorSize));
    VDPLAYER_DBG(printf("u16CapHeight[%d] \n",stVidStatus.u16VerSize));
    VDPLAYER_DBG(printf("u8Interlace [%d] \n",stVidStatus.u8Interlace));
    VDPLAYER_DBG(printf("u16FrameRate[%d] \n",stVidStatus.u16FrameRate));

    if (stVidStatus.u16FrameRate == 0)
    {
        return FALSE;
    }

    VDPLAYER_DBG(printf("\n~Clear Buffer w[%d] h[%d]\n\n",stVidStatus.u16HorSize,stVidStatus.u16VerSize));
    //Before copy data , it need to clear DWIN Buffer
    //memset((void *)_u32DWINBufStar, 0, stVidStatus.u16HorSize * stVidStatus.u16VerSize *2);

    //=================== setting MCU mode parameter  =====================
    MVOP_Param.u32YOffset   = (U32) _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_LUMA_ADDR)&0x1fffffff;
    MVOP_Param.u32UVOffset  = (U32) _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_CHROM_ADDR)&0x1fffffff;
    VDPLAYER_DBG(printf("\nMVOP y=%x, uv=%x   ",MVOP_Param.u32YOffset, MVOP_Param.u32UVOffset ));

#if ENABLE_MVC
    VDPLAYER_DBG(printf("\n FB=%x, FB end=%x   ",u32FBAddr, (u32FBAddr+VDEC_MVC_FRAMEBUFFER_LEN) ));
    if((MVOP_Param.u32YOffset<u32FBAddr)||(MVOP_Param.u32YOffset>(u32FBAddr+VDEC_MVC_FRAMEBUFFER_LEN)))
        return FALSE;
    if((MVOP_Param.u32UVOffset<u32FBAddr)||(MVOP_Param.u32UVOffset>(u32FBAddr+VDEC_MVC_FRAMEBUFFER_LEN)))
        return FALSE;
#else
    VDPLAYER_DBG(printf("\n FB=%x, FB end=%x   ",u32FBAddr, (u32FBAddr+VDEC_FRAMEBUFFER_LEN) ));
    if((MVOP_Param.u32YOffset<u32FBAddr)||(MVOP_Param.u32YOffset>(u32FBAddr+VDEC_FRAMEBUFFER_LEN)))
        return FALSE;
    if((MVOP_Param.u32UVOffset<u32FBAddr)||(MVOP_Param.u32UVOffset>(u32FBAddr+VDEC_FRAMEBUFFER_LEN)))
        return FALSE;
#endif
    MVOP_Param.u16HSize     =  stVidStatus.u16HorSize;
    MVOP_Param.u16VSize     =  stVidStatus.u16VerSize;

    MVOP_Param.u16StripSize =  (U16)((_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_PITCH)+7)>>3)<<3;
    MVOP_Param.bSD = 1;
    MVOP_Param.bProgressive = (stVidStatus.u8Interlace) ? 0:1;
    MVOP_Param.bUV7bit = 0;
    MVOP_Param.bField = 0;

    enVideoType =(EN_VDP_CODECID) _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CODEC_ID) & E_VDP_CODEC_ATTRIBUTE_MASK;
    enVideoType &= (EN_VDP_CODECID)~(E_VDP_CODEC_TS);

    VDPLAYER_DBG(printf("%x %x\n", enVideoType, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_CODEC_ID)));

    if(enVideoType == E_VDP_CODEC_JPEG)
    {
        if (stVidStatus.u16HorSize < MVOP_JPEG_WIDTH_LOWER_BOUND || stVidStatus.u16VerSize < MVOP_JPEG_HEIGHT_LOWER_BOUND)
        {
            return FALSE;
        }
    }
    else
    {
        if (stVidStatus.u16HorSize < MVOP_WIDTH_LOWER_BOUND || stVidStatus.u16VerSize < MVOP_HEIGHT_LOWER_BOUND)
        {
            return FALSE;
        }
    }

    if (stVidStatus.u16HorSize > MVOP_WIDTH_UPPER_BOUND || stVidStatus.u16VerSize > MVOP_HEIGHT_UPPER_BOUND)
    {
        return FALSE;
    }

    switch (enVideoType)
    {
        case E_VDP_CODEC_MPG_VIDEO:
        case E_VDP_CODEC_MPEG4:
        case E_VDP_CODEC_VC1:
        case E_VDP_CODEC_FLV:
            //MVOP_Param.u16HSize=((MVOP_Param.u16HSize+7)>>3)<<3;
            MVOP_Param.bYUV422= 0;
            MVOP_Param.b422pack= 0;
            MVOP_Param.bDramRdContd= 0;
            MDrv_MVOP_SetTileFormat(E_MVOP_TILE_8x32);
            break;

        case E_VDP_CODEC_H264:
            MVOP_Param.bYUV422= 0;
            MVOP_Param.b422pack= 0;
            MVOP_Param.bDramRdContd= 0;
            MDrv_MVOP_SetTileFormat(E_MVOP_TILE_16x32);
            break;
        #if ENABLE_EVD_FEATURE
        case E_VDP_CODEC_HEVC:
            stEVDfeature.bEnableEVD = TRUE;
            MVOP_Param.bYUV422= 0;
            MVOP_Param.b422pack= 0;
            MVOP_Param.bDramRdContd= 0;
            /*MVOP do not have 32x32 enum, it is for HEVC 8-bit. If MVOP add the enum can use the way.
                    MDrv_MVOP_SetTileFormat(E_MVOP_TILE_32x32);
                    */
            break;
        #endif

        case E_VDP_CODEC_RM_VIDEO:
            MVOP_Param.bYUV422= 0;
            MVOP_Param.b422pack= 0;
            MVOP_Param.bDramRdContd= 0;
            MDrv_MVOP_SetTileFormat(E_MVOP_TILE_16x32);
            break;

        case E_VDP_CODEC_JPEG:
            MVOP_Param.bYUV422= 1;
            MVOP_Param.b422pack= 1;
            MVOP_Param.bDramRdContd= 1;
            break;
        default:
            break;
    }
    MDrv_MVOP_SetInputCfg(MVOP_INPUT_DRAM, &MVOP_Param);
    #if ENABLE_EVD_FEATURE
    if(enVideoType == E_VDP_CODEC_HEVC)
    {
        //To prevent the EVDBit get magic number to cause garbage, if mvop fix setcommand api
        stEVDfeature.eEVDBit[0] = E_MVOP_EVD_8BIT;
        stEVDfeature.eEVDBit[1] = E_MVOP_EVD_8BIT;
        /* if (stream is HEVC 8 Bit)//Can not get 8bit or 10bit from VDplayer
          {
                stEVDfeature.eEVDBit[0] = E_MVOP_EVD_8BIT;
                stEVDfeature.eEVDBit[1] = E_MVOP_EVD_8BIT;
           }
           else if(stream is HEVC 10 Bit)
           {
                stEVDfeature.eEVDBit[0] = E_MVOP_EVD_10BIT;
                stEVDfeature.eEVDBit[1] = E_MVOP_EVD_10BIT;
            }
            */
        MVOP_Handle stMvopHd = { E_MVOP_MODULE_MAIN };
        MDrv_MVOP_SetCommand(&stMvopHd,E_MVOP_CMD_SET_EVD_FEATURE, &stEVDfeature);
    }
    #endif
    MDrv_MVOP_SetOutputCfg(&stVidStatus, FALSE);
    MDrv_MVOP_Enable(TRUE);
    VDPLAYER_DBG(printf("\n  Y addr [0x%x] UV addr[0x%x] \n",MVOP_Param.u32YOffset,MVOP_Param.u32UVOffset));
    VDPLAYER_DBG(printf("ptich  [%d]  \n",MVOP_Param.u16StripSize));
    return TRUE;
}

void MApp_VDPlayer_MovieThumbnail_DWINCapture(U32 * pu32dwin_addr)
{
    U32 u32dwin_size = 0 ;
    GOP_DwinProperty dwinProperty;
#if ENABLE_MVC
    U32 u32FBAddr=((VDEC_MVC_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VDEC_MVC_FRAMEBUFFER_ADR | MIU_INTERVAL) : (VDEC_MVC_FRAMEBUFFER_ADR));
#else
    U32 u32FBAddr=((VDEC_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_ADR | MIU_INTERVAL) : (VDEC_FRAMEBUFFER_ADR));
#endif
    U32 u32_DWIN_Height=0;
    U32 dwinCapTime=0;

#if DWIN_DONE_INT
    GOP_DWinIntInfo DWinIntInfo;
    memset(&DWinIntInfo,0,sizeof(GOP_DWinIntInfo));
#endif
    //if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_INTERLACE))
    //    u32_DWIN_Height=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_HEIGHT);
    //else
        u32_DWIN_Height=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_HEIGHT);

    memset(&dwinProperty,0,sizeof(dwinProperty));

    u32dwin_size =(((_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_WIDTH)+7)>>3)<<3) * u32_DWIN_Height*2; // for YUV420/422 format
    VDPLAYER_DBG(printf("\n LUMA_ADDR=%x ", _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_LUMA_ADDR)) );
    VDPLAYER_DBG(printf("\n VDEC_FRAMEBUFFER_ADR=%x ", u32FBAddr) );
    VDPLAYER_DBG(printf("\n u32dwin_size=%x ", u32dwin_size));

    if ((_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_LUMA_ADDR)&0x1fffffff) - u32FBAddr> u32dwin_size )
    {
        *pu32dwin_addr = u32FBAddr;
        VDPLAYER_DBG(printf("\n u32dwin_addr=%x (from start) ", *pu32dwin_addr));
    }
    else
    {
        *pu32dwin_addr = u32FBAddr+VDEC_FRAMEBUFFER_LEN- u32dwin_size;
        VDPLAYER_DBG(printf("\n u32dwin_addr=%x (from end)", *pu32dwin_addr));
    }

    //=================== setting Dwin parameter  =====================
    //setting Dwin
    dwinProperty.u32fbaddr0= *pu32dwin_addr;
    dwinProperty.u32fbaddr1= *pu32dwin_addr +u32dwin_size ;
    dwinProperty.u16x= 0;
    dwinProperty.u16y = 0;
    dwinProperty.u16w= (((_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FRAMEINFO_WIDTH)+7)>>3)<<3);
    dwinProperty.u16h= u32_DWIN_Height;//MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_V_SIZE);
    dwinProperty.u16fbw=dwinProperty.u16w;


    //RIU[0x1012F2] |= 0x10; //temp setting, remove later.

    MApi_GOP_DWIN_Init();
    MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, FALSE);
    MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, TRUE);
    //MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, FALSE);
    //MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_BF, FALSE);
    //MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_TF, FALSE);
    //MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_VS, FALSE);
    MApi_GOP_DWIN_SetSourceSel(DWIN_SRC_MVOP);
    MApi_GOP_DWIN_SetDataFmt((EN_GOP_DWIN_DATA_FMT)DWIN_DATA_FMT_UV8Y8);
    MApi_GOP_DWIN_SelectSourceScanType((EN_GOP_DWIN_SCAN_MODE)_MApp_VDPlayer_GetShareMemData((EN_VDPLAYER_INFO)E_SHAREMEM_INTERLACE));
    MApi_GOP_DWIN_SetWinProperty(&dwinProperty);
    MApi_GOP_DWIN_SetUVSwap(ENABLE);
    MApi_GOP_DWIN_CaptureOneFrame();

    dwinCapTime = msAPI_Timer_GetTime0();

    while (1) //((MApi_GOP_DWIN_GetIntrStatus() & GOPDWIN_INT_MASK_PROG) == 0)
    {
      #if DWIN_DONE_INT
        MApi_GOP_DWIN_GetDWinIntInfo(&DWinIntInfo);
        //printf("\n DWinIntInfo.u8DWinIntInfo =%d",DWinIntInfo.u8DWinIntInfo );
        if(DWinIntInfo.sDwinIntInfo.bDWinIntPROG ==TRUE)
        {
            break;
        }
      #endif
        if (msAPI_Timer_DiffTimeFromNow(dwinCapTime) >= MOVIE_THUMB_DWIN_CAPTURE_TIMEOUT)
        {
            VDPLAYER_DBG(printf("\n MOVIE_THUMB_DWIN_CAPTURE_TIMEOUT"));
            break; //wait for DWIN capture done(fix RGB mode slide show cannot display some pics randomly)
        }
    }
#if DWIN_DONE_INT
    MApi_GOP_DWIN_ClearIntr(GOPDWIN_INT_MASK_PROG);
    MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, FALSE);
#endif
    //msAPI_Timer_Delayms(100); //temp setting, remove later.
    MApi_GOP_DWIN_Enable(FALSE);
    MDrv_MVOP_Enable(FALSE);
    MDrv_MVOP_Exit();
}


void MApp_VDPlayer_MovieThumbnail_OutputImage(
                                            ST_PHOTO_CAPTURE_RECT *stTo,
                                            ST_PHOTO_CAPTURE_RECT *stFrom)
{
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;

    memset(&stBitbltInfo,0,sizeof(stBitbltInfo));
    memset(&stPitBaseInfo,0,sizeof(stPitBaseInfo));

    MApi_GFX_EnableAlphaBlending(FALSE);
    MApi_GFX_SetAlphaSrcFrom(ABL_FROM_ASRC);

    // BitBlt information settings
    stPitBaseInfo.sb_pit = ( stFrom->u16RectW& (~3)) * 2; // 2 bytes per pixel, the pitch is referring to original image
    stPitBaseInfo.sb_base = stFrom->u32BuffAddr; // the address is referring to original image
    VDPLAYER_DBG(printf("\n stPitBaseInfo.sb_base=%x",stPitBaseInfo.sb_base));
    VDPLAYER_DBG(printf("\n bitblt pitch=%x ",stPitBaseInfo.sb_pit));
    //printf("\n stJpegInstanceInfo.stOutputImg.u8FbFmt=%d ,   GFX_FMT_ARGB8888=%d",stJpegInstanceInfo.stOutputImg.u8FbFmt,GFX_FMT_ARGB8888 );
/*
    if (stJpegInstanceInfo.stOutputImg.u8FbFmt == GFX_FMT_ARGB8888)
    {
        stPitBaseInfo.db_pit = stJpegInstanceInfo.stOutputImg.u16BuffW * 4; // 4 bytes per pixel
    }
    else
*/
    {
        stPitBaseInfo.db_pit = stTo->u16BuffW*2;// 2 bytes per pixel
    }
    stPitBaseInfo.db_base =  stTo->u32BuffAddr;//m_thumbnailFbAttr.addr //stJpegInstanceInfo.stOutputImg.u32BuffAddr;
    VDPLAYER_DBG(printf("\n stPitBaseInfo.db_base =%x  ,   stPitBaseInfo.db_pit=%x",stPitBaseInfo.db_base , stPitBaseInfo.db_pit));

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm = stTo->u8FbFmt; //m_thumbnailFbAttr //stJpegInstanceInfo.stOutputImg.u8FbFmt;
    stBitbltInfo.src_fm = GFX_FMT_YUV422;//stJpegInstanceInfo.stSrcImg.u8FbFmt;
    //printf("\n dst_fm=%x,   src_fm=%x  \n",  stBitbltInfo.dst_fm,  stBitbltInfo.src_fm);
    stBitbltInfo.src_width = stFrom->u16RectW;//MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_H_SIZE);//stJpegInstanceInfo.stResizedImg.u16RectW;
    stBitbltInfo.src_height = stFrom->u16RectH;//MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_V_SIZE);//stJpegInstanceInfo.stResizedImg.u16RectH;

    stBitbltInfo.BitbltCoordinate.v2_x = 0;//stJpegInstanceInfo.stResizedImg.u16RectX;
    stBitbltInfo.BitbltCoordinate.v2_y = 0;//stJpegInstanceInfo.stResizedImg.u16RectY;

    stBitbltInfo.BitbltCoordinate.direction = 0; // TODO: what's this?
    stBitbltInfo.BitbltCoordinate.v0_x = stTo->u16RectX;//stJpegInstanceInfo.stOutputImg.u16RectX;
    stBitbltInfo.BitbltCoordinate.v0_y = stTo->u16RectY; //stJpegInstanceInfo.stOutputImg.u16RectY;

    stBitbltInfo.BitbltCoordinate.width = stTo->u16RectW;//stJpegInstanceInfo.stOutputImg.u16RectW;
    stBitbltInfo.BitbltCoordinate.height = stTo->u16RectH;//stJpegInstanceInfo.stOutputImg.u16RectH;

    //printf("\n  w=%x, h=%x \n",stTo->u16RectW,stTo->u16RectH);
    msAPI_OSD_SetClipWindow(0, 0, stTo->u16BuffW, stTo->u16BuffH);
    msAPI_GE_SetNearestMode(FALSE);

    // shrink src image if the width or height of destination buffer is less than 1/2
    msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_255, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);
    MApp_Photo_ShrinkSrcImage_MovieThumbnail(&stBitbltInfo, &stPitBaseInfo);
    stBitbltInfo.src_height--; // Fix the bottom garbage line.

    VDPLAYER_DBG(printf("Img Out\n"));
    VDPLAYER_DBG(printf("stBitbltInfo: \n"));
    VDPLAYER_DBG(printf("\ttype flag: %bu\n", stBitbltInfo.BitBltTypeFlag));
    VDPLAYER_DBG(printf("\tbmp flag: %bu\n", stBitbltInfo.BmpFlag));
    VDPLAYER_DBG(printf("\tdest fmt: %bu\n", stBitbltInfo.dst_fm));
    VDPLAYER_DBG(printf("\tsrc fmt: %bu\n", stBitbltInfo.src_fm));
    VDPLAYER_DBG(printf("\tbmp hnd: %d\n", stBitbltInfo.bmphandle));
    VDPLAYER_DBG(printf("\tsrc width: %u\n", stBitbltInfo.src_width));
    VDPLAYER_DBG(printf("\tsrc height: %u\n", stBitbltInfo.src_height));
    VDPLAYER_DBG(printf("\tcoord v0x: %u\n", stBitbltInfo.BitbltCoordinate.v0_x));
    VDPLAYER_DBG(printf("\tcoord v0y: %u\n", stBitbltInfo.BitbltCoordinate.v0_y));
    VDPLAYER_DBG(printf("\tcoord width: %u\n", stBitbltInfo.BitbltCoordinate.width));
    VDPLAYER_DBG(printf("\tcoord height: %u\n", stBitbltInfo.BitbltCoordinate.height));
    VDPLAYER_DBG(printf("\tcoord v2x: %u\n", stBitbltInfo.BitbltCoordinate.v2_x));
    VDPLAYER_DBG(printf("\tcoord v2y: %u\n", stBitbltInfo.BitbltCoordinate.v2_y));
    VDPLAYER_DBG(printf("\tcoord direct: %bu\n", stBitbltInfo.BitbltCoordinate.direction));
    VDPLAYER_DBG(printf("stPitBaseInfo: \n"));
    VDPLAYER_DBG(printf("\tsrc pitch: %x\n",stPitBaseInfo.sb_pit));
    VDPLAYER_DBG(printf("\tdst pitch: %x\n",stPitBaseInfo.db_pit));
    VDPLAYER_DBG(printf("\tsrc base: %08lx\n",stPitBaseInfo.sb_base));
    VDPLAYER_DBG(printf("\tdst base: %08lx\n",stPitBaseInfo.db_base));

    msAPI_GE_SetPatchMode(TRUE);
    // output image to destination buffer

    msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();
    msAPI_GE_SetPatchMode(FALSE);

    VDPLAYER_DBG(printf("2.end, sx: %u, sy: %u, sw: %u, sh: %u, sp: %u (0x%x)\n",
            stBitbltInfo.BitbltCoordinate.v2_x,
            stBitbltInfo.BitbltCoordinate.v2_y,
            stBitbltInfo.src_width,
            stBitbltInfo.src_height,
            stPitBaseInfo.sb_pit,
            stPitBaseInfo.sb_pit));
    VDPLAYER_DBG(printf("2.end, ox: %u, oy: %u, ow: %u, oh: %u, dp: %u (0x%x)\n",
            stBitbltInfo.BitbltCoordinate.v0_x,
            stBitbltInfo.BitbltCoordinate.v0_y,
            stBitbltInfo.BitbltCoordinate.width,
            stBitbltInfo.BitbltCoordinate.height,
            stPitBaseInfo.db_pit,
            stPitBaseInfo.db_pit));

    // NOTE: it's critical to reset GE registers after rotation
    msAPI_GE_SetMirror(0, 0);
    msAPI_GE_SetRotate(GEROTATE_0);

    // restore clip window to full screen
    msAPI_OSD_SetClipWindow(0, 0, g_IPanel.Width(), g_IPanel.Height());

    VDPLAYER_DBG(printf("-------Separate Line-------\n"));
}
#endif //#if MOVIE_THUMBNAIL

#if (SUPPERTED_SEAMLESS_SMOTH)
extern U32 MApi_Seamless_Stream_Open(void *pPrivate, U8 u8Mode, E_DATA_STREAM_TYPE eType);
extern BOOLEAN MApi_Seamless_Stream_Close(U32 u32Hdl);
extern LongLong MApi_Seamless_Stream_Length(U32 u32Hdl);
extern U32 MApi_Seamless_Stream_Read(U32 u32Hdl, void *pBuffAddr, U32 u32Length);
extern BOOLEAN MApi_Seamless_Stream_Init(void);

void MApp_VDPlayer_SetSeamlessSmoth(BOOLEAN bEnable)
{
    if (bEnable)
    {
        FN_DATA_STRM_IO stStreamIOFunc;
        memset(&stStreamIOFunc,0,sizeof(FN_DATA_STRM_IO));

        /*
        if (EPGEXTDB_SDRAM_LEN > 0)
        {
            m_u32TableAddress = EPGEXTDB_SDRAM_LEN;
            m_u32TableSize= EPGEXTDB_SDRAM_LEN;
        }
        else
        */
        {
            m_u32TableAddress = 0;
            m_u32TableSize= 0x400000;
        }
        m_eSeamlessPreStreamMode = msAPI_DataStreamIO_GetStreamMode();
        // To avoid the resource unreleased, it should unregister first.
        msAPI_DataStreamIO_OptionRegistation(NULL, E_DATA_STREAM_MODE_SEAMLESS);

        stStreamIOFunc.pfnInit = MApi_Seamless_Stream_Init;
        stStreamIOFunc.pfnFinalize = NULL;
        stStreamIOFunc.pfnOpen = MApi_Seamless_Stream_Open;
        stStreamIOFunc.pfnClose = MApi_Seamless_Stream_Close;
        stStreamIOFunc.pfnRead = MApi_Seamless_Stream_Read;
        stStreamIOFunc.pfnSeek = NULL;
        stStreamIOFunc.pfnTell = NULL;
        stStreamIOFunc.pfnLength = MApi_Seamless_Stream_Length;
        msAPI_DataStreamIO_OptionRegistation(&stStreamIOFunc, E_DATA_STREAM_MODE_SEAMLESS);
        msAPI_DataStreamIO_SetStreamMode(E_DATA_STREAM_MODE_SEAMLESS);

        MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_ENABLE_INTERNAL_SUBTITLE, FALSE);
        MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_BM_STREAM_MODE, E_BM_STREAM_MODE_NETWORK_UNSEEKABLE);
    }
    else
    {
        m_u32TableAddress = 0;
        m_u32TableSize= 0;
        msAPI_DataStreamIO_OptionRegistation(NULL, E_DATA_STREAM_MODE_SEAMLESS);
        msAPI_DataStreamIO_SetStreamMode(m_eSeamlessPreStreamMode);
        MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_ENABLE_INTERNAL_SUBTITLE, TRUE);
        MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_BM_STREAM_MODE, E_BM_STREAM_MODE_NORMAL);
    }
}
#endif

#if ENABLE_HK_AVI
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if ENABLE_HK_AVI_PERFORMANCE_IMPROVE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* (a * b) / c */
typedef struct
{
  U32 u32Precal_q;  /* b / c */
  U32 u32Precal_r;  /* b % c */
  U32 u32Divider;   /* c */
  U32 u32RunTime_q; /* runtime quotient */
  U32 u32RunTime_r; /* runtime remain */
  U32 u32Blockalign; /* for punAudio->stMPEG.u32BlockAlign */
} ST_DIV;

typedef U32 (*CalAudioAlignedSizeFuncPtr)(UN_VDP_AUDIO_PARAM *punAudio, U32 u32Pkt_Size);
typedef U32 (*CalAudioBitTimeFuncPtr)(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu);

extern BOOLEAN msAPI_VDPlayer_BMRead16Bytes_LE_AutoLoad(U32 *u32Ptr0, U32 *u32Ptr1, U32 *u32Ptr2, U32 *u32Ptr3);

#if 0//(CHIP_FAMILY_TYPE == CHIP_FAMILY_M12)
static inline U32 ff1(U32 v)
{
    register U32 val;
    asm volatile("l.ff1 %0,%1" : "=r"(val) : "r" (v));
    return val;
}

static inline U32 fl1(U32 v)
{
    register U32 val;
    asm volatile("l.fl1 %0,%1" : "=r"(val) : "r" (v));
    return val;
}
#else
static inline U32 fl1(U32 x)
{
    int r = 32;

    if (!x)
        return 0;

    if (!(x & 0xffff0000u)) {
        x <<= 16;
        r -= 16;
    }
    if (!(x & 0xff000000u)) {
        x <<= 8;
        r -= 8;
    }
    if (!(x & 0xf0000000u)) {
        x <<= 4;
        r -= 4;
    }
    if (!(x & 0xc0000000u)) {
        x <<= 2;
        r -= 2;
    }
    if (!(x & 0x80000000u)) {
        x <<= 1;
        r -= 1;
    }
    return r;
}
#endif

static inline U32 MulDiv(U32 a, U32 b, U32 c)
{
    U32 q; // the final quotient
    U32 r; // the final remainder
    U32 qn; // the quotient for the first divide
    U32 rn; // the remainder of the first divide
    if (a >= b) {
        qn = a / c;
        rn = a % c;
        if (fl1(b)+fl1(rn) <= 32) {
            q = qn * b;
            r = rn * b;
            if (r >= c)
                q += r/c;
        } else {
            q = (U32)(((U64)a * (U64)b) / c);
        }
    } else {
        qn = b / c;
        rn = b % c;
        if (fl1(a)+fl1(rn) <= 32) {
            q = qn * a;
            r = rn * a;
            if (r >= c)
                q += r/c;
        } else {
            q = (U32)(((U64)a * (U64)b) / c);
        }
    }

    return q;
}

void msAPI_VDPlayer_GetShareMemoryDataAVIScan(PST_HK_AVI_SCAN pstInfo)
{
    U32 u32Address;
    u32Address = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HK_AVI_SCAN);
    u32Address = _PA2VA(u32Address);
    memcpy((void *)pstInfo, (void *)u32Address, sizeof(ST_HK_AVI_SCAN));
}

void msAPI_VDPlayer_SetShareMemoryDataAVIScan(PST_HK_AVI_SCAN pstInfo)
{
    U32 u32Address;
    u32Address = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HK_AVI_SCAN);
    u32Address = _PA2VA(u32Address);
    memcpy((void *)u32Address, (void *)pstInfo, sizeof(ST_HK_AVI_SCAN));
    MsOS_FlushMemory();
}

#if ENABLE_AUDIO_HANDLER
static inline EN_VDP_DEMUX_INDEXTAB_RET msAPI_VDPlayer_Demuxer_SaveAudioKeyIdx(U8 u8Track, ST_VDP_DEMUX_AUDIO_KEYINDEX *pstKeyIdx)
{
    U32 *pu32KeyIdx, *pu32PreKeyIdx;
    U32 *pu32EndAddr;

    if(g_stDemuxer.u32AudioKeyBufAddr[u8Track] == 0)
    {
        return E_VDP_DEMUX_BUD_INDEX_TAB_RET_FAILED;
    }

    pu32KeyIdx = (U32 *)(g_stDemuxer.u32AudioKeyBufAddr[u8Track] + g_stDemuxer.u32Audio_IdxSize[u8Track]);
    pu32EndAddr = (U32 *)(g_stDemuxer.u32AudioKeyBufAddr[u8Track] + g_stDemuxer.u32AudioKeyBufSize[u8Track] - g_stDemuxer.u8AudioKeyIdxSize);

    if (g_stDemuxer.u32Audio_IdxSize[u8Track] == 0)
    {
        pu32PreKeyIdx = NULL;
    }
    else
    {
        pu32PreKeyIdx = (U32 *)(g_stDemuxer.u32AudioKeyBufAddr[u8Track] + g_stDemuxer.u32Audio_IdxSize[u8Track] - g_stDemuxer.u8AudioKeyIdxSize);
    }

    if (pu32KeyIdx <= pu32EndAddr)
    {
        if (pu32PreKeyIdx != NULL)
        {
            if (pstKeyIdx->u32Pts - pu32PreKeyIdx[1] < g_stDemuxer.u32AudioKeyIdxPeriod)
            {
                return E_VDP_DEMUX_BUD_INDEX_TAB_RET_FAILED;
            }
        }

        pu32KeyIdx[0] = u32u64_0(pstKeyIdx->u64Offset);
        pu32KeyIdx[1] = pstKeyIdx->u32Pts;
        pu32KeyIdx[2] = (pstKeyIdx->u32Size & 0xFFFFFF) | (u32u64_1(pstKeyIdx->u64Offset) << 24);
        pu32KeyIdx[3] = pstKeyIdx->u32Frm_Info_Idx;

        g_stDemuxer.u32Audio_IdxSize[u8Track] += g_stDemuxer.u8AudioKeyIdxSize;
    }
    else
    {
        return E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL;
    }

    return E_VDP_DEMUX_BUD_INDEX_TAB_RET_SUCCESS;
}
#endif

static inline BOOL msAPI_VDPlayer_Demuxer_SaveAudioKeyInfo(U8 u8Track_Id, U32 u32Pts)
{
    U32 *pu32KeyIdx;
    U32 *pu32EndAddr;

    pu32KeyIdx = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.u32Audio_IdxSize[u8Track_Id]);
    pu32EndAddr = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.stDataBuffer.u32IndexBuffSize - g_stDemuxer.u8KeyIdxSize);

    if (pu32KeyIdx <= pu32EndAddr)
    {
        pu32KeyIdx[4 + u8Track_Id] = u32Pts;

        g_stDemuxer.u32Audio_IdxSize[u8Track_Id] += g_stDemuxer.u8KeyIdxSize;
    }
    else
    {
        return FALSE;
    }
    return TRUE;
}

static inline void msAPI_VDPlayer_Demuxer_GetAudioKeyIdx(U8 u8Track, U32 u32KeyIdxNum, ST_VDP_DEMUX_AUDIO_KEYINDEX *pstKeyIdx)
{
    U32 *pu32KeyIdx;
    U32 *pu32EndAddr;

    pu32KeyIdx = (U32 *)(g_stDemuxer.u32AudioKeyBufAddr[u8Track] + u32KeyIdxNum * g_stDemuxer.u8AudioKeyIdxSize);
    pu32EndAddr = (U32 *)(g_stDemuxer.u32AudioKeyBufAddr[u8Track] + g_stDemuxer.u32AudioKeyBufSize[u8Track] - g_stDemuxer.u8KeyIdxSize);

    if ((pu32KeyIdx <= pu32EndAddr) && (pstKeyIdx))
    {
        pstKeyIdx->u64Offset= (((U64)pu32KeyIdx[2] & ~0xFFFFFF) << 8) + pu32KeyIdx[0];
        pstKeyIdx->u32Pts   = pu32KeyIdx[1];
        pstKeyIdx->u32Size  = pu32KeyIdx[2] & 0xFFFFFF;
        pstKeyIdx->u32Frm_Info_Idx = pu32KeyIdx[3];
        return;
    }

    return;
}

static inline void msAPI_VDPlayer_Demuxer_GetVideoKeyIdx(U32 u32KeyIdxNum, ST_VDP_DEMUX_KEYINDEX *pstKeyIdx)
{
    U32 *pu32KeyIdx;
    U32 *pu32EndAddr;

    pu32KeyIdx = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + u32KeyIdxNum * g_stDemuxer.u8KeyIdxSize);
    pu32EndAddr = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.stDataBuffer.u32IndexBuffSize - g_stDemuxer.u8KeyIdxSize);

    if ((pu32KeyIdx <= pu32EndAddr) && (pstKeyIdx))
    {
        pstKeyIdx->u64Offset= (((U64)pu32KeyIdx[2] & ~0xFFFFFF) << 8) + pu32KeyIdx[0];
        pstKeyIdx->u32Pts   = pu32KeyIdx[1];
        pstKeyIdx->u32Size  = pu32KeyIdx[2] & 0xFFFFFF;
        pstKeyIdx->u32Frm_Info_Idx = pu32KeyIdx[3];
    }

    return ;
}

static inline EN_VDP_DEMUX_INDEXTAB_RET msAPI_VDPlayer_Demuxer_SaveVideoKeyIdx(ST_VDP_DEMUX_KEYINDEX *pstKeyIdx)
{
    U32 *pu32KeyIdx, *pu32PreKeyIdx;
    U32 *pu32EndAddr;
    U64 u64PreOffset;

    pu32KeyIdx = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.u32Video_IdxSize);
    pu32EndAddr = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.stDataBuffer.u32IndexBuffSize - g_stDemuxer.u8KeyIdxSize);

    if (g_stDemuxer.u32Video_IdxSize == 0)
    {
        pu32PreKeyIdx = NULL;
        u64PreOffset = 0;
    }
    else
    {
        pu32PreKeyIdx = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.u32Video_IdxSize - g_stDemuxer.u8KeyIdxSize);
        u64PreOffset = ((((U64)pu32PreKeyIdx[2] & ~0xFFFFFF) << 8) + pu32PreKeyIdx[0]);
    }

    if (pu32KeyIdx <= pu32EndAddr)
    {
        if (pu32PreKeyIdx != NULL)
        {
            if ((pstKeyIdx->u32Pts - pu32PreKeyIdx[1] < g_stDemuxer.u32KeyIdxPeriod) ||
                (pstKeyIdx->u64Offset <= u64PreOffset))
        {
            return E_VDP_DEMUX_BUD_INDEX_TAB_RET_FAILED;
        }
        }

        pu32KeyIdx[0] = u32u64_0(pstKeyIdx->u64Offset);
        pu32KeyIdx[1] = pstKeyIdx->u32Pts;
        pu32KeyIdx[2] = (pstKeyIdx->u32Size & 0xFFFFFF) | (u32u64_1(pstKeyIdx->u64Offset) << 24);
        pu32KeyIdx[3] = pstKeyIdx->u32Frm_Info_Idx;

        if(g_stDemuxer.u32Video_IdxSize == 0)
        {
            g_stDemuxer.u32FirstVideoKeyFramePTS = pstKeyIdx->u32Pts;
        }
        g_stDemuxer.u32Video_IdxSize += g_stDemuxer.u8KeyIdxSize;
        g_stDemuxer.u32lastVideoKeyFramePTS = pstKeyIdx->u32Pts;
    }
    else
    {
        return E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL;
    }

    return E_VDP_DEMUX_BUD_INDEX_TAB_RET_SUCCESS;
}

static inline U32 msAPI_VDPlayer_Demuxer_CalVideoFrameTime(U32 u32FrmIdx)
{
    U32 u32FrameRate;
    U32 u32FrameRateBase;
    U32 u32Ms;

    u32FrameRate = g_stDemuxer.stBitsContent.Container.stAVI.VideoTracks[0].u32FrameRate;
    u32FrameRateBase = g_stDemuxer.stBitsContent.Container.stAVI.VideoTracks[0].u32FrameRateBase;

    if ((u32FrameRateBase == 0) || (u32FrameRate == 0) ||
        (u32FrameRate == 1 && u32FrameRateBase == 1))
    {
//        MFP_ERR(printf("No FrameRate information\n"));
        u32FrameRateBase = 41708;
        u32FrameRate = 1000000;
    }

    u32Ms = MulDiv(u32FrmIdx, u32FrameRateBase * 1000, u32FrameRate);

    return u32Ms;
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioAlignedSize_MPG_AUDIO(UN_VDP_AUDIO_PARAM *punAudio, U32 u32Pkt_Size)
{
    U32 u32AlignedPktSize;
    u32AlignedPktSize = ((u32Pkt_Size + punAudio->stMPEG.u32BlockAlign) - 1) / punAudio->stMPEG.u32BlockAlign;
    u32AlignedPktSize *= punAudio->stMPEG.u32BlockAlign;
    return u32AlignedPktSize;
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioAlignedSize_WMA(UN_VDP_AUDIO_PARAM *punAudio, U32 u32Pkt_Size)
{
    U32 u32AlignedPktSize;
    u32AlignedPktSize = (u32Pkt_Size + punAudio->stWMA.u32BlockAlign - 1) / punAudio->stWMA.u32BlockAlign;
    u32AlignedPktSize *= punAudio->stWMA.u32BlockAlign;
    return u32AlignedPktSize;
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioAlignedSize_Default(UN_VDP_AUDIO_PARAM *punAudio, U32 u32Pkt_Size)
{
    UNUSED(punAudio);
    return u32Pkt_Size;
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioAlignedSize(U8 u8Track_Id, U32 u32Pkt_Size)
{
    UN_VDP_AUDIO_PARAM *punAudio;
    EN_VDP_CODECID enCodecID;
    U32 u32AlignedPktSize;

    u32AlignedPktSize = u32Pkt_Size;
    enCodecID = g_stDemuxer.stBitsContent.enAudioCodecID[u8Track_Id];
    punAudio = &g_stDemuxer.stBitsContent.unAudioParam[u8Track_Id];
    switch(enCodecID & E_VDP_CODEC_ATTRIBUTE_MASK)
    {
        case E_VDP_CODEC_MPG_AUDIO:
            if ((punAudio->stMPEG.u32SampleSize == 0) && (punAudio->stMPEG.u32BlockAlign != 0))
            {
                u32AlignedPktSize = ((u32Pkt_Size + punAudio->stMPEG.u32BlockAlign) - 1) / punAudio->stMPEG.u32BlockAlign;
                u32AlignedPktSize *= punAudio->stMPEG.u32BlockAlign;
            }
            break;

        case E_VDP_CODEC_WMA:
            if (punAudio->stWMA.u32BlockAlign != 0)
            {
                u32AlignedPktSize = (u32Pkt_Size + punAudio->stWMA.u32BlockAlign - 1) / punAudio->stWMA.u32BlockAlign;
                u32AlignedPktSize *= punAudio->stWMA.u32BlockAlign;
            }
            break;

        default:
            break;
    }

    return u32AlignedPktSize;
}

static inline U32 msAPI_VDPlayer_Demuxer_AudioIncrTime(ST_DIV *stDiv, U32 u32Count)
{
   stDiv->u32RunTime_q += u32Count * stDiv->u32Precal_q;
   stDiv->u32RunTime_r += u32Count * stDiv->u32Precal_r;
   if (stDiv->u32RunTime_r > stDiv->u32Divider)
   {
      U32 integer = stDiv->u32RunTime_r / stDiv->u32Divider;
      stDiv->u32RunTime_q += integer;
      stDiv->u32RunTime_r -= integer * stDiv->u32Divider;
   }

   return stDiv->u32RunTime_q;
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_MPG_AUDIO1(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    u32Pkt_Size_Accu = ((u32Pkt_Size_Accu + stDiv->u32Blockalign) - 1) / stDiv->u32Blockalign;
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_MPG_AUDIO2(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_MPG_AUDIO3(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_AC3(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_AAC1(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size_Accu);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_AAC1_Accu(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_AAC2(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size_Accu);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_AAC2_Accu(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_PCM(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_ADPCM(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_WMA(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_DTS(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_AMR_NB(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(u32Pkt_Size);
    return msAPI_VDPlayer_Demuxer_AudioIncrTime(stDiv, u32Pkt_Size_Accu);
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime_Default(ST_DIV *stDiv, U32 u32Pkt_Size, U32 u32Pkt_Size_Accu)
{
    UNUSED(stDiv);
    UNUSED(u32Pkt_Size);
    UNUSED(u32Pkt_Size_Accu);
    return 0;
}

static inline U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime(U8 u8Track_Id, U32 u32Pkt_Size)
{
    UN_VDP_AUDIO_PARAM *punAudio;
    EN_VDP_CODECID enCodecID;
    U32 u32Ms;

    u32Ms = 0;
    enCodecID = g_stDemuxer.stBitsContent.enAudioCodecID[u8Track_Id];
    punAudio = &g_stDemuxer.stBitsContent.unAudioParam[u8Track_Id];
    switch(enCodecID & E_VDP_CODEC_ATTRIBUTE_MASK)
    {
        case E_VDP_CODEC_MPG_AUDIO:
            if ((punAudio->stMPEG.u32SampleSize == 0) &&
                (punAudio->stMPEG.u32BlockAlign != 0) &&
                (punAudio->stMPEG.u32Rate != 0)) // VBR
            {
                u32Ms = ((u32Pkt_Size + punAudio->stMPEG.u32BlockAlign) - 1) / punAudio->stMPEG.u32BlockAlign;
                u32Ms = (U32)(((U64)u32Ms * 1000 * punAudio->stMPEG.u32Scale) / punAudio->stMPEG.u32Rate);
            }
            else if ((punAudio->stMPEG.u32BitRate != 0) && (g_stDemuxer.bEnableCalcByBitRate == TRUE))
            {
                u32Ms = (U32)(((U64)u32Pkt_Size * 8 * 1000) / punAudio->stMPEG.u32BitRate);
            }
            else if ((punAudio->stMPEG.u32Rate * punAudio->stMPEG.u32SampleSize) != 0)
            {
                u32Ms = (U32)(((U64)u32Pkt_Size * 1000 * punAudio->stMPEG.u32Scale) /
                    ((U64)punAudio->stMPEG.u32Rate * punAudio->stMPEG.u32SampleSize));
            }
            break;

        case E_VDP_CODEC_AAC:
            if ((g_stDemuxer.bEnableCalcByBitRate == TRUE) && (punAudio->stAAC.u32BitRate != 0))
            {
                u32Ms = (U32)(((U64)u32Pkt_Size * 8 * 1000) / punAudio->stAAC.u32BitRate);
            }
            else if (punAudio->stAAC.u32SampleRate != 0)
            {
                u32Ms = (U32)(((U64)u32Pkt_Size * AAC_SAMPLE_PER_FRAME * 1000) / punAudio->stAAC.u32SampleRate);
            }
            break;

        case E_VDP_CODEC_AC3:
            if ((punAudio->stAC3.u16Frame_Size * punAudio->stAC3.u16Audio_Frame_TimeBase) != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * (U64)punAudio->stAC3.u32Audio_Frame_Time) / ((U32)punAudio->stAC3.u16Frame_Size * (U32)punAudio->stAC3.u16Audio_Frame_TimeBase));
            }
            break;

        case E_VDP_CODEC_DTS:
            if ((punAudio->stDTS.u16Frame_Size * punAudio->stDTS.u16Audio_Frame_TimeBase) != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * (U64)punAudio->stDTS.u32Audio_Frame_Time) / ((U32)punAudio->stDTS.u16Frame_Size * (U32)punAudio->stDTS.u16Audio_Frame_TimeBase));
            }
            break;

        case E_VDP_CODEC_PCM:
            if ((punAudio->stPCM.u32BitsPerSample * punAudio->stPCM.u32Channel * punAudio->stPCM.u32SampleRate) != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * 1000 * 8) /
                ((U64)punAudio->stPCM.u32BitsPerSample * punAudio->stPCM.u32Channel * punAudio->stPCM.u32SampleRate));
            }
            break;

        case E_VDP_CODEC_ADPCM:
            if ((punAudio->stADPCM.u32SampleRate * punAudio->stADPCM.u32BlockAlign) != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * 1000 * punAudio->stADPCM.u32SamplesPerBlock) /
                ((U64)punAudio->stADPCM.u32SampleRate * punAudio->stADPCM.u32BlockAlign));
            }
            break;
        case E_VDP_CODEC_WMA:
            if (punAudio->stWMA.u32ByteRate != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * 1000) / punAudio->stWMA.u32ByteRate);
            }
            break;

        case E_VDP_CODEC_AMR_NB:
        case E_VDP_CODEC_AMR_WB:
            if (punAudio->stAMR.u32BitsPerSec!= 0)
            {
                //one frame 20ms
                u32Ms = (u32Pkt_Size*20)/punAudio->stAMR.u32BitsPerSec;
            }
            break;

        default:
            break;
    }

    return u32Ms;
}

static void msAPI_VDPlayer_DemuxAVI_ChangeFilePosition(U64 u64NewPosition ,U32 u32readsize)
{
    U64 u64CurrFilePosition = msAPI_VDPlayer_BMFileTell();
    EN_BM_RET enRet;

    if (u64CurrFilePosition == u64NewPosition)
    {
        // do nothing
    }
    else
    {
        if ((u64NewPosition > u64CurrFilePosition)
                && ((u64NewPosition - u64CurrFilePosition) < (U64)msAPI_VDPlayer_BMBuffer_Remainder()))
        {
            // if there is enough data in BM, do data flushing
            msAPI_VDPlayer_BMFlushBytes((U32)(u64NewPosition - u64CurrFilePosition));
        }
        else
        {
            // no enough data in BM, do file seeking
            enRet = msAPI_VDPlayer_BMFileSeek(u64NewPosition, E_BM_FILEPOS_SEEK_SET);
            if (enRet == E_BM_RET_FAIL)
            {
                if ((u64NewPosition < u64CurrFilePosition) && (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_NETWORKSTREAM_MODE) == E_BM_STREAM_MODE_NETWORK_UNSEEKABLE))
                {
                    printf("unseekable!!!!!!!! CAN NOT rewind, cur: %x.%x, new: %x.%x\n", (U32)(u64CurrFilePosition >> 32), (U32)u64CurrFilePosition, (U32)(u64NewPosition >> 32), (U32)u64NewPosition);
                }
                else
                {
                    msAPI_VDPlayer_BMFlushBytes((U32)(u64NewPosition - u64CurrFilePosition));
                }
            }
            else
            {
                msAPI_VDPlayer_BMFillBuffer_Custom(u32readsize);
            }
        }
    }
}

static inline U32 msAPI_VDPlayer_DemuxAVI_LoadIndexCnt(U32 u32Stream)
{
    ST_OPEN_DML_IDX_HEADER_INFO *pstOpenDmlIdxHeaderInfo = g_stDemuxer.stBitsContent.Container.stAVI.pstOpenDmlIdxHeaderInfo + u32Stream;

    return pstOpenDmlIdxHeaderInfo->u32Cnt;
}

static inline void msAPI_VDPlayer_DemuxAVI_LoadIndexInfo(U32 u32Stream, U32 u32Cnt, U64 *u64IdxOffset, U32 *u32Size)
{
    ST_OPEN_DML_IDX_HEADER_INFO *pstOpenDmlIdxHeaderInfo = g_stDemuxer.stBitsContent.Container.stAVI.pstOpenDmlIdxHeaderInfo + u32Stream;
    ST_OPEN_DML_IDX_INFO *pstOpenDmlIdxInfo = ((ST_OPEN_DML_IDX_INFO *)_PA2VA((U32)pstOpenDmlIdxHeaderInfo->pstOpenDmlIdxInfo)) + u32Cnt;

    *u64IdxOffset = pstOpenDmlIdxInfo->u64IdxOffset;
    *u32Size = pstOpenDmlIdxInfo->u32Size;
}

static BOOLEAN msAPI_VDPlayer_DemuxAVI_BuildOpenDmlIndex_Video(void)
{
    S8 s8StreamIndex;
    U32 u32StdIdxCnt, u32AIdxCnt, u32ChunkId;
    U32 u32Size, u32i, u32Skip;
    U32 u32Frmcnt;
    U32 u32VideoKeyIdxCnt;
    U64 u64StdIdxOffset;
    ST_AVI_STD_INDEX stAviStdIndex;
    ST_AVI_STD_INDEX *pstAviStdIndex = &stAviStdIndex;
    ST_VDP_DEMUX_KEYINDEX stDemuxKeyIdx;
    BOOL bIsDRM;
    U32 u32DrmSize = 0, u32DrmOffset = 0, u32DrmPts = 0;

    s8StreamIndex = g_stDemuxer.stBitsContent.s8Video_StreamId;

    u32i = 0;
    u32Frmcnt = 0;
    u32VideoKeyIdxCnt = 0;
    memset(&stDemuxKeyIdx, 0, sizeof(stDemuxKeyIdx));
    memset(&stAviStdIndex, 0, sizeof(ST_AVI_STD_INDEX));

    u32StdIdxCnt = msAPI_VDPlayer_DemuxAVI_LoadIndexCnt(s8StreamIndex);
    if (u32StdIdxCnt == 0)
    {
        return FALSE;
    }

    while (u32StdIdxCnt)
    {
        BOOL bVideoStreamIdxChunk = FALSE;

        msAPI_VDPlayer_DemuxAVI_LoadIndexInfo(s8StreamIndex, u32i++, &u64StdIdxOffset, &u32Size);
        if (u64StdIdxOffset > g_stDemuxer.stBitsContent.Container.stAVI.u64FileSize)
        {
            break;
        }

        bIsDRM = FALSE;
        msAPI_VDPlayer_DemuxAVI_ChangeFilePosition(u64StdIdxOffset,((u32Size&~0xFFF)+0x1000));

        msAPI_VDPlayer_BMFlushBytes(8);
        pstAviStdIndex->u16LongsPerEntry= (U16)msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(2);
        msAPI_VDPlayer_BMFlushBytes(2);
        pstAviStdIndex->u32EntriesInUse = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
        pstAviStdIndex->u32ChunkId      = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();

        // check if this index chunk for this video stream
        u32ChunkId = pstAviStdIndex->u32ChunkId;
        if ((u8u32_2(u32ChunkId) == 'd') &&
                ((u8u32_3(u32ChunkId) == 'c') || (u8u32_3(u32ChunkId) == 'b')||(u8u32_3(u32ChunkId) == 'd')))
        {
            if(u8u32_3(u32ChunkId) == 'd')
            {
                bIsDRM = TRUE;
            }

            if ((isdigit(u8u32_0(u32ChunkId))) && (isdigit(u8u32_1(u32ChunkId))))
            {
                u32ChunkId = ((u8u32_0(u32ChunkId) - '0') * 10) + (u8u32_1(u32ChunkId) - '0');
                if (u32ChunkId == (U32)g_stDemuxer.stBitsContent.s8Video_StreamId)
                {
                    bVideoStreamIdxChunk = TRUE;
                }
            }
        }

        if (bVideoStreamIdxChunk == FALSE)
        {
            u32StdIdxCnt--;
            msAPI_VDPlayer_BMFlushBytes(12);
            continue;
        }

        u32u64_0(pstAviStdIndex->u64BaseOffset) = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
        u32u64_1(pstAviStdIndex->u64BaseOffset) = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
        msAPI_VDPlayer_BMFlushBytes(4);

        u32Skip = pstAviStdIndex->u16LongsPerEntry * 4 - sizeof(pstAviStdIndex->stAIndex);
        u32AIdxCnt = pstAviStdIndex->u32EntriesInUse;
        while (u32AIdxCnt)
        {
            pstAviStdIndex->stAIndex.u32Offset = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
            pstAviStdIndex->stAIndex.u32Size = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();

            if(bIsDRM)
            {
                u32DrmOffset = pstAviStdIndex->stAIndex.u32Offset;
                u32DrmSize   = pstAviStdIndex->stAIndex.u32Size;
                u32DrmPts    = msAPI_VDPlayer_Demuxer_CalVideoFrameTime(u32Frmcnt);
            }
            else if((u32DrmOffset != 0) && (u32DrmSize != 0) && (u32DrmPts !=0))
            {
                pstAviStdIndex->stAIndex.u32Offset = u32DrmOffset;
                pstAviStdIndex->stAIndex.u32Size   = u32DrmSize ;
            }

            if (!(pstAviStdIndex->stAIndex.u32Size & AVI_NOT_KEYFRAME))
            {
                EN_VDP_DEMUX_INDEXTAB_RET Ret;

                stDemuxKeyIdx.u32Size = pstAviStdIndex->stAIndex.u32Size + 8;
                stDemuxKeyIdx.u64Offset = pstAviStdIndex->u64BaseOffset + pstAviStdIndex->stAIndex.u32Offset - 8;
                stDemuxKeyIdx.u32Pts = msAPI_VDPlayer_Demuxer_CalVideoFrameTime(u32Frmcnt);

                if(u32DrmPts != 0)
                {
                    stDemuxKeyIdx.u32Pts = u32DrmPts;
                }
                else
                {
                    stDemuxKeyIdx.u32Pts = msAPI_VDPlayer_Demuxer_CalVideoFrameTime(u32Frmcnt);
                }

                u32DrmOffset = u32DrmSize = u32DrmPts = 0;

                Ret = msAPI_VDPlayer_Demuxer_SaveVideoKeyIdx(&stDemuxKeyIdx);

                if (Ret == E_VDP_DEMUX_BUD_INDEX_TAB_RET_SUCCESS)
                {
                    u32VideoKeyIdxCnt++;
                }
                else if (Ret == E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL)
                {
                    u32StdIdxCnt = 1;
                    break;
                }
                if (g_stDemuxer.u8ThumbNailMode && (stDemuxKeyIdx.u32Pts > THUMBNAIL_JUMPTIME))
                {
                    if ((_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_PREVIEW_MODE) & E_VDP_PREVIEW_INFO_INDEXTABLE) == FALSE)
                    {
                        u32StdIdxCnt = 1;
                        break;
                    }
                }
            }
            else
            {
                pstAviStdIndex->stAIndex.u32Size &= ~AVI_NOT_KEYFRAME;
            }

            u32Frmcnt++;

            u32AIdxCnt--;
            if (u32Skip)
            {
                msAPI_VDPlayer_BMFlushBytes(u32Skip);
            }
        }

        u32StdIdxCnt--;
    }

    if (u32VideoKeyIdxCnt == 0)
    {
        return FALSE;
    }

    g_stDemuxer.stBitsContent.Container.stAVI.u32VideoKeyIdxCnt = u32VideoKeyIdxCnt;
    return TRUE;
}

static BOOLEAN msAPI_VDPlayer_DemuxAVI_BuildOpenDmlIndex_Audios(void)
{
    U32 u32StdIdxCnt, u32AIdxCnt;
    U32 u32Size, u32Skip, u32AccumulativeSize;
    U64 u64StdIdxOffset;

    ST_AVI_STD_INDEX stAviStdIndex;
    ST_AVI_STD_INDEX *pstAviStdIndex = &stAviStdIndex;
    ST_VDP_DEMUX_KEYINDEX stDemuxVideoKeyIdx, stDemuxAudioKeyIdx;
    U8 u8AudioTrackIdx, u8StreamIndex;
    U32 u32VideoKeyIndexCnt, u32i, u32Cnt, u32ChunkId;

    if (g_stDemuxer.stBitsContent.u8Nb_AudioTracks == 0)
    {
        return TRUE;
    }

    u32VideoKeyIndexCnt = g_stDemuxer.stBitsContent.Container.stAVI.u32VideoKeyIdxCnt;
    if (!u32VideoKeyIndexCnt)
    {
        return TRUE;
    }

    memset(&stAviStdIndex, 0, sizeof(ST_AVI_STD_INDEX));
    memset(&stDemuxVideoKeyIdx, 0, sizeof(stDemuxVideoKeyIdx));

    u8AudioTrackIdx = 0;
    while (u8AudioTrackIdx < g_stDemuxer.stBitsContent.u8Nb_AudioTracks)
    {
        U32 u32Frmcnt;

        u32Frmcnt = 0;
        memset(&stDemuxAudioKeyIdx, 0, sizeof(stDemuxAudioKeyIdx));
        u8StreamIndex = g_stDemuxer.u8AudioTrackIDMap[u8AudioTrackIdx];
        u32AccumulativeSize = 0;

        u32Cnt = u32i = 0;
#if ENABLE_AUDIO_HANDLER
        if (g_stDemuxer.bEnableAudioHandler == FALSE)
#endif
        {
            msAPI_VDPlayer_Demuxer_GetVideoKeyIdx(u32Cnt++, &stDemuxVideoKeyIdx);
        }

        u32StdIdxCnt = msAPI_VDPlayer_DemuxAVI_LoadIndexCnt(u8StreamIndex);
        if (u32StdIdxCnt == 0)
        {
            // this audio stream has no super index info
            break;
        }

        while (u32StdIdxCnt)
        {
            BOOL bAudioStreamIdxChunk = FALSE;

            msAPI_VDPlayer_DemuxAVI_LoadIndexInfo(u8StreamIndex, u32i++, &u64StdIdxOffset, &u32Size);
            if (u64StdIdxOffset > g_stDemuxer.stBitsContent.Container.stAVI.u64FileSize)
            {
                break;
            }

            msAPI_VDPlayer_DemuxAVI_ChangeFilePosition(u64StdIdxOffset,((u32Size&~0xFFF)+0x1000));

            msAPI_VDPlayer_BMFlushBytes(8);
            pstAviStdIndex->u16LongsPerEntry= (U16)msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(2);
            msAPI_VDPlayer_BMFlushBytes(2);
            pstAviStdIndex->u32EntriesInUse = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
            pstAviStdIndex->u32ChunkId      = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();

            // check if this index chunk for this audio stream
            u32ChunkId = pstAviStdIndex->u32ChunkId;
            if ((u8u32_2(u32ChunkId) == 'w') && (u8u32_3(u32ChunkId) == 'b'))
            {
                if ((isdigit(u8u32_0(u32ChunkId))) && (isdigit(u8u32_1(u32ChunkId))))
                {
                    u32ChunkId = ((u8u32_0(u32ChunkId) - '0') * 10) + (u8u32_1(u32ChunkId) - '0');
                    if (u32ChunkId == u8StreamIndex)
                    {
                        bAudioStreamIdxChunk = TRUE;
                    }
                }
            }

            if (bAudioStreamIdxChunk == FALSE)
            {
                u32StdIdxCnt--;
                msAPI_VDPlayer_BMFlushBytes(12);
                continue;
            }

            u32u64_0(pstAviStdIndex->u64BaseOffset) = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
            u32u64_1(pstAviStdIndex->u64BaseOffset) = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
            msAPI_VDPlayer_BMFlushBytes(4);

            u32Skip = pstAviStdIndex->u16LongsPerEntry * 4 - sizeof(pstAviStdIndex->stAIndex);
            u32AIdxCnt = pstAviStdIndex->u32EntriesInUse;

            while (u32AIdxCnt)
            {
                pstAviStdIndex->stAIndex.u32Offset = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
                pstAviStdIndex->stAIndex.u32Size = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();

                pstAviStdIndex->stAIndex.u32Size &= ~AVI_NOT_KEYFRAME;
                // if (!(pstAviStdIndex->stAIndex.u32Size & AVI_NOT_KEYFRAME))
                {
                    stDemuxAudioKeyIdx.u32Size = pstAviStdIndex->stAIndex.u32Size + 8;
                    stDemuxAudioKeyIdx.u64Offset = pstAviStdIndex->u64BaseOffset + pstAviStdIndex->stAIndex.u32Offset - 8;

                    // check if the file position of this audio key index is bigger than the target video key index
                    while (stDemuxAudioKeyIdx.u64Offset > stDemuxVideoKeyIdx.u64Offset)
                    {
                        if (((g_stDemuxer.stBitsContent.enAudioCodecID[u8AudioTrackIdx] & E_VDP_CODEC_ATTRIBUTE_MASK) != E_VDP_CODEC_AAC) ||
                            (g_stDemuxer.bEnableCalcByBitRate == TRUE))
                        {
                            stDemuxAudioKeyIdx.u32Pts =
                                    msAPI_VDPlayer_Demuxer_CalAudioBitTime(u8AudioTrackIdx, u32AccumulativeSize);
                        }
                        else
                        {
                            stDemuxAudioKeyIdx.u32Pts =
                                    msAPI_VDPlayer_Demuxer_CalAudioBitTime(u8AudioTrackIdx, u32Frmcnt);
                        }

#if ENABLE_AUDIO_HANDLER
                        if (g_stDemuxer.bEnableAudioHandler)
                        {
                            if (msAPI_VDPlayer_Demuxer_SaveAudioKeyIdx(u8AudioTrackIdx, (PST_VDP_DEMUX_AUDIO_KEYINDEX)&stDemuxAudioKeyIdx) == E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL)
                            {
                                 goto next_track;
                            }

                            break;
                        }
#endif

                        if(msAPI_VDPlayer_Demuxer_SaveAudioKeyInfo(u8AudioTrackIdx, stDemuxAudioKeyIdx.u32Pts) == FALSE)
                        {
                            return TRUE;
                        }

                        if (u32Cnt >= u32VideoKeyIndexCnt)
                        {
                            goto next_track;
                        }

                        // get next video key index
                        msAPI_VDPlayer_Demuxer_GetVideoKeyIdx(u32Cnt++, &stDemuxVideoKeyIdx);
                    }
                }
                /*
                else
                {
                    pstAviStdIndex->stAIndex.u32Size &= ~AVI_NOT_KEYFRAME;
                }
                */

                u32AccumulativeSize += msAPI_VDPlayer_Demuxer_CalAudioAlignedSize(u8AudioTrackIdx, pstAviStdIndex->stAIndex.u32Size);
                u32Frmcnt++;

                u32AIdxCnt--;
                if (u32Skip)
                {
                    msAPI_VDPlayer_BMFlushBytes(u32Skip);
                }
            }

            u32StdIdxCnt--;
        }

next_track:
        u8AudioTrackIdx++;
    }

    return TRUE;
}

static EN_AVI_DEMUX_RETURN msAPI_VDPlayer_DemuxAVI_ScanIndex_OpenDML(void)
{
    EN_AVI_DEMUX_RETURN eAviDemuxRet = E_AVI_DEMUX_ERR_INDEX;

    if (msAPI_VDPlayer_DemuxAVI_BuildOpenDmlIndex_Video())
    {
        eAviDemuxRet = E_AVI_DEMUX_SUCCESS;

        if ((g_stDemuxer.stBitsContent.u8Nb_VideoTracks) &&
            (g_stDemuxer.u8ThumbNailMode == FALSE))
        {
            // build indices for all audio
            eAviDemuxRet = (msAPI_VDPlayer_DemuxAVI_BuildOpenDmlIndex_Audios() ?
                    E_AVI_DEMUX_SUCCESS : E_AVI_DEMUX_ERR_INDEX);
        }
    }

    return eAviDemuxRet;
}

static __attribute__((noinline)) void msAPI_VDPlayer_DemuxAVI_ScanIndex_OldStyle_Pre(CalAudioBitTimeFuncPtr *pfCalAudioBitTimeFuncPtrTable,
    ST_DIV *pstCalAudioBitTimeDivTable,
    CalAudioAlignedSizeFuncPtr *pfCalAudioAlignedSizeFuncPtrTable,
    U8 *pu8StreamIndex_To_AudioTrackID_Table)
{
    UN_VDP_AUDIO_PARAM *punAudio;
    EN_VDP_CODECID enCodecID;
    U8 u8AudioTrackId;

    memset(pu8StreamIndex_To_AudioTrackID_Table, 0xff, 256);

    for (u8AudioTrackId = 0; u8AudioTrackId < MAX_AUDIO_TRACKS; u8AudioTrackId++) {
        pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_Default;
        pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = 0;
        pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = 0;
        pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = 0;
        pstCalAudioBitTimeDivTable[u8AudioTrackId].u32RunTime_q = 0;
        pstCalAudioBitTimeDivTable[u8AudioTrackId].u32RunTime_r = 0;
        pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Blockalign = 0;
        pfCalAudioAlignedSizeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioAlignedSize_Default;
    }
    for (u8AudioTrackId = 0; u8AudioTrackId < g_stDemuxer.stBitsContent.u8Nb_AudioTracks; u8AudioTrackId++) {
        pu8StreamIndex_To_AudioTrackID_Table[g_stDemuxer.u8AudioTrackIDMap[u8AudioTrackId]] = u8AudioTrackId;
        punAudio =  &g_stDemuxer.stBitsContent.unAudioParam[u8AudioTrackId];
        enCodecID = g_stDemuxer.stBitsContent.enAudioCodecID[u8AudioTrackId];
        switch(enCodecID & E_VDP_CODEC_ATTRIBUTE_MASK) {
        case E_VDP_CODEC_MPG_AUDIO:
            if ((punAudio->stMPEG.u32SampleSize == 0) && (punAudio->stMPEG.u32BlockAlign != 0))
            {
                pfCalAudioAlignedSizeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioAlignedSize_MPG_AUDIO;
            }
            if ((punAudio->stMPEG.u32SampleSize == 0) &&
                (punAudio->stMPEG.u32BlockAlign != 0) &&
                (punAudio->stMPEG.u32Rate != 0)) // VBR
            {
                pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_MPG_AUDIO1;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = (1000 * punAudio->stMPEG.u32Scale) / punAudio->stMPEG.u32Rate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = (1000 * punAudio->stMPEG.u32Scale) % punAudio->stMPEG.u32Rate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = punAudio->stMPEG.u32Rate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Blockalign = punAudio->stMPEG.u32BlockAlign;
            }
            else if ((punAudio->stMPEG.u32BitRate != 0) && (g_stDemuxer.bEnableCalcByBitRate == TRUE))
            {
                pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_MPG_AUDIO2;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = 8000 / punAudio->stMPEG.u32BitRate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = 8000 % punAudio->stMPEG.u32BitRate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = punAudio->stMPEG.u32BitRate;
            }
            else if (punAudio->stMPEG.u32Rate * punAudio->stMPEG.u32SampleSize != 0)
            {
                pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_MPG_AUDIO3;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = (1000 * punAudio->stMPEG.u32Scale) / (punAudio->stMPEG.u32Rate * punAudio->stMPEG.u32SampleSize);
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = (1000 * punAudio->stMPEG.u32Scale) % (punAudio->stMPEG.u32Rate * punAudio->stMPEG.u32SampleSize);
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = (punAudio->stMPEG.u32Rate * punAudio->stMPEG.u32SampleSize);
            }
            break;
        case E_VDP_CODEC_AAC:
            if ((g_stDemuxer.bEnableCalcByBitRate == TRUE) && (punAudio->stAAC.u32BitRate != 0))
            {
                if (g_stDemuxer.bEnableCalcByBitRate == TRUE) {
                    pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_AAC1_Accu;
                } else {
                    pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_AAC1;
                }
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = 8000 / punAudio->stAAC.u32BitRate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = 8000 % punAudio->stAAC.u32BitRate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = punAudio->stAAC.u32BitRate;
            }
            else if (punAudio->stAAC.u32SampleRate != 0)
            {
                if (g_stDemuxer.bEnableCalcByBitRate == TRUE) {
                    pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_AAC2_Accu;
                } else {
                    pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_AAC2;
                }
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = (AAC_SAMPLE_PER_FRAME * 1000) / punAudio->stAAC.u32SampleRate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = (AAC_SAMPLE_PER_FRAME * 1000) % punAudio->stAAC.u32SampleRate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = punAudio->stAAC.u32SampleRate;
            }
            else
            {
                // Nothing
            }
            break;
        case E_VDP_CODEC_AC3:
            if ((punAudio->stAC3.u16Frame_Size * punAudio->stAC3.u16Audio_Frame_TimeBase) != 0)
            {
                pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_AC3;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = punAudio->stAC3.u32Audio_Frame_Time / ((U32)punAudio->stAC3.u16Frame_Size * punAudio->stAC3.u16Audio_Frame_TimeBase);
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = punAudio->stAC3.u32Audio_Frame_Time % ((U32)punAudio->stAC3.u16Frame_Size * punAudio->stAC3.u16Audio_Frame_TimeBase);
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = ((U32)punAudio->stAC3.u16Frame_Size * punAudio->stAC3.u16Audio_Frame_TimeBase);
            }
            else
            {
                // Nothing
            }
            break;
        case E_VDP_CODEC_DTS:
            if ((punAudio->stDTS.u16Frame_Size * punAudio->stDTS.u16Audio_Frame_TimeBase) != 0)
            {
                pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_DTS;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = punAudio->stDTS.u32Audio_Frame_Time / ((U32)punAudio->stDTS.u16Frame_Size * (U32)punAudio->stDTS.u16Audio_Frame_TimeBase);
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = punAudio->stDTS.u32Audio_Frame_Time % ((U32)punAudio->stDTS.u16Frame_Size * (U32)punAudio->stDTS.u16Audio_Frame_TimeBase);
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = ((U32)punAudio->stDTS.u16Frame_Size * (U32)punAudio->stDTS.u16Audio_Frame_TimeBase);
            }
            else
            {
                // Nothing
            }
            break;
        case E_VDP_CODEC_PCM:
            if ((punAudio->stPCM.u32BitsPerSample * punAudio->stPCM.u32Channel * punAudio->stPCM.u32SampleRate) != 0)
            {
                pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_PCM;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = 8000 / (punAudio->stPCM.u32BitsPerSample * punAudio->stPCM.u32Channel * punAudio->stPCM.u32SampleRate);
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = 8000 % (punAudio->stPCM.u32BitsPerSample * punAudio->stPCM.u32Channel * punAudio->stPCM.u32SampleRate);
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = (punAudio->stPCM.u32BitsPerSample * punAudio->stPCM.u32Channel * punAudio->stPCM.u32SampleRate);
            }
            else
            {
                // Nothing
            }
            break;
        case E_VDP_CODEC_ADPCM:
            if ((punAudio->stADPCM.u32SampleRate * punAudio->stADPCM.u32BlockAlign) != 0)
            {
                pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_ADPCM;

                U32 u32Gcd = MApp_VDPlayer_GCD((1000 * punAudio->stADPCM.u32SamplesPerBlock), (punAudio->stADPCM.u32SampleRate * punAudio->stADPCM.u32BlockAlign));
                if(u32Gcd == 0)
                {
                    pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = (1000 * punAudio->stADPCM.u32SamplesPerBlock) / (punAudio->stADPCM.u32SampleRate * punAudio->stADPCM.u32BlockAlign);
                    pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = (1000 * punAudio->stADPCM.u32SamplesPerBlock) % (punAudio->stADPCM.u32SampleRate * punAudio->stADPCM.u32BlockAlign);
                    pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = (punAudio->stADPCM.u32SampleRate * punAudio->stADPCM.u32BlockAlign);
                }
                else
                {
                    U32 u32Dividend = (1000 * punAudio->stADPCM.u32SamplesPerBlock)/u32Gcd;
                    U32 u32Divisor = (punAudio->stADPCM.u32SampleRate * punAudio->stADPCM.u32BlockAlign)/u32Gcd;

                    pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = u32Dividend / u32Divisor;
                    pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = u32Dividend % u32Divisor;
                    pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = u32Divisor;
                }
            }
            else
            {
                // Nothing
            }
            break;
        case E_VDP_CODEC_WMA:
            if (punAudio->stWMA.u32BlockAlign != 0)
            {
                pfCalAudioAlignedSizeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioAlignedSize_WMA;
            }
            if (punAudio->stWMA.u32ByteRate != 0)
            {
                pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_WMA;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = 1000 / punAudio->stWMA.u32ByteRate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = 1000 % punAudio->stWMA.u32ByteRate;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = punAudio->stWMA.u32ByteRate;
            }
            else
            {
                // Nothing
            }
            break;
        case E_VDP_CODEC_AMR_NB:
        case E_VDP_CODEC_AMR_WB:
            if (punAudio->stAMR.u32BitsPerSec != 0)
            {
                pfCalAudioBitTimeFuncPtrTable[u8AudioTrackId] = msAPI_VDPlayer_Demuxer_CalAudioBitTime_AMR_NB;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_q = 20 / punAudio->stAMR.u32BitsPerSec;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Precal_r = 20 % punAudio->stAMR.u32BitsPerSec;
                pstCalAudioBitTimeDivTable[u8AudioTrackId].u32Divider = punAudio->stAMR.u32BitsPerSec;
            }
            else
            {
                // Nothing
            }
            break;
        default:
            break;
        }
    }
}

static __attribute__((noinline)) EN_AVI_DEMUX_RETURN msAPI_VDPlayer_DemuxAVI_ScanIndex_OldStyle(void)
{
    BOOLEAN bIndexFound = FALSE;
    BOOLEAN bNeedBuildAudioKey = TRUE;
    U8 u8StreamIndex, u8AudioTrackId;
    U32 u32PadOffset, u32Loop, u32ChunkId, au32AudioKeyIdxCnt[MAX_AUDIO_TRACKS];
    U32 u32VideoFrmCnt,u32Timeout;
    U32 au32AudioFrmCnt[MAX_AUDIO_TRACKS], au32AudioTrackAccumulativeDataSize[MAX_AUDIO_TRACKS];
    U32 u32AddedAudioFrmCnt[MAX_AUDIO_TRACKS];
    U32 u32VideoKeyIdxCnt;
    U64 u64Offset;
    ST_AVI_OLD_INDEX stAviOldIndex;
    ST_AVI_OLD_INDEX *pstAviOldIndex = &stAviOldIndex;
    ST_VDP_DEMUX_KEYINDEX stDemuxVideoKeyIdx;
#if ENABLE_AUDIO_HANDLER
    ST_VDP_DEMUX_AUDIO_KEYINDEX stAudioKeyIdx;
#endif
    EN_VDP_DEMUX_INDEXTAB_RET eRet;
    U32 u32AudioPts;
    UN_VDP_AUDIO_PARAM *punAudio;
    CalAudioBitTimeFuncPtr apfCalAudioBitTimeFuncPtrTable[MAX_AUDIO_TRACKS];
    ST_DIV astCalAudioBitTimeDivTable[MAX_AUDIO_TRACKS];
    ST_DIV *stDiv;
    CalAudioAlignedSizeFuncPtr apfCalAudioAlignedSizeFuncPtrTable[MAX_AUDIO_TRACKS];
    U8 au8StreamIndex_To_AudioTrackID_Table[256];
    CalAudioBitTimeFuncPtr pfAudioBitTimeFPTR;
    CalAudioAlignedSizeFuncPtr pfAudioAlignedSizeFPTR;

    u32VideoKeyIdxCnt = 0;
    memset(&stAviOldIndex, 0, sizeof(ST_AVI_OLD_INDEX));

    // seek to 1st movi end
    msAPI_VDPlayer_DemuxAVI_ChangeFilePosition(g_stDemuxer.stBitsContent.Container.stAVI.u32FirstMoviEndPos,AVI_PRELOAD_SIZE);

    pstAviOldIndex->stRiffChunkGeneral.u32Fcc = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);

    // find 'idx1' tag
    u32Timeout = MsOS_GetSystemTime() + TIMEOUT_TIMER_2000MS;
    while (1)
    {
        // check size boundary
        if ((msAPI_VDPlayer_BMFileEOF() == TRUE)
                || (msAPI_VDPlayer_BMFileTell() >= g_stDemuxer.stBitsContent.Container.stAVI.u32FirstRiffEndPos)
                || (MsOS_GetSystemTime() >u32Timeout))
        {
            break;
        }

        if(pstAviOldIndex->stRiffChunkGeneral.u32Fcc == MKTAG('J', 'U', 'N', 'K'))
        {
            // flush this chunk
            pstAviOldIndex->stRiffChunkGeneral.u32Size = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);
            pstAviOldIndex->stRiffChunkGeneral.u32Size = EVEN_ALIGN(pstAviOldIndex->stRiffChunkGeneral.u32Size);
            msAPI_VDPlayer_BMFlushBytes(pstAviOldIndex->stRiffChunkGeneral.u32Size);

            // get next chunk
            pstAviOldIndex->stRiffChunkGeneral.u32Fcc = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);
        }
        else if (pstAviOldIndex->stRiffChunkGeneral.u32Fcc == MKTAG('i', 'd', 'x', '1'))
        {
            // old sytle index found
            bIndexFound = TRUE;
            pstAviOldIndex->stRiffChunkGeneral.u32Size = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);
            pstAviOldIndex->stRiffChunkGeneral.u32Size = EVEN_ALIGN(pstAviOldIndex->stRiffChunkGeneral.u32Size);
            break;
        }
        else
        {
            pstAviOldIndex->stRiffChunkGeneral.u32Fcc =
                    (pstAviOldIndex->stRiffChunkGeneral.u32Fcc << 8) | msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(1);
        }
    }

    if (!bIndexFound)
    {
        return E_AVI_DEMUX_ERR_INDEX;
    }

    memset(&stDemuxVideoKeyIdx, 0, sizeof(stDemuxVideoKeyIdx));
    memset(au32AudioKeyIdxCnt, 0, sizeof(au32AudioKeyIdxCnt));
    memset(au32AudioTrackAccumulativeDataSize, 0, sizeof(au32AudioTrackAccumulativeDataSize));

    u32VideoFrmCnt = 0;
    memset(au32AudioFrmCnt, 0, sizeof(au32AudioFrmCnt));
    u8StreamIndex = U8_MAX; //it means it is not video or audio stream
    u32PadOffset = U32_MAX;
    u32Loop = pstAviOldIndex->stRiffChunkGeneral.u32Size / sizeof(pstAviOldIndex->stAIndex);

    memset(u32AddedAudioFrmCnt, 0, sizeof(u32AddedAudioFrmCnt));

    if (pstAviOldIndex->stRiffChunkGeneral.u32Size > 0x400000)
    {
        msAPI_VDPlayer_BM_SetPreloadSize(U32_MAX);
    }
    else
    {
        msAPI_VDPlayer_BM_SetPreloadSize(pstAviOldIndex->stRiffChunkGeneral.u32Size);
    }

    msAPI_VDPlayer_DemuxAVI_ScanIndex_OldStyle_Pre(apfCalAudioBitTimeFuncPtrTable,
        astCalAudioBitTimeDivTable,
        apfCalAudioAlignedSizeFuncPtrTable,
        au8StreamIndex_To_AudioTrackID_Table);

    while (u32Loop)
    {
        u32Loop--;
        if(msAPI_VDPlayer_BMFileEOF() == TRUE)
        {
            break;
        }

        if(FALSE==msAPI_VDPlayer_BMRead16Bytes_LE_AutoLoad(
                    &pstAviOldIndex->stAIndex.u32ChunkId,
                    &pstAviOldIndex->stAIndex.u32Flags,
                    &pstAviOldIndex->stAIndex.u32Offset,
                    &pstAviOldIndex->stAIndex.u32Size))
        {
            return E_AVI_DEMUX_ERR_INDEX;
        }

        if (u32PadOffset == U32_MAX)
        {
            u32PadOffset = 0;
            if (g_stDemuxer.stBitsContent.Container.stAVI.u32FirstMoviStartPos > pstAviOldIndex->stAIndex.u32Offset)
            {
                u32PadOffset = g_stDemuxer.stBitsContent.Container.stAVI.u32FirstMoviStartPos;
            }
        }

        u32ChunkId = pstAviOldIndex->stAIndex.u32ChunkId;
        if (((u8u32_2(u32ChunkId) == 'd') && ((u8u32_3(u32ChunkId) == 'c') || (u8u32_3(u32ChunkId) == 'b')))
                || ((u8u32_2(u32ChunkId) == 'w') && (u8u32_3(u32ChunkId) == 'b')))
        {
            u8StreamIndex = ((u8u32_0(u32ChunkId) - '0') * 10) + (u8u32_1(u32ChunkId) - '0');
        }
        else
        {
            u8StreamIndex = INVALID_STREAM_ID;
            continue;
        }

        if (u8StreamIndex == g_stDemuxer.stBitsContent.s8Video_StreamId)
        {
            if (pstAviOldIndex->stAIndex.u32Flags & AVIIF_KEYFRAME)
            {
                stDemuxVideoKeyIdx.u64Offset = pstAviOldIndex->stAIndex.u32Offset;
                stDemuxVideoKeyIdx.u64Offset += u32PadOffset;
                stDemuxVideoKeyIdx.u32Size = pstAviOldIndex->stAIndex.u32Size + 8;
                stDemuxVideoKeyIdx.u32Pts = msAPI_VDPlayer_Demuxer_CalVideoFrameTime(u32VideoFrmCnt);

                eRet = msAPI_VDPlayer_Demuxer_SaveVideoKeyIdx(&stDemuxVideoKeyIdx);
                if (eRet == E_VDP_DEMUX_BUD_INDEX_TAB_RET_SUCCESS)
                {
                    u32VideoKeyIdxCnt++;
                }
                else if (eRet == E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL)
                {
                    printf("E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL\n");
                    break;
                }
                if (g_stDemuxer.u8ThumbNailMode && (stDemuxVideoKeyIdx.u32Pts > THUMBNAIL_JUMPTIME))
                {
                    if ((_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_PREVIEW_MODE) & E_VDP_PREVIEW_INFO_INDEXTABLE) == FALSE)
                    {
                        break;
                    }
                }
            }

            u32VideoFrmCnt++;
        }
        else
        {
            u8AudioTrackId = au8StreamIndex_To_AudioTrackID_Table[u8StreamIndex];

            if (u8AudioTrackId < g_stDemuxer.stBitsContent.u8Nb_AudioTracks && bNeedBuildAudioKey)
            {
               U32 u32AudioFrmCnt_v = u32AddedAudioFrmCnt[u8AudioTrackId];
               U32 u32AudioTrackAccumulativeDataSize_v = au32AudioTrackAccumulativeDataSize[u8AudioTrackId];
               pfAudioBitTimeFPTR = apfCalAudioBitTimeFuncPtrTable[u8AudioTrackId];
               pfAudioAlignedSizeFPTR = apfCalAudioAlignedSizeFuncPtrTable[u8AudioTrackId];
               stDiv = &astCalAudioBitTimeDivTable[u8AudioTrackId];
               punAudio = &g_stDemuxer.stBitsContent.unAudioParam[u8AudioTrackId];

#if ENABLE_AUDIO_HANDLER
                if (g_stDemuxer.bEnableAudioHandler == TRUE)
                {
                    stAudioKeyIdx.u64Offset = pstAviOldIndex->stAIndex.u32Offset;
                    stAudioKeyIdx.u64Offset += u32PadOffset;
                    stAudioKeyIdx.u32Size = pstAviOldIndex->stAIndex.u32Size;
                    stAudioKeyIdx.u32Frm_Info_Idx = au32AudioFrmCnt[u8AudioTrackId];
                    stAudioKeyIdx.u32Pts = pfAudioBitTimeFPTR(stDiv, u32AudioFrmCnt_v, u32AudioTrackAccumulativeDataSize_v);
                    au32AudioTrackAccumulativeDataSize[u8AudioTrackId] = 0;
                    u32AddedAudioFrmCnt[u8AudioTrackId] = 0;

                    if (msAPI_VDPlayer_Demuxer_SaveAudioKeyIdx(u8AudioTrackId, (PST_VDP_DEMUX_AUDIO_KEYINDEX)&stAudioKeyIdx) == E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL)
                    {
                         ;
                    }
                }
                else
#endif  // #if ENABLE_AUDIO_HANDLER
                {
                    if (au32AudioKeyIdxCnt[u8AudioTrackId] < u32VideoKeyIdxCnt)
                    {
                        msAPI_VDPlayer_Demuxer_GetVideoKeyIdx(au32AudioKeyIdxCnt[u8AudioTrackId]++, &stDemuxVideoKeyIdx);

                        u64Offset = pstAviOldIndex->stAIndex.u32Offset;
                        u64Offset += u32PadOffset;
                        u32AudioPts = pfAudioBitTimeFPTR(stDiv, u32AudioFrmCnt_v, u32AudioTrackAccumulativeDataSize_v);
                        au32AudioTrackAccumulativeDataSize[u8AudioTrackId] = 0;
                        u32AddedAudioFrmCnt[u8AudioTrackId] = 0;

                        while (u64Offset > stDemuxVideoKeyIdx.u64Offset)
                        {
                            if (msAPI_VDPlayer_Demuxer_SaveAudioKeyInfo(u8AudioTrackId, u32AudioPts) == FALSE)
                            {
                                bNeedBuildAudioKey = FALSE;
                                break;
                            }

                            if (au32AudioKeyIdxCnt[u8AudioTrackId] >= u32VideoKeyIdxCnt)
                            {
                                break;
                            }

                            // get next video key index
                            msAPI_VDPlayer_Demuxer_GetVideoKeyIdx(au32AudioKeyIdxCnt[u8AudioTrackId]++, &stDemuxVideoKeyIdx);
                        }
                    }
                }

                au32AudioTrackAccumulativeDataSize[u8AudioTrackId] += pfAudioAlignedSizeFPTR(punAudio, pstAviOldIndex->stAIndex.u32Size);
                u32AddedAudioFrmCnt[u8AudioTrackId]++;
                au32AudioFrmCnt[u8AudioTrackId]++;
            }
        }
    }
    return E_AVI_DEMUX_SUCCESS;
}

BOOL MApp_VDPlayer_AVIScanIndex(U8 u8FileHdl)
{
    ST_HK_AVI_SCAN stHK_AVI_SCAN;
    U32 u32VAaddr;

    memset(&g_stDemuxer, 0, sizeof(ST_VDP_DEMUX_GLOBAL));

    msAPI_VDPlayer_GetShareMemoryDataAVIScan(&stHK_AVI_SCAN);
    // Assign Variables
    g_stDemuxer.u8ThumbNailMode = stHK_AVI_SCAN.u8ThumbNailMode;
    g_stDemuxer.stBitsContent.Container.stAVI.u64FileSize = stHK_AVI_SCAN.u64FileSize;
    g_stDemuxer.stBitsContent.Container.stAVI.u32FirstMoviStartPos = stHK_AVI_SCAN.u32FirstMoviStartPos;
    g_stDemuxer.stBitsContent.Container.stAVI.u32FirstMoviEndPos = stHK_AVI_SCAN.u32FirstMoviEndPos;
    g_stDemuxer.stBitsContent.Container.stAVI.u32FirstRiffEndPos = stHK_AVI_SCAN.u32FirstRiffEndPos;
    g_stDemuxer.stBitsContent.Container.stAVI.pstOpenDmlIdxHeaderInfo = (ST_OPEN_DML_IDX_HEADER_INFO *)_PA2VA((U32)stHK_AVI_SCAN.pstOpenDmlIdxHeaderInfo);
    g_stDemuxer.stDataBuffer.u32IndexBuffAddr = _PA2VA(stHK_AVI_SCAN.u32IndexBuffAddr);
    g_stDemuxer.stDataBuffer.u32IndexBuffSize = stHK_AVI_SCAN.u32IndexBuffSize;
    g_stDemuxer.u8KeyIdxSize = stHK_AVI_SCAN.u8KeyIdxSize;
    g_stDemuxer.u32KeyIdxPeriod = stHK_AVI_SCAN.u32KeyIdxPeriod;
    g_stDemuxer.stBitsContent.s8Video_StreamId = stHK_AVI_SCAN.s8Video_StreamId;
    g_stDemuxer.stBitsContent.s8Audio_StreamId = stHK_AVI_SCAN.s8Audio_StreamId;
    g_stDemuxer.stBitsContent.u8Nb_VideoTracks = stHK_AVI_SCAN.u8Nb_VideoTracks;
    g_stDemuxer.stBitsContent.u8Nb_AudioTracks = stHK_AVI_SCAN.u8Nb_AudioTracks;
    g_stDemuxer.stBitsContent.Container.stAVI.VideoTracks[0].u32FrameRate = stHK_AVI_SCAN.u32FrameRate;
    g_stDemuxer.stBitsContent.Container.stAVI.VideoTracks[0].u32FrameRateBase = stHK_AVI_SCAN.u32FrameRateBase;
    if (stHK_AVI_SCAN.bEnableCalcByBitRate == TRUE)
    {
        g_stDemuxer.bEnableCalcByBitRate = TRUE;
    }
    else
    {
        g_stDemuxer.bEnableCalcByBitRate = FALSE;
    }
    g_stDemuxer.bEnableAudioHandler = FALSE;
#if ENABLE_AUDIO_HANDLER
    if (stHK_AVI_SCAN.bEnableAudioHandler == TRUE)
    {
        U32 i;
        g_stDemuxer.bEnableAudioHandler = TRUE;

        for (i = 0; i < MAX_AUDIO_TRACKS; i++)
        {
            g_stDemuxer.u32AudioKeyBufAddr[i] = _PA2VA(stHK_AVI_SCAN.u32AudioKeyBufAddr[i]);
            g_stDemuxer.u32AudioKeyBufSize[i] = stHK_AVI_SCAN.u32AudioKeyBufSize[i];
        }
        g_stDemuxer.u32AudioKeyIdxPeriod = stHK_AVI_SCAN.u32AudioKeyIdxPeriod;
        g_stDemuxer.u8AudioKeyIdxSize = stHK_AVI_SCAN.u8AudioKeyIdxSize;
    }
#endif // #if ENABLE_AUDIO_HANDLER

    memcpy(g_stDemuxer.stBitsContent.enAudioCodecID, stHK_AVI_SCAN.enAudioCodecID, MAX_AUDIO_TRACKS * sizeof(EN_VDP_CODECID));
    memcpy(g_stDemuxer.u8AudioTrackIDMap, stHK_AVI_SCAN.u8AudioTrackIDMap, MAX_AUDIO_TRACKS * sizeof(U8));
    memcpy(g_stDemuxer.stBitsContent.unAudioParam, stHK_AVI_SCAN.unAudioParam, MAX_AUDIO_TRACKS * sizeof(UN_VDP_AUDIO_PARAM));
    msAPI_VDPlayer_BMInit(u8FileHdl, g_stDemuxer.stBitsContent.Container.stAVI.u64FileSize);
#if 0
    u32VAaddr = _PA2VA(stHK_AVI_SCAN.u32BitstreamAddr);
#else
    u32VAaddr = MS_PA2KSEG0(stHK_AVI_SCAN.u32BitstreamAddr);
#endif
    msAPI_VDPlayer_BMBuffer_Configuration(u32VAaddr, stHK_AVI_SCAN.u32BitstreamSize);

    if ((msAPI_VDPlayer_DemuxAVI_ScanIndex_OpenDML() != E_AVI_DEMUX_SUCCESS)
            && (msAPI_VDPlayer_DemuxAVI_ScanIndex_OldStyle() != E_AVI_DEMUX_SUCCESS))
    {
        return FALSE;
    }

    // Assign Variables to Coprocessor
    stHK_AVI_SCAN.u32Video_IdxSize = g_stDemuxer.u32Video_IdxSize;
    stHK_AVI_SCAN.u32FirstVideoKeyFramePTS = g_stDemuxer.u32FirstVideoKeyFramePTS;
    stHK_AVI_SCAN.u32lastVideoKeyFramePTS = g_stDemuxer.u32lastVideoKeyFramePTS;
    memcpy(stHK_AVI_SCAN.u32Audio_IdxSize, g_stDemuxer.u32Audio_IdxSize, MAX_AUDIO_TRACKS * sizeof(U32));
    msAPI_VDPlayer_SetShareMemoryDataAVIScan(&stHK_AVI_SCAN);

    MsOS_Dcache_Flush(_PA2VA(stHK_AVI_SCAN.u32BitstreamAddr), stHK_AVI_SCAN.u32BitstreamSize);
    MsOS_FlushMemory();

    return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#else //ENABLE_HK_AVI_PERFORMANCE_IMPROVE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void msAPI_VDPlayer_GetShareMemoryDataAVIScan(PST_HK_AVI_SCAN pstInfo)
{
    U32 u32Address;
    u32Address = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HK_AVI_SCAN);
    u32Address = _PA2VA(u32Address);
    memcpy((void *)pstInfo, (void *)u32Address, sizeof(ST_HK_AVI_SCAN));
}

void msAPI_VDPlayer_SetShareMemoryDataAVIScan(PST_HK_AVI_SCAN pstInfo)
{
    U32 u32Address;
    u32Address = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HK_AVI_SCAN);
    u32Address = _PA2VA(u32Address);
    memcpy((void *)u32Address, (void *)pstInfo, sizeof(ST_HK_AVI_SCAN));
    MsOS_FlushMemory();
}

EN_VDP_DEMUX_INDEXTAB_RET msAPI_VDPlayer_Demuxer_SaveAudioKeyIdx(U8 u8Track, ST_VDP_DEMUX_AUDIO_KEYINDEX *pstKeyIdx)
{
    U32 *pu32KeyIdx, *pu32PreKeyIdx;
    U32 *pu32EndAddr;

    pu32KeyIdx = (U32 *)(g_stDemuxer.u32AudioKeyBufAddr[u8Track] + g_stDemuxer.u32Audio_IdxSize[u8Track]);
    pu32EndAddr = (U32 *)(g_stDemuxer.u32AudioKeyBufAddr[u8Track] + g_stDemuxer.u32AudioKeyBufSize[u8Track] - g_stDemuxer.u8AudioKeyIdxSize);

    if (g_stDemuxer.u32Audio_IdxSize[u8Track] == 0)
    {
        pu32PreKeyIdx = NULL;
    }
    else
    {
        pu32PreKeyIdx = (U32 *)(g_stDemuxer.u32AudioKeyBufAddr[u8Track] + g_stDemuxer.u32Audio_IdxSize[u8Track] - g_stDemuxer.u8AudioKeyIdxSize);
    }

    if (pu32KeyIdx <= pu32EndAddr)
    {
        if (pu32PreKeyIdx != NULL)
        {
            if (pstKeyIdx->u32Pts - pu32PreKeyIdx[1] < g_stDemuxer.u32AudioKeyIdxPeriod)
            {
                return E_VDP_DEMUX_BUD_INDEX_TAB_RET_FAILED;
            }
        }

        pu32KeyIdx[0] = u32u64_0(pstKeyIdx->u64Offset);
        pu32KeyIdx[1] = pstKeyIdx->u32Pts;
        pu32KeyIdx[2] = (pstKeyIdx->u32Size & 0xFFFFFF) | (u32u64_1(pstKeyIdx->u64Offset) << 24);
        pu32KeyIdx[3] = pstKeyIdx->u32Frm_Info_Idx;

        g_stDemuxer.u32Audio_IdxSize[u8Track] += g_stDemuxer.u8AudioKeyIdxSize;
    }
    else
    {
        return E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL;
    }

    return E_VDP_DEMUX_BUD_INDEX_TAB_RET_SUCCESS;
}

BOOL msAPI_VDPlayer_Demuxer_SaveAudioKeyInfo(U8 u8Track_Id, U32 u32Pts)
{
    U32 *pu32KeyIdx;
    U32 *pu32EndAddr;

    pu32KeyIdx = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.u32Audio_IdxSize[u8Track_Id]);
    pu32EndAddr = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.stDataBuffer.u32IndexBuffSize - g_stDemuxer.u8KeyIdxSize);

    if (pu32KeyIdx <= pu32EndAddr)
    {
        pu32KeyIdx[4 + u8Track_Id] = u32Pts;

        g_stDemuxer.u32Audio_IdxSize[u8Track_Id] += g_stDemuxer.u8KeyIdxSize;
    }
    else
    {
        return FALSE;
    }
    return TRUE;
}

void msAPI_VDPlayer_Demuxer_GetVideoKeyIdx(U32 u32KeyIdxNum, ST_VDP_DEMUX_KEYINDEX *pstKeyIdx)
{
    U32 *pu32KeyIdx;
    U32 *pu32EndAddr;

    pu32KeyIdx = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + u32KeyIdxNum * g_stDemuxer.u8KeyIdxSize);
    pu32EndAddr = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.stDataBuffer.u32IndexBuffSize - g_stDemuxer.u8KeyIdxSize);

    if ((pu32KeyIdx <= pu32EndAddr) && (pstKeyIdx))
    {
        pstKeyIdx->u64Offset= (((U64)pu32KeyIdx[2] & ~0xFFFFFF) << 8) + pu32KeyIdx[0];
        pstKeyIdx->u32Pts   = pu32KeyIdx[1];
        pstKeyIdx->u32Size  = pu32KeyIdx[2] & 0xFFFFFF;
        pstKeyIdx->u32Frm_Info_Idx = pu32KeyIdx[3];
    }

    return ;
}

EN_VDP_DEMUX_INDEXTAB_RET msAPI_VDPlayer_Demuxer_SaveVideoKeyIdx(ST_VDP_DEMUX_KEYINDEX *pstKeyIdx)
{
    U32 *pu32KeyIdx, *pu32PreKeyIdx;
    U32 *pu32EndAddr;
    U64 u64PreOffset;

    pu32KeyIdx = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.u32Video_IdxSize);
    pu32EndAddr = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.stDataBuffer.u32IndexBuffSize - g_stDemuxer.u8KeyIdxSize);

    if (g_stDemuxer.u32Video_IdxSize == 0)
    {
        pu32PreKeyIdx = NULL;
        u64PreOffset = 0;
    }
    else
    {
        pu32PreKeyIdx = (U32 *)(g_stDemuxer.stDataBuffer.u32IndexBuffAddr + g_stDemuxer.u32Video_IdxSize - g_stDemuxer.u8KeyIdxSize);
        u64PreOffset = ((((U64)pu32PreKeyIdx[2] & ~0xFFFFFF) << 8) + pu32PreKeyIdx[0]);
    }

    if (pu32KeyIdx <= pu32EndAddr)
    {
        if (pu32PreKeyIdx != NULL)
        {
            if ((pstKeyIdx->u32Pts - pu32PreKeyIdx[1] < g_stDemuxer.u32KeyIdxPeriod) ||
                (pstKeyIdx->u64Offset <= u64PreOffset))
        {
            return E_VDP_DEMUX_BUD_INDEX_TAB_RET_FAILED;
        }
        }

        pu32KeyIdx[0] = u32u64_0(pstKeyIdx->u64Offset);
        pu32KeyIdx[1] = pstKeyIdx->u32Pts;
        pu32KeyIdx[2] = (pstKeyIdx->u32Size & 0xFFFFFF) | (u32u64_1(pstKeyIdx->u64Offset) << 24);
        pu32KeyIdx[3] = pstKeyIdx->u32Frm_Info_Idx;

        if(g_stDemuxer.u32Video_IdxSize == 0)
        {
            g_stDemuxer.u32FirstVideoKeyFramePTS = pstKeyIdx->u32Pts;
        }
        g_stDemuxer.u32Video_IdxSize += g_stDemuxer.u8KeyIdxSize;
        g_stDemuxer.u32lastVideoKeyFramePTS = pstKeyIdx->u32Pts;
    }
    else
    {
        return E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL;
    }

    return E_VDP_DEMUX_BUD_INDEX_TAB_RET_SUCCESS;
}

U32 msAPI_VDPlayer_Demuxer_CalVideoFrameTime(U32 u32FrmIdx)
{
    U32 u32FrameRate;
    U32 u32FrameRateBase;
    U32 u32Ms;

    u32FrameRate = g_stDemuxer.stBitsContent.Container.stAVI.VideoTracks[0].u32FrameRate;
    u32FrameRateBase = g_stDemuxer.stBitsContent.Container.stAVI.VideoTracks[0].u32FrameRateBase;

    if ((u32FrameRateBase == 0) ||
        (u32FrameRate == 1 && u32FrameRateBase == 1))
    {
//        MFP_ERR(printf("No FrameRate information\n"));
        u32FrameRateBase = 41708;
        u32FrameRate = 1000000;
    }

    u32Ms = (U32)(((U64)u32FrmIdx * (U64)u32FrameRateBase * (U64)1000) / u32FrameRate);

    return u32Ms;
}

U32 msAPI_VDPlayer_Demuxer_CalAudioAlignedSize(U8 u8Track_Id, U32 u32Pkt_Size)
{
    UN_VDP_AUDIO_PARAM *punAudio;
    EN_VDP_CODECID enCodecID;
    U32 u32AlignedPktSize;

    u32AlignedPktSize = u32Pkt_Size;
    enCodecID = g_stDemuxer.stBitsContent.enAudioCodecID[u8Track_Id];
    punAudio = &g_stDemuxer.stBitsContent.unAudioParam[u8Track_Id];
    switch(enCodecID & E_VDP_CODEC_ATTRIBUTE_MASK)
    {
        case E_VDP_CODEC_MPG_AUDIO:
            if ((punAudio->stMPEG.u32SampleSize == 0) && (punAudio->stMPEG.u32BlockAlign != 0))
            {
                u32AlignedPktSize = ((u32Pkt_Size + punAudio->stMPEG.u32BlockAlign) - 1) / punAudio->stMPEG.u32BlockAlign;
                u32AlignedPktSize *= punAudio->stMPEG.u32BlockAlign;
            }
            break;

        case E_VDP_CODEC_WMA:
            if (punAudio->stWMA.u32BlockAlign != 0)
            {
                u32AlignedPktSize = (u32Pkt_Size + punAudio->stWMA.u32BlockAlign - 1) / punAudio->stWMA.u32BlockAlign;
                u32AlignedPktSize *= punAudio->stWMA.u32BlockAlign;
            }
            break;

        default:
            break;
    }

    return u32AlignedPktSize;
}

U32 msAPI_VDPlayer_Demuxer_CalAudioBitTime(U8 u8Track_Id, U32 u32Pkt_Size)
{
    UN_VDP_AUDIO_PARAM *punAudio;
    EN_VDP_CODECID enCodecID;
    U32 u32Ms;

    u32Ms = 0;
    enCodecID = g_stDemuxer.stBitsContent.enAudioCodecID[u8Track_Id];
    punAudio = &g_stDemuxer.stBitsContent.unAudioParam[u8Track_Id];
    switch(enCodecID & E_VDP_CODEC_ATTRIBUTE_MASK)
    {
        case E_VDP_CODEC_MPG_AUDIO:
            if ((punAudio->stMPEG.u32SampleSize == 0) &&
                (punAudio->stMPEG.u32BlockAlign != 0) &&
                (punAudio->stMPEG.u32Rate != 0)) // VBR
            {
                u32Ms = ((u32Pkt_Size + punAudio->stMPEG.u32BlockAlign) - 1) / punAudio->stMPEG.u32BlockAlign;
                u32Ms = (U32)(((U64)u32Ms * 1000 * punAudio->stMPEG.u32Scale) / punAudio->stMPEG.u32Rate);
            }
            else if ((punAudio->stMPEG.u32BitRate != 0) && (g_stDemuxer.bEnableCalcByBitRate == TRUE))
            {
                u32Ms = (U32)(((U64)u32Pkt_Size * 8 * 1000) / punAudio->stMPEG.u32BitRate);
            }
            else
            {
                u32Ms = (U32)(((U64)u32Pkt_Size * 1000 * punAudio->stMPEG.u32Scale) /
                    ((U64)punAudio->stMPEG.u32Rate * punAudio->stMPEG.u32SampleSize));
            }
            break;

        case E_VDP_CODEC_AAC:
            if ((g_stDemuxer.bEnableCalcByBitRate == TRUE) && (punAudio->stAAC.u32BitRate != 0))
            {
                u32Ms = (U32)(((U64)u32Pkt_Size * 8 * 1000) / punAudio->stAAC.u32BitRate);
            }
            else if (punAudio->stAAC.u32SampleRate != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * AAC_SAMPLE_PER_FRAME * 1000) / punAudio->stAAC.u32SampleRate);
            }
            break;

        case E_VDP_CODEC_AC3:
            if ((punAudio->stAC3.u16Frame_Size * punAudio->stAC3.u16Audio_Frame_TimeBase) != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * (U64)punAudio->stAC3.u32Audio_Frame_Time) / ((U32)punAudio->stAC3.u16Frame_Size * (U32)punAudio->stAC3.u16Audio_Frame_TimeBase));
            }
            break;

        case E_VDP_CODEC_DTS:
            if ((punAudio->stDTS.u16Frame_Size * punAudio->stDTS.u16Audio_Frame_TimeBase) != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * (U64)punAudio->stDTS.u32Audio_Frame_Time) / ((U32)punAudio->stDTS.u16Frame_Size * (U32)punAudio->stDTS.u16Audio_Frame_TimeBase));
            }
            break;

        case E_VDP_CODEC_PCM:
            if ((punAudio->stPCM.u32BitsPerSample * punAudio->stPCM.u32Channel * punAudio->stPCM.u32SampleRate) != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * 1000 * 8) /
                ((U64)punAudio->stPCM.u32BitsPerSample * punAudio->stPCM.u32Channel * punAudio->stPCM.u32SampleRate));
            }
            break;

        case E_VDP_CODEC_ADPCM:
            if ((punAudio->stADPCM.u32SampleRate * punAudio->stADPCM.u32BlockAlign) != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * 1000 * punAudio->stADPCM.u32SamplesPerBlock) /
                ((U64)punAudio->stADPCM.u32SampleRate * punAudio->stADPCM.u32BlockAlign));
            }
            break;
        case E_VDP_CODEC_WMA:
            if (punAudio->stWMA.u32ByteRate != 0)
            {
            u32Ms = (U32)(((U64)u32Pkt_Size * 1000) / punAudio->stWMA.u32ByteRate);
            }
            break;

        case E_VDP_CODEC_AMR_NB:
        case E_VDP_CODEC_AMR_WB:
            if (punAudio->stAMR.u32BitsPerSec!= 0)
            {
                //one frame 20ms
                u32Ms = (u32Pkt_Size*20)/punAudio->stAMR.u32BitsPerSec;
            }
            break;

        default:
            break;
    }

    return u32Ms;
}

static void msAPI_VDPlayer_DemuxAVI_ChangeFilePosition(U64 u64NewPosition ,U32 u32readsize)
{
    U64 u64CurrFilePosition = msAPI_VDPlayer_BMFileTell();

    if (u64CurrFilePosition == u64NewPosition)
    {
        // do nothing
    }
    else
    {
        if ((u64NewPosition > u64CurrFilePosition)
                && ((u64NewPosition - u64CurrFilePosition) < (U64)msAPI_VDPlayer_BMBuffer_Remainder()))
        {
            // if there is enough data in BM, do data flushing
            msAPI_VDPlayer_BMFlushBytes((U32)(u64NewPosition - u64CurrFilePosition));
        }
        else
        {
            // no enough data in BM, do file seeking
            msAPI_VDPlayer_BMFileSeek(u64NewPosition, E_BM_FILEPOS_SEEK_SET);
            msAPI_VDPlayer_BMFillBuffer_Custom(u32readsize);
        }
    }
}

static inline U32 msAPI_VDPlayer_DemuxAVI_LoadIndexCnt(U32 u32Stream)
{
    ST_OPEN_DML_IDX_HEADER_INFO *pstOpenDmlIdxHeaderInfo = g_stDemuxer.stBitsContent.Container.stAVI.pstOpenDmlIdxHeaderInfo + u32Stream;

    return pstOpenDmlIdxHeaderInfo->u32Cnt;
}

static inline void msAPI_VDPlayer_DemuxAVI_LoadIndexInfo(U32 u32Stream, U32 u32Cnt, U64 *u64IdxOffset, U32 *u32Size)
{
    ST_OPEN_DML_IDX_HEADER_INFO *pstOpenDmlIdxHeaderInfo = g_stDemuxer.stBitsContent.Container.stAVI.pstOpenDmlIdxHeaderInfo + u32Stream;
    ST_OPEN_DML_IDX_INFO *pstOpenDmlIdxInfo = ((ST_OPEN_DML_IDX_INFO *)_PA2VA((U32)pstOpenDmlIdxHeaderInfo->pstOpenDmlIdxInfo)) + u32Cnt;

    *u64IdxOffset = pstOpenDmlIdxInfo->u64IdxOffset;
    *u32Size = pstOpenDmlIdxInfo->u32Size;
}

static BOOLEAN msAPI_VDPlayer_DemuxAVI_BuildOpenDmlIndex_Video(void)
{
    S8 s8StreamIndex;
    U32 u32StdIdxCnt, u32AIdxCnt, u32ChunkId;
    U32 u32Size, u32i, u32Skip;
    U32 u32Frmcnt;
    U32 u32VideoKeyIdxCnt;
    U64 u64StdIdxOffset;
    ST_AVI_STD_INDEX stAviStdIndex;
    ST_AVI_STD_INDEX *pstAviStdIndex = &stAviStdIndex;
    ST_VDP_DEMUX_KEYINDEX stDemuxKeyIdx;

    s8StreamIndex = g_stDemuxer.stBitsContent.s8Video_StreamId;

    u32i = 0;
    u32Frmcnt = 0;
    u32VideoKeyIdxCnt = 0;
    memset(&stDemuxKeyIdx, 0, sizeof(stDemuxKeyIdx));
    memset(&stAviStdIndex, 0, sizeof(ST_AVI_STD_INDEX));

    u32StdIdxCnt = msAPI_VDPlayer_DemuxAVI_LoadIndexCnt(s8StreamIndex);
    if (u32StdIdxCnt == 0)
    {
        return FALSE;
    }

    while (u32StdIdxCnt)
    {
        BOOL bVideoStreamIdxChunk = FALSE;

        msAPI_VDPlayer_DemuxAVI_LoadIndexInfo(s8StreamIndex, u32i++, &u64StdIdxOffset, &u32Size);
        if (u64StdIdxOffset > g_stDemuxer.stBitsContent.Container.stAVI.u64FileSize)
        {
            break;
        }
        msAPI_VDPlayer_DemuxAVI_ChangeFilePosition(u64StdIdxOffset,((u32Size&~0xFFF)+0x1000));

        msAPI_VDPlayer_BMFlushBytes(8);
        pstAviStdIndex->u16LongsPerEntry= (U16)msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(2);
        msAPI_VDPlayer_BMFlushBytes(2);
        pstAviStdIndex->u32EntriesInUse = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
        pstAviStdIndex->u32ChunkId      = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();

        // check if this index chunk for this video stream
        u32ChunkId = pstAviStdIndex->u32ChunkId;
        if ((u8u32_2(u32ChunkId) == 'd') &&
                ((u8u32_3(u32ChunkId) == 'c') || (u8u32_3(u32ChunkId) == 'b')||(u8u32_3(u32ChunkId) == 'd')))
        {
            if ((isdigit(u8u32_0(u32ChunkId))) && (isdigit(u8u32_1(u32ChunkId))))
            {
                u32ChunkId = ((u8u32_0(u32ChunkId) - '0') * 10) + (u8u32_1(u32ChunkId) - '0');
                if (u32ChunkId == (U32)g_stDemuxer.stBitsContent.s8Video_StreamId)
                {
                    bVideoStreamIdxChunk = TRUE;
                }
            }
        }

        if (bVideoStreamIdxChunk == FALSE)
        {
            u32StdIdxCnt--;
            msAPI_VDPlayer_BMFlushBytes(12);
            continue;
        }

        u32u64_0(pstAviStdIndex->u64BaseOffset) = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
        u32u64_1(pstAviStdIndex->u64BaseOffset) = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
        msAPI_VDPlayer_BMFlushBytes(4);

        u32Skip = pstAviStdIndex->u16LongsPerEntry * 4 - sizeof(pstAviStdIndex->stAIndex);
        u32AIdxCnt = pstAviStdIndex->u32EntriesInUse;
        while (u32AIdxCnt)
        {
            pstAviStdIndex->stAIndex.u32Offset = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
            pstAviStdIndex->stAIndex.u32Size = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();

            if (!(pstAviStdIndex->stAIndex.u32Size & AVI_NOT_KEYFRAME))
            {
                EN_VDP_DEMUX_INDEXTAB_RET Ret;

                stDemuxKeyIdx.u32Size = pstAviStdIndex->stAIndex.u32Size + 8;
                stDemuxKeyIdx.u64Offset = pstAviStdIndex->u64BaseOffset + pstAviStdIndex->stAIndex.u32Offset - 8;
                stDemuxKeyIdx.u32Pts = msAPI_VDPlayer_Demuxer_CalVideoFrameTime(u32Frmcnt);
                Ret = msAPI_VDPlayer_Demuxer_SaveVideoKeyIdx(&stDemuxKeyIdx);

                if (Ret == E_VDP_DEMUX_BUD_INDEX_TAB_RET_SUCCESS)
                {
                    u32VideoKeyIdxCnt++;
                }
                else if (Ret == E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL)
                {
                    u32StdIdxCnt = 1;
                    break;
                }
                if (g_stDemuxer.u8ThumbNailMode && (stDemuxKeyIdx.u32Pts > THUMBNAIL_JUMPTIME))
                {
                    u32StdIdxCnt = 1;
                    break;
                }
            }
            else
            {
                pstAviStdIndex->stAIndex.u32Size &= ~AVI_NOT_KEYFRAME;
            }

            u32Frmcnt++;

            u32AIdxCnt--;
            if (u32Skip)
            {
                msAPI_VDPlayer_BMFlushBytes(u32Skip);
            }
        }

        u32StdIdxCnt--;
    }

    if (u32VideoKeyIdxCnt == 0)
    {
        return FALSE;
    }

    g_stDemuxer.stBitsContent.Container.stAVI.u32VideoKeyIdxCnt = u32VideoKeyIdxCnt;
    return TRUE;
}

static BOOLEAN msAPI_VDPlayer_DemuxAVI_BuildOpenDmlIndex_Audios(void)
{
    U32 u32StdIdxCnt, u32AIdxCnt;
    U32 u32Size, u32Skip, u32AccumulativeSize;
    U64 u64StdIdxOffset;

    ST_AVI_STD_INDEX stAviStdIndex;
    ST_AVI_STD_INDEX *pstAviStdIndex = &stAviStdIndex;
    ST_VDP_DEMUX_KEYINDEX stDemuxVideoKeyIdx, stDemuxAudioKeyIdx;
    U8 u8AudioTrackIdx, u8StreamIndex;
    U32 u32VideoKeyIndexCnt, u32i, u32Cnt, u32ChunkId;

    if (g_stDemuxer.stBitsContent.u8Nb_AudioTracks == 0)
    {
        return TRUE;
    }

    u32VideoKeyIndexCnt = g_stDemuxer.stBitsContent.Container.stAVI.u32VideoKeyIdxCnt;
    if (!u32VideoKeyIndexCnt)
    {
        return TRUE;
    }

    memset(&stAviStdIndex, 0, sizeof(ST_AVI_STD_INDEX));
    memset(&stDemuxVideoKeyIdx, 0, sizeof(stDemuxVideoKeyIdx));

    u8AudioTrackIdx = 0;
    while (u8AudioTrackIdx < g_stDemuxer.stBitsContent.u8Nb_AudioTracks)
    {
        U32 u32Frmcnt;

        u32Frmcnt = 0;
        memset(&stDemuxAudioKeyIdx, 0, sizeof(stDemuxAudioKeyIdx));
        u8StreamIndex = g_stDemuxer.u8AudioTrackIDMap[u8AudioTrackIdx];
        u32AccumulativeSize = 0;

        u32Cnt = u32i = 0;
#if ENABLE_AUDIO_HANDLER
        if (g_stDemuxer.bEnableAudioHandler == FALSE)
#endif
        {
            msAPI_VDPlayer_Demuxer_GetVideoKeyIdx(u32Cnt++, &stDemuxVideoKeyIdx);
        }

        u32StdIdxCnt = msAPI_VDPlayer_DemuxAVI_LoadIndexCnt(u8StreamIndex);
        if (u32StdIdxCnt == 0)
        {
            // this audio stream has no super index info
            break;
        }

        while (u32StdIdxCnt)
        {
            BOOL bAudioStreamIdxChunk = FALSE;

            msAPI_VDPlayer_DemuxAVI_LoadIndexInfo(u8StreamIndex, u32i++, &u64StdIdxOffset, &u32Size);
            if (u64StdIdxOffset > g_stDemuxer.stBitsContent.Container.stAVI.u64FileSize)
            {
                break;
            }

            msAPI_VDPlayer_DemuxAVI_ChangeFilePosition(u64StdIdxOffset,((u32Size&~0xFFF)+0x1000));

            msAPI_VDPlayer_BMFlushBytes(8);
            pstAviStdIndex->u16LongsPerEntry= (U16)msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(2);
            msAPI_VDPlayer_BMFlushBytes(2);
            pstAviStdIndex->u32EntriesInUse = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
            pstAviStdIndex->u32ChunkId      = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();

            // check if this index chunk for this audio stream
            u32ChunkId = pstAviStdIndex->u32ChunkId;
            if ((u8u32_2(u32ChunkId) == 'w') && (u8u32_3(u32ChunkId) == 'b'))
            {
                if ((isdigit(u8u32_0(u32ChunkId))) && (isdigit(u8u32_1(u32ChunkId))))
                {
                    u32ChunkId = ((u8u32_0(u32ChunkId) - '0') * 10) + (u8u32_1(u32ChunkId) - '0');
                    if (u32ChunkId == u8StreamIndex)
                    {
                        bAudioStreamIdxChunk = TRUE;
                    }
                }
            }

            if (bAudioStreamIdxChunk == FALSE)
            {
                u32StdIdxCnt--;
                msAPI_VDPlayer_BMFlushBytes(12);
                continue;
            }

            u32u64_0(pstAviStdIndex->u64BaseOffset) = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
            u32u64_1(pstAviStdIndex->u64BaseOffset) = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
            msAPI_VDPlayer_BMFlushBytes(4);

            u32Skip = pstAviStdIndex->u16LongsPerEntry * 4 - sizeof(pstAviStdIndex->stAIndex);
            u32AIdxCnt = pstAviStdIndex->u32EntriesInUse;

            while (u32AIdxCnt)
            {
                pstAviStdIndex->stAIndex.u32Offset = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
                pstAviStdIndex->stAIndex.u32Size = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();

                pstAviStdIndex->stAIndex.u32Size &= ~AVI_NOT_KEYFRAME;
                // if (!(pstAviStdIndex->stAIndex.u32Size & AVI_NOT_KEYFRAME))
                {
                    stDemuxAudioKeyIdx.u32Size = pstAviStdIndex->stAIndex.u32Size + 8;
                    stDemuxAudioKeyIdx.u64Offset = pstAviStdIndex->u64BaseOffset + pstAviStdIndex->stAIndex.u32Offset - 8;

                    // check if the file position of this audio key index is bigger than the target video key index
                    while (stDemuxAudioKeyIdx.u64Offset > stDemuxVideoKeyIdx.u64Offset)
                    {
                        if (((g_stDemuxer.stBitsContent.enAudioCodecID[u8AudioTrackIdx] & E_VDP_CODEC_ATTRIBUTE_MASK) != E_VDP_CODEC_AAC) ||
                            (g_stDemuxer.bEnableCalcByBitRate == TRUE))
                        {
                            stDemuxAudioKeyIdx.u32Pts =
                                    msAPI_VDPlayer_Demuxer_CalAudioBitTime(u8AudioTrackIdx, u32AccumulativeSize);
                        }
                        else
                        {
                            stDemuxAudioKeyIdx.u32Pts =
                                    msAPI_VDPlayer_Demuxer_CalAudioBitTime(u8AudioTrackIdx, u32Frmcnt);
                        }

#if ENABLE_AUDIO_HANDLER
                        if (g_stDemuxer.bEnableAudioHandler)
                        {
                            if (msAPI_VDPlayer_Demuxer_SaveAudioKeyIdx(u8AudioTrackIdx, (PST_VDP_DEMUX_AUDIO_KEYINDEX)&stDemuxAudioKeyIdx) == E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL)
                            {
                                 goto next_track;
                            }

                            break;
                        }
#endif

                        if(msAPI_VDPlayer_Demuxer_SaveAudioKeyInfo(u8AudioTrackIdx, stDemuxAudioKeyIdx.u32Pts) == FALSE)
                        {
                            return TRUE;
                        }

                        if (u32Cnt >= u32VideoKeyIndexCnt)
                        {
                            goto next_track;
                        }

                        // get next video key index
                        msAPI_VDPlayer_Demuxer_GetVideoKeyIdx(u32Cnt++, &stDemuxVideoKeyIdx);
                    }
                }
                /*
                else
                {
                    pstAviStdIndex->stAIndex.u32Size &= ~AVI_NOT_KEYFRAME;
                }
                */

                u32AccumulativeSize += msAPI_VDPlayer_Demuxer_CalAudioAlignedSize(u8AudioTrackIdx, pstAviStdIndex->stAIndex.u32Size);
                u32Frmcnt++;

                u32AIdxCnt--;
                if (u32Skip)
                {
                    msAPI_VDPlayer_BMFlushBytes(u32Skip);
                }
            }

            u32StdIdxCnt--;
        }

next_track:
        u8AudioTrackIdx++;
    }

    return TRUE;
}

static EN_AVI_DEMUX_RETURN msAPI_VDPlayer_DemuxAVI_ScanIndex_OpenDML(void)
{
    EN_AVI_DEMUX_RETURN eAviDemuxRet = E_AVI_DEMUX_ERR_INDEX;

    if (msAPI_VDPlayer_DemuxAVI_BuildOpenDmlIndex_Video())
    {
        eAviDemuxRet = E_AVI_DEMUX_SUCCESS;

        if ((g_stDemuxer.stBitsContent.u8Nb_VideoTracks) &&
            (g_stDemuxer.u8ThumbNailMode == FALSE))
        {
            // build indices for all audio
            eAviDemuxRet = (msAPI_VDPlayer_DemuxAVI_BuildOpenDmlIndex_Audios() ?
                    E_AVI_DEMUX_SUCCESS : E_AVI_DEMUX_ERR_INDEX);
        }
    }

    return eAviDemuxRet;
}

static EN_AVI_DEMUX_RETURN msAPI_VDPlayer_DemuxAVI_ScanIndex_OldStyle(void)
{
    BOOLEAN bIndexFound = FALSE;
    BOOLEAN bNeedBuildAudioKey = TRUE;
    U8 u8StreamIndex, u8AudioTrackId;
    U32 u32PadOffset, u32Loop, u32ChunkId, u32AudioKeyIdxCnt[MAX_AUDIO_TRACKS];
    U32 u32VideoFrmCnt,u32Timeout;
    U32 u32AudioFrmCnt[MAX_AUDIO_TRACKS], u32AudioTrackAccumulativeDataSize[MAX_AUDIO_TRACKS];
    U32 u32VideoKeyIdxCnt;
    U64 u64Offset;
    ST_AVI_OLD_INDEX stAviOldIndex;
    ST_AVI_OLD_INDEX *pstAviOldIndex = &stAviOldIndex;
    ST_VDP_DEMUX_KEYINDEX stDemuxVideoKeyIdx;

    u32VideoKeyIdxCnt = 0;
    memset(&stAviOldIndex, 0, sizeof(ST_AVI_OLD_INDEX));

    // seek to 1st movi end
    msAPI_VDPlayer_DemuxAVI_ChangeFilePosition(g_stDemuxer.stBitsContent.Container.stAVI.u32FirstMoviEndPos,AVI_PRELOAD_SIZE);

    pstAviOldIndex->stRiffChunkGeneral.u32Fcc = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);

    // find 'idx1' tag
    u32Timeout = MsOS_GetSystemTime() + TIMEOUT_TIMER_2000MS;
    while (1)
    {
        // check size boundary
        if ((msAPI_VDPlayer_BMFileEOF() == TRUE)
                || (msAPI_VDPlayer_BMFileTell() >= g_stDemuxer.stBitsContent.Container.stAVI.u32FirstRiffEndPos)
                || (MsOS_GetSystemTime() >u32Timeout))
        {
            break;
        }

        if(pstAviOldIndex->stRiffChunkGeneral.u32Fcc == MKTAG('J', 'U', 'N', 'K'))
        {
            // flush this chunk
            pstAviOldIndex->stRiffChunkGeneral.u32Size = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);
            pstAviOldIndex->stRiffChunkGeneral.u32Size = EVEN_ALIGN(pstAviOldIndex->stRiffChunkGeneral.u32Size);
            msAPI_VDPlayer_BMFlushBytes(pstAviOldIndex->stRiffChunkGeneral.u32Size);

            // get next chunk
            pstAviOldIndex->stRiffChunkGeneral.u32Fcc = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);
        }
        else if (pstAviOldIndex->stRiffChunkGeneral.u32Fcc == MKTAG('i', 'd', 'x', '1'))
        {
            // old sytle index found
            bIndexFound = TRUE;
            pstAviOldIndex->stRiffChunkGeneral.u32Size = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);
            pstAviOldIndex->stRiffChunkGeneral.u32Size = EVEN_ALIGN(pstAviOldIndex->stRiffChunkGeneral.u32Size);
            break;
        }
        else
        {
            pstAviOldIndex->stRiffChunkGeneral.u32Fcc =
                    (pstAviOldIndex->stRiffChunkGeneral.u32Fcc << 8) | msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(1);
        }
    }

    if (!bIndexFound)
    {
        return E_AVI_DEMUX_ERR_INDEX;
    }

    memset(&stDemuxVideoKeyIdx, 0, sizeof(stDemuxVideoKeyIdx));
    memset(&u32AudioKeyIdxCnt, 0, sizeof(u32AudioKeyIdxCnt));
    memset(&u32AudioTrackAccumulativeDataSize, 0, sizeof(u32AudioTrackAccumulativeDataSize));

    u32VideoFrmCnt = 0;
    memset(&u32AudioFrmCnt, 0, sizeof(u32AudioFrmCnt));
    u8StreamIndex = U8_MAX; //it means it is not video or audio stream
    u32PadOffset = U32_MAX;
    u32Loop = pstAviOldIndex->stRiffChunkGeneral.u32Size / sizeof(pstAviOldIndex->stAIndex);

    if (pstAviOldIndex->stRiffChunkGeneral.u32Size > 0x400000)
    {
        msAPI_VDPlayer_BM_SetPreloadSize(U32_MAX);
    }
    else
    {
        msAPI_VDPlayer_BM_SetPreloadSize(pstAviOldIndex->stRiffChunkGeneral.u32Size);
    }

    while (u32Loop)
    {
        u32Loop--;
        if(msAPI_VDPlayer_BMFileEOF() == TRUE)
        {
            break;
        }

        pstAviOldIndex->stAIndex.u32ChunkId = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);
        pstAviOldIndex->stAIndex.u32Flags = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);
        pstAviOldIndex->stAIndex.u32Offset = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);
        pstAviOldIndex->stAIndex.u32Size = msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(4);

        if (u32PadOffset == U32_MAX)
        {
            u32PadOffset = 0;
            if (g_stDemuxer.stBitsContent.Container.stAVI.u32FirstMoviStartPos > pstAviOldIndex->stAIndex.u32Offset)
            {
                u32PadOffset = g_stDemuxer.stBitsContent.Container.stAVI.u32FirstMoviStartPos;
            }
        }

        u32ChunkId = pstAviOldIndex->stAIndex.u32ChunkId;
        if (((u8u32_2(u32ChunkId) == 'd') && ((u8u32_3(u32ChunkId) == 'c') || (u8u32_3(u32ChunkId) == 'b')))
                || ((u8u32_2(u32ChunkId) == 'w') && (u8u32_3(u32ChunkId) == 'b')))
        {
            u8StreamIndex = ((u8u32_0(u32ChunkId) - '0') * 10) + (u8u32_1(u32ChunkId) - '0');
        }
        else
        {
            u8StreamIndex = INVALID_STREAM_ID;
            continue;
        }

        if (u8StreamIndex == g_stDemuxer.stBitsContent.s8Video_StreamId)
        {
            if (pstAviOldIndex->stAIndex.u32Flags & AVIIF_KEYFRAME)
            {
                EN_VDP_DEMUX_INDEXTAB_RET eRet;

                stDemuxVideoKeyIdx.u64Offset = pstAviOldIndex->stAIndex.u32Offset;
                stDemuxVideoKeyIdx.u64Offset += u32PadOffset;
                stDemuxVideoKeyIdx.u32Size = pstAviOldIndex->stAIndex.u32Size + 8;
                stDemuxVideoKeyIdx.u32Pts = msAPI_VDPlayer_Demuxer_CalVideoFrameTime(u32VideoFrmCnt);

                eRet = msAPI_VDPlayer_Demuxer_SaveVideoKeyIdx(&stDemuxVideoKeyIdx);
                if (eRet == E_VDP_DEMUX_BUD_INDEX_TAB_RET_SUCCESS)
                {
                    u32VideoKeyIdxCnt++;
                }
                else if (eRet == E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL)
                {
                    printf("E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL\n");
                    break;
                }
                if (g_stDemuxer.u8ThumbNailMode && (stDemuxVideoKeyIdx.u32Pts > THUMBNAIL_JUMPTIME))
                {
                    break;
                }
            }

            u32VideoFrmCnt++;
        }
        else
        {
            for (u8AudioTrackId = 0; u8AudioTrackId < g_stDemuxer.stBitsContent.u8Nb_AudioTracks; u8AudioTrackId++)
            {
                if (u8StreamIndex == g_stDemuxer.u8AudioTrackIDMap[u8AudioTrackId])
                {
                    break;
                }
            }

            if (u8AudioTrackId < g_stDemuxer.stBitsContent.u8Nb_AudioTracks && bNeedBuildAudioKey)
            {
#if ENABLE_AUDIO_HANDLER
                if (g_stDemuxer.bEnableAudioHandler == TRUE)
                {
                    ST_VDP_DEMUX_AUDIO_KEYINDEX stAudioKeyIdx;
                    stAudioKeyIdx.u64Offset = pstAviOldIndex->stAIndex.u32Offset;
                    stAudioKeyIdx.u64Offset += u32PadOffset;
                    stAudioKeyIdx.u32Size = pstAviOldIndex->stAIndex.u32Size;
                    stAudioKeyIdx.u32Frm_Info_Idx = u32AudioFrmCnt[u8AudioTrackId];

                    if (((g_stDemuxer.stBitsContent.enAudioCodecID[u8AudioTrackId] & E_VDP_CODEC_ATTRIBUTE_MASK) != E_VDP_CODEC_AAC) ||
                        (g_stDemuxer.bEnableCalcByBitRate == TRUE))
                    {
                        stAudioKeyIdx.u32Pts = msAPI_VDPlayer_Demuxer_CalAudioBitTime(u8AudioTrackId, u32AudioTrackAccumulativeDataSize[u8AudioTrackId]);
                    }
                    else
                    {
                        stAudioKeyIdx.u32Pts = msAPI_VDPlayer_Demuxer_CalAudioBitTime(u8AudioTrackId, u32AudioFrmCnt[u8AudioTrackId]);
                    }

                    if (msAPI_VDPlayer_Demuxer_SaveAudioKeyIdx(u8AudioTrackId, (PST_VDP_DEMUX_AUDIO_KEYINDEX)&stAudioKeyIdx) == E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL)
                    {
                         ;
                    }
                }
                else
#endif  // #if ENABLE_AUDIO_HANDLER
                {
                    if (u32AudioKeyIdxCnt[u8AudioTrackId] < u32VideoKeyIdxCnt)
                    {
                        msAPI_VDPlayer_Demuxer_GetVideoKeyIdx(u32AudioKeyIdxCnt[u8AudioTrackId]++, &stDemuxVideoKeyIdx);

                        u64Offset = pstAviOldIndex->stAIndex.u32Offset;
                        u64Offset += u32PadOffset;
                        while (u64Offset > stDemuxVideoKeyIdx.u64Offset)
                        {
                            U32 u32AudioPts;

                            if (((g_stDemuxer.stBitsContent.enAudioCodecID[u8AudioTrackId] & E_VDP_CODEC_ATTRIBUTE_MASK) != E_VDP_CODEC_AAC) ||
                                (g_stDemuxer.bEnableCalcByBitRate == TRUE))
                            {
                                u32AudioPts = msAPI_VDPlayer_Demuxer_CalAudioBitTime(u8AudioTrackId, u32AudioTrackAccumulativeDataSize[u8AudioTrackId]);
                            }
                            else
                            {
                                u32AudioPts = msAPI_VDPlayer_Demuxer_CalAudioBitTime(u8AudioTrackId, u32AudioFrmCnt[u8AudioTrackId]);
                            }

                            if (msAPI_VDPlayer_Demuxer_SaveAudioKeyInfo(u8AudioTrackId, u32AudioPts) == FALSE)
                            {
                                bNeedBuildAudioKey = FALSE;
                                break;
                            }

                            if (u32AudioKeyIdxCnt[u8AudioTrackId] >= u32VideoKeyIdxCnt)
                            {
                                break;
                            }

                            // get next video key index
                            msAPI_VDPlayer_Demuxer_GetVideoKeyIdx(u32AudioKeyIdxCnt[u8AudioTrackId]++, &stDemuxVideoKeyIdx);
                        }
                    }
                }

                u32AudioTrackAccumulativeDataSize[u8AudioTrackId] += msAPI_VDPlayer_Demuxer_CalAudioAlignedSize(u8AudioTrackId, pstAviOldIndex->stAIndex.u32Size);
                u32AudioFrmCnt[u8AudioTrackId]++;
            }
        }
    }
    return E_AVI_DEMUX_SUCCESS;
}

BOOL MApp_VDPlayer_AVIScanIndex(U8 u8FileHdl)
{
    ST_HK_AVI_SCAN stHK_AVI_SCAN;
    U32 u32VAaddr;

    memset(&g_stDemuxer, 0, sizeof(ST_VDP_DEMUX_GLOBAL));

    msAPI_VDPlayer_GetShareMemoryDataAVIScan(&stHK_AVI_SCAN);
    // Assign Variables
    g_stDemuxer.u8ThumbNailMode = stHK_AVI_SCAN.u8ThumbNailMode;
    g_stDemuxer.stBitsContent.Container.stAVI.u64FileSize = stHK_AVI_SCAN.u64FileSize;
    g_stDemuxer.stBitsContent.Container.stAVI.u32FirstMoviStartPos = stHK_AVI_SCAN.u32FirstMoviStartPos;
    g_stDemuxer.stBitsContent.Container.stAVI.u32FirstMoviEndPos = stHK_AVI_SCAN.u32FirstMoviEndPos;
    g_stDemuxer.stBitsContent.Container.stAVI.u32FirstRiffEndPos = stHK_AVI_SCAN.u32FirstRiffEndPos;
    g_stDemuxer.stBitsContent.Container.stAVI.pstOpenDmlIdxHeaderInfo = (ST_OPEN_DML_IDX_HEADER_INFO *)_PA2VA((U32)stHK_AVI_SCAN.pstOpenDmlIdxHeaderInfo);
    g_stDemuxer.stDataBuffer.u32IndexBuffAddr = _PA2VA(stHK_AVI_SCAN.u32IndexBuffAddr);
    g_stDemuxer.stDataBuffer.u32IndexBuffSize = stHK_AVI_SCAN.u32IndexBuffSize;
    g_stDemuxer.u8KeyIdxSize = stHK_AVI_SCAN.u8KeyIdxSize;
    g_stDemuxer.u32KeyIdxPeriod = stHK_AVI_SCAN.u32KeyIdxPeriod;
    g_stDemuxer.stBitsContent.s8Video_StreamId = stHK_AVI_SCAN.s8Video_StreamId;
    g_stDemuxer.stBitsContent.s8Audio_StreamId = stHK_AVI_SCAN.s8Audio_StreamId;
    g_stDemuxer.stBitsContent.u8Nb_VideoTracks = stHK_AVI_SCAN.u8Nb_VideoTracks;
    g_stDemuxer.stBitsContent.u8Nb_AudioTracks = stHK_AVI_SCAN.u8Nb_AudioTracks;
    g_stDemuxer.stBitsContent.Container.stAVI.VideoTracks[0].u32FrameRate = stHK_AVI_SCAN.u32FrameRate;
    g_stDemuxer.stBitsContent.Container.stAVI.VideoTracks[0].u32FrameRateBase = stHK_AVI_SCAN.u32FrameRateBase;
    if (stHK_AVI_SCAN.bEnableCalcByBitRate == TRUE)
    {
        g_stDemuxer.bEnableCalcByBitRate = TRUE;
    }
    else
    {
        g_stDemuxer.bEnableCalcByBitRate = FALSE;
    }
    g_stDemuxer.bEnableAudioHandler = FALSE;
#if ENABLE_AUDIO_HANDLER
    if (stHK_AVI_SCAN.bEnableAudioHandler == TRUE)
    {
        U32 i;
        g_stDemuxer.bEnableAudioHandler = TRUE;

        for (i = 0; i < MAX_AUDIO_TRACKS; i++)
        {
            g_stDemuxer.u32AudioKeyBufAddr[i] = _PA2VA(stHK_AVI_SCAN.u32AudioKeyBufAddr[i]);
            g_stDemuxer.u32AudioKeyBufSize[i] = stHK_AVI_SCAN.u32AudioKeyBufSize[i];
        }
        g_stDemuxer.u32AudioKeyIdxPeriod = stHK_AVI_SCAN.u32AudioKeyIdxPeriod;
        g_stDemuxer.u8AudioKeyIdxSize = stHK_AVI_SCAN.u8AudioKeyIdxSize;
    }
#endif // #if ENABLE_AUDIO_HANDLER

    memcpy(g_stDemuxer.stBitsContent.enAudioCodecID, stHK_AVI_SCAN.enAudioCodecID, MAX_AUDIO_TRACKS * sizeof(EN_VDP_CODECID));
    memcpy(g_stDemuxer.u8AudioTrackIDMap, stHK_AVI_SCAN.u8AudioTrackIDMap, MAX_AUDIO_TRACKS * sizeof(U8));
    memcpy(g_stDemuxer.stBitsContent.unAudioParam, stHK_AVI_SCAN.unAudioParam, MAX_AUDIO_TRACKS * sizeof(UN_VDP_AUDIO_PARAM));
    msAPI_VDPlayer_BMInit(u8FileHdl, g_stDemuxer.stBitsContent.Container.stAVI.u64FileSize);
    u32VAaddr = _PA2VA(stHK_AVI_SCAN.u32BitstreamAddr);
    msAPI_VDPlayer_BMBuffer_Configuration(u32VAaddr, stHK_AVI_SCAN.u32BitstreamSize);

    if ((msAPI_VDPlayer_DemuxAVI_ScanIndex_OpenDML() != E_AVI_DEMUX_SUCCESS)
            && (msAPI_VDPlayer_DemuxAVI_ScanIndex_OldStyle() != E_AVI_DEMUX_SUCCESS))
    {
        return FALSE;
    }

    // Assign Variables to Coprocessor
    stHK_AVI_SCAN.u32Video_IdxSize = g_stDemuxer.u32Video_IdxSize;
    stHK_AVI_SCAN.u32FirstVideoKeyFramePTS = g_stDemuxer.u32FirstVideoKeyFramePTS;
    stHK_AVI_SCAN.u32lastVideoKeyFramePTS = g_stDemuxer.u32lastVideoKeyFramePTS;
    memcpy(stHK_AVI_SCAN.u32Audio_IdxSize, g_stDemuxer.u32Audio_IdxSize, MAX_AUDIO_TRACKS * sizeof(U32));
    msAPI_VDPlayer_SetShareMemoryDataAVIScan(&stHK_AVI_SCAN);
    return TRUE;
}
#endif //ENABLE_HK_AVI_PERFORMANCE_IMPROVE

#if ENABLE_HK_MP4
static int MApp_VDPlyer_MP4_Get_Sample_Table_Idx(EN_MOV_MEDIA_TYPE enMediaType, int *table_index, mvc_stream_type_et *type)
{
#if ENABLE_HK_SUBTITLE
    switch (enMediaType)
    {
    case E_MOV_MEDIA_TYPE_VIDEO1:
        *table_index = 0;
        *type = MVC_STREAM_VIDEO;
        return 0;
    case E_MOV_MEDIA_TYPE_AUDIO1:
        *table_index = 1;
        *type = MVC_STREAM_AUDIO;
        return 0;
    case E_MOV_MEDIA_TYPE_SUBTITLE1:
        *table_index = 2;
        *type = MVC_STREAM_SUBTITLE;
        return 0;
    case E_MOV_MEDIA_TYPE_VIDEO2:
        *table_index = 3;
        *type = MVC_STREAM_VIDEO;
        return 0;
    case E_MOV_MEDIA_TYPE_AUDIO2:
        *table_index = 4;
        *type = MVC_STREAM_AUDIO;
        return 0;
    case E_MOV_MEDIA_TYPE_SUBTITLE2:
        *table_index = 5;
        *type = MVC_STREAM_SUBTITLE;
        return 0;
    default:
        return -1;
    }
#else
    switch (enMediaType)
    {
    case E_MOV_MEDIA_TYPE_VIDEO1:
        *table_index = 0;
        *type = MVC_STREAM_VIDEO;
        return 0;
    case E_MOV_MEDIA_TYPE_AUDIO1:
        *table_index = 1;
        *type = MVC_STREAM_AUDIO;
        return 0;
    case E_MOV_MEDIA_TYPE_VIDEO2:
        *table_index = 2;
        *type = MVC_STREAM_VIDEO;
        return 0;
    case E_MOV_MEDIA_TYPE_AUDIO2:
        *table_index = 3;
        *type = MVC_STREAM_AUDIO;
        return 0;
    default:
        return -1;
    }
#endif
}

static int MApp_VDPlayer_MP4_SetTrack_By_StreamID(void *mp4Inst, mvc_stream_type_et type, U8 u8StreamID)
{
    int ret, track_id;
    mvc_stream_type_et type_from_dx;
    mvc_program_info_st p_info;

    ret = MP4DMX_GetTrackIdByStreamId(mp4Inst, u8StreamID, &type_from_dx, &track_id);
    if (ret != MSMERR_OK)
    {
        VDPLAYER_DBG(printf("%s get track ID fail, stream ID %d\n", __FUNCTION__, u8StreamID));
        return FALSE;
    }

    if (type != type_from_dx)
    {
        VDPLAYER_DBG(printf("%s type mismatch, %d != %d\n", __FUNCTION__, type, type_from_dx));
        return FALSE;
    }

    ret = MP4DMX_GetInfomation(mp4Inst, MVC_STREAM_PROG, -1, &p_info);
    if (ret != MVC_OK)
    {
        VDPLAYER_DBG(printf("%s get program info fail\n", __FUNCTION__));
        return FALSE;
    }

    if ((type_from_dx == MVC_STREAM_AUDIO && p_info.active_audio != track_id)
     || (type_from_dx == MVC_STREAM_VIDEO && p_info.active_video != track_id)
     || (type_from_dx == MVC_STREAM_SUBTITLE && p_info.active_subtitle != track_id))
    {
        VDPLAYER_DBG(printf("%s type %d, active audio %d, video %d, sub %d, track id %d\n"
           , __FUNCTION__, type_from_dx, p_info.active_audio, p_info.active_video, p_info.active_subtitle, track_id));
        ret = MP4DMX_SetTrack(mp4Inst, type_from_dx, track_id);
        if (ret != MVC_OK)
        {
            VDPLAYER_DBG(printf("%s set type %d track to %d fail\n", __FUNCTION__, type_from_dx, track_id));
            return FALSE;
        }
    }

    return TRUE;
}

#define MAX_UPDATE_INDEX_SUM 5000// 5sec
// update until key frame pts reaches pts_end, pts_end == U32_MAX means no restriction
// return 1 if update is finished, return 0 if there is more
static int MApp_VDPlayer_MP4ScanVideoIndex(void *mp4Inst, uint32_t *first_keyframe_index, uint32_t pts_end, U32 *elapsed_time)
{
    int ret;
    U32 t1, t2;
    cb_fpos offset;
    uint32_t size, i, keyframeidx;
    uint64_t pts, duration;
    ST_VDP_DEMUX_KEYINDEX stKeyIdx;
    int update_finish;

    t1 = t2 = msAPI_Timer_GetTime0();
    i = *first_keyframe_index;
    while (1)
    {
        ret = MP4DMX_GetVideoKeyFrameIdx(mp4Inst, i, &keyframeidx);
        if (ret != MSMERR_OK)
        {
            update_finish = 1;
            break;
        }
        ret = MP4DMX_ReadSampleInfo(mp4Inst,
                                keyframeidx,
                                    &offset,
                                      &size,
                                       &pts,
                                  &duration,
                                          0,
                           MVC_STREAM_VIDEO);
        if (ret != MSMERR_OK)
        {
            update_finish = 1;
            break;
        }

        //VDPLAYER_DBG(printf ("[MP4] video index %d, pts %lld ,size %d, offset %llx\n", keyframeidx, pts, size, offset));

        stKeyIdx.u32Frm_Info_Idx = keyframeidx;
        stKeyIdx.u32Pts = pts;
        stKeyIdx.u32Size = size;
        stKeyIdx.u64Offset = offset;
        msAPI_VDPlayer_Demuxer_SaveVideoKeyIdx(&stKeyIdx);
        i++;
        if ((uint32_t)pts > pts_end)
        {
            *first_keyframe_index = i;
            update_finish = 0;
            break;
        }
    }
    t2 = msAPI_Timer_GetTime0();
    *elapsed_time += t2 - t1;
    VDPLAYER_DBG(printf ("%s scan video, key count %d, size of table %d, pts end %d, time %d\n", __FUNCTION__, i, g_stDemuxer.u32Video_IdxSize / g_stDemuxer.u8KeyIdxSize, pts_end, *elapsed_time));

    return update_finish;
}

static int MApp_VDPlayer_MP4ScanAudioIndex(void *mp4Inst, ST_CONTAINER_MP4 *pstMP4, ST_FRAME_INDEX_INFO *last_audio, U8 vdplayer_trackID, uint32_t pts_end, U32 *elapsed_time
#if ENABLE_HK_MP4_PERFORMANCE_IMPROVE
    , U64 *total_duration
#endif
    )
    {
    int ret;
    U32 t1, t2;
    cb_fpos offset;
    uint32_t size, i;
    uint64_t pts, duration;
    ST_VDP_DEMUX_AUDIO_KEYINDEX stAudioKeyIdx;
    U8 u8StreamID;
    int update_finish;

#if ENABLE_HK_MP4_PERFORMANCE_IMPROVE
    U64 average_duration;
#endif
    u8StreamID = last_audio->stream_id;
    ret = MApp_VDPlayer_MP4_SetTrack_By_StreamID(mp4Inst, MVC_STREAM_AUDIO, u8StreamID);
        if (ret == FALSE)
        {
            VDPLAYER_DBG(printf("%s set track to stream %d fail\n", __FUNCTION__, u8StreamID));
        return 1;
        }

    t1 = t2 = msAPI_Timer_GetTime0();
    i = last_audio->frame_index;
        while (1)
        {
        ret = MP4DMX_ReadSampleInfo(mp4Inst,
                                              i,
                                        &offset,
                                          &size,
                                           &pts,
                                      &duration,
                                              0,
                               MVC_STREAM_AUDIO);
            if (ret != MSMERR_OK)
        {
            update_finish = 1;
                break;
        }
            //VDPLAYER_DBG(printf ("[MP4] audio index %d, packed index %d, pts %lld ,size %d, offset %llx\n", i, packed_index, pts, size, offset));

        stAudioKeyIdx.u32Frm_Info_Idx = last_audio->sample_id;
            stAudioKeyIdx.u32Pts = pts;
            stAudioKeyIdx.u32Size = size;
            stAudioKeyIdx.u64Offset = offset;
            msAPI_VDPlayer_Demuxer_SaveAudioKeyIdx(vdplayer_trackID, &stAudioKeyIdx);
#if ENABLE_HK_MP4_PERFORMANCE_IMPROVE
        if (pstMP4->audio_pack_type[vdplayer_trackID] == E_MP4_PACK_TYPE_UNPACKED)
            {
            last_audio->sample_id += last_audio->index_gap;
            i += last_audio->index_gap;
            }
            else
#endif
            {
            last_audio->sample_id++;
            i += MP4DMX_GetAudioIdxGap(mp4Inst, size);
        }

        if (pstMP4->audio_pack_type[vdplayer_trackID] == E_MP4_PACK_TYPE_UNKNOWN)
            {
            if (i != last_audio->sample_id)
                {
                pstMP4->audio_pack_type[vdplayer_trackID] = E_MP4_PACK_TYPE_PACKED;
                    VDPLAYER_DBG(printf ("%s audio is packed format\n", __FUNCTION__));
                }
#if ENABLE_HK_MP4_PERFORMANCE_IMPROVE
                else
                {
                    // audio is not packed for the first one thousand packet, we treat it as un-packed format (not pcm)
                if (last_audio->sample_id > 1000)
                    {
                    average_duration = *total_duration / 1000;
                        // use the IdxPeriod to speed up
                        if (average_duration)
                        last_audio->index_gap = g_stDemuxer.u32AudioKeyIdxPeriod / 4 / average_duration;
                    if (last_audio->index_gap == 0)
                        last_audio->index_gap = 1;
                        stMP4.audio_pack_type[vdplayer_trackID] = E_MP4_PACK_TYPE_UNPACKED;
                    VDPLAYER_DBG(printf ("%s audio is unpacked format, avg duration %lld, index period %d, gap %d\n", __FUNCTION__, average_duration, g_stDemuxer.u32AudioKeyIdxPeriod, last_audio->index_gap));
                    }
                    else
                    *total_duration += duration;
                }
#endif
            }
        if ((uint32_t)pts > pts_end)
        {
            last_audio->frame_index = i;
            update_finish = 0;
            break;
        }
        }
    t2 = msAPI_Timer_GetTime0();
        // for audio track with sample smaller than decision threshold
    if (update_finish && stMP4.audio_pack_type[vdplayer_trackID] == E_MP4_PACK_TYPE_UNKNOWN)
        {
            average_duration = *total_duration / 1000;
                // use the IdxPeriod to speed up
                if (average_duration)
                last_audio->index_gap = g_stDemuxer.u32AudioKeyIdxPeriod / 4 / average_duration;
            if (last_audio->index_gap == 0)
                last_audio->index_gap = 1;

            stMP4.audio_pack_type[vdplayer_trackID] = E_MP4_PACK_TYPE_UNPACKED;
            VDPLAYER_DBG(printf ("%s audio is unpacked format\n", __FUNCTION__));
        }

    *elapsed_time += t2 - t1;
    VDPLAYER_DBG(printf ("%s scan audio track %d, stream %d, key count %d, size of table %d, pts end %d, time %d\n",
        __FUNCTION__, vdplayer_trackID, u8StreamID, last_audio->sample_id - 1,
        g_stDemuxer.u32Audio_IdxSize[vdplayer_trackID] / g_stDemuxer.u8AudioKeyIdxSize, pts_end, *elapsed_time));

    return update_finish;
}

#if ENABLE_HK_SUBTITLE
static void MApp_VDPlayer_MP4_ClearSubtitleSampleInfo(void)
{
    reset_mp4_subtitle_table_info(&stMP4);
}

EN_VDP_DEMUX_INDEXTAB_RET msAPI_VDPlayer_Demuxer_SaveSubtitleKeyIdx(U8 u8TrackID, SubtitleMP4PTSEntry *pstKeyIdx)
{
    U32 *pu32KeyIdx;
    U32 *pu32EndAddr;

    pu32KeyIdx = (U32 *)(g_stDemuxer.u32SubKeyBufAddr[u8TrackID] + g_stDemuxer.u32Subtitle_IdxSize[u8TrackID]);
    pu32EndAddr = (U32 *)(g_stDemuxer.u32SubKeyBufAddr[u8TrackID] + g_stDemuxer.u32SubKeyBufSize[u8TrackID] - g_stDemuxer.u8SubtitleKeyIdxSize);
    if (pu32KeyIdx <= pu32EndAddr)
    {
        memcpy((void*)pu32KeyIdx, (void*)pstKeyIdx, sizeof(SubtitleMP4PTSEntry));
        g_stDemuxer.u32Subtitle_IdxSize[u8TrackID] += g_stDemuxer.u8SubtitleKeyIdxSize;
        g_stDemuxer.u32TotalPictures[u8TrackID]++;
    }
    else
    {
        return E_VDP_DEMUX_BUD_INDEX_TAB_RET_FULL;
    }
    return E_VDP_DEMUX_BUD_INDEX_TAB_RET_SUCCESS;
}

static int MApp_VDPlayer_MP4ScanSubtitleIndex(void *mp4Inst, ST_FRAME_INDEX_INFO *last_subtitle, U8 vdplayer_trackID, uint32_t pts_end, U32 *elapsed_time)
{
    SubtitleMP4PTSEntry stSubKeyIdx;
    cb_fpos    offset;
    U64  u64PTS, u64Duration;
    S32  s32Ret;
    U32  u32T1, u32T2, u32Size, u32Idx;
    U8   u8StreamID;
    BOOL bUpdateFinish;

    u8StreamID = last_subtitle->stream_id;
    s32Ret = MApp_VDPlayer_MP4_SetTrack_By_StreamID(mp4Inst, MVC_STREAM_SUBTITLE, u8StreamID);
    if (s32Ret == FALSE)
    {
        VDPLAYER_DBG(printf("%s set track to stream %d fail\n", __FUNCTION__, u8StreamID));
        return 1;
    }

    u32T1 = u32T2 = msAPI_Timer_GetTime0();
    u32Idx = last_subtitle->frame_index;
    while (1)
    {
        s32Ret = MP4DMX_ReadSampleInfo(mp4Inst,
                                       u32Idx,
                                       &offset,
                                       (uint32_t *)&u32Size,
                                       &u64PTS,
                                       &u64Duration,
                                       0,
                                       MVC_STREAM_SUBTITLE);
        if (s32Ret != MSMERR_OK)
        {
            bUpdateFinish = TRUE;
            break;
        }
        VDPLAYER_DBG(printf ("[MP4] subtitle index %d, sample %d, pts %lld ,offset %llx\n", u32Idx, last_subtitle->sample_id, u64PTS, offset));
        stSubKeyIdx.u32FrameInfoIndex = last_subtitle->sample_id;
        stSubKeyIdx.u32StartPTS = u64PTS;
        stSubKeyIdx.u32EndPTS = u64PTS + u64Duration;
        stSubKeyIdx.u32Fileoffset = (U32)offset;
        stSubKeyIdx.u16FileoffsetHi = (U16)(offset >> 32);
        stSubKeyIdx.u16Size = u32Size;
        msAPI_VDPlayer_Demuxer_SaveSubtitleKeyIdx(vdplayer_trackID, &stSubKeyIdx);
        {
            last_subtitle->sample_id++;
            // fix me... how to get next sample index of subtitle
            u32Idx++;
        }

        if ((uint32_t)u64PTS > pts_end)
        {
            last_subtitle->frame_index = u32Idx;
            bUpdateFinish = FALSE;
            break;
        }
    }
    u32T2 = MsOS_GetSystemTime();

    *elapsed_time += (u32T2 - u32T1);

    VDPLAYER_DBG(printf ("%s scan subtitle track %d, stream %d, key count %d, size of table %d, pts end %d, time %d\n",
        __FUNCTION__, vdplayer_trackID, u8StreamID, (int)last_subtitle->sample_id - 1,
        (int)(g_stDemuxer.u32Subtitle_IdxSize[vdplayer_trackID] / g_stDemuxer.u8SubtitleKeyIdxSize), (int)pts_end, (int)*elapsed_time));

    return bUpdateFinish;
}
#endif

#define DURATION_FRACTION 10
static int MApp_VDPlayer_MP4ScanIndex(void *mp4Inst, ST_HK_MP4 *pstHK_MP4)
{
    int ret;
    U8 vdplayer_trackID;
    U32 t1, t2, init_time, video_time = 0, audio_time[MAX_AUDIO_TRACKS] = {0};
    void *mp4IndexInst;
    uint32_t last_video_key_idx = 0;
    int video_finished = 0, audio_finished[MAX_AUDIO_TRACKS] = {0};
    ST_FRAME_INDEX_INFO last_audio[MAX_AUDIO_TRACKS];
    uint32_t file_duration, fraction_index;
    mvc_program_info_st p_info;
#if ENABLE_HK_MP4_PERFORMANCE_IMPROVE
    U64 total_duration[MAX_AUDIO_TRACKS] = {0};
#endif

#if ENABLE_HK_SUBTITLE
        U32  u32SubtitleTime[MAX_AUDIO_TRACKS] = {0};
        BOOL bSubtitleFinished[MAX_SUBTITLE_TRACKS] = {0};
        ST_FRAME_INDEX_INFO last_subtitle[MAX_SUBTITLE_TRACKS];
#endif // #if ENABLE_HK_SUBTITLE

    // need to restore file position when second mp4demux is closed
    cb_off_t curpos = stMP4.pcbio->tell(stMP4.pcbio);

    // reset last audio frame info
    for (vdplayer_trackID = 0; vdplayer_trackID < pstHK_MP4->u8Nb_AudioTracks; vdplayer_trackID++)
    {
        reset_mp4_frame_index_info(&last_audio[vdplayer_trackID], pstHK_MP4->u8AudioTrackIDMap[vdplayer_trackID]);
    }
#if ENABLE_HK_SUBTITLE
        // reset last subtitle frame info
        for (vdplayer_trackID = 0; vdplayer_trackID < pstHK_MP4->u8Nb_SubtitleTracks; vdplayer_trackID++)
        {
            reset_mp4_frame_index_info(&last_subtitle[vdplayer_trackID], pstHK_MP4->u8SubtitleTrackIDMap[vdplayer_trackID]);
        }
#endif // #if ENABLE_HK_SUBTITLE


    t1 = msAPI_Timer_GetTime0();
    ret = MP4DMX_Open2(                                 &mp4IndexInst,
           (unsigned char *)MS_PA2KSEG0(pstHK_MP4->u32FrameBufferAddr),
                                         pstHK_MP4->u32FrameBufferLen,
                                                          stMP4.pcbio,
                                                                    0,
                                                        &mvc_callback,
                                             MP4_ATOM_TABLE_CACHE_SIZE);
    init_time = msAPI_Timer_GetTime0() - t1;
    VDPLAYER_DBG(printf ("MP4DMX_Open2 ret 0x%x, heap size %d, cache size %d, time %d\n", ret, pstHK_MP4->u32FrameBufferLen, MP4_ATOM_TABLE_CACHE_SIZE, init_time));
    // use original mp4 demuxer if large cache fails
    if (ret != MSMERR_OK)
    {
        stMP4.pcbio->seek(stMP4.pcbio, curpos, SEEK_SET);
        mp4IndexInst = mp4Inst;
    }

    if (MP4DMX_GetInfomation(mp4IndexInst, MVC_STREAM_PROG, -1, &p_info) == MVC_OK)
        file_duration = p_info.duration / 1000;
    else
        file_duration = U32_MAX;

    for (fraction_index = 1; fraction_index <= DURATION_FRACTION; fraction_index++)
    {
        int finished = 1;
        uint32_t pts_end;

        if (fraction_index == DURATION_FRACTION)
            pts_end = U32_MAX;
        else
            pts_end = file_duration / DURATION_FRACTION * fraction_index;

        if (video_finished == 0)
        {
            video_finished = MApp_VDPlayer_MP4ScanVideoIndex(mp4IndexInst,
                                                      &last_video_key_idx,
                                                                  pts_end,
                                                              &video_time);
            finished = finished && video_finished;
        }
        for (vdplayer_trackID = 0; vdplayer_trackID < pstHK_MP4->u8Nb_AudioTracks; vdplayer_trackID++)
        {
            audio_finished[vdplayer_trackID] =
                MApp_VDPlayer_MP4ScanAudioIndex(mp4IndexInst
                                                     ,&stMP4
                               ,&last_audio[vdplayer_trackID]
                                            ,vdplayer_trackID
                                                     ,pts_end
                               ,&audio_time[vdplayer_trackID]
#if ENABLE_HK_MP4_PERFORMANCE_IMPROVE
                           ,&total_duration[vdplayer_trackID]
#endif
                            );
            finished = finished && audio_finished[vdplayer_trackID];
        }

#if ENABLE_HK_SUBTITLE
        for (vdplayer_trackID = 0; vdplayer_trackID < pstHK_MP4->u8Nb_SubtitleTracks; vdplayer_trackID++)
        {
            bSubtitleFinished[vdplayer_trackID] =
            MApp_VDPlayer_MP4ScanSubtitleIndex(mp4IndexInst,
                                              &last_subtitle[vdplayer_trackID],
                                              vdplayer_trackID,
                                              pts_end,
                                              &u32SubtitleTime[vdplayer_trackID]);
             finished = finished && bSubtitleFinished[vdplayer_trackID];
         }
#endif // #if ENABLE_HK_SUBTITLE

        if (finished)
            break;

        t2 = msAPI_Timer_GetTime0();
        if (t2 - t1 > MAX_UPDATE_INDEX_SUM)
        {
            printf("%s, update over %dms\n", __FUNCTION__, MAX_UPDATE_INDEX_SUM);
            break;
        }
    }


    t1 = 0;
    for (vdplayer_trackID = 0; vdplayer_trackID < pstHK_MP4->u8Nb_AudioTracks; vdplayer_trackID++)
        t1 += audio_time[vdplayer_trackID];

    VDPLAYER_DBG(printf ("%s time total time %d, init %d, video %d, audio %d\n", __FUNCTION__,
        init_time + video_time + t1, init_time, video_time, t1));

    // if we use 2nd mp4 demux for index parsing, close it
    if (mp4IndexInst != mp4Inst)
    {
        MP4DMX_Close(mp4IndexInst);
        stMP4.pcbio->seek(stMP4.pcbio, curpos, SEEK_SET);
    }

    return TRUE;
}

static void MApp_VDPlayer_MP4SetFirstFrameOffset(void *mp4Inst, ST_HK_MP4_INIT *pstHK_MP4_INIT)
{
    U8 i;
    int ret, track_id;
    cb_fpos offset;
    uint32_t size;
    mvc_stream_type_et type;

    for (i = 0; i < MAX_TOTAL_TRACKS; i++)
    {
        ret = MP4DMX_GetTrackIdByStreamId(mp4Inst, i, &type, &track_id);
        if (ret != MSMERR_OK)
        {
            //VDPLAYER_DBG(printf("%s get track ID fail, stream ID %d\n", __FUNCTION__, i));
            continue;
        }
        ret = MApp_VDPlayer_MP4_SetTrack_By_StreamID(mp4Inst, type, i);
        if (ret != TRUE)
            continue;

        ret = MP4DMX_ReadSampleInfo(mp4Inst,
                                          1, // first sample
                                    &offset,
                                      &size,
                                          0,
                                          0,
                                          0,
                                       type);
        if (ret == MSMERR_OK)
            pstHK_MP4_INIT->u64Offset_Min[i] = offset;
    }
}

static void MApp_VDPlayer_MP4_Init(U32 u32Addr)
{
    ST_HK_MP4_INIT stHK_MP4_INIT;
    mvc_clip_info_st cinfo;

    memcpy((void*)&stHK_MP4_INIT, (const void*)u32Addr, sizeof(ST_HK_MP4_INIT));
    memset(&g_stDemuxer, 0, sizeof(ST_VDP_DEMUX_GLOBAL));

    EN_MOV_MEDIA_TYPE enMediaType = E_MOV_MEDIA_TYPE_VIDEO1;
    for (enMediaType = E_MOV_MEDIA_TYPE_VIDEO1; enMediaType < E_MOV_MEDIA_TYPE_MAX; enMediaType++)
    {
        g_stDemuxer.stDataBuffer.u32SampleInfoAddr[enMediaType] = _PA2VA(stHK_MP4_INIT.u32SampleInfoAddr[enMediaType]);
        g_stDemuxer.stDataBuffer.u32SampleInfoLen[enMediaType] = stHK_MP4_INIT.u32SampleInfoLen[enMediaType];
    }
    g_stDemuxer.stDataBuffer.u32HKUsedAddr = _PA2VA(stHK_MP4_INIT.u32HKUsedAddr);
    g_stDemuxer.stDataBuffer.u32HKUsedLen = stHK_MP4_INIT.u32HKUsedLen;

    if (open_mp4_resource(&stMP4, &stHK_MP4_INIT) == FALSE)
    {
        release_mp4_resource(&stMP4);
        printf("ERROR, open_mp4_resource fail\n");
        return;
    }

    // update A/V first frame offset to co-processor
    MApp_VDPlayer_MP4SetFirstFrameOffset(stMP4.mp4Inst, &stHK_MP4_INIT);
    // assign time stamp mode, default is PTS
    stHK_MP4_INIT.u8TimeStampType = E_VDP_TIMESTAMP_PTS;
    if (MP4DMX_GetInfomation(stMP4.mp4Inst, MVC_STREAM_NONE , -1, &cinfo) == MVC_OK)
    {
        if (cinfo.ts_type == MVC_TS_DTS)
            stHK_MP4_INIT.u8TimeStampType = E_VDP_TIMESTAMP_DTS;
    }

    memcpy((void*)u32Addr, (const void*)&stHK_MP4_INIT, sizeof(ST_HK_MP4_INIT));
    MsOS_FlushMemory();
}

static void MApp_VDPlayer_MP4_GetIndexInfo(U32 u32Addr)
{
    ST_HK_MP4 stHK_MP4;

    memcpy((void*)&stHK_MP4, (const void*)u32Addr, sizeof(ST_HK_MP4));

    g_stDemuxer.stDataBuffer.u32FrameBufferAddr = _PA2VA(stHK_MP4.u32FrameBufferAddr); // video frame buffer address
    g_stDemuxer.stDataBuffer.u32FrameBufferLen = stHK_MP4.u32FrameBufferLen; // video frame buffer length
    g_stDemuxer.stDataBuffer.u32IndexBuffAddr = _PA2VA(stHK_MP4.u32IndexBuffAddr); // video index info address
    g_stDemuxer.stDataBuffer.u32IndexBuffSize = stHK_MP4.u32IndexBuffSize; // video index info size
    g_stDemuxer.u8KeyIdxSize = stHK_MP4.u8KeyIdxSize;
    g_stDemuxer.u32KeyIdxPeriod = stHK_MP4.u32KeyIdxPeriod;
    VDPLAYER_DBG(printf ("video index table size %d, key size %d\n", g_stDemuxer.stDataBuffer.u32IndexBuffSize, g_stDemuxer.u8KeyIdxSize));

    g_stDemuxer.stBitsContent.u8Nb_AudioTracks = stHK_MP4.u8Nb_AudioTracks;
    memcpy(g_stDemuxer.u8AudioTrackIDMap, stHK_MP4.u8AudioTrackIDMap, MAX_AUDIO_TRACKS * sizeof(U8));
    U32 i = 0;
    for (i = 0; i < MAX_AUDIO_TRACKS; i++)
    {
        g_stDemuxer.u32AudioKeyBufAddr[i] = _PA2VA(stHK_MP4.u32AudioKeyBufAddr[i]); // audio index info address
        g_stDemuxer.u32AudioKeyBufSize[i] = stHK_MP4.u32AudioKeyBufSize[i]; // audio index info size
        VDPLAYER_DBG(printf ("audio index table size %d, key size %d, track %d, stream %d\n", g_stDemuxer.u32AudioKeyBufSize[i], stHK_MP4.u8AudioKeyIdxSize, i, g_stDemuxer.u8AudioTrackIDMap[i]));
    }
    g_stDemuxer.u8AudioKeyIdxSize = stHK_MP4.u8AudioKeyIdxSize;
    g_stDemuxer.u32AudioKeyIdxPeriod = stHK_MP4.u32AudioKeyIdxPeriod;
#if ENABLE_HK_SUBTITLE
        memcpy(g_stDemuxer.u8SubtitleTrackIDMap, stHK_MP4.u8SubtitleTrackIDMap, MAX_SUBTITLE_TRACKS * sizeof(U8));
        for (i = 0; i < MAX_SUBTITLE_TRACKS; i++)
        {
            g_stDemuxer.u32SubKeyBufAddr[i] = _PA2VA(stHK_MP4.u32SubtitleKeyBufAddr[i]); // Subtitle index info address
            g_stDemuxer.u32SubKeyBufSize[i] = stHK_MP4.u32SubtitleKeyBufSize; // Subtitle index info size
            VDPLAYER_DBG(printf ("Subtitle index table addr: 0x%x size %d, key size %d, track %d, stream %d\n",
                (unsigned int)g_stDemuxer.u32SubKeyBufAddr[i],
                (int)g_stDemuxer.u32SubKeyBufSize[i], stHK_MP4.u8SubtitleKeyIdxSize,
                (int)i, g_stDemuxer.u8SubtitleTrackIDMap[i]));
        }

        if (stHK_MP4.u8SubtitleKeyIdxSize != sizeof(SubtitleMP4PTSEntry))
        {
            VDPLAYER_ERROR("Error: subtitle index size is not identical!!!\n");
        }
        g_stDemuxer.u8SubtitleKeyIdxSize = stHK_MP4.u8SubtitleKeyIdxSize;
#endif // #if ENABLE_HK_SUBTITLE
    // parse a/v index table and return back a/v index total size to co-processor
    MApp_VDPlayer_MP4ScanIndex(stMP4.mp4Inst, &stHK_MP4);

    stHK_MP4.u32Video_IdxSize = g_stDemuxer.u32Video_IdxSize;
    stHK_MP4.u32FirstVideoKeyFramePTS = g_stDemuxer.u32FirstVideoKeyFramePTS;
    stHK_MP4.u32lastVideoKeyFramePTS = g_stDemuxer.u32lastVideoKeyFramePTS;
    memcpy(stHK_MP4.u32Audio_IdxSize, g_stDemuxer.u32Audio_IdxSize, MAX_AUDIO_TRACKS * sizeof(U32));

#if ENABLE_HK_SUBTITLE
        for (i = 0; i < stHK_MP4.u8Nb_SubtitleTracks; i++)
        {
            stHK_MP4.u32TotalPictures[i] = g_stDemuxer.u32TotalPictures[i];
            VDPLAYER_DBG(printf ("Subtitle track %d, total pictures %d\n",
                (int)i, (int)g_stDemuxer.u32TotalPictures[i]));
        }
#endif // #if ENABLE_HK_SUBTITLE

    // update index info to co-processor
    memcpy((void*)u32Addr, (const void*)&stHK_MP4, sizeof(ST_HK_MP4));
    MsOS_FlushMemory();
}

// return MP4_INVALID_FRAME_IDX for error case, base of sample_id is 1
static uint32_t MApp_VDPlayer_MP4_GetAudioFrameIdxFromIdxTable(void *mp4Inst, U8 stream_id, U32 sample_id)
{
    int ret, forward_scan;
    uint32_t frameidx = 0;
    U32 i;
    U8 vdplayer_track_id;
    cb_fpos offset;
    uint32_t size;
    ST_VDP_DEMUX_AUDIO_KEYINDEX stAudioKeyIdx;

    memset(&stAudioKeyIdx, 0, sizeof(stAudioKeyIdx));

    ret = MApp_VDPlayer_MP4_SetTrack_By_StreamID(mp4Inst, MVC_STREAM_AUDIO, stream_id);
    if (ret == FALSE)
    {
        VDPLAYER_DBG(printf("%s set track to stream %d fail\n", __FUNCTION__, stream_id));
        return MP4_INVALID_FRAME_IDX;
    }

    // find track id correponding to stream_id
    for (vdplayer_track_id = 0; vdplayer_track_id < MAX_AUDIO_TRACKS; vdplayer_track_id++)
    {
        if (stream_id == g_stDemuxer.u8AudioTrackIDMap[vdplayer_track_id])
            break;
    }

    VDPLAYER_DBG(printf("%s, stream %d, track id %d, sample id %d\n", __FUNCTION__, stream_id, vdplayer_track_id, sample_id));

    if (vdplayer_track_id == MAX_AUDIO_TRACKS)
    {
        VDPLAYER_DBG(printf("%s, can't find track for stream %d\n", __FUNCTION__, stream_id));
    }
    else
    {
        // sample id is the same as frame index for unpacked audio
        if (stMP4.audio_pack_type[vdplayer_track_id] == E_MP4_PACK_TYPE_UNPACKED)
            return sample_id;

        if (g_stDemuxer.u8AudioKeyIdxSize == 0)
        {
            return MP4_INVALID_FRAME_IDX;
        }
        // use index table for target track to find the entry with the same sample_id
        for (i = 0; i < g_stDemuxer.u32Audio_IdxSize[vdplayer_track_id] / g_stDemuxer.u8AudioKeyIdxSize; i++)
        {
            // get file offset/pts of target frame
            stAudioKeyIdx.u32Frm_Info_Idx = MP4_INVALID_FRAME_IDX;
            msAPI_VDPlayer_Demuxer_GetAudioKeyIdx(vdplayer_track_id, i, &stAudioKeyIdx);
            if (stAudioKeyIdx.u32Frm_Info_Idx == sample_id)
                break;
        }

        // use the pts of target index sample to find frame index
        if (i != g_stDemuxer.u32Audio_IdxSize[vdplayer_track_id] / g_stDemuxer.u8AudioKeyIdxSize)
            ret = MP4DMX_GetAudioIdx(mp4Inst, stAudioKeyIdx.u32Pts, &frameidx);
        else
            ret = MSMERR_FALSE;

        if (ret == MSMERR_OK)
            ret = MP4DMX_ReadSampleInfo(mp4Inst, frameidx, &offset, &size, 0, 0, 0, MVC_STREAM_AUDIO);
        if (ret == MSMERR_OK)
        {
            // file offset must match the one in index table
            if (offset == stAudioKeyIdx.u64Offset)
                return frameidx;
            if (offset > stAudioKeyIdx.u64Offset)
                forward_scan = 0;
            else
                forward_scan = 1;

            while (1)
            {
                if (forward_scan)
                    frameidx++;
                else
                    frameidx--;
                ret = MP4DMX_ReadSampleInfo(mp4Inst,
                                           frameidx,
                                            &offset,
                                              &size,
                                                  0,
                                                  0,
                                                  0,
                                   MVC_STREAM_AUDIO);
                VDPLAYER_DBG(printf ("[MP4] audio index %d, offset %llx, target offset %llx, forward %d\n", frameidx, offset, stAudioKeyIdx.u64Offset, forward_scan));
                if (ret != MSMERR_OK)
                    break;
                if (offset == stAudioKeyIdx.u64Offset)
                    return frameidx;
                // error handling if we can't get exact the same offset
                if ((forward_scan == 1 && offset > stAudioKeyIdx.u64Offset) ||
                    (forward_scan == 0 && offset < stAudioKeyIdx.u64Offset))
                    return frameidx;
            }
        }
    }

    // can't find index matches sample_id, get the frame index of sample_id-th sample
    VDPLAYER_DBG(printf ("[MP4] scan audio index to %d sample\n", sample_id));
    frameidx = 1;
    for (i = 1; i < sample_id; i++)
    {
        ret = MP4DMX_ReadSampleInfo(mp4Inst,
                                   frameidx,
                                    &offset,
                                      &size,
                                          0,
                                          0,
                                          0,
                           MVC_STREAM_AUDIO);
        if (ret != MSMERR_OK)
            break;

        frameidx += MP4DMX_GetAudioIdxGap(mp4Inst, size);
    }

    if (i == sample_id)
        return frameidx;
    else
        return MP4_INVALID_FRAME_IDX;
}

// frame index MP4_INVALID_FRAME_IDX will cause parsing end
static uint32_t MApp_VDPlayer_MP4_GetFrameIdx(void *mp4Inst, mvc_stream_type_et type, U8 stream_id, U32 sample_id)
{
    if (type != MVC_STREAM_AUDIO)
        return sample_id;

    VDPLAYER_DBG(printf("last_a (stream %d, sample %d, f_index %d, gap %d), target (id %d stream %d)\n", stMP4.last_audio.stream_id, stMP4.last_audio.sample_id, stMP4.last_audio.frame_index, stMP4.last_audio.index_gap, sample_id, stream_id));

    if (stMP4.last_audio.stream_id == stream_id)
    {
    if (sample_id == stMP4.last_audio.sample_id)
        return stMP4.last_audio.frame_index;
    else if (stMP4.last_audio.index_gap != MP4_INVALID_IDX_GAP && sample_id == stMP4.last_audio.sample_id + 1)
        return stMP4.last_audio.frame_index + stMP4.last_audio.index_gap;
    }
    if (g_stDemuxer.u8AudioKeyIdxSize == 0)
    {
        return sample_id;
    }
    return MApp_VDPlayer_MP4_GetAudioFrameIdxFromIdxTable(mp4Inst, stream_id, sample_id);
}

static uint32_t MApp_VDPlayer_MP4_UpdateFrameIdx(mvc_stream_type_et type, U8 stream_id, U32 sample_id, uint32_t frameidx, uint32_t frame_size)
{
    if (type == MVC_STREAM_AUDIO)
    {
        stMP4.last_audio.frame_index = frameidx;
        stMP4.last_audio.index_gap = MP4DMX_GetAudioIdxGap(stMP4.mp4Inst, frame_size);
        stMP4.last_audio.sample_id = sample_id;
        stMP4.last_audio.stream_id = stream_id;
        return frameidx + stMP4.last_audio.index_gap;
    }
    else
        return frameidx + 1;
}

// get enMediaType sample from u32SampleIndex until u32MaxSampleCount or timeout
static void MApp_VDPlayer_MP4_UpdateSampleTable(ST_SAMPLE_TABLE_INFO *table_info)
{
    MP4SampleInfo sample_info;
    int ret, table_idx, parsing_done;
    mvc_stream_type_et type_from_table;
    U32 table_size;
    U8 *table_addr;
    cb_fpos offset;
    uint32_t size;
    uint64_t pts, duration;
    U32 t1, t2;
    uint32_t frameidx; // corresponding to frames in mp4 track

    t1 = msAPI_Timer_GetTime0();

    ret = MApp_VDPlyer_MP4_Get_Sample_Table_Idx(table_info->type, &table_idx, &type_from_table);
    if (ret == -1)
    {
        VDPLAYER_DBG(printf("%s get sample index fail, %d\n", __FUNCTION__, table_info->type));
        MApp_VDPlayer_MP4_GetSampleInfoDone(table_info->type, table_info->table_idx);
        return;
    }

    ret = MApp_VDPlayer_MP4_SetTrack_By_StreamID(stMP4.mp4Inst, type_from_table, table_info->stream_id);
    if (ret == FALSE)
    {
        VDPLAYER_DBG(printf("%s set track to stream %d fail\n", __FUNCTION__, table_info->stream_id));
        MApp_VDPlayer_MP4_GetSampleInfoDone(table_info->type, table_info->table_idx);
        return;
    }
    table_addr = (U8 *)g_stDemuxer.stDataBuffer.u32SampleInfoAddr[table_idx];
    table_size = g_stDemuxer.stDataBuffer.u32SampleInfoLen[table_idx];

    if (table_size / sizeof(MP4SampleInfo) < table_info->max_count)
        table_info->max_count = table_size / sizeof(MP4SampleInfo);

    frameidx = MApp_VDPlayer_MP4_GetFrameIdx(stMP4.mp4Inst, type_from_table, table_info->stream_id, table_info->sample_index);
    while (1)
    {
        sample_info.u32StreamID = table_info->stream_id;
        ret = MP4DMX_ReadSampleInfo(stMP4.mp4Inst, frameidx, &offset, &size, &pts, &duration, 0, type_from_table);
        if (ret == MSMERR_OK)
        {
            sample_info.u32Index    = table_info->sample_index;
            sample_info.u32Size     = size;
            sample_info.u32PTS      = pts;
            sample_info.u64Offset   = offset;
        }
        else
        {
            sample_info.u32Index    = U32_MAX;
            sample_info.u32Size     = 0;
            sample_info.u32PTS      = 0;
            sample_info.u64Offset   = 0;
        }
        memcpy(table_addr + table_info->table_idx * sizeof(MP4SampleInfo), &sample_info, sizeof(sample_info));
        table_info->table_idx++; // update table index to the number of samples
        parsing_done = (table_info->table_idx == table_info->max_count || sample_info.u32Index == U32_MAX);
        t2 = msAPI_Timer_GetTime0();
        if (parsing_done)
            break;

        frameidx = MApp_VDPlayer_MP4_UpdateFrameIdx(type_from_table,
                                                    table_info->stream_id,
                                                    table_info->sample_index,
                                                    frameidx,
                                                    size);
        // need to update sample index after update frame index since we need to save
        // last sample index/frame index/frame size in MApp_VDPlayer_MP4_UpdateFrameIdx
            table_info->sample_index++;
        if (t2 - t1 > MP4_UPDATE_SAMPLE_THRESHOLD)
        {
            parsing_done = 1;
            break;
        }
    }
    VDPLAYER_DBG(printf("%s time %d, type %d, done %d, table idx %d\n", __FUNCTION__, t2 - t1, table_info->type, parsing_done, table_info->table_idx));
    if (parsing_done)
    {
        table_info->parsing = 0;
        MApp_VDPlayer_MP4_GetSampleInfoDone(table_info->type, table_info->table_idx);
    }
}

static void MApp_VDPlayer_MP4_StartGetSampleInfo(EN_MOV_MEDIA_TYPE enMediaType, U8 u8StreamID, U32 u32SampleIndex, U32 u32MaxSampleCount)
{
    stMP4.table_info[enMediaType].max_count    = u32MaxSampleCount;
    stMP4.table_info[enMediaType].stream_id    = u8StreamID;
    stMP4.table_info[enMediaType].type         = enMediaType;
    stMP4.table_info[enMediaType].sample_index = u32SampleIndex;
    if (stMP4.table_info[enMediaType].parsing)
    {
        printf("%s, error...media type %d, update a table in parsing state\n", __FUNCTION__, enMediaType);
        __ASSERT(0);
    }
    stMP4.table_info[enMediaType].parsing = 1;
    stMP4.table_info[enMediaType].table_idx = 0;;
}

static void MApp_VDPlayer_MP4_GetSampleInfoDone(EN_MOV_MEDIA_TYPE enMediaType, U32 u32SampleCount)
{
    MsOS_FlushMemory();
    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,6
    /*p1*/              ,MB_VDPLAYER_MP4_GET_SAMPLE
    /*p2*/              ,enMediaType
    /*p3*/              ,GetByte3(u32SampleCount)
    /*p4*/              ,GetByte2(u32SampleCount)
    /*p5*/              ,GetByte1(u32SampleCount)
    /*p6*/              ,GetByte0(u32SampleCount)
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

// stop parsing video sample info
static void MApp_VDPlayer_MP4_ClearVideoSampleInfo(void)
{
    reset_mp4_video_table_info(&stMP4);
}

// stop parsing audio sample info
static void MApp_VDPlayer_MP4_ClearAudioSampleInfo(void)
{
    reset_mp4_audio_table_info(&stMP4);
}

#endif
#endif //ENABLE_HK_AVI
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if ENABLE_POWERON_VIDEO
static FN_DATA_STRM_IO StreamIOFunc;
static U8 m_u8PanStatus;
extern void MApp_ScreenMuteMonitor(SCALER_WIN eWindow);
extern void msAPI_AEON_Disable(void);
#define POWERON_VIDEO_MAX_HANDLE_NUM        4

#define POWERON_VIDEO_STEP_PLAY_DEBUG       0 //For debug, power on movie will pause at frist frame and play next frame every 3 seconds

static ST_FALSH_FILE_HANDLE_INFO m_astPowerOnHandleInfo[POWERON_VIDEO_MAX_HANDLE_NUM];

void msAPI_Pan_Set_Status(BOOLEAN status)
{
     m_u8PanStatus=status;
}

BOOLEAN msAPI_Pan_Get_Status(void)
{
      return m_u8PanStatus;
}

static U32 msAPI_Pan_StreamOpen(void *pPrivate, U8 u8OpenMode, E_DATA_STREAM_TYPE eType)
{
    VDPLAYER_DBG(printf("msAPI_Pan_StreamOpen(0x%x, %d, %d)\n", (U32)pPrivate, u8OpenMode, eType));
    UNUSED(pPrivate);
    UNUSED(u8OpenMode);
    UNUSED(eType);
    U32 u32Handle = INVALID_DATA_STREAM_HDL;
    U32 u32i;
    BOOLEAN bResult=FALSE;
    for(u32i = 0; u32i < POWERON_VIDEO_MAX_HANDLE_NUM; u32i++)
    {
        if(m_astPowerOnHandleInfo[u32i].bValid == FALSE)
        {
            u32Handle = u32i;
            break;
        }
    }

    if(u32Handle != INVALID_DATA_STREAM_HDL)
    {
        // Currently we use hard code to set the bin file
        // If the bin ID would be set by API, please refine the *pPrivate flow.
        m_astPowerOnHandleInfo[u32Handle].BinInfo.B_ID = BIN_ID_VIDEO_ON;
        msAPI_MIU_Get_BinInfo(&m_astPowerOnHandleInfo[u32Handle].BinInfo, &bResult) ;
        if (bResult == PASS)
        {
            m_astPowerOnHandleInfo[u32Handle].u32FlashReadPTR = m_astPowerOnHandleInfo[u32Handle].BinInfo.B_FAddr;
            m_astPowerOnHandleInfo[u32Handle].bValid = TRUE;
            VDPLAYER_DBG(printf("BinInfo.B_FAddr=0x%x BinInfo.B_Len=0x%x\n",m_astPowerOnHandleInfo[u32Handle].BinInfo.B_FAddr,m_astPowerOnHandleInfo[u32Handle].BinInfo.B_Len));
        }
        else
        {
            m_astPowerOnHandleInfo[u32Handle].bValid = FALSE;
            u32Handle = INVALID_DATA_STREAM_HDL;
        }
    }
    VDPLAYER_DBG(printf("msAPI_Pan_StreamOpen result = 0x%x\n",u32Handle));
    return u32Handle;
}

static BOOLEAN msAPI_Pan_StreamClose(U32 u32Hdl)
{
    VDPLAYER_DBG(printf("msAPI_Pan_StreamClose(%d)\n", u32Hdl));
    m_astPowerOnHandleInfo[u32Hdl].bValid = FALSE;
    //MDrv_Pan_Usb_Close();
    return TRUE;
}

static U32 msAPI_Pan_StreamRead(U32 u32Hdl, void *pBuffAddr, U32 u32ReqBytes)
{
    VDPLAYER_DBG(printf("msAPI_Pan_StreamRead(%d, 0x%x) u32FlashStart=0x%x\n", (U32)u32Hdl, u32ReqBytes, m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR));
    if(u32Hdl >= POWERON_VIDEO_MAX_HANDLE_NUM || m_astPowerOnHandleInfo[u32Hdl].bValid == FALSE)
    {
        return u32ReqBytes;
    }
    U32 u32FlashEnd = m_astPowerOnHandleInfo[u32Hdl].BinInfo.B_FAddr + m_astPowerOnHandleInfo[u32Hdl].BinInfo.B_Len;
    U32 u32RestSize = 0;

    if(m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR + u32ReqBytes <= u32FlashEnd)
    {
        msAPI_MIU_Copy(m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR, (U32)pBuffAddr, u32ReqBytes, MIU_FLASH2SDRAM);
        m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR += u32ReqBytes;
        u32RestSize = 0;
    }
    else
    {
        msAPI_MIU_Copy(m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR, (U32)pBuffAddr, (u32FlashEnd - m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR), MIU_FLASH2SDRAM);
        u32RestSize = u32ReqBytes-(u32FlashEnd - m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR);
        m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR = u32FlashEnd;
    }
    return u32RestSize;
}

static LongLong msAPI_Pan_StreamLength(U32 u32Hdl)
{
    LongLong u64Size;
    memset(&u64Size,0,sizeof(u64Size));
    VDPLAYER_DBG(printf("msAPI_Pan_StreamLength(%d)\n", u32Hdl));
    if(u32Hdl >= POWERON_VIDEO_MAX_HANDLE_NUM || m_astPowerOnHandleInfo[u32Hdl].bValid == FALSE)
    {
        return u64Size;
    }

    u64Size.Hi = 0;
    u64Size.Lo = m_astPowerOnHandleInfo[u32Hdl].BinInfo.B_Len;
    return u64Size;
}

static LongLong msAPI_Pan_GetPostion(U32 u32Hdl)
{
    LongLong u64Size;

    memset(&u64Size,0,sizeof(u64Size));
    if(u32Hdl >= POWERON_VIDEO_MAX_HANDLE_NUM || m_astPowerOnHandleInfo[u32Hdl].bValid == FALSE)
    {
        return u64Size;
    }
    VDPLAYER_DBG(printf("msAPI_Pan_GetPostion(0x%x)\n", m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR));

    u64Size.Hi = 0;
    u64Size.Lo = m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR - m_astPowerOnHandleInfo[u32Hdl].BinInfo.B_FAddr;

    return u64Size;

}
static BOOLEAN msAPI_Pan_FileSeek(U32 u32Hdl, LongLong u32Pos, E_DATA_STREAM_SEEK_OPTION eOption)
{
    if(u32Hdl >= POWERON_VIDEO_MAX_HANDLE_NUM || m_astPowerOnHandleInfo[u32Hdl].bValid == FALSE)
    {
        return FALSE;
    }

    VDPLAYER_DBG(printf("msAPI_Pan_FileSeek(%d) eOption=%d u32Pos.Lo=0x%x ", u32Hdl, eOption,u32Pos.Lo));
    U32 u32FlashEnd = m_astPowerOnHandleInfo[u32Hdl].BinInfo.B_FAddr + m_astPowerOnHandleInfo[u32Hdl].BinInfo.B_Len;

    if(eOption == E_DATA_STREAM_SEEK_SET)
    {
        m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR = m_astPowerOnHandleInfo[u32Hdl].BinInfo.B_FAddr + u32Pos.Lo;
    }
    else
    {
        m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR = m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR + u32Pos.Lo;
    }

    if(m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR > u32FlashEnd)
    {
        m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR = u32FlashEnd;
    }

    VDPLAYER_DBG(printf("Set u32FlashStart[%d] to 0x%x\n", u32Hdl, m_astPowerOnHandleInfo[u32Hdl].u32FlashReadPTR));

    return TRUE;
}

static BOOLEAN msAPI_Pan_Start(void)
{
    /*FileEntry PanFileEntry,*pPanFileEntry;

    pPanFileEntry=&PanFileEntry;
        pPanFileEntry->EntryType=0;
        pPanFileEntry->FileLength.Lo=0x39BEE;//0xFE0000;//0x39BEE;
        pPanFileEntry->FileLength.Hi=0;
        pPanFileEntry->EntryFileLength=0x39BEE;//0xFE0000;//0x39BEE;
        pPanFileEntry->EntrySeconds=0x3AD8B86A;//0x3ABC2648;//0x3AD8B86A;
        pPanFileEntry->EntryID[0]=0x57;//0xBE;//0x57;
        pPanFileEntry->EntryID[1]=0;//0x2C;//0;
        pPanFileEntry->EntryID[2]=0;//1;//0;
        pPanFileEntry->EntryID[3]=0;
        pPanFileEntry->EntryID[4]=0;
        pPanFileEntry->EntryID[5]=0;
        pPanFileEntry->EntryID[6]=0;
        pPanFileEntry->EntryID[7]=0;
        pPanFileEntry->EntryID_Ext[0]=2;
        pPanFileEntry->EntryID_Ext[1]=0;
        pPanFileEntry->EntryID_Ext[2]=0;
        pPanFileEntry->EntryID_Ext[3]=0;
        pPanFileEntry->EntryID_Ext[4]=0x73;//0x1C;//0x73;
        pPanFileEntry->EntryID_Ext[5]=0;
        pPanFileEntry->EntryID_Ext[6]=0;
        pPanFileEntry->EntryID_Ext[7]=0;
        pPanFileEntry->EnvironmentID=0;
        pPanFileEntry->FileSystemID=0;
        pPanFileEntry->EntryAttrib=0x20;*/
    MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_DMP, MAIN_WINDOW);
    #if( VD_PLAYER_IS_IN_CROP_CPU )
  #if defined(MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX) || defined(__AEONR2__)
    msAPI_COPRO_Init(BIN_ID_CODE_VDPLAYER,((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MM_MEM_ADR | MIU_INTERVAL) : (AEON_MM_MEM_ADR)),AEON_MM_MEM_LEN);
  #else
    msAPI_COPRO_Init(BIN_ID_CODE_VDPLAYER,((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : ( BEON_MEM_ADR)),BEON_MEM_LEN);
  #endif
    #endif
   msAPI_Pan_Set_Status(TRUE);

    U32 u32i;
    for(u32i = 0; u32i < POWERON_VIDEO_MAX_HANDLE_NUM; u32i++)
    {
        m_astPowerOnHandleInfo[u32i].bValid = FALSE;
    }
    m_bVDPlayerPowerOnVideo=TRUE;
    msAPI_DataStreamIO_OptionRegistation(NULL,E_DATA_STREAM_MODE_POWER_ON_VIDEO);
    StreamIOFunc.pfnOpen = msAPI_Pan_StreamOpen;
    StreamIOFunc.pfnClose = msAPI_Pan_StreamClose;
    StreamIOFunc.pfnRead = msAPI_Pan_StreamRead;
    StreamIOFunc.pfnSeek = msAPI_Pan_FileSeek;
    StreamIOFunc.pfnTell = msAPI_Pan_GetPostion;
    StreamIOFunc.pfnLength = msAPI_Pan_StreamLength;
    msAPI_DataStreamIO_OptionRegistation(&StreamIOFunc,E_DATA_STREAM_MODE_POWER_ON_VIDEO);
    msAPI_DataStreamIO_SetStreamMode(E_DATA_STREAM_MODE_POWER_ON_VIDEO);
    if(MApp_VDPlayer_Init(VIDEO_PLAYER_INPUT_SOURCE_MM, VIDEO_PLAYER_PLAYING_TYPE_INVALID, NULL))
   {
       MApp_VDPlayer_EnableVideoOutputFlag(ENABLE);
       if (MApp_VDPlayer_Play())
       {
            #if(POWERON_VIDEO_STEP_PLAY_DEBUG)
                if(MApp_VDPlayer_Pause())
                {
                    printf("!!!!!!!!!!!!!!!!!!!!! Pause OK !!!!!!!!!!!!!!!!!\n");
                    U32 u32WaitTimer = msAPI_Timer_GetTime0();

                    while(msAPI_Timer_DiffTimeFromNow(u32WaitTimer) < 5000)
                    {

                    }
                    printf("!!!!!!!!!!!!!!!!!!!!! Pause End !!!!!!!!!!!!!!!!!\n");
                }
            #endif
           printf("msAPI_Pan_Start play OK!\n");
           return TRUE;
       }
       else
       {
          printf("msAPI_Pan_Start play error!\n");
          return FALSE;
       }
   }
   else
   {
       printf("msAPI_Pan_Start init error!\n");
       return FALSE;
   }
}

static void msAPI_Pan_Stop(void)
{
    printf("msAPI_Pan_Stop\n");
    U32 u32i;
    for(u32i = 0; u32i < POWERON_VIDEO_MAX_HANDLE_NUM; u32i++)
    {
        m_astPowerOnHandleInfo[u32i].bValid = FALSE;
    }
    m_bVDPlayerPowerOnVideo=FALSE;
    msAPI_Pan_Set_Status(FALSE);
    MApp_VDPlayer_Stop();
    msAPI_DataStreamIO_OptionRegistation(NULL, E_DATA_STREAM_MODE_POWER_ON_VIDEO);
    msAPI_DataStreamIO_SetStreamMode(E_DATA_STREAM_MODE_BASIC);
    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_BM_STREAM_MODE, E_BM_STREAM_MODE_NORMAL);
    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_ENABLE_INTERNAL_SUBTITLE, TRUE);
    msAPI_AEON_Disable();

}
void msAPI_Pan_Task(void)
{
    U32 u32TimeMarker;

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_DURING_LIMITED_TIME_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    if( msAPI_Pan_Start())
    {
        u32TimeMarker = msAPI_Timer_GetTime0();
#if(POWERON_VIDEO_STEP_PLAY_DEBUG)
        do{
            u32TimeMarker = msAPI_Timer_GetTime0();
            msAPI_Timer_ResetWDT();
            MApi_XC_Mux_SourceMonitor(TRUE);
            MApp_ScreenMuteMonitor(MAIN_WINDOW);
            printf(">>>>>>>>>>>>>>> Stop Screen <<<<<<<<<<<<<<<<\n");
            while(msAPI_Timer_DiffTimeFromNow(u32TimeMarker) < 3000)
            {

            }
            printf("!!!!!!!!!!!!!! Next Frame !!!!!!!!!!!!!!!!!\n");
        }while(MApp_VDPlayer_SetStep());
#else
       while(MApp_VDPlayer_Main()==EXIT_VDPLAYER_DECODING)
       {
           //printf("msAPI_Pan_decoding\n");
           msAPI_Timer_ResetWDT();
           MApi_XC_Mux_SourceMonitor(TRUE);
           MApp_ScreenMuteMonitor(MAIN_WINDOW);
           if ((msAPI_Timer_GetTime0() - u32TimeMarker > 7000))
           {
              // printf("msAPI_Pan_decoding error\n");
               break;
           }
       }
#endif
    }
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_DURING_LIMITED_TIME_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    msAPI_Pan_Stop();
}
#endif

void MApp_VDPlayer_LoadBinToCrop(void)
{
#if( VD_PLAYER_IS_IN_CROP_CPU )
  #if defined(MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX) || defined(__AEONR2__) || defined(ARM_CHAKRA)
    msAPI_COPRO_Init(BIN_ID_CODE_VDPLAYER,((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MM_MEM_ADR | MIU_INTERVAL) : (AEON_MM_MEM_ADR)),AEON_MM_MEM_LEN);
  #else
    msAPI_COPRO_Init(BIN_ID_CODE_VDPLAYER,((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : ( BEON_MEM_ADR)),BEON_MEM_LEN);
  #endif
#endif
   }

//******************************************************************************
/// Set Movie Stream mode.
/// @param  bMovieStreamMode \b IN  Specify Stream mode or not.
/// @return TRUE or FALSE
//******************************************************************************
BOOL MApp_VDPlayer_SetStreamMode(BOOL bMovieStreamMode)
{
    gbStreamMode = bMovieStreamMode;

    return TRUE;
}

#if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
//************************************************************************************************
/// Get stream file handler for virtual multiple file handler.
/// Virtual multiple file handler: use one file handler to simulate multiple file handler.
/// @param  u8StrmHdlIdx \b IN  Specify Stream file handler index.
/// @param  bSeekToBackupFilePosition \b IN  Specify need to seek to backup file position or not.
/// @return always return AV file handler.
//************************************************************************************************
static U32 MApp_VDPlayer_GetStrmHandleForSimulateMultiFileHandler(U8 u8StrmHdlIdx, BOOLEAN bSeekToBackupFilePosition)
{
    U32 u32StrmHdl;

    if(gbStreamMode)//(stream mode)
    {
        u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(AV_FILE_HANDLE);

        //Xdemux will use different file handel index to read audio or video seprately but HK always use one file handle to read movie file
        //if pre file handle index != current file handle index , it needs to backup
        if(u8Pre_StrmHdlIdx != u8StrmHdlIdx)
        {
            //ftell than backup pre file handle position
            u64BackupFilePosition[u8Pre_StrmHdlIdx] = msAPI_DataStreamIO_Tell_LongLong(u32StrmHdl);
            u8Pre_StrmHdlIdx = u8StrmHdlIdx;

            if(bSeekToBackupFilePosition)
            {
                //seek to target file position using "AV_FILE_HANDLE"
                msAPI_DataStreamIO_Seek_LongLong(u32StrmHdl, u64BackupFilePosition[u8StrmHdlIdx], E_DATA_STREAM_SEEK_SET);
            }
        }
    }
    else
    {
        u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
    }
    return u32StrmHdl;
}
#endif

#if ENABLE_HK_MM
/***************************************************************************************/
/// Read file by the given file handle number, read buffer, and read length.
/// Read limit size once until exceed limit time.
/// @param -u8HandleNo \b IN: File handle number.
/// @param -pu8Buffer \b OUT: Read buffer.
/// @param -u32Length \b IN: Read length.
/// @param -u32LimitSize \b IN: size limit.
/// @param -u16LimitTime \b IN: time limit.
/// @return -Left bytes it is not able to read. If read successfully, should return 0.
/***************************************************************************************/
static U32 _MApp_VDPlyer_LimitedFileRead(U32 u32Hdl, void *pBuffAddr, U32 u32Length, U32 u32LimitSize, U16 u16LimitTime)
{
    U32 u32ReadSize;
    static U32 u32FileReadTimer=0;
    u32FileReadTimer = msAPI_Timer_GetTime0();

    while(u32Length > u32LimitSize && MsOS_Timer_DiffTimeFromNow(u32FileReadTimer) < u16LimitTime)
    {
        msAPI_DataStreamIO_Read(u32Hdl, pBuffAddr, u32LimitSize);
        pBuffAddr = (U8*)pBuffAddr + u32LimitSize;
        u32Length -= u32LimitSize;
    }
    if(MsOS_Timer_DiffTimeFromNow(u32FileReadTimer) < u16LimitTime)
    {
        u32ReadSize = msAPI_DataStreamIO_Read(u32Hdl, pBuffAddr, u32Length);
    }
    else
    {
        u32ReadSize = u32Length;
    }

    g_u32IOReadTimer += MsOS_Timer_DiffTimeFromNow(u32FileReadTimer); //for debug
    //printf("***********%dms***********\n", MsOS_Timer_DiffTimeFromNow(u32FileReadTimer));

    return u32ReadSize;
}

static void _MApp_VDPlyer_VMailboxCallback(MBX_Msg *pMsg, MS_BOOL *pbAddToQueue)
{
    U32 tmpvar = 0;
    U8 u8StrmHdlIdx;
    U32 u32StrmHdl;

    #if ENABLE_USB_READ_RATE_MEASURED
        U32 u32ReadTimer;
    #endif
    MBX_Msg MB_Message = *pMsg;

    static U32 spuqueueaddr;
    static U16 spuqueuesize;
#if (!FILE_SYSTEM_LONGLONG_API_ENABLE)
    U32 u32Offset;
#endif

    if(_gbContinueBlockRead)
    {
        //for stream mode, support blocking read
        _MApp_VDPlayer_ProcessBlockingRead();
    }

    if (MB_Message.u8MsgClass == E_MBX_CLASS_VDPLAYER)
    {
        U32 u32Addr = 0;
        U32 u32Size = 0;
        //U32 u32Offset = 0;
        U8 i;
        U32 read_size;
#if FILE_SYSTEM_LONGLONG_API_ENABLE
        LongLong u64FileSize;
        LongLong u64FileOffset;
#endif
        *pbAddToQueue = FALSE;

        switch(MB_Message.u8Index)
        {
            // MB_VDPLAYER_RET_STATE_WAIT ----------------------------------------------
            case MB_VDPLAYER_STATE_RET_WAIT:
                enVDPlayerRet = EXIT_VDPLAYER_WAIT;
            #if ENABLE_DIVX_PLUS
                g_bChangeFile = FALSE;
            #endif
                break;

            // MB_VDPLAYER_RET_STATE_EXIT ----------------------------------------------
            case MB_VDPLAYER_STATE_RET_EXIT:
                enVDPlayerRet = EXIT_VDPLAYER_EXIT;
            #if ENABLE_DIVX_PLUS
                g_bChangeFile = FALSE;
            #endif
                break;

            // MB_VDPLAYER_FILE_OPEN ----------------------------------------------
            case MB_VDPLAYER_FILE_OPEN:
                {
                    u8StrmHdlIdx = MApp_VDPlayer_GetFreeFileHandleIdx();
                    if (u8StrmHdlIdx == INVALID_HANDLE_IDX)
                    {
                        VDPLAYER_DBG(printf ("[ERROR] out of free file handle\n"));
                        return;
                    }

                    u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);

                    if (u32StrmHdl != INVALID_DATA_STREAM_HDL)
                    {
                        u64FileSize = msAPI_DataStreamIO_Length_LongLong(u32StrmHdl);
                        VDPLAYER_DVD_DBG(printf("StrmHdl[%lu], FileSize[%lu]\n", u32StrmHdl, u64FileSize.Lo));
                    }
                    else
                    {
                        u64FileSize.Hi = 0;
                        u64FileSize.Lo = 0;
                        u8StrmHdlIdx = 0xFF;
                    }

                    //==> Send mail.
            #if FILE_SYSTEM_LONGLONG_API_ENABLE
                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                    /*ParameterCount*/  ,10
                    /*p1*/              ,MB_VDPLAYER_FILE_OPEN
                    /*p2*/              ,(U8)((u64FileSize.Hi&0xFF000000)>>24)
                    /*p3*/              ,(U8)((u64FileSize.Hi&0x00FF0000)>>16)
                    /*p4*/              ,(U8)((u64FileSize.Hi&0x0000FF00)>>8)
                    /*p5*/              ,(U8)(u64FileSize.Hi&0x000000FF)
                    /*p6*/              ,(U8)((u64FileSize.Lo&0xFF000000)>>24)
                    /*p7*/              ,(U8)((u64FileSize.Lo&0x00FF0000)>>16)
                    /*p8*/              ,(U8)((u64FileSize.Lo&0x0000FF00)>>8)
                    /*p9*/              ,(U8)(u64FileSize.Lo&0x000000FF)
                    /*p10*/             ,u8StrmHdlIdx);
            #else
                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                    /*ParameterCount*/  ,10
                    /*p1*/              ,MB_VDPLAYER_FILE_OPEN
                    /*p2*/              ,0
                    /*p3*/              ,0
                    /*p4*/              ,0
                    /*p5*/              ,0
                    /*p6*/              ,(U8)((msAPI_DataStreamIO_Length(u32StrmHdl)&0xFF000000)>>24)
                    /*p7*/              ,(U8)((msAPI_DataStreamIO_Length(u32StrmHdl)&0x00FF0000)>>16)
                    /*p8*/              ,(U8)((msAPI_DataStreamIO_Length(u32StrmHdl)&0x0000FF00)>>8)
                    /*p9*/              ,(U8)(msAPI_DataStreamIO_Length(u32StrmHdl)&0x000000FF)
                    /*p10*/             ,u8StrmHdlIdx);
            #endif
                }
                break;

            // MB_VDPLAYER_FILE_READ ----------------------------------------------
            case MB_VDPLAYER_FILE_READ:
                g_bNonBlockingRead = FALSE;
                for(i=0; i<4; i++)
                {
                    u32Addr = (u32Addr<<8) | MB_Message.u8Parameters[i];
                }
//                        u32Addr = (u32Addr & 0x7FFFFFFF);
                // u32Addr = (u32Addr & 0x1FFFFFFF) | 0x80000000;

                for(i=4; i<8; i++)
                {
                    u32Size = (u32Size<<8) | MB_Message.u8Parameters[i];
                }

                u8StrmHdlIdx = MB_Message.u8Parameters[8];
                #if ENABLE_USB_READ_RATE_MEASURED
                    u32ReadTimer = msAPI_Timer_GetTime0();
                #endif
                #if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
                    u32StrmHdl = MApp_VDPlayer_GetStrmHandleForSimulateMultiFileHandler(u8StrmHdlIdx, TRUE);
                #else
                    u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                #endif
                    read_size = msAPI_DataStreamIO_Read(u32StrmHdl, (void *)u32Addr, u32Size);
                #if ENABLE_USB_READ_RATE_MEASURED
                    m_u32ReadTimeMeasured += (msAPI_Timer_DiffTimeFromNow(u32ReadTimer));
                    m_u32ReadSizeMeasured += u32Size-read_size;
                    printf("\x1b[31m" "Blocking Read: size:%d, time: %d" "\x1b[0m""\n",m_u32ReadSizeMeasured,m_u32ReadTimeMeasured);
                #endif
                #if 0//for debug
                    printf("    u32Addr=0x%lx,u32Size=%ld , read_size=%ld\n",u32Addr,u32Size,read_size);
                    u64FileOffset = msAPI_DataStreamIO_Tell_LongLong(u32StrmHdl);
                    printf("    Pos.Hi=0x%lx,Pos.Lo=%lx\n",u64FileOffset.Hi,u64FileOffset.Lo);
                #endif
                MsOS_FlushMemory();
                // __asm__ volatile ("l.msync;");
                _gu32BlockReadTimer = msAPI_Timer_GetTime0();

                if(read_size == 0)   //finish blocking read, send ack msg
                {
                    _gbContinueBlockRead = FALSE;
                    //==> Send mail.
                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                    /*ParameterCount*/  ,6
                    /*p1*/              ,MB_VDPLAYER_FILE_READ
                    /*p2*/              ,(U8)((read_size&0xFF000000)>>24)
                    /*p3*/              ,(U8)((read_size&0x00FF0000)>>16)
                    /*p4*/              ,(U8)((read_size&0x0000FF00)>>8)
                    /*p5*/              ,(U8)(read_size&0x000000FF)
                    /*p6*/              ,u8StrmHdlIdx
                    /*p7*/              ,0
                    /*p8*/              ,0
                    /*p9*/              ,0
                    /*p10*/             ,0);
                }
                else
                {
                    if ((u8StrmHdlIdx == 0) || _gbEnableInternalSubtitle)
                    {
                        u64FileSize = msAPI_DataStreamIO_Length_LongLong(u32StrmHdl);
                    }
                    else
                    {
                        u64FileSize.Hi = 0;
                        u64FileSize.Lo = 0;
                        u8StrmHdlIdx = 0xFF;
                    }

                    if(msAPI_DataStreamIO_Tell(u32StrmHdl) >= u64FileSize.Lo)
                    {
                        _gbContinueBlockRead = FALSE;
                        //==> Send mail.
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,6
                        /*p1*/              ,MB_VDPLAYER_FILE_READ
                        /*p2*/              ,(U8)((read_size&0xFF000000)>>24)
                        /*p3*/              ,(U8)((read_size&0x00FF0000)>>16)
                        /*p4*/              ,(U8)((read_size&0x0000FF00)>>8)
                        /*p5*/              ,(U8)(read_size&0x000000FF)
                        /*p6*/              ,u8StrmHdlIdx
                        /*p7*/              ,0
                        /*p8*/              ,0
                        /*p9*/              ,0
                        /*p10*/             ,0);
                    }
                    else  //need continue read in next loop
                    {
                        _gu32ResidualReadSize = read_size;
                        _gu32gStreamHdl = u32StrmHdl;
                        _gu32BuffAddr = u32Addr + u32Size - read_size;
                        _gbContinueBlockRead = TRUE;
                    }
                }
                break;


            case MB_VDPLAYER_FILE_READ_NONBLOCKING:
                g_bNonBlockingRead = TRUE;
                for(i=0; i<4; i++)
                {
                    u32Addr = (u32Addr<<8) | MB_Message.u8Parameters[i];
                }
                //u32Addr = (u32Addr & 0x7FFFFFFF); //co-processor will return PA
                // u32Addr = (u32Addr & 0x1FFFFFFF) | 0x80000000;

                for(i=4; i<8; i++)
                {
                    u32Size = (u32Size<<8) | MB_Message.u8Parameters[i];
                }

                u8StrmHdlIdx = MB_Message.u8Parameters[8];
                #if ENABLE_USB_READ_RATE_MEASURED
                    u32ReadTimer = msAPI_Timer_GetTime0();
                #endif
                #if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
                    u32StrmHdl = MApp_VDPlayer_GetStrmHandleForSimulateMultiFileHandler(u8StrmHdlIdx, TRUE);
                #else
                    u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                #endif
                    read_size = _MApp_VDPlyer_LimitedFileRead(u32StrmHdl, (void *)u32Addr, u32Size, NONBLOCKING_READ_SIZE, NONBLOCKING_READ_TIMEOUT);
                #if ENABLE_USB_READ_RATE_MEASURED
                    m_u32ReadTimeMeasured += (msAPI_Timer_DiffTimeFromNow(u32ReadTimer));
                    m_u32ReadSizeMeasured += u32Size-read_size;
                    printf("\x1b[31m" "Non-Blocking Read: size:%d, time: %d" "\x1b[0m""\n",m_u32ReadSizeMeasured,m_u32ReadTimeMeasured);
                #endif
                #if 0
                    printf("    u32Addr=0x%lx,u32Size=%ld , read_size=%ld\n",u32Addr,u32Size,read_size);
                    u64FileOffset = msAPI_DataStreamIO_Tell_LongLong(u32StrmHdl);
                    printf("    Pos.Hi=0x%lx,Pos.Lo=%lx\n",u64FileOffset.Hi,u64FileOffset.Lo);
                #endif
                MsOS_FlushMemory();
                // __asm__ volatile ("l.msync;");
                //==> Send mail.
                VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
                /*Index*/           ,MB_VDPLAYER_FILE_READ_NONBLOCKING_DONE
                /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                /*ParameterCount*/  ,5
                /*p1*/              ,(U8)((read_size&0xFF000000)>>24)
                /*p2*/              ,(U8)((read_size&0x00FF0000)>>16)
                /*p3*/              ,(U8)((read_size&0x0000FF00)>>8)
                /*p4*/              ,(U8)(read_size&0x000000FF)
                /*p5*/              ,u8StrmHdlIdx
                /*p6*/              ,0
                /*p7*/              ,0
                /*p8*/              ,0
                /*p9*/              ,0
                /*p10*/             ,0);
                break;
    #if ENABLE_HK_AVI
            case MB_VDPLAYER_AVI_SCAN_INDEX:
                {
                    BOOL bRet;
                    U8 u8FileHdl = MB_Message.u8Parameters[0];
                    bRet = MApp_VDPlayer_AVIScanIndex(u8FileHdl);
                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                    /*ParameterCount*/  ,2
                    /*p1*/              ,MB_VDPLAYER_AVI_SCAN_INDEX
                    /*p2*/              ,bRet
                    /*p3*/              ,0
                    /*p4*/              ,0
                    /*p5*/              ,0
                    /*p6*/              ,0
                    /*p7*/              ,0
                    /*p8*/              ,0
                    /*p9*/              ,0
                    /*p10*/             ,0);
                }
                break;
    #endif

            // MB_VDPLAYER_FILE_SEEK ----------------------------------------------
            case MB_VDPLAYER_FILE_SEEK:
                _bStreamSeeked = TRUE;
                g_bNonBlockingSeek = FALSE;
#if FILE_SYSTEM_LONGLONG_API_ENABLE
                u64FileOffset.Hi = 0;
                u64FileOffset.Lo = 0;
                for(i=0; i<4; i++)
                {
                    u64FileOffset.Hi = (u64FileOffset.Hi<<8) | MB_Message.u8Parameters[i];
                }
                for(i=4; i<8; i++)
                {
                    u64FileOffset.Lo = (u64FileOffset.Lo<<8) | MB_Message.u8Parameters[i];
                }

                u8StrmHdlIdx = MB_Message.u8Parameters[8];
            #if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
                u32StrmHdl = MApp_VDPlayer_GetStrmHandleForSimulateMultiFileHandler(u8StrmHdlIdx, FALSE);
            #else
                u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
            #endif
                msAPI_DataStreamIO_Seek_LongLong(u32StrmHdl, u64FileOffset, E_DATA_STREAM_SEEK_SET);
#else
                for(i=4; i<8; i++)
                {
                    u32Offset = (u32Offset<<8) |MB_Message.u8Parameters[i];
                }

                u8StrmHdlIdx = MB_Message.u8Parameters[8];
                u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                msAPI_DataStreamIO_Seek(u32StrmHdl, u32Offset, E_DATA_STREAM_SEEK_SET);
#endif
                //==> Send mail.
                VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                /*ParameterCount*/  ,2
                /*p1*/              ,MB_VDPLAYER_FILE_SEEK
                /*p2*/              ,u8StrmHdlIdx
                /*p3*/              ,0
                /*p4*/              ,0
                /*p5*/              ,0
                /*p6*/              ,0
                /*p7*/              ,0
                /*p8*/              ,0
                /*p9*/              ,0
                /*p10*/             ,0);
                break;

            // MB_VDPLAYER_FILE_SEEK_NONBLOCKING ----------------------------------------------
            case MB_VDPLAYER_FILE_SEEK_NONBLOCKING:
                g_bNonBlockingSeek = TRUE;
#if FILE_SYSTEM_LONGLONG_API_ENABLE
                u64FileOffset.Hi = 0;
                u64FileOffset.Lo = 0;
                for(i=0; i<4; i++)
                {
                    u64FileOffset.Hi = (u64FileOffset.Hi<<8) | MB_Message.u8Parameters[i];
                }
                for(i=4; i<8; i++)
                {
                    u64FileOffset.Lo = (u64FileOffset.Lo<<8) | MB_Message.u8Parameters[i];
                }

                u8StrmHdlIdx = MB_Message.u8Parameters[8];
            #if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
                u32StrmHdl = MApp_VDPlayer_GetStrmHandleForSimulateMultiFileHandler(u8StrmHdlIdx, FALSE);
            #else
                u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
            #endif
                msAPI_DataStreamIO_Seek_LongLong(u32StrmHdl, u64FileOffset, E_DATA_STREAM_SEEK_SET);
#else
                for(i=4; i<8; i++)
                {
                    u32Offset = (u32Offset<<8) | MB_Message.u8Parameters[i];
                }
                u8StrmHdlIdx = MB_Message.u8Parameters[8];
                u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
                msAPI_DataStreamIO_Seek(u32StrmHdl, u32Offset, E_DATA_STREAM_SEEK_SET);
#endif
                //==> Send mail.
                VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER_FS
                /*Index*/           ,MB_VDPLAYER_FILE_SEEK_NONBLOCKING_DONE
                /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                /*ParameterCount*/  ,1
                /*p1*/              ,u8StrmHdlIdx
                /*p2*/              ,0
                /*p3*/              ,0
                /*p4*/              ,0
                /*p5*/              ,0
                /*p6*/              ,0
                /*p7*/              ,0
                /*p8*/              ,0
                /*p9*/              ,0
                /*p10*/             ,0);
                break;

#ifdef _VDPLAYER_DUMP_RAW_
            // MB_VDPLAYER_FILE_DUMP_RAW ----------------------------------------------
            case MB_VDPLAYER_FILE_DUMP_RAW:
                {
                    U32 u32Buffer = VDPLAYER_DUMP_RAW_ADR;

                    U8 idx = MB_Message.u8Parameters[0];
                    for(i=1; i<5; i++)
                    {
                        u32Size = (u32Size<<8) | MB_Message.u8Parameters[i];
                    }
                    //printf ("src %lX, dst %lX, size %lX\n", VDEC_FRAMEBUFFER_ADR + u32Size*idx, u32Buffer, u32Size);
                    msAPI_MIU_Copy(VDEC_FRAMEBUFFER_ADR + u32Size*idx, u32Buffer, u32Size, MIU_SDRAM12SDRAM0);
                    msAPI_FCtrl_FileWrite(VDPlayer_dump_id, u32Buffer, u32Size);

                    //==> Send mail.
                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                    /*ParameterCount*/  ,1
                    /*p1*/              ,MB_VDPLAYER_FILE_DUMP_RAW
                    /*p2*/              ,0
                    /*p3*/              ,0
                    /*p4*/              ,0
                    /*p5*/              ,0
                    /*p6*/              ,0
                    /*p7*/              ,0
                    /*p8*/              ,0
                    /*p9*/              ,0
                    /*p10*/             ,0);
                }
                break;
#endif // _VDPLAYER_DUMP_RAW_

            // MB_VDPLAYER_FILE_CLOSE ----------------------------------------------
            case MB_VDPLAYER_FILE_CLOSE:
                u32StrmHdl = MB_Message.u8Parameters[0];
                MApp_VDPlayer_ReleaseStrmHandleByIdx(u32StrmHdl);

#if ENABLE_NEW_FILE_HANDLER
                U8 u8Idx;
                for (u8Idx=0; u8Idx<TotalHandlerCnt; u8Idx++)
                {
                    if (u32StreamHandleIdx[u8Idx] != INVALID_DATA_STREAM_HDL)
                    {
                        msAPI_DataStreamIO_Close(u32StreamHandleIdx[u8Idx]);
                        u32StreamHandleIdx[u8Idx] = INVALID_DATA_STREAM_HDL;
                    }
                }
#else //ENABLE_NEW_FILE_HANDLER
                if (u32VDPlayerStreamHandleIdx_Video != INVALID_DATA_STREAM_HDL)
                {
                    msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Video);
                    u32VDPlayerStreamHandleIdx_Video = INVALID_DATA_STREAM_HDL;
                }

                if(u32VDPlayerStreamHandleIdx_Subtitle != INVALID_DATA_STREAM_HDL)
                {
                    msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Subtitle);
                    u32VDPlayerStreamHandleIdx_Subtitle = INVALID_DATA_STREAM_HDL;
                }

#if ENABLE_AUDIO_HANDLER
                if(u32VDPlayerStreamHandleIdx_Audio != INVALID_DATA_STREAM_HDL)
                {
                    msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Audio);
                    u32VDPlayerStreamHandleIdx_Audio = INVALID_DATA_STREAM_HDL;
                }
#endif
#if ENABLE_ATTACHMENT_HANDLER
                if(u32VDPlayerStreamHandleIdx_Attachment != INVALID_DATA_STREAM_HDL)
                {
                    msAPI_DataStreamIO_Close(u32VDPlayerStreamHandleIdx_Attachment);
                    u32VDPlayerStreamHandleIdx_Attachment = INVALID_DATA_STREAM_HDL;
                }
#endif

#endif

#ifdef _VDPLAYER_DUMP_RAW_
                if(VDPlayer_dump_id != INVALID_FILE_HANDLE)
                {
                    msAPI_FCtrl_FileClose(VDPlayer_dump_id);
                    VDPlayer_dump_id = INVALID_FILE_HANDLE;
                }
#endif // _VDPLAYER_DUMP_RAW_
                break;

            // MB_VDPLAYER_AUDIO_START ----------------------------------------------
            case MB_VDPLAYER_AUDIO_START:
                printf("**************HK - MB_VDPLAYER_AUDIO_START***************\n");
                if( (MB_Message.u8Parameters[0] == 1))
                {
                    /// Enable Audio parser to play TS-stream
                    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILETSP);
                }
                else
                {
                    //msAPI_Music_StartDecode();
                    msAPI_Music_StartDecodeEnhance((_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_NEW_AUDIO_MM_MODE)));
                }
#if  AUDIO_SPDIF_ENABLE
                if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                {
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                }
                else if(stGenSetting.g_SysSetting.fSPDIFMODE == 1)
                {
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
                }
#endif
                if (g_b2ndRunPreviewMute ==  TRUE)
                {
                    // patch dolphin.flv preview 2nd run video black screen but audio has sound.
                    // 2nd run black screen is disable by mplayer, but audio start mute control by
                    // videoplayer. Use this variable to control mute and unmute by mplayer value.
                    //printf("preview 2nd run audio mute\n");
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }
                else
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }

                //==> Send mail.
                VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                /*ParameterCount*/  ,1
                /*p1*/              ,MB_VDPLAYER_AUDIO_INIT
                /*p2*/              ,0
                /*p3*/              ,0
                /*p4*/              ,0
                /*p5*/              ,0
                /*p6*/              ,0
                /*p7*/              ,0
                /*p8*/              ,0
                /*p9*/              ,0
                /*p10*/             ,0);
                break;

            // MB_VDPLAYER_AUDIO_INIT ----------------------------------------------
            case MB_VDPLAYER_AUDIO_INIT:
                printf("*************HK - MB_VDPLAYER_AUDIO_INIT**************");
                tmpvar = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_CODEC_ID);

                switch (tmpvar)
                {
                    case E_VDP_CODEC_ID_WMAV1:
                    case E_VDP_CODEC_ID_WMAV2:
                        msAPI_Music_Init(MSAPI_AUD_DVB_WMA, INIT_VOLUME);
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_PARSINGBYAPP, 0x1);
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_VERSION, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_VERSION));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_CHANNELS, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_CHANNELS));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_SAMPLERATE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_SAMPLERATE));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BYTERATE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_BYTERATE));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BLOCKALIGN, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_BLOCKALIGN));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_ENCOPT, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_ENCODEOPT));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_MAX_PACKET_SIZE, 0);
                        break;

                    case E_VDP_CODEC_ID_WMAV3:
                        msAPI_Music_Init(MSAPI_AUD_DVB_WMA_PRO, INIT_VOLUME);
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_PARSINGBYAPP, 0x1);
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_VERSION, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_VERSION));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_CHANNELS, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_CHANNELS));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_SAMPLERATE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_SAMPLERATE));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BYTERATE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_BYTERATE));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BLOCKALIGN, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_BLOCKALIGN));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_ENCOPT, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_ENCODEOPT));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_MAX_PACKET_SIZE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_ADVANCE_ENCODEOPT)); //check if wma lbr
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BITS_PER_SAMPLE, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_BIT_PER_SAMPLE));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_CHANNELMASK, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_CHANNEL_MASK));
                        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_PARAM_EXIST, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_PARAM_EXIST));
                        if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_PARAM_EXIST))
                        {
                            msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_PEAK_AMP_REF, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_PEEK_REF));
                            msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_PEAK_AMP_TARGET, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_PEEK_TARGET));
                            msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_RMS_AMP_REF, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_AVE_REF));
                            msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_RMS_AMP_TARGET, _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMA_DRC_AVE_TARGET));
                        }
                        break;

                    case E_VDP_CODEC_ID_DTS:
                    case E_VDP_CODEC_ID_DTS_HD:
                        msAPI_Music_Init(MSAPI_AUD_DVB_DTS, INIT_VOLUME);
                       break;

                    case E_VDP_CODEC_ID_MP3:
                        msAPI_Music_Init(MSAPI_AUD_DVB_MP3, INIT_VOLUME);
                        if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_Audio_Request_Size) == E_VDP_AUDIO_REQUIRE_SIZE_1KB)
                            MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_1KB, 0);
                        else if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_Audio_Request_Size) == E_VDP_AUDIO_REQUIRE_SIZE_2KB)
                            MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_2KB, 0);
                        else
                            MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_4KB, 0);
                        break;
                    case E_VDP_CODEC_ID_MP2:
                        msAPI_Music_Init(MSAPI_AUD_DVB_MPEG, INIT_VOLUME);
                        if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_Audio_Request_Size) == E_VDP_AUDIO_REQUIRE_SIZE_1KB)
                            MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_1KB, 0);
                        else if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_Audio_Request_Size) == E_VDP_AUDIO_REQUIRE_SIZE_2KB)
                            MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_2KB, 0);
                        else
                            MApi_AUDIO_SetMpegInfo(Audio_MPEG_infoType_MMFileSize, FILE_SIZE_4KB, 0);
                        break;
                    case E_VDP_CODEC_ID_AC3:
                    case E_VDP_CODEC_ID_EAC3:
                        msAPI_Music_Init(MSAPI_AUD_DVB_AC3P, INIT_VOLUME);
                        if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_Audio_Request_Size))
                        {
                            msAPI_Music_StopDecode();
                            MApi_AUDIO_SetAC3PInfo(Audio_AC3P_infoType_MMFileSize, FILE_SIZE_16KB, 0);
                        }
                        break;
                    case E_VDP_CODEC_ID_AAC:
                    case E_VDP_CODEC_ID_MPEG4AAC:
                        msAPI_Music_Init(MSAPI_AUD_DVB_AAC, INIT_VOLUME);
                        break;

                    case E_VDP_CODEC_ID_FLAC:
                        msAPI_Music_Init(MSAPI_AUD_DVB_FLAC, INIT_VOLUME);
                        break;

                    case E_VDP_CODEC_ID_PCM_S16LE:
                    case E_VDP_CODEC_ID_PCM_S16BE:
                    case E_VDP_CODEC_ID_PCM_U16LE:
                    case E_VDP_CODEC_ID_PCM_U16BE:
                    case E_VDP_CODEC_ID_PCM_S8:
                    case E_VDP_CODEC_ID_PCM_U8:
                    case E_VDP_CODEC_ID_PCM_MULAW:
                    case E_VDP_CODEC_ID_PCM_ALAW:
                        {
                            U32 u32SampleRate;
                            U16 u16BitsPerSample;
                            U8 u8CannelNumber;
                            U32    tmpvartemp=tmpvar;
                            u32SampleRate  = (((U32)MB_Message.u8Parameters[1]<<8)&0xFF00) |
                                             (((U32)MB_Message.u8Parameters[2])&0x00FF);

                            u16BitsPerSample  = (((U16)MB_Message.u8Parameters[3]<<8)&0xFF00) |
                                                (((U16)MB_Message.u8Parameters[4])&0x00FF);

                            u8CannelNumber  = ((U16)(MB_Message.u8Parameters[5])&0x00FF);

                            if (tmpvar == E_VDP_CODEC_ID_PCM_U16BE || tmpvar == E_VDP_CODEC_ID_PCM_S16BE ||
                                 tmpvar == E_VDP_CODEC_ID_PCM_ALAW || tmpvar == E_VDP_CODEC_ID_PCM_MULAW)
                            {
                                tmpvar = 0xFF;
                            }
                            else
                            {
                                tmpvar = 0;
                            }

                            msAPI_Music_Init(MSAPI_AUD_DVB_XPCM, INIT_VOLUME);
                            if(tmpvartemp==E_VDP_CODEC_ID_PCM_MULAW)
                            {
                                MApi_AUDIO_XPCM_Param(G711_u_LAW, u8CannelNumber - 1, u32SampleRate, u16BitsPerSample,0, tmpvar);
                            }
                            else if(tmpvartemp==E_VDP_CODEC_ID_PCM_ALAW)
                            {
                                MApi_AUDIO_XPCM_Param(G711_A_LAW, u8CannelNumber - 1, u32SampleRate, u16BitsPerSample,0, tmpvar);
                            }
                            else
                            {
                                MApi_AUDIO_XPCM_Param(LPCM, u8CannelNumber - 1, u32SampleRate, u16BitsPerSample,0, tmpvar);
                            }
                        }
                        break;

                    case E_VDP_CODEC_ID_ADPCM_IMA_QT:
                    case E_VDP_CODEC_ID_ADPCM_IMA_WAV:
                    case E_VDP_CODEC_ID_ADPCM_IMA_DK3:
                    case E_VDP_CODEC_ID_ADPCM_IMA_DK4:
                    case E_VDP_CODEC_ID_ADPCM_IMA_WS:
                    case E_VDP_CODEC_ID_ADPCM_IMA_SMJPEG:
                    case E_VDP_CODEC_ID_ADPCM_MS:
                    case E_VDP_CODEC_ID_ADPCM_4XM:
                    case E_VDP_CODEC_ID_ADPCM_XA:
                    case E_VDP_CODEC_ID_ADPCM_ADX:
                    case E_VDP_CODEC_ID_ADPCM_EA:
                    case E_VDP_CODEC_ID_ADPCM_G726:
                        {
                            U32 u32SampleRate;
                            U16 u16BitsPerSample;
                            U8 u8CannelNumber;
                            U16 u16BlockSize;
                            U16 u16SamplePerBlock;
                            u32SampleRate  = (((U32)MB_Message.u8Parameters[1]<<8)&0xFF00) |
                                                            (((U32)MB_Message.u8Parameters[2])&0x00FF);

                            u16BitsPerSample  = (((U16)MB_Message.u8Parameters[3]<<8)&0xFF00) |
                                                                (((U16)MB_Message.u8Parameters[4])&0x00FF);

                            u8CannelNumber  = ((MB_Message.u8Parameters[5])&0x00FF);

                            u16BlockSize  = (((U16)MB_Message.u8Parameters[6]<<8)&0xFF00) |
                                                            (((U16)MB_Message.u8Parameters[7])&0x00FF);

                            u16SamplePerBlock  = (((U16)MB_Message.u8Parameters[8]<<8)&0xFF00) |
                                                            (((U16)MB_Message.u8Parameters[9])&0x00FF);

                            if (tmpvar == E_VDP_CODEC_ID_ADPCM_MS)
                            {
                                tmpvar = MS_ADPCM;//2;
                            }
                            else
                            {
                                tmpvar = IMA_ADPCM;//17;
                            }
                            msAPI_Music_Init(MSAPI_AUD_DVB_XPCM, INIT_VOLUME);
                            MApi_AUDIO_XPCM_Param((XPCM_TYPE)tmpvar, u8CannelNumber - 1, u32SampleRate, u16BitsPerSample,u16BlockSize, u16SamplePerBlock);
                        }
                        break;

                    case E_VDP_CODEC_ID_RAAC:
                    case E_VDP_CODEC_ID_RACP:
                    {
                        U16 u16Index;
                        for(i=1; i<5; i++)
                        {
                            tmpvar = (tmpvar<<8) | MB_Message.u8Parameters[i];
                        }
                        VDPLAYER_DBG(printf("SampleRate: %lu\n", tmpvar));
                        u16Index = M4AParser_GetSampleRateIndex(tmpvar) ;
                        VDPLAYER_DBG(printf("SampleRate Index: %u\n", u16Index));

                        for(i=5; i<9; i++)
                        {
                            tmpvar = (tmpvar<<8) | MB_Message.u8Parameters[i];
                        }
                        VDPLAYER_DBG(printf("AAC Stream Type: 0x%lx\n", tmpvar));

                        msAPI_Music_Init(MSAPI_AUD_DVB_AAC, INIT_VOLUME);  // Initail AAC
                    }
                    break;

                    case E_VDP_CODEC_ID_COOK:
                    {
                        U32 u32SampleRate;

                        VDPLAYER_DBG(printf("Share Memory Address :%lu\n",u32VdplayerShareMemAddr));
                        u16CodecNum=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_NUM_CODECID);
                        u16Samples_channel=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_SAMPLE_CHANNEL);
                        u32SampleRate=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_SAMPLE_RATE);
                        for(i=0;u16CodecNum>i;i++ )
                        {
                            u16CannelsA[i]=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_NUM_CHANNEL+i);
                            u16RegionsA[i]=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_NUM_REGIONS+i);
                            u16cplStartA[i]=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_NUM_CPLSTART+i);
                            u16cplQbitsA[i]=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_NUM_CPLQBITS+i);
                            u16FrameSizeA[i]=_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_RM_LBR_FRAMESIZE+i);
                        }

                        VDPLAYER_DBG(printf("u16CodecNum %u\n",u16CodecNum));
                        VDPLAYER_DBG(printf("u16Samples_channel %u\n",u16Samples_channel));
                        VDPLAYER_DBG(printf("u32SampleRate %u\n",u32SampleRate));
                        for(i=0;u16CodecNum>i;i++ )
                        {
                            // Modified by coverity_0442
                            VDPLAYER_DBG(printf("u16CannelsA[%d] %u\n",i,u16CannelsA[i]));
                            VDPLAYER_DBG(printf("u16RegionsA[%d] %u\n",i,u16RegionsA[i]));
                            VDPLAYER_DBG(printf("u16cplStartA[%d] %u\n",i,u16cplStartA[i]));
                            VDPLAYER_DBG(printf("u16cplQbitsA[%d] %u\n",i,u16cplQbitsA[i]));
                            VDPLAYER_DBG(printf("u16FrameSizeA[%d] %u\n",i,u16FrameSizeA[i]));
                        }
                        msAPI_Music_Init(MSAPI_AUD_DVB_RA8LBR, INIT_VOLUME);
                        MApi_AUDIO_RA8_Param(u16CodecNum, u16Samples_channel, u32SampleRate, &u16CannelsA[0], &u16RegionsA[0], &u16cplStartA[0], &u16cplQbitsA[0], &u16FrameSizeA[0]);

                        MDrv_AUDIO_WriteDecMailBox(5, 0x00);
                    }
                    break;

                    default:
                        //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                        //printf("          NOT SUPPORT AUDIO CODEC     \n");
                        //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                    break;
                }
            #if  AUDIO_SPDIF_ENABLE
                if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
                else if(stGenSetting.g_SysSetting.fSPDIFMODE == 1)
                    MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
            #endif
                BOOL AutoSyncSTC;
                AutoSyncSTC = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_AUDIO_AUTO_SYNC_STC);
                if (!AutoSyncSTC)
                {
                    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
                }

                break;

                // MB_VDPLAYER_ACK_COPROCESSOR_TO_HK ----------------------------------------------
                case MB_VDPLAYER_ACK_COPROCESSOR_TO_HK:
                    VDPLAYER_DVD_DBG(printf("MB_VDPLAYER_ACK_COPROCESSOR_TO_HK[0x%x][0x%x]\n", MB_Message.u8Parameters[0], MB_Message.u8Parameters[1]));
                    switch(MB_Message.u8Parameters[0])
                    {
                        case MB_VDPLAYER_INIT:
                            u8VDPlayerInitResult = MB_Message.u8Parameters[1];
                            if (u8VDPlayerInitResult == 0xFF)
                                break;
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_INIT);
                            enVDPlayerVideoType = (EN_VDPLAYER_VIDEO_TYPE)MB_Message.u8Parameters[2];

                    #if ENABLE_WMDRMPD
                            u32WMDRMPDShareMemAddr = 0; //_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WMDRMPD_SHAREMEM);
                            VDPLAYER_DBG(printf("WMDRMPD share memory addr = %08x\n", u32WMDRMPDShareMemAddr));
                        #if 0
                            // For test only.
                            if (MApp_VDPlayer_WMDRMPD_IsProtected())
                            {
                                if (!MApp_VDPlayer_WMDRMPD_GetLicense())
                                {
                                    printf("GetLicense fail\n");
                                }
                            }
                        #endif
                    #endif
                            break;

                    #if ENABLE_DVD
                        case MB_VDPLAYER_DVD_INIT:
                            u8VDPlayerInitResult = MB_Message.u8Parameters[1];
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_INIT);
                            VDPLAYER_DVD_DBG(printf("Got DVD Init Ack\n"));
                            break;

                        case MB_VDPLAYER_DVD_PREDECODE:
                            VDPLAYER_DVD_DBG(printf("Got DVD Predecode Ack: pts = %d\n", _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_TIME)));
                            MApp_DVD_SetValue(0, TRUE);
                            break;

                        case MB_VDPLAYER_DVD_SEEKPLAY:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SEEKPLAY);
                            VDPLAYER_DVD_DBG(printf("Got DVD SeekPlay Ack\n"));
                            break;

                        case MB_VDPLAYER_DVD_WAITDONE:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_DONE);
                            VDPLAYER_DVD_DBG(printf("Got DVD WaitDone Ack: pts = %d\n", _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_TIME)));
                            break;

                        case MB_VDPLAYER_DVD_SCANSYNC:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SCANSYNC);
                            VDPLAYER_DVD_DBG(printf("ScanSync Ack: pts = %d\n", _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_TIME)));
                            break;

                        case MB_VDPLAYER_DVD_SCANDONE:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SCANDONE);
                            VDPLAYER_DVD_DBG(printf("ScanDone Ack: pts = %d\n", _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_CURRENT_TIME)));
                            break;

                        case MB_VDPLAYER_DVD_SCANEXIT:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SCANEXIT);
                            VDPLAYER_DVD_DBG(printf("ScanExit Ack\n"));
                            break;
                    #endif  // ENABLE_DVD
                        case MB_VDPLAYER_STOP:
                            enVDPlayerVideoType = (EN_VDPLAYER_VIDEO_TYPE)MB_Message.u8Parameters[1];
                            m_eVDPlayerAckFlags &=(enumVDPlayerAckFlags) ~E_ACKFLG_WAIT_STOP;
                        #if ENABLE_DIVX_PLUS
                            g_bChangeFile = FALSE;
                        #endif
                            break;

                        case MB_VDPLAYER_PLAY:
                            m_eVDPlayerAckFlags &=(enumVDPlayerAckFlags) ~E_ACKFLG_WAIT_PLAY;
                            break;

                        case MB_VDPLAYER_SET_AUDIO_TRACK_ID:
                            u8VDPlayerSetAudioTrackResult = MB_Message.u8Parameters[1];
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_AUDIO_TRACK_ID);
                            break;

                        case MB_VDPLAYER_SET_SUBTITLE_TRACKID:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_SUBTITLE_TRACKID);
                            break;

                        case MB_VDPLAYER_TS_SET_PROGRAM:
                            m_eVDPlayerAckFlags &=(enumVDPlayerAckFlags) ~E_ACKFLG_WAIT_TS_SET_PROGRAM;
                            u8VDPlayerTsSetProgramResult = MB_Message.u8Parameters[1];
                            break;
                    #if ENABLE_DRM
                        case MB_VDPLAYER_GET_DRM_REG_CODE:
                            bDrmRegCode = MB_Message.u8Parameters[1];

                            g_DRMRegCode[0] = MB_Message.u8Parameters[2];
                            g_DRMRegCode[1] = MB_Message.u8Parameters[3];
                            g_DRMRegCode[2] = MB_Message.u8Parameters[4];
                            g_DRMRegCode[3] = MB_Message.u8Parameters[5];
                            g_DRMRegCode[4] = MB_Message.u8Parameters[6];
                            g_DRMRegCode[5] = MB_Message.u8Parameters[7];
                            g_DRMRegCode[6] = MB_Message.u8Parameters[8];
                            g_DRMRegCode[7] = MB_Message.u8Parameters[9];

                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_GET_DRM_REG_CODE);

                            break;

                        case MB_VDPLAYER_GET_DRM_REG_CODE_2:
                            g_DRMRegCode[8] = MB_Message.u8Parameters[1];
                            g_DRMRegCode[9] = MB_Message.u8Parameters[2];

                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_GET_DRM_REG_CODE_2);

                            break;

                        case MB_VDPLAYER_GET_DRM_DEACTIVATION_CODE:
                            //bDrmRegCode =  pMB->u8Param[1];
                            g_DRMDeactivationCode[0] = MB_Message.u8Parameters[2];
                            g_DRMDeactivationCode[1] = MB_Message.u8Parameters[3];
                            g_DRMDeactivationCode[2] = MB_Message.u8Parameters[4];
                            g_DRMDeactivationCode[3] = MB_Message.u8Parameters[5];
                            g_DRMDeactivationCode[4] = MB_Message.u8Parameters[6];
                            g_DRMDeactivationCode[5] = MB_Message.u8Parameters[7];
                            g_DRMDeactivationCode[6] = MB_Message.u8Parameters[8];
                            g_DRMDeactivationCode[7] = MB_Message.u8Parameters[9];

                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_GET_DRM_DEACTIVATION_CODE);

                            break;

                        case MB_VDPLAYER_CHECK_DRM_AUTHORIZATION:
                            bDrmAuthorization   = MB_Message.u8Parameters[1];
                            bDrmFileFormat      = MB_Message.u8Parameters[2];
                            bDrmActivationFile  = MB_Message.u8Parameters[3];

                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION);

                            break;

                        case MB_VDPLAYER_QUERY_DRM_RENTAL_STATUS:
                            bDrmRentalStatus =MB_Message.u8Parameters[0];

                            g_bDrmRental    = MB_Message.u8Parameters[1];
                            g_u8DrmUseLimit = MB_Message.u8Parameters[2];
                            g_u8DrmUseCount = MB_Message.u8Parameters[3];

                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_QUERY_DRM_RENTAL_STATUS);

                            break;
                    #endif
/*
                        case MB_VDPLAYER_GET_SUBTITLE_STATE:
                            u32GetSubtitleStateBuf = (((U32)MB_Message.u8Parameters[1]<<16)&0xFF0000) | (((U32)MB_Message.u8Parameters[2]<<8)&0xFF00)| (((U32)MB_Message.u8Parameters[3])&0xFF);

                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_GET_SUBTITLE_STATE);

                            break;
*/
                        case MB_VDPLAYER_REPEAT_AB:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_REPEAT_AB);
                            break;
                        case MB_VDPLAYER_SUBTITLE_TIMESHIFT:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SUBTITLE_TIMESHIFT);
                            break;
                        case MB_VDPLAYER_PAUSE:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_PAUSE);
                            break;
                        case MB_VDPLAYER_SET_TRICK_MODE:
                            u8VDPlayerSetTrickModeResult = MB_Message.u8Parameters[1];
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_TRICK_MODE);
                            break;
                        case MB_VDPLAYER_SET_PLAYER_POSITION:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_SET_PLAYER_POSITION);
                            break;
                        case MB_VDPLAYER_STEP:
                            u8VDPlayerStepPlayResult = MB_Message.u8Parameters[1];
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_STEP);
                            break;
                    #if ENABLE_DIVX_PLUS
                        case MB_VDPLAYER_SET_CHAPTER_ID:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_CHAPTER_ID);
                            break;
                        case MB_VDPLAYER_SET_AUTOGEN_CHAPTER_ID:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_AUTOGEN_CHAPTER_ID);
                            break;
                        case MB_VDPLAYER_SET_TITLE_ID:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_TITLE_ID);
                            break;
                        case MB_VDPLAYER_SET_EDITION_ID:
                            Remove_enumVDPlayerAckFlags(m_eVDPlayerAckFlags, E_ACKFLG_WAIT_SET_EDITION_ID);
                            break;
                    #endif
                        default:
                            //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                            //printf("          Unkow Co-processor ACK(0x%x)        \n",MB_Message.u8Parameters[0]);
                            //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                            break;

                    }
                break;

                // MB_VDPLAYER_SETUP_DISPLAY ----------------------------------------------
                case MB_VDPLAYER_SETUP_DISPLAY:
                    {
                        U32 u32VdplayerBuffY0 = 0;
                        U8  u8TSStream = 0;

                        if(MB_Message.u8Parameters[0] == E_VDPLAYER_VIDEO_MJPEG)
                        {
                            u32VdplayerBuffY0  = (((U32)MB_Message.u8Parameters[5]<<24)&0xFF000000) |
                                                 (((U32)MB_Message.u8Parameters[6]<<16)&0x00FF0000) |
                                                 (((U32)MB_Message.u8Parameters[7]<<8)&0x0000FF00) |
                                                 (((U32)MB_Message.u8Parameters[8])&0x000000FF);
                        }
                        else
                        {
                            u8TSStream = MB_Message.u8Parameters[5];
                        }

                #if SEAMLESS_PLAYING_ENABLE
                        if (!_bEnableSeamlessPlaying || !MApi_XC_IsFreezeImg(MAIN_WINDOW))
                #endif
                        {
                            _MApp_VDPlayer_SetupDisplayPath(MB_Message.u8Parameters[0],
                                ((U16)(MB_Message.u8Parameters[1]<<8)&0xFF00)|(MB_Message.u8Parameters[2]&0x00FF),
                                ((U16)(MB_Message.u8Parameters[3]<<8)&0xFF00)|(MB_Message.u8Parameters[4]&0x00FF),
                                0,0,
                                PANEL_WIDTH,PANEL_HEIGHT, u32VdplayerBuffY0,u8TSStream);
                        }

                #if SEAMLESS_PLAYING_ENABLE
                        if (_bEnableSeamlessPlaying)
                            _u32SeamlessTimer = (U32)MsOS_GetSystemTime();
                #endif

#if ENABLE_DVD
                        VDPLAYER_DVD_DBG(printf("SetupDisp\n"));
                        if (bIsDVD)
                            MApp_MPlayer_DVD_StartPlay();
#endif
                    }
                    if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_MVD_FRAMEBUFFER_MODE) == (U32)ENABLE_FBL_MODE)
                    {
                        printf("FBL mode: Ummute need to wait fpll done\n");
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_SCALER_FPLL, ENABLE, 0, MAIN_WINDOW);
                        U32 u32WhileEnteredTime = msAPI_Timer_GetTime0();
                        while(msAPI_Scaler_GetScreenMute(MAIN_WINDOW)&E_SCREEN_MUTE_BY_SCALER_FPLL)
                        {
                            MApi_XC_Sys_CheckFpllStatusTask();
                            if( msAPI_Timer_DiffTimeFromNow(u32WhileEnteredTime) > 3000 )
                            {
                                //Time out
                                break;
                            }
                        }
                    }
                    //==> Send mail.
                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                    /*ParameterCount*/  ,1
                    /*p1*/              ,MB_VDPLAYER_SETUP_DISPLAY
                    /*p2*/              ,0
                    /*p3*/              ,0
                    /*p4*/              ,0
                    /*p5*/              ,0
                    /*p6*/              ,0
                    /*p7*/              ,0
                    /*p8*/              ,0
                    /*p9*/              ,0
                    /*p10*/             ,0);

                #if DYNSCALING
                    //send DS status mailbox to co-p after MB_VDPLAYER_SETUP_DISPLAY ack
                    if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING)==1)
                    {
                        _MApp_VDPlayer_SendXCStatus2Firmware(
                            _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DYNSCALING_ADDRESS) + (1024*3), MAIN_WINDOW);
                    }
                #endif

                    if(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_VIDEO_FRC_MODE))
                    {
                        MDrv_PQ_DisableFilmMode(PQ_MAIN_WINDOW,FALSE);
                    }
                    else
                    {
                        MDrv_PQ_DisableFilmMode(PQ_MAIN_WINDOW,TRUE);
                    }

                    MApp_UiMediaPlayer_Notify(E_MPLAYER_NOTIFY_SETUP_DISPLAY, NULL);
            #if (SUPPERTED_ADVERTISEMENT_MODE)
                    if ((m_eVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW) == 0)
                    {
                        MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                        msAPI_Scaler_SetBlueScreen( DISABLE,E_XC_FREE_RUN_COLOR_BLACK,  0, MAIN_WINDOW);
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, MAIN_WINDOW);
                        MM_TRACE();
                    }
            #endif
                    break;

                // MB_VDPLAYER_SET_DISPLAY_INFO ----------------------------------------------
                case MB_VDPLAYER_SET_DISPLAY_INFO:
            #if (SUPPERTED_ADVERTISEMENT_MODE)
                    if ((m_eVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW) == 0)
                        break;
            #endif
                    if (gstVidStatus.u32FrameRate > 0)
                    {
#if (ENABLE_FDMASK_DELAY == 1)
                        const XC_ApiInfo *pXC_ApiInfo;
                        U16 u16Delay;

                        pXC_ApiInfo = MApi_XC_GetInfo();
                        if (gstVidStatus.u8Interlace)
                        {
                            u16Delay = (1000000UL * DEFAULT_FIELD_COUNT) / gstVidStatus.u32FrameRate;
                        }
                        else
                        {
                            u16Delay = (1000000UL * DEFAULT_FIELD_COUNT) / gstVidStatus.u32FrameRate;
                        }
#else
                        U16 u16Delay = (1000000UL * DEFAULT_FIELD_COUNT) / gstVidStatus.u32FrameRate;
#endif  // #if (ENABLE_FDMASK_DELAY == 1)

                        if (u16Delay >= 1000)
                            u16Delay = 1000;
                        msAPI_VDPlayer_ScreenDisplaySetting( (EN_VDPLAYER_SCREEN_SETTINGS)MB_Message.u8Parameters[0] ,MB_Message.u8Parameters[1], u16Delay );
                    }
                    else
                    {
                        msAPI_VDPlayer_ScreenDisplaySetting( (EN_VDPLAYER_SCREEN_SETTINGS)MB_Message.u8Parameters[0] , MB_Message.u8Parameters[1],  DEFAULT_SCREEN_UNMUTE_TIME );
                    }
                    break;

                // MB_VDPLAYER_CLOSE_DISPLAY ----------------------------------------------
                case MB_VDPLAYER_CLOSE_DISPLAY:
                    {
                #if SEAMLESS_PLAYING_ENABLE
                        if (_bEnableSeamlessPlaying)
                        {
                            _u32SeamlessTimer = (U32)MsOS_GetSystemTime()+100000;
                            MApi_XC_FreezeImg(ENABLE, MAIN_WINDOW);
                        }
                        else
                #endif
                        {
                            msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                            MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
                            MDrv_MVOP_Enable(FALSE);
                        }

                        if(MB_Message.u8Parameters[0] == E_VDPLAYER_VIDEO_MJPEG)
                        {
                        #if (ENABLE_MIU_1 == ENABLE)
                            MDrv_MVOP_MiuSwitch(1);
                        #endif
                        }
                    }
                break;

                // MB_VDPLAYER_MPEG_SUBTITLE_SETHEADERINFO ----------------------------------------------
                case MB_VDPLAYER_MPEG_SUBTITLE_SETHEADERINFO:
                    {
                        U32 numb;
                        U32 addr;

                        //printf("Subtitle set header information: sbtype:%d; videotype:%d\n", (U16)pMB->u8Param[0] , (U16)pMB->u8Param[1]);
                         switch ( u32subtitletype)
                        {
                            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
                                numb = MB_Message.u8Parameters[2];
                                addr = COMBU32(MB_Message.u8Parameters[3], MB_Message.u8Parameters[4], MB_Message.u8Parameters[5], MB_Message.u8Parameters[6]);
                                addr = _PA2VA(addr);

                                if (numb && addr)
                                {
                                    U32 buf[16];

                                    memset(buf, 0, sizeof(buf));
                                    memcpy(&buf,(U8*)addr,64);
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                                    msAPI_MpegSP_SetPalette(buf,  numb);
#endif
                                }
                                break;


                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
                                break;

                            default:
                                break;
                        }
                        break;
                    }

                // MB_VDPLAYER_SPUQUEUE_PUSH ----------------------------------------------
                case MB_VDPLAYER_SPUQUEUE_PUSH:
#if (ENABLE_INTERNAL_SUBTITLE)
                {
                    U32 u32PTS1;
                    U32 u32PTS2;

                    switch (u32subtitletype)
                    {
#if (TS_INTERNAL_SUBTITLE_BMP)
                        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS:
                            {
                                U32 u32SdramAddr=0;
                                U16 u16PesLen=0;

                                u32SdramAddr = COMBU32(MB_Message.u8Parameters[0], MB_Message.u8Parameters[1], MB_Message.u8Parameters[2],MB_Message.u8Parameters[3]);
                                u16PesLen = COMBU16(MB_Message.u8Parameters[4], MB_Message.u8Parameters[5]);
                                u32PTS1 = COMBU32(MB_Message.u8Parameters[6], MB_Message.u8Parameters[7], MB_Message.u8Parameters[8], MB_Message.u8Parameters[9]);
                                BMP_DBG(printf("@@BMP pushQ, PTS:%d, Addr:0x%x, Len:0x%x\n",u32PTS1,u32SdramAddr,u16PesLen));
                                msAPI_Subtitle_Queue_Push(_PA2VA(u32SdramAddr), u16PesLen, u32PTS1); //msAPI_Subtitle_Queue_Push use VA
#if 0
                                //==> Send mail.
                                VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                /*ParameterCount*/  ,1
                                /*p1*/              ,MB_VDPLAYER_SPUQUEUE_PUSH
                                /*p2*/              ,0
                                /*p3*/              ,0
                                /*p4*/              ,0
                                /*p5*/              ,0
                                /*p6*/              ,0
                                /*p7*/              ,0
                                /*p8*/              ,0
                                /*p9*/              ,0
                                /*p10*/             ,0);
#endif
                            }
                            break;
#endif

#if (TS_INTERNAL_SUBTITLE_PGS)
                        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS:
                            {
                                U32 u32SdramAddr=0;
                                U16 u16PesLen=0;

                                u32SdramAddr = COMBU32(MB_Message.u8Parameters[0], MB_Message.u8Parameters[1], MB_Message.u8Parameters[2],MB_Message.u8Parameters[3]);
                                u16PesLen = COMBU16(MB_Message.u8Parameters[4], MB_Message.u8Parameters[5]);
                                u32PTS1 = COMBU32(MB_Message.u8Parameters[6], MB_Message.u8Parameters[7], MB_Message.u8Parameters[8], MB_Message.u8Parameters[9]);
                                PGS_DBG(printf("@@PGS PushQ, PTS:%d, Addr:0x%x, Len:0x%x\n",u32PTS1,u32SdramAddr,u16PesLen));
                                msAPI_Subtitle_Queue_Push(_PA2VA(u32SdramAddr), u16PesLen, u32PTS1); //msAPI_Subtitle_Queue_Push use VA
                            }
                            break;
#endif

                        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
#if (ENABLE_INTERNAL_BMP_SUBTITLE)
                            spuqueuesize = (((U16) MB_Message.u8Parameters[4] << 8) & 0xFF00) | (((U16)MB_Message.u8Parameters[5])&0x00FF);
                            u32PTS1 = (((U32)MB_Message.u8Parameters[6]<<24)&0xFF000000) |
                                      (((U32)MB_Message.u8Parameters[7]<<16)&0x00FF0000) |
                                      (((U32)MB_Message.u8Parameters[8]<<8)&0x0000FF00) |
                                      (((U32)MB_Message.u8Parameters[9])&0x000000FF);

                            msAPI_VDPlayer_SubtitlePushQueue((EN_VDP_CODECID)u32subtitletype, spuqueueaddr, (U32)spuqueuesize, u32PTS1, 0);

                            //u8subtitletype = pMB->u8Param[0];
#endif
                            break;

                        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:    //divx
#if (ENABLE_INTERNAL_BMP_SUBTITLE)
                            {
                                U16 len = COMBU16(MB_Message.u8Parameters[2], MB_Message.u8Parameters[3]);
                                U32 adr = COMBU32(MB_Message.u8Parameters[4], MB_Message.u8Parameters[5],MB_Message.u8Parameters[6], MB_Message.u8Parameters[7]);

                                msAPI_VDPlayer_SubtitlePushQueue((EN_VDP_CODECID)u32subtitletype, adr, len, 0, 0);

                                //u8subtitletype = pMB->u8Param[0];
                            }
#endif
                            break;
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
#if (ENABLE_INTERNAL_TEXT_SUBTITLE)
                            spuqueuesize = (((U16) MB_Message.u8Parameters[8] << 8) & 0xFF00) | (((U16)MB_Message.u8Parameters[9])&0x00FF);
                            u32PTS1 = (((U32)MB_Message.u8Parameters[2]<<24)&0xFF000000) |
                                      (((U32)MB_Message.u8Parameters[3]<<16)&0x00FF0000) |
                                      (((U32)MB_Message.u8Parameters[4]<<8)&0x0000FF00) |
                                      (((U32)MB_Message.u8Parameters[5])&0x000000FF);
                            u32PTS2 = (((U32)MB_Message.u8Parameters[6]<<8)&0x0000FF00) | (((U32)MB_Message.u8Parameters[7])&0x000000FF);
                            u32PTS2 += u32PTS1;

                            msAPI_VDPlayer_SubtitlePushQueue( (EN_VDP_CODECID)u32subtitletype, /*pMB->u8Param[1],*/ spuqueueaddr,spuqueuesize, u32PTS1  , u32PTS2 );
#endif
                            break;

                        default:// unknow format
                            break;
                    }

                    spuqueueaddr=0;
                    spuqueuesize=0;

                }
#endif //#if (ENABLE_INTERNAL_SUBTITLE)
                    break;
                // MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR ----------------------------------------------
                case MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR:
#if (TS_INTERNAL_SUBTITLE_BMP)
                    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
                    {
                        /// provide subtitle decoder PES Queue buffer.
                        {
                            BMP_DBG(printf("@@BMP get Q SDRAM addr\n"));
                            U32 u32SDRAMAddress = msAPI_Subtitle_Queue_GetSDRAMAddress(0);
                            u32SDRAMAddress = _VA2PA(u32SDRAMAddress);
                            U32 u32ST_QLength = msAPI_Subtitle_GetQueueLength();

                            VDPLAYER_DBG(printf("\tsubtitle queue buffer addr:0x%x  len:0x%x\n",u32SDRAMAddress,u32ST_QLength));
                            //==> Send mail.
                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                            /*ParameterCount*/  ,10
                            /*p1*/              ,MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR
                            /*p2*/              ,GetByte3(u32SDRAMAddress)
                            /*p3*/              ,GetByte2(u32SDRAMAddress)
                            /*p4*/              ,GetByte1(u32SDRAMAddress)
                            /*p5*/              ,GetByte0(u32SDRAMAddress)
                            /*p6*/              ,GetByte3(u32ST_QLength)
                            /*p7*/              ,GetByte2(u32ST_QLength)
                            /*p8*/              ,GetByte1(u32ST_QLength)
                            /*p9*/              ,GetByte0(u32ST_QLength)
                            /*p10*/             ,(U8)EN_VDP_FILE_FORMAT_TS);
                        }
                        break;
                    }
#endif
#if (TS_INTERNAL_SUBTITLE_PGS)
                    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
                    {
                        /// provide subtitle decoder PES Queue buffer.
                        {
                            PGS_DBG(printf("@@PGS get Q SDRAM addr\n"));
                            U32 u32SDRAMAddress = msAPI_Subtitle_Queue_GetSDRAMAddress(0);
                            u32SDRAMAddress = _VA2PA(u32SDRAMAddress);
                            U32 u32ST_QLength = msAPI_Subtitle_GetQueueLength();

                            VDPLAYER_DBG(printf("\tsubtitle queue buffer addr:0x%x  len:0x%x\n",u32SDRAMAddress,u32ST_QLength));
                            //==> Send mail.
                            VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                            /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                            /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                            /*ParameterCount*/  ,10
                            /*p1*/              ,MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR
                            /*p2*/              ,GetByte3(u32SDRAMAddress)
                            /*p3*/              ,GetByte2(u32SDRAMAddress)
                            /*p4*/              ,GetByte1(u32SDRAMAddress)
                            /*p5*/              ,GetByte0(u32SDRAMAddress)
                            /*p6*/              ,GetByte3(u32ST_QLength)
                            /*p7*/              ,GetByte2(u32ST_QLength)
                            /*p8*/              ,GetByte1(u32ST_QLength)
                            /*p9*/              ,GetByte0(u32ST_QLength)
                            /*p10*/             ,(U8)EN_VDP_FILE_FORMAT_TS);
                        }
                        break;
                    }
#endif
                    {
                        switch (u32subtitletype)
                        {
                            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
                            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
                                {
                                    U16 len = COMBU16(MB_Message.u8Parameters[2], MB_Message.u8Parameters[3]);
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                                    U32 adr = msAPI_MpegSP_SpuQueue_GetSDRAMAddress(len);
#else
                                    U32 adr = 0;
#endif
                                    //==> Send mail.
                                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                    /*ParameterCount*/  ,5
                                    /*p1*/              ,MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR
                                    /*p2*/              ,GetByte3(adr)
                                    /*p3*/              ,GetByte2(adr)
                                    /*p4*/              ,GetByte1(adr)
                                    /*p5*/              ,GetByte0(adr)
                                    /*p6*/              ,0
                                    /*p7*/              ,0
                                    /*p8*/              ,0
                                    /*p9*/              ,0
                                    /*p10*/             ,0);
                                    spuqueueaddr = adr;
                                    spuqueuesize = len;
                                }
                                break;

                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                if(u8IsFontTableReady)
                                {
                                    U16 len = COMBU16(MB_Message.u8Parameters[2], MB_Message.u8Parameters[3]);
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                                    U32 adr = msAPI_MpegSP_SpuQueue_GetSDRAMAddress(len);
#else
                                    U32 adr=0;
#endif
                                    //==> Send mail.
                                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                    /*ParameterCount*/  ,5
                                    /*p1*/              ,MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR
                                    /*p2*/              ,GetByte3(adr)
                                    /*p3*/              ,GetByte2(adr)
                                    /*p4*/              ,GetByte1(adr)
                                    /*p5*/              ,GetByte0(adr)
                                    /*p6*/              ,0
                                    /*p7*/              ,0
                                    /*p8*/              ,0
                                    /*p9*/              ,0
                                    /*p10*/             ,0);
                                    spuqueueaddr = adr;
                                    spuqueuesize = len;
                                }
                                else
#endif
                                {
                                    static U32 u32Spuqueueaddrhead = INTERNAL_TEXT_SUBTITLE_BUFFER_ADR;
                                    static U32 u32SizeAlloc = 0;

                                    u32Spuqueueaddrhead += MAX_INTERNAL_TEXT_SUBTITLE_LEN;
                                    u32SizeAlloc += MAX_INTERNAL_TEXT_SUBTITLE_LEN;

                                    if(u32SizeAlloc >= INTERNAL_TEXT_SUBTITLE_BUFFER_SIZE)
                                    {
                                        u32Spuqueueaddrhead = INTERNAL_TEXT_SUBTITLE_BUFFER_ADR;
                                        u32SizeAlloc = 0;
                                    }
                                    spuqueueaddr= u32Spuqueueaddrhead;
                                    spuqueuesize=MAX_INTERNAL_TEXT_SUBTITLE_LEN;

                                    //==> Send mail.
                                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                                    /*ParameterCount*/  ,5
                                    /*p1*/              ,MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR
                                    /*p2*/              ,(U8)((spuqueueaddr&0xFF000000)>>24)
                                    /*p3*/              ,(U8)((spuqueueaddr&0x00FF0000)>>16)
                                    /*p4*/              ,(U8)((spuqueueaddr&0x0000FF00)>>8)
                                    /*p5*/              ,(U8)(spuqueueaddr&0x000000FF)
                                    /*p6*/              ,0
                                    /*p7*/              ,0
                                    /*p8*/              ,0
                                    /*p9*/              ,0
                                    /*p10*/             ,0);
                                }
                                break;

                            default:
                                break;
                        }

                        break;
                    }

                // MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW ----------------------------------------------
                case MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW:
                {
#if (TS_INTERNAL_SUBTITLE_BMP)
                    if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
                    {
                        BMP_DBG(printf("@@BMP MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW\n"));
                        _bSubtitleShow_MW = MB_Message.u8Parameters[2];

                        if (!(_bSubtitleShow_MW && _bSubtitleShow_User && (u8InternalST_Num>0)))
                        {
                            MApp_VDPlayer_TS_SubtitleErase();
                        }
                        break;
                    }
#endif
#if (TS_INTERNAL_SUBTITLE_PGS)
                    if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
                    {
                        PGS_DBG(printf("@@PGS MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW\n"));
                        _bSubtitleShow_MW = MB_Message.u8Parameters[2];

                        if (!(_bSubtitleShow_MW && _bSubtitleShow_User && (u8InternalST_Num>0)))
                        {
                            MApp_VDPlayer_TS_SubtitleErase();
                        }
                        break;
                    }
#endif

                    switch (u32subtitletype)
                    {
                        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
                        case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                            /*  mark internal subtitle controlled by Coprocessor, only controlled by UI
                            if (MB_Message.u8Parameters[2] == TRUE)
                            {
                                msAPI_MpegSP_Show();
                            }
                            else
                            {
                                msAPI_MpegSP_Unshow();
                            }
                            */
/*
                            if (msAPI_MailBox_WaitReady())
                            {
                                MailBoxPara.u8CmdClass  = MB_CLASS_VDPLAYER;
                                MailBoxPara.u8CmdIdx    = MB_VDPLAYER_ACK_HK_TO_COPROCESSOR;
                                MailBoxPara.ParamCnt    = 1;
                                MailBoxPara.CMDType     = MB_CMD_TYPE_DEFAULT;
                                MailBoxPara.u8Param[0]  = MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW;
                                msAPI_MailBox_SendMsg();
                            }
*/
#endif
                            break;

                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                        case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
                            // need to check timothy.h
                            if (MB_Message.u8Parameters[2] == TRUE)
                            {
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                if(u8IsFontTableReady)
                                {
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                                /*  mark internal subtitle controlled by Coprocessor, only controlled by UI
                                    msAPI_MpegSP_Show();
                                */
#endif
                                }
                                else
#endif
                                {
                                    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT,(U32)(MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT-u16SubtitleTagCnt));
                                }
                            }
                            else
                            {
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                if(u8IsFontTableReady)
                                {
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                                /*  mark internal subtitle controlled by Coprocessor, only controlled by UI
                                    msAPI_MpegSP_Unshow();
                                */
#endif
                                }
                                else
#endif
                                {
                                    _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, 0 );
                                }
                            }
/*
                            if (msAPI_MailBox_WaitReady())
                            {
                                MailBoxPara.u8CmdClass  = MB_CLASS_VDPLAYER;
                                MailBoxPara.u8CmdIdx    = MB_VDPLAYER_ACK_HK_TO_COPROCESSOR;
                                MailBoxPara.ParamCnt    = 1;
                                MailBoxPara.CMDType     = MB_CMD_TYPE_DEFAULT;
                                MailBoxPara.u8Param[0]  = MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW;
                                msAPI_MailBox_SendMsg();
                            }
*/
                            break;

                        default:
                            break;
                    }

                    break;
                }


                // MB_VDPLAYER_MPEG_SUBTITLE_RESET ----------------------------------------------
                case MB_VDPLAYER_MPEG_SUBTITLE_RESET:
                    //==> Send mail.
                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                    /*ParameterCount*/  ,1
                    /*p1*/              ,MB_VDPLAYER_MPEG_SUBTITLE_RESET
                    /*p2*/              ,0
                    /*p3*/              ,0
                    /*p4*/              ,0
                    /*p5*/              ,0
                    /*p6*/              ,0
                    /*p7*/              ,0
                    /*p8*/              ,0
                    /*p9*/              ,0
                    /*p10*/             ,0);
                    break;

                case MB_VDPLAYER_SET_SUBTITLE_TRACKID:
#if (TS_INTERNAL_SUBTITLE_BMP)
                    if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
                    {
                        BMP_DBG(printf("@@BMP Set subtitle trackid\n"));
                        U16 u16CPageID,u16APageID;
                        u16CPageID = COMBU16(MB_Message.u8Parameters[0], MB_Message.u8Parameters[1]);
                        u16APageID = COMBU16(MB_Message.u8Parameters[2], MB_Message.u8Parameters[3]);
                        msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN);
                        MApp_TS_Subtitle_SetVideoInfo(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH),_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT));
                        msAPI_Subtitle_SetPageIDs(u16CPageID, u16APageID);

                        MApp_VDPlayer_TS_SubtitleErase();
                    }
#endif
#if (TS_INTERNAL_SUBTITLE_PGS)
                    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
                    {
                        PGS_DBG(printf("@@PGS set subtitle trackid\n"));
                        U16 u16CPageID,u16APageID;
                        u16CPageID = COMBU16(MB_Message.u8Parameters[0], MB_Message.u8Parameters[1]);
                        u16APageID = COMBU16(MB_Message.u8Parameters[2], MB_Message.u8Parameters[3]);
                        msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN);
                        MApp_TS_Subtitle_SetVideoInfo(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH),_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT));
                        msAPI_Subtitle_SetPageIDs(u16CPageID, u16APageID);

                        MApp_VDPlayer_TS_SubtitleErase();
                    }
#endif
                    break;

                // MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT ----------------------------------------------
                case MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT:
                {
                    U8 u8Cmd = MB_Message.u8Parameters[0];
                    u32subtitletype = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_SUBTITLE_CODEC_ID);
#if (TS_INTERNAL_SUBTITLE_BMP)
                    if ((u8Cmd == E_SUBTITLE_INIT_COMMAND_INIT) && (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS))
                    {
                        BMP_DBG(printf("@@BMP init\n"));
                        //(printf("\tTS subtitle init \n"));
                        //(printf("\tMB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT \n"));
                        //(printf("\tSubtitle Init Queue,SUBTITLE_ADR:0x%x, SUBTITLE_LEN:0x%x\n",SUBTITLE_ADR, SUBTITLE_LEN));
                        //(printf("\tTSP subtitle buffer addr:0x%x, len:0x%x\n",u32SubtitleAddr,u32SubtitleSize));

                        msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN);
                        MApp_TS_Subtitle_SetVideoInfo(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH),_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT));
                        /// Init ack
                        //==> Send mail.
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,2
                        /*p1*/              ,MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT
                        /*p2*/              ,(U8)EN_VDP_FILE_FORMAT_TS
                        /*p3*/              ,0
                        /*p4*/              ,0
                        /*p5*/              ,0
                        /*p6*/              ,0
                        /*p7*/              ,0
                        /*p8*/              ,0
                        /*p9*/              ,0
                        /*p10*/             ,0);

                        //Control Subtitle
                        _bSubtitleShow_MW = ENABLE;
                        u8IsSubtitleBusy = FALSE;
                        u8IssubtitleInit = TRUE;
                        u8IsSubtitleInitfinish = TRUE;

                        VDPLAYER_DBG(printf( " [Aeon OS] TS subtitle init success \n"));
                        u8InternalST_Num = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_SUBTITLE);
                        break;
                    }
                    else if ((u8Cmd == E_SUBTITLE_INIT_COMMAND_DEINIT) && (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS))
                    {
                        BMP_DBG(printf("@@BMP deinit\n"));
                        MApp_VDPlayer_TS_SubtitleErase();
                        MApp_TS_Subtitle_SetVideoInfo(0,0);
                        u8IssubtitleInit = FALSE;
                        _bSubtitleShow_MW   = DISABLE;      // control by MW.
                        u8InternalST_Num = 0;
                        u8IsSubtitleInitfinish = FALSE;
                        break;
                    }
#else
                    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)
                    {
                        return;
                    }
#endif //#if (TS_INTERNAL_SUBTITLE_BMP)

#if (TS_INTERNAL_SUBTITLE_PGS)
                    if ((u8Cmd == E_SUBTITLE_INIT_COMMAND_INIT) && (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS))
                    {
                        PGS_DBG(printf("@@PGS init\n"));
                        //(printf("\t@@PGS TS subtitle init \n"));
                        //(printf("\t@@PGS MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT \n"));
                        //(printf("\t@@PGS Subtitle Init Queue,SUBTITLE_ADR:0x%x, SUBTITLE_LEN:0x%x\n",SUBTITLE_ADR, SUBTITLE_LEN));
                        //(printf("\t@@PGS TSP subtitle buffer addr:0x%x, len:0x%x\n",u32SubtitleAddr,u32SubtitleSize));

                        msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN);
                        MApp_TS_Subtitle_SetVideoInfo(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_WIDTH),_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_HEIGHT));
                        /// Init ack
                        //==> Send mail.
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,2
                        /*p1*/              ,MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT
                        /*p2*/              ,(U8)EN_VDP_FILE_FORMAT_TS
                        /*p3*/              ,0
                        /*p4*/              ,0
                        /*p5*/              ,0
                        /*p6*/              ,0
                        /*p7*/              ,0
                        /*p8*/              ,0
                        /*p9*/              ,0
                        /*p10*/             ,0);

                        //Control Subtitle
                        _bSubtitleShow_MW = ENABLE;
                        u8IsSubtitleBusy = FALSE;
                        u8IssubtitleInit = TRUE;
                        u8IsSubtitleInitfinish = TRUE;

                        VDPLAYER_DBG(printf( " [Aeon OS] TS subtitle init success \n"));
                        u8InternalST_Num = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_SUBTITLE);
                        break;
                    }
                    else if ((u8Cmd == E_SUBTITLE_INIT_COMMAND_DEINIT) && (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS))
                    {
                        PGS_DBG(printf("@@PGS deinit\n"));
                        MApp_VDPlayer_TS_SubtitleErase();
                        MApp_TS_Subtitle_SetVideoInfo(0,0);
                        u8IssubtitleInit = FALSE;
                        _bSubtitleShow_MW   = DISABLE;      // control by MW.
                        u8InternalST_Num = 0;
                        u8IsSubtitleInitfinish = FALSE;
                        break;
                    }
#else
                    if (u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS)
                    {
                        return;
                    }
#endif //#if (TS_INTERNAL_SUBTITLE_PGS)

                    if (u8Cmd == E_SUBTITLE_INIT_COMMAND_INIT)
                    {
                        switch( u32subtitletype )
                        {
                            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB:
                            case E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP:
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                                if (!msAPI_MpegSP_Init())
                                {
                                    VDPLAYER_DBG(printf("subtitle picture init failed\n"));

                                    return;
                                }
                                MApp_MPlayer_EnableInternalSubtitle(TRUE);
                                u8IssubtitleInit = TRUE;

                                //if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)
                                {
                                    msAPI_MpegSP_SetSubtitleDimension(COMBU16(MB_Message.u8Parameters[5], MB_Message.u8Parameters[6]), COMBU16(MB_Message.u8Parameters[7], MB_Message.u8Parameters[8]));
                                }
                                _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT,MAX_SPU_QUEUE_SIZE);
                                break;
#else
                                return;
#endif //#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)

                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                            case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
                                {
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                    U32 u32FontTableSize;
                                    u32FontTableSize = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_SUBTITLE_ATTACHEDFILE_SIZE);

                                    if( u32FontTableSize > 0 )
                                    {
                                        U32 u32FontTableAddr;
                                        u32FontTableAddr = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_SUBTITLE_ATTACHEDFILE_BUFF_ADDR);
                                        u32FontTableAddr = _PA2VA(u32FontTableAddr);
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                                        if (!msAPI_MpegSP_Init())
#endif
                                        {
                                            VDPLAYER_DBG(printf("subtitle picture init failed\n"));

                                            return;
                                        }
                                        MApp_MPlayer_EnableInternalSubtitle(TRUE);

                                        if (!msAPI_DivXTTF_InitTTF(u32FontTableAddr,u32FontTableSize))
                                        {
                                            VDPLAYER_DBG(printf("True type font init failed\n"));
                                            return;
                                        }

                                        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT,MAX_SPU_QUEUE_SIZE);
                                        u8IssubtitleInit = TRUE;
                                        u8IsFontTableReady = TRUE;
                                    }
                                    else
#endif
                                    {

#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                                        u8IsFontTableReady = FALSE;
#endif
                                        MApp_VDPlayer_TextSubtitleInit();
                                        //MApp_MPlayer_SubtitleInit();
                                        _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT, MAX_INTERNAL_TEXT_SUBTITLE_TAG_COUNT);
                                        spuqueueaddr= (((U32)u16tagposition)<<8) + INTERNAL_TEXT_SUBTITLE_BUFFER_SIZE;
                                        //spulen=MP4_SUBTITLE_BUFFER_LEN;
                                    }
                                }
                                break;
                            default:// unknow format
                                break;
                        }

                        //==> Send mail.
                        VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                        /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                        /*ParameterCount*/  ,1
                        /*p1*/              ,MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT
                        /*p2*/              ,0
                        /*p3*/              ,0
                        /*p4*/              ,0
                        /*p5*/              ,0
                        /*p6*/              ,0
                        /*p7*/              ,0
                        /*p8*/              ,0
                        /*p9*/              ,0
                        /*p10*/             ,0);

                        VDPLAYER_DBG(printf( " [Aeon OS] subtitle init success \n"));

                        u8IsSubtitleBusy        = FALSE;
                    }
                    else if (u8Cmd == E_SUBTITLE_INIT_COMMAND_DEINIT)
                    {
                        //if (pMB->u8Param[1] == TRUE)
                        {
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                            msAPI_MpegSP_Dinit();
#endif
                        }

                        //if (pMB->u8Param[2] == TRUE)
                        {
                            MApp_VDPlayer_TextSubtitleInit();
//                                    MApp_MPlayer_SubtitleInit();
                            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_CURRENT_SUBTITLE_TAGCOUNT,0);
                        }

                        u8IssubtitleInit        = FALSE;
                        u32subtitletype          = 0;
                        u8IsSubtitleBusy        = FALSE;
                        u8IsSubtitleInitfinish  = FALSE;
                        u32GetSubtitleStateBuf  = 0;
#if (defined(MSOS_TYPE_LINUX) && ENABLE_DIVX_TTF)
                        u8IsFontTableReady=FALSE;
#endif
                    }
                    else
                    {
                        u8IsSubtitleInitfinish = TRUE;
                    }

                    break;
                }

            case MB_VDPLAYER_MPEG_SUBTITLE_GETQUEUEINFO:
                {
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
                    U8 queuecount = msAPI_MpegSP_SpuQueue_GetCount();
#else
                    U8 queuecount = 0;
#endif
                    //==> Send mail.
                    VDPLAYER_MAILBOX_SEND(E_MBX_CLASS_VDPLAYER
                    /*Index*/           ,MB_VDPLAYER_ACK_HK_TO_COPROCESSOR
                    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
                    /*ParameterCount*/  ,2
                    /*p1*/              ,MB_VDPLAYER_MPEG_SUBTITLE_GETQUEUEINFO
                    /*p2*/              ,queuecount
                    /*p3*/              ,0
                    /*p4*/              ,0
                    /*p5*/              ,0
                    /*p6*/              ,0
                    /*p7*/              ,0
                    /*p8*/              ,0
                    /*p9*/              ,0
                    /*p10*/             ,0);
                }
                break;
#if ENABLE_DRM
            case MB_VDPLAYER_SET_REPLAYBACK:
                g_bReplay = TRUE;
                break;
#endif
            case MB_VDPLAYER_AUDIO_UNSUPPORT:  //20100809EL
                g_bUnsupportAudio = TRUE;
                //printf(">>>>>111  MB_VDPLAYER_AUDIO_UNSUPPORT\n");
                break;

            default:
                //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                //printf("          Unkown Co-processor MAILBOX(0x%x)       \n",MB_Message.u8Index);
                //printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                break;
//****************************************************************************************
        }

        // Update u32VDPlayerLoopWdtTimer if receive Mailbox in init process, used for Init timeout checking
        if(m_eVDPlayerAckFlags&E_ACKFLG_WAIT_INIT)
            u32VDPlayerLoopWdtTimer = msAPI_Timer_GetTime0();
    }
}

BOOLEAN MApp_VDPlayer_MediaCodec_Initialize(void)
{
    if(m_bMM_Initial == FALSE)
    {
        //E_MBX_CPU_MIPS, E_MBX_ROLE_CP unused.
        if(E_MBX_SUCCESS == MDrv_VMBX_Init(E_MBX_CPU_MIPS, E_MBX_ROLE_CP, TIMEOUT_TIMER_2000MS))
        {
            if (MApp_MediaCodec_Initialize() == TRUE)
            {
                  //printf("\n\n***************MApp_MediaCodec_Initialize***************\n\n\n");
                  // We can call MApp_MediaCodecTask(void) to do Demux/ Decode..
                  m_bMM_Initial = TRUE;

                  return TRUE;
            }
            else
            {
                //something error
                VDPLAYER_ERROR("!!!!!!!! %s --> MApp_MediaCodec_Initialize FALSE \n",__FUNCTION__);
                return FALSE;
            }
        }
        else
        {
            //something error
            VDPLAYER_ERROR("!!!!!!!! %s --> MApp_MediaCodec_Initialize FALSE \n",__FUNCTION__);
            return FALSE;
        }
    }

    return TRUE;
}

BOOLEAN MApp_VDPlayer_MediaCodec_Finalize(void)
{
    if(m_bMM_Initial == TRUE)
    {
        if (MApp_MediaCodec_Destroy() == TRUE)
        {
              // We can call MApp_MediaCodecTask(void) to do Demux/ Decode..
              //printf("\n\n***************MApp_MediaCodec_Destroy***************\n\n\n");
              m_bMM_Initial = FALSE;

              return TRUE;
        }
        else
        {
            //something error
            VDPLAYER_ERROR("!!!!!!!! %s --> MApp_MediaCodec_Destroy FALSE \n",__FUNCTION__);
            return FALSE;

        }
    }

    return TRUE;
}

BOOLEAN MApp_VDPlayer_MediaCodec_IsReady(void)
{
    return m_bMM_Initial;
}
#endif

#if ENABLE_PROBE_MOVIE_HEADER
void MApp_VDPlayer_BeginProbeHeaderOnly()
{
    m_bVDPlayerProbeHeaderOnly = TRUE;
}

void MApp_VDPlayer_StopProbeHeaderOnly()
{
    m_bVDPlayerProbeHeaderOnly = FALSE;
}
#endif

//******************************************************************************
/// Set video delay time in millisecond for A/V sync.
/// @param  u32VideoSyncDelayMsTime \b IN  Specify video delay time in millisecond.
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN MApp_VDPlayer_SetVideoSyncDelayMsTime(U32 u32VideoSyncDelayMsTime)
{
    m_u32VideoSyncDelayMsTime = u32VideoSyncDelayMsTime;

    return TRUE;
}

//******************************************************************************
/// Get video delay time in millisecond for A/V sync.
/// @param  NA
/// @return video delay time in millisecond.
//******************************************************************************
U32 MApp_VDPlayer_GetVideoSyncDelayMsTime(void)
{
    return m_u32VideoSyncDelayMsTime;
}

//******************************************************************************
/// Get current movie audio codecID can support or not.
/// @param  NA
/// @return TRUE if supported, FALSE not supported.
//******************************************************************************
BOOLEAN MApp_VDPlayer_GetMovieAudioCodecSupported(void)
{
    U32 u32AudioCodecID;
    BOOLEAN bRet = FALSE;
    u32AudioCodecID = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_CODEC_ID);

    if(g_bUnsupportAudio) //like HT3.1 I12
    {
        //This means Audio codeID is correct but audio raw data is wrong
        //or from kc side : if ((MApp_VDPlayer_GetShareMemInfo(E_SHAREMEM_TOTAL_AUDIO_TRACK) == 0) && (msAPI_VDPlayer_Demuxer_GetAudioTrackCount() > 0))
        return FALSE;
    }
    else
    {
        if(_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_AUDIO_TRACK)==0)
        {
            return FALSE; //no audio track case, like DivX HD1080p I03, show unsupported UI
        }
        else
        {
            switch (u32AudioCodecID)
            {
                case E_VDP_CODEC_ID_WMAV1:
                case E_VDP_CODEC_ID_WMAV2:
                case E_VDP_CODEC_ID_WMAV3:
                case E_VDP_CODEC_ID_DTS:
                case E_VDP_CODEC_ID_DTS_HD:
                case E_VDP_CODEC_ID_DTS_EXPRESS:
                case E_VDP_CODEC_ID_MP3:
                case E_VDP_CODEC_ID_MP2:
                case E_VDP_CODEC_ID_AC3:
                case E_VDP_CODEC_ID_EAC3:
                case E_VDP_CODEC_ID_AAC:
                case E_VDP_CODEC_ID_MPEG4AAC:
                case E_VDP_CODEC_ID_FLAC:
                case E_VDP_CODEC_ID_PCM_S16LE:
                case E_VDP_CODEC_ID_PCM_S16BE:
                case E_VDP_CODEC_ID_PCM_U16LE:
                case E_VDP_CODEC_ID_PCM_U16BE:
                case E_VDP_CODEC_ID_PCM_S8:
                case E_VDP_CODEC_ID_PCM_U8:
                case E_VDP_CODEC_ID_PCM_MULAW:
                case E_VDP_CODEC_ID_PCM_ALAW:
                case E_VDP_CODEC_ID_ADPCM_IMA_QT:
                case E_VDP_CODEC_ID_ADPCM_IMA_WAV:
                case E_VDP_CODEC_ID_ADPCM_IMA_DK3:
                case E_VDP_CODEC_ID_ADPCM_IMA_DK4:
                case E_VDP_CODEC_ID_ADPCM_IMA_WS:
                case E_VDP_CODEC_ID_ADPCM_IMA_SMJPEG:
                case E_VDP_CODEC_ID_ADPCM_MS:
                case E_VDP_CODEC_ID_ADPCM_4XM:
                case E_VDP_CODEC_ID_ADPCM_XA:
                case E_VDP_CODEC_ID_ADPCM_ADX:
                case E_VDP_CODEC_ID_ADPCM_EA:
                case E_VDP_CODEC_ID_ADPCM_G726:
                case E_VDP_CODEC_ID_RAAC:
                case E_VDP_CODEC_ID_RACP:
                case E_VDP_CODEC_ID_COOK:
                case E_VDP_CODEC_ID_DRA:
                case E_VDP_CODEC_ID_VORBIS:
                    bRet = TRUE;
                break;

                default:
                    bRet = FALSE;
                break;
            }
        }
    }
    return bRet;
}

//******************************************************************************
/// Query audio language by audio track index.
/// @param u16AudioTrack \b IN: audio track index
/// @return four characters in U32
//******************************************************************************
U32 MApp_VDPlayer_GetAudioLanguageByTrackIndex(U16 u16AudioTrack)
{
    if(u16AudioTrack >= _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_AUDIO_TRACK))
    {
        return 0;
    }
    return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_AUDIO_LANGUAGE+u16AudioTrack);
}

//******************************************************************************
/// Query internal subtitle language by subtitle track index.
/// @param u16SubtitleTrack \b IN: subtitle track index
/// @return four characters in U32
//******************************************************************************
U32 MApp_VDPlayer_GetInternalSubtitleLanguageByTrackIndex(U16 u16SubtitleTrack)
{
    if(u16SubtitleTrack >= _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TOTAL_SUBTITLE))
    {
        return 0;
    }
    return _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_SUBTITLE_LANGUAGE+u16SubtitleTrack);
}

//******************************************************************************
/// Set suspend Internal Subtitle from AEON into Queue.
/// @param  bSuspend \b IN  Specify suspend Internal Subtitle or not.
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN MApp_VDPlayer_SetSuspendInternalSubtitle2Queue(BOOLEAN bSuspend)
{
    m_bSuspendInternalSubtitle2Queue = bSuspend;

    return TRUE;
}

#if ENABLE_PIP
BOOLEAN MAPP_VDPlayer_SetPIPDisplayWindow(SCALER_WIN eWindow, MS_WINDOW_TYPE *pstDispWin)
{
    if(eWindow == MAIN_WINDOW)
    {
        if(pstDispWin == NULL)
        {
            if (m_eVDPlayerFlgs & E_VDPLAYER_FLG_PREVIEW)
            {
                MS_WINDOW_TYPE tDstWin = {_gu16PreviewX, _gu16PreviewY, _gu16PreviewWidth, _gu16PreviewHeight};

                #if ( defined(SCALER_DNR_BUF_PREV_ADR))
                //printf("Set FB = DNR_Prev %X %X\n", SCALER_DNR_BUF_PREV_ADR, SCALER_DNR_BUF_PREV_LEN );
                MApi_XC_SetFrameBufferAddress(SCALER_DNR_BUF_PREV_ADR, SCALER_DNR_BUF_PREV_LEN, MAIN_WINDOW);
                MApi_XC_SetAutoPreScaling(ENABLE, MAIN_WINDOW);
                #else
                MApi_XC_SetFrameBufferAddress(SCALER_DNR_BUF_ADR, SCALER_DNR_BUF_LEN, MAIN_WINDOW);
                #endif


                MApp_Scaler_EnableOverScan(FALSE);

                #if DYNSCALING
                if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_ENABLE_DYNSCALING)==1)
                {
                    MS_WINDOW_TYPE tCapWin;
                    tCapWin.x = MDrv_MVOP_GetHStart();
                    tCapWin.y = MDrv_MVOP_GetVStart();
                    tCapWin.width = gstVidStatus.u16HorSize;
                    tCapWin.height = gstVidStatus.u16VerSize;
                    MApp_Scaler_SetWindow(&tCapWin, NULL, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                    SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW); //?? aspect ration??
                    //_MApp_VDPlayer_SendXCStatus2Firmware(stDS_Info.u32DS_Info_BaseAddr + (1024*3), MAIN_WINDOW);
                }
                else
                #endif
                {
                    MApp_Scaler_SetWindow(NULL, NULL, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                        SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW); //?? aspect ration??
                }
            }
            else
            {
                MApp_Scaler_EnableOverScan(FALSE);
                if (MApi_XC_IsCurrentFrameBufferLessMode())
                {
                    // NOTE: RM and VC1 not concider FB case
                    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                    stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                }
                else
                {
                    _MApp_VDPlayer_ScaleScalerWindows(VDPLAYER_ZOOM_FACT_NORMAL, TRUE);
                }
            }
            return TRUE;
        }
        else
        {
             printf("\r\n pstDispWin != NULL is not Support");
        }
    }
    else
    {
         printf("\r\n sub window  can not support storage");
    }
    return FALSE;
}
#endif

//******************************************************************************
/// Check Fail Status which cause by user press EXIT key, or by error case.
/// @param  void
/// @return EN_VDPLAYER_FAIL_STATUS
//******************************************************************************
EN_VDPLAYER_FAIL_STATUS MApp_VDPlayer_CheckFailStatus(void)
{
    return m_eFailStatus;
}

//******************************************************************************
/// Check Supported Audio, and SetShareMem to VDPlayer
/// @param void
/// @return  u32UnsupportedAudioCodec
//******************************************************************************
static U32 _MApp_VDPlayer_CheckSupportedAudio(void)
{
    U32  u32UnsupportedAudioCodec = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_SUPPORTED_AUDIO);
    U64 u64SupportAudio = 0;
    u64SupportAudio=MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_capability);

    if (((u64SupportAudio & Audio_DEC_PCM)==0)&&((u64SupportAudio&Audio_DEC_XPCM)==0))
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_PCM;
    }
    if ((u64SupportAudio & Audio_DEC_MPEG)==0)
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_MPG;
    }
    if ((u64SupportAudio & Audio_DEC_AC3)==0)
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_AC3;
    }
    if ((u64SupportAudio & Audio_DEC_AC3P)==0)
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_EAC3;
    }
    if (((u64SupportAudio & Audio_DEC_AAC_LC)==0)&&((u64SupportAudio & Audio_DEC_HEAAC_V1)==0)&&((u64SupportAudio & Audio_DEC_HEAAC_V2)==0)&&((u64SupportAudio & Audio_DEC_DOLBYPULSE)==0))
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_AAC;
    }
    if (((u64SupportAudio & Audio_DEC_WMA)==0)&&((u64SupportAudio & Audio_DEC_WMAPRO)==0))
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_WMA;
    }
    if ((u64SupportAudio & Audio_DEC_RA8)==0)
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_RM;
    }
    if ((u64SupportAudio & Audio_DEC_DTS)==0)
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_DTS;
    }
    if ((u64SupportAudio & Audio_DEC_FLAC)==0)
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_FLAC;
    }
    if ((u64SupportAudio & Audio_DEC_VORBIS)==0)
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_VORBIS;
    }
    if ((u64SupportAudio & Audio_DEC_AMR_NB)==0)
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_AMR_NB;
    }
    if ((u64SupportAudio & Audio_DEC_AMR_WB)==0)
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_AMR_WB;
    }
    if ((u64SupportAudio & Audio_DEC_DRA)==0)
    {
        u32UnsupportedAudioCodec |=E_VDP_AUDIO_NO_SUPPORT_DRA;
    }
    return u32UnsupportedAudioCodec;
}
#endif // #if (ENABLE_DMP)

#undef MAPP_VIDEOPLAYER_C

