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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
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

#ifndef _MAPP_PHOTO_H_
#define _MAPP_PHOTO_H_

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

///////////////////////////////////////////////////////////////////////////////
/// @file   mapp_photo.h
/// This file contains the interface for multimedia (MM) photo part
/// @author MStar Semiconductor Inc.
/// @brief  photo module, including decode/display/encode
///////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
#include "MsCommon.h"
#include "apiPNL.h"
#include "MApp_Exit.h"

#include "msAPI_FSCommon.h"
#include "MApp_UiMediaPlayer_Define.h"

#ifdef _MAPP_PHOTO_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif // #if _MAPP_PHOTO_C_

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#if ENABLE_4K2K
#define ENABLE_MAPP_PHOTO_BMP   ENABLE
#define ENABLE_MAPP_PHOTO_PNG   ENABLE
#define ENABLE_MAPP_PHOTO_GIF   DISABLE
#define ENABLE_MAPP_PHOTO_TIFF  DISABLE
#else
#define ENABLE_MAPP_PHOTO_BMP   ENABLE
#define ENABLE_MAPP_PHOTO_PNG   ENABLE
#define ENABLE_MAPP_PHOTO_GIF   ENABLE
#define ENABLE_MAPP_PHOTO_TIFF  ENABLE
#endif
// Photo Decoder
// Feature defintions
#define PHOTO_DECODE_MIN_WIDTH                      (0)
#define PHOTO_DECODE_MIN_HEIGHT                     (0)

#if ENABLE_4K2K
#define PHOTO_DECODE_JPEG_BASELINE_MAX_WIDTH        (3840)
#define PHOTO_DECODE_JPEG_BASELINE_MAX_HEIGHT       (2160)

#define PHOTO_DECODE_JPEG_PROGRESSIVE_MAX_WIDTH     (0)
#define PHOTO_DECODE_JPEG_PROGRESSIVE_MAX_HEIGHT    (0)

#define PHOTO_DECODE_BMP_MAX_WIDTH                  (2400)
#define PHOTO_DECODE_BMP_MAX_HEIGHT                 (1600)

#define PHOTO_DECODE_PNG_MAX_WIDTH                  (2400)
#define PHOTO_DECODE_PNG_MAX_HEIGHT                 (1600)

#define PHOTO_DECODE_TIFF_MAX_WIDTH                 (2400)
#define PHOTO_DECODE_TIFF_MAX_HEIGHT                (1600)

#define PHOTO_DECODE_GIF_MAX_WIDTH                  (1600)
#define PHOTO_DECODE_GIF_MAX_HEIGHT                 (1200)

#define PHOTO_DECODE_MAX_WIDTH                      (3840)
#define PHOTO_DECODE_MAX_HEIGHT                     (3840)

#define PHOTO_DECODE_MPO_BASELINE_MAX_WIDTH         (3840)
#define PHOTO_DECODE_MPO_BASELINE_MAX_HEIGHT        (2160)

#define PHOTO_DECODE_MPO_PROGRESSIVE_MAX_WIDTH      (0)
#define PHOTO_DECODE_MPO_PROGRESSIVE_MAX_HEIGHT     (0)

#else

#if (SUPPORT_MM_PHOTO_4K)//defined(SCALER_DNR_4K_PHOTO_BUF_LEN) && (SCALER_DNR_4K_PHOTO_BUF_LEN!=0)
#define PHOTO_DECODE_JPEG_BASELINE_MAX_WIDTH        (3840)
#define PHOTO_DECODE_JPEG_BASELINE_MAX_HEIGHT       (2160)
#else
#define PHOTO_DECODE_JPEG_BASELINE_MAX_WIDTH        (1920)
#define PHOTO_DECODE_JPEG_BASELINE_MAX_HEIGHT       (1088)
#endif

#define PHOTO_DECODE_JPEG_PROGRESSIVE_MAX_WIDTH     (1024)
#define PHOTO_DECODE_JPEG_PROGRESSIVE_MAX_HEIGHT    (768)

#define PHOTO_DECODE_BMP_MAX_WIDTH                  (1200)
#define PHOTO_DECODE_BMP_MAX_HEIGHT                 (800)

#define PHOTO_DECODE_PNG_MAX_WIDTH                  (1200)
#define PHOTO_DECODE_PNG_MAX_HEIGHT                 (800)

