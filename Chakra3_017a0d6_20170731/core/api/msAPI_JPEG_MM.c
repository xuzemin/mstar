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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_JPEG.h
/// @brief API for JPEG decoding and display
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_JPEG_C

#include <stdio.h>
#include <string.h>

#include "debug.h"

#include "Board.h"
#include "hwreg.h"

// Common Definition
#include "datatype.h"




#include "drvCPU.h"
#include "msAPI_MailBox.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "drvMIU.h"
#include "drvMVOP.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "drvAUDIO.h"
#include "apiGOP.h"

#include "msAPI_Flash.h"
#include "apiGOP.h"
#include "msAPI_Video.h"


#include "msAPI_MIU.h"
#include "msAPI_JPEG_MM.h"
#include "apiXC_Ace.h"
#include "msAPI_Memory.h"
#include "msAPI_Timer.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_Scaler.h"
#include "MApp_PCMode.h"

#include "GPIO.h"
#include "MApp_GlobalVar.h"
//#include "Debug.h"
#if ((ENABLE_DMP) || (DISPLAY_LOGO))
////////////////////////////////

static JPEG_DISPLAY_INFO JpegDispInfo;
U32 gJpegDecodeStartTime;
//U16 u16JpegMaxWidth = (U16)JPEGBASEWIDTHMAX , u16JpegMaxHeight = (U16)JPEGBASEHEIGHTMAX;

extern void MApp_Picture_Setting_SetColor(INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_WIN eWindow);
#define JPEG_DBG(x) MS_DEBUG_MSG(x)

//**********************************************************
//#define JPEG_DECODE_DONE            0xFF
#define JPEG_BUFFER_TIMEOUT_MS        (1000LU)
#define JPEG_DECODE_TIMEOUT_MS        (3000LU)

#define JPEG_DWIN_CAPTURE_TIMEOUT   (50)

//extern En_DVB_decSystemType enDecSys;

U32 u32JpegOutputBuffer;

U8  u8CurrentBufferNo = 1;

static U8 u8AeonMailBox[12];
U32 u32ReadBuffAddr, u32ReadBuffLen;

// thumbnail variables
//static BOOLEAN bEnableThumbnail;

E_JPEG_EN_ERROR_CODE eErrCode = E_JPEG_EN_NO_ERR;

//**********************************************************
//Local Function ProtoType:
static BOOLEAN _msAPI_JPEG_MBXInit(void);

//**********************************************************
//Local Function :
BOOLEAN _msAPI_JPEG_MBXInit(void)
{
        //Register Class:
    MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_JPEG);
    MSApi_MBX_RegisterMSG(E_MBX_CLASS_JPEG, MM_COMMON_MBX_QUEUESIZE);

    return TRUE;
}




//**********************************************************

/******************************************************************************/
/// API for JPEG decoder initialization::
BOOLEAN msAPI_JPEG_Init(U8 u8Type)
{
    U32 u32AeonInitTimeOut = 0;
    BOOLEAN bAeonInit = TRUE;

    //temporarily
    JpegDispInfo.u16SrcWidth = 0;
    JpegDispInfo.u16SrcHeight = 0;
    u8Type = u8Type;

    u32AeonInitTimeOut = msAPI_Timer_GetTime0();

    if (bAeonInit == FALSE)
    {
        JPEG_DBG(printf("AEON False!\n"));
    }
    else
    {
        _msAPI_JPEG_MBXInit();
        JPEG_DBG(printf("Aeon load= %lu\n", msAPI_Timer_DiffTimeFromNow(u32AeonInitTimeOut)));
    }

    return bAeonInit;
}

/******************************************************************************/
/// API for JPEG information initialization
/// @param enJpegOutputFormat \b IN JPEG output format defined in JPEG_OUTPUT_FORMAT
/// @param u32JpegDstAddr \b IN JPEG output address to store the decompressed image
/// @param pJpegInfo \b IN Pointer to JPEG_INFO to store the initialization values
/******************************************************************************/
void msAPI_JPEG_InitJpegInfo(JPEG_OUTPUT_FORMAT enJpegOutputFormat, U32 u32JpegOutputAddr)
{
    U8 u8mode;

    u32JpegOutputBuffer = u32JpegOutputAddr;
    u8mode = 0x80;
    if (enJpegOutputFormat == JPEG_OUTPUT_FORMAT_SD)
    {
        // Standard Definition
        u8mode |= 0x08;
        JPEG_DBG(printf("SD\n"));
    }
    else if (enJpegOutputFormat == JPEG_OUTPUT_FORMAT_HD)
    {
        // High Definition
        JPEG_DBG(printf("HD\n"));
    }
}

/******************************************************************************/
/// API for retrieving the image information reported by decoder
/// @param pJpegInfo \b IN Pointer to JPEG_INFO to store the image information including width, height, and YUV format
/******************************************************************************/
BOOLEAN msAPI_JPEG_GetImageInfo(BOOLEAN bThumbnail, U16 *u16Width, U16 *u16Height)
{
    bThumbnail = bThumbnail;

    if (u16Width)
        *u16Width = JpegDispInfo.u16Width;
    if (u16Height)
        *u16Height = JpegDispInfo.u16Height;

    return TRUE;
}

