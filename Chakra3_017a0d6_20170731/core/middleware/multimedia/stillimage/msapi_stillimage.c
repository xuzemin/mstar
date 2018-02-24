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
// Copyright (c) 2008-2010 MStar Semiconductor, Inc.
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

#define _MSAPI_STILLIMAGE_C_
///////////////////////////////////////////////////////////////////////////////
/// @file   msAPI_VDPlayer_Decode.c
/// @author MStar Semiconductor Inc.
/// @brief  The Decoder Flow Control Module
///////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
//#include "mm_common.h"           // Every source code should include this in the first line
#include "MsOS.h"
#include "msapi_stillimage.h"
#include "msapi_stillimage_bm.h"
#include "msapi_stillimage_dlmalloc.h"

#include "msapi_jpeg_decoder.h"
#include "msapi_bmp_decoder.h"
//#include "msapi_png_decoder.h"
//#include "msapi_tiff_decoder.h"
#include "msapi_gif_decoder.h"

//#include "msapi_jpeg_encoder.h"
#include <string.h>

//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------
ST_STILLIMAGE g_stStillImage;

//------------------------------------------------------------------------------
// Local Function Prototypes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local Function Implementation
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Global Function Implementation
//------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/// The API is used to as an initialization function of still image API module
/// @param: None
/// @return: TRUE if initialization ok, otherwise, FALSE.
//-------------------------------------------------------------------------------------------------
BOOL msAPI_StillImage_Reset(void)
{
    // can't use memset here becasue it may clear configuration parameters set by msAPI_StillImage_SetCfgParams()
    g_stStillImage.enError = E_STILLIMAGE_ERR_NONE;
    g_stStillImage.u16Progress = 0;
    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_FORMAT_NONE;
    g_stStillImage.u32OutputPitch = 0;
    g_stStillImage.u32OutputWidth = 0;
    g_stStillImage.u32OutputHeight = 0;
    g_stStillImage.u32ImageWidth = 0;
    g_stStillImage.u32ImageHeight = 0;
    g_stStillImage.bHasThumbnail = FALSE;
    g_stStillImage.enOutputFormat = E_STILLIMAGE_OUTPU_FORMAT_NONE;

    g_stStillImage.u32FirstPixelPos = 0;

    g_stStillImage.pfStillImage_ReadHeader = NULL;
    g_stStillImage.pfStillImage_Task = NULL;

    return TRUE;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to check the format of input data
/// @param: None
/// @return: E_STILLIMAGE_RET_OK if input data format is identified, otherwise E_STILLIMAGE_RET_FAIL.
//-------------------------------------------------------------------------------------------------
EN_STILLIMAGE_RET msAPI_StillImage_Probe(void)
{
    U64 u64Size;

    msAPI_StillImage_Reset();

    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_FORMAT_NONE;
    u64Size = msAPI_StillImage_BMFile_Size();

    // initial memory pool
    // for (PNG decoder)/(JPEG encoder), memory pool has to be inited at the beginning
    if (msAPI_StillImage_Dlmalloc_InitMemPool(
            (void *)g_stStillImage.stInputCfgParams.u32MemPoolBuffAddr,
            g_stStillImage.stInputCfgParams.u32MemPoolBuffLen) == FALSE)
    {
        g_stStillImage.enError = E_STILLIMAGE_INIT_FAILED;
        goto fail;
    }

    switch (g_stStillImage.stInputCfgParams.enCmdType)
    {
        case E_STILLIMAGE_DECODE:
#if ENABLE_HK_BMP
            if ((g_stStillImage.stInputCfgParams.u32ControlFlags & (U32)E_STILLIMAGE_CONTROL_FLAG_ENABLE_BMP_DECODER)
                    && (msAPI_BmpDecoder_Probe() == E_STILLIMAGE_RET_OK))
            {
                g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_BMP;
                SI_INF_MUST(printf("[Still Image] Decoder, BMP, size: %d. \n", u32u64_0(u64Size)));
            }
            else
#endif
#if ENABLE_HK_PNG
            if ((g_stStillImage.stInputCfgParams.u32ControlFlags & (U32)E_STILLIMAGE_CONTROL_FLAG_ENABLE_PNG_DECODER)
                    && (msAPI_PngDecoder_Probe() == E_STILLIMAGE_RET_OK))
            {
                g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_PNG;
                SI_INF_MUST(printf("[Still Image] Decoder, PNG, size: %d. \n", u32u64_0(u64Size)));
            }
            else
#endif
#if ENABLE_HK_TIFF
            if ((g_stStillImage.stInputCfgParams.u32ControlFlags & (U32)E_STILLIMAGE_CONTROL_FLAG_ENABLE_TIFF_DECODER)
                    && (msAPI_TiffDecoder_Probe() == E_STILLIMAGE_RET_OK))
            {
                g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_TIFF;
                SI_INF_MUST(printf("[Still Image] Decoder, TIFF, size: %d. \n", u32u64_0(u64Size)));
            }
            else
#endif
#if ENABLE_HK_GIF
            if ((g_stStillImage.stInputCfgParams.u32ControlFlags & (U32)E_STILLIMAGE_CONTROL_FLAG_ENABLE_GIF_DECODER)
                    && (msAPI_GifDecoder_Probe() == E_STILLIMAGE_RET_OK))
            {
                g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_GIF;
                SI_INF_MUST(printf("[Still Image] Decoder, GIF, size: %d. \n", u32u64_0(u64Size)));
            }
            else
#endif
            if ((g_stStillImage.stInputCfgParams.u32ControlFlags & (U32)E_STILLIMAGE_CONTROL_FLAG_ENABLE_JPEG_DECODER)
                    && (msAPI_JpegDecoder_Probe() == E_STILLIMAGE_RET_OK))
            {
                g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_JPEG;
                SI_INF_MUST(printf("[Still Image] Decoder, JPEG, size: %d. \n", u32u64_0(u64Size)));
            }
            else
            {
                g_stStillImage.enError = E_STILLIMAGE_DATA_FORMAT_NOT_SUPPORTED;
                SI_INF_MUST(printf("[Still Image] Decoder, unknown format, size: %d. \n", u32u64_0(u64Size)));
            }
            break;

        case E_STILLIMAGE_ENCODE:
#if ENABLE_HK_JPE
            if ((g_stStillImage.stInputCfgParams.u32ControlFlags & (U32)E_STILLIMAGE_CONTROL_FLAG_ENABLE_JPEG_ENCODER)
                    && (msAPI_JpegEncoder_Init() == E_STILLIMAGE_RET_OK))
            {
                g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_RAW;
            }
            else
#endif
            {
                g_stStillImage.enError = E_STILLIMAGE_DATA_FORMAT_NOT_SUPPORTED;
                SI_INF_MUST(printf("[Still Image] Encode, unknown format, size: %d. \n", u32u64_0(u64Size)));
            }
            break;

        default:
            break;
    }

fail:
    return (g_stStillImage.enInputFormat != E_STILLIMAGE_INPUT_DATA_FORMAT_NONE ? E_STILLIMAGE_RET_OK : E_STILLIMAGE_RET_FAIL);
}

//-------------------------------------------------------------------------------------------------
/// The API is used to parse header of input data
/// @param: None
/// @return: E_STILLIMAGE_RET_OK if input data header parsing successful, otherwise E_STILLIMAGE_RET_FAIL.
//-------------------------------------------------------------------------------------------------
EN_STILLIMAGE_RET msAPI_StillImage_ParseHeader(void)
{
    g_stStillImage.enError = E_STILLIMAGE_ERR_NONE;

    switch (g_stStillImage.stInputCfgParams.enCmdType)
    {
        case E_STILLIMAGE_DECODE:
            if ((g_stStillImage.pfStillImage_ReadHeader() != E_STILLIMAGE_RET_OK)
                    && (g_stStillImage.enError == E_STILLIMAGE_ERR_NONE))
            {
                g_stStillImage.enError = E_STILLIMAGE_IMAGE_FORMAT_NOT_SUPPORTED;
            }

            if (MAJOR_FORMAT(g_stStillImage.enInputFormat) == E_STILLIMAGE_INPUT_DATA_JPEG)
            {
                // TBD: JPEG decoder manager the buffer by itself
                msAPI_StillImage_BM_SetPreloadSize(0);
            }
            break;

        case E_STILLIMAGE_ENCODE:
            break;

        default:
            break;
    }

    g_stStillImage.u16Progress = 0;

    return (g_stStillImage.enError == E_STILLIMAGE_ERR_NONE ? E_STILLIMAGE_RET_OK : E_STILLIMAGE_RET_FAIL);
}

EN_STILLIMAGE_RET msAPI_StillImage_Init(ST_STILLIMAGE_CFG_PARAMS *pstCfgParams)
{
#define CHECK_BM_RESULT(result)         \
    if (result != E_BM_RET_OK)          \
    {                                   \
        return E_STILLIMAGE_RET_FAIL;   \
    }

#define CHECK_STILLIMAGE_RESULT(result) \
    if (result != E_STILLIMAGE_RET_OK)  \
    {                                   \
        return E_STILLIMAGE_RET_FAIL;   \
    }

    EN_BM_RET enBmRet;
    EN_STILLIMAGE_RET enRet;
    
    enRet = msAPI_StillImage_SetCfgParams(pstCfgParams);
    CHECK_STILLIMAGE_RESULT(enRet);

    msAPI_StillImage_BM_Init();
    enBmRet = msAPI_StillImage_BM_SetIO(&pstCfgParams->stDataIoFuncs);
    CHECK_BM_RESULT(enBmRet);
    
    msAPI_StillImage_BM_SetPreloadSize(BM_DEFAULT_PRELOAD_SIZE);
    enBmRet = msAPI_StillImage_BMBuffer_Configuration(
            pstCfgParams->u32InputBuffAddr,
            pstCfgParams->u32InputBuffAddr + pstCfgParams->u32InputBuffLen);
    CHECK_BM_RESULT(enBmRet);
    msAPI_StillImage_BMBuffer_Reset();

    enBmRet = msAPI_StillImage_BMFile_Open();
    CHECK_BM_RESULT(enBmRet);

    if (msAPI_StillImage_BMFile_Size() == 0)
    {
        msAPI_StillImage_BMFile_SetSize(pstCfgParams->u32InputBuffLen);
    }
    msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BMBuffer_ActiveBuffSize());

    enRet = msAPI_StillImage_Probe();
    CHECK_STILLIMAGE_RESULT(enRet);

    enRet = msAPI_StillImage_ParseHeader();
    CHECK_STILLIMAGE_RESULT(enRet);

    return E_STILLIMAGE_RET_OK;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to as an initialization function of still image API module
/// @param: None
/// @return: E_STILLIMAGE_RET_FAIL, something wrong when working on current job.
///          E_STILLIMAGE_RET_DONE, current job was done successfully.
///          E_STILLIMAGE_RET_WORKING, more time is needed for current job.
//-------------------------------------------------------------------------------------------------
EN_STILLIMAGE_RET msAPI_StillImage_Task(void)
{
    EN_STILLIMAGE_RET enRet = E_STILLIMAGE_RET_DONE;

    if (g_stStillImage.pfStillImage_Task == NULL)
    {
        enRet = E_STILLIMAGE_RET_FAIL;
        SI_INF_MUST(printf("[Still Image] No task function.\n"));
        return enRet;
    }
    	
    switch (g_stStillImage.stInputCfgParams.enDataAccessMethod)
    {
        case E_STILLIMAGE_VIA_MAILBOX:
        case E_STILLIMAGE_IN_MEMORY:
            if ((msAPI_StillImage_BM_GetPreloadSize() > 0) &&
                 (msAPI_StillImage_BMBuffer_SpaceLeft() > BM_DEFAULT_PRELOAD_SIZE))
            {
                msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BMBuffer_SpaceLeft());
            }
            break;

        default:
            break;
    }

    switch (g_stStillImage.stInputCfgParams.enCmdType)
    {
        case E_STILLIMAGE_DECODE:
            switch (g_stStillImage.pfStillImage_Task())
            {
                case E_STILLIMAGE_RET_FAIL:
                    enRet = E_STILLIMAGE_RET_FAIL;
                    SI_INF_MUST(printf("[Still Image] Decode failed.\n"));
                    break;

                case E_STILLIMAGE_RET_DONE:
                    enRet = E_STILLIMAGE_RET_DONE;
                    SI_INF_MUST(printf("[Still Image] Decode done.\n"));
                    break;

                case E_STILLIMAGE_RET_DECODE_ONE_FRAME_DONE:
                    enRet = E_STILLIMAGE_RET_DECODE_ONE_FRAME_DONE;
                    //SI_INF_MUST(printf("[Still Image] Decode one frame done(gif or mpo).\n"));
                    break;

                case E_STILLIMAGE_RET_OK:
                case E_STILLIMAGE_RET_WORKING:
                default:
                    enRet = E_STILLIMAGE_RET_WORKING;
                    break;
            }
            break;

        case E_STILLIMAGE_ENCODE:
            switch (g_stStillImage.pfStillImage_Task())
            {
                case E_STILLIMAGE_RET_FAIL:
                    enRet = E_STILLIMAGE_RET_FAIL;
                    SI_INF_MUST(printf("[Still Image] Encode failed.\n"));
                    break;

                case E_STILLIMAGE_RET_DONE:
                    enRet = E_STILLIMAGE_RET_DONE;
                    SI_INF_MUST(printf("[Still Image] Encode done.\n"));
                    break;

                case E_STILLIMAGE_RET_OK:
                case E_STILLIMAGE_RET_WORKING:
                default:
                    enRet = E_STILLIMAGE_RET_WORKING;
                    break;
            }
            break;

        default:
            SI_INF_MUST(printf("[Still Image] Cmd (%d) unknown.\n", g_stStillImage.stInputCfgParams.enCmdType));
            break;
    }

    return enRet;
}

