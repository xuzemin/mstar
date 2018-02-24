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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

///////////////////////////////////////////////////////////////////////////////
/// @file   msapi_jpeg_decoder.c
/// @author MStar Semiconductor Inc.
/// @brief  API of JPEG decoder
///////////////////////////////////////////////////////////////////////////////
#define _MSAPI_JPEG_DECODER_C_

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
//#include "mm_common.h"           // Every source code should include this in the first line
#include "MsCommon.h"
#include <string.h>
#include "drvBDMA.h"

// NOTE: DO NOT include "MApp_StillImage_ShareMemCfg.h" in decoder/encoder modules
// and make sure it be included in only one file, "msAPI_StillImage.h"
#include "msapi_stillimage.h"
#include "msapi_stillimage_bm.h"
#include "msapi_jpeg_decoder.h"

#include "msapi_stillimage_dlmalloc.h"

#include "apiJPEG.h"

//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------
// JPEG related
#define JFIF_SOI_CHECKING_LEN    640

// JPEG RST PATCH
#define JPEG_RST_PATCH      (1)

#if SUPPORT_EXIF_EXTRA_INFO
#define SUPPORT_EXIF_RESOLUTION     0
#define SUPPORT_EXIF_CAMERA_INFO    0
#else
#define SUPPORT_EXIF_RESOLUTION     0
#define SUPPORT_EXIF_CAMERA_INFO    0
#endif

typedef enum
{
    EN_JPEG_MARKER_SOF0     = 0xC0,
    EN_JPEG_MARKER_SOF1     = 0xC1,
    EN_JPEG_MARKER_SOF2     = 0xC2,
    EN_JPEG_MARKER_SOF3     = 0xC3,
    EN_JPEG_MARKER_SOF5     = 0xC5,
    EN_JPEG_MARKER_SOF6     = 0xC6,
    EN_JPEG_MARKER_SOF7     = 0xC7,
    EN_JPEG_MARKER_JPG      = 0xC8,
    EN_JPEG_MARKER_SOF9     = 0xC9,
    EN_JPEG_MARKER_SOF10    = 0xCA,
    EN_JPEG_MARKER_SOF11    = 0xCB,
    EN_JPEG_MARKER_SOF13    = 0xCD,
    EN_JPEG_MARKER_SOF14    = 0xCE,
    EN_JPEG_MARKER_SOF15    = 0xCF,
    EN_JPEG_MARKER_DHT      = 0xC4,
    EN_JPEG_MARKER_DAC      = 0xCC,
    EN_JPEG_MARKER_RST0     = 0xD0,
    EN_JPEG_MARKER_RST1     = 0xD1,
    EN_JPEG_MARKER_RST2     = 0xD2,
    EN_JPEG_MARKER_RST3     = 0xD3,
    EN_JPEG_MARKER_RST4     = 0xD4,
    EN_JPEG_MARKER_RST5     = 0xD5,
    EN_JPEG_MARKER_RST6     = 0xD6,
    EN_JPEG_MARKER_RST7     = 0xD7,
    EN_JPEG_MARKER_SOI      = 0xD8,
    EN_JPEG_MARKER_EOI      = 0xD9,
    EN_JPEG_MARKER_SOS      = 0xDA,
    EN_JPEG_MARKER_DQT      = 0xDB,
    EN_JPEG_MARKER_DNL      = 0xDC,
    EN_JPEG_MARKER_DRI      = 0xDD,
    EN_JPEG_MARKER_DHP      = 0xDE,
    EN_JPEG_MARKER_EXP      = 0xDF,
    EN_JPEG_MARKER_APP0     = 0xE0,
    EN_JPEG_MARKER_APP1     = 0xE1,
    EN_JPEG_MARKER_APP15    = 0xEF,
    EN_JPEG_MARKER_JPG0     = 0xF0,
    EN_JPEG_MARKER_JPG13    = 0xFD,
    EN_JPEG_MARKER_COM      = 0xFE,
    EN_JPEG_MARKER_PREFIX   = 0xFF,
    EN_JPEG_MARKER_TEM      = 0x01,
} EN_JPEG_MARKER_ID;

typedef enum
{
    EN_JPEG_FMT_UNKNOWN         = 0x0,
    EN_JPEG_FMT_BASELINE,
    EN_JPEG_FMT_PROGRESSIVE,

    EN_JPEG_FMT_UNSUPPORT,
} EN_JPEG_FROMAT;

typedef struct
{
    EN_JPEG_MARKER_ID enPrefix;
    EN_JPEG_MARKER_ID enId;
    U16 u16Size;
} ST_JPEG_MARKER;

#define MIM_MARKER_SIZE_WITHOUT_DATA    2U
#define MIM_MARKER_SIZE_WITH_DATA       4U
#define _U32_MAX (0xffffffff)

typedef enum
{
    EN_IDLE,
    EN_INIT,
    EN_DECODE_HEADER,
    EN_DECODE_LINE,
    EN_WAIT_DONE,
    EN_WAIT_DISPLAYED_DONE, //for mpo use
} EN_JPEG_DECODE_STATE;

// misc
typedef struct
{
    EN_JPEG_DECODE_STATE enState;

    BOOL bThumbnailFound;

    BOOL bHeaderDecoded;
    BOOL bStartCmdSent;
    U8 u8OutputPixelSize;

    EN_JPEG_FROMAT enFormat;
} ST_JPEG_DECODE;

typedef enum
{
    EN_DECODE_DONE = 0,
    EN_DECODING,
    EN_DECODE_ERR,
#if JPEG_RST_PATCH
    EN_DECODE_RST_ERR,
#endif // #if JPEG_RST_PATCH
} EN_JPEG_DECODER_STATUS;

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define JPEG_DBG(x)         //x
#define JPEG_INFO(x)        //x
#define JPEG_INFO_MUST(x)   //x
#define JPEG_ERR(x)         //x

#define printf_red(args...)           do{ printf("\033[1;31m"); printf(args); printf("\033[m"); }while(0)

#if (SUPPORT_EXIF_RESOLUTION==0)
#define MApi_JPEG_GetEXIFImageWidth(x)  FALSE
#define MApi_JPEG_GetEXIFImageHeight(x) FALSE
#endif

#if (SUPPORT_EXIF_CAMERA_INFO==0)
#define MApi_JPEG_GetEXIFManufacturer(x,y)      FALSE
#define MApi_JPEG_GetEXIFModel(x,y)             FALSE
#define MApi_JPEG_GetEXIFFlash(x)               FALSE
#define MApi_JPEG_GetEXIFISOSpeedRatings(x)     FALSE
#define MApi_JPEG_GetEXIFExposureBiasValue(x)   FALSE
#define MApi_JPEG_GetEXIFExposureTime(x)        FALSE
#define MApi_JPEG_GetEXIFFNumber(x)             FALSE
#define MApi_JPEG_GetEXIFFocalLength(x)         FALSE
#define MApi_JPEG_GetEXIFShutterSpeedValue(x)   FALSE
#define MApi_JPEG_GetEXIFApertureValue(x)       FALSE
#endif
//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------
static ST_JPEG_DECODE stJpegInfo_Decode;

#if JPEG_RST_PATCH
static BOOLEAN bJpegRstPatch_Activated  = FALSE;
static U32 u32JpegRstPatch_DataOffset   = 0;
static U32 u32JpegRstPatch_BufferAddr   = 0;
static U32 u32JpegRstPatch_BufferSize   = 0;
static S32 s32JpegRstPatch_CachedData   = 0; // it has to be signed
#endif // #if JPEG_RST_PATCH

static BOOLEAN bJpeg_UnRecoverableRstError  = FALSE;

#ifndef SUPPORT_MPO_FORMAT
#define SUPPORT_MPO_FORMAT 0
#endif

#if SUPPORT_MPO_FORMAT
JPEG_MPO_INDEX_INFO *pMPOIndex;
JPEG_MPO_ATTRIBUTE_INFO *pMPOAttr;
U32 num_of_mpo_image = 0;
U32 num_of_mpo_image_left = 0;
U32 read_buffer_start = 0;
U32 read_buffer_size = 0;
U32 start_offset = 0;
U32 write_buff_start = 0;
U32 write_offset = 0;
U32 display_buffer = 0;
U32 display_width = 0;
U32 display_height = 0;
U8 dspl_orientation = 0;
U8 u8DecodedMPOImageNum = 0;