/******************************************************************************/
/// API for starting JPEG data decoding
/// @param u32InternalBuffAddr \b IN Specify the internal buffer address used by decoder
/// @param u32InternalBuffLen \b IN Specify the internal buffer length
/// @param u32InputDataAddr \b IN Specify the input data buffer address
/// @param u32InputDataLen \b IN Specify the input data length
/// @param u32OutputDataAddr \b IN Specify the output data address
/// @param u8Type \b IN Specify the type of decoding, 0 for full image, 1 for thumbnail
/******************************************************************************/
void msAPI_JPEG_StartDecode(U32 u32InternalBuffAddr, U32 u32InternalBuffLen, U32 u32InputDataAddr, U32 u32InputDataLen, U32 u32OutputDataAddr, U8 u8Type)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_JPEG;
    mbxMsg.u8Index = MB_JPEG_CMD_DECODE_INIT;
    mbxMsg.u8ParameterCount = 9;
    mbxMsg.u8Parameters[0] = (U8)(u32InputDataAddr);
    mbxMsg.u8Parameters[1] = (U8)(u32InputDataAddr >> 8);
    mbxMsg.u8Parameters[2] = (U8)(u32InputDataAddr >> 16);
    mbxMsg.u8Parameters[3] = (U8)(u32InputDataAddr >> 24);
    mbxMsg.u8Parameters[4] = (U8)(u32OutputDataAddr);
    mbxMsg.u8Parameters[5] = (U8)(u32OutputDataAddr >> 8);
    mbxMsg.u8Parameters[6] = (U8)(u32OutputDataAddr >> 16);
    mbxMsg.u8Parameters[7] = (U8)(u32OutputDataAddr >> 24);
    mbxMsg.u8Parameters[8] = 0;
    while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_JPEG;
    mbxMsg.u8Index = MB_JPEG_CMD_DECODE_INIT;
    mbxMsg.u8ParameterCount = 9;
    mbxMsg.u8Parameters[0] = (U8)(u32InternalBuffAddr);
    mbxMsg.u8Parameters[1] = (U8)(u32InternalBuffAddr >> 8);
    mbxMsg.u8Parameters[2] = (U8)(u32InternalBuffAddr >> 16);
    mbxMsg.u8Parameters[3] = (U8)(u32InternalBuffAddr >> 24);
    mbxMsg.u8Parameters[4] = (U8)(u32InputDataLen >> 16);
    mbxMsg.u8Parameters[5] = (U8)(u32InternalBuffLen >> 16);
    mbxMsg.u8Parameters[6] = (U8)u8Type;
    mbxMsg.u8Parameters[7] = (U8)(0);
    mbxMsg.u8Parameters[8] = 1;
    while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_JPEG;
    mbxMsg.u8Index = MB_JPEG_CMD_DECODE_INIT;
    mbxMsg.u8ParameterCount = 9;
    mbxMsg.u8Parameters[0] = (U8)(JPEGBASEWIDTHMAX);
    mbxMsg.u8Parameters[1] = (U8)(JPEGBASEWIDTHMAX >> 8);
    mbxMsg.u8Parameters[2] = (U8)(JPEGBASEHEIGHTMAX);
    mbxMsg.u8Parameters[3] = (U8)(JPEGBASEHEIGHTMAX >> 8);
    mbxMsg.u8Parameters[4] = (U8)(JPEGPROWIDTHMAX);
    mbxMsg.u8Parameters[5] = (U8)(JPEGPROWIDTHMAX >> 8);
    mbxMsg.u8Parameters[6] = (U8)(JPEGPROHEIGHTMAX);
    mbxMsg.u8Parameters[7] = (U8)(JPEGPROHEIGHTMAX >> 8);
    mbxMsg.u8Parameters[8] = 2;
    while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));

    u32ReadBuffAddr = u32InputDataAddr;
    u32ReadBuffLen = u32InputDataLen;
}

JPEG_DECODER_STATE msAPI_JPEG_GetDecoderState(U32 *pu32Addr, U32 *pu32Size)
{

    MBX_Msg MB_Message;
    memset(&MB_Message,0,sizeof(MBX_Msg));
    if(MSApi_MBX_RecvMsg(E_MBX_CLASS_JPEG, &MB_Message, 0,MBX_CHECK_NORMAL_MSG)==E_MBX_SUCCESS)
    {
        if (MB_Message.u8MsgClass== E_MBX_CLASS_JPEG)
        {
            switch (MB_Message.u8Index)
            {
                case MB_JPEG_CMD_RETURN_STATUS:
                    return JPEG_DECODER_STATE_OUTPUT;

                case MB_JPEG_CMD_ASK_4_DATA:
                    *pu32Size = ((U32) MB_Message.u8Parameters[0] << 24);
                    *pu32Size += ((U32) MB_Message.u8Parameters[1] << 16);
                    *pu32Size += ((U32) MB_Message.u8Parameters[2] << 8);
                    *pu32Size += ((U32) MB_Message.u8Parameters[3]);

                    *pu32Addr = u32ReadBuffAddr;
                    if (MB_Message.u8Parameters[4])
                        *pu32Addr += ((u32ReadBuffLen - 128) / 2);

                    return JPEG_DECODER_STATE_INPUT;

                default:
                    break;
            }
        }
    }

    return JPEG_DECODER_STATE_DECODE;
}

void msAPI_JPEG_ProceedDecode(U32 u32DataSize)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_JPEG;
    mbxMsg.u8Index = MB_JPEG_CMD_FEED_DATA_SUCCESS;
    mbxMsg.u8ParameterCount = 4;
    mbxMsg.u8Parameters[0] = u32DataSize >> 24;
    mbxMsg.u8Parameters[1] = u32DataSize >> 16;
    mbxMsg.u8Parameters[2] = u32DataSize >> 8;
    mbxMsg.u8Parameters[3] = u32DataSize;
    mbxMsg.u8Parameters[4] = (U8)(JPEGPROWIDTHMAX);
    mbxMsg.u8Parameters[5] = (U8)(JPEGPROWIDTHMAX >> 8);
    mbxMsg.u8Parameters[6] = (U8)(JPEGPROHEIGHTMAX);
    mbxMsg.u8Parameters[7] = (U8)(JPEGPROHEIGHTMAX >> 8);
    mbxMsg.u8Parameters[8] = 2;
    while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));
}