#define PHOTO_DECODE_TIFF_MAX_WIDTH                 (1200)
#define PHOTO_DECODE_TIFF_MAX_HEIGHT                (800)

#define PHOTO_DECODE_GIF_MAX_WIDTH                  (800)
#define PHOTO_DECODE_GIF_MAX_HEIGHT                 (600)

#if (SUPPORT_MM_PHOTO_4K)//defined(SCALER_DNR_4K_PHOTO_BUF_LEN) && (SCALER_DNR_4K_PHOTO_BUF_LEN!=0)
#define PHOTO_DECODE_MAX_WIDTH                      (3840)
#define PHOTO_DECODE_MAX_HEIGHT                     (2160)
#else
#define PHOTO_DECODE_MAX_WIDTH                      (1920)
#define PHOTO_DECODE_MAX_HEIGHT                     (1080)
#endif

#define PHOTO_DECODE_MPO_BASELINE_MAX_WIDTH         (1920)
#define PHOTO_DECODE_MPO_BASELINE_MAX_HEIGHT        (1080)

#define PHOTO_DECODE_MPO_PROGRESSIVE_MAX_WIDTH      (1024)
#define PHOTO_DECODE_MPO_PROGRESSIVE_MAX_HEIGHT     (768)
#endif

#define PHOTO_MAX_GIF_DELAY_TIME_SLOT_NUM           (64)
#define YUV422_BYTE_PER_PIXEL                       (2L)

// width/height of buffer used internally
#define PHOTO_ADJUSTED_PANEL_WIDTH  ((U16)PHOTO_ALIGNMENT(g_IPanel.Width()))
#define PHOTO_ADJUSTED_PANEL_HEIGHT (g_IPanel.Height())

#define PHOTO_SHRINK_BUFFER_0_WIDTH     PHOTO_ALIGNMENT(PHOTO_DECODE_MAX_WIDTH / 2 + 16 + 16)
#define PHOTO_SHRINK_BUFFER_0_HEIGHT    (PHOTO_DECODE_MAX_HEIGHT / 2 + 2)

#define PHOTO_SHRINK_BUFFER_1_WIDTH     PHOTO_ALIGNMENT(PHOTO_DECODE_MAX_WIDTH / 4 + 16 + 16)
#define PHOTO_SHRINK_BUFFER_1_HEIGHT    (PHOTO_DECODE_MAX_HEIGHT / 4 + 2)

// share memory
#define PHOTO_SHARE_MEM_BUFFER_ADDR (((PHOTO_SHARE_MEM_MEMORY_TYPE & MIU1) ? (PHOTO_SHARE_MEM_ADR | MIU_INTERVAL) : (PHOTO_SHARE_MEM_ADR)))
#define PHOTO_SHARE_MEM_BUFFER_SIZE (PHOTO_SHARE_MEM_LEN)

// Memory Layout for PHOTO decoder
// data buffer
#define PHOTO_DATA_BUFFER_ADDR      PHOTO_ALIGNMENT(((MAD_JPEG_READBUFF_MEMORY_TYPE & MIU1) ? (MAD_JPEG_READBUFF_ADR | MIU_INTERVAL) : (MAD_JPEG_READBUFF_ADR)))
#define PHOTO_DATA_BUFFER_SIZE      (MAD_JPEG_READBUFF_LEN)

#define PHOTO_OUTPUT_BUFFER_ADDR    PHOTO_ALIGNMENT(((MAD_JPEG_OUT_MEMORY_TYPE & MIU1) ? (MAD_JPEG_OUT_ADR | MIU_INTERVAL) : (MAD_JPEG_OUT_ADR)))
#define PHOTO_OUTPUT_BUFFER_SIZE    (MAD_JPEG_OUT_LEN)

// 0.0, Photo display buffer for full screen / preview
#define PHOTO_DISPLAY_BUFFER_ADDR   PHOTO_ALIGNMENT(((MAD_JPEG_DISPLAY_MEMORY_TYPE & MIU1) ? (MAD_JPEG_DISPLAY_ADR | MIU_INTERVAL) : (MAD_JPEG_DISPLAY_ADR)))
#define PHOTO_DISPLAY_BUFFER_SIZE   (MAD_JPEG_DISPLAY_LEN)