EN_STILLIMAGE_RET msAPI_StillImage_Stop(void)
{
    if (g_stStillImage.pfStillImage_Stop == NULL)
    {
        SI_INF_MUST(printf("[Still Image] No stop function.\n"));
        return E_STILLIMAGE_RET_FAIL;
    }

    return g_stStillImage.pfStillImage_Stop();
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get configuration parameters to still image API module
/// @param: pstCfgParams, a pointer points to the memory to where the configuration parameters
///         will be copied.
/// @return: None
//-------------------------------------------------------------------------------------------------
void msAPI_StillImage_GetCfgParams(PST_STILLIMAGE_CFG_PARAMS pstCfgParams)
{
    if (pstCfgParams)
    {
        *pstCfgParams = g_stStillImage.stInputCfgParams;
    }
}

//-------------------------------------------------------------------------------------------------
/// The API is used to set configuration parameters to still image API module
/// @param: pstCfgParams, a pointer points to configuration parameters.
/// @return: None
//-------------------------------------------------------------------------------------------------
EN_STILLIMAGE_RET msAPI_StillImage_SetCfgParams(PST_STILLIMAGE_CFG_PARAMS pstCfgParams)
{
    if (pstCfgParams)
    {
        pstCfgParams->u32InputBuffAddr            = MsOS_PA2KSEG1(pstCfgParams->u32InputBuffAddr);
        pstCfgParams->u32OutputBuffAddr           = MsOS_PA2KSEG1(pstCfgParams->u32OutputBuffAddr);
        pstCfgParams->u32ProgressiveJpegBuffAddr  = MsOS_PA2KSEG1(pstCfgParams->u32ProgressiveJpegBuffAddr);
        pstCfgParams->u32MemPoolBuffAddr          = MsOS_PA2KSEG0(pstCfgParams->u32MemPoolBuffAddr);
        
        g_stStillImage.stInputCfgParams = *pstCfgParams;
        return E_STILLIMAGE_RET_OK;
    }
    return E_STILLIMAGE_RET_FAIL;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get error code of still image API module
/// @param: None
/// @return: the error code
//-------------------------------------------------------------------------------------------------
EN_STILLIMAGE_ERR_CODE msAPI_StillImage_GetErrorCode(void)
{
    return g_stStillImage.enError;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get current progress of current job
/// @param: None
/// @return: current progress, 0 ~ 1000
//-------------------------------------------------------------------------------------------------
U16 msAPI_StillImage_GetProgress(void)
{
    return g_stStillImage.u16Progress;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get current input data format
/// @param: None
/// @return: the input data format
//-------------------------------------------------------------------------------------------------
EN_STILLIMAGE_INPUT_DATA_FORMAT msAPI_StillImage_GetInputDataFormat(void)
{
    return g_stStillImage.enInputFormat;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the pitch of output data
/// @param: None
/// @return: the pitch of output data
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetOutputPitch(void)
{
    return g_stStillImage.u32OutputPitch;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the width of output data
/// @param: None
/// @return: the width of output data
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetOutputWidth(void)
{
    return g_stStillImage.u32OutputWidth;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the height of output data
/// @param: None
/// @return: the height of output data
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetOutputHeight(void)
{
    return g_stStillImage.u32OutputHeight;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the total size of output data
/// @param: None
/// @return: the total size in byte of output data
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetOutputSize(void)
{
    return g_stStillImage.u32OutputSize;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the width of original image
/// @param: None
/// @return: the width of output data
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetImageWidth(void)
{
    return g_stStillImage.u32ImageWidth;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the height of original image
/// @param: None
/// @return: the height of output data
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetImageHeight(void)
{
    return g_stStillImage.u32ImageHeight;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get output data format
/// @param: None
/// @return: the output data format
//-------------------------------------------------------------------------------------------------
EN_STILLIMAGE_OUTPUT_DATA_FORMAT msAPI_StillImage_GetOutputDataFormat(void)
{
    return g_stStillImage.enOutputFormat;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to check if there is thumbnail in input data
/// @param: None
/// @return: TRUE, if there is a thumbnail in input data. FALSE, otherwise.
//-------------------------------------------------------------------------------------------------
BOOL msAPI_StillImage_HasThumbnail(void)
{
    return g_stStillImage.bHasThumbnail;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the down scale factor performed by decoder
/// @param: None
/// @return: The scale down factor performed.
//-------------------------------------------------------------------------------------------------
U8 msAPI_StillImage_DownScaleFactor(void)
{
    return g_stStillImage.u8DownScaleFactor;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the orientation specified in image info
/// @param: None
/// @return: the orientation specified.
//-------------------------------------------------------------------------------------------------
EN_STILLIMAGE_ORIENTATION msAPI_StillImage_Orientation(void)
{
    return g_stStillImage.enOrientation;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get if there is data time specified in image info
/// @param: None
/// @return: TRUE, if there is date time in image info. FALSE, otherwise
//-------------------------------------------------------------------------------------------------
BOOL msAPI_StillImage_HasDateTime(void)
{
    return g_stStillImage.bHasDateTime;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the year of data time specified in image info
/// @param: None
/// @return: the year of date time
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_DateTimeYear(void)
{
    return g_stStillImage.u32Year;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the month of data time specified in image info
/// @param: None
/// @return: the month of date time
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_DateTimeMonth(void)
{
    return g_stStillImage.u32Month;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the day of data time specified in image info
/// @param: None
/// @return: the day of date time
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_DateTimeDay(void)
{
    return g_stStillImage.u32Day;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the hour of data time specified in image info
/// @param: None
/// @return: the hour of date time
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_DateTimeHour(void)
{
    return g_stStillImage.u32Hour;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the minute of data time specified in image info
/// @param: None
/// @return: the minute of date time
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_DateTimeMinute(void)
{
    return g_stStillImage.u32Minute;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the second of data time specified in image info
/// @param: None
/// @return: the second of date time
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_DateTimeSecond(void)
{
    return g_stStillImage.u32Second;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the gif decoded frame index
/// @param: None
/// @return: the  gif decoded frame index
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetDecodedFrameIndex(void)
{
    return g_stStillImage.u32DecodedFrameIndex;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the gif total slot num
/// @param: None
/// @return: the  gif total slot num
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetGifSlotTotalNum(void)
{
    return g_stStillImage.u32SlotTotalNum;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get the gif every output frame size
/// @param: None
/// @return: the  gif every output frame size
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetGifOutputFrameSize(void)
{
    return g_stStillImage.u32OutputFrameSize;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to update the display frame index for gif
/// @param:  u32DisplayedFrameIndex \b IN  Specify the display frame index.
/// @return: the  minisecond of delay time
//-------------------------------------------------------------------------------------------------
void msAPI_StillImage_UpdateDisplayedFrameIndex(U32 u32DisplayedFrameIndex)
{
    g_stStillImage.u32DisplayedFrameIndex = u32DisplayedFrameIndex;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get displayed frame index
/// @param: None
/// @return: the  minisecond of delay time
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetDisplayedFrameIndex(void)
{
    return g_stStillImage.u32DisplayedFrameIndex;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get gif animation loop times, zero means infinite loop
/// @param: None
/// @return: loop times
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetGifLoopTimes(void)
{
    return g_stStillImage.u32LoopTotalNumber;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get data access method
/// @param: None
/// @return: data access method
//-------------------------------------------------------------------------------------------------
EN_STILLIMAGE_DATA_ACCESS_METHOD msAPI_StillImage_GetDataAccessMethod(void)
{
    return g_stStillImage.stInputCfgParams.enDataAccessMethod;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get input buffer Length
/// @param: None
/// @return: input buffer Length
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetInputBuffLen(void)
{
    return g_stStillImage.stInputCfgParams.u32InputBuffLen;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif width
/// @param: None
/// @return: exif width
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetExifWidth(void)
{
    return g_stStillImage.u32ExifWidth;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif height
/// @param: None
/// @return: exif height
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetExifHeight(void)
{
    return g_stStillImage.u32ExifHeight;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif camera maker
/// @param: None
/// @return: pointer of g_stStillImage.au8CameraMaker
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetEXIFManufacturer(void)
{
    return (U32)(&g_stStillImage.au8CameraMaker);
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif camera model
/// @param: None
/// @return: pointer of g_stStillImage.au8CameraModel
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetEXIFModel(void)
{
    return (U32)(&g_stStillImage.au8CameraModel);
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif flash mode
/// @param: None
/// @return: flash mode
//-------------------------------------------------------------------------------------------------
U16 msAPI_StillImage_GetEXIFFlash(void)
{
    return g_stStillImage.u16FlashMode;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif ISO speed
/// @param: None
/// @return: ISO speed
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetEXIFISOSpeedRatings(void)
{
    return g_stStillImage.u32ISOSpeed;
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif exposure bias value
/// @param: None
/// @return: pointer of g_stStillImage.stExposureBias
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetEXIFExposureBiasValue(void)
{
    return (U32)(&g_stStillImage.stExposureBias);
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif exposure time
/// @param: None
/// @return: pointer of g_stStillImage.stExposureTime
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetEXIFExposureTime(void)
{
    return (U32)(&g_stStillImage.stExposureTime);
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif F-stop
/// @param: None
/// @return: pointer of g_stStillImage.stF_Stop
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetEXIFFNumber(void)
{
    return (U32)(&g_stStillImage.stF_Stop);
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif Focal Length
/// @param: None
/// @return: pointer of g_stStillImage.stFocalLength
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetEXIFFocalLength(void)
{
    return (U32)(&g_stStillImage.stFocalLength);
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif Shutter Speed
/// @param: None
/// @return: pointer of g_stStillImage.stShutterSpeed
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetEXIFShutterSpeedValue(void)
{
    return (U32)(&g_stStillImage.stShutterSpeed);
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get exif Aperture
/// @param: None
/// @return: pointer of g_stStillImage.stAperture
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_GetEXIFApertureValue(void)
{
    return (U32)(&g_stStillImage.stAperture);
}

//-------------------------------------------------------------------------------------------------
/// The API is used to get MPO disparity type
/// @param: None
/// @return: loop times
//-------------------------------------------------------------------------------------------------
BOOLEAN msAPI_StillImage_GetMPODisparityType(void)
{
    BOOLEAN bMPODisparityType;
    bMPODisparityType = ((g_stStillImage.enInputFormat == E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_BASELINE)
                       ||(g_stStillImage.enInputFormat == E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_PROGRESSIVE));
    return bMPODisparityType;
}

#undef _MSAPI_STILLIMAGE_C_

///*** please do not remove change list tag ***///
///***$Change: 428882 $***///
