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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MSAPI_JPEG_H
#define    _MSAPI_JPEG_H

// Include files
#include "datatype.h"
#include "msAPI_Video.h"

#ifdef MSAPI_JPEG_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#define JPEG_SINGLE_BUFFER_SIZE     (3*1024)    // 3 KB
//JPEG resolution definition
#if (VIDEO_FIRMWARE_CODE == VIDEO_FIRMWARE_CODE_SD)
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
    JPEG_DECODER_STATE_STATUS = 0xBB,
} JPEG_DECODER_STATE;


#define JPEG_DISPLAY_ALIGN_ORIGINAL     0
#define JPEG_DISPLAY_ALIGN_CENTER       1

typedef struct
{
    U16 u16X;
    U16 u16Y;
    U16 u16Width;
    U16 u16Height;
    U16 u16SrcWidth;
    U16 u16SrcHeight;
    U16 u16OrigWidth;
    U16 u16OrigHeight;
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

#define JPEG_MARKER_SOI     0xFFD8
#define JPEG_MARKER_SOF0    0xFFC0
#define JPEG_MARKER_SOF2    0xFFC2
#define JPEG_MARKER_APP0    0xFFE0
#define JPEG_MARKER_APP1    0xFFE1
#define JPEG_MARKER_APP2    0xFFE2
#define JPEG_MARKER_SOS     0xFFDA
#define JPEG_TAG_JFIF       0x4A464946

#define JPEG_TAG_EXIF       0x45786966

#define JPEG_TIFF_BIG_ENDIAN            0x4D4D
#define JPEG_TIFF_LITTLE_ENDIAN         0x4949

#define JPEG_TIFF_TAG_IMAGE_WIDTH       0x0100
#define JPEG_TIFF_TAG_IMAGE_HEIGHT      0x0101
#define JPEG_TIFF_TAG_DATETIME          0x0132
#define JPEG_TIFF_TAG_TITLE             0x010E
#define JPEG_TIFF_TAG_ORIENTATION       0x0112
#define JPEG_TIFF_SOI_OFFSET            0x0201
#define JPEG_TIFF_TAG_EXIF_POINTER      0x8769

#define JPEG_EXIF_TAG_IMAGE_WIDTH       0xA002
#define JPEG_EXIF_TAG_IMAGE_HEIGHT      0xA003
#define JPEG_EXIF_TAG_DATETIME          0x9003


#define JPEG_EXIF_TYPE_BYTE             0x0001
#define JPEG_EXIF_TYPE_ASCII            0x0002
#define JPEG_EXIF_TYPE_SHORT            0x0003
#define JPEG_EXIF_TYPE_LONG             0x0004
#define JPEG_EXIF_TYPE_RATIONAL         0x0005
#define JPEG_EXIF_TYPE_UNDEFINED        0x0007
#define JPEG_EXIF_TYPE_SLONG            0x0009
#define JPEG_EXIF_TYPE_SRATIONAL        0x000A

typedef enum
{
    JPEG_EXIF_DECODE_REQUEST = 0x00,
    JPEG_EXIF_DECODE_DONE,
    JPEG_EXIF_DECODE_ERR_NOT_JPEG,
    JPEG_EXIF_DECODE_ERR_NO_EXIF,
    JPEG_EXIF_DECODE_ERR_FILE,
    JPEG_EXIF_DECODE_TIME_OUT,
} JPEG_EXIF_DECODE_STATUS;

typedef struct
{
    U16 u16Width;
    U16 u16Height;
    U8  u8Orientation;
    U8  u8DateTime[20];
    U8  u8Title[20];
    U32 u32FileSize;
    U8  u8Flags;
} JPEG_EXIF_INFO;


// EXIF flags
#define JPEG_EXIF_HEADER_EXIST          0x01
#define JPEG_EXIF_THUMBNAIL_EXIST       0x02

#define JPEG_ORIENT_ORIGINAL            0
#define JPEG_ORIENT_TOP_LEFT            1
#define JPEG_ORIENT_TOP_RIGHT           2
#define JPEG_ORIENT_BOTTOM_RIGHT        3
#define JPEG_ORIENT_BOTTOM_LEFT         4
#define JPEG_ORIENT_LEFT_TOP            5
#define JPEG_ORIENT_RIGHT_TOP           6
#define JPEG_ORIENT_RIGHT_BOTTOM        7
#define JPEG_ORIENT_LEFT_BOTTOM         8

// JPEG decoder only uses MAD_ES_BUFFER_ADR - MAD_ES_BUFFER_ADR + 2k
#define JPEG_FILE_BACKBUFF_ADDR         ((MAD_PCM_BUFFER_MEMORY_TYPE & MIU1) ? (MAD_PCM_BUFFER_ADR | MIU_INTERVAL) : (MAD_PCM_BUFFER_ADR))
#define JPEG_FILE_TIFF_BUFF             (JPEG_FILE_BACKBUFF_ADDR + 0x1000)

// JPEG information flags
#define JPEG_INFO_FLAG_JPEG         0x01
#define JPEG_INFO_FLAG_BASELINE     0x02
#define JPEG_INFO_FLAG_PROGRESSIVE  0x04
#define JPEG_INFO_FLAG_THUMBNAIL    0x10


INTERFACE BOOLEAN msAPI_JPEG_Init(JPEG_OUTPUT_FORMAT enJpegOutputFormat, U32 u32JpegOutputAddr);
INTERFACE BOOLEAN msAPI_JPEG_GetImageInfo(U16 *u16Width, U16 *u16Height);
INTERFACE U8 msAPI_JPEG_GetExifInfo(void);
INTERFACE void msAPI_JPEG_StartDecode(U32 u32JpegStartAddr, U32 u32JpegBlockSize);
INTERFACE JPEG_DECODE_STATUS msAPI_JPEG_GetDecodeStatus(void);
INTERFACE U8 msAPI_JPEG_GetDecoderState(void);
INTERFACE JPEG_RESULT msAPI_JPEG_CheckOutputStatus(void);
INTERFACE void msAPI_JPEG_Restart(void);
INTERFACE void msAPI_JPEG_CloseDisplayPath(void);
INTERFACE void msAPI_Jpeg_SetDisplayInfo(U16 u16OutputX, U16 u16OutputY, U16 u16OutputWidth, U16 u16OutputHeight, U32 u32DecodeAddr, U16 u16LineSize, U8 enGopDFormat, U8 u8Align);
INTERFACE void msAPI_Jpeg_EnableThumbnail(U8 bEnableThumb);
INTERFACE void msAPI_JPEG_Display(U16 u16VX, U16 u16VY, U16 *u16RealHSize, U16 *u16RealVSize, U8 bOriginalAspect);
INTERFACE void msAPI_JPEG_GetSize(U16 *u16Width, U16 *u16Height);
INTERFACE void msAPI_JPEG_DecodeExifInfo(JPEG_EXIF_INFO *pExifInfo, U16 u16ByteCnt);
INTERFACE void msAPI_JPEG_StopDecoding(void);
INTERFACE void msAPI_JPEG_Sof0Parser(JPEG_EXIF_INFO *pExifInfo, U16 u16ByteCnt);
INTERFACE U32 msAPI_JPEG_GetBytes(U8 u8ByteCnt);
INTERFACE void msAPI_JPEG_SkipByteCnt(U16 u16ByteCnt);
INTERFACE BOOLEAN msAPI_JPEG_DecodeExif_EndOfFile(void);
INTERFACE void msAPI_JPEG_DecodeExifInfo_Init(void);
INTERFACE void msAPI_JPEG_Rotate(U32 u32OutputBuff, U8 u8Orientation);

#undef INTERFACE
#endif