typedef enum
{
    E_MP_TYPE_BASELINE             = 0x030000
  , E_MP_TYPE_LARGE_THUMBNAIL_CLASS1           = 0x010001
  , E_MP_TYPE_LARGE_THUMBNAIL_CLASS2        = 0x010002
  , E_MP_TYPE_MULTI_FRAME_PANORAMA  = 0x020001
  , E_MP_TYPE_MULTI_FRAME_DISPARITY        = 0x020002
  , E_MP_TYPE_MULTI_FRAME_MULTI_ANGLE        = 0x020003
  , E_MP_TYPE_MASK = 0x00FFFFFF
} MP_TYPE_CODE;

//currently, we only support disparity type two image decoding
#define DECODE_MPO_IMAGE_MAX_NUM 2

#endif

//------------------------------------------------------------------------------
// Local Function Prototypes
//------------------------------------------------------------------------------
EN_STILLIMAGE_RET msAPI_JpegDecoder_ReadHeader(void);
EN_STILLIMAGE_RET msAPI_JpegDecoder_Decode(void);
EN_STILLIMAGE_RET msAPI_JpegDecoder_Stop(void);

static void _msAPI_JpegDecoder_Reset(void);
static void msAPI_JpegDecoder_ErrorMapping(S16 sErrCode);

// Functions asked/needed by apiJPD.c mechanism
static S32  msAPI_JpegDecoder_FillHeaderBuffer(U32 u32Addr, U32 u32Length);
static S32  msAPI_JpegDecoder_FillDecodeBuffer(JPEG_BuffLoadType eType);
static S32  msAPI_JpegDecoder_DataRead(U32 u32Addr, U32 u32Byte, BOOL *pIsEOF);
static EN_JPEG_DECODER_STATUS msAPI_JpegDecoder_WaitDone(void);
#if SUPPORT_MPO_FORMAT
static U8 MApi_JPEG_MPO_DecodeNext(void);
#endif

//------------------------------------------------------------------------------
// Global Function Implementation
//------------------------------------------------------------------------------
EN_STILLIMAGE_RET msAPI_JpegDecoder_Probe(void)
{
    ST_JPEG_MARKER stMarker;
    U16 u16CheckSize;

    // show MApi_JPEG debug message
    //MApi_JPEG_SetDbgLevel(E_JPEG_DEBUG_ALL);

    // Initialize variable
    _msAPI_JpegDecoder_Reset();

    msAPI_StillImage_BMFile_Seek(0, E_BM_FILEPOS_SEEK_SET);
    msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BM_GetPreloadSize());

    // if EN_JPEG_MARKER_PREFIX(0xFF), EN_JPEG_MARKER_SOI(0xD8) aren't the first 2 bytes of the data,
    // following JFIF_SOI_CHECKING_LEN of data will be checked against EN_JPEG_MARKER_PREFIX and EN_JPEG_MARKER_SOI.
    u16CheckSize = JFIF_SOI_CHECKING_LEN;
    u16CheckSize = MIN(u16CheckSize, (U32)msAPI_StillImage_BMFile_Size());

    while (u16CheckSize >= MIM_MARKER_SIZE_WITHOUT_DATA)
    {
        stMarker.enPrefix = (EN_JPEG_MARKER_ID)msAPI_StillImage_BMBuffer_ReadBytes_AutoLoad(1);
        stMarker.enId = (EN_JPEG_MARKER_ID)msAPI_StillImage_BMBuffer_PeekNthByte(0);
        if ((stMarker.enPrefix == EN_JPEG_MARKER_PREFIX)
                && (stMarker.enId == EN_JPEG_MARKER_SOI))
        {
            msAPI_StillImage_BMBuffer_ReadBytes_AutoLoad(1);

            g_stStillImage.pfStillImage_ReadHeader = msAPI_JpegDecoder_ReadHeader;
            g_stStillImage.pfStillImage_Task = msAPI_JpegDecoder_Decode;
            g_stStillImage.pfStillImage_Stop = msAPI_JpegDecoder_Stop;
            stJpegInfo_Decode.enState = EN_INIT;
            return E_STILLIMAGE_RET_OK;
        }

        u16CheckSize--;
    }

    return E_STILLIMAGE_RET_FAIL;
}

EN_STILLIMAGE_RET msAPI_JpegDecoder_ReadHeader(void)
{
    S16 s16JpegDecoderErrCode;
    EN_STILLIMAGE_RET enRet = E_STILLIMAGE_RET_OK;
    JPEG_InitParam JpegInitParam;
    JPEG_EXIF_DateTime stDateTime;
    JPEG_EXIF_Orientation enOrientation;

    if (stJpegInfo_Decode.enState != EN_INIT)
    {
        g_stStillImage.enError = E_STILLIMAGE_JPEG_WRONG_STATE;
        JPEG_ERR(printf("[JPEG] Read header, wrong state (%d)\n", stJpegInfo_Decode.enState));
        return E_STILLIMAGE_RET_FAIL;
    }

    msAPI_StillImage_BMFile_Seek(0, E_BM_FILEPOS_SEEK_SET);
    msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BM_GetPreloadSize());
    MApi_JPEG_SetMaxDecodeResolution(
            g_stStillImage.stInputCfgParams.u32JpegBaseLineMaxWidth,
            g_stStillImage.stInputCfgParams.u32JpegBaseLineMaxHeight);

    MApi_JPEG_SetProMaxDecodeResolution(
            g_stStillImage.stInputCfgParams.u32JpegProgressiveMaxWidth,
            g_stStillImage.stInputCfgParams.u32JpegProgressiveMaxHeight);

#if SUPPORT_MPO_FORMAT
    MApi_JPEG_SetMPOMaxDecodeResolution(
            g_stStillImage.stInputCfgParams.u32MPOBaseLineMaxWidth,
            g_stStillImage.stInputCfgParams.u32MPOBaseLineMaxHeight);
    MApi_JPEG_SetMPOProMaxDecodeResolution(
            g_stStillImage.stInputCfgParams.u32MPOProgressiveMaxWidth,
            g_stStillImage.stInputCfgParams.u32MPOProgressiveMaxHeight);
#endif

    JpegInitParam.u32MRCBufAddr = MsOS_VA2PA(g_stStillImage.stInputCfgParams.u32InputBuffAddr);
    JpegInitParam.u32MRCBufSize = g_stStillImage.stInputCfgParams.u32InputBuffLen;
    JpegInitParam.u32MWCBufAddr = MsOS_VA2PA(g_stStillImage.stInputCfgParams.u32OutputBuffAddr);
    JpegInitParam.u32MWCBufSize = g_stStillImage.stInputCfgParams.u32OutputBuffLen;
    JpegInitParam.u32InternalBufAddr = MsOS_VA2PA(g_stStillImage.stInputCfgParams.u32ProgressiveJpegBuffAddr);
    JpegInitParam.u32InternalBufSize = g_stStillImage.stInputCfgParams.u32ProgressiveJpegBuffLen;
    JpegInitParam.u32DecByteRead = (MS_U32)msAPI_StillImage_BMBuffer_Remainder();
    JpegInitParam.bEOF =
            msAPI_StillImage_BMFile_Tell() + msAPI_StillImage_BMBuffer_Remainder() ==  msAPI_StillImage_BMFile_Size();
    JpegInitParam.u8DecodeType =
            g_stStillImage.stInputCfgParams.bDecodeThumbnail ? E_JPEG_TYPE_THUMBNAIL : E_JPEG_TYPE_MAIN;
    JpegInitParam.bInitMem = TRUE;
    JpegInitParam.pFillHdrFunc = msAPI_JpegDecoder_FillHeaderBuffer;

    MApi_JPEG_SupportCMYK(FALSE);
    MApi_JPEG_SupportRGB(FALSE);
    if (g_stStillImage.stInputCfgParams.u32ControlFlags & (U32)E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_CMYK)
    {
        MApi_JPEG_SupportCMYK(TRUE);
    }
    if (g_stStillImage.stInputCfgParams.u32ControlFlags & (U32)E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_RGB)
    {
        MApi_JPEG_SupportRGB(TRUE);
    }

    MApi_JPEG_Init(&JpegInitParam);
