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
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2010 MStar Semiconductor, Inc.
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
///////////////////////////////////////////////////////////////////////////////


#ifndef _MSAPI_STILLIMAGE_H_
#define _MSAPI_STILLIMAGE_H_

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
#include "datatype.h"
//#include "mm_types.h"

// TBD: this api includes app header ok?
#include "mapp_stillimage_sharememcfg.h"

#include "msapi_stillimage_defines.h"
#include "msapi_stillimage_bm.h"

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#undef INTERFACE
#ifdef  _MSAPI_STILLIMAGE_C_
#define INTERFACE
#else
#define INTERFACE       extern
#endif  // #ifdef  _MSAPI_STILLIMAGE_C_

//------------------------------------------------------------------------------
// Macros & Defines
//------------------------------------------------------------------------------
#ifndef _ALIGNMENT_
#define _ALIGNMENT_(x, a) ((((x) + (a - 1)) / (a)) * (a))
#endif // #ifndef _ALIGNMENT_

#ifndef EVEN_ALIGN
#define EVEN_ALIGN(x) ((x) + ((x)%2))
#endif // #ifndef EVEN_ALIGN

#define EXIF_CAMERA_MAKER_SIZE  32
#define EXIF_CAMERA_MODEL_SIZE  128

//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------
typedef enum
{
    E_STILLIMAGE_RET_OK         = 0,
    E_STILLIMAGE_RET_FAIL,

    E_STILLIMAGE_RET_WORKING,
    E_STILLIMAGE_RET_DECODE_ONE_FRAME_DONE, //for gif animation, return done after decode every fame.
    E_STILLIMAGE_RET_DONE,
} EN_STILLIMAGE_RET;

typedef struct
{
    EN_STILLIMAGE_CMD_TYPE enCmdType;

    U32 u32MinWidth;
    U32 u32MinHeight;

    U32 u32JpegBaseLineMaxWidth;
    U32 u32JpegBaseLineMaxHeight;

    U32 u32JpegProgressiveMaxWidth;
    U32 u32JpegProgressiveMaxHeight;

    U32 u32BmpMaxWidth;
    U32 u32BmpMaxHeight;

    U32 u32PngMaxWidth;
    U32 u32PngMaxHeight;

    U32 u32TiffMaxWidth;
    U32 u32TiffMaxHeight;

    U32 u32GifMaxWidth;
    U32 u32GifMaxHeight;

    U32 u32MPOBaseLineMaxWidth;
    U32 u32MPOBaseLineMaxHeight;

    U32 u32MPOProgressiveMaxWidth;
    U32 u32MPOProgressiveMaxHeight;

    BOOL bDecodeThumbnail;

    EN_STILLIMAGE_DATA_ACCESS_METHOD enDataAccessMethod;

    U32 u32InputBuffAddr;
    U32 u32InputBuffLen;

    U32 u32OutputBuffAddr;
    U32 u32OutputBuffLen;

    U32 u32ProgressiveJpegBuffAddr;
    U32 u32ProgressiveJpegBuffLen;

    U32 u32MemPoolBuffAddr;
    U32 u32MemPoolBuffLen;

    BOOL bIsStreamMode;
    U32 u32StreamMode_ReadTimeOut;

    //gif related
    U32 u32FrameInfoArrayAddr;
    U32 u32FrameInfoArraySize;
    BOOL bOnlyDecodeFirstFrame;
    BOOL bOnlyPlayFirstLoopForLoopAnimation;

    // functionality control
    U32 u32ControlFlags;

    ST_STILLIMAGE_DATA_IO_FUNC stDataIoFuncs;
} ST_STILLIMAGE_CFG_PARAMS, *PST_STILLIMAGE_CFG_PARAMS;

typedef struct
{
    ST_STILLIMAGE_CFG_PARAMS stInputCfgParams;

    EN_STILLIMAGE_ERR_CODE enError;

    U16 u16Progress;

    EN_STILLIMAGE_INPUT_DATA_FORMAT enInputFormat;

    U32 u32OutputPitch;
    U32 u32OutputWidth;
    U32 u32OutputHeight;
    U32 u32OutputSize;

    U32 u32ImageWidth;
    U32 u32ImageHeight;

    BOOL bHasThumbnail;

    U8 u8DownScaleFactor;

    EN_STILLIMAGE_OUTPUT_DATA_FORMAT enOutputFormat;

    U32 u32FirstPixelPos;

    //*******EXIF Information*********
    U32 u32ExifWidth;
    U32 u32ExifHeight;
    EN_STILLIMAGE_ORIENTATION enOrientation;
    U8 au8CameraMaker[EXIF_CAMERA_MAKER_SIZE];
    U8 au8CameraModel[EXIF_CAMERA_MODEL_SIZE];
    U16 u16FlashMode;
    U32 u32ISOSpeed;
    ST_STILLIMAGE_RATIONAL stExposureBias;
    ST_STILLIMAGE_RATIONAL stExposureTime;
    ST_STILLIMAGE_RATIONAL stF_Stop;    
    ST_STILLIMAGE_RATIONAL stFocalLength;
    ST_STILLIMAGE_RATIONAL stShutterSpeed;
    ST_STILLIMAGE_RATIONAL stAperture;

    // Shooting Date Time
    BOOL bHasDateTime;
    U32 u32Year, u32Month, u32Day;
    U32 u32Hour, u32Minute, u32Second;
    //*********************************

    //gif related
    U32 u32DecodedFrameIndex, u32DisplayedFrameIndex;
    U32 u32SlotTotalNum, u32OutputFrameSize;
    U32 u32LoopTotalNumber; //zero means infinite loop

    EN_STILLIMAGE_RET (*pfStillImage_ReadHeader)(void);
    EN_STILLIMAGE_RET (*pfStillImage_Task)(void);
    EN_STILLIMAGE_RET (*pfStillImage_Stop)(void);
} ST_STILLIMAGE, *PST_STILLIMAGE;