JPEG_DECODE_STATUS msAPI_JPEG_GetDecodeStatus(void)
{
    U16 u16AlignedHeight = 0;
    U8 u8DownScaleFactor = 0;
    MBX_Msg MB_Message;
    memset(&MB_Message,0,sizeof(MBX_Msg));
    if ((EN_DECODE_STATE) u8AeonMailBox[2] == e_DecodeDone)
    {
        MS_DEBUG_MSG(printf("Decode done\n"));
        if (u8AeonMailBox[7])
        {
            MS_DEBUG_MSG(printf("Progressive: "));
        }
        else
        {
            MS_DEBUG_MSG(printf("Baseline: "));
        }

        JpegDispInfo.u16SrcPitch = (U16)u8AeonMailBox[3] << 8;
        JpegDispInfo.u16SrcPitch += (U16)u8AeonMailBox[4];

        u16AlignedHeight = (U16)u8AeonMailBox[5] << 8;
        u16AlignedHeight += (U16)u8AeonMailBox[6];

        JpegDispInfo.u16Width = (U16)u8AeonMailBox[8] << 8;
        JpegDispInfo.u16Width += (U16)u8AeonMailBox[9];
        JpegDispInfo.u16Height = (U16)u8AeonMailBox[10] << 8;
        JpegDispInfo.u16Height += (U16)u8AeonMailBox[11];

        if(
            (MSApi_MBX_RecvMsg(E_MBX_CLASS_JPEG, &MB_Message, 0,MBX_CHECK_NORMAL_MSG)==E_MBX_SUCCESS)
            &&(MB_Message.u8MsgClass==E_MBX_CLASS_JPEG)
            &&(MB_Message.u8Index==MB_JPEG_CMD_GET_RESOLUTION)
         )

        {
#if 0
            JpegDispInfo.u16SrcWidth = (U16)u8AeonMailBox[3] << 8;
            JpegDispInfo.u16SrcWidth += (U16)u8AeonMailBox[4];
            JpegDispInfo.u16SrcHeight = (U16)u8AeonMailBox[5] << 8;
            JpegDispInfo.u16SrcHeight += (U16)u8AeonMailBox[6];
#endif

            u8DownScaleFactor = MB_Message.u8Parameters[5];
            JpegDispInfo.u16SrcWidth = ((JpegDispInfo.u16Width + 0x1U) & ~0x1U) / u8DownScaleFactor;
            JpegDispInfo.u16SrcHeight = ((JpegDispInfo.u16Height + 0x1U) & ~0x1U) / u8DownScaleFactor;

            if (JpegDispInfo.u16SrcWidth > JpegDispInfo.u16SrcPitch)
            {
                JpegDispInfo.u16SrcWidth = JpegDispInfo.u16SrcPitch;
            }
            if (JpegDispInfo.u16SrcHeight > u16AlignedHeight)
            {
                JpegDispInfo.u16SrcHeight = u16AlignedHeight;
            }
        }
        else
        {
            JpegDispInfo.u16SrcWidth = JpegDispInfo.u16SrcPitch;
            JpegDispInfo.u16SrcHeight = u16AlignedHeight;
        }

        MS_DEBUG_MSG(printf("%ux%u --DownScaled--> %ux%u --Aligned--> %ux%u\n",
               JpegDispInfo.u16Width, JpegDispInfo.u16Height,
               JpegDispInfo.u16SrcWidth, JpegDispInfo.u16SrcHeight,
               JpegDispInfo.u16SrcPitch, u16AlignedHeight));

        // Marked by coverity_0445
        //printf("factor: %bu\n", u8DownScaleFactor);

        return JPEG_DECODE_DONE;
    }

    MS_DEBUG_MSG(printf("Decode fail\n"));
    return JPEG_DECODE_ERROR1; // any error
}

void msAPI_JPEG_Restart()
{
    return;  //temporarily
}

void msAPI_JPEG_CloseDisplayPath()
{
    // Enable Blue Screen
    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    //MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW); // call by msAPI_Scaler_SetBlueScreen already
    MDrv_MVOP_Enable(FALSE);
    //fix DTV display abnormal after displayed LOGO
#if(ENABLE_MIU_1 == ENABLE)
    //MDrv_MVOP_MiuSwitch(1);
#endif
}

void msAPI_Jpeg_SetDisplayInfo(U16 u16OutputX, U16 u16OutputY, U16 u16OutputWidth, U16 u16OutputHeight, U32 u32DecodeAddr, U16 u16LineSize, U8 enGopDFormat, U8 u8Align)
{
    JpegDispInfo.u32DispBuff = u32DecodeAddr;
    JpegDispInfo.u16X = u16OutputX;
    JpegDispInfo.u16Y = u16OutputY;
    JpegDispInfo.u16Width = u16OutputWidth;
    JpegDispInfo.u16Height = u16OutputHeight;
    JpegDispInfo.u16DispBuffPitch = u16LineSize;
    JpegDispInfo.enFormat = enGopDFormat;
    JpegDispInfo.u8Align = u8Align;
}

void msAPI_JPEG_StopDecoding()
{
    return;
}