// co-buffers using PHOTO_DISPLAY_BUFFER_ADDR
// 1.0, thumbnail shrink buffer 0
#define PHOTO_THUMBNAIL_SHRINK_BUFFER_0_ADDR    PHOTO_ALIGNMENT(PHOTO_DISPLAY_BUFFER_ADDR)
#define PHOTO_THUMBNAIL_SHRINK_BUFFER_0_SIZE    (YUV422_BYTE_PER_PIXEL * PHOTO_SHRINK_BUFFER_0_WIDTH * PHOTO_SHRINK_BUFFER_0_HEIGHT)

// 1.1, thumbnail shrink buffer 0
#define PHOTO_THUMBNAIL_SHRINK_BUFFER_1_ADDR    PHOTO_ALIGNMENT(PHOTO_THUMBNAIL_SHRINK_BUFFER_0_ADDR + PHOTO_THUMBNAIL_SHRINK_BUFFER_0_SIZE)
#define PHOTO_THUMBNAIL_SHRINK_BUFFER_1_SIZE    (YUV422_BYTE_PER_PIXEL * PHOTO_SHRINK_BUFFER_1_WIDTH * PHOTO_SHRINK_BUFFER_1_HEIGHT)

#define PHOTO_POOL_BUFFER_ADDR      PHOTO_ALIGNMENT(((MAD_JPEG_INTERBUFF_MEMORY_TYPE & MIU1) ? (MAD_JPEG_INTERBUFF_ADR | MIU_INTERVAL) : (MAD_JPEG_INTERBUFF_ADR)))
#define PHOTO_POOL_BUFFER_SIZE      (MAD_JPEG_INTERBUFF_LEN)

// co-buffers using PHOTO_POOL_BUFFER_ADDR
// 0.0, memory pool
// currently used by BMP/PNG decoder on CP
#define PHOTO_MEMPOOL_BUFFER_ADDR       PHOTO_ALIGNMENT(PHOTO_POOL_BUFFER_ADDR)
#define PHOTO_MEMPOOL_BUFFER_SIZE       0x00100000    // 1M

#if (PHOTO_MEMPOOL_BUFFER_SIZE > PHOTO_POOL_BUFFER_SIZE)
    //PHOTO_POOL_BUFFER_SIZE at least 1M
    #error In-sufficient PHOTO_MEMPOOL_BUFFER
#endif

#if ENABLE_4K2K
// 0.1, source of display buffer
#define PHOTO_DISPLAY_SRC_BUFFER_ADDR   PHOTO_ALIGNMENT(PHOTO_MEMPOOL_BUFFER_ADDR + PHOTO_MEMPOOL_BUFFER_SIZE)
#define PHOTO_DISPLAY_SRC_BUFFER_SIZE   0

// 0.2, shrink buffer 0
#define PHOTO_SHRINK_BUFFER_0_ADDR      PHOTO_ALIGNMENT(PHOTO_DISPLAY_SRC_BUFFER_ADDR + PHOTO_DISPLAY_SRC_BUFFER_SIZE)
#define PHOTO_SHRINK_BUFFER_0_SIZE      0

// co-buffers using PHOTO_SHRINK_BUFFER_0_ADDR
//GIF delay time array buffer
#define PHOTO_GIF_FRAME_INFO_ARRAY_BUFFER_ADDR PHOTO_ALIGNMENT(PHOTO_SHRINK_BUFFER_0_ADDR)
#define PHOTO_GIF_FRAME_INFO_ARRAY_BUFFER_SIZE  0
#else
// 0.1, source of display buffer
#define PHOTO_DISPLAY_SRC_BUFFER_ADDR   PHOTO_ALIGNMENT(PHOTO_MEMPOOL_BUFFER_ADDR + PHOTO_MEMPOOL_BUFFER_SIZE)
#define PHOTO_DISPLAY_SRC_BUFFER_SIZE   PHOTO_DISPLAY_BUFFER_SIZE

// 0.2, shrink buffer 0
#define PHOTO_SHRINK_BUFFER_0_ADDR      PHOTO_ALIGNMENT(PHOTO_DISPLAY_SRC_BUFFER_ADDR + PHOTO_DISPLAY_SRC_BUFFER_SIZE)
#define PHOTO_SHRINK_BUFFER_0_SIZE      (YUV422_BYTE_PER_PIXEL * PHOTO_SHRINK_BUFFER_0_WIDTH * PHOTO_SHRINK_BUFFER_0_HEIGHT)

