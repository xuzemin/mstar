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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MSAPI_MUSIC_H
#define _MSAPI_MUSIC_H

// Include files
#include "datatype.h"

#include "msAPI_audio.h"

#ifdef MSAPI_MUSIC_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define MP3_TAG_XING                0x58696E67
#define MP3_TAG_VBRI                0x56425249
#define MP3_FLAG_VBR_XING           0x01   //for Xing
#define MP3_FLAG_VBR_VBRI           0x02
#define MP3_INVALID_RATE 0xffff
#define ES_ALIGNMENT 128 //128 bytes

/// MP3 deocde result
typedef enum
{
    MP3_RESULT_PASS = 0,       ///< Pass
    MP3_RESULT_TIMEOUT,        ///< DSP timeout
    MP3_RESULT_ABORT,          ///< User abort: Remote controller or card plugged out
    MP3_RESULT_DECODE_FAIL,    ///< Decode failed
    MP3_RESULT_FILE_ERROR,     ///< MP3 file error
} MP3_RESULT;

/// MP3 decode status
typedef enum
{
    MP3_DECODE_RUNNING = 0x00, ///< Keep decoding
    MP3_DECODE_ERROR1,         ///< Error # 1
    MP3_DECODE_ERROR2,         ///< Error # 2
    MP3_DECODE_ERROR3,         ///< Error # 3
    MP3_DECODE_ERROR4,         ///< Error # 4
    MP3_DECODE_ERROR5,         ///< Error # 5
    MP3_DECODE_ERROR6,         ///< Error # 6
    MP3_DECODE_DONE    = 0xFF  ///< Done
} MP3_DECODE_STATUS;

/// MP3 Version
typedef enum
{
    EN_MP3_VERSION_2_5 = 0x0,
    EN_MP3_VERSION_RESERVED = 0x1,
    EN_MP3_VERSION_2 = 0x2,
    EN_MP3_VERSION_1 = 0x3,
    EN_MP3_VERSION_NOT_DETERMINE_YET = 0xFF,
} EN_MP3_VERSION;

/// MP3 Layer
typedef enum
{
    EN_MP3_LAYER_RESERVED = 0x0,
    EN_MP3_LAYER_3 = 0x1,
    EN_MP3_LAYER_2 = 0x2,
    EN_MP3_LAYER_1 = 0x3,
    EN_MP3_LAYER_NOT_DETERMINE_YET = 0xFF,
} EN_MP3_LAYER;

#define MP3_INFO_LENGTH 64
#define MP3_INFO_YEAR_LENGTH 12
typedef struct
{
    U8 title[MP3_INFO_LENGTH];
    U8 artist[MP3_INFO_LENGTH];
    U8 album[MP3_INFO_LENGTH];
    U8 year[MP3_INFO_YEAR_LENGTH];
    U8 comment[MP3_INFO_LENGTH];
    U8 GenreStr[MP3_INFO_LENGTH];
    U8 genre;
    U8 u8TitleLength;
    U8 u8ArtistLength;
    U8 u8AlbumLength;
    U8 u8GenreLength;
    U32  jpgOffset;
    U32  jpgSize;
    EN_MP3_LAYER en_layer;
    U32 u32ID3TagSize;
} MP3_INFO;

#define MP3_TAG_ID3v1_LENGTH 4 //if ID3v2 < 4 bytes , we display ID3v1 tag

#define MP3_TAG_ID3v2_3_TALB      0x54414C42
#define MP3_TAG_ID3v2_3_TPE1      0x54504531
#define MP3_TAG_ID3v2_3_TCOM      0x54434F4D
#define MP3_TAG_ID3v2_3_TEXT      0x54455854
#define MP3_TAG_ID3v2_3_TIT1      0x54495431
#define MP3_TAG_ID3v2_3_TIT2      0x54495432
#define MP3_TAG_ID3v2_3_TLEN      0x544C454E
#define MP3_TAG_ID3v2_3_TYER      0x54594552
#define MP3_TAG_ID3v2_3_APIC      0x41504943
#define MP3_TAG_ID3v2_3_TCON      0x54434F4E

#define MP3_TAG_ID3v2_4_TDRC      0x54445243