#if SUPPORT_MPO_FORMAT
    if(MApi_JPEG_IsMPOFormat())
    {
        JPEG_INFO_MUST(printf("It is MPO file.\n"));

        if(!MApi_JPEG_GetMPOIndex(&pMPOIndex))
        {
            JPEG_ERR(printf("MDrv_JPEG_GetMPOIndex Error.\n"));
            return E_STILLIMAGE_RET_FAIL;
        }

        num_of_mpo_image = num_of_mpo_image_left = pMPOIndex->num_of_image;
        read_buffer_start = JpegInitParam.u32MRCBufAddr;
        read_buffer_size = JpegInitParam.u32MRCBufSize;
        start_offset = JpegInitParam.u32MRCBufAddr;
        write_buff_start = JpegInitParam.u32MWCBufAddr;
        write_offset = JpegInitParam.u32MWCBufAddr;
        u8DecodedMPOImageNum = 0;
        g_stStillImage.u32DisplayedFrameIndex = _U32_MAX;
        g_stStillImage.u32DecodedFrameIndex = _U32_MAX;

        JPEG_DBG(printf("num_of_mpo_image=0x%x, num_of_mpo_image_left=0x%x\n", num_of_mpo_image, num_of_mpo_image_left));
        //display_buffer = param.u32DsplBufferAddr;
        //dspl_orientation = param.showVertical;
    }
#endif
    s16JpegDecoderErrCode = MApi_JPEG_GetErrorCode();

    // update information about this image
    g_stStillImage.u32FirstPixelPos     = 0;
    g_stStillImage.u32OutputPitch       = (U32)MApi_JPEG_GetAlignedPitch();
    g_stStillImage.u32OutputWidth       = (U32)MApi_JPEG_GetAlignedWidth();
    g_stStillImage.u32OutputHeight      = (U32)MApi_JPEG_GetAlignedHeight();
    g_stStillImage.u32ImageWidth        = (U32)MApi_JPEG_GetOriginalWidth();
    g_stStillImage.u32ImageHeight       = (U32)MApi_JPEG_GetOriginalHeight();
    g_stStillImage.u8DownScaleFactor    = MApi_JPEG_GetScaleDownFactor();
    g_stStillImage.bHasThumbnail        = MApi_JPEG_ThumbnailFound();
#if SUPPORT_MPO_FORMAT
    if(MApi_JPEG_IsMPOFormat())
    {
        if(!MApi_JPEG_IsProgressive())
        {
            switch(pMPOIndex->mp_entry[0].attribute & E_MP_TYPE_MASK)
            {
                case E_MP_TYPE_BASELINE:
                    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_MPO_BASELINE_SUBJPEG_BASELINE;
                    break;
                case E_MP_TYPE_MULTI_FRAME_PANORAMA:
                    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_MPO_PANORAMA_SUBJPEG_BASELINE;
                    break;
                case E_MP_TYPE_MULTI_FRAME_DISPARITY:
                    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_BASELINE;
                    break;
                case E_MP_TYPE_MULTI_FRAME_MULTI_ANGLE:
                    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_MPO_MULTI_ANGLE_SUBJPEG_BASELINE;
                    break;
                default:
                    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_JPEG_BASELINE;
                    break;
            }
        }
        else
        {
            switch(pMPOIndex->mp_entry[0].attribute & E_MP_TYPE_MASK)
            {
                case E_MP_TYPE_BASELINE:
                    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_MPO_BASELINE_SUBJPEG_PROGRESSIVE;
                    break;
                case E_MP_TYPE_MULTI_FRAME_PANORAMA:
                    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_MPO_PANORAMA_SUBJPEG_PROGRESSIVE;
                    break;
                case E_MP_TYPE_MULTI_FRAME_DISPARITY:
                    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_PROGRESSIVE;
                    break;
                case E_MP_TYPE_MULTI_FRAME_MULTI_ANGLE:
                    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_MPO_MULTI_ANGLE_SUBJPEG_PROGRESSIVE;
                    break;
                default:
                    g_stStillImage.enInputFormat = E_STILLIMAGE_INPUT_DATA_JPEG_PROGRESSIVE;
                    break;
            }
        }
    }
    else
#endif
    {
        g_stStillImage.enInputFormat        = MApi_JPEG_IsProgressive() ?
                                                E_STILLIMAGE_INPUT_DATA_JPEG_PROGRESSIVE :
                                                E_STILLIMAGE_INPUT_DATA_JPEG_BASELINE;
    }

    //EXIF image width
    if(MApi_JPEG_GetEXIFImageWidth(&g_stStillImage.u32ExifWidth)==FALSE)
    {
        g_stStillImage.u32ExifWidth = 0;
    }
    //EXIF image height
    if(MApi_JPEG_GetEXIFImageHeight(&g_stStillImage.u32ExifHeight)==FALSE)
    {
        g_stStillImage.u32ExifHeight = 0;
    }
    //EXIF camera maker
    if(MApi_JPEG_GetEXIFManufacturer(g_stStillImage.au8CameraMaker, EXIF_CAMERA_MAKER_SIZE)==FALSE)
    {
        memset(&g_stStillImage.au8CameraMaker, 0, EXIF_CAMERA_MAKER_SIZE);
    }
    //EXIF camera model
    if(MApi_JPEG_GetEXIFModel(g_stStillImage.au8CameraModel, EXIF_CAMERA_MODEL_SIZE)==FALSE)
    {
        memset(&g_stStillImage.au8CameraModel, 0, EXIF_CAMERA_MODEL_SIZE);
    }
    //EXIF flash mode
    if(MApi_JPEG_GetEXIFFlash(&g_stStillImage.u16FlashMode)==FALSE)
    {
        g_stStillImage.u16FlashMode = 0;
    }
    //EXIF ISO speed
    if(MApi_JPEG_GetEXIFISOSpeedRatings(&g_stStillImage.u32ISOSpeed)==FALSE)
    {
        g_stStillImage.u32ISOSpeed = 0;
    }
    //EXIF exposure bias
    if(MApi_JPEG_GetEXIFExposureBiasValue((void*)&g_stStillImage.stExposureBias)==FALSE)
    {
        memset(&g_stStillImage.stExposureBias, 0, sizeof(ST_STILLIMAGE_RATIONAL));
    }
    //EXIF exposure time
    if(MApi_JPEG_GetEXIFExposureTime((void*)&g_stStillImage.stExposureTime)==FALSE)
    {
        memset(&g_stStillImage.stExposureTime, 0, sizeof(ST_STILLIMAGE_RATIONAL));
    }
    //EXIF F-stop
    if(MApi_JPEG_GetEXIFFNumber((void*)&g_stStillImage.stF_Stop)==FALSE)
    {
        memset(&g_stStillImage.stF_Stop, 0, sizeof(ST_STILLIMAGE_RATIONAL));
    }
    //EXIF Focal Length
    if(MApi_JPEG_GetEXIFFocalLength((void*)&g_stStillImage.stFocalLength)==FALSE)
    {
        memset(&g_stStillImage.stFocalLength, 0, sizeof(ST_STILLIMAGE_RATIONAL));
    }
    //EXIF Shutter Speed
    if(MApi_JPEG_GetEXIFShutterSpeedValue((void*)&g_stStillImage.stShutterSpeed)==FALSE)
    {
        memset(&g_stStillImage.stShutterSpeed, 0, sizeof(ST_STILLIMAGE_RATIONAL));
    }
    //EXIF Shutter Speed
    if(MApi_JPEG_GetEXIFApertureValue((void*)&g_stStillImage.stAperture)==FALSE)
    {
        memset(&g_stStillImage.stAperture, 0, sizeof(ST_STILLIMAGE_RATIONAL));
    }

    //EXIF date time
    g_stStillImage.bHasDateTime = FALSE;
    if (MApi_JPEG_GetEXIFDateTime(&stDateTime) == TRUE)
    {
        g_stStillImage.bHasDateTime = (stDateTime.bHasDataTime ? TRUE : FALSE);

        g_stStillImage.u32Year  = stDateTime.u32Year;
        g_stStillImage.u32Month = stDateTime.u32Month;
        g_stStillImage.u32Day   = stDateTime.u32Day;

        g_stStillImage.u32Hour      = stDateTime.u32Hour;
        g_stStillImage.u32Minute    = stDateTime.u32Minute;
        g_stStillImage.u32Second    = stDateTime.u32Second;
    }

    //EXIF orientation
    g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_NOT_FOUND;
    if (MApi_JPEG_GetEXIFOrientation(&enOrientation) == TRUE)
    {
        switch (enOrientation)
        {
            case E_JPEG_EXIF_ORIENT_RESERVED:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_RESERVED;
                break;

            case E_JPEG_EXIF_ORIENT_ROTATE_0:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_ROTATE_0;
                break;

            case E_JPEG_EXIF_ORIENT_MIRROR_LR:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_MIRROR_LR;
                break;

            case E_JPEG_EXIF_ORIENT_ROTATE_180:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_ROTATE_180;
                break;

            case E_JPEG_EXIF_ORIENT_MIRROR_TB:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_MIRROR_TB;
                break;

            case E_JPEG_EXIF_ORIENT_ROTATE_90_MIRROR_LR:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_ROTATE_90_MIRROR_LR;
                break;

            case E_JPEG_EXIF_ORIENT_ROTATE_90:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_E_ORIENT_ROTATE_90;
                break;

            case E_JPEG_EXIF_ORIENT_ROTATE_90_MIRROR_TB:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_ROTATE_90_MIRROR_TB;
                break;

            case E_JPEG_EXIF_ORIENT_ROTATE_270:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_ROTATE_270;
                break;

            case E_JPEG_EXIF_ORIENT_NOT_FOUND:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_NOT_FOUND;
                break;

            default:
                g_stStillImage.enOrientation = E_STILLIMAGE_ORIENT_UNDEFINE;
                break;
        }
    }