// 0.3, shrink buffer 1
#define PHOTO_SHRINK_BUFFER_1_ADDR      PHOTO_ALIGNMENT(PHOTO_SHRINK_BUFFER_0_ADDR + PHOTO_SHRINK_BUFFER_0_SIZE)
#define PHOTO_SHRINK_BUFFER_1_SIZE      (YUV422_BYTE_PER_PIXEL * PHOTO_SHRINK_BUFFER_1_WIDTH * PHOTO_SHRINK_BUFFER_1_HEIGHT)

// co-buffers using PHOTO_SHRINK_BUFFER_0_ADDR
//GIF delay time array buffer
#define PHOTO_GIF_FRAME_INFO_ARRAY_BUFFER_ADDR PHOTO_ALIGNMENT(PHOTO_SHRINK_BUFFER_0_ADDR)
#define PHOTO_GIF_FRAME_INFO_ARRAY_BUFFER_SIZE  (4L * PHOTO_MAX_GIF_DELAY_TIME_SLOT_NUM)
#endif

// co-buffers using PHOTO_POOL_BUFFER_ADDR
// 1.0
#define PHOTO_JPEG_PROGRESSIVE_BUFFER_ADDR PHOTO_ALIGNMENT(PHOTO_POOL_BUFFER_ADDR)
#define PHOTO_JPEG_PROGRESSIVE_BUFFER_SIZE PHOTO_POOL_BUFFER_SIZE

#if ENABLE_MPO_SUPPORT
    #ifdef MPO_DISPLAY_BUFFER_ADR
    #define PHOTO_DISPLAY_MPO_BUFFER_ADDR   (PHOTO_ALIGNMENT(MPO_DISPLAY_BUFFER_ADR))
    #define PHOTO_DISPLAY_MPO_BUFFER_SIZE   MPO_DISPLAY_BUFFER_LEN
    #else
    #error "MPO_DISPLAY_BUFFER_ADR is not define in mmap"
    #endif
#else
    //this macro should not be used
    #define PHOTO_DISPLAY_MPO_BUFFER_ADDR   0
    #define PHOTO_DISPLAY_MPO_BUFFER_SIZE   0
#endif

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define PHOTO_ALIGNMENT(v)   (((U32)(v) + (15L)) & ~(15L))
#define PHOTO_ALIGNMENT_32(v)   (((U32)(v) + (31L)) & ~(31L))

#ifndef ENABLE_HK_PHOTO
#define ENABLE_HK_PHOTO 0
#endif

//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------
typedef enum
{
    E_PHOTO_INFO_INPUT_DATA_FORMAT,
    E_PHOTO_INFO_FILE_FORMAT,
    E_PHOTO_INFO_IMAGE_TYPE,

    E_PHOTO_INFO_FILE_SIZE,
    E_PHOTO_INFO_IMAGE_WIDTH,
    E_PHOTO_INFO_IMAGE_HEIGHT,

    E_PHOTO_INFO_PITCH,
    E_PHOTO_INFO_WIDTH,
    E_PHOTO_INFO_HEIGHT,
    E_PHOTO_INFO_SIZE,

    E_PHOTO_INFO_HAS_THUMBNAIL,
    E_PHOTO_INFO_OUTPUT_FORMAT,
    E_PHOTO_INFO_PROGRESS,      // 0 ~ 100
    E_PHOTO_INFO_ERROR_INFO,

    //Exif information
    E_PHOTO_INFO_EXIF_WIDTH,
    E_PHOTO_INFO_EXIF_HEIGHT,
    E_PHOTO_INFO_ORIENTATION,
    E_PHOTO_INFO_HAS_DATE_TIME,
    E_PHOTO_INFO_DATE_TIME_YEAR,
    E_PHOTO_INFO_DATE_TIME_MONTH,
    E_PHOTO_INFO_DATE_TIME_DAY,
    E_PHOTO_INFO_DATE_TIME_HOUR,
    E_PHOTO_INFO_DATE_TIME_MINUTE,
    E_PHOTO_INFO_DATE_TIME_SECOND,

    //for gif animation
    E_PHOTO_INFO_DECODED_FRAME_INDEX,
    E_PHOTO_INFO_DISPLAYED_FRAME_INDEX,
    E_PHOTO_INFO_SLOT_NUM,
    E_PHOTO_INFO_FRAME_SIZE,

    //MPO
    E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE,

    E_PHOTO_INFO_SCALE_DOWN_FACTOR,
} EN_PHOTO_INFO;

