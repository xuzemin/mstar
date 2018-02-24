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

#define MSAPI_IFRAME_C
///////////////////////////////////////////////////////////////////////////////
//
//  File name: msAPI_IFrame.c
//  Version: 1.0
//  Date: 2006/3/25
//
//  Company: MStarSemi Inc.
//
//  Description: IFrame API
//  [Doxygen]
/// @file msAPI_IFrame.h
/// This file includes MStar application interface for I-Frame process
/// @brief Video IFrame API
/// @author MStarSemi Inc.
///
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
/*                    Header Files                                            */
/* ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "Board.h"
#include "debug.h"

#if MHEG5_ENABLE
// XC related include files
#include "MsCommon.h"

#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "drvMVOP.h"
#include "msAPI_Video.h"
#include "mapp_iframe.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_MHEG5.h"

#include "MApp_Scaler.h"
#include "MApp_XC_PQ.h"
#include "drvCPU.h"
#include "msAPI_MailBox.h"

#include "msAPI_BDMA.h"
#include "apiXC_Ace.h"
#include "sysinfo.h"
#include "mapp_videoplayer.h"
#include "MApp_MVDMode.h"
/* Variables and functions defined in MApp */
#define MVD_DEBUGINFO(x)    MS_DEBUG_MSG(x)
#define DISABLE_COLOR_ENHANCE  1
#define DISABLE_COLOR_ENHANCE2 2
#define ENABLE_COLOR_ENHANCE 2

extern BOOLEAN fEnableSignalMonitor;
extern BOOLEAN fEnableMvdTimingMonitor;
extern BOOLEAN bMVDTimingChange;
extern BOOLEAN bPrepareChange;
extern VDEC_DispInfo gstVidStatus, gstPreVidStatus;

static U16 u16Position_X=0, u16Position_Y=0, u16Offset_X=0, u16Offset_Y=0;
static U16 u16Scale_Width=MHEG_XRES_COORD, u16Scale_Height=MHEG_YRES_COORD;
static U16 u16BoxSize_X=MHEG_XRES_COORD, u16BoxSize_Y=MHEG_YRES_COORD;
static U16 preH_CapSize=0, preV_CapSize=0, preH_CapStart=0, preV_CapStart=0;
static BOOLEAN bDecodeSucceed=false;
U16 Run_Time = 0;
U16 Run_Time_Max = 1;


/******************************************************************************/
/// API for decode I frame
/// @param u32FrameBufAddr \b IN: start address of frame buffer to which I frame is decoded
/// @param u32StreamBufAddr \b IN: start address of the I frame bitstream
/// @param u32StreamBufEndAddr \b IN: End address of the I frame bitstream
/// @return BOOLEAN:
/// -TRUE : decode sucessfully
/// -FALSE: error occured when decoding
/******************************************************************************/
static BOOLEAN _MApp_IFrame_Decode( U32 u32FrameBufAddr, U32 u32StreamBufAddr, U32 u32StreamBufEndAddr)
{
    MVOP_VidStat stMvopVidSt;
    MVOP_InputCfg dc_param;
    //MS_SYS_INFO enMsSysInfo;
    VDEC_FrameInfo FI;

    g_MHEG5Video.bIFrame = TRUE;

    // Enable Blue Screen
    //msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, ENABLE, NULL, MAIN_WINDOW);
    //msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

    #if 0
    // set Scaler input source
    SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) = INPUT_SOURCE_DTV;
    enMsSysInfo.enDataInputSourceType = DATA_INPUT_SOURCE_DTV;
    enMsSysInfo.enInputSourceType = INPUT_SOURCE_DTV;
    enMsSysInfo.enAspectRatio = VIDEOSCREEN_NORMAL;
    msAPI_Scaler_SetSourceType(enMsSysInfo.enInputSourceType);
    #endif

    // set MHEG I-frame buffer & bitstream buffer and then decode I-frame
    if (MApi_VDEC_MHEG_DecodeIFrame(u32FrameBufAddr, u32StreamBufAddr, u32StreamBufEndAddr) == FALSE)
    {
        MS_DEBUG_MSG(printf("decode I-frame hang\n"));
        return FALSE;
    }
    MS_DEBUG_MSG(printf("decode I-frame done\n"));


    // get frame information
    if( FALSE == msAPI_VID_GetVidInfo(&gstVidStatus) ) {
        MVD_DEBUGINFO(printf( "invalid mpeg or video info\n"));
        return false;
    }
    //(printf("hsize,vsize=%u,%u\n", gstVidStatus.u16HorSize, gstVidStatus.u16VerSize));
    //(printf("frame rate=%u\n", gstVidStatus.u32FrameRate));
    //(printf("i/p=%bx\n", gstVidStatus.u8Interlace));

    MApi_VDEC_GetDecFrameInfo(&FI);
    //printf("FI.u32LumaAddr:%lx , FI.u32ChromaAddr:%lx\n",FI.u32LumaAddr,FI.u32ChromaAddr);

    // set mvop parameters
    MDrv_MVOP_EnableBlackBG();
    MDrv_MVOP_Enable( FALSE );

    dc_param.u16HSize = gstVidStatus.u16HorSize;
    dc_param.u16VSize = gstVidStatus.u16VerSize;
    //dc_param.u32YOffset = u32FrameBufAddr;
    dc_param.u32YOffset = FI.u32LumaAddr & ~MIU_INTERVAL;
    dc_param.u32UVOffset = (FI.u32ChromaAddr & ~MIU_INTERVAL);