//U8 u8x = 0;
void msAPI_JPEG_Display(U8 bOriginalAspect)
{
    MVOP_InputCfg dc_param;
#if 0
    MS_SYS_INFO enMsSysInfo;
#endif
    MVOP_VidStat videoSetting;
    U16 displayX, displayY, displayHSize, displayVSize;
    MS_WINDOW_TYPE tDstWin;

    // no display info, just decode only
    if ((JpegDispInfo.u16Width == 0) && (JpegDispInfo.u16Height == 0))
        return;

    // Enable Blue Screen
    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

//    MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);// called by MApp_ScreenMuteMonitor already

//    msAPI_VID_VOPInit();
    MDrv_MVOP_Init();

    //Refine: When we enter MM, input source type already be set to INPUT_SOURCE_STORAGE and
    //          msAPI_Scaler_SetSourceType() was called. So, we don't need to set source type again.
#if 0
    // set Scaler input source
    SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) = INPUT_SOURCE_STORAGE;
    enMsSysInfo.enDataInputSourceType = DATA_INPUT_SOURCE_STORAGE;
    enMsSysInfo.enInputSourceType = INPUT_SOURCE_STORAGE;
    enMsSysInfo.enAspectRatio = VIDEOSCREEN_NORMAL;
    msAPI_Scaler_SetSourceType(enMsSysInfo.enInputSourceType, OUTPUT_SCALER_MAIN_WINDOW);
#endif

    // set mvop parameters
    MDrv_MVOP_EnableBlackBG();
    MDrv_MVOP_Enable(FALSE);
    //=========JPEG TETS==========
    dc_param.u16HSize = JpegDispInfo.u16SrcPitch;
    dc_param.u16VSize = JpegDispInfo.u16SrcHeight;
    dc_param.u32YOffset = u32JpegOutputBuffer;
    dc_param.u32UVOffset = u32JpegOutputBuffer;
    dc_param.bSD = 1;
    dc_param.bYUV422 = 1;
    dc_param.bProgressive = 1;
    dc_param.bUV7bit = 0;
    dc_param.bDramRdContd = 1;
    dc_param.bField = 0;
    dc_param.b422pack = 1;
    dc_param.u16StripSize = dc_param.u16HSize;
    MDrv_MVOP_SetInputCfg(MVOP_INPUT_DRAM, &dc_param);

    memset(&videoSetting, 0, sizeof(MVOP_VidStat));
    videoSetting.u16HorSize = dc_param.u16HSize;
    videoSetting.u16VerSize = dc_param.u16VSize;
    videoSetting.u16FrameRate = 30000;  // frame rate to 60Hz
    videoSetting.u8AspectRate = ASP_4TO3;//ASP_16TO9;
    videoSetting.u8Interlace = 0;
    MDrv_MVOP_SetOutputCfg(&videoSetting, FALSE);

    // set scaling aspect to program
    stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_ORIGIN;

    if (bOriginalAspect)
    {
        // Set to the original aspect ratio
        if ((((U32)JpegDispInfo.u16Width * 32) / (U32)JpegDispInfo.u16Height) >
                (((U32)JpegDispInfo.u16SrcWidth * 32) / (U32)JpegDispInfo.u16SrcHeight))
        {
            // Height major
            displayHSize = (U16)(((U32)JpegDispInfo.u16Height * 32 / (U32)JpegDispInfo.u16SrcHeight) *
                                 (U32)JpegDispInfo.u16SrcWidth / 32) & 0xFFFE;
            displayX = JpegDispInfo.u16X + (JpegDispInfo.u16Width - displayHSize) / 2;
            displayY = JpegDispInfo.u16Y;
            displayVSize = JpegDispInfo.u16Height;
        }
        else
        {
            // Width major
            displayVSize = (U16)(((U32)JpegDispInfo.u16Width * 32 / (U32)JpegDispInfo.u16SrcWidth) *
                                 (U32)JpegDispInfo.u16SrcHeight / 32) & 0xFFFE;
            displayY = JpegDispInfo.u16Y + (JpegDispInfo.u16Height - displayVSize) / 2;
            displayX = JpegDispInfo.u16X;
            displayHSize = JpegDispInfo.u16Width;
        }
    }
    else
    {
        displayX = JpegDispInfo.u16X;
        displayY = JpegDispInfo.u16Y;
        displayHSize = JpegDispInfo.u16Width;
        displayVSize = JpegDispInfo.u16Height;
    }

    tDstWin.x = displayX;
    tDstWin.y = displayY;
    tDstWin.width = displayHSize;
    tDstWin.height = displayVSize;

    MApp_Scaler_EnableOverScan(FALSE);
    MApp_Scaler_SetWindow(NULL, NULL, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    //switch MIU to 0
    MDrv_MVOP_MiuSwitch(0);

    MDrv_MVOP_Enable(TRUE);
//    msAPI_VID_SetVOPClk(ENABLE);
    //MsOS_DelayTask(50);

    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);


    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