#if 1 ///for parasoft
    g_stStillImage.enOutputFormat       = E_STILLIMAGE_OUTPU_RAW_YUV422;
    stJpegInfo_Decode.u8OutputPixelSize = 2;
#else
    g_stStillImage.enOutputFormat       = E_STILLIMAGE_OUTPU_RAW_YUV422;

    switch (g_stStillImage.enOutputFormat)
    {
        default:
        case E_STILLIMAGE_OUTPU_RAW_YUV422:
            stJpegInfo_Decode.u8OutputPixelSize = 2;
            break;

        case E_STILLIMAGE_OUTPU_RAW_ARGB8888:
            stJpegInfo_Decode.u8OutputPixelSize = 4;
            break;
    }
#endif
    g_stStillImage.u32OutputSize        = (U32)(g_stStillImage.u32OutputPitch * g_stStillImage.u32OutputHeight * stJpegInfo_Decode.u8OutputPixelSize);

    JPEG_INFO_MUST(printf("Thumbnail? %s\n", g_stStillImage.bHasThumbnail ? "Yes" : "No"));
    JPEG_INFO_MUST(printf("Image WxH: %dx%d\n", g_stStillImage.u32ImageWidth, g_stStillImage.u32ImageHeight));
    JPEG_INFO_MUST(printf("Progressive? %s\n", g_stStillImage.enInputFormat == E_STILLIMAGE_INPUT_DATA_JPEG_PROGRESSIVE ? "Yes" : "No"));
    JPEG_INFO_MUST(printf("Is MPO disparity type? %s\n", ((g_stStillImage.enInputFormat == E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_PROGRESSIVE) ||
        (g_stStillImage.enInputFormat == E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_BASELINE)) ? "Yes" : "No"));
    JPEG_INFO_MUST(printf("Scaled WxH: %d(%d)x%d\n", g_stStillImage.u32OutputWidth, g_stStillImage.u32OutputPitch, g_stStillImage.u32OutputHeight));
    JPEG_INFO_MUST(printf("Scale factor: %d\n", g_stStillImage.u8DownScaleFactor));

    // TBD: JPEG decoder now only supports baseline and progressive.
    if (MApi_JPEG_IsProgressive() == TRUE)
    {
        stJpegInfo_Decode.enFormat = EN_JPEG_FMT_PROGRESSIVE;
    }
    else
    {
        stJpegInfo_Decode.enFormat = EN_JPEG_FMT_BASELINE;
    }

    if (s16JpegDecoderErrCode != E_JPEG_NO_ERROR)
    {
        msAPI_JpegDecoder_ErrorMapping(s16JpegDecoderErrCode);
        msAPI_JpegDecoder_Stop();
        JPEG_ERR(printf("[JPEG] init error, %d\n", s16JpegDecoderErrCode));
        return E_STILLIMAGE_RET_FAIL;
    }

    if (enRet == E_STILLIMAGE_RET_OK)
    {
        stJpegInfo_Decode.enState = EN_DECODE_HEADER;
    }

    return enRet;
}

EN_STILLIMAGE_RET msAPI_JpegDecoder_Decode(void)
{
    S16 s16JpegDecoderErrCode = 0;
    EN_STILLIMAGE_RET enRet = E_STILLIMAGE_RET_WORKING;

    switch (stJpegInfo_Decode.enState)
    {
        case EN_IDLE:
        case EN_INIT:
        default:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_WRONG_STATE;
            JPEG_ERR(printf("[JPEG] Decode, wrong state (%d)\n", stJpegInfo_Decode.enState));
            goto fail;

        case EN_DECODE_HEADER:
            if (MApi_JPEG_DecodeHdr() == E_JPEG_FAILED)
            {
                s16JpegDecoderErrCode = MApi_JPEG_GetErrorCode();
                goto fail;
            }
            else
            {
                stJpegInfo_Decode.enState = EN_DECODE_LINE;
            }
            break;

        case EN_DECODE_LINE:
            switch (MApi_JPEG_Decode())
            {
                case E_JPEG_DONE:
                    break;

                case E_JPEG_OKAY:
                    stJpegInfo_Decode.enState = EN_WAIT_DONE;
                    break;

                case E_JPEG_FAILED:
                    s16JpegDecoderErrCode = MApi_JPEG_GetErrorCode();
                    goto fail;

                default:
                    break;
            }
            break;
#if SUPPORT_MPO_FORMAT
        case EN_WAIT_DISPLAYED_DONE:
            if(g_stStillImage.u32DisplayedFrameIndex != _U32_MAX)
            {
                    JPEG_DBG(printf_red("[JPEG] Decode Next MPO!!!!!!!!!!!!!!!!!\n"));
                    if(0 == MApi_JPEG_MPO_DecodeNext())
                    {
                        enRet = E_STILLIMAGE_RET_FAIL;
                    }

                    stJpegInfo_Decode.enState = EN_WAIT_DONE;
            }
            enRet = E_STILLIMAGE_RET_DECODE_ONE_FRAME_DONE;
            break;
#endif
        case EN_WAIT_DONE:
            switch (msAPI_JpegDecoder_WaitDone())
            {
                case EN_DECODE_DONE:
#if SUPPORT_MPO_FORMAT
                    if(MApi_JPEG_IsMPOFormat() && (num_of_mpo_image_left > 0) && (u8DecodedMPOImageNum < DECODE_MPO_IMAGE_MAX_NUM))
                    {
                        JPEG_DBG(printf("[JPEG] Decode MPO one jpeg done!!!!!!!!!!!!!!!!!\n"));
                        g_stStillImage.u16Progress = 500;
                        stJpegInfo_Decode.enState = EN_WAIT_DISPLAYED_DONE;
                        g_stStillImage.u32DecodedFrameIndex = (u8DecodedMPOImageNum -1);
                        enRet = E_STILLIMAGE_RET_DECODE_ONE_FRAME_DONE;

                    }
                    else
#endif
                    {
                        // TBD: How can I find a good way to knowing the decode progress?
                        g_stStillImage.u16Progress = 1000;

                        msAPI_JpegDecoder_Stop();
                        enRet = E_STILLIMAGE_RET_DONE;
                    }
                    break;

                case EN_DECODING:
                    break;

#if JPEG_RST_PATCH
                case EN_DECODE_RST_ERR:
                    if (bJpegRstPatch_Activated == TRUE)
                    {
                        // get free buffer
                        u32JpegRstPatch_BufferSize = g_stStillImage.stInputCfgParams.u32InputBuffLen * 2;
                        u32JpegRstPatch_BufferAddr = MApi_JPEG_GetFreeMemory(u32JpegRstPatch_BufferSize);
                        if (u32JpegRstPatch_BufferAddr == NULL)
                        {
                            JPEG_ERR(printf("[JPEG] RST patch error, insufficient memory\n"));
                            s16JpegDecoderErrCode = E_JPEG_DECODE_ERROR;
                            goto fail;
                        }
                        u32JpegRstPatch_BufferAddr = MsOS_PA2KSEG1(u32JpegRstPatch_BufferAddr);

                        // get data location
                        u32JpegRstPatch_DataOffset = MApi_JPEG_GetDataOffset();

                        // reset BM
                        msAPI_StillImage_BMBuffer_FlushBytes(msAPI_StillImage_BMBuffer_Remainder());
                        msAPI_StillImage_BMBuffer_UpdateBase();

                        // reconfigure BM buffer
                        msAPI_StillImage_BMBuffer_Configuration(
                                u32JpegRstPatch_BufferAddr + u32JpegRstPatch_BufferSize / 2,
                                u32JpegRstPatch_BufferAddr + u32JpegRstPatch_BufferSize);
                        msAPI_StillImage_BMBuffer_Reset();

                        // reset jpeg
                        MApi_JPEG_Rst();
                        MApi_JPEG_Exit();

                        // restart decode
                        stJpegInfo_Decode.enState = EN_INIT;
                        if (msAPI_JpegDecoder_ReadHeader() != E_STILLIMAGE_RET_OK)
                        {
                            JPEG_ERR(printf("[JPEG] RST patch error, 2nd read header failed\n"));
                            s16JpegDecoderErrCode = E_JPEG_DECODE_ERROR;
                            goto fail;
                        }
                    }
                    break;
#endif // #if JPEG_RST_PATCH

                case EN_DECODE_ERR:
                default:
                    g_stStillImage.u16Progress = MApi_JPEG_GetCurVidx()*100/g_stStillImage.u32OutputHeight;
                    if(g_stStillImage.u16Progress > 100)
                    {
                        g_stStillImage.u16Progress = 100;
                    }
                    s16JpegDecoderErrCode = E_JPEG_DECODE_ERROR;
                    goto fail;
            }
            break;
    }

    return enRet;

fail:
    if (s16JpegDecoderErrCode)
    {
        msAPI_JpegDecoder_ErrorMapping(s16JpegDecoderErrCode);
    }

    if (stJpegInfo_Decode.enState != EN_IDLE)
    {
        msAPI_JpegDecoder_Stop();
    }

    return E_STILLIMAGE_RET_FAIL;
}