typedef enum
{
    E_PHOTO_EXIF_INFO_CAMERA_MAKER,
    E_PHOTO_EXIF_INFO_CAMERA_MODEL,
    E_PHOTO_EXIF_INFO_FLASH_MODE,
    E_PHOTO_EXIF_INFO_ISO_SPEED,
    E_PHOTO_EXIF_INFO_EXPOSURE_BIAS,
    E_PHOTO_EXIF_INFO_EXPOSURE_TIME,
    E_PHOTO_EXIF_INFO_F_STOP,
    E_PHOTO_EXIF_INFO_FOCAL_LENGTH,
    E_PHOTO_EXIF_INFO_SHUTTER_SPEED,
    E_PHOTO_EXIF_INFO_APERTURE
} EN_PHOTO_EXIF_INFO;

typedef enum
{
    E_PHOTO_FILE_JPEG,
    E_PHOTO_FILE_BMP,
    E_PHOTO_FILE_PNG,
    E_PHOTO_FILE_TIFF,
    E_PHOTO_FILE_GIF,

    E_PHOTO_FILE_UNKNOWN,
} EN_PHOTO_FILE;

typedef enum
{
    E_PHOTO_IMAGE_JPEG_BASELINE,
    E_PHOTO_IMAGE_JPEG_PROGRESSIVE,
    E_PHOTO_IMAGE_BMP,
    E_PHOTO_IMAGE_PNG_NON_INTERLACED,
    E_PHOTO_IMAGE_PNG_INTERLACED,
    E_PHOTO_IMAGE_TIFF,
    E_PHOTO_IMAGE_GIF_NON_ANIMATION,
    E_PHOTO_IMAGE_GIF_ANIMATION,

    E_PHOTO_IMAGE_UNKNOWN,
} EN_PHOTO_IMAGE;

typedef enum
{
    E_PHOTO_OUTPUT_YUV422,
    E_PHOTO_OUTPUT_ARGB8888,
    E_PHOTO_OUTPUT_ARGB1555,

    E_PHOTO_OUTPUT_JPEG,

    E_PHOTO_OUTPUT_FORMAT_UNKNOWN,
} EN_PHOTO_OUTPUT_FORMAT;

typedef enum
{
    E_PHOTO_ERR_NONE = 0,
    E_PHOTO_ERR_NOT_SUPPORT_FILE_FMT,
    E_PHOTO_ERR_NOT_SUPPORT_IMAGE_FMT,
    E_PHOTO_ERR_DECODE_FAILURE,
    E_PHOTO_ERR_ENCODE_FAILURE,
    E_PHOTO_ERR_DATA_OPERATION_FAILURE,
    E_PHOTO_ERR_MEMORY_LAYOUT_VIOLATTION,
    E_PHOTO_ERR_NO_THUMBNAIL,
} EN_PHOTO_ERRCODE;

typedef enum
{
    E_PHOTO_ORIENT_RESERVED             = 0, // reserved, all rotation below is clockwise
    E_PHOTO_ORIENT_ROTATE_0             = 1, // rotate 0
    E_PHOTO_ORIENT_MIRROR_LR            = 2, // mirror left/right
    E_PHOTO_ORIENT_ROTATE_180           = 3, // rotate 180
    E_PHOTO_ORIENT_MIRROR_TB            = 4, // mirror top/bottom
    E_PHOTO_ORIENT_ROTATE_90_MIRROR_LR  = 5, // rotate 90 then mirror left/right
    E_PHOTO_ORIENT_E_ORIENT_ROTATE_90   = 6, // rotate 90
    E_PHOTO_ORIENT_ROTATE_90_MIRROR_TB  = 7, // rotate 90 then mirror top/bottom
    E_PHOTO_ORIENT_ROTATE_270           = 8, // rotate 270
    E_PHOTO_ORIENT_NOT_FOUND            = 9,
    E_PHOTO_ORIENT_UNDEFINE             = 10,
} EN_PHOTO_ORIENTATION;