//    MApi_XC_GenerateBlackVideo(DISABLE, MAIN_WINDOW); // called by MApp_ScreenMuteMonitor() already

    return;
}
#if (MOVIE_THUMBNAIL)
//DO DIWN for movie thumbnail
void msAPI_JPEG_Display2_Movie_Thumbnail(
        U16 u16OutputWidth, U16 u16OutputHeight,
        U32 u32DestAddr, U32 u32DestSize, U16 u16LineSize, U8 enGopDFormat)
{
    U8  gopBank;
    GOP_DwinProperty dwinProperty;
    U32 dwinCapTime;
    XC_ApiStatus stXC_WinTime_Info;

    if(MApi_XC_GetStatus(&stXC_WinTime_Info, MAIN_WINDOW) == FALSE)
    {
        JPEG_DBG(printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n"));
        //__ASSERT(0);
    }
    /*
    printf("\nw=%u\n", stXC_WinTime_Info.stDispWin.width);
    printf("\nh=%u\n", stXC_WinTime_Info.stDispWin.height);
    printf("\nx=%u\n", stXC_WinTime_Info.stDispWin.x);
    printf("\ny=%u\n", stXC_WinTime_Info.stDispWin.y);
    u16OutputHeight = stXC_WinTime_Info.stDispWin.height-1;
    u16OutputWidth = stXC_WinTime_Info.stDispWin.width;
    u16LineSize =u16OutputWidth*2;
    */
    // skip DWIN if u32DispBuff is 0
    if (u32DestAddr == 0)
    {
        //__ASSERT(0);
        return;
    }
    gopBank =MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(E_GOP_CAP);

#if  defined(ENABLE_DMP) || (DISPLAY_LOGO)
    // set GOPD clock
    MApi_GOP_SetClkForCapture();
#endif //#ifdef ENABLE_DMP

    MApi_GOP_DWIN_Init();

    MApi_GOP_DWIN_SelectSourceScanType((EN_GOP_DWIN_SCAN_MODE)DWIN_SCAN_MODE_PROGRESSIVE/*MDrv_MVOP_GetIsInterlace()*/);
    MApi_GOP_DWIN_SetDataFmt((EN_GOP_DWIN_DATA_FMT)enGopDFormat);
    JPEG_DBG(printf("\n stXC_WinTime_Info.stDispWin.x=%u ,  stXC_WinTime_Info.stDispWin.y=%u  ,   g_IPanel.HStart()=%u  \n", stXC_WinTime_Info.stDispWin.x , stXC_WinTime_Info.stDispWin.y,  g_IPanel.HStart()));
    dwinProperty.u16x = 0; //stXC_WinTime_Info.stDispWin.x- g_IPanel.HStart();//MDrv_Scaler_GetDisplayWinStartH();//MDrv_Scaler_GetHPosition();//0;
    dwinProperty.u16y =0; //stXC_WinTime_Info.stDispWin.y;//MDrv_Scaler_GetDisplayWinStartV();//MDrv_Scaler_GetVPosition();//0;

    dwinProperty.u16h = u16OutputHeight; //u16OutputHeight - 1;
    dwinProperty.u32fbaddr0 = u32DestAddr;


    if (enGopDFormat == DWIN_DATA_FMT_RGB565)
    {
        dwinProperty.u32fbaddr1 = u32DestAddr + u32DestSize /** 2UL*/ + 64; // 64-byte is safe margin
        dwinProperty.u16w = u16OutputWidth& 0xfffc;//(u16OutputWidth & 0xfffc);
        dwinProperty.u16fbw = (u16LineSize) & 0xfffc;
        JPEG_DBG(printf("\nDWIN_DATA_FMT_RGB565  scaler pos x=%x  ,  y=%x, width=%x,  height=%x \n", dwinProperty.u16x, dwinProperty.u16y, dwinProperty.u16w ,dwinProperty.u16h));
    }
    else if (enGopDFormat == DWIN_DATA_FMT_ARGB8888)
    {
        dwinProperty.u32fbaddr1 = u32DestAddr + u32DestSize /** 4UL*/ + 64; // 64-byte is safe margin
        dwinProperty.u16w = u16OutputWidth& 0xfffc; //(u16OutputWidth & 0xfffe);  //kiwi 080912
        dwinProperty.u16fbw =( u16LineSize) & 0xfffc;
        JPEG_DBG(printf("\nDWIN_DATA_FMT_ARGB8888  scaler pos x=%x  ,  y=%x, width=%x,  height=%x \n", dwinProperty.u16x, dwinProperty.u16y, dwinProperty.u16w ,dwinProperty.u16h));
    }
    else if (enGopDFormat == DWIN_DATA_FMT_UV8Y8)
    {
        dwinProperty.u32fbaddr1 = u32DestAddr + u32DestSize /** 2UL*/ + 64; // 64-byte is safe margin
        dwinProperty.u16w = u16OutputWidth & 0xfffc ;//(u16OutputWidth & 0xfffc);
        dwinProperty.u16fbw = (u16LineSize) & 0xfffc;
        JPEG_DBG(printf("\n DWIN_DATA_FMT_UV8Y8  scaler pos x=%x  ,  y=%x, width=%x,  height=%x \n", dwinProperty.u16x, dwinProperty.u16y, dwinProperty.u16w ,dwinProperty.u16h));
        JPEG_DBG(printf("\n scaler pos u16fbw=%x  ,  u32fbaddr1=%lx, u32fbaddr0=%lx, \n", dwinProperty.u16fbw, dwinProperty.u32fbaddr1 , dwinProperty.u32fbaddr0));
    }

    //dwinProperty.u32fbaddr1 = 0xFFFFFFFF;
    //MApi_GFX_ClearFrameBuffer(0x4000000,0x200  , 0xff);
    //MApi_GFX_FlushQueue();
    //MApi_GOP_GWIN_SetForceWrite(TRUE);
    //RIU[0x1E2C] &= ~0xF00;
    //RIU[0x1E2C] |= 0x600;
    //enable DWIN progressive INT
    //MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, FALSE);
    //MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_VS, TRUE);
    MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, TRUE);

    MApi_GOP_DWIN_SetWinProperty(&dwinProperty);
    MApi_GOP_DWIN_SetAlphaValue(0x0f); // set to solid
    msAPI_Timer_Delayms(10);
    MApi_GOP_DWIN_CaptureOneFrame2();//MApi_GOP_DWIN_CaptureOneFrame2();

    dwinCapTime = msAPI_Timer_GetTime0();
    //printf("\n..%d", MApi_GOP_DWIN_GetIntrStatus() );
    while ((MApi_GOP_DWIN_GetIntrStatus() & GOPDWIN_INT_MASK_PROG) == 0)
    {
        if (msAPI_Timer_DiffTimeFromNow(dwinCapTime) >= JPEG_DWIN_CAPTURE_TIMEOUT)
        {
            //__ASSERT(0);
            break; //wait for DWIN capture done(fix RGB mode slide show cannot display some pics randomly)
        }
    }
    //MApi_GOP_DWIN_SetWinProperty(&dwinProperty);
    //RIU[0x1FFE] = 6;
    //RIU[0x1FFF] = 2;
    //RIU[0x1F40] = 0x80;
    //RIU[0x1F41] = 0x0;
    //MDrv_Timer_Delayms(10);
    //printf("\n..%d", MApi_GOP_DWIN_GetIntrStatus() );
    //RIU[0x1266] = 0x4;

    msAPI_Timer_Delayms(10); //temp solution. Need to check with DWIN HW designer.

    MApi_GOP_DWIN_ClearIntr(GOPDWIN_INT_MASK_PROG);
    MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, FALSE);
    MApi_GOP_GWIN_SwitchGOP(gopBank);
}
#endif  //#if (MOVIE_THUMBNAIL)