EN_STILLIMAGE_RET msAPI_JpegDecoder_Stop(void)
{
    MApi_JPEG_Rst();
    MApi_JPEG_Exit();

    _msAPI_JpegDecoder_Reset();

    return E_STILLIMAGE_RET_OK;
}

//------------------------------------------------------------------------------
// Local Function Implementation
//------------------------------------------------------------------------------
static void _msAPI_JpegDecoder_Reset(void)
{
    memset(&stJpegInfo_Decode, 0, sizeof(stJpegInfo_Decode));

    stJpegInfo_Decode.enState = EN_IDLE;
    stJpegInfo_Decode.enFormat = EN_JPEG_FMT_UNKNOWN;

    stJpegInfo_Decode.bHeaderDecoded = FALSE;
    stJpegInfo_Decode.bStartCmdSent = FALSE;

    stJpegInfo_Decode.u8OutputPixelSize = 2; // default for YUV 422

#if JPEG_RST_PATCH
    bJpegRstPatch_Activated = FALSE;
    u32JpegRstPatch_DataOffset = 0;
    u32JpegRstPatch_BufferAddr = 0;
    u32JpegRstPatch_BufferSize = 0;
#endif // #if JPEG_RST_PATCH

    bJpeg_UnRecoverableRstError = FALSE;
}

void msAPI_JpegDecoder_ErrorMapping(S16 sErrCode)
{
    switch (sErrCode)
    {
        case E_JPEG_BAD_DHT_COUNTS:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_DHT_COUNTS;
            break;

        case E_JPEG_BAD_DHT_INDEX:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_DHT_INDEX;
            break;

        case E_JPEG_BAD_DHT_MARKER:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_DHT_MARKER;
            break;

        case E_JPEG_BAD_DQT_MARKER:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_DQT_MARKER;
            break;

        case E_JPEG_BAD_DQT_TABLE:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_DQT_TABLE;
            break;

        case E_JPEG_BAD_PRECISION:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_PRECISION;
            break;

        case E_JPEG_BAD_HEIGHT:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_HEIGHT;
            break;

        case E_JPEG_BAD_WIDTH:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_WIDTH;
            break;

        case E_JPEG_TOO_MANY_COMPONENTS:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_TOO_MANY_COMPONENTS;
            break;

        case E_JPEG_BAD_SOF_LENGTH:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_SOF_LENGTH;
            break;

        case E_JPEG_BAD_VARIABLE_MARKER:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_VARIABLE_MARKER;
            break;

        case E_JPEG_BAD_DRI_LENGTH:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_DRI_LENGTH;
            break;

        case E_JPEG_BAD_SOS_LENGTH:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_SOS_LENGTH;
            break;

        case E_JPEG_BAD_SOS_COMP_ID:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_SOS_COMP_ID;
            break;

        case E_JPEG_W_EXTRA_BYTES_BEFORE_MARKER:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_W_EXTRA_BYTES_BEFORE_MARKER;
            break;

        case E_JPEG_NO_ARITHMETIC_SUPPORT:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_NO_ARITHMITIC_SUPPORT;
            break;

        case E_JPEG_UNEXPECTED_MARKER:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_UNEXPECTED_MARKER;
            break;

        case E_JPEG_NOT_JPEG:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_NOT_JPEG;
            break;

        case E_JPEG_UNSUPPORTED_MARKER:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_UNSUPPORTED_MARKER;
            break;

        case E_JPEG_BAD_DQT_LENGTH:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_DQT_LENGTH;
            break;

        case E_JPEG_TOO_MANY_BLOCKS:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_TOO_MANY_BLOCKS;
            break;

        case E_JPEG_UNDEFINED_QUANT_TABLE:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_UNDEFINED_QUANT_TABLE;
            break;

        case E_JPEG_UNDEFINED_HUFF_TABLE:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_UNDEFINED_HUFF_TABLE;
            break;

        case E_JPEG_NOT_SINGLE_SCAN:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_NOT_SINGLE_SCAN;
            break;

        case E_JPEG_UNSUPPORTED_COLORSPACE:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_UNSUPPORTED_COLORSPACE;
            break;

        case E_JPEG_UNSUPPORTED_SAMP_FACTORS:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_UNSUPPORTED_SAMP_FACTORS;
            break;

        case E_JPEG_DECODE_ERROR:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_DECODE_ERROR;
            break;

        case E_JPEG_BAD_RESTART_MARKER:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_RESTART_MARKER;
            break;

        case E_JPEG_ASSERTION_ERROR:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_ASSERTION_ERROR;
            break;

        case E_JPEG_BAD_SOS_SPECTRAL:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_SOS_SPECTRAL;
            break;

        case E_JPEG_BAD_SOS_SUCCESSIVE:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_SOS_SUCCESSIVE;
            break;

        case E_JPEG_STREAM_READ:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_STREAM_READ;
            break;

        case E_JPEG_NOTENOUGHMEM:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_NOTENOUGHMEM;
            break;

        case E_JPEG_STOP_DECODE:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_STOP_DECODE;
            break;

        case E_JPEG_BAD_APP1_MARKER:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_BAD_APP1_MARKER;
            break;

        case E_JPEG_NO_THUMBNAIL:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_NO_THUMBNAIL;
            break;

        case E_JPEG_UNSUPPORTED_HUFF_DECODE:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_UNSUPPORTED_HUFF_DECODE;
            break;

        case E_JPEG_READBUFFER_TOOSMALL:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_READBUFFER_TOOSMALL;
            break;

        case E_JPEG_NOT_ENOUGH_HEADER_INFO:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_NOT_ENOUGH_HEADER_INFO;
            break;

        case E_JPEG_JPD_DECODE_ERROR:
            g_stStillImage.enError = E_STILLIMAGE_JPEG_JPD_DECODE_ERROR;
            break;

        default:
            break;
    }
}