// NOTES:
// MApp_Photo_DataRequestCallBack is the callback function registered by caller of this module.
// This callback function will be called when MApp_Photo module requires more data to be filled by caller.
// It should return how many bytes of data actually read and a negative return value implies EOF
typedef S32 (*MApp_Photo_DataRequestCallBack)(U8 *pu8BufferAddr, U32 u32RequestSize);

typedef struct
{
    U32 u32MinDecodeWidth;
    U32 u32MinDecodeHeight;

    U32 u32MaxDecodeJpegBaselineWidth;
    U32 u32MaxDecodeJpegBaselineHeight;

    U32 u32MaxDecodeJpegProgressiveWidth;
    U32 u32MaxDecodeJpegProgressiveHeight;

    U32 u32MaxDecodeBmpWidth;
    U32 u32MaxDecodeBmpHeight;

    U32 u32MaxDecodePngWidth;
    U32 u32MaxDecodePngHeight;

    U32 u32MaxDecodeTiffWidth;
    U32 u32MaxDecodeTiffHeight;

    U32 u32MaxDecodeGifWidth;
    U32 u32MaxDecodeGifHeight;

    U32 u32MaxDecodeMpoBaselineWidth;
    U32 u32MaxDecodeMpoBaselineHeight;

    U32 u32MaxDecodeMpoProgressiveWidth;
    U32 u32MaxDecodeMpoProgressiveHeight;
} ST_PHOTO_DECODE_RESOLUTION_DEFINTIONS;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Extern Functions
//------------------------------------------------------------------------------
INTERFACE void              MApp_Photo_MemCfg(
                                    U32 u32DataBufferAddr,      U32 u32DataBufferSize,
                                    U32 u32OutputBufferAddr,    U32 u32OutputBufferSize,
                                    U32 u32PoolMemAddr,         U32 u32PoolMemSize,
                                    U32 u32PoolBufferSize);
INTERFACE void MApp_Photo_DecodeResolutionCfg(ST_PHOTO_DECODE_RESOLUTION_DEFINTIONS stPhotoResolution);

INTERFACE void MApp_Photo_EnableStreamMode(BOOLEAN bEnabled);
INTERFACE void MApp_Photo_DoAlphaBlendForPng(BOOLEAN bEnabled);
INTERFACE BOOLEAN           MApp_Photo_DecodeFile_Init(FileEntry *pFileEntry, BOOLEAN bThumbnail);

// NOTE
// 1. please read the NOTE above the definition of MApp_Photo_DataRequestCallBack before register one.
// 2. if the value of MApp_Photo_DataRequestCallBack is
//  a. NULL --> all data is already in u32DataBufferAddr and data size is u32DataBufferSize of MApp_Photo_MemCfg()
//  b. != NULL --> don't fill any data to u32DataBufferAddr of MApp_Photo_MemCfg().
//     The callback function will be used for filling 1st bytes of data.
INTERFACE BOOLEAN           MApp_Photo_DecodeMemory_Init(BOOLEAN bThumbnail, MApp_Photo_DataRequestCallBack pfCallBack);
INTERFACE BOOLEAN           MApp_Photo_EncodeMemory_Init(U32 u32Width, U32 u32Height, MApp_Photo_DataRequestCallBack pfCallBack);

INTERFACE EN_RET            MApp_Photo_Main(void);
INTERFACE void              MApp_Photo_Stop(void);

INTERFACE EN_PHOTO_ERRCODE  MApp_Photo_GetErrCode(void);
INTERFACE U32               MApp_Photo_GetInfo(EN_PHOTO_INFO enInfo);
INTERFACE BOOLEAN           MApp_Photo_GetExifInfo(EN_PHOTO_EXIF_INFO enInfo, void *pBufAddr, U16 u16BufSize);
INTERFACE void              MApp_Photo_UpdateDisplayedFrameIndex(U32 u32DisplayedFrameIndex);
INTERFACE U32               MApp_Photo_GetFrameDelayTime(U32 u32FrameIndex);
INTERFACE BOOLEAN MApp_Photo_SetForceDisplayPhotoPartialError(BOOLEAN bForceDisPlay);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#undef INTERFACE

#endif // _MAPP_PHOTO_H_