#if defined(SUPPORT_MPEG2_SD_ONLY)
    dc_param.bSD = 1;
#elif VIDEO_FIRMWARE_CODE >= VIDEO_FIRMWARE_CODE_HD
    dc_param.bSD = 0;
#else
    dc_param.bSD = 1;
#endif
    dc_param.bYUV422 = 0;
    dc_param.bProgressive = (gstVidStatus.u8Interlace) ? 0:1;
    dc_param.bUV7bit = 0;
    dc_param.bDramRdContd = 0;
    dc_param.bField = 0;
    dc_param.b422pack = 0;
    dc_param.u16StripSize = 0;
    MDrv_MVOP_SetInputCfg(MVOP_INPUT_DRAM, &dc_param);

    memset(&stMvopVidSt, 0, sizeof(MVOP_VidStat));
    stMvopVidSt.u16HorSize   = gstVidStatus.u16HorSize;
    stMvopVidSt.u16VerSize   = gstVidStatus.u16VerSize;
    stMvopVidSt.u16FrameRate = gstVidStatus.u32FrameRate;
    stMvopVidSt.u8AspectRate = gstVidStatus.u8AspectRate;
    stMvopVidSt.u8Interlace  = gstVidStatus.u8Interlace;
    MDrv_MVOP_SetOutputCfg(&stMvopVidSt, FALSE);

    // set scaler window
    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    MDrv_MVOP_Enable( TRUE );

    return TRUE;
}