// This function is used when JPEG decoder is parsing header only
static S32 msAPI_JpegDecoder_FillHeaderBuffer(U32 u32Addr, U32 u32Length)
{
    BOOL bIsEOF;
    U32 u32Cnt;
    // Asked by JPEG decoder. 1st read data should be put ot 1st byte of BM buffer
    msAPI_StillImage_BMBuffer_Reset();

    u32Cnt = msAPI_JpegDecoder_DataRead(MsOS_PA2KSEG1(u32Addr), u32Length, &bIsEOF);
    MApi_JPEG_UpdateReadInfo(u32Cnt, bIsEOF);
    JPEG_DBG(printf("msAPI_JpegDecoder_FillHeaderBuffer().........\n"));
    JPEG_DBG(printf("u32Addr=0x%x, u32ReadSize=0x%x\n", u32Addr, u32Cnt));
    JPEG_DBG(printf("%02x %02x %02x %02x %02x %02x %02x %02x \n",
        *((U8*)(u32Addr)), *((U8*)(u32Addr+1)), *((U8*)(u32Addr+2)), *((U8*)(u32Addr+3)),
        *((U8*)(u32Addr+4)), *((U8*)(u32Addr+5)), *((U8*)(u32Addr+6)), *((U8*)(u32Addr+7))
        ));
    JPEG_DBG(printf("%02x %02x %02x %02x %02x %02x %02x %02x \n",
        *((U8*)(u32Addr+u32Cnt-8)), *((U8*)(u32Addr+u32Cnt-7)), *((U8*)(u32Addr+u32Cnt-6)), *((U8*)(u32Addr+u32Cnt-5)),
        *((U8*)(u32Addr+u32Cnt-4)), *((U8*)(u32Addr+u32Cnt-3)), *((U8*)(u32Addr+u32Cnt-2)), *((U8*)(u32Addr+u32Cnt-1))
        ));

    return u32Cnt;
}

// This function is used when JPEG decoder hardware is decoding data
static S32 msAPI_JpegDecoder_FillDecodeBuffer(JPEG_BuffLoadType eType)
{
    BOOL bIsEOF;
    U32 u32Addr, u32Request, u32ReadSize;

    // TBD: those who call this function should provide values for u32Addr and u32Request
    u32Addr = g_stStillImage.stInputCfgParams.u32InputBuffAddr;
    u32Request = g_stStillImage.stInputCfgParams.u32InputBuffLen / 2;
    if (eType == E_JPEG_BUFFER_HIGH)
    {
        u32Addr += u32Request;
    }
    u32ReadSize = msAPI_JpegDecoder_DataRead(u32Addr, u32Request, &bIsEOF);
    MApi_JPEG_UpdateReadInfo(u32ReadSize, bIsEOF);
    MApi_JPEG_SetMRBufferValid(eType);

    JPEG_DBG(printf("msAPI_JpegDecoder_FillDecodeBuffer().........\n"));
    JPEG_DBG(printf("u32Addr=0x%x, u32ReadSize=0x%x\n", u32Addr, u32ReadSize));
    JPEG_DBG(printf("%02x %02x %02x %02x %02x %02x %02x %02x \n",
        *((U8*)(u32Addr)), *((U8*)(u32Addr+1)), *((U8*)(u32Addr+2)), *((U8*)(u32Addr+3)),
        *((U8*)(u32Addr+4)), *((U8*)(u32Addr+5)), *((U8*)(u32Addr+6)), *((U8*)(u32Addr+7))
        ));
    JPEG_DBG(printf("%02x %02x %02x %02x %02x %02x %02x %02x \n",
        *((U8*)(u32Addr+u32ReadSize-8)), *((U8*)(u32Addr+u32ReadSize-7)), *((U8*)(u32Addr+u32ReadSize-6)), *((U8*)(u32Addr+u32ReadSize-5)),
        *((U8*)(u32Addr+u32ReadSize-4)), *((U8*)(u32Addr+u32ReadSize-3)), *((U8*)(u32Addr+u32ReadSize-2)), *((U8*)(u32Addr+u32ReadSize-1))
        ));
    return u32ReadSize;
}

#if JPEG_RST_PATCH
static S32 msAPI_JpegDecoder_RstPatchDataRead(U32 u32Addr, U32 u32Byte, BOOL *pIsEOF)
{
    #define MARKER_RST_0    0x00FFFFD0
    #define MARKER_RST_1    0x00FFFFD1
    #define MARKER_RST_2    0x00FFFFD2
    #define MARKER_RST_3    0x00FFFFD3
    #define MARKER_RST_4    0x00FFFFD4
    #define MARKER_RST_5    0x00FFFFD5
    #define MARKER_RST_6    0x00FFFFD6
    #define MARKER_RST_7    0x00FFFFD7

    #define MARKER_MASK     0xFF000007
    #define SWAP32_(x) (((x) << 24) | ((0x0000FF00UL & (x)) <<  8) | ((0x00FF0000UL & (x)) >>  8) | ((x)  >> 24))
    #define HAL_MEMORY_BARRIER()    { MsOS_Sync(); MsOS_FlushMemory(); }

    U32 u32Remainder, u32TotalData, u32Redundant;
    U32 u32Pattern, u32PatternAddr;
    U8 *pu8CachedBufferStartAddr;
    U64 u64Position;
#ifdef PROJNAME_SAMSUNG
    U32 u32DramFlag = E_BDMA_SDRAM12SDRAM1;
    BDMA_SrcDev eBDMASearchFlag = E_BDMA_SRCDEV_MIU1;
#else
    U32 u32DramFlag = E_BDMA_SDRAM2SDRAM;
    BDMA_SrcDev eBDMASearchFlag = E_BDMA_SRCDEV_MIU0;
#endif

    // collect information
    u32Remainder = msAPI_StillImage_BMBuffer_Remainder();
    u64Position = msAPI_StillImage_BMFile_Tell();
    pu8CachedBufferStartAddr = (U8 *)((u32JpegRstPatch_BufferAddr + u32JpegRstPatch_BufferSize / 2) - s32JpegRstPatch_CachedData);

    if ((u32u64_0(u64Position) == 0) && (u32Remainder == 0))
    {
        // 1st time, reload data
        msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BMBuffer_ActiveBuffSize());
        u32Remainder = msAPI_StillImage_BMBuffer_Remainder();
    }

    // check if there is enough data for processing
    u32TotalData = u32Remainder + s32JpegRstPatch_CachedData;

    if (u32TotalData <= u32Byte * 2)
    {
        // move data to cache buffer
        // TODO: what to do with this flag E_BDMA_SDRAM2SDRAM
        MDrv_BDMA_CopyHnd(MsOS_VA2PA((U32)pu8CachedBufferStartAddr), MsOS_VA2PA((U32)(pu8CachedBufferStartAddr - u32Remainder)), (u32TotalData), (BDMA_CpyType)(u32DramFlag), BDMA_OPCFG_DEF);

        // update cache data pointer and cache data size
        pu8CachedBufferStartAddr -= u32Remainder;
        s32JpegRstPatch_CachedData = u32TotalData;

        // flush & reload data
        msAPI_StillImage_BMBuffer_FlushBytes(u32Remainder);
        msAPI_StillImage_BMBuffer_CustomFill(msAPI_StillImage_BMBuffer_ActiveBuffSize());
        u32Remainder = msAPI_StillImage_BMBuffer_Remainder();
    }

    u32TotalData = s32JpegRstPatch_CachedData + u32Remainder;

    // search 0xFFD0 ~ 0xFFD8
    if (u32TotalData != 0)
    {
        U32 u32DataOffset = u32JpegRstPatch_DataOffset;

        // skip header
        if (u32TotalData < u32JpegRstPatch_DataOffset)
        {
            u32DataOffset = u32TotalData;
            u32JpegRstPatch_DataOffset -= u32TotalData;
        }
        else
        {
            // for next run
            u32JpegRstPatch_DataOffset = 0;
        }

        // search redundant EN_JPEG_MARKER_PREFIXs by using BDMA
        // and remove them by MDrv_BDMA_CopyHnd
        u32Pattern = 0x00FFFFD0;
search_again:
        u32PatternAddr = MDrv_BDMA_Search(
                (U32)(pu8CachedBufferStartAddr + u32DataOffset),
                u32TotalData - u32DataOffset,
                SWAP32_(u32Pattern),
                SWAP32_(MARKER_MASK),
                eBDMASearchFlag);

        if (u32PatternAddr != 0xFFFFFFFF)
        {
            U8 *pu8Ptr = (U8 *)u32PatternAddr + 1; // because the searched patter is xxFFFFD0 ~ xxFFFFD7

            // search redundant EN_JPEG_MARKER_PREFIXs
            for (u32Redundant = 0; ; u32Redundant++, pu8Ptr--)
            {
                if (*pu8Ptr != EN_JPEG_MARKER_PREFIX)
                {
                    break;
                }
            }

            // remove EN_JPEG_MARKER_PREFIXs
            if (u32Redundant)
            {
                JPEG_DBG(printf("redundant: %d, data: %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x, %02x\n",
                        u32Redundant,
                        *((U8 *)u32PatternAddr - 4),
                        *((U8 *)u32PatternAddr - 3),
                        *((U8 *)u32PatternAddr - 2),
                        *((U8 *)u32PatternAddr - 1),
                        *((U8 *)u32PatternAddr - 0),
                        *((U8 *)u32PatternAddr + 1),
                        *((U8 *)u32PatternAddr + 2),
                        *((U8 *)u32PatternAddr + 3),
                        *((U8 *)u32PatternAddr + 4)));

                // TODO: what to do with this flag E_BDMA_SDRAM2SDRAM
                MDrv_BDMA_CopyHnd(MsOS_VA2PA((U32)pu8CachedBufferStartAddr), MsOS_VA2PA((U32)(pu8CachedBufferStartAddr + u32Redundant)), (pu8Ptr - pu8CachedBufferStartAddr + 1), (BDMA_CpyType)(u32DramFlag), BDMA_OPCFG_DEF);
                

                pu8CachedBufferStartAddr += u32Redundant;
                u32TotalData -= u32Redundant;
                s32JpegRstPatch_CachedData -= u32Redundant;

                u64Position = msAPI_StillImage_BMFile_Tell();
                JPEG_INFO_MUST(printf("RST (%02x%02x), cnt: %d, pos: %d (0x%08x)\n",
                        *((U8 *)u32PatternAddr + 2),
                        *((U8 *)u32PatternAddr + 3),
                        u32Redundant,
                        u32u64_0(u64Position) - s32JpegRstPatch_CachedData + (pu8Ptr - pu8CachedBufferStartAddr + 1),
                        u32u64_0(u64Position) - s32JpegRstPatch_CachedData + (pu8Ptr - pu8CachedBufferStartAddr + 1)));


            }

            // search again
            goto search_again;
        }
    }

    // update cache data pointer and cache data size
    if (u32TotalData <= u32Byte)
    {
        // there is insufficient data requested
        u32Byte = u32TotalData;
        s32JpegRstPatch_CachedData = 0;
        *pIsEOF = TRUE;
    }
    else
    {
        // just minus u32Byte from s32JpegRstPatch_CachedData
        // even s32JpegRstPatch_CachedData becomes negative, it's ok for next run
        s32JpegRstPatch_CachedData -= u32Byte;
        *pIsEOF = FALSE;
    }

    // copy data to input buffer and flush cpu cache to physical memory
    // TODO: what to do with this flag E_BDMA_SDRAM2SDRAM
    MDrv_BDMA_CopyHnd(MsOS_VA2PA((U32)pu8CachedBufferStartAddr), MsOS_VA2PA(u32Addr), (u32Byte), (BDMA_CpyType)(u32DramFlag), BDMA_OPCFG_DEF);
    HAL_MEMORY_BARRIER();

    return u32Byte;
}
#endif // #if JPEG_RST_PATCH