#define MP3_TAG_ID3v2_2_TAL      0x54414C
#define MP3_TAG_ID3v2_2_TCM     0x54434D
#define MP3_TAG_ID3v2_2_TT1      0x545431
#define MP3_TAG_ID3v2_2_TT2      0x545432
#define MP3_TAG_ID3v2_2_TYE      0x545945
#define MP3_TAG_ID3v2_2_COM      0x434F4D
#define MP3_TAG_ID3v2_2_PIC      0x504943
#define MP3_TAG_ID3v2_2_TCO      0x54434F

INTERFACE void msAPI_Music_Init(En_DVB_decSystemType enDecSystem, U16 u16InitVolume);
INTERFACE void msAPI_Music_StartDecode(void);
INTERFACE void msAPI_Music_SetAudioParam(En_DVB_decSystemType enDecSystem);
INTERFACE void msAPI_Music_StartDecodeEnhance(BOOLEAN bNewAudioMode);
INTERFACE void msAPI_Music_StartBrowse(void);
INTERFACE void msAPI_Music_StopDecode(void);
INTERFACE void msAPI_Music_PauseDecode(void);
INTERFACE U8 msAPI_Music_CheckPlayDone(void);
INTERFACE EN_MP3_LAYER msAPI_Music_GetLayer(void);
INTERFACE U32 msAPI_Music_AudioIsSupported(void);
INTERFACE U8 msAPI_Music_CheckInputRequest(U32 *pU32WrtAddr, U32 *pU32WrtBytes);
INTERFACE void msAPI_Music_SetInput(void);
INTERFACE void msAPI_Music_SetSampleRateIndex(U16 u16Index);
INTERFACE void msAPI_Music_SetXPCMParam(XPCM_TYPE audioType, U8 channels, U16 sampleRate, U8 bitsPerSample, U16 blockSize, U16 samplePerBlock);
INTERFACE void msAPI_Music_FileEndDataHandle(U32 u32DataLeft);
INTERFACE BOOLEAN msAPI_Music_Parse_ID3v1(U32 u32FileBuffAddr, MP3_INFO *pMp3InfoPtr);
INTERFACE U32 msAPI_Music_Parse_ID3v2(U32 u32FileHandle, U32 u32FileBuffAddr, U32 u32FileBuffLen, MP3_INFO *pMp3InfoPtr, BOOLEAN bGetMp3OffsetOnly);
INTERFACE BOOLEAN msAPI_Music_ReMapGenreStr(U8 *pu8SrcString, U8 *pu8SrcStrLen);
INTERFACE EN_MP3_LAYER msAPI_Music_Parse_Layer(U32 u32FileBuffAddr);
INTERFACE U32 msAPI_Music_GetPlayTick(void);
INTERFACE U16 msAPI_Music_GetEsMEMCnt(void);
INTERFACE void msAPI_Music_CleanFileEndData(U32 StrAddr, U32 length, U32 ClearValue);

INTERFACE U32 msAPI_Music_GetMP3CBRFrameSize(U8 u8Version,U8 u8Layer,U8 u8PaddingFlag,U8 u8SampleRateIndex,U8 u8BitRateIndex);

INTERFACE U32 msAPI_Music_GetFileTime(
        U32 u32FileBuffAddr,
        U32 u32FileSize,
        EN_MP3_VERSION *penVersion,
        EN_MP3_LAYER *penLayer,
        U16 *u16BitRate,
        U32 *pu16SampleRate,
        U8 *bFlag,
        U16 *pu16TOCLength,
        U8 *pu8TOC);

INTERFACE U16 msAPI_Music_GetResidualBufferSize(void);
INTERFACE U16 msAPI_Music_GetPCMBufferSize(U16 u16BitRate);
INTERFACE U16 msAPI_Music_GetPCMBufferSize2(U16 u16BitRate,U32 u32SampleRate);
INTERFACE U32 msAPI_Music_GetCurrentFrameNumber(void);
INTERFACE U16 msAPI_Music_GetSampleRate(void);
INTERFACE U16 msAPI_Music_GetBitRate(void);
INTERFACE U32 msAPI_Music_GetBitRateByIndex(U8 u8Version, U8 u8Layer, U8 u8BitRateIndex);

#undef INTERFACE
#endif