/******************************************************************************/
/// API for decode I frame
/// @param u32FrameBufAddr \b IN: start address of frame buffer to which I frame is decoded
/// @param u32StreamBufAddr \b IN: start address of the I frame bitstream
/// @param u32StreamBufEndAddr \b IN: End address of the I frame bitstream
/// @return BOOLEAN:
/// -TRUE : decode sucessfully
/// -FALSE: error occured when decoding
/******************************************************************************/
static BOOLEAN _MApp_IFrame_Decode_H264( U32 u32FrameBufAddr, U32 u32StreamBufAddr, U32 u32StreamBufEndAddr)
{
    MVOP_VidStat stMvopVidSt;
    MVOP_InputCfg dc_param;
    //MS_SYS_INFO enMsSysInfo;
    VDEC_FrameInfo FI;
    U16 c;

    g_MHEG5Video.bIFrame = TRUE;

    // Enable Blue Screen
    //msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, ENABLE, NULL, MAIN_WINDOW);
    //msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);


    // set MHEG I-frame buffer & bitstream buffer and then decode I-frame
    if (MApi_VDEC_MHEG_DecodeIFrame(u32FrameBufAddr, u32StreamBufAddr, u32StreamBufEndAddr) == FALSE)
    {
        MS_DEBUG_MSG(printf("decode H264 I-frame hang\n"));
        return FALSE;
    }
    //printf("decode H264 I-frame done\n");




    for(c = 100; c > 0; c--)
    {
        if(E_VDEC_OK == MApi_VDEC_CheckDispInfoRdy())
        {
            // get frame information
            if( TRUE == msAPI_VID_GetVidInfo(&gstVidStatus) )
            {
               MApi_VDEC_GetDecFrameInfo(&FI);
               //printf("Get video success\n");
                //MVD_DEBUGINFO(printf( "invalid mpeg or video info\n"));
                break;
            }
        }
    }
    //printf("width:%d , height:%d , addr:0x%0x , 0x%x\n",FI.u16Width , FI.u16Height , FI.u32ChromaAddr , FI.u32LumaAddr);

    if(c == 0)
    {
        return false;
    }
    //(printf("hsize,vsize=%u,%u\n", gstVidStatus.u16HorSize, gstVidStatus.u16VerSize));
    //(printf("frame rate=%u\n", gstVidStatus.u32FrameRate));
    //(printf("i/p=%bx\n", gstVidStatus.u8Interlace));

    // set mvop parameters
    MDrv_MVOP_EnableBlackBG();
    MDrv_MVOP_Enable( FALSE );

    dc_param.u16HSize = gstVidStatus.u16HorSize;
    dc_param.u16VSize = gstVidStatus.u16VerSize;
    dc_param.u32YOffset = FI.u32LumaAddr & ~MIU_INTERVAL;//u32FrameBufAddr;
#if VIDEO_FIRMWARE_CODE >= VIDEO_FIRMWARE_CODE_HD
    dc_param.u32UVOffset = (FI.u32ChromaAddr & ~MIU_INTERVAL);// + 1920UL*1088UL;//u32FrameBufAddr + 1920UL*1088UL;
    dc_param.bSD = 0;
#else
    dc_param.u32UVOffset = (FI.u32ChromaAddr & ~MIU_INTERVAL);// + 720UL*576UL;//u32FrameBufAddr + 720UL*576UL;
    dc_param.bSD = 1;
#endif
    dc_param.bYUV422 = 0;
    dc_param.bProgressive = (gstVidStatus.u8Interlace) ? 0:1;
    dc_param.bUV7bit = 0;
    dc_param.bDramRdContd = 0;
    dc_param.bField = 0;
    dc_param.b422pack = 0;
    dc_param.u16StripSize = FI.u16Pitch;
    MDrv_MVOP_SetInputCfg(MVOP_INPUT_DRAM, &dc_param);

    memset(&stMvopVidSt, 0, sizeof(MVOP_VidStat));
    stMvopVidSt.u16HorSize   = gstVidStatus.u16HorSize;
    stMvopVidSt.u16VerSize   = gstVidStatus.u16VerSize;
    stMvopVidSt.u16FrameRate = gstVidStatus.u32FrameRate;
    stMvopVidSt.u8AspectRate = gstVidStatus.u8AspectRate;
    stMvopVidSt.u8Interlace  = gstVidStatus.u8Interlace;
    MDrv_MVOP_SetOutputCfg(&stMvopVidSt, FALSE);

    // set scaler window
    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    MDrv_MVOP_Enable( TRUE );

    return TRUE;
}