static S32 msAPI_JpegDecoder_DataRead(U32 u32Addr, U32 u32Byte, BOOL *pIsEOF)
{
    U32 u32Remainder;

    UNUSED(u32Addr);

#if JPEG_RST_PATCH
    if (bJpegRstPatch_Activated == TRUE)
    {
        u32Remainder = msAPI_JpegDecoder_RstPatchDataRead(u32Addr, u32Byte, pIsEOF);
        return u32Remainder;
    }
    else
#endif // #if JPEG_RST_PATCH
    {
        // always set BM to phase 1 (for blocking read) for JPEG
        msAPI_StillImage_BMBuffer_FlushBytes(msAPI_StillImage_BMBuffer_Remainder());
        if (msAPI_StillImage_BMFile_EOF())
        {
            *pIsEOF = TRUE;
            return 0;
        }

        msAPI_StillImage_BMBuffer_CustomFill(u32Byte);

        u32Remainder = msAPI_StillImage_BMBuffer_Remainder();
        *pIsEOF = u32Remainder + (U32)msAPI_StillImage_BMFile_Tell() == msAPI_StillImage_BMFile_Size() ? TRUE : FALSE;

        return u32Remainder;
    }
}

static EN_JPEG_DECODER_STATUS msAPI_JpegDecoder_WaitDone(void)
{
    EN_JPEG_DECODER_STATUS enStatus = EN_DECODING;
    JPEG_Event enEvent;

    //For H/W bug, Check Vidx.
    if (E_JPEG_FAILED == MApi_JPEG_HdlVidxChk())
    {
        enEvent = E_JPEG_EVENT_DEC_ERROR_MASK;
    }
    else
    {
        enEvent = MApi_JPEG_GetJPDEventFlag();
    }

    if (E_JPEG_EVENT_DEC_DONE & enEvent)
    {
#if SUPPORT_MPO_FORMAT
        if(MApi_JPEG_IsMPOFormat())
        {
            JPEG_DBG(printf("[JPEG] One of MPO picture decode done!!!!!!!!!!!!!!!!!\n"));
#if 0       // Don't need to do this when decode next MPO in the same start address
            if (E_JPEG_EVENT_DEC_MRB_DONE & enEvent)
            {
                JPEG_BuffLoadType enPreLoadBuffType;

                if(MApi_JPEG_GetBuffLoadType(&enPreLoadBuffType) ==E_JPEG_OKAY)
                {
                    msAPI_JpegDecoder_FillDecodeBuffer(enPreLoadBuffType);
                }
            }
#endif
            u8DecodedMPOImageNum++;
            --num_of_mpo_image_left;
            if(num_of_mpo_image_left > 0)
            {
                JPEG_DBG(printf("num_of_mpo_image_left=0x%x.......................\n", num_of_mpo_image_left));
                while(num_of_mpo_image_left &&
                          ((pMPOIndex->mp_entry[num_of_mpo_image - num_of_mpo_image_left].attribute & E_MP_TYPE_MASK) != E_MP_TYPE_MULTI_FRAME_DISPARITY))
                {
                    JPEG_DBG(printf("skip entry %x because it is not disparity type.\n", (num_of_mpo_image - num_of_mpo_image_left)));
                    num_of_mpo_image_left--;
                }
            }
            else
            {
                //display_width = MApi_JPEG_GetAlignedPitch();
                //display_height = MApi_JPEG_GetAlignedHeight();
                // MApi_JPEG_MPO_MWB_COMBINE(display_buffer, write_buff_start, display_width, display_height, num_of_mpo_image, dspl_orientation);
                MApi_JPEG_DumpMPO();
            }
            enStatus = EN_DECODE_DONE;
        }
        else
#endif
        {
            JPEG_DBG(printf("[JPEG] Decode Done\n"));
            enStatus = EN_DECODE_DONE;
        }
    }
    else if (E_JPEG_EVENT_DEC_ERROR_MASK & enEvent)
    {
        JPEG_DBG(printf("[JPEG] Baseline decode error\n"));

        if (enEvent & E_JPEG_EVENT_DEC_RST_ERROR)
        {
#if JPEG_RST_PATCH
            if (bJpegRstPatch_Activated == FALSE)
            {
                bJpegRstPatch_Activated = TRUE;
                s32JpegRstPatch_CachedData = 0;
                JPEG_INFO_MUST(printf("RST patch activated\n"));
                return EN_DECODE_RST_ERR;
            }
            else if (bJpeg_UnRecoverableRstError == FALSE)
            {
                JPEG_INFO_MUST(printf("RST patch error, RST error again\n"));
                bJpeg_UnRecoverableRstError = TRUE;
            }
#else // #if JPEG_RST_PATCH

            bJpeg_UnRecoverableRstError = TRUE;
#endif // #if JPEG_RST_PATCH

            if ((bJpeg_UnRecoverableRstError == TRUE)
                    && (!(g_stStillImage.stInputCfgParams.u32ControlFlags & (U32)E_STILLIMAGE_CONTROL_FLAG_STOP_WHEN_RST_ERROR)))
            {
                // reset flag
                MApi_JPEG_SetJPDEventFlag(E_JPEG_EVENT_DEC_RST_ERROR);
                return enStatus;
            }
        }

        enStatus = EN_DECODE_ERR;
    }
    else if (E_JPEG_EVENT_DEC_MRB_DONE & enEvent)
    {
        JPEG_BuffLoadType enPreLoadBuffType;

        switch (MApi_JPEG_GetBuffLoadType(&enPreLoadBuffType))
        {
            case E_JPEG_OKAY:
                msAPI_JpegDecoder_FillDecodeBuffer(enPreLoadBuffType);
                break;

            case E_JPEG_FAILED:
                enStatus = EN_DECODE_ERR;
                break;

            case E_JPEG_RETRY:
            default:
                break;
        }
    }

    return enStatus;
}