void msAPI_JPEG_Display2(
    U16 u16InputX, U16 u16InputY, U16 u16InputWidth, U16 u16InputHeight,
    U16 u16OutputX, U16 u16OutputY, U16 u16OutputWidth, U16 u16OutputHeight,
    U32 u32SrcAddr, U16 u16SrcWidth, U16 u16SrcHeight,
    U32 u32DestAddr, U32 u32DestSize, U16 u16LineSize, U8 enGopDFormat)
{
    MVOP_InputCfg dc_param;
#if 0
    MS_SYS_INFO enMsSysInfo;
#endif
    MVOP_VidStat videoSetting;
    U8  gopBank;
    GOP_DwinProperty dwinProperty;
    U32 dwinCapTime;
    MS_WINDOW_TYPE tCropWin, tDstWin;

    // Enable Blue Screen
    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

//   MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW); // called by  msAPI_Scaler_SetBlueScreen() already

//   msAPI_VID_VOPInit();
    MDrv_MVOP_Init();

    //Refine: When we enter MM, input source type already be set to INPUT_SOURCE_STORAGE and
    //          msAPI_Scaler_SetSourceType() was called. So, we don't need to set source type again.
#if 0
    // set Scaler input source
    SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) = INPUT_SOURCE_STORAGE;
    enMsSysInfo.enDataInputSourceType = DATA_INPUT_SOURCE_STORAGE;
    enMsSysInfo.enInputSourceType = INPUT_SOURCE_STORAGE;
    enMsSysInfo.enAspectRatio = VIDEOSCREEN_NORMAL;
    msAPI_Scaler_SetSourceType(enMsSysInfo.enInputSourceType, OUTPUT_SCALER_MAIN_WINDOW);
#endif
    MApi_GFX_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_PC, GFX_YUV_IN_255, GFX_YUV_YUYV,  GFX_YUV_YUYV);

    // set mvop parameters
    MDrv_MVOP_EnableBlackBG();
    MDrv_MVOP_Enable(FALSE);
    //switch MIU to 0
    MDrv_MVOP_MiuSwitch(0);
    dc_param.u16HSize = (u16SrcWidth);// + 15) & 0xfff0;       // VOP must be 8 pixel alignment
    dc_param.u16VSize = u16SrcHeight;
    dc_param.u32YOffset = u32SrcAddr;
    dc_param.u32UVOffset = u32SrcAddr;
    dc_param.bSD = 1;
    dc_param.bYUV422 = 1;
    dc_param.bProgressive = 1;
    dc_param.bUV7bit = 0;
    dc_param.bDramRdContd = 1;
    dc_param.bField = 0;
    dc_param.b422pack = 1;
    dc_param.u16StripSize = dc_param.u16HSize;
    MDrv_MVOP_SetInputCfg(MVOP_INPUT_DRAM, &dc_param);

    memset(&videoSetting, 0, sizeof(MVOP_VidStat));
    videoSetting.u16HorSize = dc_param.u16HSize;
    videoSetting.u16VerSize = u16SrcHeight;
    videoSetting.u16FrameRate = 30000;  // frame rate to 60Hz
    videoSetting.u8AspectRate = ASP_4TO3;
    videoSetting.u8Interlace = 0;
    MDrv_MVOP_SetOutputCfg(&videoSetting, FALSE);

    // set scaling aspect to program
    stSystemInfo[MAIN_WINDOW].enAspectRatio = VIDEOSCREEN_ORIGIN;

    tCropWin.x = u16InputX;
    tCropWin.y = u16InputY;
    tCropWin.width = u16InputWidth & 0xfffe;
    tCropWin.height = u16InputHeight;

    tDstWin.x = u16OutputX;
    tDstWin.y = u16OutputY;
    tDstWin.width = u16OutputWidth;
    tDstWin.height = u16OutputHeight;
    MApp_Scaler_SetWindow(NULL, &tCropWin, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                          SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    MDrv_MVOP_Enable(TRUE);
//    msAPI_VID_SetVOPClk(ENABLE);

    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

    // wait input vsycn ready before disable black video
    //MApi_XC_WaitInputVSync(3, 50);       // <-- move to MApp_Jpeg_DisplayLogo
    //MApi_XC_GenerateBlackVideo(DISABLE, MAIN_WINDOW); // <-- move to MApp_Jpeg_DisplayLogo

    // skip DWIN if u32DispBuff is 0
    if (u32DestAddr == 0)
    {
        return;
    }

    gopBank = MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(E_GOP_CAP);

#if ((ENABLE_DMP) || (DISPLAY_LOGO))
    // set GOPD clock
    MApi_GOP_SetClkForCapture();
#endif //#if ENABLE_DMP

    MApi_GOP_DWIN_Init();

    MApi_GOP_DWIN_SelectSourceScanType((EN_GOP_DWIN_SCAN_MODE)MDrv_MVOP_GetIsInterlace());
    MApi_GOP_DWIN_SetDataFmt((EN_GOP_DWIN_DATA_FMT)enGopDFormat);
    dwinProperty.u16x = 0;
    dwinProperty.u16y = 0;
    dwinProperty.u16h = u16OutputHeight - 1;
    dwinProperty.u32fbaddr0 = u32DestAddr;
    if (enGopDFormat == DWIN_DATA_FMT_RGB565)
    {
        dwinProperty.u32fbaddr1 = u32DestAddr + u32DestSize * 2UL + 64; // 64-byte is safe margin
        dwinProperty.u16w = (u16OutputWidth & 0xfffc);
        dwinProperty.u16fbw = u16LineSize & 0xfffc;
    }
    else if (enGopDFormat == DWIN_DATA_FMT_ARGB8888)
    {
        dwinProperty.u32fbaddr1 = u32DestAddr + u32DestSize * 4UL + 64; // 64-byte is safe margin
        dwinProperty.u16w = (u16OutputWidth & 0xfffe);
        dwinProperty.u16fbw = u16LineSize & 0xfffe;
    }

    // enable DWIN progressive INT
    MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, TRUE);

    MApi_GOP_DWIN_SetWinProperty(&dwinProperty);
    MApi_GOP_DWIN_SetAlphaValue(0x0f); // set to solid
    msAPI_Timer_Delayms(10);
    MApi_GOP_DWIN_CaptureOneFrame();

    dwinCapTime = msAPI_Timer_GetTime0();

    while ((MApi_GOP_DWIN_GetIntrStatus() & GOPDWIN_INT_MASK_PROG) == 0)
    {
        if (msAPI_Timer_DiffTimeFromNow(dwinCapTime) >= JPEG_DWIN_CAPTURE_TIMEOUT)
        {
            break; //wait for DWIN capture done(fix RGB mode slide show cannot display some pics randomly)
        }
    }

    MApi_GOP_DWIN_ClearIntr(GOPDWIN_INT_MASK_PROG);
    MApi_GOP_DWIN_EnableIntr(GOPDWIN_INT_MASK_PROG, FALSE);

    MApi_GOP_GWIN_SwitchGOP(gopBank);

    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

    MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);

    MDrv_MVOP_EnableBlackBG();
    MDrv_MVOP_Enable(FALSE);
}