/******************************************************************************/
/// API for process I frame decoding mailbox msg from Aeon
/// @param *u8MailBox \b IN: pointer to Mail box
/******************************************************************************/
void MApp_IFrame_ProcessMailboxMsg(U8 *u8MailBox)
{
    MBX_Msg mbxMsg;
    U32 u32StreamBufAddr, u32StreamBufEndAddr;
    static U8 u8ColorPalettePatch;
    //MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction = &g_MHEG5Video.stMHEG5VideoAction;
    MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction = &g_MHEG5Video.stMHEG5IFrameAction;
    U32 U32VdecFrameBufferAddr, u32BitStreamAddr;
    U32 u32StreamBufSize = 0;
    BOOLEAN bDecodeResult = FALSE;
    BOOLEAN bCodecTypeIsH264 = FALSE;

    U32 u32FrameBufAddr = 0;
    U32 u32FrameBufSize = 0;
    U32 u32BitstreamBufAddr = 0;
    U32 u32BitstreamBufSize = 0;

    //printf("MApp_IFrame_ProcessMailboxMsg : %x\n",u8MailBox[1]);
    // Command Index
    switch (u8MailBox[1])
    {
        case MB_MPEG_IFRAME_DECODE:
            // Enable Blue Screen
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, ENABLE, NULL, MAIN_WINDOW);
            msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

            u32StreamBufAddr = ((U32)u8MailBox[2])          |
                               (((U32)u8MailBox[3]) << 8)   |
                               (((U32)u8MailBox[4]) << 16)  |
                               (((U32)u8MailBox[5]) << 24);

            u32StreamBufEndAddr = ((U32)u8MailBox[6])          |
                                  (((U32)u8MailBox[7]) << 8)   |
                                  (((U32)u8MailBox[8]) << 16)  |
                                  (((U32)u8MailBox[9]) << 24);

            bCodecTypeIsH264 = u8MailBox[11];
          #if 0
            MVD_DEBUGINFO(printf("u32StreamBufAddr = 0x%08LX\n", u32StreamBufAddr));
            MVD_DEBUGINFO(printf("u32StreamBufEndAddr = 0x%08LX\n", u32StreamBufEndAddr));
          #else // Modified by coverity_0483
            MVD_DEBUGINFO(printf("u32StreamBufAddr = 0x%08lx\n", u32StreamBufAddr));
            MVD_DEBUGINFO(printf("u32StreamBufEndAddr = 0x%08lx\n", u32StreamBufEndAddr));
          #endif

            bDecodeSucceed = false;
            pstMHEG5VideoAction->s16Position_X = 0;
            pstMHEG5VideoAction->s16Position_Y = 0;
            pstMHEG5VideoAction->s16VideoOffset_X = 0;
            pstMHEG5VideoAction->s16VideoOffset_Y = 0;
            pstMHEG5VideoAction->u16BoxSize_X = MHEG_XRES_COORD;
            pstMHEG5VideoAction->u16BoxSize_Y = MHEG_YRES_COORD;
            pstMHEG5VideoAction->u16Scale_Width = MHEG_XRES_COORD;
            pstMHEG5VideoAction->u16Scale_Height = MHEG_YRES_COORD;

            //==> We must stop codec and switch codec before MApi_BDMA_Copy to bitstream addr.
            M5API_VID_Switch2Codec(bCodecTypeIsH264 ? E_VDEC_CODEC_TYPE_H264 : E_VDEC_CODEC_TYPE_MPEG2, TRUE);
            //==<

            //MApi_VDEC_MHEG_RstIFrameDec();

            u32StreamBufAddr = ((u32StreamBufAddr + 0x07) & 0xFFFFFFF8);
            u32StreamBufEndAddr =((u32StreamBufEndAddr + 0x07) & 0xFFFFFFF8);
            u32StreamBufSize = u32StreamBufEndAddr - u32StreamBufAddr;

            u32FrameBufAddr = ((VDEC_FRAMEBUFFER_MEMORY_TYPE&MIU1)?(VDEC_FRAMEBUFFER_ADR|MIU_INTERVAL):VDEC_FRAMEBUFFER_ADR);
            u32FrameBufSize = VDEC_FRAMEBUFFER_LEN;
            u32BitstreamBufAddr = (VDEC_BITSTREAM_MEMORY_TYPE&MIU1)?(VDEC_BITSTREAM_ADR|MIU_INTERVAL):VDEC_BITSTREAM_ADR;
            u32BitstreamBufSize = VDEC_BITSTREAM_LEN;

            //==> Decode Iframe
            if(bCodecTypeIsH264)
            {
                if (VDEC_BITSTREAM_MEMORY_TYPE   & MIU1)
                {
                    u32BitStreamAddr = ((VDEC_BITSTREAM_ADR + 0xA000) | MIU_INTERVAL);
                    //==> Copy to BitStream buffer.
                    MApi_BDMA_Copy(u32StreamBufAddr , u32BitStreamAddr , u32StreamBufSize, MIU_SDRAM02SDRAM1);
                }
                else
                {
                    u32BitStreamAddr = (VDEC_BITSTREAM_ADR + 0xA000);
                    //==> Copy to BitStream buffer.
                    MApi_BDMA_Copy(u32StreamBufAddr , u32BitStreamAddr , u32StreamBufSize, MIU_SDRAM2SDRAM);
                }

                U32VdecFrameBufferAddr =    (VDEC_FRAMEBUFFER_MEMORY_TYPE & MIU1)   ? (u32FrameBufAddr | MIU_INTERVAL) : u32FrameBufAddr;

                //==> Decode H264 Iframe
                bDecodeResult = _MApp_IFrame_Decode_H264( U32VdecFrameBufferAddr, u32BitStreamAddr , (u32BitStreamAddr + u32StreamBufSize));
            }
            else
            {
                if (VDEC_BITSTREAM_MEMORY_TYPE   & MIU1)
                {
                    u32BitStreamAddr = (u32BitstreamBufAddr | MIU_INTERVAL);
                    //==> Copy to BitStream buffer.
                    MApi_BDMA_Copy(u32StreamBufAddr , u32BitStreamAddr , u32StreamBufSize, MIU_SDRAM02SDRAM1);
                }
                else
                {
                    u32BitStreamAddr = u32BitstreamBufAddr;
                    //==> Copy to BitStream buffer.
                    MApi_BDMA_Copy(u32StreamBufAddr , u32BitStreamAddr , u32StreamBufSize, MIU_SDRAM2SDRAM);
                }

                U32VdecFrameBufferAddr =    (VDEC_FRAMEBUFFER_MEMORY_TYPE & MIU1)   ? (u32FrameBufAddr | MIU_INTERVAL) : u32FrameBufAddr;

                //==> Decode MVD Iframe
                bDecodeResult = _MApp_IFrame_Decode( U32VdecFrameBufferAddr , u32BitStreamAddr , (u32BitStreamAddr + u32StreamBufSize));
            }

            if(bDecodeResult)
            {
                //msAPI_IFrame_Show();
                if ( msAPI_VID_GetVidInfo(&gstVidStatus) )
                {
                    u16Scale_Width = MHEG_XRES_COORD;
                    u16Scale_Height = MHEG_YRES_COORD;
                    bDecodeSucceed = true;
                    preH_CapSize = g_MHEG5Video.stARCWin.u16H_CapSize;
                    preV_CapSize = g_MHEG5Video.stARCWin.u16V_CapSize;
                    preH_CapStart = g_MHEG5Video.stARCWin.u16H_CapStart;
                    preV_CapStart = g_MHEG5Video.stARCWin.u16V_CapStart;
                    msAPI_MHEG5_SetGraphInfoRefreshType(SENDARC_AFD_FOR_GE);
                }
            }

            mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
            mbxMsg.u8MsgClass = E_MBX_CLASS_MPEG;
            mbxMsg.u8Index = MB_MHEG5_STATE_CMD_IFRAME_CONTROL;
            mbxMsg.u8ParameterCount = 4;
            mbxMsg.u8Parameters[0] = u8MailBox[2];
            mbxMsg.u8Parameters[1] = u8MailBox[3];
            mbxMsg.u8Parameters[2] = u8MailBox[4];
            mbxMsg.u8Parameters[3] = u8MailBox[5];
            while(E_MBX_SUCCESS != MSApi_MBX_SendMsg(&mbxMsg));

            if ( u8MailBox[10] == DISABLE_COLOR_ENHANCE )
            {
                u8ColorPalettePatch = 1;
            }
            else if (u8MailBox[10] == DISABLE_COLOR_ENHANCE2)
            {
                u8ColorPalettePatch = 2;
            }
            else
            {
                u8ColorPalettePatch = 0;
            }
            break;


        case MB_MPEG_IFRAME_ENABLE:

            if ( u8MailBox[2] )
            {
                if ( bDecodeSucceed )
                {
                    MApp_IFrame_Show(u8ColorPalettePatch);
                }
            }
            else
            {
                if(msAPI_MHEG5_IsIFrameExist())
                {
                    MApp_IFrame_Hide();
                }

                //printf("I:hide\n");
                if ( u8MailBox[3] == ENABLE_COLOR_ENHANCE )
                {
                    //printf("I:TurnOnACE\n");
                    MApi_XC_Sys_ACE_PatchDTGColorChecker(0);
                }
            }
            break;

        case MB_MPEG_IFRAME_SET_POSITION:
        // case MB_MPEG_IFRAME_SCALE_CROP:
            if ( u8MailBox[1] == MB_MPEG_IFRAME_SET_POSITION  )
            {

                u16Position_X = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
                u16Position_Y = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );


                // printk("PO:%d,%d\n",u16Position_X,u16Position_Y);
                if(pstMHEG5VideoAction->s16Position_X != u16Position_X ||
                   pstMHEG5VideoAction->s16Position_Y != u16Position_Y)
                {
                    pstMHEG5VideoAction->s16Position_X = u16Position_X;
                    pstMHEG5VideoAction->s16Position_Y = u16Position_Y;

                    if(g_MHEG5Video.bIFrame)
                    {
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 350, MAIN_WINDOW);
                        MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                    }
                }
            }
            break;

        case MB_MPEG_IFRAME_SET_POSITION_CROP:
            //else if ( u8MailBox[1] == MB_MPEG_IFRAME_SET_VIDOFFSET||
              //   u8MailBox[1] == MB_MPEG_IFRAME_SET_POSITION_CROP )
            {

                pstMHEG5VideoAction->s16VideoOffset_X = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
                pstMHEG5VideoAction->s16VideoOffset_Y = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );
                //printk("MPO:%u,%u\n",pstMHEG5VideoAction->s16VideoOffset_X,pstMHEG5VideoAction->s16VideoOffset_Y);
                //pstMHEG5VideoAction->s16VideoOffset_X = (S16)u16Offset_X;
                //pstMHEG5VideoAction->s16VideoOffset_Y = (S16)u16Offset_Y;

                //printk("PO:%d,%d\n",u16Offset_X,u16Offset_Y);
                if(g_MHEG5Video.bIFrame)
                {
                    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                }
            }
            break;

        case MB_MPEG_IFRAME_SET_VIDOFFSET:
            //else if ( u8MailBox[1] == MB_MPEG_IFRAME_SET_VIDOFFSET||
              //   u8MailBox[1] == MB_MPEG_IFRAME_SET_POSITION_CROP )
            {
                u16Offset_X = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
                u16Offset_Y = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );

                //printk("MPO:%u,%u\n",pstMHEG5VideoAction->s16VideoOffset_X,pstMHEG5VideoAction->s16VideoOffset_Y);

                //printk("PO:%d,%d\n",u16Offset_X,u16Offset_Y);
                if(pstMHEG5VideoAction->s16VideoOffset_X != (S16)u16Offset_X ||
                   pstMHEG5VideoAction->s16VideoOffset_Y != (S16)u16Offset_Y)
                {
                    pstMHEG5VideoAction->s16VideoOffset_X = (S16)u16Offset_X;
                    pstMHEG5VideoAction->s16VideoOffset_Y = (S16)u16Offset_Y;

                    if(g_MHEG5Video.bIFrame)
                    {
                        MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                    }

                }
            }
            break;

        case MB_MPEG_IFRAME_BOXSIZE:
            //else if ( u8MailBox[1] == MB_MPEG_IFRAME_BOXSIZE )
            {

                u16BoxSize_X =  ( ((U16)u8MailBox[2] & 0x00FF) | (((U16)u8MailBox[3] << 8) & 0xFF00) );
                u16BoxSize_Y =  ( ((U16)u8MailBox[4] & 0x00FF) | (((U16)u8MailBox[5] << 8) & 0xFF00) );


                if( pstMHEG5VideoAction->u16BoxSize_X != u16BoxSize_X ||
                    pstMHEG5VideoAction->u16BoxSize_Y != u16BoxSize_Y)
                {
                    pstMHEG5VideoAction->u16BoxSize_X = u16BoxSize_X;//u16BoxSize_X;
                    pstMHEG5VideoAction->u16BoxSize_Y = u16BoxSize_Y;//u16BoxSize_Y;

                    if(g_MHEG5Video.bIFrame)
                    {
                        MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                    }
                }
                // Option = OPTION_SCALE;
            }
            break;

        case MB_MPEG_IFRAME_SCALE:
            //else
            {

                u16Scale_Width =  ( ((U16)u8MailBox[2] & 0x00FF) | (((U16)u8MailBox[3] << 8) & 0xFF00) );
                u16Scale_Height = ( ((U16)u8MailBox[4] & 0x00FF) | (((U16)u8MailBox[5] << 8) & 0xFF00) );


                /*  if ((g_MHEG5Video.eSceneAspectRatio == SCENE_Normal) &&
                   ( u16TempScale_Width == u16Scale_Width && u16TempScale_Height == u16Scale_Height ))
                {
                    return;
                }*/

                //  printk("PO:%d,%d\n",u16Scale_Width,u16Scale_Height);
                /* if ( u8MailBox[1] == MB_MPEG_IFRAME_SCALE_CROP )
                {
                    return;
                }*/
                if(pstMHEG5VideoAction->u16Scale_Width != u16Scale_Width || pstMHEG5VideoAction->u16Scale_Height != u16Scale_Height)
                {
                    pstMHEG5VideoAction->u16Scale_Width = u16Scale_Width;
                    pstMHEG5VideoAction->u16Scale_Height = u16Scale_Height;

                    if(g_MHEG5Video.bIFrame)
                    {
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 350, MAIN_WINDOW);
                        MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                    }
                }
                //  Option = OPTION_SCALE;
            }

            //msAPI_IFrame_Cal_Window(Option);
            break;

        default:
            break;
    }
}