//------------------------------------------------------------------------------
// Extern Global Variabls
//------------------------------------------------------------------------------
extern ST_STILLIMAGE g_stStillImage;

//------------------------------------------------------------------------------
// Extern Functions
//------------------------------------------------------------------------------
INTERFACE BOOL msAPI_StillImage_Reset(void);
INTERFACE EN_STILLIMAGE_RET msAPI_StillImage_Probe(void);
INTERFACE EN_STILLIMAGE_RET msAPI_StillImage_ParseHeader(void);
INTERFACE EN_STILLIMAGE_RET msAPI_StillImage_Init(ST_STILLIMAGE_CFG_PARAMS *pstCfgParams);
INTERFACE EN_STILLIMAGE_RET msAPI_StillImage_Task(void);
INTERFACE EN_STILLIMAGE_RET msAPI_StillImage_Stop(void);

INTERFACE EN_STILLIMAGE_RET msAPI_StillImage_SetCfgParams(PST_STILLIMAGE_CFG_PARAMS pstCfgParams);
INTERFACE void msAPI_StillImage_GetCfgParams(PST_STILLIMAGE_CFG_PARAMS pstCfgParams);

INTERFACE EN_STILLIMAGE_ERR_CODE msAPI_StillImage_GetErrorCode(void);
INTERFACE U16 msAPI_StillImage_GetProgress(void);
INTERFACE EN_STILLIMAGE_INPUT_DATA_FORMAT msAPI_StillImage_GetInputDataFormat(void);
INTERFACE U32 msAPI_StillImage_GetOutputPitch(void);
INTERFACE U32 msAPI_StillImage_GetOutputWidth(void);
INTERFACE U32 msAPI_StillImage_GetOutputHeight(void);
INTERFACE U32 msAPI_StillImage_GetOutputSize(void);
INTERFACE U32 msAPI_StillImage_GetImageWidth(void);
INTERFACE U32 msAPI_StillImage_GetImageHeight(void);
INTERFACE EN_STILLIMAGE_OUTPUT_DATA_FORMAT msAPI_StillImage_GetOutputDataFormat(void);
INTERFACE BOOL msAPI_StillImage_HasThumbnail(void);
INTERFACE U8 msAPI_StillImage_DownScaleFactor(void);
INTERFACE EN_STILLIMAGE_ORIENTATION msAPI_StillImage_Orientation(void);
INTERFACE BOOL msAPI_StillImage_HasDateTime(void);
INTERFACE U32 msAPI_StillImage_DateTimeYear(void);
INTERFACE U32 msAPI_StillImage_DateTimeMonth(void);
INTERFACE U32 msAPI_StillImage_DateTimeDay(void);
INTERFACE U32 msAPI_StillImage_DateTimeHour(void);
INTERFACE U32 msAPI_StillImage_DateTimeMinute(void);
INTERFACE U32 msAPI_StillImage_DateTimeSecond(void);
INTERFACE U32 msAPI_StillImage_GetDecodedFrameIndex(void);
INTERFACE U32 msAPI_StillImage_GetGifSlotTotalNum(void);
INTERFACE U32 msAPI_StillImage_GetGifOutputFrameSize(void);
INTERFACE void msAPI_StillImage_UpdateDisplayedFrameIndex(U32 u32DisplayedFrameIndex);
INTERFACE U32 msAPI_StillImage_GetDisplayedFrameIndex(void);
INTERFACE U32 msAPI_StillImage_GetGifLoopTimes(void);
INTERFACE EN_STILLIMAGE_DATA_ACCESS_METHOD msAPI_StillImage_GetDataAccessMethod(void);
INTERFACE U32 msAPI_StillImage_GetInputBuffLen(void);
INTERFACE U32 msAPI_StillImage_GetExifWidth(void);
INTERFACE U32 msAPI_StillImage_GetExifHeight(void);
INTERFACE U32 msAPI_StillImage_GetEXIFManufacturer(void);
INTERFACE U32 msAPI_StillImage_GetEXIFModel(void);
INTERFACE U16 msAPI_StillImage_GetEXIFFlash(void);
INTERFACE U32 msAPI_StillImage_GetEXIFISOSpeedRatings(void);
INTERFACE U32 msAPI_StillImage_GetEXIFExposureBiasValue(void);
INTERFACE U32 msAPI_StillImage_GetEXIFExposureTime(void);
INTERFACE U32 msAPI_StillImage_GetEXIFFNumber(void);
INTERFACE U32 msAPI_StillImage_GetEXIFFocalLength(void);
INTERFACE U32 msAPI_StillImage_GetEXIFShutterSpeedValue(void);
INTERFACE U32 msAPI_StillImage_GetEXIFApertureValue(void);
INTERFACE BOOLEAN msAPI_StillImage_GetMPODisparityType(void);

#undef INTERFACE

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef _MSAPI_STILLIMAGE_H_

///*** please do not remove change list tag ***///
///***$Change: 428882 $***///