void msAPI_JPEG_AdjustDisplay(
    U16 u16InputX, U16 u16InputY, U16 u16InputWidth, U16 u16InputHeight,
    U16 u16OutputX, U16 u16OutputY, U16 u16OutputWidth, U16 u16OutputHeight)
{
    MS_WINDOW_TYPE tCropWin, tDstWin;
    // NOTE: this function has to be called only after msAPI_JPEG_Display2() is called before

    tCropWin.x = u16InputWidth & 0xfffe;
    tCropWin.y = u16InputHeight;
    tCropWin.width = u16InputX;
    tCropWin.height = u16InputY;

    tDstWin.x = u16OutputX;
    tDstWin.y = u16OutputY;
    tDstWin.width = u16OutputWidth;
    tDstWin.height = u16OutputHeight;
    MApp_Scaler_SetWindow(NULL, &tCropWin, &tDstWin, stSystemInfo[MAIN_WINDOW].enAspectRatio,
                          SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

}

void msAPI_JPEG_GetSize(U16 *u16Width, U16 *u16Height)
{
    *u16Width = JpegDispInfo.u16SrcWidth;
    *u16Height = JpegDispInfo.u16SrcHeight;
}

void msAPI_JPEG_GetPitch(U16 *u16Pitch)
{
    *u16Pitch = JpegDispInfo.u16SrcPitch;
}

void msAPI_JPEG_SetSize(U16 u16Width, U16 u16Height, U16 u16Pitch)
{
    // TODO: this function is used for testing purpose
    JpegDispInfo.u16SrcWidth = u16Width;
    JpegDispInfo.u16SrcHeight = u16Height;
    JpegDispInfo.u16SrcPitch = u16Pitch;
}

BOOLEAN msAPI_JPEG_EncoderInit(void)
{
    U32 u32AeonInitTimeOut = 0;
    BOOLEAN bAeonInit = TRUE;

    //MDrv_Aeon_Enable();
    u32AeonInitTimeOut = msAPI_Timer_GetTime0();
    while (MDrv_ReadByte(MB_51_REG_PARAM_00) != 0x18)
    {
        if (msAPI_Timer_DiffTimeFromNow(u32AeonInitTimeOut) > 1000)
        {
            bAeonInit = FALSE;
            break;
        }
    }

    if (bAeonInit == FALSE)
    {
        JPEG_DBG(printf("AEON False!\n"));
    }
    else
    {
        _msAPI_JPEG_MBXInit();

        JPEG_DBG(printf("Aeon load= %lu\n", msAPI_Timer_DiffTimeFromNow(u32AeonInitTimeOut)));
    }

    return bAeonInit;
}

/******************************************************************************/
/// API for starting JPEG data decoding
/// @param u32InternalBuffAddr \b IN Specify the internal buffer address used by encoder
/// @param u32InternalBuffLen \b IN Specify the internal buffer length
/// @param u32InputDataAddr \b IN Specify the input data buffer address
/// @param u32InputDataLen \b IN Specify the input data length
/// @param u32OutputDataAddr \b IN Specify the output buffer address
/// @param u32OutputDataAddr \b IN Specify the output buffer length
/// @param u16Width \b IN Specify the width of source image
/// @param u16Height \b IN Specify the height of source image
/// @return TURE if parameters are correctly sent to encoder or FALSE otherwise
/******************************************************************************/
BOOLEAN msAPI_JPEG_StartEncode(
    U32 u32InternalBuffAddr,
    U32 u32InternalBuffLen,
    U32 u32InputDataAddr,
    U32 u32InputDataLen,
    U32 u32OutputBuffAddr,
    U32 u32OutputBuffLen,
    U16 u16Width,
    U16 u16Height)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_JPEG_ENCODER;
    mbxMsg.u8Index = MB_JPEG_EN_CMD_SET_READ_BUFF_INFO;
    mbxMsg.u8ParameterCount = 8;
    mbxMsg.u8Parameters[0] = (U8)(u32InputDataAddr);
    mbxMsg.u8Parameters[1] = (U8)(u32InputDataAddr >> 8);
    mbxMsg.u8Parameters[2] = (U8)(u32InputDataAddr >> 16);
    mbxMsg.u8Parameters[3] = (U8)(u32InputDataAddr >> 24);
    mbxMsg.u8Parameters[4] = (U8)(u32InputDataLen);
    mbxMsg.u8Parameters[5] = (U8)(u32InputDataLen >> 8);
    mbxMsg.u8Parameters[6] = (U8)(u32InputDataLen >> 16);
    mbxMsg.u8Parameters[7] = (U8)(u32InputDataLen >> 24);
    if(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg))
    {
        return FALSE;
    }

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_JPEG_ENCODER;
    mbxMsg.u8Index = MB_JPEG_EN_CMD_SET_INTERNAL_BUFF_INFO;
    mbxMsg.u8ParameterCount = 8;
    mbxMsg.u8Parameters[0] = (U8)(u32InternalBuffAddr);
    mbxMsg.u8Parameters[1] = (U8)(u32InternalBuffAddr >> 8);
    mbxMsg.u8Parameters[2] = (U8)(u32InternalBuffAddr >> 16);
    mbxMsg.u8Parameters[3] = (U8)(u32InternalBuffAddr >> 24);
    mbxMsg.u8Parameters[4] = (U8)(u32InternalBuffLen);
    mbxMsg.u8Parameters[5] = (U8)(u32InternalBuffLen >> 8);
    mbxMsg.u8Parameters[6] = (U8)(u32InternalBuffLen >> 16);
    mbxMsg.u8Parameters[7] = (U8)(u32InternalBuffLen >> 24);
    if(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg))
    {
        return FALSE;
    }

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_JPEG_ENCODER;
    mbxMsg.u8Index = MB_JPEG_EN_CMD_SET_WRITE_BUFF_INFO;
    mbxMsg.u8ParameterCount = 8;
    mbxMsg.u8Parameters[0] = (U8)(u32OutputBuffAddr);
    mbxMsg.u8Parameters[1] = (U8)(u32OutputBuffAddr >> 8);
    mbxMsg.u8Parameters[2] = (U8)(u32OutputBuffAddr >> 16);
    mbxMsg.u8Parameters[3] = (U8)(u32OutputBuffAddr >> 24);
    mbxMsg.u8Parameters[4] = (U8)(u32OutputBuffLen);
    mbxMsg.u8Parameters[5] = (U8)(u32OutputBuffLen >> 8);
    mbxMsg.u8Parameters[6] = (U8)(u32OutputBuffLen >> 16);
    mbxMsg.u8Parameters[7] = (U8)(u32OutputBuffLen >> 24);
    if(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg))
    {
        return FALSE;
    }

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_JPEG_ENCODER;
    mbxMsg.u8Index = MB_JPEG_EN_CMD_SET_RESOLUTION_INFO;
    mbxMsg.u8ParameterCount = 4;
    mbxMsg.u8Parameters[0] = (U8)(u16Width);
    mbxMsg.u8Parameters[1] = (U8)(u16Width >> 8);
    mbxMsg.u8Parameters[2] = (U8)(u16Height);
    mbxMsg.u8Parameters[3] = (U8)(u16Height >> 8);
    if(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg))
    {
        return FALSE;
    }

    eErrCode = E_JPEG_EN_NOT_READY;
    return TRUE;
}