/******************************************************************************/
/// API for hide I frame
/******************************************************************************/
void MApp_IFrame_Hide( void )
{
    g_MHEG5Video.bIFrame = FALSE;
    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, ENABLE, NULL, MAIN_WINDOW);
    MApp_IFrame_ReturnFromDispIFrame();
}


/******************************************************************************/
/// API for display I frame
/// @param u8Patch \b IN: special color settings for i-frame (ON/OFF)
/******************************************************************************/
void MApp_IFrame_Show( U8 u8Patch )
{
    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
    if(u8Patch)
    {
        MApi_XC_Sys_ACE_PatchDTGColorChecker(u8Patch);
    }
    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 300, MAIN_WINDOW);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, NULL, MAIN_WINDOW);
}


/******************************************************************************/
/// API for return from I frame mode to normal video mode
/******************************************************************************/
void MApp_IFrame_ReturnFromDispIFrame()
{

    fEnableSignalMonitor = TRUE;
    fEnableMvdTimingMonitor = TRUE;

    {// reset MVD_TimingMonitor to get hsize,vsize and set mvop/scaler
        //bMVDTimingChange = FALSE;
        //bPrepareChange = TRUE;
        //MApp_MVD_PrepareTimingChange();

        MApp_VID_VariableInit();
    }
//    msAPI_VID_ReturnFromIFrame();
    //MDrv_MVOP_SetInputCfg(MVOP_INPUT_MVD, NULL);

    M5API_VID_Command(MSAPI_VID_STOP);

    //msAPI_VID_Command(MSAPI_VID_PLAY);
}

#endif
#undef MSAPI_IFRAME_C