#if SUPPORT_MPO_FORMAT
static U8 MApi_JPEG_MPO_DecodeNext(void)
{
    BOOL bIsEOF;
    U32 u32Cnt;
    display_width = MApi_JPEG_GetAlignedPitch();
    display_height = MApi_JPEG_GetAlignedHeight();
    start_offset = read_buffer_start ;
    JPEG_DBG(printf("read_buffer_start=0x%x, read_buffer_size=0x%x\n", read_buffer_start, read_buffer_size));
    JPEG_DBG(printf("num_of_mpo_image = %d, num_of_mpo_image_left = 0x%x\n", num_of_mpo_image, num_of_mpo_image_left));
    JPEG_DBG(printf("MPO start_offset = 0x%x, image offset = 0x%x\n", pMPOIndex->start_of_offset, pMPOIndex->mp_entry[num_of_mpo_image - num_of_mpo_image_left].offset));
    JPEG_DBG(printf("[MApi_JPEG_MPO_DecodeNext]start_offset = 0x%x, write_offset = 0x%x\n", start_offset, write_offset));
    JPEG_DBG(printf("seek to 0x%x\n", (pMPOIndex->start_of_offset + pMPOIndex->mp_entry[num_of_mpo_image - num_of_mpo_image_left].offset)));

    msAPI_StillImage_BMBuffer_Reset();
    //blocking seek due to blocking read.
    msAPI_StillImage_BMFile_Seek((pMPOIndex->start_of_offset + pMPOIndex->mp_entry[num_of_mpo_image - num_of_mpo_image_left].offset), E_BM_FILEPOS_SEEK_SET);

    u32Cnt = msAPI_JpegDecoder_DataRead((start_offset), read_buffer_size, &bIsEOF);
    MApi_JPEG_UpdateReadInfo(u32Cnt, bIsEOF);

#if 0
    U16 u16Index;
    for(u16Index=0; u16Index<32; u16Index++)
    {
        JPEG_DBG(printf("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x \n",
            *((U8*)(start_offset+16*u16Index)), *((U8*)(start_offset+16*u16Index+1)), *((U8*)(start_offset+16*u16Index+2)), *((U8*)(start_offset+16*u16Index+3)),
            *((U8*)(start_offset+16*u16Index+4)), *((U8*)(start_offset+16*u16Index+5)), *((U8*)(start_offset+16*u16Index+6)), *((U8*)(start_offset+16*u16Index+7)),
            *((U8*)(start_offset+16*u16Index+8)), *((U8*)(start_offset+16*u16Index+9)), *((U8*)(start_offset+16*u16Index+10)), *((U8*)(start_offset+16*u16Index+11)),
            *((U8*)(start_offset+16*u16Index+12)), *((U8*)(start_offset+16*u16Index+13)), *((U8*)(start_offset+16*u16Index+14)), *((U8*)(start_offset+16*u16Index+15))
            ));
    }
#endif

    MApi_JPEG_Rst();

    MApi_JPEG_SetMaxDecodeResolution(
            g_stStillImage.stInputCfgParams.u32JpegBaseLineMaxWidth,
            g_stStillImage.stInputCfgParams.u32JpegBaseLineMaxHeight);
    MApi_JPEG_SetProMaxDecodeResolution(
            g_stStillImage.stInputCfgParams.u32JpegProgressiveMaxWidth,
            g_stStillImage.stInputCfgParams.u32JpegProgressiveMaxHeight);

#if SUPPORT_MPO_FORMAT
    MApi_JPEG_SetMPOMaxDecodeResolution(
            g_stStillImage.stInputCfgParams.u32MPOBaseLineMaxWidth,
            g_stStillImage.stInputCfgParams.u32MPOBaseLineMaxHeight);
    MApi_JPEG_SetMPOProMaxDecodeResolution(
            g_stStillImage.stInputCfgParams.u32MPOProgressiveMaxWidth,
            g_stStillImage.stInputCfgParams.u32MPOProgressiveMaxHeight);
#endif

    JPEG_InitParam JpegInitParam;
    JpegInitParam.u32MRCBufAddr = MsOS_VA2PA(g_stStillImage.stInputCfgParams.u32InputBuffAddr);
    JpegInitParam.u32MRCBufSize = g_stStillImage.stInputCfgParams.u32InputBuffLen;
    JpegInitParam.u32MWCBufAddr = MsOS_VA2PA(g_stStillImage.stInputCfgParams.u32OutputBuffAddr);
    JpegInitParam.u32MWCBufSize = g_stStillImage.stInputCfgParams.u32OutputBuffLen;
    JpegInitParam.u32InternalBufAddr = MsOS_VA2PA(g_stStillImage.stInputCfgParams.u32ProgressiveJpegBuffAddr);
    JpegInitParam.u32InternalBufSize = g_stStillImage.stInputCfgParams.u32ProgressiveJpegBuffLen;
    JpegInitParam.u32DecByteRead = (MS_U32)msAPI_StillImage_BMBuffer_Remainder();
    JpegInitParam.bEOF =
            msAPI_StillImage_BMFile_Tell() + msAPI_StillImage_BMBuffer_Remainder() ==  msAPI_StillImage_BMFile_Size();
    JpegInitParam.u8DecodeType = E_JPEG_TYPE_MAIN;
    JpegInitParam.bInitMem = TRUE;
    JpegInitParam.pFillHdrFunc = msAPI_JpegDecoder_FillHeaderBuffer;
    JPEG_DBG(printf("Before Next MPO Init, JpegInitParam.u8DecodeType=%d==========\n", JpegInitParam.u8DecodeType));
    MApi_JPEG_Init(&JpegInitParam);

    if(  !MApi_JPEG_DecodeHdr() )
    {
        JPEG_ERR(printf("MApi_JPEG_DecodeHeader Error.\n"));
        return 0;
    }
    JPEG_DBG(printf("%dx%d\n", MApi_JPEG_GetNonAlignmentWidth(), MApi_JPEG_GetNonAlignmentHeight()));

    MApi_JPEG_Decode();
    return 1;
}

#if 0
static void MApi_JPEG_MPO_MWB_COMBINE(U32 display_buff, U32 write_buff_start, U32 display_width, U32 display_height, U32 num_of_mpo_image, U8 vertical)
{
    U32 base_buff_length = display_width * display_height;
    JPEG_DBG(printf("MApi_JPEG_MPO_MWB_COMBINE:display_buff = 0x%x, write_buff_start = 0x%x, vertical = %d\n", display_buff, write_buff_start, vertical));

    if(0 == vertical)
    {
        U32 i = 0, j = 0;
        for(j = 0; j < display_height; j++)
        {
            for(i = 0; i < num_of_mpo_image; i++)
            {
                memcpy((void *)(display_buff + display_width*2*num_of_mpo_image*j + display_width*2*i),
                       (void *)(write_buff_start + base_buff_length*2*i + display_width*2*j),
                       display_width*2);
            }
        }
    }
    else
    {
        memcpy((void *)display_buff, (void *)write_buff_start, base_buff_length*2*num_of_mpo_image);
    }

    return;
}
#endif
#endif

#undef _MSAPI_JPEG_DECODER_C_

///*** please do not remove change list tag ***///
///***$Change: 428882 $***///
