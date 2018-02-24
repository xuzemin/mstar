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
#ifndef _MSAPI_JPEG_H
#define _MSAPI_JPEG_H

// Include files
#include "datatype.h"
#include "apiXC.h"
#include "msAPI_Video.h"
#include "msAPI_audio.h"

#ifdef MSAPI_JPEG_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#if ENABLE_CI_PLUS
#define MOVIE_THUMBNAIL 0
#else
#define MOVIE_THUMBNAIL 1
#endif
#define JPEG_INIT_DECODE        0
#define JPEG_INIT_ENCODE        1

#define JPEG_SINGLE_BUFFER_SIZE     (3*1024)    // 3 KB

//JPEG resolution definition
#if(MEMORY_MAP < MMAP_64MB)
    #define JPEGBASEWIDTHMAX    1366
    #define JPEGBASEHEIGHTMAX   768
#else
    #define JPEGBASEWIDTHMAX    1600
    #define JPEGBASEHEIGHTMAX   1200
#endif

#define JPEGPROWIDTHMAX 1024
#define JPEGPROHEIGHTMAX 768

/// JPEG output resolution
typedef enum
{
    JPEG_OUTPUT_FORMAT_HD,         ///< HD mode: with buffer size 1920x1088x2 bytes.
    JPEG_OUTPUT_FORMAT_SD,         ///< SD mode: with buffer size 720x480x2 bytes
} JPEG_OUTPUT_FORMAT;

/// JPEG deocde result
typedef enum
{
    JPEG_RESULT_PASS = 0,       ///< Pass
    JPEG_RESULT_TIMEOUT,        ///< DSP timeout
    JPEG_RESULT_ABORT,          ///< User abort: Remote controller or card plugged out
    JPEG_RESULT_DECODE_FAIL,    ///< Decode failed
    JPEG_RESULT_FILE_ERROR,     ///< JPEG file error
} JPEG_RESULT;

/// JPEG decode status
typedef enum
{
    JPEG_DECODE_RUNNING = 0x00, ///< Keep decoding
    JPEG_DECODE_ERROR1,         ///< Error # 1
    JPEG_DECODE_ERROR2,         ///< Error # 2
    JPEG_DECODE_ERROR3,         ///< Error # 3
    JPEG_DECODE_ERROR4,         ///< Error # 4
    JPEG_DECODE_ERROR5,         ///< Error # 5
    JPEG_DECODE_ERROR6,         ///< Error # 6
    JPEG_DECODE_DONE    = 0xFF  ///< Done
} JPEG_DECODE_STATUS;

/// JPEG decoder state
typedef enum
{
    JPEG_DECODER_STATE_INPUT = 1,
    JPEG_DECODER_STATE_DECODE,
    JPEG_DECODER_STATE_OUTPUT,
    JPEG_DECODER_STATE_INITIAL = 0x11,
} JPEG_DECODER_STATE;

typedef enum
{
    E_JPEG_EN_NOT_READY = 0x0,
    E_JPEG_EN_NO_ERR,
    E_JPEG_EN_NO_INTER_BUFFER_TOO_SMALL,
    E_JPEG_EN_STOPPED_BY_USER,
    E_JPEG_EN_GENERAL_ERR,
} E_JPEG_EN_ERROR_CODE;

/// JPEG information
typedef struct
{
    //LOGO_RESOLUTION enJpegQuality;  ///< JPEG output resolution
    //DTVRES_RESOLUTION_TYPE  enDisplayResolution;    ///< Display resolution (for scalar)

    //  Below are used as VOP input parameters
    U32     u32YAddress;    ///< Y address
    U32     u32UVAddress;   ///< UV address
    U16     u16Width;       ///< Width
    U16     u16Height;      ///< Height
    U16     u16OrigWidth;   ///< Original width
    U16     u16OrigHeight;  ///< Original width
    //bool    bInterlace;     ///< Interlace or progressive
    bool    bYUV422;        ///< TRUE: YUV 422; FALSE: YUV 420
    bool    bSD;            ///< TRUE: SD mode; FALSE: HD mode

    /* cc.chen - T.B.D. */
    bool        bLogoReady;     ///< TRUE: Logo is available; FALSE: Otherwise
    bool        bShowing;       ///< TRUE: Showing logo now; FALSE: Otherwise

} JPEG_INFO;

#define JPEG_DISPLAY_ALIGN_ORIGINAL     0
#define JPEG_DISPLAY_ALIGN_CENTER       1

typedef struct
{
    U16 u16X;
    U16 u16Y;
    U16 u16Width;
    U16 u16Height;
    U16 u16SrcWidth;
    U16 u16SrcPitch;
    U16 u16SrcHeight;
    U32 u32DispBuff;
    U16 u16DispBuffPitch;
    U8  enFormat;
    U8  u8Align;
} JPEG_DISPLAY_INFO;

typedef enum
{
    JPEG_ROTATE_0,
    JPEG_ROTATE_90,
    JPEG_ROTATE_180,
    JPEG_ROTATE_270,
    JPEG_ROTATE_NUM
} JPEG_ROTATE_CMD;