E_JPEG_EN_ERROR_CODE msAPI_JPEG_GetEncoderState(U32 *pu32Size)
{
    MBX_Msg MB_Message;
    memset(&MB_Message,0,sizeof(MBX_Msg));
    if (eErrCode != E_JPEG_EN_NOT_READY)
        return E_JPEG_EN_NO_ERR;

    *pu32Size = 0;
    if(MSApi_MBX_RecvMsg(E_MBX_CLASS_JPEG_ENCODER, &MB_Message, 0,MBX_CHECK_NORMAL_MSG)==E_MBX_SUCCESS)
    {
        if (MB_Message.u8MsgClass == E_MBX_CLASS_JPEG_ENCODER)
        {
            switch (MB_Message.u8Index)
            {
                case MB_JPEG_EN_RESULT:
                    eErrCode = (E_JPEG_EN_ERROR_CODE)MB_Message.u8Parameters[4];
                    switch (eErrCode)
                    {
                        case E_JPEG_EN_NO_ERR:
                            *pu32Size = ((U32)MB_Message.u8Parameters[0]);
                            *pu32Size += ((U32)MB_Message.u8Parameters[1] << 8);
                            *pu32Size += ((U32)MB_Message.u8Parameters[2] << 16);
                            *pu32Size += ((U32)MB_Message.u8Parameters[3] << 24);
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    return eErrCode;
}
#else // #if ((ENABLE_DMP) || (DISPLAY_LOGO))
#if defined (__51__)
static code U8 Useless;
#endif
#endif // #if ((ENABLE_DMP) || (DISPLAY_LOGO))

#undef MSAPI_JPEG_C