typedef enum
{
    MB_JPEG_CMD_NONE                     = 0x00,

    // 51 --> Aeon
    MB_JPEG_CMD_RESET                    = 0x11,
    MB_JPEG_CMD_GET_STATUS               = 0x12,
    MB_JPEG_CMD_FEED_DATA_SUCCESS        = 0x13,
    MB_JPEG_CMD_DECODE_HEADER            = 0x15,
    MB_JPEG_CMD_DECODE_LINE              = 0x16,
    MB_JPEG_CMD_GET_PIC_INFO             = 0x17,
    MB_JPEG_CMD_GET_PIC_ORIGINAL_SIZE    = 0x18,
    MB_JPEG_CMD_SET_RATIO                = 0x19,
    MB_JPEG_CMD_DECODE_INIT              = 0x20,
    MB_JPEG_CMD_STOP_DECODE              = 0x21,

    // Aeon --> 51
    MB_JPEG_CMD_ASK_4_DATA               = 0x80,
    MB_JPEG_CMD_RETURN_STATUS            = 0x81,
    MB_JPEG_CMD_RETURN_PIC_INFO          = 0x82,
    MB_JPEG_CMD_RETURN_PIC_ORIGINAL_SIZE = 0x83,
    MB_JPEG_CMD_RETURN_LOOP_OVER         = 0x84,
    MB_JPEG_CMD_GET_RESOLUTION           = 0x85,
    MB_JPEG_CMD_STOP_DECODE_ACK          = 0x86,
} MB_JPEG_CMD;

typedef enum
{
    e_Idle          = 0x01,
    e_DecodeErr     = 0x02,
    e_DecodeHeader  = 0x03,
    e_DecodeLine    = 0x04,
    e_DecodeDone    = 0x05,
    e_Init          = 0x06,
} EN_DECODE_STATE;

typedef enum
{
    MB_JPEG_EN_CMD_NONE                     = 0x00,

    // 51 --> Aeon
    MB_JPEG_EN_CMD_SET_READ_BUFF_INFO       = 0x11,
    MB_JPEG_EN_CMD_SET_INTERNAL_BUFF_INFO   = 0x12,
    MB_JPEG_EN_CMD_SET_WRITE_BUFF_INFO      = 0x13,
    MB_JPEG_EN_CMD_SET_RESOLUTION_INFO      = 0x14,

    // Aeon --> 51
    MB_JPEG_EN_RESULT                       = 0x80,
} MB_JPEG_EN_CMD;

// EXIF flags
#define JPEG_EXIF_HEADER_EXIST          0x01
#define JPEG_EXIF_THUMBNAIL_EXIST       0x02

//INTERFACE void msAPI_JPEG_Init(void);
INTERFACE BOOLEAN msAPI_JPEG_Init(U8 u8Type);
INTERFACE void msAPI_JPEGEncoder_Init(void);
INTERFACE void msAPI_JPEG_InitJpegInfo(JPEG_OUTPUT_FORMAT enJpegOutputFormat, U32 u32JpegOutputAddr);
INTERFACE BOOLEAN msAPI_JPEG_GetImageInfo(BOOLEAN bThumbnail, U16 *u16Width, U16 *u16Height);
INTERFACE void msAPI_JPEG_StartDecode(U32 u32InternalBuffAddr, U32 u32InternalBuffLen, U32 u32InputDataAddr, U32 u32InputDataLen,U32 u32OutputDataAddr, U8 u8Type);
INTERFACE void msAPI_JPEG_ProceedDecode(U32 u32DataSize);
INTERFACE JPEG_DECODER_STATE msAPI_JPEG_GetDecoderState(U32 *pu32Addr, U32 *pu32Size);
INTERFACE JPEG_DECODE_STATUS msAPI_JPEG_GetDecodeStatus(void);
INTERFACE void msAPI_JPEG_Restart(void);
INTERFACE void msAPI_JPEG_CloseDisplayPath(void);
INTERFACE void msAPI_Jpeg_SetDisplayInfo(U16 u16OutputX, U16 u16OutputY, U16 u16OutputWidth, U16 u16OutputHeight, U32 u32DecodeAddr, U16 u16LineSize, U8 enGopDFormat, U8 u8Align);
INTERFACE void msAPI_JPEG_Display(U8 bOriginalAspect);
INTERFACE void msAPI_JPEG_GetSize(U16 *u16Width, U16 *u16Height);
INTERFACE void msAPI_JPEG_GetPitch(U16 *u16Pitch);
INTERFACE void msAPI_JPEG_StopDecoding(void);
INTERFACE void msAPI_JPEG_SetSize(U16 u16Width, U16 u16Height, U16 u16Pitch);
INTERFACE void msAPI_JPEG_Display2(
        U16 u16InputX, U16 u16InputY, U16 u16InputWidth, U16 u16InputHeight,
        U16 u16OutputX, U16 u16OutputY, U16 u16OutputWidth, U16 u16OutputHeight,
        U32 u32SrcAddr, U16 u16SrcWidth, U16 u16SrcHeight,
        U32 u32DestAddr, U32 u32DestSize, U16 u16LineSize, U8 enGopDFormat);

INTERFACE void msAPI_JPEG_Display2_Movie_Thumbnail(
        U16 u16OutputWidth, U16 u16OutputHeight,
        U32 u32DestAddr, U32 u32DestSize, U16 u16LineSize, U8 enGopDFormat);

INTERFACE void msAPI_JPEG_AdjustDisplay(
        U16 u16InputX, U16 u16InputY, U16 u16InputWidth, U16 u16InputHeight,
        U16 u16OutputX, U16 u16OutputY, U16 u16OutputWidth, U16 u16OutputHeight);

INTERFACE BOOLEAN msAPI_JPEG_EncoderInit(void);
INTERFACE BOOLEAN msAPI_JPEG_StartEncode(
        U32 u32InternalBuffAddr,
        U32 u32InternalBuffLen,
        U32 u32InputDataAddr,
        U32 u32InputDataLen,
        U32 u32OutputBuffAddr,
        U32 u32OutputBuffLen,
        U16 u16Width,
        U16 u16Height);
INTERFACE E_JPEG_EN_ERROR_CODE msAPI_JPEG_GetEncoderState(U32 *pu32Size);

#undef INTERFACE
#endif
